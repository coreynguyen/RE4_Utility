#include "wregistry.h"

bool wreg::read_string(HKEY hKeyRoot, const wchar_t* pszSubKey, const wchar_t* pszValue, std::wstring &strOutValue) {

	HKEY  hKey;
	LONG  lRes;
	wchar_t  pszBuffer[1025] = {0};
	DWORD rdwSize = sizeof(pszBuffer);
	DWORD dwType = KEY_ALL_ACCESS;
	strOutValue = L"";

	lRes = RegOpenKeyExW(hKeyRoot, pszSubKey, 0, KEY_READ, &hKey);
	if (lRes != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		SetLastError(lRes);
		std::wcout << L"failed to open key" << std::endl;
		return false;
		}
	lRes = RegQueryValueExW(hKey, pszValue, NULL, &dwType, (LPBYTE)pszBuffer, &rdwSize);

	if (lRes != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		SetLastError(lRes);
		std::wcout << L"failed to read key" << std::endl;
		return false;
		}

	lRes = RegCloseKey(hKey);
	if (lRes != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		SetLastError(lRes);
		std::wcout << L"failed to close key" << std::endl;
		return false;
		}

	strOutValue = pszBuffer;

	return true;
	}
