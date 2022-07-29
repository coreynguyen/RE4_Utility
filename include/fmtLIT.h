#ifndef FMTLIT_H
#define FMTLIT_H


#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"


struct fmtLIT_Light_Emit_Shine {
	uint32_t unk1;
	uint32_t unk2;
	float speed[3];	// z is not used
	fmtLIT_Light_Emit_Shine ();
	void read_light_emit_shine (bytestream &f);
	void write_light_emit_shine (bytestream &s);
	};

struct fmtLIT_Light_Emit_Path_Fade {
	float start;
	float speed;
	fmtLIT_Light_Emit_Path_Fade ();
	void read_light_emit_fade (bytestream &f);
	void write_light_emit_fade (bytestream &s);
	};

struct fmtLIT_Light_Emit_Path_Flag {
	bool loop_off;
	bool inverse_on;
	bool path_flag3;
	bool path_flag4;
	bool path_flag5;
	bool path_flag6;
	bool path_flag7;
	bool path_flag8;
	fmtLIT_Light_Emit_Path_Flag ();
	void read_light_emit_path_flag (uint32_t val);
	void write_light_emit_path_flag (bytestream &s);
	};

struct fmtLIT_Light_Emit_Path { // custom flicker
	uint32_t unk1;
	uint32_t unk2;
	fmtLIT_Light_Emit_Path_Flag flag;
	uint8_t unk3;
	uint8_t unk4;
	uint8_t unk5;
	uint8_t path_index;
	fmtLIT_Light_Emit_Path ();
	void read_light_emit_path (bytestream &f);
	void write_light_emit_path (bytestream &s);
	};

struct fmtLIT_Light_Emit_Shadow_Flag {
	bool use_tex;
	bool shdw_flag2;
	bool invert_tex;
	bool shdw_flag4;
	bool shdw_flag5;
	bool shdw_flag6;
	bool shdw_flag7;
	bool shdw_flag8;
	fmtLIT_Light_Emit_Shadow_Flag ();
	void read_light_emit_shadow_flag (uint32_t val);
	void write_light_emit_shadow_flag (bytestream &s);
	};

struct fmtLIT_Light_Emit_Shadow {
	uint8_t unk1; // always 0?
	fmtLIT_Light_Emit_Shadow_Flag tex_flag;
	uint8_t type;	// range:[0:NORMAL; 1:CAST; 2:CAST_ADD; 3:CAST2; 4:CAST2_ADD; 5:FOOT]
	uint8_t tex_no; // range [0 - 255]
	int8_t gnd_dist; // range [-128 to 127]
	uint16_t unk2;
	uint16_t unk3;
	uint8_t unk4;
	uint8_t unk5;
	uint8_t unk6;
	uint8_t unk7;
	float unk8[3];
	uint32_t unk9;
	fmtLIT_Light_Emit_Shadow ();
	void read_light_emit_shadow (bytestream &f);
	void write_light_emit_shadow (bytestream &s);
	};

struct fmtLIT_Light_Emit_Spot {
	float rotation[3];	// EulerAngles in radians range:[-3.14 to 3.14] {pi} causes light to animation by rotating light
	fmtLIT_Light_Emit_Spot ();
	void read_light_emit_spot (bytestream &f);
	void write_light_emit_spot (bytestream &s);
	};

struct fmtLIT_Light_Emit_Wave {
	float center;
	float range;
	float speed; // must be greater then 0.0
	float unk1;
	fmtLIT_Light_Emit_Wave ();
	void read_light_emit_wave (bytestream &f);
	void write_light_emit_wave (bytestream &s);
	};

struct fmtLIT_Light_Emit_Flicker {
	uint8_t colour[4]; // doesnt seem to do anything??
	uint8_t rate; // flicker intensity range:[0 - 127] 127 being very strong
	fmtLIT_Light_Emit_Flicker ();
	void read_light_emit_flicker (bytestream &f);
	void write_light_emit_flicker (bytestream &s);
	};

struct fmtLIT_Light_Type_Local {
	float smooth_edge;
	fmtLIT_Light_Type_Local ();
	void read_light_type_local (bytestream &f);
	void write_light_type_local (bytestream &s);
	};

struct fmtLIT_Light_Type_Spot_quad {
	float direction[3];
	float distance;	// range [1.0 - 90.0] must be greater then 1.0
	float smooth_edge;
	fmtLIT_Light_Type_Spot_quad ();
	void read_light_type_spot_quad (bytestream &f);
	void write_light_type_spot_quad (bytestream &s);
	};

struct fmtLIT_Light_type_custom { // i didnt bother to to implement; since I need to test ingame alot
	/*
	this type is not demostrated in any of the files
	however it can be played with in the debug menu

	a curve graph is shown; in which 6 float
	values can be changed which alter the
	curve graph.

	various light intensity and falloff can be observed

	because there are no file examples of how this
	data works in the file I can only guess what
	the structure might be.
	*/
	uint8_t gear;
	float direction[3];
	float A0;
	float A1;
	float A2;
	float K0;
	float K1;
	float K2;
	};

struct fmtLIT_Light_Type_Para {
	float direction[3]; // z not used {Roll}
	uint32_t is_dir_auto;	// 0: No  1: Yes
	float smooth_edge;
	fmtLIT_Light_Type_Para ();
	void read_light_type_para (bytestream &f);
	void write_light_type_para (bytestream &s);
	};

struct fmtLIT_Light_Type_Spot {
	float direction[3];
	float distance;	// range [1.0 - 90.0] must be greater then 1.0
	float smooth_edge;
	fmtLIT_Light_Type_Spot ();
	void read_light_type_spot (bytestream &f);
	void write_light_type_spot (bytestream &s);
	};

struct fmtLIT_Light_Type_Quad {
	float smooth_edge;
	float direction[3];
	float unk1;
	fmtLIT_Light_Type_Quad ();
	void read_light_type_quad (bytestream &f);
	void write_light_type_quad (bytestream &s);
	};

struct fmtLIT_Light_Type_Linear {
	float direction[3];
	uint8_t is_dir_auto;
	fmtLIT_Light_Type_Linear ();
	void read_light_type_linear (bytestream &f);
	void write_light_type_linear (bytestream &s);
	};

struct fmtLIT_Light_Type_Constant {
	uint8_t unk1;
	uint8_t unk2;
	uint8_t unk3;
	uint8_t unk4;
	uint32_t unk5;
	float unk6;
	fmtLIT_Light_Type_Constant ();
	void read_light_type_constant (bytestream &f);
	void write_light_type_constant (bytestream &s);
	};

struct fmtLIT_Light_Interact_Flag {
	bool on_player;
	bool on_enemy;
	bool on_object;
	bool on_effect;
	bool on_room;
	bool on_item;
	bool on_subchar;
	bool on_thermo;
	fmtLIT_Light_Interact_Flag ();
	void read_light_mask_flag (uint32_t val);
	void write_light_mask_flag (bytestream &s);
	};

struct fmtLIT_Light_Attribute {
	bool no_tune;
	bool elec_light;
	bool taimatu; // fire
	bool attr_flag4;
	bool attr_flag5;
	bool attr_flag6;
	bool attr_flag7;
	bool attr_flag8;
	fmtLIT_Light_Attribute ();
	void read_light_attribute_flag (uint32_t val);
	void write_light_attribute_flag (bytestream &s);
	};

struct fmtLIT_Light_Unknown { // 64bytes
	uint32_t unk021;
	float unk022;
	uint8_t unk023;
	uint8_t unk024;
	uint8_t unk025;
	uint8_t unk026;
	uint16_t unk027;
	uint16_t unk028;
	uint32_t unk029;
	uint32_t unk030;
	uint32_t unk031;
	uint32_t unk032;
	uint32_t unk033;
	uint32_t unk034;
	uint32_t unk035;
	uint32_t unk036;
	uint32_t unk037;
	uint8_t unk038;
	uint8_t unk039;
	uint8_t unk040;
	uint8_t unk041;
	uint32_t unk042;
	uint32_t unk043;
	fmtLIT_Light_Unknown ();
	void read_light_unkdata (bytestream &f);
	void write_light_unkdata (bytestream &s);
	};

struct fmtLIT_Light_Flag {
	bool lit_flag1;	// Enable Data {MUST ALWAYS BE ON}
	bool lit_flag2;	// Enable Light?
	bool lit_flag3;	// Light is SkyLight?
	bool lit_flag4;
	bool lit_flag5;
	bool lit_flag6;
	bool lit_flag7;
	bool lit_flag8;
	fmtLIT_Light_Flag ();
	void read_light_flag (uint32_t val);
	void write_light_flag (bytestream &s);
	};

struct fmtLIT_Light { // 300 bytes
	/*uint8_t*/fmtLIT_Light_Flag flag; // flag? Range:[3; 5; 7]
	/*
	based on samples first 3 bits are used
	the first bit MUST always be on;
	therefore the combinations are

	001	=	1
	011	=	3
	101	=	5
	111	=	7

	bit1	=	Enable Data Read?
	bit2	=	Enable Light ?
	bit3	=	Enable

	collected counts of the types used across all samples

	type1		=	0
	type3		=	78
	type5		=	7731
	type7		=	39381
	*/
	uint8_t type; // light type range:[0: CONSTANT; 1:LINEAR; 2:QUADRATIC; 3:SPOT_LIGHT; 4:CUSTOM; 5:PARALLEL; 6:SPOT_QUAD; 7:LOCAL_AMBIENT]
	uint8_t emit_type; // light emission type range [0:NORMAL; 1:FLICKER; 2:WAVE; 3:SPOT_ROTATE; 4:SHADOW; 5:PATH; 6:FADE; 7:SHINE; 8:SPOT_LOCK; 9:RESERVED]
	fmtLIT_Light_Interact_Flag mask_flag; // light mask
	float position[3]; // position
	float radius; // radius {0.0 // infinity} radius should be in units of 100
	uint8_t colour[4]; // light colour
	float intensity; // light intensity range [0.1 >] must be greater then 0.1; 0.6 seems to be default
	uint8_t parent_type; // parent range:[0:WOLRD; 1:ENEMY; 2:ROOM; 3:EtcModel; 4:OBJECT]
	uint8_t kind; // kind? range:[0- 255] seen values in files ranging around 0-26; may be an index to something?
	fmtLIT_Light_Attribute attr; // atriibute
	uint8_t priority; // priority range:[0 - 6] 3 is default
	uint16_t parent_part_id;	// Range:[0 - 99]
	uint16_t parent_model_id;	// Range:[0:PLAYER; 3:ASHLEY; 4:LUIS] * for full list see below
	/*	ID_LIST
		0x00: 	PLAYER
		0x01:
		0x02:
		0x03: 	ASHLEY
		0x04: 	LUIS
		0x05:
		0x06:
		0x07:
		0x08:
		0x09:
		0x0A:
		0x0B:
		0x0C:
		0x0D:
		0x0E: 	JET_SKI
		0x0F: 	MOTOR_BOAT
		0x10: 	GANADO_1
		0x11: 	GANADO_2
		0x12: 	GANADO_1-C
		0x13: 	GANADO_1+W
		0x14: 	GANADO_2+W
		0x15: 	GANADO_1+C
		0x16: 	GANADO_1+C2
		0x17: 	GANADO_1-C2
		0x18: 	TRADER
		0x19: 	GANADO_2+A
		0x1A: 	GANADO_2+R
		0x1B: 	GANADO_2+CM
		0x1C: 	GANADO_2+CM2
		0x1D: 	GANADO_3+GM
		0x1E: 	GANADO_3+W
		0x1F: 	GANADO_3
		0x20: 	SPIDER // ?GANADO_3+G+C
		0x21: 	ENEMY_DOG
		0x22: 	DOG
		0x23: 	CROW
		0x24: 	SNAKE S
		0x25: 	PARASITE
		0x26: 	COW
		0x27: 	BLACKBASS
		0x28: 	CHICKEN
		0x29: 	BAT
		0x2A: 	TRAP
		0x2B: 	ELGIGANTE
		0x2C: 	INSECT_BOSS
		0x2D: 	INSECT_HUMAN
		0x2E: 	SPIDER_S
		0x2F: 	SALAMANDER
		0x30: 	SADDLER
		0x31: 	SADDLER_2
		0x32: 	U3
		0x33: 	INSECT_BOSS_EVENT
		0x34: 	MAYOR
		0x35: 	MAYOR_AFTER
		0x36: 	REGENERATOR
		0x37: 	NO2
		0x38: 	NO2_AFTER
		0x39: 	NO3
		0x3A: 	NO3_AFTER
		0x3B: 	TRUCK
		0x3C: 	AMMOR
		0x3D: 	HELICOPTER
		0x3E:
		0x3F:
		0x40: 	OBJ
		0x41: 	DOOR
		0x42: 	WEP
		0x43: 	BOX
		0x44: 	WALL
		0x45: 	RACK
		0x46: 	WINDOW
		0x47: 	TORCH
		0x48: 	BARREL
		0x49: 	TREE
		0x4A: 	ROCK
		0x4B: 	SWITCH
		0x4C: 	ITEM
		0x4D: 	HIT
		0x4E: 	BARRED
		0x4F: 	MINE
		0x50: 	SHIELD
	*/
	uint16_t hit_radius; // collision sphere of light
	uint8_t unk3;
	uint8_t unk4;
	float unk5;
	fmtLIT_Light_Type_Constant type_constant;
	fmtLIT_Light_Type_Linear type_linear;
	fmtLIT_Light_Type_Spot type_spot;
	fmtLIT_Light_Type_Quad type_quad;
	fmtLIT_Light_Type_Para type_para;
	fmtLIT_Light_Type_Spot_quad type_spot_quad;
	fmtLIT_Light_Type_Local type_local;
	fmtLIT_Light_Emit_Flicker emit_flicker;
	fmtLIT_Light_Emit_Wave emit_wave;
	fmtLIT_Light_Emit_Spot emit_spot;
	fmtLIT_Light_Emit_Shadow emit_shadow;
	fmtLIT_Light_Emit_Path emit_path;
	fmtLIT_Light_Emit_Path_Fade emit_fade;
	fmtLIT_Light_Emit_Shine emit_shine;
	uint8_t reserve1[64];// 64 bytes is reserved for light type properties
	uint8_t reserve2[64];// 64 bytes is reserved for light emission type properties
	uint8_t reserve3[64];// 64 bytes is reserved; is blank on all samples
	uint8_t reserve4[64];// 64 bytes is reserved; is blank on all samples
	fmtLIT_Light ();
	void read_light (bytestream &f);
	void write_light (bytestream &s);
	};

struct fmtLIT_Entry { // 260 bytes + {n lights x 300 bytes}
	/*
	terminology is a bit indecisive; it is not a
	'lit group' or an area..

	the game refers to this data as scene cut data

	the data represents a scene setup which can
	modify lighting; atmospherics and post processing
	*/
	uint8_t room_ambient[4];
	uint32_t light_count;	// light count range:[0-99]
	uint32_t fog_type;	// fog type {bit mask?} range: [0:NONE; 2:LINEAR; 4:EXP; 5:EXP2; 6:REV_EXP; 7:REV_EXP2]
	float fog_start;
	float fog_end;
	uint8_t fog_colour[4];	// fog color
	uint32_t mfog_type;		// mirror fog type  {bit mask?} range: [0:NONE; 2:LINEAR; 4:EXP; 5:EXP2; 6:REV_EXP; 7:REV_EXP2; ]
	float mfog_start;
	float mfog_end;
	uint8_t mfog_colour[4];	// mirror fog color
	int32_t focus_dist; // range:[-2000 to 300000]
	uint8_t unk011;	// enable focus distance? range[0 - 1]
	// to see a focus affect type 0A 01 to enable it
	uint8_t focus_level; // focus level range: [0 - 10] {0 focused; 10 very unfocused}
	uint8_t focus_mode; // focus mode range:[0:NEAR; 1:FAR; 2:FOLLOW_PL_NEAR; 3:FOLLOW_PL_NEAR]
	uint8_t blur_affect; // blur rate range:[0 - 255] {0 no blur; 255 very blurry}
	uint8_t tune_src; // Tune Source range:[0:CORE; 1:ROOM] also always 0
	uint8_t unk012; // range:[0; 99]
	uint8_t unk013; // range:[0; 176]
	uint8_t unk014; // always 0
	uint8_t tune_light_colour[4]; // tune light colour
	uint8_t tune_ambient_colour[4]; // tune ambient colour
	uint8_t tune_effect_colour[4]; // tune effects colour
	uint8_t tev_scale_model; // Model TEV Scale range: [0:x1; 1:x2; 2:x4]
	uint8_t tev_scale_player; // Player TEV Scale range: [0:x1; 1:x2; 2:x4]
	uint8_t unk016c;	// scale value; but not sure what it controls range:[0; 1]
	uint8_t unk016d;	// likely a scale value aswell range:[0; 1]
	float fog_thickness; // fog distance? Range: [0.0 - 1.0]
	uint8_t hokan; // Completion Parameter range:[0 - 249] observed values {0; 50; 60; 70; 75; 81; 87; 90}
	uint8_t unk018b; // ???? range:[0; 9]
	uint8_t unk018c; // always 0
	uint8_t unk018d; // always 0
	fmtLIT_Light_Unknown unkdata1;
	fmtLIT_Light_Unknown unkdata2;
	float unk051; // seen 0.0; 45.447; 6023.8
	float unk052; // seen 0; 450; 700 which may be radii?
	float unk053; // seen 0.0; -1332.73; -2623.36
	float unk054; // seen 0; 3760; 4151
	uint32_t unk055; // ?
	float unk056; // seen 0.0; 0.78; 1.37
	uint8_t unk057a; // always 0
	uint8_t unk057b; // always 0
	uint8_t unk057c; // seen 0 or 2 in some files
	uint8_t unk057d; // seen 0; 3; 5
	float unk058; // seen 0.0; 186.162; 2916.05
	/*uint8_t*/float wind_dir;	// Wind {Cloth} Direction range[0 - 255] number is in radians
	/*uint8_t*/float wind_power;	// Wind {Cloth} Power range[0 - 255] multiply by 0.2 then the range is between 0.0 - 51.0
	/*uint8_t*/float wind_frequency;	// Wind {Cloth} Frequency range [0 - 255] multiply by 0.0104706 then the range is between [0.0 - 2.67]
	uint8_t unk059d; // always 0
	uint8_t blur_type; // blur type range:[0:NORMAL; 1:SPREAD; 2:ADD]
	int8_t blur_power; // blur pow range [-128 to 127]
	uint8_t mipmap_min_lod; // MipMap Min LOD range:[0 - 5] always 0
	uint8_t mipmap_max_lod; // MipMap Max LOD range:[0 - 5]
	uint8_t mipmap_aniso_type; // MipMap Aniso range:[0:GX_ANISO_1; 1:GX_ANISO_2; 2:GX_ANISO_4]
	// to see a Blur affect type 03 FF 00 to enable it
	uint8_t contrast_level; // contrast level range:[0 - 3] needs to be greater then 0 to enable; in a sample 113 was found here? maybe parsing wrong or this is a flag
	uint8_t contrast_power; // contrast pow range [0 - 255] and level need to be greater then 0 to enable
	uint8_t contrast_bias; // contrast bias range [0 - 0255] should be 0; larger the number the more darker the image
	float mipmap_lod_bias; // MipMap LOD Bias range: [-1.0 to 1.0]
	uint8_t object_ambient[4];
	uint8_t effect_ambient[4];
	std::vector<fmtLIT_Light> light_array;
	fmtLIT_Entry ();
	void read_lit_entry (bytestream &f);
	void write_fmtLIT_Entry (bytestream &s);
	};

struct fmtLIT {
	uint16_t area_count; // cut table count
	uint8_t litVersion; // ? LitVer range:[37 - 49]
	/*
	decreasing the number results in an error
	'LitVer: VERSION UP' being thrown in the game

	I collected counts of each version being used

	37		x1		!Returns Error		Isnstance: r120_02.LIT
	39		x6		!Returns Error		Instances: ranging through st3 to st7 rooms
	40		x206	!Returns Error		Instances: ranging through st0 to st7 rooms
	41		x6		!Returns Error		Instances: ranging through st0 to st7 rooms
	42		x2								Instances: r324_02.LIT; s11_003.lit
	43		x97
	44		x357
	48		x6								Instances: r51f_02.LIT; r530_02.LIT; r60e_02.LIT; r61f_02.LIT; r621_02.LIT; r702_02.LIT
	49		x3								Instances: r512_02.LIT; r532_02.LIT; r612_02.LIT

	Ironically changing the version does not result in any sort of
	visible affect.

	The file structure was written with alot of spaced out
	in groups of 64bytes

	They likely planned it like this so they could adjust
	structures during development while maintaining
	stable file reading.

	This may also explain why some data blocks dont
	do anything when being overwritten with random
	bytes
	*/
	uint8_t nMaxLights; // nMaxLights range:[0 - 67] max number of lights across all cuts
	std::vector<uint32_t> area_addrs;
	std::vector<fmtLIT_Entry> areas;
	// pad file to 32
	fmtLIT ();
	void read_lit (bytestream &f);
	size_t recalc_pointers ();
	void write_lit (bytestream &s);
	};

#endif // FMTLIT_H
