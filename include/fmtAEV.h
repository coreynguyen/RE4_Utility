/*	======================================================================

	Maxscript:    [PC] Resident Evil 4
	Author:        mariokart64n
	Date:           January 30 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Editing of the AEV files {Atari Events}

	Change Log:
		2022-05-09
			- Switched over read functions to bytestream; so that I can read big endian
			- Reviewed each structure; in preparation for porting to c++

		2022-01-30
			- Wrote IT!
	======================================================================	*/

#ifndef FMTAEV_H
#define FMTAEV_H

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




struct fmtAEV_Normal {	// 0x00 Normal
	uint32_t unk820;
	uint32_t unk821;
	fmtAEV_Normal ();
	void read_type00 (bytestream &f);
	void write_type00 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Door {	// 0x01 Door Way; jumps rooms
	float next_pos_x; // observed ranges [-689322.0 to 247465.0]
	float next_pos_y;
	float next_pos_z;
	float next_ang_y;	// Angle in Radians; range [-3.14 to 3.14]
	uint8_t next_stage_no;
	uint8_t next_room_no;
	uint8_t key_id;	// range [0: DEFAULT; 1: IN_LOCK_CLOSE; 2: IN_LOCK_OPEN]
	uint8_t key_flg;	// range [0 - 63]; seen 0; 7; 10; 17; 20
	uint8_t unk116; // always 0
	uint8_t unk117; // always 0
	uint8_t unk118; // always 0
	uint8_t unk119; // always 0
	uint8_t next_part_no; // seen 0; 1; 2
	uint8_t key_se;	// range [0 - 10] seen 0; 1; 2; 6
	uint8_t open_se;	// range [0 - 255]; only seen 0 or 1
	uint8_t fade_eff;	// range [0: NORMAL; 1: FADE; 2: BLACK]
	fmtAEV_Door ();
	void read_type01 (bytestream &f);
	void write_type01 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Cut_Scene {	// 0x02 Cut Scene
	/*
		This Type is present in the games files; but the
		data is in the wrong endian and often appears
		to be filled with garbage
	*/
	uint32_t unk823;
	uint32_t unk824[3];
	uint32_t unk825;
	fmtAEV_Cut_Scene ();
	void read_type02 (bytestream &f);
	void write_type02 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Flag {	// 0x04 Grouped Enemy Trigger
	uint8_t flg_id;	// range [0: ROOM_FLG; 1: ROOM_SAVE_FLG; 2: SCENARIO_FLG]; only seen 0 used
	uint8_t flg_act;	// range [0: ON; 1: OFF]
	uint16_t flg_no; // seen [0 to 101] used
	fmtAEV_Flag ();
	void read_type04 (bytestream &f);
	void write_type04 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Message {	// 0x05 Message
	uint16_t mes_type;	// range [0: ROOM_MES; 1: COMMON_MES]
	int16_t mes_no; // seen [-1 to 178]
	uint8_t cam_no;	// range [0 - 255; 0 = no_cam]; seen [0 to 60]
	uint8_t se_type;	// range [0: SE_ROOM; 1: SE_PL]; only seen 0
	int16_t se_no;	// range [0 - 255]; only seen [0 to 13]
	fmtAEV_Message ();
	void read_type05 (bytestream &f);
	void write_type05 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Jump {	// 0x07 Jump
	float jump_pos_x;
	float jump_pos_y;
	float jump_pos_z;
	fmtAEV_Jump ();
	void read_type07 (bytestream &f);
	void write_type07 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Save {	// 0x08 Type Writer
	uint32_t term_no; // range [0 - 10]; seen 0; 1
	fmtAEV_Save ();
	void read_type08 (bytestream &f);
	void write_type08 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Shadow_Display {	// 0x09 SHD_DISP {not seen in samples}
	int16_t shd_no;	// range [0 - 255]
	uint8_t disp_flg;	// range [0: OFF; 1: ON]
	uint8_t unk880;
	fmtAEV_Shadow_Display ();
	void read_type09 (bytestream &f);
	void write_type09 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Damage { // 0x0A Damage Causing Events {When walking through or bumping into}
	uint32_t damage_timer;	// range [0 - 1800]; seconds? only seen 0 in samples
	uint8_t damage_type;	// range [0 - 30]; only seen 0; 1
	uint8_t damage_flag;	// range [0 - 3]; seen 0; 2
	/*
		0x01	1	DIE
		0x02	2	ANG_SET
	*/
	uint16_t unk416; // always 0
	uint32_t damage_volume;	// range [0 - 1000]; seen 0; 50
	float damage_angle;	// Radians; range [-3.14 to 3.14]
	fmtAEV_Damage ();
	void read_type0A (bytestream &f);
	void write_type0A (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Scenario { // 0x0B Map Blocking Events {Crank Dependent Pathways; etc...}
	uint32_t unk420; // garbage? seen [0; 1; 68; 69; 65536]
	uint32_t unk421; // always 0; garbage?
	uint32_t unk422; // always 0; garbage?
	uint32_t scr_at_flg4; // senn [0; 4; 2048; 16384; 1048576; 1064960; 4194304; 8388608]
	/*
		21098765432109876543210987654321
		33322222222221111111111000000000
		____________________________________________________
		00000000000000000000000000000100 NO_EFF_SET ::ON	0x00000004
		////////////////////////////////////////////////////////-
		00000000000000000000000000010000 S:2m_DOWN ::ON		0x00000010
		00000000000000000000000000100000 S:FRANCE ::ON		0x00000020
		////////////////////////////////////////////////////////-
		00000000000000000000100000000000 S:CLIFF ::ON			0x00000800
		00000000000000000001000000000000 S:2m_UP ::ON			0x00001000
		00000000000000000010000000000000 S:1m_DOWN ::ON		0x00002000
		00000000000000000100000000000000 S:EM_NOHIT ::ON	0x00004000
		////////////////////////////////////////////////////////-
		00000000000100000000000000000000 S:FALL ::ON			0x00100000
		00000000001000000000000000000000 S:1m_UP ::ON			0x00200000
		00000000010000000000000000000000 S:PL_NO_HIT ::ON	0x00400000
		00000000100000000000000000000000 S:SEE_NOHIT ::ON	0x00800000
	*/
	uint32_t scr_at_flg5; // seen [0; 64; 4194304; 4210688; 4210752; 8388736]
	/*
		21098765 43210987 65432109 87654321
		33322222 22222111 11111110 00000000
		_____________________________________________________________________________________________
		00000000 00000000 00000000 01000000 NO_EFF_SET_2 ::ON				0x00000040
		00000000 00000000 01000000 00000000 E: EAT_MIDDLE_NOHIT ::ON	0x00004000
		00000000 01000000 00000000 00000000 E: EAT_SMALL_NOHIT ::ON	0x00400000
		////////////////////////////////////////////////////////-
		00000000 00000000 00000000 00000000 E: EAT_EFF_BIT [0] ::ON		0x00000000
		00000000 00000000 10000000 00000000 E: EAT_EFF_BIT [1] ::ON		0x00008000
		00000000 00001000 00000000 00000000 E: EAT_EFF_BIT [2] ::ON		0x00080000
		00000000 10000000 10000000 00000000 E: EAT_EFF_BIT [3] ::ON		0x00808000
		10000000 00000000 00000000 00000000 E: EAT_EFF_BIT [4] ::ON		0x80000000
		10000000 00000000 10000000 00000000 E: EAT_EFF_BIT [5] ::ON		0x80008000
		10000000 10000000 00000000 00000000 E: EAT_EFF_BIT [6] ::ON		0x80800000
		10000000 10000000 10000000 00000000 E: EAT_EFF_BIT [7] ::ON		0x80808000

		the EFF BIT Works Weird:
			0x00000000 EAT_EFF_BIT [0]
			0x00008000 EAT_EFF_BIT [1]
			0x00800000 EAT_EFF_BIT [2]
			0x00808000 EAT_EFF_BIT [3]
			0x80000000 EAT_EFF_BIT [4]
			0x80008000 EAT_EFF_BIT [5]
			0x80800000 EAT_EFF_BIT [6]
			0x80808000 EAT_EFF_BIT [7]
		*/
	uint32_t scr_at_flg6; // seen [0; 1; 2; 4; 5]
	/*
		21098765432109876543210987654321
		33322222222221111111111000000000
		____________________________________________________
		00000000000000000000000000000001 EAT_NO_SET ::ON		0x00000001
		00000000000000000000000000000010 SAT_NO_SET ::ON		0x00000002
		00000000000000000000000000000100 S:ROUTE_NOHIT ::OFF	0x00000004
	*/
	uint32_t scr_at_flg7; // seen [0; 256; 512]
	/*
		21098765432109876543210987654321
		33322222222221111111111000000000
		____________________________________________________
		00000000000000000000000100000000 F_BOX ::ON		0x00000100
		00000000000000000000001000000000 F_FLOOR ::ON	0x00000200
	*/
	fmtAEV_Scenario ();
	void read_type0B (bytestream &f);
	void write_type0B (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_View_Control { // 0x0C View Control
	float pos[3]; // always 0; is also enabled by enable_pos state
	float ang_y; // Radians; range [-3.14 to 3.14]
	uint8_t pos_on; // always 0; but would be 1 if pos is set
	uint8_t type;	// range [0; 1]
	uint8_t unk887; // always 0
	uint8_t unk888; // always 0
	float radius; // always 0; range [0 to 5000]
	float out_range; // always 0; range [0 to 5000] relative to radius; the two values form a tube area
	fmtAEV_View_Control ();
	void read_type0C (bytestream &f);
	void write_type0C (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Field_Info { // 0x0D Unknown {not listed in tool}
	uint32_t field_id;	// range [0 - 3]; only seen 0; 3
	fmtAEV_Field_Info ();
	void read_type0D (bytestream &f);
	void write_type0D (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Ladder { // 0x10 Fixed Ladder Climb Up ? Ada's Grapple Gun
	//METERS_TO_MILLIMETERS = 1000.0;
	float ladder_pos[3];
	float ladder_ang;	// Radians; range [-3.14 to 3.14]
	int8_t ladder_height;	// Meters {multiple by 1000 to get mm}; range [-128 to 127]
	uint8_t unk663; // always 0
	uint8_t ladder_pos_on; // range 0;
	uint8_t cam_no1;	// range [0 - 255]
	uint8_t cam_no2;	// range [0 - 255]
	uint8_t cam_no3;	// range [0 - 255]
	fmtAEV_Ladder ();
	void read_type10 (bytestream &f, bool re4_2007 = false);
	void write_type10 (bytestream &s, bool re4_2007 = false);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Use { // 0x11 Item Dependent Events {Locked Doors; Puzzles; ...}
	uint32_t use_id;	// range [0 - 255]
	fmtAEV_Use ();
	void read_type11 (bytestream &f);
	void write_type11 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Hide { // 0x12 Ashley's "HIDE" Command
	uint8_t hide_type;	// range [0 - 3]; always seen as 1
	uint8_t hide_pos_on;	// range [0: OFF; 1: ON]; always seen as 1
	uint8_t hide_area_on;	// range [0: OFF; 1: ON; always seen as 1
	uint8_t unk772; // always 0

	// interaction area
	float hide_area[8];

	// character way point?
	float hide_pos[3];
	uint32_t unk774;
	uint32_t cam_no; // 0 = off; do i need to restore the 0 base to use as an index?
	fmtAEV_Hide ();
	void read_type12 (bytestream &f, bool re4_2007 = false);
	void write_type12 (bytestream &s, bool re4_2007 = false);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Jump_Position {	// 0x13 Pos Jump
	float jump_pos[3];
	float jump_ang;	// Radians; range [-3.14 to 3.14]
	fmtAEV_Jump_Position ();
	void read_type13 (bytestream &f);
	void write_type13 (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Grapple { // 0x15 Ada's Grapple Gun
	/*
		I need to test this in game; var. names are taken from son of persia's tool;
		but the inspected values don't seem correct..
	*/
	float ShotPoint[3];
	float DestinationPoint[3];
	float CameraParameter[3]; //angle -3.14 to 3.14
	float CameraAngle;
	uint8_t unk810;
	uint8_t unk811;
	uint8_t unk812;
	uint8_t unk813;
	fmtAEV_Grapple ();
	void read_type15 (bytestream &f, bool re4_2007 = false);
	void write_type15 (bytestream &s, bool re4_2007 = false);
	void write_ini ();
	void read_ini (std::string &secname);
	};

struct fmtAEV_Region { // 156 bytes {52 + 40 + 64}
	fmtATARI area; // 52 bytes
	uint8_t unk016 ;	// Always 3; ?
	/*
		0	HAS ZONE
		1	HAS DATA
	*/
	uint8_t type;	// ranges [0; 1; 2; 4; 5; 8; 10; 11; 13; 14; 16; 17; 18; 20; 21]
	/*
		0x00	0	NORMAL
		0x01	1	DOOR
		0x02	2	EXEC
		//-
		0x04	4	FLG
		0x05	5	MESSAGE
		0x06	6	PLANTER
		0x07	7	JUMP
		0x08	8	SAVE
		//-
		0x09	09	SHD_DISP
		0x0A	10	DAMAGE
		0x0B	11	SCR_AT
		0x0C 12	VIEW_CTRL
		0x0D	13	FIELD_INFO
		0x0E	14	STOOP
		0x0F	15	SMALL_KEY
		0x10	16	LADDER
		0x11	17	USE
		0x12	18	HIDE
		0x13	19	POS_JUMP
		0x14	20	ITEM_PARENT
		0x15	21	ADA_GRAPPLE
		//-
		*/
	uint8_t index;	// id for each trigger {looks like serial index; buts its an id}
	uint8_t hit_type;	// range [0 - 3]
	/*
		0x00	0	UNDER
		0x01	1	FRONT
		0x02	2	UNDER+ANGLE
		0x03	3	FRONT+ANGLE
		*/
	uint8_t trigger_type;	// appears to be a bitmask; range [0x01; 0x02; 0x04; 0x08; 0x81; 0x82; 0x88]
	/*
		0x01	001	AUTO
		0x02	002	MANUAL
		0x04	004	SEMIAUTO
		0x08	008	ACT_BTN
		0x80	128	ONLY_ONCE
		*/
	uint8_t target_type;	// appears to be a bitmask; range [1; 2; 3; 7; 8; 9; 10; 15]
	/*
		0x00	0	-
		0x01	1	PL
		0x02	2	EM
		0x03	3	PL+EM
		0x04	4	OBJ
		0x05	5	PL+OBJ
		0x06	6	EM+OBJ
		0x07	7	PL+EM+OBJ
		0x08	8	SUB
		0x09	9	PL+SUB
		0x0A	10	EM+SUB
		0x0B	11	PL+EM+SUB
		0x0C	12	OBJ+SUB
		0x0D	13	PL+OBJ+SUB
		0x0E	14	EM+OBJ+SUB
		0x0F	15	PL+EM+OBJ+SUB
		*/
	uint8_t unk021;	// 0 {normal} and 18 have been observed
	uint8_t unk022;	// always 0; NULL
	uint32_t unk023;	// always 0; NULL
	uint32_t unk024;	// always 0; NULL
	uint8_t priority;	// range [0:low - 15:high; 2=defualt]
	uint8_t unk025b;	// range [0; 1]
	uint8_t unk025c;	// always 0; NULL
	uint8_t unk025d;	// always 0; NULL
	int8_t hit_angle;	// range [180 to -180], multiply by 2 to get degrees
	uint8_t open_angle;	// range [0 to 180, default: 0x2D], multiply by 2 to get degrees
	uint8_t action_type;	// ranges [0; 1; 2; 4; 6; 8; 9; 10; 12; 13; 14; 16; 20; 22; 27; 28; 32; 34; 35; 39; 40; 43; 46; 52; 55; 62; 63; 65; 67]
	/*	List By Mr Curious
		Hex	Dec	Desc
		0x00	0	talk
		0x01	1	check
		0x02	2	jump out
		0x03	3	jump in
		0x04	4	jump down
		0x05	5	jump over
		0x06	6	push
		0x07	7	kick
		0x08	8	climb up
		0x09	9	climb down
		0x0A	10	knock down
		0x0B	11	raise up
		0x0C	12	jump
		0x0D	13	look
		0x0E	14	look down
		0x0F	15	back to the wall
		0x10	16	open
		0x11	17	swim
		0x12	18	jump over
		0x13	19	crouch
		0x14	20	operate
		0x15	21	help
		0x16	22	piggyback
		0x17	23	throw
		0x18	24	sprint19
		0x1A	26	jump
		0x1B	27	slide down
		0x1C	28	catch
		0x1D	29	pull up
		0x1E	30	wait
		0x1F	31	stand back
		0x20	32	hide
		0x21	33	follow me
		0x22	34	give me a hand
		0x23	35	get on
		0x24	36	get off
		0x25	37	dodge
		0x26	38	hide
		0x27	39	crawl
		0x28	40	take
		0x29	41	cut
		0x2A	42	rotate
		0x2B	43	shake off
		0x2C	44	suplex
		0x2D	45	dummy
		0x2E	46	begin
		0x2F	47	save
		0x30	48	{blank}
		0x31	49	accelerate
		0x32	50
		0x33	51	send Ashley
		0x34	52	?
		0x35	53	knock over
		0x36	54	respond
		0x37	55	infiltrate
		0x38	56	fan kick
		0x39	57	back kick
		0x3A	58	knee
		0x3B	59	neck breaker
		0x3C	60	thrust punch
		0x3D	61	chikyo chagi
		0x3E	62	jump
		0x3F	63	ring
		0x40	64	hop down
		0x41	65	fire
		0x42	66	rotate
		0x43	67	hook shot
		0x44	68	aaa
		*/
	// not shown in examples
	uint8_t unk026;
	uint32_t unk027; // 1 = disabled, > 1 crashes game
	uint8_t unk028; // does nothing
	uint8_t unk029; // does nothing
	uint8_t msg_flag; //activating 1st bit causes text to disappear
	uint8_t msg_type; // color preset 0 = normal 1 = green 2 = red

	// padding?
	uint32_t unk030;
	uint32_t unk031;

	// 64 bytes appear to be reserved for writing trigger specific data
	//bytestream data;

	fmtAEV_Normal         data_type00;	// General Purpose
	fmtAEV_Door           data_type01;	// Door Way (Room Change)
	fmtAEV_Cut_Scene      data_type02;	// Cut Scene
										// 0x03
	fmtAEV_Flag           data_type04;	// Grouped Enemy Trigger
	fmtAEV_Message        data_type05;	// Message
										// 0x06
	fmtAEV_Jump           data_type07;
	fmtAEV_Save           data_type08;	// Type Writer
	fmtAEV_Shadow_Display data_type09;
	fmtAEV_Damage         data_type0A;	// Damage Causing Events (When walking through or bumping into)
	fmtAEV_Scenario       data_type0B;	// Map Blocking Events (Crank Dependent Pathways, etc...)
	fmtAEV_View_Control   data_type0C;
	fmtAEV_Field_Info     data_type0D;	// ?
										// 0x0E
										// 0x0F
	fmtAEV_Ladder         data_type10;	// Fixed Ladder Climb Up
	fmtAEV_Use            data_type11;	// Item Dependent Events (Locked Doors, Puzzles, ...)
	fmtAEV_Hide           data_type12;	// Ashley's "HIDE" Command
	fmtAEV_Jump_Position  data_type13;	// ?
										// 0x14
	fmtAEV_Grapple        data_type15;	// Ada's Grapple Gun

	/*
		0x00 General Purpose
		0x01 Door Way {Room Change}
		0x02 Cut Scene
		0x03
		0x04 Grouped Enemy Trigger
		0x05 Message
		0x06
		0x07
		0x08 Type Writer
		0x09 Shadow_Display{};
		0x0A Damage Causing Events {When walking through or bumping into}
		0x0B Events {Crank Dependent Pathways; etc...}
		0x0C View_Control
		0x0D Field_Info
		0x0E Region (Crouch)
		0x0F
		0x10 Ladder
		0x11 Locked Doors, Puzzles, etc
		0x12 Ashley's "HIDE" Command
		0x13 Jump_Position
		0x14 Region
		0x15 Ada's Grapple Gun
	*/
	void clear();
	fmtAEV_Region ();
	virtual ~fmtAEV_Region ();
	void read_region (bytestream &f, bool re4_2007 = false);
	void write_region (bytestream &s, bool re4_2007 = false);
	void export_region (std::wstring outfile, std::string secname = "ATARI_EVENT");
	void import_region (std::string secname = "ATARI_EVENT");
	};

struct fmtAEV {	// 16 + {n * 156} bytes {in re4 2007 the buffer is 160 bytes instead of 156}

	uint8_t type[4];		// 0x00564541
	uint16_t version; // Always 0x0104
	uint16_t count; // Range [0 to 64] ? 64 is the max probably
	// padding
	uint32_t unk003;	// Always 0
	uint32_t unk004;	// Always 0
	std::vector<fmtAEV_Region> data;

	// data always padded to 32byte alignment
	fmtAEV ();
	size_t size (bool re4_2007 = false);
	bool validate (bytestream &f, bool &re4_2007, bool verbose = true);
	void read_aev (bytestream &f);
	void write_aev (bytestream &s, bool re4_2007 = false);
	void save_aev (std::wstring savefile, bool re4_2007 = false);
	void export_txt (std::wstring outpath, std::wstring prefix = L"aev", std::wstring subfolder = L"area_events");
	};


#endif // FMTAEV_H
