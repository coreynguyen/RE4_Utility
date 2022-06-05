#ifndef REGISTRY_H
#define REGISTRY_H

#include <iostream>
#include <string>
#include <windows.h>
#include <shlwapi.h>
#include <tchar.h>

namespace reg {
	// https://github.com/sd-eblana/bawx/blob/master/trunk/xbmc/win32/Registry.cpp

	/** TESTGOESHERE */
	int create_key_path(HKEY hKey, const char *sPath);


	/**
	* Creates a key specified by pszSubKey - you can't create
	* keys directly under HKEY_LOCAL_MACHINE in Windows NT or 2000
	* just for an extra bit of info.
	*/
	bool create_key(HKEY hKeyRoot, const char* pszSubKey);

	/** TESTGOESHERE */
	bool remove_key(HKEY hKeyRoot, const char* pszSubKey);

	/** Deletes a value from a given subkey and root */
	bool remove(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue);

	/**
	* Fetch a binary value. If the size specified by rdwSize
	* is too small, rdwSize will be set to the correct size.
	*/
	bool read_binary(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, PVOID pBuffer, DWORD& rdwSize);

	/** Fetch a little endian DWORD from the registry */
	bool read_integer(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, unsigned __int64 &u64Buff);

	/** Fetch a little endian DWORD from the registry */
	bool read_integer(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, unsigned long &ulBuff);

	/** Reads a string to the registry. */
	bool read_string(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, std::string &strOutValue);

	/** Writes a binary value to the registry */
	bool write_binary(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, PVOID pData, DWORD dwSize);

	/** Writes a DWORD value to the registry */
	bool write_integer(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, unsigned long ulValue);

	/** Writes a DWORD_PTR value to the registry */
	bool write_integer(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, unsigned __int64 u64Value);

	/** Writes a string to the registry. */
	bool write_string(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, const char* pszString);

	/** Writes a bool to the registry. */
	bool write_bool(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue, bool bVal);

	/** Reads a bool to the registry. */
	bool read_bool(HKEY hKeyRoot, const char* pszSubKey, const char* pszValue);


	};


















#endif // REGISTRY_H
