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
		load_blocks[i] = f.readbyte();
		}
	for (unsigned int i = 0; i < 8; i++) {
		unload_blocks[i] = f.readbyte();
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

	block_count = (uint16_t)block.size();
	load_count = (uint16_t)load.size();
	link_count = (uint16_t)link.size();
	s.writeshort(block_count);
	s.writeshort(load_count);
	s.writeshort(link_count);

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


void fmtBLK::xml_export (std::wstring file, std::wstring internalname) {
	/* copies the variables into an XML text */

	std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

	unsigned int block_count = block.size();
	unsigned int link_count = link.size();
	std::string rootname;
	if (internalname != L"") {rootname = wstring_to_string(internalname);}
	else {rootname = wstring_to_string(getFilenameFileW(file));}

	// XML Root Node
	xml += "<blk name=\"" + rootname + ".blk\" count=\"" + to_string(block_count) + "\">\n";
	xml += "    <!-- positional units are millimeters and angles are radians -->\n";


	std::stringstream ss;
	std::string state = "FALSE";
	std::string model = "";
	std::string stridx;
	if (block_count > 0) {
		xml += "    <blocks count=\"" + to_string(block_count) + "\">\n";
		xml += "        <!-- Maximum of 64 Entries -->\n";
		for (unsigned int i = 0; i < block_count; i++) {
			xml += "        <entry index=\"" + to_string(i) + "\">\n";
			ss.str(std::string()); ss << std::uppercase << TO_HEX(i, false, 2);
			xml += "            <!-- " + rootname + "_" + padString(ss.str(), 2, "0") + ".dat -->\n";
			xml += "            <flag>" + to_string((int)block[i].flag) + "</flag>\n";
			xml += "            <unk1>" + to_string((int)block[i].unk1) + "</unk1>\n";
			xml += "            <unk2>" + to_string((int)block[i].unk2) + "</unk2>\n";
			xml += "            <unk3>" + to_string((int)block[i].unk3) + "</unk3>\n";
			xml += "            <connections count=\"8\">\n";
			xml += "                <!-- Maximum of 8 Entries -->\n";
			for (unsigned int b = 0; b < 8; b++) {
				stridx = to_string(b + 1);
				xml += "                <block" + stridx + ">" + to_string(block[i].connect[b]) + "</block" + stridx + ">\n";
				}
			xml += "            </connections>\n";
			xml += "        </entry>\n";
			}
		xml += "    </blocks>\n";
		}
	if (link_count > 0) {
		/*
			the links require a trigger area, therefore the trigger area count
			and link count should be the same.

			however the way the file is written, its possible to have more
			trigger areas defined then links.

			I don't bother error handling this, so i assume this is always the case
		*/

		xml += "    <links count=\"" + to_string(link_count) + "\">\n";
		for (unsigned int i = 0; i < link_count; i++) {

			xml += "        <entry index=\"" + to_string(i) + "\">\n";
			xml += "            <block>" + to_string((int)link[i].link_block) + "</block>\n";
			xml += "            <flag>" + to_string((int)link[i].unk51) + "</flag>\n";
			xml += "            <unk53>" + to_string((int)link[i].unk53) + "</unk53>\n";
			xml += "            <unk54>" + to_string((int)link[i].unk54) + "</unk54>\n";
			xml += "            <load count=\"8\">\n";
			xml += "                <!-- Maximum of 8 Blocks -->\n";
			for (unsigned int b = 0; b < 8; b++) {
				stridx = to_string(b + 1);
				xml += "                <block" + stridx + ">" + to_string((int)link[i].load_blocks[b]) + "</block" + stridx + ">\n";
				}
			xml += "            </load>\n";
			xml += "            <unload count=\"8\">\n";
			xml += "                <!-- Maximum of 8 Blocks -->\n";
			for (unsigned int b = 0; b < 8; b++) {
				stridx = to_string(b + 1);
				xml += "                <block" + stridx + ">" + to_string((int)link[i].unload_blocks[b]) + "</block" + stridx + ">\n";
				}
			xml += "            </unload>\n";

			// Locate the Area from Index
			/*
				I may have area_index and area_no confused, if there is a problem
				with the wrong trigger area loading, then swap them down below

			*/
			unsigned int area_count = load.size();
			unsigned int num_areas = 0;
			for (unsigned int x = 0; x < area_count; x++) {
				if (load[x].area_no == i) {
					num_areas++;
					}
				}
			if (num_areas > 0) {
				xml += "            <areas count=\"" + to_string(num_areas) + "\">\n";

				for (unsigned int x = 0; x < area_count; x++) {

					// check if area no matches current link index
					if (load[x].area_no == i) {
						// assign area index to x, and exit

						xml += "                <atari index=\"" + to_string(num_areas) + "\">\n";
						xml += "                    <flag>" + to_string((int)load[x].unk41) + "</flag>\n";
						xml += "                    <index>" + to_string((int)load[x].area_index) + "</index>\n";
						xml += "                    <priority>" + to_string((int)load[x].area_priority) + "</priority>\n";
						// stuff from the atari struct
						xml += "                    <hasData>" + to_string((int)load[x].area.unk1) + "</hasData>\n";
						xml += "                    <useData>" + to_string((int)load[x].area.unk2) + "</useData>\n";
						xml += "                    <player>" + to_string((int)load[x].area.unk3) + "</player>\n";
						xml += "                    <enemy>" + to_string((int)load[x].area.unk4) + "</enemy>\n";
						xml += "                    <unk5>" + to_string((int)load[x].area.unk5) + "</unk5>\n";
						xml += "                    <shape>" + to_string((int)load[x].area.type) + "</shape>\n";
						xml += "                    <!--ENUM: shape\n";
						xml += "                           0: None\n";
						xml += "                           1: BOX\n";
						xml += "                           2: CIRCLE\n";
						xml += "                           3: SPHERE\n";
						xml += "                    -->\n";
						xml += "                    <unk7>" + to_string((int)load[x].area.unk7) + "</unk7>\n";
						xml += "                    <unk8>" + to_string((int)load[x].area.unk8) + "</unk8>\n";
						xml += "                    <pos_z>" + to_string(load[x].area.pos_z) + "</pos_z>\n";
						xml += "                    <height>" + to_string(load[x].area.height) + "</height>\n";
						xml += "                    <radius>" + to_string(load[x].area.radius) + "</radius>\n";
						xml += "                    <pos0_x>" + to_string(load[x].area.pos[0]) + "</pos0_x>\n";
						xml += "                    <pos0_y>" + to_string(load[x].area.pos[1]) + ".1</pos0_y>\n";
						xml += "                    <pos1_x>" + to_string(load[x].area.pos[2]) + "</pos1_x>\n";
						xml += "                    <pos1_y>" + to_string(load[x].area.pos[3]) + "</pos1_y>\n";
						xml += "                    <pos2_x>" + to_string(load[x].area.pos[4]) + "</pos2_x>\n";
						xml += "                    <pos2_y>" + to_string(load[x].area.pos[5]) + "</pos2_y>\n";
						xml += "                    <pos3_x>" + to_string(load[x].area.pos[6]) + "</pos3_x>\n";
						xml += "                    <pos3_y>" + to_string(load[x].area.pos[7]) + "</pos3_y>\n";
						xml += "                </atari>\n";
						num_areas++;
						}
					}
				xml += "            </areas>\n";
				}

			// if trigger area index is valid, write entry

			xml += "        </entry>\n";

			}
		xml += "    </links>\n";
		}



	// Close XML Root Node
	xml += "</blk>\n";

	// Save File
	bytestream s;
	s.writeFileW(file, 0, xml.size(), (char*)xml.c_str());

	}

void fmtBLK::xml_import (rapidxml::xml_document<> &doc) {


	// Check Root Node
	rapidxml::xml_node<>* NODE_BLK = doc.first_node("blk");
	if (NODE_BLK == NULL) {return;}

	rapidxml::xml_node<>* NODE_ITEM;
	std::string str;

	// Check for Block Node
	rapidxml::xml_node<>* BLOC_NODE = NODE_BLK->first_node("blocks");
	if (BLOC_NODE != NULL) {

		// Clear Array
		block.clear();

		// Count Number of Blocks (*.dat) files
		int BLOC_NUM = 0;
		for (rapidxml::xml_node<>* NODE_ENTRY = BLOC_NODE->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {BLOC_NUM++;}
		if (BLOC_NUM > 0) {

			// Dimension Array
			block = std::vector<fmtBLK_Connect>(BLOC_NUM);
			int BLOC_INDEX = 0;
			rapidxml::xml_node<>* NODE_CONN;
			for (rapidxml::xml_node<>* NODE_ENTRY = BLOC_NODE->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
				if ((NODE_ITEM = NODE_ENTRY->first_node("flag")) != NULL) {
					block[BLOC_INDEX].flag = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));
					}
				if ((NODE_ITEM = NODE_ENTRY->first_node("unk1")) != NULL) {
					block[BLOC_INDEX].unk1 = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));
					}
				if ((NODE_ITEM = NODE_ENTRY->first_node("unk2")) != NULL) {
					block[BLOC_INDEX].unk2 = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));
					}
				if ((NODE_ITEM = NODE_ENTRY->first_node("unk3")) != NULL) {
					block[BLOC_INDEX].unk3 = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));
					}
				if ((NODE_ITEM = NODE_ENTRY->first_node("connections")) != NULL) {
					if ((NODE_CONN = NODE_ITEM->first_node("block1")) != NULL) {
						block[BLOC_INDEX].connect[0] = (int8_t)(convert_to<int>(std::string(NODE_CONN->value())));
						}
					if ((NODE_CONN = NODE_ITEM->first_node("block2")) != NULL) {
						block[BLOC_INDEX].connect[1] = (int8_t)(convert_to<int>(std::string(NODE_CONN->value())));
						}
					if ((NODE_CONN = NODE_ITEM->first_node("block3")) != NULL) {
						block[BLOC_INDEX].connect[2] = (int8_t)(convert_to<int>(std::string(NODE_CONN->value())));
						}
					if ((NODE_CONN = NODE_ITEM->first_node("block4")) != NULL) {
						block[BLOC_INDEX].connect[3] = (int8_t)(convert_to<int>(std::string(NODE_CONN->value())));
						}
					if ((NODE_CONN = NODE_ITEM->first_node("block5")) != NULL) {
						block[BLOC_INDEX].connect[4] = (int8_t)(convert_to<int>(std::string(NODE_CONN->value())));
						}
					if ((NODE_CONN = NODE_ITEM->first_node("block6")) != NULL) {
						block[BLOC_INDEX].connect[5] = (int8_t)(convert_to<int>(std::string(NODE_CONN->value())));
						}
					if ((NODE_CONN = NODE_ITEM->first_node("block7")) != NULL) {
						block[BLOC_INDEX].connect[6] = (int8_t)(convert_to<int>(std::string(NODE_CONN->value())));
						}
					if ((NODE_CONN = NODE_ITEM->first_node("block8")) != NULL) {
						block[BLOC_INDEX].connect[7] = (int8_t)(convert_to<int>(std::string(NODE_CONN->value())));
						}
					}
				BLOC_INDEX++;
				}
			}
		}

	// Check for Link Node
	rapidxml::xml_node<>* LINK_NODE = NODE_BLK->first_node("links");

	if (LINK_NODE != NULL) {

		// Clear Arrays
		link.clear();
		load.clear();

		// Count Number of Links
		int AREA_NUM = 0;
		int LINK_NUM = 0;
		rapidxml::xml_node<>* NODE_AREA;
		rapidxml::xml_node<>* AREA_ENTRY;
		for (rapidxml::xml_node<>* NODE_ENTRY = LINK_NODE->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
			LINK_NUM++;
			if ((NODE_AREA = NODE_ENTRY->first_node("areas")) != NULL) {
				for (rapidxml::xml_node<>* NODE_ATARI = NODE_AREA->first_node("atari"); NODE_ATARI; NODE_ATARI = NODE_ATARI->next_sibling()) {
					AREA_NUM++;
					}
				}
			}
		if (LINK_NUM > 0) {

			// Dimension Array
			link = std::vector<fmtBLK_Link>(LINK_NUM);
			if (AREA_NUM > 0) {load = std::vector<fmtBLK_Area>(AREA_NUM);}
			int LINK_INDEX = 0;
			int AREA_INDEX = 0;
			rapidxml::xml_node<>* NODE_BLOC;
			for (rapidxml::xml_node<>* NODE_ENTRY = LINK_NODE->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
				if ((NODE_AREA = NODE_ENTRY->first_node("block")) != NULL) {
					link[LINK_INDEX].link_block = (uint8_t)(convert_to<int>(std::string(NODE_AREA->value())));
					}
				if ((NODE_AREA = NODE_ENTRY->first_node("flag")) != NULL) {
					link[LINK_INDEX].unk51 = (uint8_t)(convert_to<int>(std::string(NODE_AREA->value())));
					}
				if ((NODE_AREA = NODE_ENTRY->first_node("unk53")) != NULL) {
					link[LINK_INDEX].unk53 = (uint8_t)(convert_to<int>(std::string(NODE_AREA->value())));
					}
				if ((NODE_AREA = NODE_ENTRY->first_node("unk54")) != NULL) {
					link[LINK_INDEX].unk54 = (uint8_t)(convert_to<int>(std::string(NODE_AREA->value())));
					}
				if ((NODE_AREA = NODE_ENTRY->first_node("load")) != NULL) {
					for (rapidxml::xml_node<>* NODE_ATARI = NODE_AREA->first_node("atari"); NODE_ATARI; NODE_ATARI = NODE_ATARI->next_sibling()) {
						if ((NODE_BLOC = NODE_ATARI->first_node("block1")) != NULL) {
							link[LINK_INDEX].load_blocks[0] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block2")) != NULL) {
							link[LINK_INDEX].load_blocks[1] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block3")) != NULL) {
							link[LINK_INDEX].load_blocks[2] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block4")) != NULL) {
							link[LINK_INDEX].load_blocks[3] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block5")) != NULL) {
							link[LINK_INDEX].load_blocks[4] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block6")) != NULL) {
							link[LINK_INDEX].load_blocks[5] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block7")) != NULL) {
							link[LINK_INDEX].load_blocks[6] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block8")) != NULL) {
							link[LINK_INDEX].load_blocks[7] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						}
					}
				if ((NODE_AREA = NODE_ENTRY->first_node("unload")) != NULL) {
					for (rapidxml::xml_node<>* NODE_ATARI = NODE_AREA->first_node("atari"); NODE_ATARI; NODE_ATARI = NODE_ATARI->next_sibling()) {
						if ((NODE_BLOC = NODE_ATARI->first_node("block1")) != NULL) {
							link[LINK_INDEX].unload_blocks[0] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block2")) != NULL) {
							link[LINK_INDEX].unload_blocks[1] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block3")) != NULL) {
							link[LINK_INDEX].unload_blocks[2] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block4")) != NULL) {
							link[LINK_INDEX].unload_blocks[3] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block5")) != NULL) {
							link[LINK_INDEX].unload_blocks[4] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block6")) != NULL) {
							link[LINK_INDEX].unload_blocks[5] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block7")) != NULL) {
							link[LINK_INDEX].unload_blocks[6] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						else if ((NODE_BLOC = NODE_ATARI->first_node("block8")) != NULL) {
							link[LINK_INDEX].unload_blocks[7] = (int8_t)(convert_to<int>(std::string(NODE_BLOC->value())));
							}
						}
					}
				if ((NODE_AREA = NODE_ENTRY->first_node("areas")) != NULL) {
					for (rapidxml::xml_node<>* NODE_ATARI = NODE_AREA->first_node("atari"); NODE_ATARI; NODE_ATARI = NODE_ATARI->next_sibling()) {
						if ((AREA_ENTRY = NODE_ATARI->first_node("hasData")) != NULL) {load[AREA_INDEX].area.unk1 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("useData")) != NULL) {load[AREA_INDEX].area.unk2 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("player")) != NULL) {load[AREA_INDEX].area.unk3 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("enemy")) != NULL) {load[AREA_INDEX].area.unk4 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("unk5")) != NULL) {load[AREA_INDEX].area.unk5 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("shape")) != NULL) {load[AREA_INDEX].area.type = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("unk7")) != NULL) {load[AREA_INDEX].area.unk7 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("unk8")) != NULL) {load[AREA_INDEX].area.unk8 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos_z")) != NULL) {load[AREA_INDEX].area.pos_z = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("height")) != NULL) {load[AREA_INDEX].area.height = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("radius")) != NULL) {load[AREA_INDEX].area.radius = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos0_x")) != NULL) {load[AREA_INDEX].area.pos[0] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos0_y")) != NULL) {load[AREA_INDEX].area.pos[1] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos1_x")) != NULL) {load[AREA_INDEX].area.pos[2] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos1_y")) != NULL) {load[AREA_INDEX].area.pos[3] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos2_x")) != NULL) {load[AREA_INDEX].area.pos[4] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos2_y")) != NULL) {load[AREA_INDEX].area.pos[5] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos3_x")) != NULL) {load[AREA_INDEX].area.pos[6] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("pos3_y")) != NULL) {load[AREA_INDEX].area.pos[7] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("flag")) != NULL) {load[AREA_INDEX].unk41 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("index")) != NULL) {load[AREA_INDEX].area_index = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						if ((AREA_ENTRY = NODE_ATARI->first_node("priority")) != NULL) {load[AREA_INDEX].area_priority = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
						load[AREA_INDEX].area_no = LINK_INDEX;
						AREA_INDEX++;
						}
					}
				LINK_INDEX++;
				}
			}
		}
	}


