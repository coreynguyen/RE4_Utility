/*	======================================================================

	Title:		[PC] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		October 05 2020

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Editing of the ESL files (Enemy Spawn List)

	Change Log:

	[2022-02-26]
		replaced read / write functions to use bytestream class
		i regret converting over the read function, because there is now
		dependencies I may revert it back and just byte swap the 3 values
		that are larger then an 8bit int

	[2020-10-05]
		wrote it !

	======================================================================	*/
#ifndef FMTESL_H
#define FMTESL_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"


struct fmtESL_BE { // Behavior Flag
	bool be_alive;	// isVisible
	bool be_set;
	bool be_flg3;
	bool be_flg4;
	bool be_flg5;
	bool be_flg6;
	bool be_flg7;
	bool be_die;
	fmtESL_BE ();
	void set_be_flag (uint8_t val);
	uint8_t get_be_flag ();
	void read_be_flag (bytestream &f);
	void write_be_flag (bytestream &s);
	void write_ini (bool printall = false) {
		if (be_alive || printall) {ini->boolean("be_alive", be_alive);}
		if (be_set || printall) {ini->boolean("be_set", be_set);}
		if (be_flg3 || printall) {ini->boolean("be_flg3", be_flg3);}
		if (be_flg4 || printall) {ini->boolean("be_flg4", be_flg4);}
		if (be_flg5 || printall) {ini->boolean("be_flg5", be_flg5);}
		if (be_flg6 || printall) {ini->boolean("be_flg6", be_flg6);}
		if (be_flg7 || printall) {ini->boolean("be_flg7", be_flg7);}
		if (be_die || printall) {ini->boolean("be_die", be_die);}
		}
	void read_ini (std::string &secname) {
		be_alive = ini->get_boolean(secname, "be_alive");
		be_set = ini->get_boolean(secname, "be_set");
		be_flg3 = ini->get_boolean(secname, "be_flg3");
		be_flg4 = ini->get_boolean(secname, "be_flg4");
		be_flg5 = ini->get_boolean(secname, "be_flg5");
		be_flg6 = ini->get_boolean(secname, "be_flg6");
		be_flg7 = ini->get_boolean(secname, "be_flg7");
		be_die = ini->get_boolean(secname, "be_die");
		}
	};

struct fmtESL_EM { // Enemy Flag
	bool em_flg01;
	bool em_flg02;
	bool em_flg03;
	bool em_flg04;
	bool em_flg05;
	bool em_flg06;
	bool em_flg07;
	bool em_flg08;
	bool em_flg09;
	bool em_flg10;
	bool em_flg11;
	bool em_flg12;
	bool em_flg13;
	bool em_flg14;
	bool em_flg15;
	bool em_flg16;
	bool em_flg17;
	bool em_flg18;
	bool em_flg19;
	bool em_flg20;
	bool em_flg21;
	bool em_flg22;
	bool em_flg23;
	bool em_flg24;
	bool em_flg25;
	bool em_flg26;
	bool em_flg27;
	bool em_flg28;
	bool em_flg29;
	bool em_flg30;
	bool em_flg31;
	bool em_flg32;
	fmtESL_EM ();
	void set_em_flag (uint32_t val);
	uint32_t get_em_flag ();
	void read_em_flag (bytestream &f);
	void write_em_flag (bytestream &s);
	void write_ini (bool printall = false) {
		if (em_flg01 || printall) {ini->boolean("em_flg01", em_flg01);}
		if (em_flg02 || printall) {ini->boolean("em_flg02", em_flg02);}
		if (em_flg03 || printall) {ini->boolean("em_flg03", em_flg03);}
		if (em_flg04 || printall) {ini->boolean("em_flg04", em_flg04);}
		if (em_flg05 || printall) {ini->boolean("em_flg05", em_flg05);}
		if (em_flg06 || printall) {ini->boolean("em_flg06", em_flg06);}
		if (em_flg07 || printall) {ini->boolean("em_flg07", em_flg07);}
		if (em_flg08 || printall) {ini->boolean("em_flg08", em_flg08);}
		if (em_flg09 || printall) {ini->boolean("em_flg09", em_flg09);}
		if (em_flg10 || printall) {ini->boolean("em_flg10", em_flg10);}
		if (em_flg11 || printall) {ini->boolean("em_flg11", em_flg11);}
		if (em_flg12 || printall) {ini->boolean("em_flg12", em_flg12);}
		if (em_flg13 || printall) {ini->boolean("em_flg13", em_flg13);}
		if (em_flg14 || printall) {ini->boolean("em_flg14", em_flg14);}
		if (em_flg15 || printall) {ini->boolean("em_flg15", em_flg15);}
		if (em_flg16 || printall) {ini->boolean("em_flg16", em_flg16);}
		if (em_flg17 || printall) {ini->boolean("em_flg17", em_flg17);}
		if (em_flg18 || printall) {ini->boolean("em_flg18", em_flg18);}
		if (em_flg19 || printall) {ini->boolean("em_flg19", em_flg19);}
		if (em_flg20 || printall) {ini->boolean("em_flg20", em_flg20);}
		if (em_flg21 || printall) {ini->boolean("em_flg21", em_flg21);}
		if (em_flg22 || printall) {ini->boolean("em_flg22", em_flg22);}
		if (em_flg23 || printall) {ini->boolean("em_flg23", em_flg23);}
		if (em_flg24 || printall) {ini->boolean("em_flg24", em_flg24);}
		if (em_flg25 || printall) {ini->boolean("em_flg25", em_flg25);}
		if (em_flg26 || printall) {ini->boolean("em_flg26", em_flg26);}
		if (em_flg27 || printall) {ini->boolean("em_flg27", em_flg27);}
		if (em_flg28 || printall) {ini->boolean("em_flg28", em_flg28);}
		if (em_flg29 || printall) {ini->boolean("em_flg29", em_flg29);}
		if (em_flg30 || printall) {ini->boolean("em_flg30", em_flg30);}
		if (em_flg31 || printall) {ini->boolean("em_flg31", em_flg31);}
		if (em_flg32 || printall) {ini->boolean("em_flg32", em_flg32);}
		}
	void read_ini (std::string &secname) {
		em_flg01 = ini->get_boolean(secname, "em_flg01");
		em_flg02 = ini->get_boolean(secname, "em_flg02");
		em_flg03 = ini->get_boolean(secname, "em_flg03");
		em_flg04 = ini->get_boolean(secname, "em_flg04");
		em_flg05 = ini->get_boolean(secname, "em_flg05");
		em_flg06 = ini->get_boolean(secname, "em_flg06");
		em_flg07 = ini->get_boolean(secname, "em_flg07");
		em_flg08 = ini->get_boolean(secname, "em_flg08");
		em_flg09 = ini->get_boolean(secname, "em_flg09");
		em_flg10 = ini->get_boolean(secname, "em_flg10");
		em_flg11 = ini->get_boolean(secname, "em_flg11");
		em_flg12 = ini->get_boolean(secname, "em_flg12");
		em_flg13 = ini->get_boolean(secname, "em_flg13");
		em_flg14 = ini->get_boolean(secname, "em_flg14");
		em_flg15 = ini->get_boolean(secname, "em_flg15");
		em_flg16 = ini->get_boolean(secname, "em_flg16");
		em_flg17 = ini->get_boolean(secname, "em_flg17");
		em_flg18 = ini->get_boolean(secname, "em_flg18");
		em_flg19 = ini->get_boolean(secname, "em_flg19");
		em_flg20 = ini->get_boolean(secname, "em_flg20");
		em_flg21 = ini->get_boolean(secname, "em_flg21");
		em_flg22 = ini->get_boolean(secname, "em_flg22");
		em_flg23 = ini->get_boolean(secname, "em_flg23");
		em_flg24 = ini->get_boolean(secname, "em_flg24");
		em_flg25 = ini->get_boolean(secname, "em_flg25");
		em_flg26 = ini->get_boolean(secname, "em_flg26");
		em_flg27 = ini->get_boolean(secname, "em_flg27");
		em_flg28 = ini->get_boolean(secname, "em_flg28");
		em_flg29 = ini->get_boolean(secname, "em_flg29");
		em_flg30 = ini->get_boolean(secname, "em_flg30");
		em_flg31 = ini->get_boolean(secname, "em_flg31");
		em_flg32 = ini->get_boolean(secname, "em_flg32");
		}
	};

struct fmtESL_Spawn { // 32 bytes, max 256 items
	fmtESL_BE be_flag;
	uint8_t modelID;	// hex is the udas packate 2A = em2a.udas
	uint8_t type;		// Range [0 - 255], event model anything above 0 is for a cutscene
	uint8_t anim_set;
	fmtESL_EM em_flag;
	uint16_t healthPoints;
	uint8_t unk1;
	uint8_t chara; // Character Chase Mode
	/*	Only valid for Ganado's
		0x00	0	chara
		0x01	1	Keep
		0x02	2	Rush
		0x03	3	Stop
		0x04	4	Escape
		0x05	5	In Room
		*/
	uint16_t position[3];
	uint16_t rotation[3];
	uint16_t roomID;				// Range [0 - 255]
	uint16_t guard_radius; // meters
	uint8_t unk4;
	uint8_t unk5;
	uint8_t unk6;
	uint8_t unk7;
	fmtESL_Spawn ();
	void read_esl_spawn (bytestream &f);
	void write_esl_spawn (bytestream &s);
	void write_ini (bool printall = false) {
		std::string cmt;
		be_flag.write_ini(printall);
		ini->integer("modelID", modelID);
		ini->integer("type", type);
		ini->integer("anim_set", anim_set);
		em_flag.write_ini(printall);
		ini->integer("healthPoints", healthPoints);
		if (printall) {ini->integer("unk1", unk1);}

		switch (chara) {
			case 0x00: {cmt = "chara"; break;}
			case 0x01: {cmt = "Keep"; break;}
			case 0x02: {cmt = "Rush"; break;}
			case 0x03: {cmt = "Stop"; break;}
			case 0x04: {cmt = "Escape"; break;}
			case 0x05: {cmt = "In Room"; break;}
			default: {cmt = "Does Nothing?";}
			}

		ini->integer("chara", chara, cmt);
		ini->vector3(
			"position",
			(float)position[0] * app->centi_to_milli,
			(float)position[1] * app->centi_to_milli,
			(float)position[2] * app->centi_to_milli,
			false
			);
		ini->vector3(
			"rotation",
			(float)rotation[0] * app->eslrot_to_degree,
			(float)rotation[1] * app->eslrot_to_degree,
			(float)rotation[2] * app->eslrot_to_degree,
			false
			);
		ini->integer("stage_id", (roomID && 0xFF00) >> 8);
		ini->integer("room_id", roomID && 0x00FF);
		ini->integer("guard_radius", guard_radius * app->meters_to_milli);
		if (printall) {ini->integer("unk4", unk4);}
		if (printall) {ini->integer("unk5", unk5);}
		if (printall) {ini->integer("unk6", unk6);}
		if (printall) {ini->integer("unk7", unk7);}
		}
	void read_ini (std::string &secname) {
		be_flag.read_ini(secname);
		modelID = ini->get_integer(secname, "modelID");
		type = ini->get_integer(secname, "type");
		anim_set = ini->get_integer(secname, "anim_set");
		em_flag.read_ini(secname);
		healthPoints = ini->get_integer(secname, "healthPoints");
		unk1 = ini->get_integer(secname, "unk1");
		chara = ini->get_integer(secname, "chara");
		float pos_x, pos_y, pos_z;
		float rot_x, rot_y, rot_z;
		ini->get_vector3(secname, "position", pos_x, pos_y, pos_z);
		ini->get_vector3(secname, "rotation", rot_x, rot_y, rot_z);
		position[0] = pos_x * app->milli_to_centi;
		position[1] = pos_y * app->milli_to_centi;
		position[2] = pos_z * app->milli_to_centi;
		rotation[0] = rot_x * app->degree_to_eslrot;
		rotation[1] = rot_y * app->degree_to_eslrot;
		rotation[2] = rot_z * app->degree_to_eslrot;
		roomID = ini->get_integer(secname, "stage_id") << 8;
		roomID += ini->get_integer(secname, "room_id");
		guard_radius = ini->get_integer(secname, "guard_radius") * app->milli_to_centi;
		unk4 = ini->get_integer(secname, "unk4");
		unk5 = ini->get_integer(secname, "unk5");
		unk6 = ini->get_integer(secname, "unk6");
		unk7 = ini->get_integer(secname, "unk7");
		}
	};

struct fmtESL { // Enemy Spawn List
	fmtESL_Spawn spawn[255]; // max 255 entries, data gets copied into the sav file
	bool validate (bytestream &f);
	bool read_esl (bytestream &f);
	void write_esl (bytestream &s);
	};

#endif // FMTESL_H
