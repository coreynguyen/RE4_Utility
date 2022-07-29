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
#include <vector>
#include <algorithm>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "filesystem.h"
#include "fmtDAT.h"


struct fmtUDAS_Entry {
	int32_t type;		// Types
	/*
		0: File Package
		1: Sound File?
		2: Compressed?
		3: ???
		4: SND (Embedded DAS)
	*/
	uint32_t size;	// if 0 the file is null
	uint32_t unk003;	// always 0?
	uint32_t addr; 		// ignore address if size is 0
	uint32_t unk005;	// sub type? type 1 = 6, type 2 = 5
	int32_t unk006;	// room_id, same as the udas its contained in (if sub type is 0, this is -1)
	uint32_t unk007;	// parent?
	uint32_t unk008;	// always 0?
	bytestream data;
	fmtUDAS_Entry ();
	~fmtUDAS_Entry ();
	void read_udas_entry (bytestream &f);
	std::string type_to_ext ();
	void repr ();
	};

struct fmtUDAS {
	/*
		excluding the header (32 bytes)
		each block is padded to 1024
		thats the data files as well as the header section
	*/
	uint32_t count;
	std::vector<fmtUDAS_Entry> asset;
	uint32_t magic;

	fmtUDAS ();
	~fmtUDAS ();

	bool validate_udas (bytestream &f);
	bool read_udas (bytestream &f);
	bool open_udas (std::wstring filename);
	void unpack_udas (std::wstring fpathW, std::wstring filenameW);
	};


#endif // FMTUDAS_H
