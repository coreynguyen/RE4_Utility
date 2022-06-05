/*	======================================================================

	Title:		[PC] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		September 29 2020

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Editing of the Pack files (Texture Pack)

	Change Log:
		2020-09-29
		- Wrote It!
	======================================================================	*/

#ifndef FMTPACK_H
#define FMTPACK_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"
#include "filesystem.h"

#include "fmtPACK_Database.h"
#include "fmtTPL.h"



struct fmtPACK_Entry {
	uint32_t size;	// size in bytes after the header
	uint32_t unk001; // Always -1  maybe this was a pointer to the filename?
	uint32_t packid; // same as the packid defined in the PACK header
	uint32_t type; // 0:TGA 1:DDS
	/*
		only DXT1 DDS files are observed
		simular with the TGA we only see 32bit RGBA
		however the alpha component is in a separate tga file... very weird
	*/
	bytestream data; // data padded to 128byte alignment {however start from -16}
	fmtPACK_Entry ();
	void read_entry (bytestream &f, bool storeData = false);
	void write_entry (bytestream &s);
	};

struct fmtPACK {
	uint32_t packid; // should be same as the filename
	uint32_t count;
	std::vector<uint32_t> addrs;
	/*
		address are blocked aligned to 128bytes
		however this is count from -16 from the header
	*/
	std::vector<fmtPACK_Entry> info;
	fmtPACK ();
	std::string getFileExtensionFromFourCC (unsigned int num);
	std::string guess_extension (unsigned int &id);
	std::string getFilename (unsigned int num);

	size_t size ();
	size_t recalc_addr ();
	bool read (bytestream &f, bool storeData = false);
	void write (bytestream &s);
	bool open (std::wstring fileW, bool storeData = false);
	void save (std::wstring fileW);
	void dump_pack_image (unsigned int index, std::wstring outnameW);
	void dump_pack (std::wstring out_dirW, std::wstring prefixW = L"");
	void repack (uint32_t pack_num, std::wstring imgpath, std::wstring outfile);
	void export_txt (std::wstring outpath, std::wstring prefix = L"pack", std::wstring subfolder = L"images");
	void import_txt (std::wstring file);
	};


#endif // FMTPACK_H
