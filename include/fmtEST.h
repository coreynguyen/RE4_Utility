/*	======================================================================

	Title:		[PC] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		May 01 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		manages est file

	Change Log:

	[2022-05-01]
		wrote it !

	======================================================================	*/
#ifndef FMTEST_H
#define FMTEST_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <sstream>
#include <string>
#include <vector>

#include "bytestream.h"
#include "filesystem.h"
#include "stringext.h"

struct fmtEST_Effect_Flags { // 4 Bytes
	bool flag01;	// 3D
	bool flag02;	// Flip X
	bool flag03;	// Flip Y
	bool flag04;	// Flip Rnd X
	bool flag05;	// Flip Rnd Y
	bool flag06;	// Null Mode
	bool flag07;	// Light On
	bool flag08;	// Colour x4
	bool flag09;	// FP No Display
	bool flag10;	// FP Display, Always FALSE
	bool flag11;	// OT Under Water
	bool flag12;	// OT Water
	bool flag13;	// Sim Lit
	bool flag14;	// Nega, Always FALSE
	bool flag15;	// Mask Use
	bool flag16;	// Alpha Draw
	bool flag17;	// Tex Render
	bool flag18;	// Alpha x4
	bool flag19;	// Low Priority
	bool flag20;	// 2.5D
	bool flag21;	// Alpha Clip
	bool flag22;	// Z Draw
	bool flag23;	// OT First
	bool flag24;	// Alpha Draw2
	bool flag25; // Always FALSE
	bool flag26; // Always FALSE
	bool flag27; // Always FALSE
	bool flag28; // Always FALSE
	bool flag29; // Always FALSE
	bool flag30; // Always FALSE
	bool flag31; // Always FALSE
	bool flag32; // Always FALSE
	fmtEST_Effect_Flags ();
	void get_esp_flags (uint32_t val);
	void read_esp_flags (bytestream &f);
	uint32_t set_esp_flags ();
	void write_esp_flags (bytestream &s);
	};

struct fmtEST_Effect { // 300 bytes
	uint8_t state;	// Always 1
	uint8_t esp_id; // Range [0 - 255]
	uint8_t tex_id; // Range [0 - 255]
	uint8_t unk13; // Always 0
	uint16_t time; // Range [0 - 7000] start time, divide by 10 to get seconds
	uint8_t parent; // Range [0 - 228]
	uint8_t part_id; // Range [0 - 255]
	fmtEST_Effect_Flags flag;
	float position[3];
	float rand[3]; // particle volume
	float speed[3]; // Range [-11108.3 to 12119.0]
	float speed_d; // decay? seems to work like a multiplier, 1 being normal, 2 being twice as fast, Range [0.0 to 1.18]
	float rand_speed[3]; // Range [-400.0 - 1676.31]
	float speed_acceleration[3]; // Range [-523.0 to 170.0]
	float rand_speed_acceleration[3]; // Range [-2.0 to 5.0]
	float rotation[3]; // Range [-300.0 to 347.0]
	float rand_rotation[3]; // Range [-172.623 to 720.0]
	float rotation_acceleration[3]; // Range [-40.0 to 360.0]
	float rand_rotation_acceleration[3]; // Range [-10.0 to 10.0028]
	float width;
	float height;
	float r_size; // Range [0.0 - 55915.3] Random Size
	float plus; // Range [-0.5 to 13.32] i thought it was a normalized value
	float d_plus; //- Range [0.0 to 1.02]
	uint8_t rgba[4];
	float d_rgba[4];
	uint16_t color_end_frame;
	uint16_t color_start_frame;
	uint16_t unk14; // Always 0
	uint16_t size_start_frame;
	uint16_t life_time; // end time, divide by 10 to get seconds
	uint8_t unk15; // Always 0
	uint8_t unk16; // Always 0
	uint8_t unk17; // Always 0
	uint8_t animation_rate; // Range [0 - 255]
	uint8_t unk18; // Always 0
	uint8_t unk19; // Always 0
	uint8_t release_trigger; // Range [0 - 255]
	uint8_t unk20; // Always 0
	uint8_t blend_mode; // Range [0; 1, 2, 3, 4]
	uint8_t sim_type;	// range:[0:NONE , 1:NORMAL, 2:OFFSET, 3:REPLACE]
	uint8_t sim_power; // Range [0 - 255]
	uint8_t tex_mask; // Range [0 - 255]
	uint8_t color_in; // Range [0 - 200]
	uint8_t color_out; // Range [0 - 70]
	uint8_t work0; // Range [0 - 255]
	uint8_t work1; // Range [0 - 255]
	uint8_t work2; // Range [0 - 255]
	uint8_t work3; // Range [0 - 254]
	uint32_t work4; // Range [-140 to 500]
	uint32_t work5; // Range [-300 to 300]
	uint32_t work6; // Range [-20 to 80]
	float vec0[3];
	float vec1[3]; // Range [-9431.94 to 19000.0]
	float vec2[3]; // Range [-460.0 to 460.0]
	uint8_t sp0; // Range [0 - 176]
	uint8_t sp1; // Range [0 - 176]
	uint8_t sp2; // Range [0 - 255]
	uint8_t sp3; // Range [0; 1]
	uint32_t unk21; // Always 0
	uint8_t path_own; // Always 0
	uint8_t path_no; // spline shape; 0:Spiral 1:Circle 2:Line 3:line2 4:S Curve 5:J 6:1/4 Circle 7:1/4 Circle2 8:1/2 Circle 9:1/2 Circle2 10:Torus Knot
	uint8_t path_st; // normalize 0 -255, value is the distance along the spline the particle spawns
	uint8_t path_rnd; // random range to position path_st, set to 255 to have the particle spawn all along the spline
	uint8_t kind; // 0:Esp 1:Ctrl
	uint8_t ctr_id; // only active when kind == 1, Range [0; 1, 2, 66, 67, 68, 69, 76, 255]
	uint8_t unk22; // Always 0
	uint8_t id_flag; // Range [0; 1, 2, 3, 4]
	uint8_t inter; // spawn interval, divide by 10 to get seconds, Range [0 - 255]
	uint8_t num; // Range [0 - 255]
	uint8_t rp; // Range [0 - 251]
	uint8_t unk23; // Always 0
	uint16_t life; // id section

	// endian check
	uint16_t unk24; // Range [0; 12, 20; 30; 252, 253, 254, 255, 12420]
	uint16_t unk25; // Range [0; 16, 252, 253, 254, 255]
	uint16_t unk26; // Range [0; 16, 252, 253, 254, 255]
	float path_scale[3]; // Range [-60.0 to 4100.0]

	// only active when life != 0
	uint8_t d_size; // Range [0 - 255]
	uint8_t d_speed; // Range [0 - 255]
	uint8_t d_alpha; // Range [0 - 255]
	uint8_t d_inter; // Range [0 - 255]
	uint8_t r_inter; // r interval? repeat, random? seems to add delay to interval, Range [0; 1, 2, 3, 4, 5, 6, 8, 10; 12, 20; 30]
	uint8_t path_rotation_x; // Range [0 - 255]
	uint8_t path_rotation_y; // Range [0 - 255]
	uint8_t path_flag; // Range [0; 1, 2]
	void clear ();
	fmtEST_Effect ();
	void read_esp_data (bytestream &f);
	void write_esp_data (bytestream &s);
	void repr ();
	size_t size ();
	bool export_txt (std::wstring savefile, bool hide_unset = true);
	bool import_txt (std::wstring openfileW);
	};

struct fmtEST { // 48 + n Bytes
	/*
		The EST is a compositor of animated sprites
		There are 4 Groups, each allowing a maxim of
		64 sprites layers
	*/
	uint16_t table0_count; // range [1 to 64] Sprites in EST
	uint16_t table1_count;
	uint16_t table2_count;
	uint16_t table3_count;
	uint8_t unk05; // Always 0
	uint8_t unk06; // Always 0 // NullFlg
	uint8_t unk07; // Range [2, 254] NullPtr [0xFC: SA, 0xFD: SC, 0xFE: WD, 0xFF: NL] {Parent}
	uint8_t unk08; // Always 0
	float position[3];
	float rotation[3]; // {Only rotZ is used}
	uint8_t unk40; // Always 0
	uint8_t unk41; // Always 16
	uint8_t unk42; // Always 0
	uint8_t unk43; // Always 0
	uint32_t unk44; // Always 0
	uint32_t unk45; // Always 0
	std::vector<fmtEST_Effect> table0;
	std::vector<fmtEST_Effect> table1;
	std::vector<fmtEST_Effect> table2;
	std::vector<fmtEST_Effect> table3;
	fmtEST ();
	size_t size ();
	void read_est_entry (bytestream &f);
	void write_est_entry (bytestream &s);
	void repr ();
	void export_est (std::wstring outpath, int padlen = 65, int varlen = 21, int dc_len = 6);

	};

#endif // FMTEST_H
