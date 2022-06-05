/*	======================================================================

	Maxscript:    [PC] Resident Evil 4
	Author:        mariokart64n
	Date:           March 31 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Modify TPL {Texture Pack Library} data

	ToDo:
		> Make this work with a normal gamecube TPL

	Change Log:
		2022-03-31
		> cleaned up the code recoded stuff
		> replaced reading and writing functions with bytestream class

	======================================================================	*/
#ifndef FMTTPL_H
#define FMTTPL_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>

#include <math.h>


#include "appsettings.h"
#include "scriptini.h"

#include "bytestream.h"
#include "stringext.h"
#include "wstringext.h"
#include "filesystem.h"
#include "vectorext.h"
#include "fmtPACK.h"


struct fmtTPL_Pack {
	uint32_t fileid;
	uint32_t texid;
	std::string filename;
	fmtTPL_Pack ();
	std::string generate_filename ();
	void read_pack (bytestream &f);
	void write_pack (bytestream &s);
	};

struct fmtTPL_Palette { // 12 + n Bytes
	/*
		Colour Look Up Table {CLUT} or Colour Palette
	*/
	uint16_t count;
	uint8_t is_compressed;
	uint8_t pad;
	uint32_t type;
	uint32_t addr;
	std::vector<unsigned short> data;
	fmtTPL_Palette ();
	std::string enum_pal_type (unsigned int v);
	void read_palette (bytestream &f);
	void write_palette (bytestream &s);
	size_t size ();
	};

struct fmtTPL_Image { // 36 + n Bytes
	/*
		Image Data or Indices to CLUT
	*/
	uint16_t width;
	uint16_t height;
	uint32_t type;
	uint32_t addr;
	uint32_t wrap_s;
	uint32_t wrap_t;
	uint32_t min_filter;
	uint32_t mag_filter;
	float lod_bias;
	uint8_t enable_lod;
	uint8_t min_lod;
	uint8_t max_lod;
	uint8_t is_compressed;
	std::vector<unsigned int> data;
	// stuff for calculating size
	char bbp[15];
	/*
	ID		Name						Bits per pixel	Block width	Block	height	Block size	Type
	0x00	I4							4					8				8					32 bytes		Gray
	0x01	I8							8					8				4					32 bytes		Gray
	0x02	IA4						8					8				4					32 bytes		Gray + Alpha
	0x03	IA8						16					4				4					32 bytes		Gray + Alpha
	0x04	RGB565					16					4				4					32 bytes		Color
	0x05	RGB5A3					16					4				4					32 bytes		Color + Alpha
	0x06	RGBA32 {RGBA8}	32					4				4					64 bytes		Color + Alpha
	0x07
	0x08	C4 {CI4}					4					8				8					32 bytes		Palette {IA8 RGB565 RGB5A3}
	0x09	C8 {CI8}					8					8				4					32 bytes		Palette {IA8 RGB565 RGB5A3}
	0x0A	C14X2 {CI14x2}		16					4				4					32 bytes		Palette {IA8 RGB565 RGB5A3}
	0x0E	CMPR					4					8				8					32 bytes		Color + 1 bit Alpha {compressed}
	*/
	fmtTPL_Image ();
	size_t size ();
	void read_image (bytestream &f);
	void write_image (bytestream &s);
	};

struct fmtTPL_Entry { // 8 Bytes
	uint32_t image_addr;
	uint32_t palette_addr;
	fmtTPL_Entry ();
	void read_table (bytestream &f);
	void write_table (bytestream &s);
	};

struct fmtTPL {
	/*
		Texture Pallete Library
	*/
	uint32_t fileid; // magic is 0x002724C0 if (tpl is modified
	uint32_t image_count; // Image Count
	uint32_t table_addr; // Address To Image Data
	std::vector<fmtTPL_Entry> table; // need to subtract 12548356 from all address wtf
	std::vector<fmtTPL_Image> image;
	std::vector<fmtTPL_Palette> palette;
	/*
		Texture Pack Data (not a part of the typical TPL format)
	*/
	uint32_t addr_offset; // used to obfuscate the other addresses
	std::vector<fmtTPL_Pack> pack;
	fmtTPL ();
	unsigned int removeFillerNumber (unsigned int num, unsigned int fill, unsigned int bytes);
	size_t recalc_pointers ();
	bool read (bytestream &f);
	void write (bytestream &s);
	size_t size ();
	void fetch_images (std::wstring pack_path, std::wstring outpath);
	};


#endif // FMTTPL_H
