#include "fmtITA.h"

fmtITA_Entry_Flags::fmtITA_Entry_Flags () {
	hasData = true;
	useData = true;
	flg3 = false;
	flg4 = false;
	flg5 = false;
	flg6 = false;
	flg7 = false;
	flg8 = false;
	}

void fmtITA_Entry_Flags::set_entry_flag (uint8_t val) {
	hasData = bit::get(val, 1);
	useData = bit::get(val, 2);
	flg3 = bit::get(val, 3);
	flg4 = bit::get(val, 4);
	flg5 = bit::get(val, 5);
	flg6 = bit::get(val, 6);
	flg7 = bit::get(val, 7);
	flg8 = bit::get(val, 8);
	}

uint8_t fmtITA_Entry_Flags::get_entry_flag () {
	uint8_t val = 0;
	val = bit::set(val, 1, hasData);
	val = bit::set(val, 2, useData);
	val = bit::set(val, 3, flg3);
	val = bit::set(val, 4, flg4);
	val = bit::set(val, 5, flg5);
	val = bit::set(val, 6, flg6);
	val = bit::set(val, 7, flg7);
	val = bit::set(val, 8, flg8);
	return val;
	}

void fmtITA_Entry_Flags::read_entry_flag (bytestream &f) {
	set_entry_flag(f.readUbyte());
	}

void fmtITA_Entry_Flags::write_entry_flag (bytestream &s) {
	s.writebyte(get_entry_flag());
	}

fmtITA_Hit_Flags::fmtITA_Hit_Flags () {
	position_auto_off = false;
	hit_area_auto_off = false;
	see_check_off = false;
	flg4 = false;
	drop_type_shoot_and_fall = false;
	flg6 = false;
	drop_type_fall = false;
	hide_set_on = false;
	}

void fmtITA_Hit_Flags::set_hit_flag (uint8_t val) {
	position_auto_off = bit::get(val, 1);
	hit_area_auto_off = bit::get(val, 2);
	see_check_off = bit::get(val, 3);
	flg4 = bit::get(val, 4);
	drop_type_shoot_and_fall = bit::get(val, 5);
	flg6 = bit::get(val, 6);
	drop_type_fall = bit::get(val, 7);
	hide_set_on = bit::get(val, 8);
	}

uint8_t fmtITA_Hit_Flags::get_hit_flag () {
	uint8_t val = 0;
	val = bit::set(val, 1, position_auto_off);
	val = bit::set(val, 2, hit_area_auto_off);
	val = bit::set(val, 3, see_check_off);
	val = bit::set(val, 4, flg4);
	val = bit::set(val, 5, drop_type_shoot_and_fall);
	val = bit::set(val, 6, flg6);
	val = bit::set(val, 7, drop_type_fall);
	val = bit::set(val, 8, hide_set_on);
	return val;
	}

void fmtITA_Hit_Flags::read_hit_flag (bytestream &f) {
	set_hit_flag(f.readUbyte());
	}

void fmtITA_Hit_Flags::write_hit_flag (bytestream &s) {
	s.writebyte(get_hit_flag());
	}


fmtITA_Entry::fmtITA_Entry () {
	entry_flag.set_entry_flag(0);
	unk010 = 3;
	entry_index = 0;
	hit_type = 0;
	unk013 = 1;
	unk014 = 1;
	unk015 = 0;
	unk016 = 0;
	unk017 = 0;
	unk018 = 0;
	priority = 8;
	unk026 = 0;
	set_wait_type = 0;
	set_target_no = 0;
	hit_angle = 0;
	open_angle = 90;
	unk031 = 0;
	unk032 = 0;
	unk033 = 0;
	unk034 = 0;
	unk035 = 0;
	unk036 = 0;
	unk037 = 0;
	unk038 = 0;
	country = 0;
	unk039 = 0;
	unk040 = 0;
	unk041 = 0;
	unk042 = 0;
	unk043 = 0;
	unk044 = 0;
	unk045 = 0;
	unk046 = 0;
	unk047 = 0;
	set_pos_x = 0.0;
	set_pos_y = 0.0;
	set_pos_z = 0.0;
	unk051 = 0;
	unk052 = 0;
	unk053 = 0;
	unk054 = 0;
	eff_offset_pos_x = 0.0;
	eff_offset_pos_y = 0.0;
	eff_offset_pos_z = 0.0;
	item_id = 0;
	item_flag = 0;
	item_num = 0;
	unk058 = 0;
	unk059 = 0;
	eff_type = 0;
	unk061 = 0;
	unk062 = 0;
	hit_area_disp = 1;
	hit_flags.set_hit_flag(0);
	unk065 = 0;
	unk066 = 0;
	unk067 = 0;
	radius = 0.0;
	cone_ang_x = 0.0;
	cone_ang_y = 0.0;
	cone_open_angle = 0.0;
	se_no_drop = 0;
	se_no_hit = 0;
	unk074 = 0;
	unk075 = 0;
	}

bool fmtITA_Entry::is_re4_2007 (bytestream &f) {
	bool valid = false;
	size_t pos = f.tell();

	if (pos + 176 <= f.size) {
		f.seek(pos + 92);
		unsigned long chk1 = f.readUlong(); // 0
		if (chk1 == 0) {
			f.seek(pos + 108);
			unsigned long chk2 = f.readUlong();
			if (chk2 == 0x0000803F) {
				f.seek(pos + 124);
				unsigned long chk3 = f.readUlong();
				if (chk3 == 0x0000803F) {
					f.seek(pos + 168);
					unsigned long chk4 = f.readUlong(); // 0
					if (chk4 == 0) {
						unsigned long chk5 = f.readUlong(); // 0
						if (chk5 == 0) {
							valid = true;
							}
						}
					}
				}
			}
		}

	f.seek(pos + 176);

	return valid;
	}

void fmtITA_Entry::read_entry (bytestream &f, bool re4_2007) {
	area.read_area(f);
	entry_flag.read_entry_flag(f);
	unk010 = f.readUbyte();
	entry_index = f.readUbyte();
	hit_type = f.readUbyte();
	unk013 = f.readUbyte();
	unk014 = f.readUbyte();
	unk015 = f.readUbyte();
	unk016 = f.readUbyte();
	unk017 = f.readUlong();
	unk018 = f.readUlong();
	priority = f.readUbyte();
	unk026 = f.readUbyte();
	set_wait_type = f.readUbyte();
	set_target_no = f.readUbyte();
	hit_angle = (f.readbyte()) * 2;
	open_angle = (f.readbyte()) * 2; // 2D?
	unk031 = f.readUbyte();
	unk032 = f.readUbyte();
	unk033 = f.readUbyte();
	unk034 = f.readUbyte();
	unk035 = f.readUbyte();
	unk036 = f.readUbyte();
	unk037 = f.readUbyte();
	unk038 = f.readUbyte();
	country = f.readUbyte();
	unk039 = f.readUbyte();
	unk040 = f.readUbyte();
	unk041 = f.readUbyte();
	unk042 = f.readUbyte();
	unk043 = f.readUbyte();
	unk044 = f.readUbyte();
	unk045 = f.readUbyte();
	unk046 = f.readUbyte();
	unk047 = f.readUbyte();
	if (re4_2007) {f.seek(4, 1);}
	set_pos_x = f.readfloat();
	set_pos_y = f.readfloat();
	set_pos_z = f.readfloat();
	if (re4_2007) {f.seek(4, 1);}
	unk051 = f.readUbyte();
	unk052 = f.readUbyte();
	unk053 = f.readUbyte();
	unk054 = f.readUbyte();
	eff_offset_pos_x = f.readfloat();
	eff_offset_pos_y = f.readfloat();
	if (re4_2007) {f.seek(4, 1);}
	eff_offset_pos_z = f.readfloat();
	item_id = f.readUshort();
	item_flag = f.readUshort();
	item_num = f.readUshort();
	unk058 = f.readUbyte();
	unk059 = f.readUbyte();
	eff_type = f.readUbyte();
	unk061 = f.readUbyte();
	unk062 = f.readUbyte();
	hit_area_disp = f.readUbyte();
	hit_flags.read_hit_flag(f);
	unk065 = f.readUbyte();
	unk066 = f.readUbyte();
	unk067 = f.readUbyte();
	radius = f.readfloat();
	cone_ang_x = f.readfloat();
	cone_ang_y = f.readfloat();
	cone_open_angle = f.readfloat();
	se_no_drop = f.readUbyte();
	se_no_hit = f.readUbyte();
	unk074 = f.readUbyte();
	unk075 = f.readUbyte();
	if (re4_2007) {f.seek(8, 1);}
	}

void fmtITA_Entry::write_entry (bytestream &s, bool re4_2007) {
	area.write_area(s);
	entry_flag.write_entry_flag(s);
	s.writebyte(unk010);
	s.writebyte(entry_index);
	s.writebyte(hit_type);
	s.writebyte(unk013);
	s.writebyte(unk014);
	s.writebyte(unk015);
	s.writebyte(unk016);
	s.writelong(unk017);
	s.writelong(unk018);
	s.writebyte(priority);
	s.writebyte(unk026);
	s.writebyte(set_wait_type);
	s.writebyte(set_target_no);
	s.writebyte(hit_angle / 2);
	s.writebyte(open_angle / 2);
	s.writebyte(unk031);
	s.writebyte(unk032);
	s.writebyte(unk033);
	s.writebyte(unk034);
	s.writebyte(unk035);
	s.writebyte(unk036);
	s.writebyte(unk037);
	s.writebyte(unk038);
	s.writebyte(country);
	s.writebyte(unk039);
	s.writebyte(unk040);
	s.writebyte(unk041);
	s.writebyte(unk042);
	s.writebyte(unk043);
	s.writebyte(unk044);
	s.writebyte(unk045);
	s.writebyte(unk046);
	s.writebyte(unk047);
	if (re4_2007) {s.writelong(0);}
	s.writefloat(set_pos_x);
	s.writefloat(set_pos_y);
	s.writefloat(set_pos_z);
	if (re4_2007) {s.writelong(0x0000803F);}
	s.writebyte(unk051);
	s.writebyte(unk052);
	s.writebyte(unk053);
	s.writebyte(unk054);
	s.writefloat(eff_offset_pos_x);
	s.writefloat(eff_offset_pos_y);
	if (re4_2007) {s.writelong(0x0000803F);}
	s.writefloat(eff_offset_pos_z);
	s.writeshort(item_id);
	s.writeshort(item_flag);
	s.writeshort(item_num);
	s.writebyte(unk058);
	s.writebyte(unk059);
	s.writebyte(eff_type);
	s.writebyte(unk061);
	s.writebyte(unk062);
	s.writebyte(hit_area_disp);
	hit_flags.write_hit_flag(s);
	s.writebyte(unk065);
	s.writebyte(unk066);
	s.writebyte(unk067);
	s.writefloat(radius);
	s.writefloat(cone_ang_x);
	s.writefloat(cone_ang_y);
	s.writefloat(cone_open_angle);
	s.writebyte(se_no_drop);
	s.writebyte(se_no_hit);
	s.writebyte(unk074);
	s.writebyte(unk075);
	if (re4_2007) {
		s.writelong(0);
		s.writelong(0);
		}
	}

size_t fmtITA_Entry::size (bool re4_2007) {
	if (re4_2007) {return 176;}
	return 156;
	}

fmtITA::fmtITA () {
	fileid[3] = 0x00;
	fileid[2] = 0x41;
	fileid[1] = 0x54;
	fileid[0] = 0x49;
	unk001 = 0x0105;
	count = 0;
	unk003 = 0;
	unk004 = 0;
	data.clear();
	}

void fmtITA::read_ita (bytestream &f) {
	size_t pos = f.tell();

	// FileID Always Little Endian
	f.setLittleEndian();


	for (unsigned int i = 0; i < 4; i++) {fileid[i] = f.readUbyte();}
	if (fileid[3] == 0x00 && fileid[2] == 0x41 && fileid[1] == 0x54 && fileid[0] == 0x49) {
		unk001 = f.readUshort(); // should always be 0x0105, probably version

		// Try to Detect Endian
		if (unk001 == 0x0501) {
			f.setBigEndian();
			f.seek(pos + 4);
			unk001 = f.readUshort();
			}

		count = f.readUshort();

		if (pos + 16 + (count * 156) <= f.size) {
			unk003 = f.readUlong();
			unk004 = f.readUlong();


			if (count > 0) {


				// detect if (file is 2007 variant
				bool is_re4_2007 = false;
				fmtITA_Entry ia;
				unsigned int i = 0;
				while (!f.eos() && !is_re4_2007 && i < count) {
					is_re4_2007 = is_re4_2007 || ia.is_re4_2007(f);
					i += 1;
					}

				// Seek Back to Table, Read Entries
				f.seek(pos + 16);
				data = std::vector<fmtITA_Entry>(count);
				for (unsigned int i = 0; i < count; i++) {
					data[i].read_entry(f, is_re4_2007);
					}
				}
			} else {std::cout << "ita table is invalid {" << count * 156 << "}: \t" << f.file << "\n";}
		} else {std::cout << "Invalid File\n";}
	}

void fmtITA::write_ita (bytestream &s, bool re4_2007) {
	// Write Header
	s.writebyte(0x49);
	s.writebyte(0x54);
	s.writebyte(0x41);
	s.writebyte(0x00);
	s.writeshort(unk001);
	s.writeshort(count = data.size());
	s.writelong(0);
	s.writelong(0);
	for (unsigned int i = 0; i < count; i++) {
		data[i].write_entry(s, re4_2007);
		}
	size_t pad = (32-((s.tell() - 16) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0xCD);} // pad to 32
	}

size_t fmtITA::size (bool re4_2007) {
	size_t nsize = (count * 156);
	if (re4_2007) {nsize = 16 + (count * 176);}
	nsize += (32-(nsize % 32)) % 32;
	return (nsize + 16);
	}

void fmtITA::xml_export (std::wstring file, bool hideNulls) {
	/* copies the variables into an XML text */

	std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

	unsigned int ita_count = data.size();
	if (ita_count == 0) {return;}
	std::string str;
	std::stringstream ss;

	// XML Root Node
	xml += "<ita name=\"" + wstring_to_string(getFilenameFileW(file)) + ".ita\" count=\"" + to_string(ita_count) + "\">\n";
	xml += "    <!--156 Bytes Per-->\n"; // comment
	for (unsigned int i = 0; i < ita_count; i++) {
		xml += "    <entry index=\"" + to_string(i) + "\">\n";
		xml += "        <atari>\n";
		xml += "            <!-- 52 Bytes Per-->\n";
		xml += "            <hasData>" + to_string((int)data[i].area.unk1) + "</hasData>\n";
		xml += "            <useData>" + to_string((int)data[i].area.unk2) + "</useData>\n";
		xml += "            <player>" + to_string((int)data[i].area.unk3) + "</player>\n";
		xml += "            <enemy>" + to_string((int)data[i].area.unk4) + "</enemy>\n";
		xml += "            <unk5>" + to_string((int)data[i].area.unk5) + "</unk5>\n";
		xml += "            <shape>" + to_string((int)data[i].area.type) + "</shape>\n";
		xml += "            <!--ENUM: shape\n";
		xml += "                   0: None\n";
		xml += "                   1: BOX\n";
		xml += "                   2: CIRCLE\n";
		xml += "                   3: SPHERE\n";
		xml += "            -->\n";
		if (!hideNulls) {xml += "            <unk7>" + to_string((int)data[i].area.unk7) + "</unk7>\n";}
		if (!hideNulls) {xml += "            <unk8>" + to_string((int)data[i].area.unk8) + "</unk8>\n";}
		xml += "            <pos_z>" + to_string(data[i].area.pos_z) + "</pos_z>\n";
		xml += "            <height>" + to_string(data[i].area.height) + "</height>\n";
		xml += "            <radius>" + to_string(data[i].area.radius) + "</radius>\n";
		xml += "            <pos0_x>" + to_string(data[i].area.pos[0]) + "</pos0_x>\n";
		xml += "            <pos0_y>" + to_string(data[i].area.pos[1]) + "</pos0_y>\n";
		xml += "            <pos1_x>" + to_string(data[i].area.pos[2]) + "</pos1_x>\n";
		xml += "            <pos1_y>" + to_string(data[i].area.pos[3]) + "</pos1_y>\n";
		xml += "            <pos2_x>" + to_string(data[i].area.pos[4]) + "</pos2_x>\n";
		xml += "            <pos2_y>" + to_string(data[i].area.pos[5]) + "</pos2_y>\n";
		xml += "            <pos3_x>" + to_string(data[i].area.pos[6]) + "</pos3_x>\n";
		xml += "            <pos3_y>" + to_string(data[i].area.pos[7]) + "</pos3_y>\n";
		xml += "        </atari>\n";
		if (data[i].entry_flag.hasData) {str = "TRUE";} else {str = "FALSE";} xml += "        <hasData>" + str + "</hasData>\n";
		if (data[i].entry_flag.useData) {str = "TRUE";} else {str = "FALSE";} xml += "        <useData>" + str + "</useData>\n";
		if (!hideNulls) {if (data[i].entry_flag.flg3) {str = "TRUE";} else {str = "FALSE";} xml += "        <flg3>" + str + "</flg3>\n";}
		if (!hideNulls) {if (data[i].entry_flag.flg4) {str = "TRUE";} else {str = "FALSE";} xml += "        <flg4>" + str + "</flg4>\n";}
		if (!hideNulls) {if (data[i].entry_flag.flg5) {str = "TRUE";} else {str = "FALSE";} xml += "        <flg5>" + str + "</flg5>\n";}
		if (!hideNulls) {if (data[i].entry_flag.flg6) {str = "TRUE";} else {str = "FALSE";} xml += "        <flg6>" + str + "</flg6>\n";}
		if (!hideNulls) {if (data[i].entry_flag.flg7) {str = "TRUE";} else {str = "FALSE";} xml += "        <flg7>" + str + "</flg7>\n";}
		if (!hideNulls) {if (data[i].entry_flag.flg8) {str = "TRUE";} else {str = "FALSE";} xml += "        <flg8>" + str + "</flg8>\n";}
		if (!hideNulls) {xml += "        <unk010>" + to_string((int)data[i].unk010) + "</unk010>\n";}
		xml += "        <index>" + to_string((int)data[i].entry_index) + "</index>\n";
		xml += "        <hit_type>" + to_string((int)data[i].hit_type) + "</hit_type>\n";
		xml += "        <!--ENUM: hit_type\n";
		xml += "               0: UNDER\n";
		xml += "               1: FRONT\n";
		xml += "               2: UNDER+ANGLE\n";
		xml += "               3: FRONT+ANGLE\n";
		xml += "        -->\n";
		xml += "        <unk013>" + to_string((int)data[i].unk013) + "</unk013>\n";
		if (!hideNulls) {xml += "        <unk014>" + to_string((int)data[i].unk014) + "</unk014>\n";}
		if (!hideNulls) {xml += "        <unk015>" + to_string((int)data[i].unk015) + "</unk015>\n";}
		if (!hideNulls) {xml += "        <unk016>" + to_string((int)data[i].unk016) + "</unk016>\n";}
		if (!hideNulls) {xml += "        <unk017>" + to_string(data[i].unk017) + "</unk017>\n";}
		if (!hideNulls) {xml += "        <unk018>" + to_string(data[i].unk018) + "</unk018>\n";}
		xml += "        <priority>" + to_string((int)data[i].priority) + "</priority>\n";
		if (!hideNulls) {xml += "        <unk026>" + to_string((int)data[i].unk026) + "</unk026>\n";}
		xml += "        <set_wait_type>" + to_string((int)data[i].set_wait_type) + "</set_wait_type>\n";
		xml += "        <!--ENUM: set_wait_type\n";
		xml += "               0: NORMAL\n";
		xml += "               1: EM_DEAD\n";
		xml += "               2: UNDERETC_BREAKANGLE\n";
		xml += "        -->\n";
		xml += "        <set_target_no>" + to_string((int)data[i].set_target_no) + "</set_target_no>\n";
		xml += "        <hit_angle>" + to_string((int)data[i].hit_angle) + "</hit_angle>\n";
		xml += "        <open_angle>" + to_string((int)data[i].open_angle) + "</open_angle>\n";
		xml += "        <unk031>" + to_string((int)data[i].unk031) + "</unk031>\n";
		if (!hideNulls) {xml += "        <unk032>" + to_string((int)data[i].unk032) + "</unk032>\n";}
		if (!hideNulls) {xml += "        <unk033>" + to_string((int)data[i].unk033) + "</unk033>\n";}
		if (!hideNulls) {xml += "        <unk034>" + to_string((int)data[i].unk034) + "</unk034>\n";}
		if (!hideNulls) {xml += "        <unk035>" + to_string((int)data[i].unk035) + "</unk035>\n";}
		if (!hideNulls) {xml += "        <unk036>" + to_string((int)data[i].unk036) + "</unk036>\n";}
		if (!hideNulls) {xml += "        <unk037>" + to_string((int)data[i].unk037) + "</unk037>\n";}
		if (!hideNulls) {xml += "        <unk038>" + to_string((int)data[i].unk038) + "</unk038>\n";}
		xml += "        <country>" + to_string((int)data[i].country) + "</country>\n";
		xml += "        <!--ENUM: country\n";
		xml += "               0: JPN/USA\n";
		xml += "               1: JPN\n";
		xml += "               2: USA\n";
		xml += "        -->\n";
		if (!hideNulls) {xml += "        <unk039>" + to_string((int)data[i].unk039) + "</unk039>\n";}
		if (!hideNulls) {xml += "        <unk040>" + to_string((int)data[i].unk040) + "</unk040>\n";}
		if (!hideNulls) {xml += "        <unk041>" + to_string((int)data[i].unk041) + "</unk041>\n";}
		if (!hideNulls) {xml += "        <unk042>" + to_string((int)data[i].unk042) + "</unk042>\n";}
		if (!hideNulls) {xml += "        <unk043>" + to_string((int)data[i].unk043) + "</unk043>\n";}
		if (!hideNulls) {xml += "        <unk044>" + to_string((int)data[i].unk044) + "</unk044>\n";}
		if (!hideNulls) {xml += "        <unk045>" + to_string((int)data[i].unk045) + "</unk045>\n";}
		if (!hideNulls) {xml += "        <unk046>" + to_string((int)data[i].unk046) + "</unk046>\n";}
		if (!hideNulls) {xml += "        <unk047>" + to_string((int)data[i].unk047) + "</unk047>\n";}
		xml += "        <set_pos_x>" + to_string(data[i].set_pos_x) + "</set_pos_x>\n";
		xml += "        <set_pos_y>" + to_string(data[i].set_pos_y) + "</set_pos_y>\n";
		xml += "        <set_pos_z>" + to_string(data[i].set_pos_z) + "</set_pos_z>\n";
		if (!hideNulls) {xml += "        <unk051>" + to_string((int)data[i].unk051) + "</unk051>\n";}
		if (!hideNulls) {xml += "        <unk052>" + to_string((int)data[i].unk052) + "</unk052>\n";}
		if (!hideNulls) {xml += "        <unk053>" + to_string((int)data[i].unk053) + "</unk053>\n";}
		if (!hideNulls) {xml += "        <unk054>" + to_string((int)data[i].unk054) + "</unk054>\n";}
		xml += "        <eff_offset_pos_x>" + to_string(data[i].eff_offset_pos_x) + "</eff_offset_pos_x>\n";
		xml += "        <eff_offset_pos_y>" + to_string(data[i].eff_offset_pos_y) + "</eff_offset_pos_y>\n";
		xml += "        <eff_offset_pos_z>" + to_string(data[i].eff_offset_pos_z) + "</eff_offset_pos_z>\n";

		//xml += "        <item_id>" + to_string(data[i].item_id) + "</item_id>\n";
		
		ss.str(std::string());
		ss << std::uppercase << TO_HEX(data[i].item_id, false, 4); // 0x0001
		xml += "        <item_id>0x" + padString(ss.str(), 4, "0") + "</item_id>\n";



		xml += "        <item_flag>" + to_string(data[i].item_flag) + "</item_flag>\n";
		xml += "        <item_num>" + to_string(data[i].item_num) + "</item_num>\n";
		xml += "        <unk058>" + to_string((int)data[i].unk058) + "</unk058>\n";
		if (!hideNulls) {xml += "        <unk059>" + to_string((int)data[i].unk059) + "</unk059>\n";}
		xml += "        <eff_type>" + to_string((int)data[i].eff_type) + "</eff_type>\n";
		xml += "        <!--ENUM: eff_type\n";
		xml += "               0: None\n";
		xml += "               1: KIRA EFF\n";
		xml += "               2: EM DROP(W)\n";
		xml += "               3: EM DROP(B)\n";
		xml += "               4: EM DROP(G)\n";
		xml += "               5: EM DROP(R)\n";
		xml += "               6: AUTO\n";
		xml += "               7: EM DROP(BIG)\n";
		xml += "               8: EM DROP(KEY)\n";
		xml += "               9: SANDGLASS\n";
		xml += "        -->\n";
		if (!hideNulls) {xml += "        <unk061>" + to_string((int)data[i].unk061) + "</unk061>\n";}
		if (!hideNulls) {xml += "        <unk062>" + to_string((int)data[i].unk062) + "</unk062>\n";}
		xml += "        <hit_area_disp>" + to_string((int)data[i].hit_area_disp) + "</hit_area_disp>\n";
		xml += "        <!--ENUM: hit_area_disp\n";
		xml += "               0: OFF\n";
		xml += "               1: ON\n";
		xml += "        -->\n";
		if (data[i].hit_flags.position_auto_off) {str = "TRUE";} else {str = "FALSE";} xml += "        <position_auto_off>" + str + "</position_auto_off>\n";
		if (data[i].hit_flags.hit_area_auto_off) {str = "TRUE";} else {str = "FALSE";} xml += "        <hit_area_auto_off>" + str + "</hit_area_auto_off>\n";
		if (data[i].hit_flags.see_check_off) {str = "TRUE";} else {str = "FALSE";} xml += "        <see_check_off>" + str + "</see_check_off>\n";
		if (!hideNulls) {if (data[i].hit_flags.flg4) {str = "TRUE";} else {str = "FALSE";} xml += "        <flg12>" + str + "</flg12>\n";}
		if (data[i].hit_flags.drop_type_shoot_and_fall) {str = "TRUE";} else {str = "FALSE";} xml += "        <drop_type>" + str + "</drop_type>\n";
		if (!hideNulls) {if (data[i].hit_flags.flg6) {str = "TRUE";} else {str = "FALSE";} xml += "        <flg14>" + str + "</flg14>\n";}
		if (data[i].hit_flags.drop_type_fall) {str = "TRUE";} else {str = "FALSE";} xml += "        <fall_type>" + str + "</fall_type>\n";
		if (data[i].hit_flags.hide_set_on) {str = "TRUE";} else {str = "FALSE";} xml += "        <hide_set_on>" + str + "</hide_set_on>\n";
		if (!hideNulls) {xml += "        <unk065>" + to_string((int)data[i].unk065) + "</unk065>\n";}
		if (!hideNulls) {xml += "        <unk066>" + to_string((int)data[i].unk066) + "</unk066>\n";}
		if (!hideNulls) {xml += "        <unk067>" + to_string((int)data[i].unk067) + "</unk067>\n";}
		xml += "        <radius>" + to_string(data[i].radius) + "</radius>\n";
		xml += "        <cone_ang_x>" + to_string(data[i].cone_ang_x) + "</cone_ang_x>\n";
		xml += "        <cone_ang_y>" + to_string(data[i].cone_ang_y) + "</cone_ang_y>\n";
		xml += "        <cone_open_angle>" + to_string(data[i].cone_open_angle) + "</cone_open_angle>\n";
		xml += "        <se_no_drop>" + to_string((int)data[i].se_no_drop) + "</se_no_drop>\n";
		xml += "        <se_no_hit>" + to_string((int)data[i].se_no_hit) + "</se_no_hit>\n";
		if (!hideNulls) {xml += "        <unk074>" + to_string((int)data[i].unk074) + "</unk074>\n";}
		if (!hideNulls) {xml += "        <unk075>" + to_string((int)data[i].unk075) + "</unk075>\n";}
		xml += "    </entry>\n";
		}

	// Close XML Root Node
	xml += "</ita>\n";

	// Save File
	bytestream s;
	s.writeFileW(file, 0, xml.size(), (char*)xml.c_str());

	}

void fmtITA::xml_import (rapidxml::xml_document<> &doc) {

	// Check Root Node
	rapidxml::xml_node<>* NODE_ITA = doc.first_node("ita");
	if (NODE_ITA == NULL) {return;}

	// Count File Nodes
	int ITA_NUM = 0;
	for (rapidxml::xml_node<>* NODE_ENTRY = NODE_ITA->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {ITA_NUM++;}

	// Exit if NO entries
	if (ITA_NUM == 0) {return;}

	// Dimension File Array
	count = ITA_NUM;
	data = std::vector<fmtITA_Entry>(ITA_NUM);

	// Loop Through Each File
	int ITA_INDEX = 0;
	std::string str;
	bool state;
	rapidxml::xml_node<>* NODE_ITEM;
	rapidxml::xml_node<>* NODE_AREA;
	rapidxml::xml_node<>* AREA_ENTRY;
	for (rapidxml::xml_node<>* NODE_ENTRY = NODE_ITA->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
		if ((NODE_AREA = NODE_ENTRY->first_node("atari")) != NULL) {
			if ((AREA_ENTRY = NODE_AREA->first_node("hasData")) != NULL) {data[ITA_INDEX].area.unk1 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("useData")) != NULL) {data[ITA_INDEX].area.unk2 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("player")) != NULL) {data[ITA_INDEX].area.unk3 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("enemy")) != NULL) {data[ITA_INDEX].area.unk4 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("unk5")) != NULL) {data[ITA_INDEX].area.unk5 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("shape")) != NULL) {data[ITA_INDEX].area.type = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("unk7")) != NULL) {data[ITA_INDEX].area.unk7 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("unk8")) != NULL) {data[ITA_INDEX].area.unk8 = ((uint8_t)convert_to<int>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos_z")) != NULL) {data[ITA_INDEX].area.pos_z = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("height")) != NULL) {data[ITA_INDEX].area.height = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("radius")) != NULL) {data[ITA_INDEX].area.radius = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos0_x")) != NULL) {data[ITA_INDEX].area.pos[0] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos0_y")) != NULL) {data[ITA_INDEX].area.pos[1] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos1_x")) != NULL) {data[ITA_INDEX].area.pos[2] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos1_y")) != NULL) {data[ITA_INDEX].area.pos[3] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos2_x")) != NULL) {data[ITA_INDEX].area.pos[4] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos2_y")) != NULL) {data[ITA_INDEX].area.pos[5] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos3_x")) != NULL) {data[ITA_INDEX].area.pos[6] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			if ((AREA_ENTRY = NODE_AREA->first_node("pos3_y")) != NULL) {data[ITA_INDEX].area.pos[7] = (convert_to<float>(std::string(AREA_ENTRY->value())));}
			}
		if ((NODE_ITEM = NODE_ENTRY->first_node("hasData")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].entry_flag.hasData = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("useData")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].entry_flag.useData = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("flg3")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].entry_flag.flg3 = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("flg4")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].entry_flag.flg4 = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("flg5")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].entry_flag.flg5 = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("flg6")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].entry_flag.flg6 = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("flg7")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].entry_flag.flg7 = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("flg8")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].entry_flag.flg8 = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk010")) != NULL) {data[ITA_INDEX].unk010 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("index")) != NULL) {data[ITA_INDEX].entry_index = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("hit_type")) != NULL) {data[ITA_INDEX].hit_type = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk013")) != NULL) {data[ITA_INDEX].unk013 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk014")) != NULL) {data[ITA_INDEX].unk014 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk015")) != NULL) {data[ITA_INDEX].unk015 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk016")) != NULL) {data[ITA_INDEX].unk016 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk017")) != NULL) {data[ITA_INDEX].unk017 = (convert_to<uint32_t>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk018")) != NULL) {data[ITA_INDEX].unk018 = (convert_to<uint32_t>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("priority")) != NULL) {data[ITA_INDEX].priority = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk026")) != NULL) {data[ITA_INDEX].unk026 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("set_wait_type")) != NULL) {data[ITA_INDEX].set_wait_type = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("set_target_no")) != NULL) {data[ITA_INDEX].set_target_no = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("hit_angle")) != NULL) {data[ITA_INDEX].hit_angle = ((int8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("open_angle")) != NULL) {data[ITA_INDEX].open_angle = ((int8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk031")) != NULL) {data[ITA_INDEX].unk031 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk032")) != NULL) {data[ITA_INDEX].unk032 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk033")) != NULL) {data[ITA_INDEX].unk033 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk034")) != NULL) {data[ITA_INDEX].unk034 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk035")) != NULL) {data[ITA_INDEX].unk035 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk036")) != NULL) {data[ITA_INDEX].unk036 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk037")) != NULL) {data[ITA_INDEX].unk037 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk038")) != NULL) {data[ITA_INDEX].unk038 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("country")) != NULL) {data[ITA_INDEX].country = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk039")) != NULL) {data[ITA_INDEX].unk039 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk040")) != NULL) {data[ITA_INDEX].unk040 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk041")) != NULL) {data[ITA_INDEX].unk041 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk042")) != NULL) {data[ITA_INDEX].unk042 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk043")) != NULL) {data[ITA_INDEX].unk043 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk044")) != NULL) {data[ITA_INDEX].unk044 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk045")) != NULL) {data[ITA_INDEX].unk045 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk046")) != NULL) {data[ITA_INDEX].unk046 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk047")) != NULL) {data[ITA_INDEX].unk047 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("set_pos_x")) != NULL) {data[ITA_INDEX].set_pos_x = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("set_pos_y")) != NULL) {data[ITA_INDEX].set_pos_y = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("set_pos_z")) != NULL) {data[ITA_INDEX].set_pos_z = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk051")) != NULL) {data[ITA_INDEX].unk051 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk052")) != NULL) {data[ITA_INDEX].unk052 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk053")) != NULL) {data[ITA_INDEX].unk053 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk054")) != NULL) {data[ITA_INDEX].unk054 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("eff_offset_pos_x")) != NULL) {data[ITA_INDEX].eff_offset_pos_x = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("eff_offset_pos_y")) != NULL) {data[ITA_INDEX].eff_offset_pos_y = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("eff_offset_pos_z")) != NULL) {data[ITA_INDEX].eff_offset_pos_z = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("item_id")) != NULL) {data[ITA_INDEX].item_id = (convert_to<uint16_t>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("item_flag")) != NULL) {data[ITA_INDEX].item_flag = (convert_to<uint16_t>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("item_num")) != NULL) {data[ITA_INDEX].item_num = (convert_to<uint16_t>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk058")) != NULL) {data[ITA_INDEX].unk058 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk059")) != NULL) {data[ITA_INDEX].unk059 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("eff_type")) != NULL) {data[ITA_INDEX].eff_type = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk061")) != NULL) {data[ITA_INDEX].unk061 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk062")) != NULL) {data[ITA_INDEX].unk062 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("hit_area_disp")) != NULL) {data[ITA_INDEX].hit_area_disp = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("position_auto_off")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].hit_flags.position_auto_off = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("hit_area_auto_off")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].hit_flags.hit_area_auto_off = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("see_check_off")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].hit_flags.see_check_off = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("flg12")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].hit_flags.flg4 = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("drop_type")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].hit_flags.drop_type_shoot_and_fall = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("flg14")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].hit_flags.flg6 = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("fall_type")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].hit_flags.drop_type_fall = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("hide_set_on")) != NULL) {if ((str = toupper(std::string(NODE_ITEM->value()))) == "FALSE" || str == "0") {state = false;} else {state = true;} data[ITA_INDEX].hit_flags.hide_set_on = state;}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk065")) != NULL) {data[ITA_INDEX].unk065 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk066")) != NULL) {data[ITA_INDEX].unk066 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk067")) != NULL) {data[ITA_INDEX].unk067 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("radius")) != NULL) {data[ITA_INDEX].radius = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("cone_ang_x")) != NULL) {data[ITA_INDEX].cone_ang_x = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("cone_ang_y")) != NULL) {data[ITA_INDEX].cone_ang_y = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("cone_open_angle")) != NULL) {data[ITA_INDEX].cone_open_angle = (convert_to<float>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("se_no_drop")) != NULL) {data[ITA_INDEX].se_no_drop = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("se_no_hit")) != NULL) {data[ITA_INDEX].se_no_hit = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk074")) != NULL) {data[ITA_INDEX].unk074 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_ENTRY->first_node("unk075")) != NULL) {data[ITA_INDEX].unk075 = ((uint8_t)convert_to<int>(std::string(NODE_ITEM->value())));}

		ITA_INDEX++;
		} // FILE NODE, END

	}
