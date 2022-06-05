/*	======================================================================

	Title:		[PC] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		May 01 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		manages eff file

	Change Log:

	[2022-05-01]
		wrote it !

	======================================================================	*/
#ifndef FMTEFF_H
#define FMTEFF_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <sstream>
#include <string>
#include <vector>

#include "bytestream.h"
#include "filesystem.h"
#include "fmtEST.h"
#include "fmtTPL.h"

struct fmtEFF_Index { // 8 Bytes
	uint16_t id1; // Memory Index to Write Asset to [0 to 255]
	uint16_t id2; // flag? range [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 30, 31, 65535]
	uint16_t id3; // Always 0
	uint16_t id4; // Always 0
	fmtEFF_Index ();
	void read_index (bytestream &f);
	void write_index (bytestream &s);
	size_t size ();
	};

struct fmtEFF_Index_Table { // 4 + n Bytes
	uint32_t count; // max number of entries seen is 110
	std::vector<fmtEFF_Index> index;
	fmtEFF_Index_Table ();
	void read_index_table (bytestream &f);
	void write_index_table (bytestream &s);
	size_t size ();
	};

struct fmtEFF_Pointer_Table { // 4 + n Bytes
	uint32_t count;
	std::vector<uint32_t> addr;
	fmtEFF_Pointer_Table ();
	void read_pointer_table (bytestream &f);
	void write_pointer_table (bytestream &s, uint32_t override_count = 0);
	size_t size (uint32_t override_count = 0);
	};

struct fmtEFF_TPL_Table { // 4 + n Bytes
	/*
		TPL's with Multiple Texture appear to have the same dimension,
		likely they are texture frames for a animation
	*/
	fmtEFF_Pointer_Table table;
	std::vector<fmtTPL> tpl_gc; // orphaned TPL data from gamecube
	std::vector<fmtTPL> tpl_pc;
	void read_tpl_table (bytestream &f, uint32_t header_pos, fmtEFF_Pointer_Table header_addrs, bool scan = false);
	void write_tpl_table (bytestream &s);
	size_t size ();
	};

struct fmtEFF_Sprite { // 32 Bytes
	uint16_t unk71; // ? Height Range [1 - 1024]
	uint16_t unk72; // ? Width Range [1 - 910]
	uint16_t unk73; // ? Height Range [0, 8, 28, 31, 32, 43, 47, 48, 56, 64, 86, 128, 512]
	uint16_t unk74; // ? Width Range [0 - 910]
	uint16_t unk75; // Texture Count in the TPL
	uint8_t unk76; // ? Range [0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 21]
	uint8_t unk77; // ? Range [0, 1, 2]

	// below is likely padding to pad the entry to 32 bytes
	uint32_t unk78; // Always 0
	uint32_t unk79; // Always 0
	uint32_t unk80; // Always 0
	uint32_t unk81; // Always 0
	uint32_t unk82; // Always 0
	fmtEFF_Sprite ();
	void read_sprite_block (bytestream &f);
	void write_sprite_block (bytestream &s);
	size_t size ();
	};

struct fmtEFF_Sprite_Table { // 4 + {n * 32} Bytes
	fmtEFF_Pointer_Table table;
	std::vector<fmtEFF_Sprite> entry;
	void read_sprite_block_table (bytestream &f);
	void write_sprite_block_table (bytestream &s);




	void export_sprite_table (std::wstring outpath, std::string section, fmtEFF_Index_Table &info, fmtEFF_TPL_Table &library, int padlen = 65, int varlen = 21, int dc_len = 6);
	size_t size ();
	};

struct fmtEST_Table { // n Bytes
	fmtEFF_Pointer_Table table;
	std::vector<fmtEST> entry;
	void read_addr_table (bytestream &f);
	void write_addr_table (bytestream &s);
	size_t size ();
	void export_est_table (fmtEFF_Index_Table &info, std::string section, std::wstring outfile, std::wstring outpath, unsigned int index_offset = 0, int padlen = 65, int varlen = 21, int dc_len = 6);
	};

struct fmtEFF_Spline_Data { // 40 bytes
	float vertex[3];
	uint32_t unk30; // Always 0
	uint32_t unk31; // Always 0
	uint32_t unk32; // Always 0
	float position; // cumulative distance from current point, to the next {adds from previous}
	uint32_t unk33; // Always 0
	uint32_t unk34; // Always 0
	uint32_t unk35; // Always 0
	fmtEFF_Spline_Data ();
	void read_spline_data (bytestream &f);
	void write_spline_data (bytestream &s);
	/** Calculates Size of Block */
	size_t size ();
	};

struct fmtEFF_Spline { // 4 + n Bytes
	uint16_t count; // max num of splines seen, 149
	uint16_t unk30; // Always 0
	std::vector<fmtEFF_Spline_Data> data;
	fmtEFF_Spline ();
	void read_spline (bytestream &f);
	void write_spline (bytestream &s);
	size_t size ();
	bool export_obj (std::wstring fileW, std::string objname = "line001");
	};

struct fmtEFF_Spline_Table {
	fmtEFF_Pointer_Table table;
	std::vector<fmtEFF_Spline> entry;
	void read_spline_table (bytestream &f);
	void write_spline_table (bytestream &s);
	void export_spline_table (std::wstring outpath, std::string section, int padlen = 65, int varlen = 21, int dc_len = 6);
	size_t size ();
	};

struct fmtEFF_Model { // n Bytes
	fmtEFF_Pointer_Table table;
	/*
		Table Always stores 4 entries && can contain all
		null pointers, pointer data seems fixed:
			1: BinMesh
			2: TPL
			3: another table of TPL but in big endian && encrpyted lol

		maybe whats happening is ptr0 is always the mesh
		while ptr1,ptr2,ptr3 are reserved for TPL's that the BIN can use?
	*/
	bytestream model;
	bytestream texture;
	fmtEFF_TPL_Table gc_tpl;
	// 4th asset not seen in the wild

	void read_bin_group (bytestream &f);
	void write_bin_group (bytestream &s);
	size_t size ();
	};

struct fmtEFF_Model_Table { // n Bytes
	/*
		Each Bin is Paired with a TPL,
		so there is a sub Pointer Table to associate each pair
	*/
	fmtEFF_Pointer_Table table;
	std::vector<fmtEFF_Model> entry; // Bin + Tpl packages
	void read_bin_table (bytestream &f, bool scan = false);
	void write_bin_table (bytestream &s);
	};

struct fmtEFF { // Other Names, ESP, EST
	/*

	EFF File on PC contained orphaned gamecube data.

	There may be gamecube data written just after
	the Mesh and Texture Pointer Tables.

	Calculating there end position is a bit tricky, I think
	All known points need to be collected from every

	block in order to derive the exact length of the orphaned
	data...

	A block overview, shows how the data is left, the new
	data pushed to the end of the file

		HEADER

		--- BLOCK01 INDICES

		--- BLOCK02 INDICES

		--- BLOCK03_INDICES

		--- BLOCK04 INDICES

		--- BLOCK05 INDICES

		--- BLOCK06 TABLE
		------- BLOCK06 *ORHAN* DATA
		---------------------------------*
															|
		--- BLOCK07 TABLE						|
		------- BLOCK07 DATA					|
															|
		--- BLOCK08 TABLE						|
		------- BLOCK08 DATA					|
															|
		--- BLOCK09 TABLE						|
		------- BLOCK09 DATA					|
															|
		--- BLOCK10 TABLE						|
		------- BLOCK10 DATA					|
															|
		--- BLOCK11 TABLE						|
		------- BLOCK11 *ORHAN* DATA		|
		------- BLOCK06 DATA < ----------*
		------- BLOCK11 DATA

	*/

	fmtEFF_Pointer_Table blocks;
	// padded to 32 bytes
	/*
		These 5 pointer tables are ALWAYS defined,
		and are padded to 32bytes even if (empty
	*/
	fmtEFF_Index_Table sprite_block_info; // Block1, describes block7
	fmtEFF_Index_Table esp1_block_info; // Block2, count matches block8 'esp1_block'
	fmtEFF_Index_Table esp2_block_info; // Block3, count matches block9 'esp2_block'
	fmtEFF_Index_Table spline_block_info; // Block4, guess-> for spline_block
	fmtEFF_Index_Table model_block_info; // Block5, guess-> for block11
	fmtEFF_TPL_Table tpl_block; // Block 6, Archive of TPL's
	// Gamecube TPL data is orphaned here
	fmtEFF_Sprite_Table sprite_block; // Block 7, table in direct relation to the Archive of TPL, appears to provide an ID to each TPL
	fmtEST_Table esp1_block; // Block 8, guess-> enabled
	fmtEST_Table esp2_block; // Block 9, guess-> disabled, event driven
	fmtEFF_Spline_Table spline_block; // Block 10
	fmtEFF_Model_Table model_block; // Block 11
	// Gamecube Mesh data is orphaned here
	// PC TPL Data is Appended Here
	// PC Mesh Data is Appended Here
	bool validate (bytestream &f);
	void read_eff (bytestream &f, bool read_gc_data = true);
	void write_eff (bytestream &s);
	size_t size ();
	void export_eff (std::wstring outpath, int padlen = 65, int varlen = 21, int dc_len = 6);
	};

#endif // FMTEFF_H
