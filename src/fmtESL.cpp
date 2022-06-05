#include "fmtESL.h"


fmtESL_BE::fmtESL_BE () {
	be_alive = true;
	be_set = false;
	be_flg3 = false;
	be_flg4 = false;
	be_flg5 = false;
	be_flg6 = false;
	be_flg7 = false;
	be_die = false;
	}

void fmtESL_BE::set_be_flag (uint8_t val) {
	be_alive = bit::get(val, 1);
	be_set = bit::get(val, 2);
	be_flg3 = bit::get(val, 3);
	be_flg4 = bit::get(val, 4);
	be_flg5 = bit::get(val, 5);
	be_flg6 = bit::get(val, 6);
	be_flg7 = bit::get(val, 7);
	be_die = bit::get(val, 8);
	}

uint8_t fmtESL_BE::get_be_flag () {
	int val = 0;
	val = bit::set(val, 1, be_alive);
	val = bit::set(val, 2, be_set);
	val = bit::set(val, 3, be_flg3);
	val = bit::set(val, 4, be_flg4);
	val = bit::set(val, 5, be_flg5);
	val = bit::set(val, 6, be_flg6);
	val = bit::set(val, 7, be_flg7);
	val = bit::set(val, 8, be_die);
	return val;
	}

void fmtESL_BE::read_be_flag (bytestream &f) {
	set_be_flag(f.readUbyte());
	}

void fmtESL_BE::write_be_flag (bytestream &s) {
	s.writebyte(get_be_flag());
	}

fmtESL_EM::fmtESL_EM () {
	em_flg01 = false;
	em_flg02 = false;
	em_flg03 = false;
	em_flg04 = false;
	em_flg05 = false;
	em_flg06 = false;
	em_flg07 = false;
	em_flg08 = false;
	em_flg09 = false;
	em_flg10 = false;
	em_flg11 = false;
	em_flg12 = false;
	em_flg13 = false;
	em_flg14 = false;
	em_flg15 = false;
	em_flg16 = false;
	em_flg17 = false;
	em_flg18 = false;
	em_flg19 = false;
	em_flg20 = false;
	em_flg21 = false;
	em_flg22 = false;
	em_flg23 = false;
	em_flg24 = false;
	em_flg25 = false;
	em_flg26 = false;
	em_flg27 = false;
	em_flg28 = false;
	em_flg29 = false;
	em_flg30 = false;
	em_flg31 = false;
	em_flg32 = false;
	}

void fmtESL_EM::set_em_flag (uint32_t val) {
	em_flg01 = bit::get(val,  1);
	em_flg02 = bit::get(val,  2);
	em_flg03 = bit::get(val,  3);
	em_flg04 = bit::get(val,  4);
	em_flg05 = bit::get(val,  5);
	em_flg06 = bit::get(val,  6);
	em_flg07 = bit::get(val,  7);
	em_flg08 = bit::get(val,  8);
	em_flg09 = bit::get(val,  9);
	em_flg10 = bit::get(val, 10);
	em_flg11 = bit::get(val, 11);
	em_flg12 = bit::get(val, 12);
	em_flg13 = bit::get(val, 13);
	em_flg14 = bit::get(val, 14);
	em_flg15 = bit::get(val, 15);
	em_flg16 = bit::get(val, 16);
	em_flg17 = bit::get(val, 17);
	em_flg18 = bit::get(val, 18);
	em_flg19 = bit::get(val, 19);
	em_flg20 = bit::get(val, 20);
	em_flg21 = bit::get(val, 21);
	em_flg22 = bit::get(val, 22);
	em_flg23 = bit::get(val, 23);
	em_flg24 = bit::get(val, 24);
	em_flg25 = bit::get(val, 25);
	em_flg26 = bit::get(val, 26);
	em_flg27 = bit::get(val, 27);
	em_flg28 = bit::get(val, 28);
	em_flg29 = bit::get(val, 29);
	em_flg30 = bit::get(val, 30);
	em_flg31 = bit::get(val, 31);
	em_flg32 = bit::get(val, 32);
	}

uint32_t fmtESL_EM::get_em_flag () {
	unsigned int val = 0;
	val = bit::set(val,  1, em_flg01);
	val = bit::set(val,  2, em_flg02);
	val = bit::set(val,  3, em_flg03);
	val = bit::set(val,  4, em_flg04);
	val = bit::set(val,  5, em_flg05);
	val = bit::set(val,  6, em_flg06);
	val = bit::set(val,  7, em_flg07);
	val = bit::set(val,  8, em_flg08);
	val = bit::set(val,  9, em_flg09);
	val = bit::set(val, 10, em_flg10);
	val = bit::set(val, 11, em_flg11);
	val = bit::set(val, 12, em_flg12);
	val = bit::set(val, 13, em_flg13);
	val = bit::set(val, 14, em_flg14);
	val = bit::set(val, 15, em_flg15);
	val = bit::set(val, 16, em_flg16);
	val = bit::set(val, 17, em_flg17);
	val = bit::set(val, 18, em_flg18);
	val = bit::set(val, 19, em_flg19);
	val = bit::set(val, 20, em_flg20);
	val = bit::set(val, 21, em_flg21);
	val = bit::set(val, 22, em_flg22);
	val = bit::set(val, 23, em_flg23);
	val = bit::set(val, 24, em_flg24);
	val = bit::set(val, 25, em_flg25);
	val = bit::set(val, 26, em_flg26);
	val = bit::set(val, 27, em_flg27);
	val = bit::set(val, 28, em_flg28);
	val = bit::set(val, 29, em_flg29);
	val = bit::set(val, 30, em_flg30);
	val = bit::set(val, 31, em_flg31);
	val = bit::set(val, 32, em_flg32);
	return val;
	}

void fmtESL_EM::read_em_flag (bytestream &f) {
	set_em_flag(f.readUlong());
	}

void fmtESL_EM::write_em_flag (bytestream &s) {
	s.writelong(get_em_flag());
	}

fmtESL_Spawn::fmtESL_Spawn () {
	be_flag.set_be_flag(0);
	modelID = 0;
	type = 0;
	anim_set = 0;
	em_flag.set_em_flag(0);
	healthPoints = 0;
	unk1 = 0;
	chara = 0;
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	rotation[0] = 0;
	rotation[1] = 0;
	rotation[2] = 0;
	roomID = 0;
	guard_radius = 0;
	unk4 = 0;
	unk5 = 0;
	unk6 = 0;
	unk7 = 0;
	}

void fmtESL_Spawn::read_esl_spawn (bytestream &f) {
	//const double GUARDRAD_SCALE = 1000.0; //  converts meters to millimeters
	//const double POSITION_SCALE = 10.0; //  cm converts to millimeters
	//const double ROTATION_SCALE = 0.010986332551700724487745603456244676035; // converts whatever to degrees
	//const double ROTATION_SCALE2 = 0.00019174767574620779644429946175175338444; // converts whatever to radians

	be_flag.read_be_flag(f);
	modelID = f.readUbyte();
	type = f.readUbyte();
	anim_set = f.readUbyte();
	em_flag.read_em_flag(f);
	healthPoints = f.readUshort(); // set to 0, enemy will ignore player and cannot die
	unk1 = f.readUbyte();
	chara = f.readUbyte();
	position[0] = f.readshort();// * POSITION_SCALE;
	position[1] = f.readshort();// * POSITION_SCALE;
	position[2] = f.readshort();// * POSITION_SCALE;
	rotation[0] = f.readshort();// * ROTATION_SCALE;
	rotation[1] = f.readshort();// * ROTATION_SCALE;
	rotation[2] = f.readshort();// * ROTATION_SCALE;
	roomID = f.readUshort();
	guard_radius = f.readUshort();// * GUARDRAD_SCALE
	// padding
	unk4 = f.readUbyte();
	unk5 = f.readUbyte();
	unk6 = f.readUbyte();
	unk7 = f.readUbyte();
	}

void fmtESL_Spawn::write_esl_spawn (bytestream &s) {
	be_flag.write_be_flag(s);
	s.writebyte(modelID);
	s.writebyte(type);
	s.writebyte(anim_set);
	em_flag.write_em_flag(s);
	s.writeshort(healthPoints);
	s.writebyte(unk1);
	s.writebyte(chara);
	s.writeshort(position[0]);
	s.writeshort(position[1]);
	s.writeshort(position[2]);;
	s.writeshort(rotation[0]);
	s.writeshort(rotation[1]);
	s.writeshort(rotation[2]);
	s.writeshort(roomID);
	s.writeshort(guard_radius);
	s.writebyte(unk4);
	s.writebyte(unk5);
	s.writebyte(unk6);
	s.writebyte(unk7);
	}

bool fmtESL::validate (bytestream &f) {
	bool isGood = false;
	//size_t pos = f.tell();
	if (8160 <= f.size) {
		isGood = true;
		}
	return isGood;
	}

bool fmtESL::read_esl (bytestream &f) {
	bool sucess = false;
	if (validate(f)) {
		unsigned int spawn_count = 255;
		for (unsigned int i = 0; i < spawn_count; i++) {
			spawn[i].read_esl_spawn(f);
			}
		sucess = true;
		}
	return sucess;
	}

void fmtESL::write_esl (bytestream &s) {
	unsigned int spawn_count = 255;
	for (unsigned int i = 0; i < spawn_count; i++) {
		spawn[i].write_esl_spawn(s);
		}
	}
