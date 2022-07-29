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
