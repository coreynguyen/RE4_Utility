#include "fmtDSE.h"

fmtDSE_Entry::fmtDSE_Entry () {
	room_id = 0;
	door_se_id = 0;
	unk03 = -1;
	unk04 = -1;
	unk05 = -1;
	unk06 = -1;
	}

void fmtDSE_Entry::read_dse_entry (bytestream &f) {
	room_id = f.readUshort();
	door_se_id = f.readUshort();
	unk03 = f.readshort();
	unk04 = f.readshort();
	unk05 = f.readshort();
	unk06 = f.readshort();
	}

void fmtDSE_Entry::write_dse_entry (bytestream &s) {
	s.writeUshort(room_id);
	s.writeUshort(door_se_id);
	s.writeshort(unk03);
	s.writeshort(unk04);
	s.writeshort(unk05);
	s.writeshort(unk06);
	}

fmtDSE::fmtDSE () {
	count = 0;
	data.clear();
	}

void fmtDSE::read_dse (bytestream &f) {
	count = f.readUlong();
	if (count > 0 ) {
		data = std::vector<fmtDSE_Entry> (count);
		for (unsigned int i = 0; i < count; i++) {
			data[i].read_dse_entry(f);
			}
		}
	}

void fmtDSE::write_dse (bytestream &s) {
	s.writeUlong(data.size());
	for (unsigned int i = 0; i < count; i++) {
		data[i].write_dse_entry(s);
		}
	unsigned int pad = (32-((s.tell()) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) { // pad to 32
		s.writeUbyte(0xCD);
		}
	}

