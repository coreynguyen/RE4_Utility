/*	======================================================================

	Title:		Wide String Helper Library
	Author:		mariokart64n
	Version:	0.1
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		General wide string helper class

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2019-01-28]
		wrote it!

	======================================================================	*/

#ifndef WSTRINGEXT_H
#define WSTRINGEXT_H

#include <iostream>
#include <string>
#include <vector>

#include <windows.h>
#include <shlwapi.h>
#include <shlobj.h>

std::wstring toUpperW(const std::wstring &s);
std::wstring toLowerW(const std::wstring &s);
std::wstring getexepathW();

/**
 * Splits Path from FullFilePath
 * @param FullFilePath
 * @return (Path) returns: "g:\subdir1\subdir2\"
 */
std::wstring getFilenamePathW (const std::wstring &str);


std::wstring openfilenameW(const wchar_t* filter, HWND owner, unsigned long flags);

/**
 * Splits File Name from FullFilePath
 * @param FullFilePath
 * @return (Filename) returns: "myImage"
 */
std::wstring getFilenameFileW(const std::wstring &str);

/**
 * Splits File Extension from FullFilePath
 * @param FullFilePath
 * @return (Extension) returns: ".jpg"
 */
std::wstring getFilenameTypeW (std::wstring const &path);
std::string ReplaceAllW(std::string str, const std::string& from, const std::string& to);
std::wstring string_to_wstring (std::string s);
std::wstring getSavePathW(std::wstring defaultPath = L"", const wchar_t* szCaption = L"Browse for folder...", unsigned int flags = BIF_USENEWUI, HWND hOwner = NULL);
void getFilesW (std::wstring pattern, std::vector<std::wstring> &v);


#endif // WSTRINGEXT_H
