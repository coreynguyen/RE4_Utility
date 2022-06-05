#include "windows.h"
#include "stringext.h"
/*
std::string ltrim(std::string str) {
	std::string::const_iterator it =  std::find_if( str.begin() , str.end() , [](unsigned char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
	str.erase( str.begin() , it);
	return str;
	}

std::string rtrim(std::string str) {
	std::string::const_iterator it =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
	str.erase( it.base() , str.end() );
	return str;
	}
	*/
//std::string rtrim(std::string str) {
//	int start2 = 0, end2 = str.length() - 1;
//	while(isspace(str[start2]) || isspace(str[end2])) {
//		if(isspace(str[start2])) {start2++;}
//		if(isspace(str[end2])) {end2--;}
//		}
//	str.erase(0,start2);
//	str.erase((end2 - start2) + 1);
//	return str;
//	}
std::string padString (std::string str, unsigned int len, std::string pad, bool addToLeft) {
	std::string temp = str;
	std::string padding = "";
	if (temp.size() > len) {
		temp = temp.substr(0, len);
		}
	if ((len - temp.size()) > 0) {
		for (unsigned int i = 0; i < ((len - temp.size())); i++){
			padding += pad;
			}
		}
	if (addToLeft) {
		return (padding + temp);
		}
	else {
		return (temp + padding);
		}
	}
std::string toupper(const std::string & s) {
	std::string ret(s.size(), char());
	for(unsigned int i = 0; i < s.size(); ++i) {
		ret[i] = (s[i] <= 'z' && s[i] >= 'a') ? s[i]-('a'-'A') : s[i];
		}
	return ret;
	}
std::string tolower(const std::string &s) {
	std::string ret(s.size(), char());
	for (unsigned int i = 0; i < s.size(); ++i) {
		ret[i] = (s[i] <= 'Z' && s[i] >= 'A') ? s[i]-('A'-'a') : s[i];
		}
	return ret;
	}
std::string openfilename(const char* filter, HWND owner) {
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
std::string savefilename(const char* filter, HWND owner) {
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

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
    if(uMsg == BFFM_INITIALIZED) {
        std::string tmp = (const char *) lpData;
        std::cout << "path: " << tmp << std::endl;
        SendMessageA(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		}
    return 0;
	}

std::string getSavePath(std::string defaultPath, const char* szCaption, unsigned int flags, HWND hOwner) {

	std::string folderpath = "";
	// The BROWSEINFO struct tells the shell
	// how it should display the dialog.
	BROWSEINFOA bi;
	memset(&bi, 0, sizeof(bi));
	bi.ulFlags   = flags;//BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.hwndOwner = hOwner;
	bi.lpszTitle = szCaption;
    bi.lpfn      = BrowseCallbackProc;
    bi.lParam    = (LPARAM)defaultPath.c_str();

	// must call this if using BIF_USENEWUI
	if (BIF_USENEWUI | flags) {
		OleInitialize(NULL);
		}


	// Show the dialog and get the itemIDList for the
	// selected folder.
	LPITEMIDLIST pIDL = ::SHBrowseForFolderA(&bi);

	if(pIDL != NULL) {
		// Create a buffer to store the path, then
		// get the path.
		char buffer[MAX_PATH] = {'\0'};
		if(SHGetPathFromIDListA(pIDL, buffer) != 0) {
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


std::string getFilenameType(std::string const & path ) {
	/*
	std::string ext;

	// Find the last dot, if any.
	size_t dotIdx = path.find_last_of( "." );
	if ( dotIdx != std::string::npos ) {
		// Find the last directory separator, if any.
		size_t dirSepIdx = path.find_last_of( "/\\" );

		// If the dot is at the beginning of the file name, do not treat it as a file extension.
		// e.g., a hidden file:  ".alpha".
		// This test also incidentally avoids a dot that is really a current directory indicator.
		// e.g.:  "alpha/./bravo"
		if ( dotIdx > dirSepIdx + 1 ) {
			ext = path.substr( dotIdx );
			}
		}
	return ext;
	*/
	return std::string(PathFindExtensionA(path.c_str()));
	}
std::string getexepath() {
	// https://stackoverflow.com/a/19535628
	char result[ MAX_PATH ];
	return std::string( result, GetModuleFileNameA( NULL, result, MAX_PATH ) );
	}
std::string getFilenamePathRoot(const std::string &str) {
    size_t found;
    std::string strt;
    found = str.find_last_of("/\\");
    if (found < str.size()) {
        strt = str.substr(0, found);
        found = strt.find_last_of("/\\");
        return strt.substr(found + 1, -1);
        }
    else {
        return str;
        }
    }
std::string getFilenamePath (const std::string &str) {
    // getFilenamePath file   -- returns: "g:\subdir1\subdir2\"
    size_t found;
    std::string strt;
    found = str.find_last_of("/\\");
    if (found < str.size()) {
        strt = str.substr(0, found);
        return (strt + "\\");
        }
    else {
        return "";
        }
    }
std::string filenameFromPath(const std::string &str) {
    // filenameFromPath file  -- returns: "myImage.jpg"
    size_t found;
    std::string strt;
    found = str.find_last_of("/\\");
    if (found < str.size()) {
        strt = str.substr(found + 1, -1);
        return strt;
        }
    else {
        return str;
        }
    }
std::string getFilenameFile(const std::string &str) {
    // getFilenameFile file   -- returns: "myImage"
    size_t found;
    std::string strt;
    found = str.find_last_of("/\\");
    if (found < str.size()) {
        strt = str.substr(found + 1, -1);
        found = strt.find(".");
        if (found < strt.size()) {
            strt = strt.substr(0, found);
            }
        //return strt;
        }
    else {
		strt = str;
        //return str;
        }
    size_t lastdot = strt.find_last_of(".");
    if (lastdot == std::string::npos) return strt;
    return strt.substr(0, lastdot);
	}

std::vector<std::string> split(std::string str, std::string token) {
    // https://stackoverflow.com/a/46943631
    /*
    std::vector<std::string>result;
    while (str.size() ){
        unsigned int index = str.find(token);
        if(index!=std::string::npos) {
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
            }
        else {
            result.push_back(str);
            str = "";
            }
        }
    return result;
    */
    // https://tousu.in/qa/?qa=451507/
	std::vector<std::string> wordVector;
	std::stringstream stringStream(str);
	std::string line;
	while(std::getline(stringStream, line)) {
		std::size_t prev = 0, pos;
		while ((pos = line.find_first_of(token, prev)) != std::string::npos) {
			if (pos > prev) {
				wordVector.push_back(line.substr(prev, pos-prev));
				}
			prev = pos + 1;
			}
		if (prev < line.length()) {
			wordVector.push_back(line.substr(prev, std::string::npos));
			}
		}
	return wordVector;
    }

std::string trim(const std::string& str, const std::string& whitespace) {
    // https://stackoverflow.com/a/1798170
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
	}

std::string reduce(const std::string& str, const std::string& fill, const std::string& whitespace) {
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos) {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
		}

    return result;
	}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    // https://stackoverflow.com/a/24315631
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
    return str;
    }

std::string get_part_date(const std::string &datepart, time_t now) {
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    //time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), datepart.c_str(), &tstruct);
    return buf;
	}
std::string wstring_to_string (std::wstring ws) {
	// http://blog.mijalko.com/2008/06/convert-stdstring-to-stdwstring.html
	std::string s;
	return s.assign(ws.begin(), ws.end());
	}
std::string IntToHexString(int number, int length) {
    std::string s;
    std::ostringstream temp;
    temp << std::hex << number;
    s = toupper(temp.str());
    s.insert(s.begin(), length - s.length(), '0');
    return ("0x" + s);
    }
void getFiles (std::string pattern, std::vector<std::string> &v) {
    std::string path = getFilenamePath(pattern);
    WIN32_FIND_DATAA data;
    HANDLE hFind;
    if ((hFind = FindFirstFileA(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
    do {v.insert( v.end(), (path + data.cFileName));}
    while (FindNextFileA(hFind, &data) != 0);
        FindClose(hFind);
        }
    }
void pause (bool useSystem) {
	if (useSystem) {
		system("pause");
		}
	else {
		std::cout << "Press ENTER to continue...";
		std::cin.clear();
		std::cin.sync();
		std::cin.get();
		//getchar();
		}
	}
