/*	======================================================================

	Maxscript:    [PC] Resident Evil 4
	Author:        mariokart64n
	Date:           June 06 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Editing of the BLK files {Block Areas}

	Change Log:
		20222-06-06
			- Revised Script; switched read function over to bytestream

	======================================================================	*/
#ifndef FMTBLK_H
#define FMTBLK_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"
#include "filesystem.h"
#include "fmtATARI.h"


struct fmtBLK_Connect {	// 12 bytes
	/*
		Each Entry's Index represents a dat containing an SMD
		and is considered a 'Block'

		The current block of the entry can have up to 8 other
		blocks connected to it.

		Meaning that the connect blocks {dats} are also
		Loaded at runtime.

		The connections make it possible for continue loading
		of the stage map

		Example:
			{ [B0][B1][B2][B3] }

		Block0 {B0} needs to have a connection to B1;
		so that they player can move to B1 without a
		loading screen.

		Block1 {B1} needs to have a connection to B0 and B2
		in the event the player moves Left or Right

	*/
	uint8_t flag;	// always 1?
	uint8_t unk1;	// always 0?
	uint8_t unk2;	// always 0?
	uint8_t unk3;	// always 0?
	int32_t connect[8]; // index blocks to connect for pre-loading {-1 means no connection}
	fmtBLK_Connect ();
	void read_connect (bytestream &f);
	void write_connect (bytestream &s);
	};

struct fmtBLK_Area {	// 56 Bytes
	fmtATARI area;
	uint8_t unk41;		// flag; Always 3 ?
	uint8_t area_index; // index is used as a lookup id in 'fmtBLK_Link' to connect to the area entry
	uint8_t area_no;		// Same as 'area_index' ? huh
	uint8_t area_priority;	// [0:Low - 7:High; Default: 0]
	fmtBLK_Area ();
	void read_area (bytestream &f);
	void write_area (bytestream &s);
	};

struct fmtBLK_Link {	// 20 Bytes
	uint8_t unk51;	// flag; always 1?
	uint8_t link_block;	// ID of the Block or Sector of the map to use. example r100_xx.dat where xx is the id as hex
	uint8_t unk53;	// always 0?
	uint8_t unk54;	// always 0?

	// load and unload block lists are not observed to be used in the game
	uint8_t load_blocks[8];
	uint8_t unload_blocks[8];
	fmtBLK_Link ();
	void read_area_link (bytestream &f);
	void write_area_link (bytestream &s);
	};

struct fmtBLK { // 24 Bytes + Tables[n]
	/*
		BLK enables loading of larger stage maps in sectors or blocks
	*/

	uint8_t fileid[4];
	uint16_t version;	// always 0x0100?

	uint16_t block_count;	// Range [0 - 31]
	uint16_t load_count;
	uint16_t link_count;

	uint32_t block_addr;
	uint32_t load_addr;
	uint32_t link_addr;

	/*
		For each entry the game will try to load a .dat file based on the following name scheme
		r100_xx.dat xx = the block index as a hex string
	*/
	std::vector<fmtBLK_Connect> block;

	/*
		Entries Between 'fmtBLK_Area' and 'fmtBLK_Link' must be the same
	*/
	std::vector<fmtBLK_Area> load;
	std::vector<fmtBLK_Link> link;

	// file is padded with 0xCD filled to a 32byte alignment
	fmtBLK ();
	size_t size ();
	bool validate (bytestream &f, size_t fsize = 0, bool verbose = true);
	void read_blk (bytestream &f);
	void write_blk (bytestream &s);
	void open (std::wstring file);
	void save (std::wstring file);
	};



#endif // FMTBLK_H
