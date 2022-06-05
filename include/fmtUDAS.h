/*	======================================================================

	Title:		[PC] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		September 27 2020

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		unpacking udas

	Change Log:

	[2020-09-27]
		wrote it !

	======================================================================	*/
#ifndef FMTUDAS_H
#define FMTUDAS_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <algorithm>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "filesystem.h"
#include "fmtDAT.h"


struct fmtUDAS_Entry {
	uint32_t type;		// Types: [0: File Package | 1: Sound File? | 2: Compressed? | 3: ? | 4: Embedded DAS]
	uint32_t size;	// if 0 make end of file
	uint32_t unk003;	// always 0?
	uint32_t addr;
	uint32_t unk005;	// group index?
	uint32_t unk006;	// flag?
	uint32_t unk007;	// parent?
	uint32_t unk008;	// always 0?
	bytestream data;
	fmtUDAS_Entry ();
	~fmtUDAS_Entry ();
	void read_udas_entry (bytestream &f);
	};

struct fmtUDAS {
	/*
		excluding the header (32 bytes)
		each block is padded to 1024
		thats the data files as well as the header section
	*/
	uint32_t count;
	fmtUDAS_Entry* entry;
	uint32_t magic;

	fmtUDAS ();
	~fmtUDAS ();
	bool read_udas (std::wstring filename);
	void unpack_udas (std::wstring fpathW, std::wstring filenameW);
	};


#endif // FMTUDAS_H
