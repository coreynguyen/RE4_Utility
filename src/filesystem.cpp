#include "filesystem.h"

std::wstring win::openfilenameW(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL, unsigned long flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY) {
	// add to link -lcomdlg32 -lole32
	std::wstring filename(MAX_PATH, L'\0');
	OPENFILENAMEW ofn = { };
	//ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); //sizeof(LPOPENFILENAMEW);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = &filename[0];  // use the std::wstring buffer directly
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Select a File";
	ofn.Flags = flags;
	//OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_EXPLORER| OFN_ALLOWMULTISELECT|OFN_NOCHANGEDIR|OFN_HIDEREADONLY| OFN_SHAREAWARE;
	if (!GetOpenFileNameW(&ofn)) {return L"";}
	//std::size_t firstScan = filename.find_first_not_of("\0");
	//std::size_t first = 0;
	//if (firstScan == std::string::npos) {first = filename.length();}
	//else {first = firstScan;}
	//std::size_t last = filename.find_last_not_of("\0");
	//return filename.substr(first, last-first+1);
	return filename;
	}
std::string win::openfilename(const char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
	// add to link -lcomdlg32 -lole32
	OPENFILENAMEA ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	std::string fileNameStr = "";
	if (GetOpenFileNameA(&ofn)) {
		fileNameStr = fileName;
		}
	return fileNameStr;
	}
std::string win::savefilename(const char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
	// add to link -lcomdlg32 -lole32
	OPENFILENAMEA ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	std::string fileNameStr;
	if (GetSaveFileNameA(&ofn)) {
		fileNameStr = fileName;
		}
	return fileNameStr;
	}

int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData){
    char dir[MAX_PATH];
    ITEMIDLIST *lpid;
        HWND hEdit;

        switch (uMsg){
        case BFFM_INITIALIZED:
                SendMessageA(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
                break;
        case BFFM_VALIDATEFAILED:
                MessageBoxA(hWnd,(char*)lParam,"error",MB_OK);
                hEdit=FindWindowExA(hWnd,NULL,"EDIT",NULL);
                SetWindowTextA(hEdit,"");
                return 1;
                break;

        case BFFM_SELCHANGED:
                lpid=(ITEMIDLIST *)lParam;
                SHGetPathFromIDListA(lpid,dir);
                hEdit=FindWindowExA(hWnd,NULL,"EDIT",NULL);
                SetWindowTextA(hEdit,dir);
                break;
        }
        return 0;
}

bool GetDir() {
	HWND hWnd = NULL;
	std::string def_dir = "";
	char path[MAX_PATH];

	BROWSEINFOA bInfo;
	LPITEMIDLIST pIDList;

	memset(&bInfo,0,sizeof(bInfo));
	bInfo.hwndOwner = hWnd;
	bInfo.pidlRoot = NULL;
	bInfo.pszDisplayName = (char*)path;
	bInfo.lpszTitle = "ok";
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_VALIDATE | BIF_NEWDIALOGSTYLE;
	bInfo.lpfn = BrowseCallbackProc;
	bInfo.lParam = (LPARAM)def_dir.c_str();
	pIDList = SHBrowseForFolderA(&bInfo);
	if (pIDList == NULL){
		path[0] = '\0';
		return false;
		}
	else {
		if (!SHGetPathFromIDListA(pIDList,(char*) path))
		return false;
		CoTaskMemFree(pIDList);
		return true;
		}
	return false;
	}

size_t win::getFileSize (std::string fileName) {
	/*
	std::ifstream file(name.c_str(), std::ios::binary | std::ios::ate );
	size_t fileSize = file.tellg();
	file.close();
	return fileSize;
	*/
	// Native Solution (therefore faster)
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesExA((char*)fileName.c_str(), GetFileExInfoStandard, &fad))
		return -1; // error condition, could call GetLastError to find out more
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return size.QuadPart;
	}

size_t win::getFileSizeW(std::wstring fileName) {
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesExW((wchar_t*)fileName.c_str(), GetFileExInfoStandard, &fad))
		return -1; // error condition, could call GetLastError to find out more
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return size.QuadPart;
	}

bool win::doesFileExist (std::string fileName) {
	//std::ifstream infile(fileName.c_str());
	//return infile.good();
	DWORD dwAttrib = GetFileAttributesA(fileName.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}

bool win::doesFileExistW (std::wstring fileName) {
	/*	Old function that used fstream

	std::ifstream infile(fileName.c_str());
	return infile.good();
	*/

	/*	Old function that used File Attributes

	DWORD dwAttrib = GetFileAttributesW((wchar_t*)fileName.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	*/
	return (PathFileExistsW((wchar_t*)fileName.c_str()));
	// add to link -lshlwapi
	}

bool win::doesFolderExist (std::string dirName_in) {
	//DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) {
		return false;  //something is wrong with your path!
		}
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
		return true;   // this is a directory!
		}
	return false;    // this is not a directory!
	}

bool win::doesFolderExistW (std::wstring dirName_in) {
	//DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	DWORD ftyp = GetFileAttributesW((wchar_t*)dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) {
		return false;  //something is wrong with your path!
		}
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
		return true;   // this is a directory!
		}
	return false;    // this is not a directory!
	}

bool win::makeDirW(std::wstring wsPath) {
	// https://www.codeguru.com/cpp/w-p/files/article.php/c4439/CreatePath--Full-Path-Creation-wstring-version.htm
	unsigned long attr;
	size_t pos;
	bool result = false;
	std::wstring tmp;

	// Check for trailing slash:
	/* I dont understand what this code is doing
	pos = wsPath.find_last_of(L"\\");

	if (wsPath.length() == pos + 1) { // last character is "\"
		wsPath.resize(pos);
		}
	*/
	if (wsPath.length() > 0) {
		if (wsPath[wsPath.length() - 1] != '\\') {
			wsPath += L"\\";
			}
		// Look for existing object:
		attr = GetFileAttributesW(wsPath.c_str());

		//std::wcout << "CreatingFolder:\t" << wsPath << std::endl;
		//std::wcout << "Attribute:\t" << attr << std::endl;
		if (attr == 0xFFFFFFFF) { // doesn't exist yet - create it!
			pos = wsPath.find_last_of(L"\\", wsPath.length() - 2);
			//pos = wsPath.find_first_of(L"\\/");
			//std::wcout << "POS:\t" << pos << std::endl;
			if (pos != std::wstring::npos) {
				// Create parent dirs:
				//std::wcout << L"Build\t" << wsPath.substr(0, pos + 1) << std::endl;
				result = makeDirW(wsPath.substr(0, pos + 1));
				}
			// Create node:
			result = result && CreateDirectoryW(wsPath.c_str(), NULL);
			//std::wcout << wsPath << std::endl;
			CreateDirectoryW(wsPath.c_str(), NULL);
			}
		else if (FILE_ATTRIBUTE_DIRECTORY != attr) {  // object already exists, but is not a dir
			//SetLastError(ERROR_FILE_EXISTS);
			result = false;
			}
		}
	return result;
	}

bool win::makeDir(std::string sPath) {
	// https://www.codeguru.com/cpp/w-p/files/article.php/c4439/CreatePath--Full-Path-Creation-wstring-version.htm
	unsigned long attr;
	size_t pos;
	bool result = false;
	std::string tmp;

	// Check for trailing slash:
	/* I dont understand what this code is doing
	pos = sPath.find_last_of(L"\\");

	if (sPath.length() == pos + 1) { // last character is "\"
		sPath.resize(pos);
		}
	*/
	if (sPath.length() > 0) {
		if (sPath[sPath.length() - 1] != '\\') {
			sPath += "\\";
			}
		// Look for existing object:
		attr = GetFileAttributesA(sPath.c_str());

		//std::wcout << "CreatingFolder:\t" << sPath << std::endl;
		//std::wcout << "Attribute:\t" << attr << std::endl;
		if (attr == 0xFFFFFFFF) { // doesn't exist yet - create it!
			pos = sPath.find_last_of("\\", sPath.length() - 2);
			//pos = sPath.find_first_of(L"\\/");
			//std::wcout << "POS:\t" << pos << std::endl;
			if (pos != std::string::npos) {
				// Create parent dirs:
				//std::wcout << L"Build\t" << sPath.substr(0, pos + 1) << std::endl;
				result = makeDir(sPath.substr(0, pos + 1));
				}
			// Create node:
			result = result && CreateDirectoryA(sPath.c_str(), NULL);
			CreateDirectoryA(sPath.c_str(), NULL);
			}
		else if (FILE_ATTRIBUTE_DIRECTORY != attr) {  // object already exists, but is not a dir
			//SetLastError(ERROR_FILE_EXISTS);
			result = false;
			}
		}
	return result;
	}

bool win::copyFile (std::string existing_filename, std::string target_filename) {
	bool result = CopyFileA (existing_filename.c_str(), target_filename.c_str(), true);
	return result;
	}

bool win::copyFileW (std::wstring existing_filename, std::wstring target_filename) {
	bool result = CopyFileW ((wchar_t*)existing_filename.c_str(), (wchar_t*)target_filename.c_str(), true);
	return result;
	}

bool win::moveFileW (std::wstring existing_filename, std::wstring target_filename) {
	bool result = MoveFileW ((wchar_t*)existing_filename.c_str(), (wchar_t*)target_filename.c_str());
	return result;
	}

void win::getFilesW (std::wstring* &dirFiles, unsigned long &numFiles, std::wstring pattern) {
	// http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
	/*
	std::wstring* dirFiles = NULL;
	unsigned long numFiles = 0;
	getFilesW(dirFiles, numFiles, L"G:\\SteamLibrary\\steamapps\\common\\Tomb Raider (VI) The Angel of Darkness\\data\\Maps\\unGMX_v.1.0\\_CLZ\\*.clz");
	std::cout << "NumFiles:\t" << numFiles << endl;
	for (unsigned long i = 0; i < numFiles; i++) {
		std::wcout << numFiles << L"\t" << dirFiles[i] << endl;
		}
	if (dirFiles!=NULL){delete[] dirFiles;}
	*/
	WIN32_FIND_DATAW data;
	HANDLE hFind;
	numFiles = 0;
	std::wstring fullPathW;
	if ((hFind = FindFirstFileW((wchar_t*)pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0x10 ) {
				fullPathW = getFilenamePathW(pattern);

				if (win::doesFileExistW(fullPathW + data.cFileName)) {
					numFiles++;
					//fileList.insert( fileList.end(), (fullPath + data.cFileName));
					}
				}

			} while (FindNextFileW(hFind, &data) != 0);
		FindClose(hFind);
		}
	if (numFiles > 0) {
		dirFiles = new std::wstring[numFiles];
		numFiles = 0;
		if ((hFind = FindFirstFileW((wchar_t*)pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
			do {
				if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0x10) {
					fullPathW = getFilenamePathW(pattern);
					if (win::doesFileExistW(fullPathW + data.cFileName)) {
						dirFiles[numFiles] = fullPathW + data.cFileName;
						numFiles++;
						}
					}
				} while (FindNextFileW(hFind, &data) != 0);
			FindClose(hFind);
			}
		}
	}

void win::getFiles (std::string* &dirFiles, unsigned long &numFiles, std::string pattern) {
	// http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
	/*
	std::wstring* dirFiles = NULL;
	unsigned long numFiles = 0;
	getFilesW(dirFiles, numFiles, L"G:\\SteamLibrary\\steamapps\\common\\Tomb Raider (VI) The Angel of Darkness\\data\\Maps\\unGMX_v.1.0\\_CLZ\\*.clz");
	std::cout << "NumFiles:\t" << numFiles << endl;
	for (unsigned long i = 0; i < numFiles; i++) {
		std::wcout << numFiles << L"\t" << dirFiles[i] << endl;
		}
	if (dirFiles!=NULL){delete[] dirFiles;}
	*/
	WIN32_FIND_DATAA data;
	HANDLE hFind;
	numFiles = 0;
	std::string fullPath;
	if ((hFind = FindFirstFileA((char*)pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0x10 ) {
				fullPath = getFilenamePath(pattern);

				if (win::doesFileExist(fullPath + data.cFileName)) {
					numFiles++;
					//fileList.insert( fileList.end(), (fullPath + data.cFileName));
					}
				}

			} while (FindNextFileA(hFind, &data) != 0);
		FindClose(hFind);
		}
	if (numFiles > 0) {
		dirFiles = new std::string[numFiles];
		numFiles = 0;
		if ((hFind = FindFirstFileA((char*)pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
			do {
				if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0x10) {
					fullPath = getFilenamePath(pattern);
					if (win::doesFileExist(fullPath + data.cFileName)) {
						dirFiles[numFiles] = fullPath + data.cFileName;
						numFiles++;
						}
					}
				} while (FindNextFileA(hFind, &data) != 0);
			FindClose(hFind);
			}
		}
	}

std::string win::runningPath(bool pathOnly) {
	// https://stackoverflow.com/a/13310600
	char szFilePath[MAX_PATH + 1] = { 0 };
	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL) {
		// Use GetModuleFileName() with module handle to get the path
		GetModuleFileNameA(hModule, szFilePath, (sizeof(szFilePath)));
		//cout << szFilePath << endl;
		//system("PAUSE");
		if (pathOnly) {
			 // Delete the file name, only get the path string //
			(strrchr(szFilePath,'\\'))[0] = 0;
			}
		return (std::string)szFilePath;
		}
	else {
		//cout << "Module handle is NULL" << endl ;
		//system("PAUSE");
		return "";
		}
	return "";
	}

std::wstring win::runningPathW() {
	// https://stackoverflow.com/a/13310600
	wchar_t ownPth[MAX_PATH];
	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL) {
		// Use GetModuleFileName() with module handle to get the path
		GetModuleFileNameW(hModule, ownPth, (sizeof(ownPth)));
		//cout << ownPth << endl;
		//system("PAUSE");
		return (std::wstring)ownPth;
		}
	else {
		//cout << "Module handle is NULL" << endl ;
		//system("PAUSE");
		return L"";
		}
	}

