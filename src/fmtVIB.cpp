#include "fmtVIB.h"


fmtVIB_Rumble::fmtVIB_Rumble () {
	start_frame_pos = 0;
	end_frame_pos = 0;
	start_vib_level = 0;
	end_vib_level = 0;
	}

void fmtVIB_Rumble::read_vib_rumble (bytestream &f) {
	start_frame_pos = f.readUlong();
	end_frame_pos = f.readUshort();
	start_vib_level = f.readUbyte();
	end_vib_level = f.readUbyte();
	}

void fmtVIB_Rumble::write_vib_rumble (bytestream &s) {
	s.writeUlong(start_frame_pos);
	s.writeUshort(end_frame_pos);
	s.writeUbyte(start_vib_level);
	s.writeUbyte(end_vib_level);
	}

fmtVIB_Entry::fmtVIB_Entry () {
	count = 0;
	}

void fmtVIB_Entry::read_vib_entry (bytestream &f) {
	count = f.readUlong();
	if (count > 0) {
		rumbles = std::vector<fmtVIB_Rumble>(count);
		for (unsigned int i = 0; i < count; i++) {
			rumbles[i].read_vib_rumble(f);
			}
		}
	}

void fmtVIB_Entry::write_vib_entry (bytestream &s) {
	s.writeUlong(count);
	for (unsigned int i = 0; i < count; i++) {
		rumbles[i].write_vib_rumble(s);
		}
	}

fmtVIB::fmtVIB () {
	count = 64;
	}

void fmtVIB::read_vib (bytestream &f) {
	size_t pos = f.tell();

	count = f.readUlong();
	if (count > 0) {

		addrs = std::vector<uint32_t>(count);
		for (unsigned int i = 0; i < count; i++) {
			addrs[i] = f.readUlong();
			}

		vib_layout = std::vector<fmtVIB_Entry>(count);
		for (unsigned int i = 0; i < count; i++) {
			if (addrs[i] > (pos + 4)) {
				f.seek(pos + addrs[i]);
				vib_layout[i].read_vib_entry(f);
				}
			}
		}
	}

void fmtVIB::write_vib (bytestream &s) {
	size_t ptr = 4;
	uint32_t addr = 0;

	s.writeUlong(count);
	if (count > 0) {
		ptr += count * 4;
		for (unsigned int i = 0; i < count; i++) {
			addr = 0;
			if (i < vib_layout.size()) {
				if (vib_layout[i].rumbles.size() > 0) {
					addr = ptr;
					ptr += (vib_layout[i].rumbles.size() * 8) + 4;
					}
				}
			s.writeUlong(addr);
			}
		for (unsigned int i = 0; i < count; i++) {
			if (i < vib_layout.size()) {
				if (vib_layout[i].rumbles.size() > 0) {
					vib_layout[i].write_vib_entry(s);
					}
				}
			}
		}
	unsigned int pad = (32-((s.tell()) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writeUbyte(0xCD);} // pad to 32
	}

