/*	======================================================================

	Title:		Windows File System Helper Library
	Author:		mariokart64n
	Version:	0.1
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		General helper class for accessing files on windows

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2019-01-28]
		wrote it!

	======================================================================	*/
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <cstring>
#include <windows.h>
#include <shlwapi.h>
#include <tchar.h>
#include <strings.h>
#include <wchar.h>
#include "stringext.h"
#include "wstringext.h"



namespace win {
    std::string fixTrailingSlash (std::string path, bool addSlash = true);
    std::wstring fixTrailingSlashW (std::wstring path, bool addSlash = true);
    std::string amendRelativePath (std::string relPath, std::string basePath);
    std::wstring amendRelativePathW (std::wstring relPath, std::wstring basePath);
	std::wstring openfilenameW(const wchar_t* filter, HWND owner, unsigned long flags);
	std::string openfilename(const char *filter, HWND owner);
	std::string savefilename(const char *filter, HWND owner);


	int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	bool GetDir();


    bool is_absolute_path (std::string path);
    bool is_absolute_pathW (std::wstring path);
	size_t getFileSize (std::string fileName);
	size_t getFileSizeW(std::wstring fileName);
	bool doesFileExist (std::string fileName);
	bool doesFileExistW (std::wstring fileName);
	bool doesFolderExist (std::string dirName_in);
	bool doesFolderExistW (std::wstring dirName_in);
	bool makeDirW(std::wstring wsPath);
	bool makeDir(std::string sPath);
	bool copyFile (std::string existing_filename, std::string target_filename);
	bool copyFileW (std::wstring existing_filename, std::wstring target_filename);
	bool moveFileW (std::wstring existing_filename, std::wstring target_filename);
	void getFiles (std::string* &dirFiles, unsigned long &numFiles, std::string pattern);
	void getFilesW (std::wstring* &dirFiles, unsigned long &numFiles, std::wstring pattern);
	std::string runningPath(bool pathOnly = true);
	std::wstring runningPathW();
	};


#endif // FILESYSTEM_H
