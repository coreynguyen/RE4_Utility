#include "registry.h"

int reg::create_key_path(HKEY hKey, const char *sPath) {
	char sDir[MAX_PATH];

	int iNameSz = (int)strlen(sPath);
	int iCount = 0;
	int iPos = 0;

	for (iPos = 0; iPos < iNameSz; iPos++) {
		if (sPath[iPos] == '\\' || sPath[iPos] == '/') {
			sDir[iPos] = '\0';
			if (create_key(hKey, sDir)) {
				iCount++;
				}
			}
		sDir[iPos] = sPath[iPos];
		}

	sDir[iPos] = '\0';
	if (create_key(hKey, sDir)) {
		iCount++;
		}
	return iCount;
	}

bool reg::create_key(HKEY hKeyRoot, const char* pszSubKey) {
	HKEY hKey;
	DWORD dwFunc;
	LONG  lRet;

	//------------------------------------------------------------------------------

	SECURITY_DESCRIPTOR SD;
	SECURITY_ATTRIBUTES SA;

	if (!InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION))
	return false;

	if (!SetSecurityDescriptorDacl(&SD, true, 0, false))
	return false;

	SA.nLength = sizeof(SA);
	SA.lpSecurityDescriptor = &SD;
	SA.bInheritHandle = false;

	//------------------------------------------------------------------------------

	lRet = RegCreateKeyExA(
		hKeyRoot,
		pszSubKey,
		0,
		(char*)NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		&SA,
		&hKey,
		&dwFunc
		);

	if (lRet == ERROR_SUCCESS) {
		RegCloseKey(hKey);
		hKey = (HKEY)NULL;
		return true;
		}

	SetLastError((DWORD)lRet);
	return false;
	}

bool reg::remove_key(HKEY hKeyRoot, const char* pszSubKey) {

	DWORD dwRet = ERROR_SUCCESS;
	if (RegDeleteKeyA(hKeyRoot, pszSubKey) != ERROR_SUCCESS) {
		HINSTANCE hLibInst = LoadLibraryA("shlwapi.dll");

		if (!hLibInst) {
			//throw ERROR_NO_SHLWAPI_DLL;
			}

		typedef DWORD(__stdcall* SHDELKEYPROC)(HKEY, const char*);
		SHDELKEYPROC DeleteKeyRecursiveA = (SHDELKEYPROC)GetProcAddress(hLibInst, "SHDeleteKeyA");
		//#if defined(UNICODE) || defined(_UNICODE)
		//	SHDELKEYPROC DeleteKeyRecursive = (SHDELKEYPROC)GetProcAddress(hLibInst, "SHDeleteKeyW");
		//#else
		//	SHDELKEYPROC DeleteKeyRecursive = (SHDELKEYPROC)GetProcAddress(hLibInst, "SHDeleteKeyA");
		//#endif

		if (!DeleteKeyRecursiveA) {
			FreeLibrary(hLibInst);
			return false;
			}

		dwRet = DeleteKeyRecursiveA(hKeyRoot, pszSubKey);

		FreeLibrary(hLibInst);
		}

	if (dwRet == ERROR_SUCCESS) {
		return true;
		}

	SetLastError(dwRet);
	return false;
	}

bool reg::remove(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue) {

	HKEY hKey;
	LONG lRes;

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_SET_VALUE, &hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError((DWORD)lRes);
		return false;
		}

	lRes = RegDeleteValueA(hKey, pszValue);

	RegCloseKey(hKey);

	if (lRes == ERROR_SUCCESS) {
		return true;
		}

	SetLastError(lRes);
	return false;
	}

bool reg::read_binary(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, PVOID pBuffer, DWORD& rdwSize) {

	HKEY  hKey;
	DWORD dwType = REG_BINARY;
	DWORD dwSize = rdwSize;
	LONG lRes = 0;

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_READ, &hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError((DWORD)lRes);
		return false;
		}

	lRes = RegQueryValueExA(hKey, pszValue, 0, &dwType, (LPBYTE)pBuffer, &dwSize);

	rdwSize = dwSize;
	RegCloseKey(hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	if (dwType != REG_BINARY) {
		//throw ERROR_WRONG_TYPE;
		}

	return true;
	}

bool reg::read_integer(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, unsigned __int64 &u64Buff) {

	HKEY hKey;
	DWORD dwType = REG_QWORD;
	DWORD dwSize = sizeof(u64Buff);
	LONG  lRes;

	u64Buff = 0;

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_READ, &hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	lRes = RegQueryValueExA(hKey, pszValue, 0, &dwType, (LPBYTE)&u64Buff, &dwSize);

	RegCloseKey(hKey);

	if (dwType != REG_QWORD) {
		//throw ERROR_WRONG_TYPE;
		}

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	return true;
	}

bool reg::read_integer(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, unsigned long &ulBuff) {

	HKEY hKey;
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(ulBuff);
	LONG  lRes;

	ulBuff = 0;

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_READ, &hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	lRes = RegQueryValueExA(hKey, pszValue, 0, &dwType, (LPBYTE)&ulBuff, &dwSize);

	RegCloseKey(hKey);

	if (dwType != REG_DWORD) {
		//throw ERROR_WRONG_TYPE;
		}

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}


	return true;
	}

bool reg::read_string(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, std::string &strOutValue) {

	HKEY  hKey;
	LONG  lRes;
	char  pszBuffer[1025] = {0};
	DWORD rdwSize = sizeof(pszBuffer);
	DWORD dwType = KEY_ALL_ACCESS;
	strOutValue = "";

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_READ, &hKey);
	if (lRes != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		SetLastError(lRes);
		std::cout << "failed to open key" << std::endl;
		return false;
		}
	lRes = RegQueryValueExA(hKey, pszValue, NULL, &dwType, (LPBYTE)pszBuffer, &rdwSize);

	if (lRes != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		SetLastError(lRes);
		std::cout << "failed to read key" << std::endl;
		return false;
		}

	lRes = RegCloseKey(hKey);
	if (lRes != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		SetLastError(lRes);
		std::cout << "failed to close key" << std::endl;
		return false;
		}

	strOutValue = pszBuffer;

	return true;
	}

bool reg::write_binary(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, PVOID pData, DWORD dwSize) {

	HKEY hKey;
	LONG lRes = 0;

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	lRes = RegSetValueExA(hKey, pszValue, 0, REG_BINARY, (unsigned char*)pData, dwSize);

	RegCloseKey(hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	return true;
	}

bool reg::write_integer(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, unsigned long ulValue) {

	HKEY hKey;
	LONG lRes;

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	lRes = RegSetValueExA(hKey, pszValue, 0, REG_DWORD, (unsigned char*)&ulValue, sizeof(ulValue));

	RegCloseKey(hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	return true;
	}

bool reg::write_integer(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, unsigned __int64 u64Value) {

	HKEY hKey;
	LONG lRes;

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	lRes = RegSetValueExA(hKey, pszValue, 0, REG_QWORD, (LPBYTE)&u64Value, sizeof(u64Value));

	RegCloseKey(hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	return true;
	}

bool reg::write_string(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, const char* pszString) {

	HKEY  hKey;
	LONG  lRes;
	DWORD dwSize = lstrlenA(pszString) * sizeof(char);

	lRes = RegOpenKeyExA(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	lRes = RegSetValueExA(hKey, pszValue, 0, REG_SZ, (unsigned char*)pszString, dwSize);

	RegCloseKey(hKey);

	if (lRes != ERROR_SUCCESS) {
		SetLastError(lRes);
		return false;
		}

	return true;
	}

bool reg::write_bool(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, bool bVal) {

	DWORD dwVal = 0;
	if (bVal) {
		dwVal = 1;
		}
	return write_integer(hKeyRoot, pszSubKey, pszValue, dwVal);
	}

bool reg::read_bool(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue) {

	DWORD dwVal = 0;
	if (read_integer(hKeyRoot, pszSubKey, pszValue, dwVal)) {
		return (dwVal > 0);
		}
	return false;
	}

