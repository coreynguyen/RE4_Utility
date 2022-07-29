#include "fmtBLK.h"



fmtBLK_Connect::fmtBLK_Connect () {
	flag = 1;
	unk1 = 0;
	unk2 = 0;
	unk3 = 0;
	connect[0] = -1;
	connect[1] = -1;
	connect[2] = -1;
	connect[3] = -1;
	connect[4] = -1;
	connect[5] = -1;
	connect[6] = -1;
	connect[7] = -1;
	}

void fmtBLK_Connect::read_connect (bytestream &f) {
	flag = f.readbyte();
	unk1 = f.readbyte();
	unk2 = f.readbyte();
	unk3 = f.readbyte();
	connect[0] = f.readbyte();
	connect[1] = f.readbyte();
	connect[2] = f.readbyte();
	connect[3] = f.readbyte();
	connect[4] = f.readbyte();
	connect[5] = f.readbyte();
	connect[6] = f.readbyte();
	connect[7] = f.readbyte();
	}

void fmtBLK_Connect::write_connect (bytestream &s) {
	s.writebyte(flag);
	s.writebyte(unk1);
	s.writebyte(unk2);
	s.writebyte(unk3);
	s.writebyte(connect[0]);
	s.writebyte(connect[1]);
	s.writebyte(connect[2]);
	s.writebyte(connect[3]);
	s.writebyte(connect[4]);
	s.writebyte(connect[5]);
	s.writebyte(connect[6]);
	s.writebyte(connect[7]);
	}

fmtBLK_Area::fmtBLK_Area () {
	unk41 = 3;
	area_index = 0;
	area_no = 0;
	area_priority = 0;
	}

void fmtBLK_Area::read_area (bytestream &f) {
	area.read_area(f);
	unk41 = f.readUbyte();
	area_index = f.readUbyte();
	area_no = f.readUbyte();
	area_priority = f.readUbyte();
	}

void fmtBLK_Area::write_area (bytestream &s) {
	area.write_area(s);
	s.writebyte(unk41);
	s.writebyte(area_index);
	s.writebyte(area_no);
	s.writebyte(area_priority);
	}

fmtBLK_Link::fmtBLK_Link () {
	unk51 = 1;
	link_block = 0;
	unk53 = 0;
	unk54 = 0;
	load_blocks[0] = -1;
	load_blocks[1] = -1;
	load_blocks[2] = -1;
	load_blocks[3] = -1;
	load_blocks[4] = -1;
	load_blocks[5] = -1;
	load_blocks[6] = -1;
	load_blocks[7] = -1;
	unload_blocks[0] = -1;
	unload_blocks[1] = -1;
	unload_blocks[2] = -1;
	unload_blocks[3] = -1;
	unload_blocks[4] = -1;
	unload_blocks[5] = -1;
	unload_blocks[6] = -1;
	unload_blocks[7] = -1;
	}

void fmtBLK_Link::read_area_link (bytestream &f) {
	unk51 = f.readUbyte();
	link_block = f.readUbyte();
	unk53 = f.readUbyte();
	unk54 = f.readUbyte();
	for (unsigned int i = 0; i < 8; i++) {
		load_blocks[i] = f.readUbyte();
		}
	for (unsigned int i = 0; i < 8; i++) {
		unload_blocks[i] = f.readUbyte();
		}
	}

void fmtBLK_Link::write_area_link (bytestream &s) {
	s.writebyte(unk51);
	s.writebyte(link_block);
	s.writebyte(unk53);
	s.writebyte(unk54);
	for (unsigned int i = 0; i < 8; i++) {
		s.writebyte(load_blocks[i]);
		}
	for (unsigned int i = 0; i < 8; i++) {
		s.writebyte(unload_blocks[i]);
		}
	}

fmtBLK::fmtBLK () {
	fileid[0] = 0x42;
	fileid[1] = 0x4C;
	fileid[2] = 0x4B;
	fileid[3] = 0x00;
	version = 0x0100;
	block_count = 0;
	load_count = 0;
	link_count = 0;
	block_addr = 0;
	load_addr = 0;
	link_addr = 0;
	}

size_t fmtBLK::size () {
	size_t nsize = 24 + (block.size() * 12) + (load.size() * 56) + (link.size() * 20);
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

bool fmtBLK::validate (bytestream &f, size_t fsize, bool verbose) {
	/*
		Verifies the file is of the correct type and will set the endian accordingly
	*/

	// if (Data Size is not provided; assume it is the entire file buffer
	if (fsize == 0) {
		fsize = f.size;
		}

	// Get Start Position; return at the end
	size_t pos = f.tell();

	// Set Default Pass State to Fail
	bool isGood = false;

	// Check there is enough room to do the check
	if (f.tell() + 24 < fsize) {

		// Read for Known File ID 'BLK'
		unsigned int chk1 = f.readUbyte();
		unsigned int chk2 = f.readUbyte();
		unsigned int chk3 = f.readUbyte();
		unsigned int chk4 = f.readUbyte();

		if (chk1 == 0x42 && chk2 == 0x4C && chk3 == 0x4B && chk4 == 0x00) {

			// Check Version
			unsigned int chk5 = f.readUshort();
			if (chk5 == 0x0001 || chk5 == 0x0100) {

				// Correct for Endian
				if (chk5 == 0x0001) {

					// Switch Endian
					f.islilEndian = !f.islilEndian;

					}

				// Read Counts
				unsigned int chk6 = f.readUshort();
				unsigned int chk7 = f.readUshort();
				unsigned int chk8 = f.readUshort();

				// Calculate File Size
				unsigned int chk9 = 24 + (chk6 * 12) + (chk7 * 56) + (chk8 * 20);
				if (pos + chk9 <= fsize) {

					/*
						I could do an additional check on the first table;
						if (there are entries then the first long is always 1
					*/

					// Change Pass State to Good
					isGood = true;
					}

				} else {if (verbose) {std::cout << "Invalid Version [" << chk5 << "]\n";}}

			} else {if (verbose) {std::cout << "Invalid FileID [" << chk1 << chk2 << chk3 << chk4 << "]\n";}}

		} else {if (verbose) {std::cout << "Invalid FileSize\n";}}

	f.seek(pos);
	return isGood;
	}

void fmtBLK::read_blk (bytestream &f) {


	if (validate(f)) {

		size_t pos = f.tell();

		// File Info
		fileid[0] = f.readUbyte();
		fileid[1] = f.readUbyte();
		fileid[2] = f.readUbyte();
		fileid[3] = f.readUbyte();
		version = f.readUshort();

		// Array Counts
		block_count = f.readUshort();
		load_count = f.readUshort();
		link_count = f.readUshort();

		// Data Addresses
		block_addr = f.readUlong();
		load_addr = f.readUlong();
		link_addr = f.readUlong();

		// Tables
		block.clear();
		if (block_count > 0) {

			block = std::vector<fmtBLK_Connect>(block_count);

			f.seek(pos + block_addr);

			for (unsigned int i = 0; i < block_count; i++) {
				block[i].read_connect(f);
				}
			}

		load.clear();
		if (load_count > 0) {

			load = std::vector<fmtBLK_Area>(load_count);
			f.seek(pos + load_addr);

			for (unsigned int i = 0; i < load_count; i++) {
				load[i].read_area(f);
				}
			}

		link.clear();
		if (link_count > 0) {

			link = std::vector<fmtBLK_Link>(link_count);

			f.seek(pos + link_addr);

			for (unsigned int i = 0; i < link_count; i++) {
				link[i].read_area_link(f);
				}
			}

		} else {std::cout << "Error:\n\tBLK File Failed Validation: {" << f.file << "}\n";}
	}

void fmtBLK::write_blk (bytestream &s) {

	s.writebyte(0x42);
	s.writebyte(0x4C);
	s.writebyte(0x4B);
	s.writebyte(0x00);
	s.writeshort(0x0100);

	s.writeshort(block_count = block.size());
	s.writeshort(load_count = load.size());
	s.writeshort(link_count = link.size());

	size_t ptr = 24;
	s.writelong(block_addr = ptr);
	ptr += block_count * 12;

	s.writelong(load_addr = ptr);
	ptr += load_count * 56;

	s.writelong(link_addr = ptr);
	ptr += link_count * 20;

	unsigned int pad = (32-(ptr % 32)) % 32;

	for (unsigned int i = 0; i < block_count; i++) {
		block[i].write_connect(s);
		}
	for (unsigned int i = 0; i < load_count; i++) {
		load[i].write_area(s);
		}
	for (unsigned int i = 0; i < link_count; i++) {
		link[i].write_area_link(s);
		}
	for (unsigned int i = 0; i < pad; i++) { // pad to 32
		s.writebyte(0xCD);
		}
	}

void fmtBLK::open (std::wstring file) {
	bytestream f;
	if (f.openFileW(file)) {

		read_blk(f);

		f.close();

		}
	else {std::cout << "error failed to open file\n";}
	}


void fmtBLK::save (std::wstring file) {
	bytestream s;
	if (s.openFileW(file)) {

		s.resize(size());

		write_blk(s);

		s.close();
		}
	else {std::cout << "error failed to save file\n";}
	}

