#ifndef WREGISTRY_H
#define WREGISTRY_H

#include <iostream>
#include <string>
#include <windows.h>
#include <shlwapi.h>
#include <tchar.h>

namespace wreg {

	/** Reads a string to the registry. */
	bool read_string(HKEY hKeyRoot, const wchar_t* pszSubKey, const wchar_t* pszValue, std::wstring &strOutValue);

	};

#endif // WREGISTRY_H
