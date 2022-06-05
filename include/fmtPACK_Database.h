/*	======================================================================

	Maxscript:    [PC] Resident Evil 4
	Author:        mariokart64n
	Date:           April 16 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Data Collected on the PACK's and the textures within them

	Change Log:
		2022-04-16
		> Wrote It !

	======================================================================	*/


#ifndef FMTPACK_DATABASE_H
#define FMTPACK_DATABASE_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>


#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "fmtTPL.h"

struct fmtPACK_Archive_Info {
	uint32_t id;
	uint32_t count;
	uint32_t hash1;
	uint32_t hash2;
	std::string res;
	fmtPACK_Archive_Info (uint32_t i = 0, uint32_t c = 0, uint32_t h = 0, uint32_t j = 0, std::string r = "");
	};

struct fmtPACK_Texture_Attr {
	bool is_opacity;
	bool is_normal;
	bool is_font;
	bool is_anim;
	bool is_background;
	bool is_widget;
	bool is_icon;
	fmtPACK_Texture_Attr (bool o = false, bool n = false, bool f = false, bool a = false, bool b = false, bool w = false, bool i = false);
	};

struct fmtPACK_Texture_Info {
	int32_t pack;
	int32_t index;
	std::string name;
	uint32_t hash1; // original texture
	uint32_t hash2; // upscaled texture
	fmtPACK_Texture_Attr attr;
	int32_t setid;
	int32_t animid;
	int32_t frame;
	int32_t normal_map;
	int32_t opacity_map;
	fmtPACK_Texture_Info (int32_t p = -1, int32_t i = -1, std::string x = "", uint32_t h = 0, uint32_t j = 0, fmtPACK_Texture_Attr t = fmtPACK_Texture_Attr(), int32_t g = -1, int32_t s = -1, int32_t f = -1, int32_t n = -1, int32_t o = -1);
	};

struct fmtPACK_Database {
	fmtPACK_Archive_Info* archive;
	fmtPACK_Texture_Info* texture;
	fmtPACK_Database ();
	virtual ~fmtPACK_Database ();
	};



#endif // FMTPACK_DATABASE_H
