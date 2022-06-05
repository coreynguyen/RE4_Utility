#include "fmtEFF.h"

fmtEFF_Index::fmtEFF_Index () {
	id1 = id2 = id3 = id4 = 0;
	}

void fmtEFF_Index::read_index (bytestream &f) {
	id1 = f.readUshort();
	id2 = f.readUshort();
	id3 = f.readUshort();
	id4 = f.readUshort();
	}

void fmtEFF_Index::write_index (bytestream &s) {
	s.writeshort(id1);
	s.writeshort(id2);
	s.writeshort(id3);
	s.writeshort(id4);
	}

size_t fmtEFF_Index::size () {
	return 8;
	}

fmtEFF_Index_Table::fmtEFF_Index_Table () {
	count = 0;
	}

void fmtEFF_Index_Table::read_index_table (bytestream &f) {
	count = f.readUlong();
	index.clear();
	if (count > 0) {
		index = std::vector<fmtEFF_Index>(count);
		for (unsigned int i = 0; i < count; i++) {
			index[i].read_index(f);
			}
		}
	}

void fmtEFF_Index_Table::write_index_table (bytestream &s) {
	size_t pos = s.tell();
	count = index.size();
	s.writelong(count);
	for (unsigned int i = 0; i < count; i++) {
		index[i].write_index(s);
		}
	unsigned int pad = (32-((s.tell() - pos) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0);}
	}

size_t fmtEFF_Index_Table::size () {
	size_t nsize = 4 + (index.size() * 4);
	for (unsigned int i = 0; i < index.size(); i++) {
		nsize += index[i].size();
		}
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

fmtEFF_Pointer_Table::fmtEFF_Pointer_Table () {
	count = 0;
	}

void fmtEFF_Pointer_Table::read_pointer_table (bytestream &f) {
	count = f.readUlong();
	addr.clear();
	if (count > 0) {
		addr = std::vector<uint32_t>(count);
		for (unsigned int i = 0; i < count; i++) {
			addr.at(i) = f.readUlong();
			}
		}
	}

void fmtEFF_Pointer_Table::write_pointer_table (bytestream &s, uint32_t override_count) {
	size_t pos = s.tell();

	count = addr.size();

	if (override_count > 0) {
		count = override_count;
		}

	s.writelong(count);
	for (unsigned int i = 0; i < count; i++) {
		if (i < addr.size()) {
			s.writelong(addr[i]);
			}
		else {
			s.writelong(0);
			}
		}
	unsigned int pad = (32-((s.tell() - pos) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0);}
	}

size_t fmtEFF_Pointer_Table::size (uint32_t override_count) {
	size_t nsize = 4;
	if (override_count > 0) {
		nsize += override_count * 4;
		}
	else {
		nsize += addr.size() * 4;
		}
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

void fmtEFF_TPL_Table::read_tpl_table (bytestream &f, uint32_t header_pos, fmtEFF_Pointer_Table header_addrs, bool scan) {

	// Log Start Position
	size_t pos = f.tell();

	// Read Pointer Table
	table.read_pointer_table(f);

	if (table.count > 0) {
		scan = true;
		if (scan) {

			// Seek Past Padding
			f.seek((32-((f.tell() - pos) % 32)) % 32, 1);

			// Log Data Start Position
			size_t data_addr = f.tell() - pos;

			// Get the Smallest pointer
			size_t min_addr = data_addr;

			// Start off with the first pointer
			min_addr = table.addr[0];
			for (unsigned int i = 1; i < table.count; i++) {

				// Check if (next TPL pointer is smaller, log it if (it is
				if (table.addr[i] > 0 && table.addr[i] < min_addr) {
					min_addr = table.addr[i];
					}
				}

			// Check if (there is room between the end of the pointer table, && the first entry
			// if (this is a PC EFF then certainly there will be a massive pointer gap
			//std::cout << "TPL: \t" << pos << std::endl;
			if (min_addr > data_addr) {

				// Further check for a the smallest address but also include header addresses
				for (unsigned int i = 0; i < header_addrs.count; i++) {

					// only consider addresses that are beyond this block && are not Null
					if (header_addrs.addr[i] > 0 && header_pos + header_addrs.addr[i] > pos && header_pos + header_addrs.addr[i] - pos < min_addr) {

						// Check if (header pointer is smaller, log it if (it is
						min_addr = header_pos + header_addrs.addr[i] - pos;
						}
					}

				}
			//std::cout << "min_addr: \t" << min_addr << std::endl;

			}

		// Resume Normal Reading of the PACK TPL's

		tpl_pc = std::vector<fmtTPL>(table.count);
		for (unsigned int i = 0; i < table.count; i++) {


			// Check Pointer is not NULL
			if (table.addr[i] > 0 && pos + table.addr[i] + 12 < f.size) {

				// Read PACK TPL
				f.seek(pos + table.addr[i]);
				//format "TPL%: \t@ %\n" i {{pos + table.addr[i]} as integer}
				tpl_pc[i].read(f);
				} else {std::cout << "Error: \tTPL Pointer Out of Bounds: \t @ " << pos + table.addr[i] << " \t:: " << f.file << "\n";}
			}
		}
	}

void fmtEFF_TPL_Table::write_tpl_table (bytestream &s) {
	//table.count = tpl_pc.count;
	table.addr.clear();
	table.addr = std::vector<uint32_t>(table.count);

	size_t pos = s.tell();
	size_t ptr = 4 + (table.count * 4);
	ptr += (32-(ptr % 32)) % 32;
	for (unsigned int i = 0; i < table.count; i++) {
		table.addr[i] = ptr;
		//ptr += tpl_pc[i].size();
		ptr += (32-(ptr % 32)) % 32;
		}
	unsigned int pad;
	table.write_pointer_table(s);
	for (unsigned int i = 0; i < table.count; i++) {
		//tpl_pc[i].write(s);
		pad = (32-((s.tell() - pos) % 32)) % 32;
		for (unsigned int ii = 0; ii < pad; ii++) {s.writebyte(0);}
		}
	}

size_t fmtEFF_TPL_Table::size () {
	size_t nsize = table.size();
//	for (unsigned int i = 0; i < tpl_pc.size; i++) {
//		nsize += tpl_pc[i].size();
//		}
//	for (unsigned int i = 0; i < tpl_gc.size; i++) {
//		nsize += tpl_gc[i].size();
//		}
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

fmtEFF_Sprite::fmtEFF_Sprite () {
	unk71 = 0;
	unk72 = 0;
	unk73 = 0;
	unk74 = 0;
	unk75 = 0;
	unk76 = 0;
	unk77 = 0;
	unk78 = 0;
	unk79 = 0;
	unk80 = 0;
	unk81 = 0;
	unk82 = 0;
	}

void fmtEFF_Sprite::read_sprite_block (bytestream &f) {
	unk71 = f.readUshort();
	unk72 = f.readUshort();
	unk73 = f.readUshort();
	unk74 = f.readUshort();
	unk75 = f.readUshort();
	unk76 = f.readUbyte();
	unk77 = f.readUbyte();
	unk78 = f.readUlong();
	unk79 = f.readUlong();
	unk80 = f.readUlong();
	unk81 = f.readUlong();
	unk82 = f.readUlong();
	}

void fmtEFF_Sprite::write_sprite_block (bytestream &s) {
	s.writeshort(unk71);
	s.writeshort(unk72);
	s.writeshort(unk73);
	s.writeshort(unk74);
	s.writeshort(unk75);
	s.writebyte(unk76);
	s.writebyte(unk77);
	s.writelong(unk78);
	s.writelong(unk79);
	s.writelong(unk80);
	s.writelong(unk81);
	s.writelong(unk82);
	}

size_t fmtEFF_Sprite::size () {
	return 32;
	}

void fmtEFF_Sprite_Table::read_sprite_block_table (bytestream &f) {
	size_t pos = f.tell();
	table.read_pointer_table(f);
	entry.clear();
	if (table.count > 0) {
		entry = std::vector<fmtEFF_Sprite>(table.count);
		for (unsigned int i = 0; i < table.count; i++) {
			if (table.addr[i] > 0) {
				f.seek(pos + table.addr[i]);
				entry[i].read_sprite_block(f);
				}
			}
		}
	}

void fmtEFF_Sprite_Table::write_sprite_block_table (bytestream &s) {
	table.count = entry.size();
	table.addr.clear();
	table.addr = std::vector<uint32_t>(table.count);
	//size_t pos = s.tell();
	size_t ptr = 4 + (table.count * 4);
	ptr += (32-(ptr % 32)) % 32;
	for (unsigned int i = 0; i < table.count; i++) {
		table.addr[i] = ptr;
		ptr += 32;
		}
	table.write_pointer_table(s);
	for (unsigned int i = 0; i < table.count; i++) {
		entry[i].write_sprite_block(s);
		}
	}

void fmtEFF_Sprite_Table::export_sprite_table (std::wstring outpath, std::string section, fmtEFF_Index_Table &info, fmtEFF_TPL_Table &library, int padlen, int varlen, int dc_len) {

	// Create Folder
	if (!win::doesFolderExistW(outpath)) {
		win::makeDirW(outpath);
		}

	std::wstring library_path = outpath + L"library\\";
	// create another folder to save the tpl's
	if (!win::doesFolderExistW(library_path)) {
		win::makeDirW(library_path);
		}


	// Export Text File

	// Write header
	std::string txt = "; =============================================================\n";
	txt += ";      Resident Evil 4 Ultimate HD Edition - Sprite Data\n";
	txt += ";             Generated from re4eff by mariokart64n\n";
	txt += "; -------------------------------------------------------------\n;\n";
	txt += "; * Defines Paths to Resource Folders both relative and\n";
	txt += ";   absolute paths are allowed\n;\n";
	txt += "; -------------------------------------------------------------\n;\n";
	txt += ";                  -- CORE SPRITE CHART --\n";
	txt += ";       ________________________________________________\n";
	txt += ";      | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n";
	txt += ";      |________________________________________________\n";
	txt += ";   00 | 00 01 __ 03 04 05 06 07 08 09 0A 0B 0C __ 0E 0F \n";
	txt += ";   01 | 10 __ 12 13 __ __ 16 17 18 19 __ 1B 1C 1D 1E 1F \n";
	txt += ";   02 | 20 __ 22 23 __ 25 26 __ 28 __ __ __ 2C __ 2E __ \n";
	txt += ";   03 | __ __ 32 __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   04 | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   05 | 50 51 52 53 __ __ 56 57 58 59 5A __ __ __ __ 5F \n";
	txt += ";   06 | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ 6F \n";
	txt += ";   07 | __ __ 72 __ __ __ __ __ __ 79 __ __ __ __ __ __ \n";
	txt += ";   08 | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   09 | __ __ __ __ __ __ 96 __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0A | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0B | __ B1 B2 __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0C | __ __ __ __ __ __ __ __ __ __ __ __ __ CD CE __ \n";
	txt += ";   0D | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0E | __ __ E2 __ __ __ __ __ __ E9 __ __ __ __ __ __ \n";
	txt += ";   0F | __ __ __ __ __ __ __ F7 __ __ __ __ FC __ __ FF \n;\n;\n";
	txt += ";       00: Blood Splat 1         25: Vertical Gradient\n";
	txt += ";       01: Blood Splat 2         26: Flame 1\n";
	txt += ";       03: Blood Splat 3         28: Flame 2\n";
	txt += ";       04: Blood Spot 1          2C: Explosion 5\n";
	txt += ";       05: Blood Spot 2          2E: Explosion 6\n";
	txt += ";       06: Blood Splat 4         32: Blended Square\n";
	txt += ";       07: Blood Splat 5         50: Dish\n";
	txt += ";       08: Specular 1            51: Smoke 4\n";
	txt += ";       09: Blood Splat 6         52: Smoke 5\n";
	txt += ";       0A: Explosion 1           53: Smoke 6\n";
	txt += ";       0B: V Shaped Gradient     56: Splash 1\n";
	txt += ";       0C: Blood Splat 7         57: Splash 2\n";
	txt += ";       0E: Blood Splat 8         58: Splash 3\n";
	txt += ";       0F: Blood Splat 9         59: Splash 4\n";
	txt += ";       10: Blood Splat 10        5A: Splash 5\n";
	txt += ";       12: Bullet Hole           5F: Splash 6\n";
	txt += ";       13: Specular 2            6F: Bubbles\n";
	txt += ";       16: Blood Splat 11        72: Screen Static\n";
	txt += ";       17: Specular 3            79: Specular 5\n";
	txt += ";       18: Blood Splat 12        96: Web\n";
	txt += ";       19: Blood Splat 13        B1: Transparent Circle\n";
	txt += ";       1B: Water Ripple          B2: Circle\n";
	txt += ";       1C: Specular 4            CD: Smoke 7\n";
	txt += ";       1D: Smoke 1               CE: Splash 7\n";
	txt += ";       1E: Smoke 2               E2: Splash 8\n";
	txt += ";       1F: Smoke 3               E9: Highlighted Gradient\n";
	txt += ";       20: Explosion 2           F7: Square\n";
	txt += ";       22: Explosion 3           FC: Square Smoke\n";
	txt += ";       23: Explosion 4           FF: Blended Circle\n;\n";
	txt += "; =============================================================\n\n";
	txt += "[" + section + "]\n\n";


	// write paths
	std::string index_str; // padded index as string
	std::string sprite_path;
	std::stringstream ss;


	std::cout << "SpriteTable: \t" << table.count << std::endl;
	std::cout << "SpriteInfo : \t" << info.count << std::endl;
	std::cout << "TextureLib : \t" << library.table.count << std::endl;



	for (unsigned int i = 0 ; i < table.count; i++) {
		index_str = to_string(i);

		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 12, " ", false) + "Sprite #" + padString(index_str, 4, " ") + "\n";

		index_str = padString(index_str, 7, " ");

		// write index table stuff
		ss.str(std::string());
		ss << std::uppercase << TO_HEX(info.index.at(i).id1, false, 4);
		txt += padString("  sprite_id   " + index_str, varlen, " ", false);
		txt += " = 0x" + ss.str() + "\n";

		if (info.index.at(i).id2 != 0) {
			ss.str(std::string());
			ss << std::uppercase << TO_HEX(info.index.at(i).id2, false, 4);
			txt += padString("  sprite_flag " + index_str, varlen, " ", false);
			txt += " = 0x" + ss.str() + "\n";
			}

		sprite_path = "sprite" + padString(index_str, 4, "0");
		txt += padString("  sprite_path " + index_str, varlen, " ", false);
		txt += " = " + sprite_path + "\n";

		// write the sprite stuff
		txt += padString("  image_height" + index_str, varlen, " ", false) + " = " + to_string(entry.at(i).unk71) + "\n"; // ? Height Range [1 - 1024]
		txt += padString("  image_width " + index_str, varlen, " ", false) + " = " + to_string(entry.at(i).unk72) + "\n"; //  ? Width Range [1 - 910]
		txt += padString("  texel_width " + index_str, varlen, " ", false) + " = " + to_string(entry.at(i).unk73) + "\n"; //  ? Height Range [0, 8, 28, 31, 32, 43, 47, 48, 56, 64, 86, 128, 512]
		txt += padString("  texel_height" + index_str, varlen, " ", false) + " = " + to_string(entry.at(i).unk74) + "\n"; //  ? Width Range [0 - 910]
		txt += padString("  image_count " + index_str, varlen, " ", false) + " = " + to_string(entry.at(i).unk75) + "\n"; //  Texture Count in the TPL
		txt += padString("  unk1_path   " + index_str, varlen, " ", false) + " = " + to_string((int)entry.at(i).unk76) + "\n"; //  ? Range [0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 21]
		txt += padString("  unk2_path   " + index_str, varlen, " ", false) + " = " + to_string((int)entry.at(i).unk77) + "\n"; //  ? Range [0, 1, 2]




//		entry[i].export_est(outpath + string_to_wstring(sprite_path) + L"\\");

		}
	bytestream s;
	s.writeFileW(outpath + L"lib.txt", 0, txt.size(), (char*)txt.c_str());

	}

size_t fmtEFF_Sprite_Table::size () {
	size_t nsize = table.size();
	for (unsigned int i = 0; i < entry.size(); i++) {
		nsize += entry[i].size();
		}
	return nsize;
	}

void fmtEST_Table::read_addr_table (bytestream &f) {
	size_t pos = f.tell();

	table.read_pointer_table(f);
	entry.clear();
	if (table.count > 0) {
		entry = std::vector<fmtEST>(table.count);
		for (unsigned int i = 0; i < table.count; i++) {
			if (table.addr.at(i) > 0) {
				f.seek(pos + table.addr.at(i));
				entry[i].read_est_entry(f);
				}
			}
		}
	}

void fmtEST_Table::write_addr_table (bytestream &s) {
	table.count = entry.size();
	table.addr = std::vector<uint32_t>(table.count);
	size_t pos = s.tell();
	size_t ptr = 4 + (table.count * 4);
	ptr += (32-(ptr % 32)) % 32;
	for (unsigned int i = 0; i < table.count; i++) {
		table.addr[i] = ptr;
		ptr += entry[i].size();
		ptr += (32-(ptr % 32)) % 32;
		}
	table.write_pointer_table(s);
	unsigned int pad;
	for (unsigned int i = 0; i < table.count; i++) {
		entry[i].write_est_entry(s);
		pad = (32-((s.tell() - pos) % 32)) % 32;
		for (unsigned int ii = 0; ii < pad; ii++) {s.writebyte(0);}
		}
	}

void fmtEST_Table::export_est_table (fmtEFF_Index_Table &info, std::string section, std::wstring outfile, std::wstring outpath, unsigned int index_offset, int padlen, int varlen, int dc_len) {
	if (table.count == 0) {return;}
	unsigned int group_index = index_offset;
	std::stringstream ss;
	std::string index_str;
	std::string group_path;


	// Write header
	std::string txt = "; =============================================================\n";
	txt += ";    Resident Evil 4 Ultimate HD Edition - Animation Data\n";
	txt += ";             Generated from re4eff by mariokart64n\n";
	txt += "; -------------------------------------------------------------\n;\n";
	txt += "; * Defines Paths to Resource Folders both relative and\n";
	txt += ";   absolute paths are allowed\n;\n";
	txt += "; * 'group_id' represents the memory location in which the \n";
	txt += ";   resource is written to. If the same 'group_id' is assigned\n";
	txt += ";   then only the last resource will be accessible through\n";
	txt += ";   memory. Therefore you should keep the 'group_id' discret\n;\n";
	txt += "; -------------------------------------------------------------\n;\n";
	txt += ";                    -- EFF CORE CHART --\n";
	txt += ";       ________________________________________________\n";
	txt += ";      | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n";
	txt += ";      |________________________________________________\n";
	txt += ";   00 | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F \n";
	txt += ";   01 | 10 11 12 13 14 15 16 17 18 19 1A 1B 1C __ 1E 1F \n";
	txt += ";   02 | 20 21 22 __ 24 25 26 27 28 __ __ __ 2C __ 2E 2F \n";
	txt += ";   03 | 30 31 32 33 34 __ 36 __ __ 39 3A 3B 3C 3D __ 3F \n";
	txt += ";   04 | 40 41 42 43 44 45 46 47 __ __ __ __ __ 4D 4E 4F \n";
	txt += ";   05 | 50 51 52 __ __ __ __ 57 58 __ __ __ __ __ __ __ \n";
	txt += ";   06 | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   07 | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   08 | __ __ __ __ __ __ __ 87 __ __ __ __ __ __ 8E __ \n";
	txt += ";   09 | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0A | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0B | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0C | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0D | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0E | __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ \n";
	txt += ";   0F | __ __ __ F3 __ F5 F6 __ __ F9 FA FB __ __ __ __ \n;\n;\n";
	txt += ";       00: Blood Spurt           28: Water Surface Expl\n";
	txt += ";       01: Blood Splat           2C: Blue Pickup Aura\n";
	txt += ";       02: Blood Splat 2         2E: Blue Pickup Aura, \n";
	txt += ";       03: Red Laser             2F: Red Pickup Aura\n";
	txt += ";       04: Water Splash          30: Red Pickup Aura, S\n";
	txt += ";       05: Water Splash 2        31: Green Pickup Aura\n";
	txt += ";       06: Screen Glare          32: Green Pickup Aura,\n";
	txt += ";       07: Screen Glare 2        33: White Pickup Aura\n";
	txt += ";       08: Screen Glare 3        34: Blood Drop on Grou\n";
	txt += ";       09: Screen Glare 4        36: Explosion with Deb\n";
	txt += ";       0A: Water Surface Expl    39: Water Surface Expl\n";
	txt += ";       0B: Explosion with Deb    3A: Water Surface Spla\n";
	txt += ";       0C: Burst of Smoke        3B: Multiple Sparks\n";
	txt += ";       0D: Explosion with Deb    3C: Violent Screen Fla\n";
	txt += ";       0E: Water Surface Spla    3D: Short Burst Sparkl\n";
	txt += ";       0F: Water Surface Spla    3F: Slow Screen Flashe\n";
	txt += ";       10: Fire Explosion, Bl    40: Tiny Water Splash\n";
	txt += ";       11: Water Surface Spla    41: Tiny Water Splash \n";
	txt += ";       12: Water Surface Ripp    42: Mid Water Splash, \n";
	txt += ";       13: Water Surface Spla    43: Mid Water Splash, \n";
	txt += ";       14: Water Surface Spla    44: Small Water Splash\n";
	txt += ";       15: Water Surface Expl    45: Green Splashes\n";
	txt += ";       16: Small Smoke Cloud     46: Light Blue item Pi\n";
	txt += ";       17: Small Smoke Cloud     47: Light Blue item Pi\n";
	txt += ";       18: Small Explosion       4D: Extend Time Pickup\n";
	txt += ";       19: Water Surface Spla    4F: Flashing Red Dot 1\n";
	txt += ";       1A: Ground Scurched Bl    50: Flashing Red Dot 2\n";
	txt += ";       1B: Screen Grain Effec    51: Screen Flashing Wh\n";
	txt += ";       1C: Blood Drop on Grou    52: Yellow Shooting Pl\n";
	txt += ";       1E: Screen goes black     57: Small Explosion 2\n";
	txt += ";       1F: Mid Smoke Cloud       58: Blood Drop on Grou\n";
	txt += ";       20: Small Smoke Cloud     87: Black on White Dot\n";
	txt += ";       21: Pulsating Sparkle     8E: Circle Made of Dot\n";
	txt += ";       22: Small Water Surfac    F3: Thermal Vision Scr\n";
	txt += ";       24: Pulsating Sparkle     F5: Amber Screen\n";
	txt += ";       25: Pulsating Sparkle     F6: Amber Screen + Lav\n";
	txt += ";       26: Ground Scurched Bl    F9: Falling Green Smok\n";
	txt += ";       27: Fire Explosion, Bl    FA: Enveloping Grey Sm\n;\n";
	txt += "; =============================================================\n\n";
	txt += "[" + section + "]\n\n";

	for (unsigned int i = 0 ; i < table.count; i++) {
		index_str = to_string(group_index);

		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 11, " ", false) + "GROUP #" + padString(index_str, 4, " ") + "\n";

		index_str = padString(index_str, 8, " ");


		ss.str(std::string());
		ss << std::uppercase << TO_HEX(info.index[i].id1, false, 4);
		txt += padString("  group_id  " + index_str, varlen, " ", false);
		txt += " = 0x" + ss.str() + "\n";

		if (info.index[i].id2 != 0) {
			ss.str(std::string());
			ss << std::uppercase << TO_HEX(info.index[i].id2, false, 4);
			txt += padString("  group_flag" + index_str, varlen, " ", false);
			txt += " = 0x" + ss.str() + "\n";
			}

		group_path = "group" + padString(to_string(group_index), 4, "0");
		txt += padString("  group_path" + index_str, varlen, " ", false);
		txt += " = " + group_path + "\n";

		entry[i].export_est(outpath + string_to_wstring(group_path) + L"\\");

		group_index++;
		}
	bytestream s;
	s.writeFileW(outfile, 0, txt.size(), (char*)txt.c_str());

	}

size_t fmtEST_Table::size () {
	size_t nsize = table.size();
	for (unsigned int i = 0; i < entry.size(); i++) {
		nsize += entry[i].size();
		}
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

fmtEFF_Spline_Data::fmtEFF_Spline_Data () {
	vertex[0] = 0.0f;
	vertex[1] = 0.0f;
	vertex[2] = 0.0f;
	unk30 = 0;
	unk31 = 0;
	unk32 = 0;
	position = 0.0;
	unk33 = 0;
	unk34 = 0;
	unk35 = 0;
	}

void fmtEFF_Spline_Data::read_spline_data (bytestream &f) {
	vertex[0] = f.readfloat();
	vertex[1] = f.readfloat();
	vertex[2] = f.readfloat();
	unk30 = f.readUlong();
	unk31 = f.readUlong();
	unk32 = f.readUlong();
	position = f.readfloat();
	unk33 = f.readUlong();
	unk34 = f.readUlong();
	unk35 = f.readUlong();
	}

void fmtEFF_Spline_Data::write_spline_data (bytestream &s) {
	s.writefloat(vertex[0]);
	s.writefloat(vertex[1]);
	s.writefloat(vertex[2]);
	s.writelong(unk30);
	s.writelong(unk31);
	s.writelong(unk32);
	s.writefloat(position);
	s.writelong(unk33);
	s.writelong(unk34);
	s.writelong(unk35);
	}

size_t fmtEFF_Spline_Data::size () {
	return 40;
	}

fmtEFF_Spline::fmtEFF_Spline () {
	count = 0;
	unk30 = 0;
	}

void fmtEFF_Spline::read_spline (bytestream &f) {
	count = f.readUshort();
	unk30 = f.readUshort();
	data.clear();
	if (count > 0) {
		data = std::vector<fmtEFF_Spline_Data>(count);
		for (unsigned int i = 0; i < count; i++) {
			data.at(i).read_spline_data(f);
			}
		}
	}

void fmtEFF_Spline::write_spline (bytestream &s) {
	s.writeshort(count = data.size());
	s.writeshort(unk30);
	for (unsigned int i = 0; i < count; i++) {
		data[i].write_spline_data(s);
		}
	unsigned int pad = (32-((4 + (40 * data.size())) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0);}
	}

size_t fmtEFF_Spline::size () {
	return 4 + (40 * data.size());
	}

bool fmtEFF_Spline::export_obj (std::wstring fileW, std::string objname) {
	bool isGood = false;

	// check number of vertices
	if (count > 0) {

		// set float length
		int dc_len = 6;

		// write obj header
		std::stringstream ss;
		std::string txt = "# =============================================================\n";
		txt += "#                   Wavefront OBJ - ASCII Line\n";
		txt += "#             Generated from re4eff by mariokart64n\n";
		txt += "# -------------------------------------------------------------\n";
		txt += "#   File Created: " + get_part_date("%Y-%m-%d %H:%M:%S") + "\n#\n";
		txt += "# * you may need to enable lines/shapes in your\n";
		txt += "#   obj importer / exporter settings";
		txt += "\n#\n# =============================================================\n\n";

		// write vertices
		for (unsigned int i = 0; i < count; i++) { // objs to write
			txt += "v ";


			ss.str(std::string());
			ss  << std::fixed << std::setprecision(dc_len) << data.at(i).vertex[0];
			txt += " " + ss.str();

			ss.str(std::string());
			ss  << std::fixed << std::setprecision(dc_len) << -data.at(i).vertex[2];
			txt += " " + ss.str();

			ss.str(std::string());
			ss  << std::fixed << std::setprecision(dc_len) << data.at(i).vertex[1];
			txt += " " + ss.str();

			txt += "\n";
			}
		txt += "# " + to_string(count) + " vertices\n\n";
		txt += "o " + objname + "\n";
		txt += "g " + objname + "\nl";
		for (unsigned int i = 0; i < count; i++) {
			txt += " " + to_string(i + 1);
			}
		txt += "\n";


		if (fileW == L"") {
			std::cout << txt << std::endl;
			}
		else {
			bytestream s;
			s.writeFileW(fileW, 0, txt.size(), (char*)txt.c_str());
			}
		isGood = true;
		}
	return isGood;
	}

void fmtEFF_Spline_Table::read_spline_table (bytestream &f) {
	size_t pos = f.tell();
	table.read_pointer_table(f);
	entry.clear();
	if (table.count > 0) {
		entry = std::vector<fmtEFF_Spline>(table.count);
		for (unsigned int i = 0; i < table.count; i++) {
			if (table.addr.at(i) > 0) {
				f.seek(pos + table.addr.at(i));
				entry.at(i).read_spline(f);
				}
			}
		}
	}

void fmtEFF_Spline_Table::write_spline_table (bytestream &s) {
	table.count = entry.size();
	table.addr = std::vector<uint32_t>(table.count);
	size_t pos = s.tell();
	size_t ptr = 4 + (table.count * 4);
	ptr += (32-(ptr % 32)) % 32;
	for (unsigned int i = 0; i < table.count; i++) {
		table.addr[i] = ptr;
		ptr += entry[i].size();
		ptr += (32-(ptr % 32)) % 32;
		}
	table.write_pointer_table(s);
	unsigned int pad;
	for (unsigned int i = 0; i < table.count; i++) {
		entry[i].write_spline(s);
		pad = (32-((s.tell() - pos) % 32)) % 32;
		for (unsigned int ii = 0; ii < pad; ii++) {s.writebyte(0);}
		}
	}

void fmtEFF_Spline_Table::export_spline_table (std::wstring outpath, std::string section, int padlen, int varlen, int dc_len) {

	// create folder
	if (!win::doesFolderExistW(outpath)) {
		win::makeDirW(outpath);
		}


	std::string line_path = "splines";
	std::wstring spline_path = string_to_wstring(line_path) + L"\\";
	if (!win::doesFolderExistW(outpath + spline_path)) {
		win::makeDirW(outpath + spline_path);
		}

	// create text
	std::string txt = "; =============================================================\n";
	txt += ";       Resident Evil 4 Ultimate HD Edition - Line Data\n";
	txt += ";             Generated from re4eff by mariokart64n\n";
	txt += "; -------------------------------------------------------------\n;\n";
	txt += "; * Defines Paths to Resource Folders\n;   both relative and absolute paths are allowed\n;\n";
	txt += "; =============================================================\n\n";
	txt += "[" + section + "]\n\n";
	//txt += padString("  line_path", varlen, " ", false) + " = lines\n";

	std::string line_file;
	std::string obj_name = "line";
	std::string index_str;
	for (unsigned int i = 0; i < table.count; i++) {
		index_str = to_string(i);
		line_file = padString(index_str, 3, "0");
		txt += padString("  line_file" + padString(index_str, 9, " "), varlen, " ", false);
		txt += " = " + line_path + "\\" + obj_name + line_file + ".obj\n";

		// Create Obj File
		entry.at(i).export_obj(
			outpath + spline_path + string_to_wstring(obj_name + line_file) + L".obj",
			obj_name + index_str
			);
		}

	// write text file
	bytestream s;
	s.writeFileW(outpath + L"pth.txt", 0, txt.size(), (char*)txt.c_str());
	}

size_t fmtEFF_Spline_Table::size () {
	size_t nsize = table.size();
	for (unsigned int i = 0; i < entry.size(); i++) {
		nsize += entry[i].size();
		}
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

void fmtEFF_Model::read_bin_group (bytestream &f) {

	// Log Start Position
//	size_t pos = f.tell();

	// Read Pointer Table {Always 4 Entries}
	table.read_pointer_table(f);

	// Table Should Always have 4 Entries, but just encase check it isn't empty
	if (table.count > 0) {

//		bool byte_order = f.islilEndian;
//		for (unsigned int i = 0; i < table.count; i++) {
//
//			// Check Pointer is not NULL
//			if (table.addr[i] > 0 && {table.addr[i] + 16 + pos} < f.size) {
//
//				// Seek to Asset
//				f.seek{pos + table.addr[i]}
//
//				case i of {
//					1: { // Model
//						model.read_bin(f);//platform:0
//						}
//
//					2: { // TPL
//						texture.read(f);
//						}
//
//					3: { // Obfusticated TPL Table
//						//f.swapBytes = true
//						//gc_tpl.read_tpl_table &f 0 0 scan:false
//						//f.swapBytes = byte_order
//						}
//
//					default: {
//						std::cout << "Error: \tUnexpected Pointer Index [" << i << "\n]";
//						}
//					}
//				}
//			}
		}
	}

void fmtEFF_Model::write_bin_group (bytestream &s) {
	table.count = 4;
	table.addr = std::vector<uint32_t>(4);

	size_t pos = s.tell();
	size_t ptr = 32;
	unsigned int pad = 0;

	// Model
	table.addr[0] = ptr;
	//ptr += model.size();
	ptr += (32-(ptr % 32)) % 32;

	// Texture Library
	table.addr[1] = ptr;
	//ptr += tpl.size();
	ptr += (32-(ptr % 32)) % 32;

	// Block3, 4 normally are left NULL
	table.addr[2] = 0; // samples with 3 present appear to contain corrupt tpl data
	table.addr[3] = 0; // never observed in samples

	// Write Table
	table.write_pointer_table(s);

	// Write Model
	//model.write(s);
	pad = (32-((s.tell() - pos) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0);}

	// Write Texture Library
	//tpl.write(s);
	pad = (32-((s.tell() - pos) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0);}
	}

size_t fmtEFF_Model::size () {
	size_t nsize = 32;
//	nsize += model.size() + ((32-((model.size()) % 32)) % 32);
//	nsize += tpl.size() + ((32-((tpl.size()) % 32)) % 32);
	return nsize;
	}

void fmtEFF_Model_Table::read_bin_table (bytestream &f, bool scan) {

	// Log Start Position
	size_t pos = f.tell();

	// Read Pointer Table
	table.read_pointer_table(f);
	entry.clear();

	// Check Count is not NULL
	if (table.count > 0) {


		// Dimension entry Array
		entry = std::vector<fmtEFF_Model>(table.count);

		// Read Each entry Group
		for (unsigned int i = 0; i < table.count; i++) {

			// Check Pointer is not NULL
			if (table.addr[i] > 0) {

				// Read BIN Archive
				f.seek(pos + table.addr[i]);
				entry[i].read_bin_group(f);
				}
			}
		}
	}

void fmtEFF_Model_Table::write_bin_table (bytestream &s) {

	table.count = entry.size();
	table.addr.clear();
	size_t pos = s.tell();
	size_t ptr = 4 + (table.count * 4);
	ptr += (32-(ptr % 32)) % 32;
	for (unsigned int i = 0; i < table.count; i++) {
		table.addr[i] = ptr;
		ptr += entry[i].size();
		ptr += (32-(ptr % 32)) % 32;
		}
	table.write_pointer_table(s);
	unsigned int pad;
	for (unsigned int i = 0; i < table.count; i++) {
		entry[i].write_bin_group(s);
		pad = (32-((s.tell() - pos) % 32)) % 32;
		for (unsigned int i = 0; i < pad; i++) {s.writebyte(0);}
		}
	}

bool fmtEFF::validate (bytestream &f) {
	bool isGood = false;
	size_t pos = f.tell();
	if (f.size >= 224) {
		unsigned int check1 = f.readUlong();

		// Check Byte Order
		if (check1 >= 0x01000000 || check1 < 0) {

			// Change Byte Order
			f.islilEndian = !f.islilEndian;
			f.seek(-4, 1);
			check1 = f.readUlong();
			}

		// Check Count is 11
		if (check1 == 11) {
			unsigned int check2 = f.readUlong();
			if (check2 == 0) {
				// don't have alot to go off here lol, just pass it as ok
				isGood = true;
				}
			else if (check2 == 64) {
				f.seek(pos + 48);
				unsigned int check3 = f.readUlong();
				unsigned int check4 = f.readUlong();
				unsigned int check5 = f.readUlong();
				unsigned int check6 = f.readUlong();
				if (check3 == 0 && check4 == 0 && check5 == 0 && check6 == 0) {
					isGood = true;
					} else {std::cout << "Error: \tInvalid Table\n";}
				} else {std::cout << "Error: \tHeader Signature Failure\n";}
			} else {std::cout << "Error: \tHeader Invalid\n";}
		f.seek(pos);
		} else {std::cout << "Error: \tInvalid File Size\n";}
	return isGood;
	}

void fmtEFF::read_eff (bytestream &f, bool read_gc_data) {

	// Get Start, needed for reading embedded files
	size_t pos = f.tell();


	if (validate(f)) {

		// Read Main Pointer Table
		blocks.read_pointer_table(f);

		// Read Blocks
		unsigned int valid_blocks = 0;
		for (unsigned int i = 0; i < blocks.count; i++) {

			// Check Pointer is Not NULL
			if (blocks.addr.at(i) > 0) {
				valid_blocks += 1;
				// Read Blocks
				f.seek(pos + blocks.addr.at(i));
				switch (i) {
					case  0: {sprite_block_info.read_index_table(f); break;}	// Sprite Info
					case  1: {esp1_block_info.read_index_table(f); break;}	// Effect Info
					case  2: {esp2_block_info.read_index_table(f); break;} // Effect2 Info
					case  3: {spline_block_info.read_index_table(f); break;}
					//case  4: {model_block_info.read_index_table(f); break;}	// Model Info
					case  5: {tpl_block.read_tpl_table(f, pos, blocks, read_gc_data); break;}				// Texture Data {TPL}
					case  6: {sprite_block.read_sprite_block_table(f); break;}	// Sprite Texture Data
					case  7: {esp1_block.read_addr_table(f); break;}			// Effect Data {ESP / EST}
					case  8: {esp2_block.read_addr_table(f); break;} // Event Activated Effect Data {ESP / EST}
					case  9: {spline_block.read_spline_table(f); break;} // Paths Data
					//case 10: {model_block.read_bin_table(f, read_gc_data); break;}			// Mesh Data {BIN}
					}
				}
			}
		}
	}

void fmtEFF::write_eff (bytestream &s) {
	//size_t pos = s.tell(); // should be 0, unless file is embedded
	size_t ptr = 32;

	// Get Size of Index Tables
	size_t sprite_block_info_size = sprite_block_info.size();
	size_t esp1_block_info_size = esp1_block_info.size();
	size_t esp2_block_info_size = esp2_block_info.size();
	size_t spline_block_info_size = spline_block_info.size();
	size_t model_block_info_size = model_block_info.size();

	// Get Size of Resources
	size_t tpl_block_size = tpl_block.size();
	size_t sprite_block_size = sprite_block.size();
	size_t esp1_block_size = esp1_block.size();
	size_t esp2_block_size = esp2_block.size();
	size_t spline_block_size = spline_block.size();
	size_t model_block_size = 0;//model_block.size();

	// Rebuild Pointer Table
	blocks.count = 11;
	blocks.addr.clear();
	blocks.addr = std::vector<uint32_t>(blocks.count);
	for (unsigned int i = 0; i < blocks.count; i++) {
		blocks.addr[i] = 0;
		}

	blocks.addr[0] = ptr;
	ptr += sprite_block_info_size;

	blocks.addr[1] = ptr;
	ptr += esp1_block_info_size;

	blocks.addr[2] = ptr;
	ptr += esp2_block_info_size;

	blocks.addr[3] = ptr;
	ptr += spline_block_info_size;

	blocks.addr[4] = ptr;
	ptr += model_block_info_size;

	if (sprite_block_info.index.size() > 0) {
		blocks.addr[5] = ptr;
		ptr += tpl_block_size;

		blocks.addr[6] = ptr;
		ptr += sprite_block_size;
		}

	if (esp1_block_info.index.size() > 0) {
		blocks.addr[7] = ptr;
		ptr += esp1_block_size;
		}

	if (esp2_block_info.index.size() > 0) {
		blocks.addr[8] = ptr;
		ptr += esp2_block_size;
		}

	if (spline_block_info.index.size() > 0) {
		blocks.addr[9] = ptr;
		ptr += spline_block_size;
		}

	if (model_block_info.index.size() > 0) {
		blocks.addr[10] = ptr;
		ptr += model_block_size;
		}

	// Write Blocks
	for (unsigned int i = 0; i < blocks.count; i++) {

		// Check Pointer is Not NULL
		if (blocks.addr[i] > 0) {

			// Write Blocks
			switch (i + 1) {
				case  1: {sprite_block_info.write_index_table(s); break;}	// Sprite Info
				case  2: {esp1_block_info.write_index_table(s); break;}	// Effect Info
				case  3: {esp2_block_info.write_index_table(s); break;} // Effect2 Info
				case  4: {spline_block_info.write_index_table(s); break;}
				case  5: {model_block_info.write_index_table(s); break;}	// Model Info
				case  6: {tpl_block.write_tpl_table(s); break;}				// Texture Data {TPL}
				case  7: {sprite_block.write_sprite_block_table(s); break;}	// Sprite Texture Data
				case  8: {esp1_block.write_addr_table(s); break;}			// Effect Data {ESP / EST}
				case  9: {esp2_block.write_addr_table(s); break;} // Event Activated Effect Data {ESP / EST}
				case 10: {spline_block.write_spline_table(s); break;} // Paths Data
				case 11: {model_block.write_bin_table(s); break;}			// Mesh Data {BIN}
				}
			}
		}
	}

size_t fmtEFF::size () {
	size_t nsize = 32;

	nsize += sprite_block_info.size();
	nsize += esp1_block_info.size();
	nsize += esp2_block_info.size();
	nsize += spline_block_info.size();
	nsize += model_block_info.size();

	if (sprite_block_info.index.size() > 0) {
		nsize += tpl_block.size();
		nsize += sprite_block.size();
		}

	if (esp1_block_info.index.size() > 0) {
		nsize += esp1_block.size();
		}

	if (esp2_block_info.index.size() > 0) {
		nsize += esp2_block.size();
		}

	if (spline_block_info.index.size() > 0) {
		nsize += spline_block.size();
		}

	if (model_block_info.index.size() > 0) {
		//nsize += model_block.size();
		}

	return nsize;
	}

void fmtEFF::export_eff (std::wstring outpath, int padlen, int varlen, int dc_len) {
	/*
		* Each folder contains a txt which contains configurations
		  for that data. if the txt is not present then defaults are loaded

		* 'eff.txt' defines relative or absolute paths to the 4 resource folders

		* names of txt's do not matter, [Section] tags inside the txt
		  are used to identify each txt file

		* sub folders are created for each resource, it is possible for
		  no sub folders to be created if eff is empty

		* If user fails to provide path to PACK then TPL's are exported
		  instead of library folders containing the textures

		* Data ID's are read from each txt, however if the txt is missing
		  then the order of the assets become their IDS

		[EFF_FOLDER]
		|
		+-- eff.txt # defines paths to each resource folder
		+-- tpl.dat # orphaned tpl library block (optional)
		+-- bin.dat # orphaned bin model block (optional)
		|
		+-- [EFFECT]
		|   |
		|   +-- est.txt # Defines Resource ID for each folder
		|   +-- sst.txt # Defines Resource ID for each folder
		|   |
		|   +-- [GROUP000]
		|       |
		|       +-- pos.txt # defines transform of group
		|       |
		|       +-- [LAYER0]
		|       |   |
		|       |   +-- sst00.txt
		|       |   +-- sst01.txt
		|       |
		|       +-- [LAYER1]
		|       |   |
		|       |   +-- sst00.txt
		|       |   +-- sst01.txt
		|       |
		|       +-- [LAYER3]
		|       |   |
		|       |   +-- sst00.txt
		|       |   +-- sst01.txt
		|       |
		|       +-- [LAYER4]
		|           |
		|           +-- sst3.txt
		|
		+-- [MODELS]
		|   |
		|   +-- mdl.txt # defines resource id for each folder
		|   |
		|   +-- [MESH00]
		|       |
		|       +-- bin0.tpl
		|       +-- tex0.tpl
		|
		+-- [PATHS]
		|   |
		|   +-- pth.txt # defines resource id for each obj file
		|   |
		|   +-- [SPLINES]
		|       |
		|       +-- path0.obj
		|       +-- path1.obj
		|
		+-- [SPRITES]
			|
			+-- lib.txt # defines resource id for each folder
			|
			+-- [LIBRARY0]
			|   |
			|   +-- tex.txt
			|   +-- img0.tga
			|   +-- img1.tga
			|
			+-- [LIBRARY1]
				|
				+-- tex.txt
				+-- img0.tga

	*/


	// Create Path
	if (!win::doesFolderExistW(outpath)) {
		win::makeDirW(outpath);
		}

	// Create Resource Folders
    if (esp1_block.table.count > 0 || esp2_block.table.count > 0) {
		std::wstring p = outpath + L"effects\\";
		if (!win::doesFolderExistW(p)) {
			win::makeDirW(p);
			}
		}
    if (spline_block_info.count > 0) {
		std::wstring p = outpath + L"lines\\";
		if (!win::doesFolderExistW(p)) {
			win::makeDirW(p);
			}
		}
    if (model_block.table.count > 0) {
		std::wstring p = outpath + L"models\\";
		if (!win::doesFolderExistW(p)) {
			win::makeDirW(p);
			}
		}
    if (sprite_block.table.count > 0) {
		std::wstring p = outpath + L"sprites\\";
		if (!win::doesFolderExistW(p)) {
			win::makeDirW(p);
			}
		}

	// Create EFF Text
	//int padlen = 65;
	//int varlen = 21;
	//int dc_len = 6;
	std::stringstream ss;
	std::string txt = "; =============================================================\n";
	txt += ";       Resident Evil 4 Ultimate HD Edition - Effects Data\n";
	txt += ";             Generated from re4eff by mariokart64n\n";
	txt += "; -------------------------------------------------------------\n;\n";
	txt += "; * Defines Paths to Resource Folders\n;   both relative and absolute paths are allowed\n";
	txt += "; =============================================================\n\n";
	txt += "[EFF_RESOUCE]\n\n";


    if (esp1_block.table.count > 0 || esp2_block.table.count > 0) {
		txt += padString("  effects_path", varlen, " ", false) + " = effects\n";
		}
    if (spline_block_info.count > 0) {
		txt += padString("  lines_path", varlen, " ", false) + " = lines\n";
		}
    if (model_block.table.count > 0) {
		txt += padString("  models_path", varlen, " ", false) + " = models\n";
		}
    if (sprite_block.table.count > 0) {
		txt += padString("  sprites_path", varlen, " ", false) + " = sprites\n";
		}

	bytestream s;
	s.writeFileW(outpath + L"eff.txt", 0, txt.size(), (char*)txt.c_str());

	// Export Each Resource
	unsigned int group_index = 0;
	std::string index_str;
	if (esp1_block.table.count > 0) {
		esp1_block.export_est_table(
			esp1_block_info,
			"EFF_EFFECT",
			outpath + L"effects\\est.txt",
			outpath + L"effects\\",
			group_index // this is used to create folder names
			);
		group_index += esp1_block.table.count; // increment so that we don't overwrite other folders
		}
	if (esp2_block.table.count > 0) {
		esp2_block.export_est_table(
			esp2_block_info,
			"EFF_SCR_EFFECT",
			outpath + L"effects\\sst.txt",
			outpath + L"effects\\",
			group_index // this is used to create folder names
			);
		}
	if (spline_block_info.count > 0) {
		spline_block.export_spline_table(outpath + L"lines\\", "EFF_LINE");
		}


	// models
	//
	//
	//
	//

    if (sprite_block.table.count > 0) {
		sprite_block.export_sprite_table(outpath + L"sprites\\", "EFF_SPRITE", sprite_block_info, tpl_block);
		}


	}

