/*	======================================================================

	Title:		[PC] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		September 27 2020

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Editing of the ITA files (Item Spawns)

	Change Log:

	[2022-05-05]
		REfreshed code and moved native read functions to bytestream class

	[2020-07-27]
		wrote it !

	======================================================================	*/
#ifndef FMTITA_H
#define FMTITA_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>

#include "rapidxml_ext.h"

#include "bytestream.h"
#include "stringext.h"
#include "fmtATARI.h"

struct fmtITA_Entry_Flags {	// always 3
	bool hasData;
	bool useData;
	bool flg3;
	bool flg4;
	bool flg5;
	bool flg6;
	bool flg7;
	bool flg8;
	fmtITA_Entry_Flags ();
	void set_entry_flag (uint8_t val);
	uint8_t get_entry_flag ();
	void read_entry_flag (bytestream &f);
	void write_entry_flag (bytestream &s);
	};

struct fmtITA_Hit_Flags {
	bool position_auto_off;
	bool hit_area_auto_off;
	bool see_check_off;
	bool flg4;
	bool drop_type_shoot_and_fall;
	bool flg6;
	bool drop_type_fall;
	bool hide_set_on;
	fmtITA_Hit_Flags ();
	void set_hit_flag (uint8_t val);
	uint8_t get_hit_flag ();
	void read_hit_flag (bytestream &f);
	void write_hit_flag (bytestream &s);
	};

struct fmtITA_Entry {	// 156 Bytes {for 2007 port 176 bytes}
	fmtATARI area;	// reads 52 Bytes
	fmtITA_Entry_Flags entry_flag;	// always 3
	uint8_t unk010;	// always 3, another flag, nulling makes area item detection disappear
	uint8_t entry_index;	// flag, changing it has no effects, Range [0 to 127]
	uint8_t hit_type;	// Range [0: UNDER, 1: FRONT, 2: UNDER+ANGLE, 3: FRONT+ANGLE]
	uint8_t unk013;	// Range [1, 2, 8, 130]
	uint8_t unk014;	// Always 1
	uint8_t unk015;	// Always 0
	uint8_t unk016;	// Always 0
	uint32_t unk017;	// Always 0
	uint32_t unk018;	// Always 0
	uint8_t priority;	// Range [0:Low - 15:High, Default:8], seen [0, 2, 8]
	uint8_t unk026;	// Always 0
	uint8_t set_wait_type;	// Range [0: NORMAL, 1: EM_DEAD, 2: ETC_BREAK]
	uint8_t set_target_no;	// Range [0 - 255]
	int8_t hit_angle;
	int8_t open_angle; // Always 0x2D
	uint8_t unk031;	// Range [0, 1, 40]
	uint8_t unk032;	// Always 0
	uint8_t unk033;	// Always 0
	uint8_t unk034;	// Always 0
	uint8_t unk035;	// Always 0
	uint8_t unk036;	// Always 0
	uint8_t unk037;	// Always 0
	uint8_t unk038;	// Always 0
	uint8_t country;	// Range [0: JPN / USA, 1: JPN, 2: USA]
	uint8_t unk039;	// Always 0
	uint8_t unk040;	// Always 0
	uint8_t unk041;	// Always 0
	uint8_t unk042;	// Always 0
	uint8_t unk043;	// Always 0
	uint8_t unk044;	// Always 0
	uint8_t unk045;	// Always 0
	uint8_t unk046;	// Always 0
	uint8_t unk047;	// Always 0
	// on 2007 they read another 4 bytes to pad to 32?, Always 0
	float set_pos_x; // Range [-353156.0 to 187233.0]
	float set_pos_y;
	float set_pos_z;
	// on 2007 they store set_pos_w, Always 1.0
	uint8_t unk051;	// Always 0
	uint8_t unk052;	// Always 0
	uint8_t unk053;	// Always 0
	uint8_t unk054;	// Always 0
	float eff_offset_pos_x; // Range [0.0 to 250.0]
	float eff_offset_pos_y;
	// on 2007 they eff_offset_pos_w, Always 1.0
	float eff_offset_pos_z;
	uint16_t item_id;	// Range [0 to 4101]
	uint16_t item_flag;	// Range [0 - 255, default: 0], seen 0 thru 155
	uint16_t item_num;	// Range [0 - 60000, default: 0] {Amount} seen 0 thru 200
	uint8_t unk058;	// ?? Index to something Range [0 to 55]
	uint8_t unk059;	// Always 0
	uint8_t eff_type;	// Range [0 - 9]
	/*
		0x00	None
		0x01	KIRA EFF
		0x02	EM DROP{W}
		0x03	EM DROP{B}
		0x04	EM DROP{G}
		0x05	EM DROP{R}
		0x06	AUTO
		0x07	EM DROP{BIG}
		0x08	EM DROP{KEY}
		0x09	SANDGLASS
	*/
	uint8_t unk061;	// Always 0
	uint8_t unk062;	// Always 0
	uint8_t hit_area_disp;	// Range [0, 1] should be 1, changing it hides the collision sphere on the screen
	fmtITA_Hit_Flags hit_flags;
	/*
		0x01	1	POSITION_AUTO_OFF
		0x02	2	HIT_AREA_AUTO_OFF
		0x04	4	SEE_CHECK_OFF
		0x08	8
		0x10	16	DROP_TYPE_SHOOT_AND_FALL
		0x20	32
		0x40	64	DROP_TYPE_FALL
		0x80	128	HIDE_SET_ON
	*/
	uint8_t unk065;// Always 0
	uint8_t unk066; // Always 0
	uint8_t unk067; // Always 0
	float radius; // Range [0 to 2600]
	float cone_ang_x; // Range [-3.14087 to 3.13999]
	float cone_ang_y;
	float cone_open_angle; // Range [0.0 to 6.28]
	uint8_t se_no_drop; // Range [0, 4, 5, 10, 11, 14, 25, 90, 91]
	uint8_t se_no_hit; // Range [0, 2, 4, 10, 11, 13, 24, 89, 90]
	uint8_t unk074;// Always 0
	uint8_t unk075;// Always 0
	// on 2007 they read another 8 bytes to pad?, Always 0
	fmtITA_Entry ();
	bool is_re4_2007 (bytestream &f);
	void read_entry (bytestream &f, bool re4_2007 = false);
	void write_entry (bytestream &s, bool re4_2007 = false);
	size_t size (bool re4_2007 = false);
	};

struct fmtITA { // 16 + n Bytes
	uint8_t fileid[4]; // 'ITA '
	uint16_t unk001; // Always 0x0105
	uint16_t count;		// Range [0 - 127] Max entries is 127
	uint32_t unk003;	// Always 0
	uint32_t unk004;	// Always 0
	std::vector<fmtITA_Entry> data;
	fmtITA ();
	void read_ita (bytestream &f);
	void write_ita (bytestream &s, bool re4_2007 = false);
	size_t size (bool re4_2007 = false);
	void xml_export (std::wstring file, bool hideNulls = true);
	void xml_import (rapidxml::xml_document<> &doc);
	};


#endif // FMTITA_H
