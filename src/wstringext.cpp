#include "wstringext.h"


std::wstring toUpperW(const std::wstring &s) {
	std::wstring ret(s.size(), char());
	for (unsigned int i = 0; i < s.size(); ++i) {
		ret[i] = (s[i] <= L'z' && s[i] >= L'a') ? s[i]-(L'a'-L'A') : s[i];
		}
	return ret;
	}

std::wstring toLowerW(const std::wstring &s) {
	std::wstring ret(s.size(), char());
	for (unsigned int i = 0; i < s.size(); ++i) {
		ret[i] = (s[i] <= L'Z' && s[i] >= L'A') ? s[i]-(L'A'-L'a') : s[i];
		}
	return ret;
	}
std::wstring getexepathW() {
	// https://stackoverflow.com/a/19535628
	wchar_t result[ MAX_PATH ];
	return std::wstring( result, GetModuleFileNameW( NULL, result, MAX_PATH ) );
	}
std::wstring getFilenamePathW (const std::wstring &str) {
	// getFilenamePath file   -- returns: "g:\subdir1\subdir2\"
	wchar_t found;
	std::wstring strt;
	found = str.find_last_of(L"/\\");
	if (found != std::wstring::npos) {
		strt = str.substr(0, found);
		return (strt + L"\\");
		}
	else {
		return L"";
		}
	}

std::wstring openfilenameW(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL, unsigned long flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY) {
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

std::wstring getFilenameFileW(const std::wstring &str) {
	// getFilenameFile file   -- returns: "myImage"
	wchar_t found;
	std::wstring strt;
	found = str.find_last_of(L"/\\");
	if (found < str.size()) {
		strt = str.substr(found + 1, -1);
		found = strt.find(L".");
		if (found < strt.size()) {
			strt = strt.substr(0, found);
			}
		//return strt;
		}
	else {
		strt = str;
		//return str;
		}
	size_t lastdot = strt.find_last_of(L".");
	if (lastdot == std::string::npos) return strt;
	return strt.substr(0, lastdot);
	}

std::wstring getFilenameTypeW (std::wstring const &path ) {
	// getFilenameType file -- returns: ".jpg"
	/*
	std::wstring ext;
	wchar_t dotIdx = path.find_last_of( L"." );
	if ( dotIdx != std::wstring::npos ) {
		wchar_t dirSepIdx = path.find_last_of( L"/\\" );
		if ( dotIdx > dirSepIdx + 1 ) {
			ext = path.substr( dotIdx );
			}
		}
	*/

	return (std::wstring(PathFindExtensionW((wchar_t*)path.c_str())));

	//return ext;
	}

std::wstring ReplaceAll(std::wstring str, const std::wstring& from, const std::wstring& to) {
    // https://stackoverflow.com/a/24315631
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
    return str;
    }

std::wstring string_to_wstring (std::string s) {
	// http://blog.mijalko.com/2008/06/convert-stdstring-to-stdwstring.html
	std::wstring ws;
	return ws.assign(s.begin(), s.end());
	}

static int CALLBACK BrowseCallbackProcW(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
    if(uMsg == BFFM_INITIALIZED) {
        std::wstring tmp = (const wchar_t *) lpData;
        std::wcout << L"path: " << tmp << std::endl;
        SendMessageW(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		}
    return 0;
	}

std::wstring getSavePathW(std::wstring defaultPath, const wchar_t* szCaption, unsigned int flags, HWND hOwner) {

	std::wstring folderpath = L"";
	// The BROWSEINFO struct tells the shell
	// how it should display the dialog.
	BROWSEINFOW bi;
	memset(&bi, 0, sizeof(bi));
	bi.ulFlags   = flags;//BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.hwndOwner = hOwner;
	bi.lpszTitle = szCaption;
    bi.lpfn      = BrowseCallbackProcW;
    bi.lParam    = (LPARAM)defaultPath.c_str();

	// must call this if using BIF_USENEWUI
	if (BIF_USENEWUI | flags) {
		OleInitialize(NULL);
		}


	// Show the dialog and get the itemIDList for the
	// selected folder.
	LPITEMIDLIST pIDL = ::SHBrowseForFolderW(&bi);

	if(pIDL != NULL) {
		// Create a buffer to store the path, then
		// get the path.
		wchar_t buffer[MAX_PATH] = {'\0'};
		if(SHGetPathFromIDListW(pIDL, buffer) != 0) {
			// Set the string value.
			folderpath = buffer;

			}

		// free the item id list
		CoTaskMemFree(pIDL);
		}
	if (BIF_USENEWUI | flags) {
		OleUninitialize();
		}
	return folderpath;
	}

void getFilesW (std::wstring pattern, std::vector<std::wstring> &v) {
    std::wstring path = getFilenamePathW(pattern);
    WIN32_FIND_DATAW data;
    HANDLE hFind;
    if ((hFind = FindFirstFileW(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
    do {v.insert( v.end(), (path + data.cFileName));}
    while (FindNextFileW(hFind, &data) != 0);
        FindClose(hFind);
        }
    }
