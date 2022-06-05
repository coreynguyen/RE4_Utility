#include "fmtETS.h"


fmtETS_Entry::fmtETS_Entry () {
	model_id = 0;
	index = 0;
	scale[0] = 1.0;
	scale[1] = 1.0;
	scale[2] = 1.0;
	rotation[0] = 0.0;
	rotation[1] = 0.0;
	rotation[2] = 0.0;
	position[0] = 0.0;
	position[1] = 0.0;
	position[2] = 0.0;
	}

void fmtETS_Entry::read_ets_entry (bytestream &f, bool re4_2007) {
	if (!re4_2007) { // 40 bytes
		model_id = f.readUshort();
		index = f.readUshort();
		scale[0] = f.readfloat();
		scale[1] = f.readfloat();
		scale[2] = f.readfloat();
		rotation[0] = f.readfloat();
		rotation[1] = f.readfloat();
		rotation[2] = f.readfloat();
		position[0] = f.readfloat();
		position[1] = f.readfloat();
		position[2] = f.readfloat();
		}
	else { // 64 bytes
		scale[0] = f.readfloat();
		scale[1] = f.readfloat();
		scale[2] = f.readfloat();
		f.seek(4, seek::cur);
		rotation[0] = f.readfloat();
		rotation[1] = f.readfloat();
		rotation[2] = f.readfloat();
		f.seek(4, seek::cur);
		position[0] = f.readfloat();
		position[1] = f.readfloat();
		position[2] = f.readfloat();
		f.seek(4, seek::cur);
		model_id = f.readUshort();
		index = f.readUshort();
		f.seek(12, seek::cur);
		}
	}

void fmtETS_Entry::write_ets_entry (bytestream &s, bool re4_2007) {
	if (!re4_2007) {
		s.writeshort(model_id);
		s.writeshort(index);
		s.writefloat(scale[0]);
		s.writefloat(scale[1]);
		s.writefloat(scale[2]);
		s.writefloat(rotation[0]);
		s.writefloat(rotation[1]);
		s.writefloat(rotation[2]);
		s.writefloat(position[0]);
		s.writefloat(position[1]);
		s.writefloat(position[2]);
		}
	else {
		s.writefloat(scale[0]);
		s.writefloat(scale[1]);
		s.writefloat(scale[2]);
		s.writelong(0);
		s.writefloat(rotation[0]);
		s.writefloat(rotation[1]);
		s.writefloat(rotation[2]);
		s.writelong(0);
		s.writefloat(position[0]);
		s.writefloat(position[1]);
		s.writefloat(position[2]);
		s.writelong(0);
		s.writeshort(model_id);
		s.writeshort(index);
		s.writelong(0);
		s.writelong(0);
		s.writelong(0);
		}
	}

size_t fmtETS_Entry::size (bool re4_2007) {
	size_t nsize = 40;
	if (re4_2007) {nsize = 64;}
	return nsize;
	}



fmtETS::fmtETS () {
	count = 0;
	unk01 = 0;
	unk02 = 0;
	unk03 = 0;
	unk04 = 0;
	data.clear();
	}

bool fmtETS::validate (bytestream &f, bool &re4_2007) {
	// Set default state to fail
	bool isGood = false;

	// log starting position
	size_t pos = f.tell();

	// Check if (file is minimum size
	if (pos + 16 <= f.size) {

		// Read Count, use to determine endian
		unsigned int chk1 = f.readUshort();

		// Check count is valid
		if (chk1 >= 0x0100) {

			// Swap endian
			f.islilEndian = !f.islilEndian;

			// read count again
			f.seek(pos);
			chk1 = f.readUshort();
			}

		// Check file is not empty
		if (chk1 > 0) {

			// Checking padding in header
			f.seek(pos + 2);
			unsigned int chk2 = f.readUshort();
			unsigned int chk3 = f.readUlong();
			unsigned int chk4 = f.readUlong();
			unsigned int chk5 = f.readUlong();

			if (chk2 == 0 && chk3 == 0 && chk4 == 0 && chk5 == 0) {

				// check that the count does not cause an overrun
				if (pos + (chk1 * 40) <= f.size) {

					// chage state to pass, theres nothing left to check
					isGood = true;

					// check if (file is from re4 2007
					re4_2007 = false; // set default state to false

					if (pos + 144 <= f.size) {

						// Check padding regions
						f.seek(pos + 28);
						chk2 = f.readUlong();
						f.seek(pos + 44);
						chk3 = f.readUlong();
						f.seek(pos + 60);
						chk4 = f.readUlong();
						f.seek(pos + 132);
						chk5 = f.readUlong();
						unsigned int chk6 = f.readUlong();
						unsigned int chk7 = f.readUlong();
						if (chk2 == 0 && chk3 == 0 && chk4 == 0 && chk5 == 0 && chk6 == 0 && chk7 == 0) {

							// chk for overrun
							if (pos + 16 + (chk1 * 64) <= f.size) {

								// probably RE4 2007
								re4_2007 = true;
								std::cout << "re4_2007: true\n";
								}
							}
						}
					} else {std::cout << "ets table out of bounds\n";}
				} else {std::cout << "ets signature fail\n";}
			} else {std::cout << "ets is empty\n";}
		} else {std::cout << "filesize invalid\n";}
	f.seek(pos);
	return isGood;
	}

void fmtETS::read_ets (bytestream &f) {
	//size_t pos = f.tell();
	bool re4_2007 = false;
	if (validate(f, re4_2007)) {
		count = f.readUshort();
		unk01 = f.readUshort();
		unk02 = f.readUlong();
		unk03 = f.readUlong();
		unk04 = f.readUlong();
		if (count > 0) {
			data = std::vector<fmtETS_Entry>(count);
			for (unsigned int i = 0; i < count; i++) {
				data.at(i).read_ets_entry(f, re4_2007);
				}
			}
		} else {std::cout << "invalid ETS file: \t" << f.file << "\n\n";}
	}

void fmtETS::write_ets (bytestream &s, bool re4_2007) {
	s.writeshort(count = data.size());
	s.writeshort(unk01);
	s.writelong(unk02);
	s.writelong(unk03);
	s.writelong(unk04);

	for (unsigned int i = 0; i < count; i++) {
		data.at(i).write_ets_entry(s, re4_2007);
		}
	unsigned int pad = (32-(s.tell() % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0xCD);} // pad to 32
	}

size_t fmtETS::size (bool re4_2007) {
	size_t nsize = 16 + (data.size() * 40);
	if (re4_2007) {nsize = 16 + (data.size() * 64);}
	return (nsize + (32-(nsize % 32)) % 32);
	}

