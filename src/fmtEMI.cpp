#include "fmtEMI.h"


fmtEMI_Entry::fmtEMI_Entry () {
	work_type = 0;	// Work Type
	work0 = 0;
	work1 = 0;
	work2 = 0;
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;
	dir = 0.0f;
	for (unsigned int i = 0; i < 44; i++) {reserve[i] = 0;}
	}

void fmtEMI_Entry::read_emi_entry (bytestream &f) {
	work_type = f.readUbyte();
	work0 = f.readUbyte();
	work1 = f.readUbyte();
	work2 = f.readUbyte();
	position[0] = f.readfloat();
	position[1] = f.readfloat();
	position[2] = f.readfloat();
	dir = f.readfloat();
	for (unsigned int i = 0; i < 44; i++) {
		reserve[i] = f.readUbyte();
		}
	}

void fmtEMI_Entry::write_emi_entry (bytestream &s) {
	s.writeUbyte(work_type);
	s.writeUbyte(work0);
	s.writeUbyte(work1);
	s.writeUbyte(work2);
	s.writefloat(position[0]);
	s.writefloat(position[1]);
	s.writefloat(position[2]);
	s.writefloat(dir);
	for (unsigned int i = 0; i < 44; i++) {
		s.writeUbyte(reserve[i]);
		}
	}

fmtEMI::fmtEMI () {
	count = 0;
	unk01 = 0;
	data.clear();
	}

void fmtEMI::read_emi (bytestream &f) {
	count = f.readUlong();
	unk01 = f.readUlong();
	if (count > 0) {
		data = std::vector<fmtEMI_Entry>(count);
		for (unsigned int i = 0; i < count; i++) {
			data[i].read_emi_entry(f);
			}
		}
	}

void fmtEMI::write_emi (bytestream &s) {
	count = data.size();
	s.writeUlong(count);
	s.writeUlong(unk01);
	for (unsigned int i = 0; i < count; i++) {
		data[i].write_emi_entry(s);
		}
	unsigned int pad = (32-((s.tell()) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writeUbyte(0xCD);} // pad to 32
	}
