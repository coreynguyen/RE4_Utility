/*	======================================================================

	Title:		[Gamecube] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		April 15 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Reads and Writes to DAT Archive Structure

	Change Log:

	[2022-04-15]
		wrote it !

	======================================================================	*/

#ifndef FMTDAT_H
#define FMTDAT_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>
#include <algorithm>
#include "bytestream.h"
#include "filesystem.h"
#include "stringext.h"

struct fmtDAT {
	uint32_t count;
	uint32_t* addr;
	std::string* type;
	bytestream* data;
	fmtDAT ();
	~fmtDAT ();
	void close ();
	bool validate (bytestream &f);
	bool read (bytestream &f, size_t fsize = 0);
	bool open (std::wstring filenameW);
	void write (std::string filename, bool isLittleEndian = true, bool hasPadding = true);
	void unpack (std::wstring outdirW, std::wstring prefixW = L"file");
	};

#endif // FMTDAT_H
