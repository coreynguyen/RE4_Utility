#include "fmtATARI.h"


fmtATARI::fmtATARI () {
	unk1 = 0;
	unk2 = 0;
	unk3 = 0;
	unk4 = 0;
	unk5 = 1;
	type = 1;
	unk7 = 0;
	unk8 = 0;
	pos_z = 0.0;
	height = 1000.0f;
	radius = 1000.0f;
	pos[0] = -1000.0;
	pos[1] = -1000.0;
	pos[2] = 1000.0;
	pos[3] = -1000.0;
	pos[4] = 1000.0;
	pos[5] = 1000.0;
	pos[6] = 1000.0;
	pos[7] = -1000.0;
	}

void fmtATARI::clear () {
	unk1 = 0;
	unk2 = 0;
	unk3 = 0;
	unk4 = 0;
	unk5 = 1;
	type = 1;
	unk7 = 0;
	unk8 = 0;
	pos_z = 0.0;
	height = 1000.0f;
	radius = 1000.0f;
	pos[0] = -1000.0;
	pos[1] = -1000.0;
	pos[2] = 1000.0;
	pos[3] = -1000.0;
	pos[4] = 1000.0;
	pos[5] = 1000.0;
	pos[6] = 1000.0;
	pos[7] = -1000.0;
	}

void fmtATARI::read_area (bytestream &f) {
	unk1 = f.readUbyte();
	unk2 = f.readUbyte();
	unk3 = f.readUbyte();
	unk4 = f.readUbyte();
	unk5 = f.readUbyte();
	type = f.readUbyte();
	unk7 = f.readUbyte();
	unk8 = f.readUbyte();
	pos_z = f.readfloat();
	height = f.readfloat();
	radius = f.readfloat();
	pos[0] = f.readfloat(); // on cylinder CONE ANG
	pos[1] = f.readfloat();
	pos[2] = f.readfloat();
	pos[3] = f.readfloat(); // on cylinder OPEN ANG
	pos[4] = f.readfloat();
	pos[5] = f.readfloat();
	pos[6] = f.readfloat();
	pos[7] = f.readfloat();
	}

void fmtATARI::write_area (bytestream &s) {
	s.writebyte(unk1);
	s.writebyte(unk2);
	s.writebyte(unk3);
	s.writebyte(unk4);
	s.writebyte(unk5);
	s.writebyte(type);
	s.writebyte(unk7);
	s.writebyte(unk8);
	s.writefloat(pos_z);
	s.writefloat(height);
	s.writefloat(radius);
	for (unsigned int i = 0; i < 8; i++) {
		s.writefloat(pos[i]);
		}
	}

void fmtATARI::write_ini () {
	ini->separator("Location");
	ini->fraction("wall_height", height);
	ini->fraction("plane_y_pos", pos_z);
	ini->fraction("sphere_radius", radius);
	ini->vector2("corner0_pos", pos[0], pos[1], false);
	ini->vector2("corner1_pos", pos[2], pos[3], false);
	ini->vector2("corner2_pos", pos[4], pos[5], false);
	ini->vector2("corner3_pos", pos[6], pos[7], false);
	}

void fmtATARI::read_ini (std::string &secname) {
	height = ini->get_fraction(secname, "wall_height");
	pos_z = ini->get_fraction(secname, "plane_y_pos");
	radius = ini->get_fraction(secname, "sphere_radius");

	ini->get_vector2(secname, "corner0_pos", pos[0], pos[1]);
	ini->get_vector2(secname, "corner1_pos", pos[2], pos[3]);
	ini->get_vector2(secname, "corner2_pos", pos[4], pos[5]);
	ini->get_vector2(secname, "corner3_pos", pos[6], pos[7]);
	}
