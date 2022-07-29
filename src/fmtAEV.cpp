#include "fmtAEV.h"


fmtAEV_Normal::fmtAEV_Normal () {
	unk820 = 0;
	unk821 = 0;
	}

void fmtAEV_Normal::read_type00 (bytestream &f) {
	unk820 = f.readUlong();
	unk821 = f.readUlong();
	}

void fmtAEV_Normal::write_type00 (bytestream &s) {
	s.writelong(unk820);
	s.writelong(unk821);
	}

void fmtAEV_Normal::write_ini () {
	ini->integer("unk820", unk820);
	ini->integer("unk821", unk821);
	}

void fmtAEV_Normal::read_ini (std::string &secname) {
	unk820 = (uint32_t)ini->get_integer(secname, "unk820");
	unk821 = (uint32_t)ini->get_integer(secname, "unk821");
	}

fmtAEV_Door::fmtAEV_Door () {
	next_pos_x = 0.0;
	next_pos_y = 0.0;
	next_pos_z = 0.0;
	next_ang_y = 0.0;
	next_stage_no = 0;
	next_room_no = 0;
	key_id = 0;
	key_flg = 0;
	unk116 = 0;
	unk117 = 0;
	unk118 = 0;
	unk119 = 0;
	next_part_no = 0;
	key_se = 0;
	open_se = 0;
	fade_eff = 0;
	}

void fmtAEV_Door::read_type01 (bytestream &f) {
	next_pos_x = f.readfloat();
	next_pos_y = f.readfloat();
	next_pos_z = f.readfloat();
	next_ang_y = f.readfloat();
	next_stage_no = f.readUbyte();
	next_room_no = f.readUbyte();
	key_id = f.readUbyte();
	key_flg = f.readUbyte();
	unk116 = f.readUbyte();
	unk117 = f.readUbyte();
	unk118 = f.readUbyte();
	unk119 = f.readUbyte();
	next_part_no = f.readUbyte();
	key_se = f.readUbyte();
	open_se = f.readUbyte();
	fade_eff = f.readUbyte();
	}

void fmtAEV_Door::write_type01 (bytestream &s) {
	s.writefloat(next_pos_x);
	s.writefloat(next_pos_y);
	s.writefloat(next_pos_z);
	s.writefloat(next_ang_y);
	s.writebyte(next_stage_no);
	s.writebyte(next_room_no);
	s.writebyte(key_id);
	s.writebyte(key_flg);
	s.writebyte(unk116);
	s.writebyte(unk117);
	s.writebyte(unk118);
	s.writebyte(unk119);
	s.writebyte(next_part_no);
	s.writebyte(key_se);
	s.writebyte(open_se);
	s.writebyte(fade_eff);
	}

void fmtAEV_Door::write_ini () {
	ini->integer("next_stage_no", next_stage_no);
	ini->integer("next_room_no", next_room_no);
	ini->integer("next_part_no", next_part_no);
	ini->vector3("next_pos", next_pos_x, next_pos_y, next_pos_z, false);
	ini->fraction("next_ang_y", (float)(next_ang_y * app->radian_to_degree));

	std::string cmt = "";
	switch (key_id) {
		case 0x00: {cmt = "DEFAULT"; break;}
		case 0x01: {cmt = "IN_LOCK_CLOSE"; break;}
		case 0x02: {cmt = "IN_LOCK_OPEN"; break;}
		default: {cmt = "Doesn't Do Anything?";}
		}
	ini->integer("key_id", key_id, cmt);
	ini->integer("key_flg", key_flg);
	ini->integer("key_se", key_se);
	ini->integer("open_se", open_se);

	switch (fade_eff) {
		case 0x00: {cmt = "NORMAL"; break;}
		case 0x01: {cmt = "FADE"; break;}
		case 0x02: {cmt = "BLACK"; break;}
		default: {cmt = "Doesn't Do Anything?";}
		}
	ini->integer("fade_eff", fade_eff, cmt);
	}

void fmtAEV_Door::read_ini (std::string &secname) {
	ini->get_vector3(secname, "next_pos", next_pos_x, next_pos_y, next_pos_z);
	next_ang_y = ini->get_fraction(secname, "next_ang_y");
	next_stage_no = (uint8_t)ini->get_integer(secname, "next_stage_no");
	next_room_no = (uint8_t)ini->get_integer(secname, "next_room_no");
	key_id = (uint8_t)ini->get_integer(secname, "key_id");
	key_flg = (uint8_t)ini->get_integer(secname, "key_flg");
	next_part_no = (uint8_t)ini->get_integer(secname, "next_part_no");
	key_se = (uint8_t)ini->get_integer(secname, "key_se");
	open_se = (uint8_t)ini->get_integer(secname, "open_se");
	fade_eff = (uint8_t)ini->get_integer(secname, "fade_eff");
	}

fmtAEV_Cut_Scene::fmtAEV_Cut_Scene () {
	unk823 = 0;
	unk824[0] = 0;
	unk824[1] = 0;
	unk824[2] = 0;
	unk825 = 0;
	}

void fmtAEV_Cut_Scene::read_type02 (bytestream &f) {
	unk823 = f.readUlong();
	unk824[0] = f.readfloat();
	unk824[1] = f.readfloat();
	unk824[2] = f.readfloat();
	unk825 = f.readUlong();
	}

void fmtAEV_Cut_Scene::write_type02 (bytestream &s) {
	s.writelong(unk823);
	s.writefloat(unk824[0]);
	s.writefloat(unk824[1]);
	s.writefloat(unk824[2]);
	s.writelong(unk825);
	}

void fmtAEV_Cut_Scene::write_ini () {
	ini->integer("unk823", unk823);
	ini->fraction("unk824_x", unk824[0]);
	ini->fraction("unk824_y", unk824[1]);
	ini->fraction("unk824_z", unk824[2]);
	ini->integer("unk825", unk825);
	}

void fmtAEV_Cut_Scene::read_ini (std::string &secname) {
	unk823 = (uint32_t)ini->get_integer(secname, "unk823");
	unk824[0] = (float)ini->get_fraction(secname, "unk824_x");
	unk824[1] = (float)ini->get_fraction(secname, "unk824_y");
	unk824[2] = (float)ini->get_fraction(secname, "unk824_z");
	unk825 = (uint32_t)ini->get_integer(secname, "unk825");
	}

fmtAEV_Flag::fmtAEV_Flag () {
	flg_id = 0;
	flg_act = 0;
	flg_no = 0;
	}

void fmtAEV_Flag::read_type04 (bytestream &f) {
	flg_id = f.readUbyte();
	flg_act = f.readUbyte();
	flg_no = f.readUshort();
	}

void fmtAEV_Flag::write_type04 (bytestream &s) {
	s.writebyte(flg_id);
	s.writebyte(flg_act);
	s.writeshort(flg_no);
	}

void fmtAEV_Flag::write_ini () {
	std::string cmt = "";
	switch (flg_id) {
		case 0x00: {cmt = "ROOM_FLG"; break;}
		case 0x01: {cmt = "ROOM_SAVE_FLG"; break;}
		case 0x02: {cmt = "SCENARIO_FLG"; break;}
		default: {cmt = "Doesn't Do Anything?";}
		}
	ini->integer("flg_id", flg_id, cmt);
	ini->integer("flg_no", flg_no);
	if (flg_act > 0) {
		ini->boolean("flg_act", true);
		}
	else {
		ini->boolean("flg_act", false);
		}
	}

void fmtAEV_Flag::read_ini (std::string &secname) {
	flg_id = (uint8_t)ini->get_integer(secname, "flg_id");
	flg_no = (uint16_t)ini->get_integer(secname, "flg_no");
	flg_act = (uint16_t)ini->get_boolean(secname, "flg_act");
	}

fmtAEV_Message::fmtAEV_Message () {
	mes_type = 0;
	mes_no = 0;
	cam_no = 0;
	se_type = 0;
	se_no = 0;
	}

void fmtAEV_Message::read_type05 (bytestream &f) {
	mes_type = f.readUshort();
	mes_no = f.readshort();
	cam_no = f.readUbyte();
	se_type = f.readUbyte();
	se_no = f.readUshort();
	}

void fmtAEV_Message::write_type05 (bytestream &s) {
	s.writeshort(mes_type);
	s.writeshort(mes_no);
	s.writebyte(cam_no);
	s.writebyte(se_type);
	s.writeshort(se_no);
	}

void fmtAEV_Message::write_ini () {
	std::string cmt;
	switch (mes_type) {
		case 0x00: {cmt = "ROOM_MES"; break;}
		case 0x01: {cmt = "COMMON_MES"; break;}
		default: {cmt = "Doesn't Do Anything?";}
		}
	ini->integer("mes_type", mes_type, cmt);
	ini->integer("mes_no", mes_no);
	ini->integer("cam_no", cam_no);
	switch (se_type) {
		case 0x00: {cmt = "SE_ROOM"; break;}
		case 0x01: {cmt = "SE_PL"; break;}
		default: {cmt = "Doesn't Do Anything?";}
		}
	ini->integer("se_type", se_type, cmt);
	ini->integer("se_no", se_no);
	}

void fmtAEV_Message::read_ini (std::string &secname) {
	mes_type = (uint16_t)ini->get_integer(secname, "mes_type");
	mes_no = (uint16_t)ini->get_integer(secname, "mes_no");
	cam_no = (uint8_t)ini->get_integer(secname, "cam_no");
	se_type = (uint8_t)ini->get_integer(secname, "se_type");
	se_no = (uint16_t)ini->get_integer(secname, "se_no");
	}

fmtAEV_Jump::fmtAEV_Jump () {
	jump_pos_x = 0.0f;
	jump_pos_y = 0.0f;
	jump_pos_z = 0.0f;
	}

void fmtAEV_Jump::read_type07 (bytestream &f) {
	jump_pos_x = f.readfloat();
	jump_pos_y = f.readfloat();
	jump_pos_z = f.readfloat();
	}

void fmtAEV_Jump::write_type07 (bytestream &s) {
	s.writefloat(jump_pos_x);
	s.writefloat(jump_pos_y);
	s.writefloat(jump_pos_z);
	}

void fmtAEV_Jump::write_ini () {
	ini->vector3("jump_pos", jump_pos_x, jump_pos_y, jump_pos_z, false);
	}

void fmtAEV_Jump::read_ini (std::string &secname) {
	ini->get_vector3(secname, "jump_pos", jump_pos_x, jump_pos_y, jump_pos_z);
	}

fmtAEV_Save::fmtAEV_Save () {
	term_no = 0;
	}

void fmtAEV_Save::read_type08 (bytestream &f) {
	term_no = f.readUlong();
	}

void fmtAEV_Save::write_type08 (bytestream &s) {
	s.writelong(term_no);
	}

void fmtAEV_Save::write_ini () {
	ini->integer("term_no", term_no);
	}

void fmtAEV_Save::read_ini (std::string &secname) {
	term_no = (uint32_t)ini->get_integer(secname, "term_no");;
	}

fmtAEV_Shadow_Display::fmtAEV_Shadow_Display () {
	shd_no = 0;
	disp_flg = 0;
	unk880 = 0;
	}

void fmtAEV_Shadow_Display::read_type09 (bytestream &f) {
	shd_no = f.readUshort();
	disp_flg = f.readUbyte();
	unk880 = f.readUbyte();
	}

void fmtAEV_Shadow_Display::write_type09 (bytestream &s) {
	s.writeshort(shd_no);
	s.writebyte(disp_flg);
	s.writebyte(unk880);
	}

void fmtAEV_Shadow_Display::write_ini () {
	ini->integer("shd_no", shd_no);
	if (disp_flg > 0) {
		ini->boolean("disp_flg", true);
		}
	else {
		ini->boolean("disp_flg", false);
		}
	}

void fmtAEV_Shadow_Display::read_ini (std::string &secname) {
	shd_no = (uint16_t)ini->get_integer(secname, "shd_no");
	if (ini->get_boolean(secname, "disp_flg")) {
		disp_flg = 1;
		}
	else {
		disp_flg = 0;
		}
	}

fmtAEV_Damage::fmtAEV_Damage () {
	damage_timer = 0;
	damage_type = 0;
	damage_flag = 0;
	unk416 = 0;
	damage_volume = 0;
	damage_angle = 0.0f;
	}

void fmtAEV_Damage::read_type0A (bytestream &f) {
	damage_timer = f.readUlong();
	damage_type = f.readUbyte();
	damage_flag = f.readUbyte();
	unk416 = f.readUshort();
	damage_volume = f.readUlong();
	damage_angle = f.readfloat();
	}

void fmtAEV_Damage::write_type0A (bytestream &s) {
	s.writelong(damage_timer);
	s.writebyte(damage_type);
	s.writebyte(damage_flag);
	s.writeshort(unk416);
	s.writelong(damage_volume);
	s.writefloat(damage_angle);
	}

void fmtAEV_Damage::write_ini () {
	ini->integer("damage_type", damage_type);
	ini->integer("damage_timer", damage_timer);
	ini->integer("damage_volume", damage_volume);
	ini->boolean("damage_die_flg", bit::get(damage_flag, 1));
	if (bit::get(damage_flag, 2)) {
		ini->boolean("damage_ang_flg", true);
		ini->fraction("damage_angle", (float)(damage_angle * app->radian_to_degree));
		}
	}

void fmtAEV_Damage::read_ini (std::string &secname) {
	damage_timer = (uint32_t)ini->get_integer(secname, "damage_timer");
	damage_type = (uint8_t)ini->get_integer(secname, "damage_type");
	damage_volume = (uint32_t)ini->get_integer(secname, "damage_volume");
	damage_flag = bit::set(damage_flag, 1, ini->get_boolean(secname, "damage_die_flg"));
	damage_flag = bit::set(damage_flag, 2, ini->get_boolean(secname, "damage_ang_flg"));
	damage_angle = (float)(ini->get_fraction(secname, "damage_angle") * app->degree_to_radian);
	}

fmtAEV_Scenario::fmtAEV_Scenario () {
	unk420 = 0;
	unk421 = 0;
	unk422 = 0;
	scr_at_flg4 = 0;
	scr_at_flg5 = 0;
	scr_at_flg6 = 0;
	scr_at_flg7 = 0;
	}

void fmtAEV_Scenario::read_type0B (bytestream &f) {
	unk420 = f.readUlong();
	unk421 = f.readUlong();
	unk422 = f.readUlong();
	scr_at_flg4 = f.readUlong();
	scr_at_flg5 = f.readUlong();
	scr_at_flg6 = f.readUlong();
	scr_at_flg7 = f.readUlong();
	}

void fmtAEV_Scenario::write_type0B (bytestream &s) {
	s.writelong(unk420);
	s.writelong(unk421);
	s.writelong(unk422);
	s.writelong(scr_at_flg4);
	s.writelong(scr_at_flg5);
	s.writelong(scr_at_flg6);
	s.writelong(scr_at_flg7);
	}

void fmtAEV_Scenario::write_ini () {
	ini->hexnumber("unk420", unk420, 8);
	ini->hexnumber("unk421", unk421, 8);
	ini->hexnumber("unk422", unk422, 8);
	ini->boolean("NO_EFF_SET", bit::get(scr_at_flg4, 3));
	ini->boolean("2m_DOWN", bit::get(scr_at_flg4, 5));
	ini->boolean("FRANCE", bit::get(scr_at_flg4, 6));
	ini->boolean("CLIFF", bit::get(scr_at_flg4, 12));
	ini->boolean("2m_UP", bit::get(scr_at_flg4, 13));
	ini->boolean("1m_DOWN", bit::get(scr_at_flg4, 14));
	ini->boolean("EM_NOHIT", bit::get(scr_at_flg4, 15));
	ini->boolean("FALL", bit::get(scr_at_flg4, 21));
	ini->boolean("1m_UP", bit::get(scr_at_flg4, 22));
	ini->boolean("PL_NO_HIT", bit::get(scr_at_flg4, 23));
	ini->boolean("SEE_NOHIT", bit::get(scr_at_flg4, 24));
	ini->boolean("NO_EFF_SET_2", bit::get(scr_at_flg4, 7));
	ini->boolean("EAT_MIDDLE_NOHIT", bit::get(scr_at_flg4, 15));
	ini->boolean("EAT_SMALL_NOHIT", bit::get(scr_at_flg4, 23));
	ini->boolean("EAT_SMALL_NOHIT", bit::get(scr_at_flg4, 23));
	switch (scr_at_flg5) {
		case 0x00000000: {ini->integer("EAT_EFF_BIT", 0); break;}
		case 0x00008000: {ini->integer("EAT_EFF_BIT", 1); break;}
		case 0x00080000: {ini->integer("EAT_EFF_BIT", 2); break;}
		case 0x00808000: {ini->integer("EAT_EFF_BIT", 3); break;}
		case 0x80000000: {ini->integer("EAT_EFF_BIT", 4); break;}
		case 0x80008000: {ini->integer("EAT_EFF_BIT", 5); break;}
		case 0x80800000: {ini->integer("EAT_EFF_BIT", 6); break;}
		case 0x80808000: {ini->integer("EAT_EFF_BIT", 7); break;}
		}
	ini->boolean("EAT_NO_SET", bit::get(scr_at_flg6, 1));
	ini->boolean("SAT_NO_SET", bit::get(scr_at_flg6, 2));
	ini->boolean("ROUTE_NOHIT", bit::get(scr_at_flg6, 3));
	ini->boolean("F_BOX", bit::get(scr_at_flg7, 9));
	ini->boolean("F_FLOOR", bit::get(scr_at_flg7, 10));
	}

void fmtAEV_Scenario::read_ini (std::string &secname) {
	unk420 = (uint32_t)ini->get_integer(secname, "unk420");
	unk421 = (uint32_t)ini->get_integer(secname, "unk421");
	unk422 = (uint32_t)ini->get_integer(secname, "unk422");
	unsigned int eat_eff_bit = (unsigned int)ini->get_integer(secname, "EAT_EFF_BIT");
	switch (eat_eff_bit) {
		case 0: {scr_at_flg5 = 0x00000000; break;}
		case 1: {scr_at_flg5 = 0x00008000; break;}
		case 2: {scr_at_flg5 = 0x00080000; break;}
		case 3: {scr_at_flg5 = 0x00808000; break;}
		case 4: {scr_at_flg5 = 0x80000000; break;}
		case 5: {scr_at_flg5 = 0x80008000; break;}
		case 6: {scr_at_flg5 = 0x80800000; break;}
		case 7: {scr_at_flg5 = 0x80808000; break;}
		}

	scr_at_flg4 = bit::set(scr_at_flg4,  3, ini->get_boolean(secname, "NO_EFF_SET"));
	scr_at_flg4 = bit::set(scr_at_flg4,  5, ini->get_boolean(secname, "2m_DOWN"));
	scr_at_flg4 = bit::set(scr_at_flg4,  6, ini->get_boolean(secname, "FRANCE"));
	scr_at_flg4 = bit::set(scr_at_flg4, 12, ini->get_boolean(secname, "CLIFF"));
	scr_at_flg4 = bit::set(scr_at_flg4, 13, ini->get_boolean(secname, "2m_UP"));
	scr_at_flg4 = bit::set(scr_at_flg4, 14, ini->get_boolean(secname, "1m_DOWN"));
	scr_at_flg4 = bit::set(scr_at_flg4, 15, ini->get_boolean(secname, "EM_NOHIT"));
	scr_at_flg4 = bit::set(scr_at_flg4, 21, ini->get_boolean(secname, "FALL"));
	scr_at_flg4 = bit::set(scr_at_flg4, 22, ini->get_boolean(secname, "1m_UP"));
	scr_at_flg4 = bit::set(scr_at_flg4, 23, ini->get_boolean(secname, "PL_NO_HIT"));
	scr_at_flg4 = bit::set(scr_at_flg4, 24, ini->get_boolean(secname, "SEE_NOHIT"));
	scr_at_flg4 = bit::set(scr_at_flg4,  7, ini->get_boolean(secname, "NO_EFF_SET_2"));
	scr_at_flg4 = bit::set(scr_at_flg4, 15, ini->get_boolean(secname, "EAT_MIDDLE_NOHIT"));
	scr_at_flg4 = bit::set(scr_at_flg4, 23, ini->get_boolean(secname, "EAT_SMALL_NOHIT"));
	scr_at_flg6 = bit::set(scr_at_flg6,  1, ini->get_boolean(secname, "EAT_NO_SET"));
	scr_at_flg6 = bit::set(scr_at_flg6,  2, ini->get_boolean(secname, "SAT_NO_SET"));
	scr_at_flg6 = bit::set(scr_at_flg6,  3, ini->get_boolean(secname, "ROUTE_NOHIT"));
	scr_at_flg7 = bit::set(scr_at_flg7,  9, ini->get_boolean(secname, "F_BOX"));
	scr_at_flg7 = bit::set(scr_at_flg7, 10, ini->get_boolean(secname, "F_FLOOR"));
	}

fmtAEV_View_Control::fmtAEV_View_Control () {
	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;
	ang_y = 0.0f;
	pos_on = 0;
	type = 0;
	unk887 = 0;
	unk888 = 0;
	radius = 0.0f;
	out_range = 0.0f;
	}

void fmtAEV_View_Control::read_type0C (bytestream &f) {
	pos[0] = f.readfloat();
	pos[1] = f.readfloat();
	pos[2] = f.readfloat();
	ang_y = f.readfloat();
	pos_on = f.readUbyte();
	type = f.readUbyte();
	unk887 = f.readUbyte();
	unk888 = f.readUbyte();
	radius = f.readfloat();
	out_range = f.readfloat();
	}

void fmtAEV_View_Control::write_type0C (bytestream &s) {
	s.writefloat(pos[0]);
	s.writefloat(pos[1]);
	s.writefloat(pos[2]);
	s.writefloat(ang_y);
	s.writebyte(pos_on);
	s.writebyte(type);
	s.writebyte(unk887);
	s.writebyte(unk888);
	s.writefloat(radius);
	s.writefloat(out_range); // offset back
	}

void fmtAEV_View_Control::write_ini () {

	ini->integer("type", type);
	if (pos_on > 0) {
		ini->boolean("pos_set", true);
		}
	else
		{
		ini->boolean("pos_set", false);
		}
	
	if (pos_on > 0) {
		ini->vector3("position", pos[0], pos[1], pos[2]);
		}
	ini->fraction("angle_y", ang_y);
	ini->fraction("radius", (float)(radius * app->radian_to_degree));
	ini->fraction("out_range", (float)(out_range * app->radian_to_degree));

	}

void fmtAEV_View_Control::read_ini (std::string &secname) {
	ini->get_vector3(secname, "position", pos[0], pos[1], pos[2]);
	ang_y = ini->get_fraction(secname, "ang_y");
	pos_on = 0;
	if (ini->get_boolean(secname, "pos_on")) {
		pos_on = 1;
		}
	type = (uint8_t)ini->get_integer(secname, "type");
	unk887 = (uint8_t)ini->get_integer(secname, "unk887");
	unk888 = (uint8_t)ini->get_integer(secname, "unk888");
	radius = (float)(ini->get_fraction(secname, "radius") * app->degree_to_radian);
	out_range = (float)(ini->get_fraction(secname, "out_range") * app->degree_to_radian);
	}

fmtAEV_Field_Info::fmtAEV_Field_Info () {
	field_id = 0;
	}

void fmtAEV_Field_Info::read_type0D (bytestream &f) {
	field_id = f.readUlong();
	}

void fmtAEV_Field_Info::write_type0D (bytestream &s) {
	s.writelong(field_id);
	}

void fmtAEV_Field_Info::write_ini () {
	ini->integer("field_id", field_id);
	}

void fmtAEV_Field_Info::read_ini (std::string &secname) {
	field_id = (uint32_t)ini->get_integer(secname, "field_id");
	}

fmtAEV_Ladder::fmtAEV_Ladder () {
	ladder_pos[0] = 0.0f;
	ladder_pos[1] = 0.0f;
	ladder_pos[2] = 0.0f;
	ladder_ang = 0.0f;
	ladder_height = 0;
	unk663 = 0;
	ladder_pos_on = 0;
	cam_no1 = 0;
	cam_no2 = 0;
	cam_no3 = 0;
	}

void fmtAEV_Ladder::read_type10 (bytestream &f, bool re4_2007) {
	ladder_pos[0] = f.readfloat();
	ladder_pos[1] = f.readfloat();
	ladder_pos[2] = f.readfloat();
	if (re4_2007) {f.readUlong();} // 1.0
	ladder_ang = f.readfloat();
	ladder_height = f.readbyte();// * METERS_TO_MILLIMETERS
	unk663 = f.readUbyte();
	ladder_pos_on = f.readUbyte();
	cam_no1 = f.readUbyte();
	cam_no2 = f.readUbyte();
	cam_no3 = f.readUbyte();
	}

void fmtAEV_Ladder::write_type10 (bytestream &s, bool re4_2007) {
	s.writefloat(ladder_pos[0]);
	s.writefloat(ladder_pos[1]);
	s.writefloat(ladder_pos[2]);
	if (re4_2007) {s.writelong(0x0000803F);}
	s.writefloat(ladder_ang);
	s.writebyte(ladder_height);// / METERS_TO_MILLIMETERS
	s.writebyte(unk663);
	s.writebyte(ladder_pos_on);
	s.writebyte(cam_no1);
	s.writebyte(cam_no2);
	s.writebyte(cam_no3);
	}

void fmtAEV_Ladder::write_ini () {
	if (ladder_pos_on > 0) {
		ini->boolean("ladder_pos_on", true);
		}
	else {
		ini->boolean("ladder_pos_on", false);
		}
	
	if (ladder_pos_on) {
		ini->vector3("ladder_pos", ladder_pos[0], ladder_pos[1], ladder_pos[2], false);
		}
	ini->fraction("ladder_ang", (float)(ladder_ang * app->radian_to_degree));
	ini->integer("ladder_height", ladder_height, "Meters");
	ini->integer("cam_no1", cam_no1);
	ini->integer("cam_no2", cam_no2);
	ini->integer("cam_no3", cam_no3);
	}

void fmtAEV_Ladder::read_ini (std::string &secname) {
	ini->get_vector3(secname, "ladder_pos", ladder_pos[0], ladder_pos[1], ladder_pos[2]);
	ladder_ang = ini->get_fraction(secname, "ladder_ang");
	ladder_height = (uint8_t)ini->get_integer(secname, "ladder_height");
	unk663 = (uint8_t)ini->get_integer(secname, "unk663");
	ladder_pos_on = 0;
	if (ini->get_boolean(secname, "ladder_pos_on")) {
		ladder_pos_on = 1;
		}
	cam_no1 = (uint8_t)ini->get_integer(secname, "cam_no1");
	cam_no2 = (uint8_t)ini->get_integer(secname, "cam_no2");
	cam_no3 = (uint8_t)ini->get_integer(secname, "cam_no3");
	}

fmtAEV_Use::fmtAEV_Use () {
	use_id = 0;
	}

void fmtAEV_Use::read_type11 (bytestream &f) {
	use_id = f.readUlong();
	}

void fmtAEV_Use::write_type11 (bytestream &s) {
	s.writelong(use_id);
	}

void fmtAEV_Use::write_ini () {
	ini->integer("use_id", use_id);
	}

void fmtAEV_Use::read_ini (std::string &secname) {
	use_id = (uint32_t)ini->get_integer(secname, "use_id");
	}

fmtAEV_Hide::fmtAEV_Hide () {
	hide_type = 0;
	hide_pos_on = 0;
	hide_area_on = 0;
	unk772 = 0;
	hide_area[0] = 0.0f;
	hide_area[1] = 0.0f;
	hide_area[2] = 0.0f;
	hide_area[3] = 0.0f;
	hide_area[4] = 0.0f;
	hide_area[5] = 0.0f;
	hide_area[6] = 0.0f;
	hide_area[7] = 0.0f;
	hide_pos[0] = 0.0f;
	hide_pos[1] = 0.0f;
	hide_pos[2] = 0.0f;
	unk774 = 0;
	cam_no = 0;
	}

void fmtAEV_Hide::read_type12 (bytestream &f, bool re4_2007) {
	if (!re4_2007) {
		hide_type = f.readUbyte();
		hide_pos_on = f.readUbyte();
		hide_area_on = f.readUbyte();
		unk772 = f.readUbyte();
		hide_area[0] = f.readfloat();
		hide_area[1] = f.readfloat();
		hide_area[2] = f.readfloat();
		hide_area[3] = f.readfloat();
		hide_area[4] = f.readfloat();
		hide_area[5] = f.readfloat();
		hide_area[6] = f.readfloat();
		hide_area[7] = f.readfloat();
		hide_pos[0] = f.readfloat();
		hide_pos[1] = f.readfloat();
		hide_pos[2] = f.readfloat();
		unk774 = f.readUlong();
		cam_no = f.readUlong();
		}
	else {
		hide_pos[0] = f.readfloat();
		hide_pos[1] = f.readfloat();
		hide_pos[2] = f.readfloat();
		if (re4_2007) {f.readUlong();} // 1.0
		hide_type = f.readUbyte();
		hide_pos_on = f.readUbyte();
		hide_area_on = f.readUbyte();
		unk772 = f.readUbyte();
		hide_area[0] = f.readfloat();
		hide_area[1] = f.readfloat();
		hide_area[2] = f.readfloat();
		hide_area[3] = f.readfloat();
		hide_area[4] = f.readfloat();
		hide_area[5] = f.readfloat();
		hide_area[6] = f.readfloat();
		hide_area[7] = f.readfloat();
		unk774 = f.readUlong();
		cam_no = f.readUlong();
		}
	}

void fmtAEV_Hide::write_type12 (bytestream &s, bool re4_2007) {
	if (!re4_2007) {
		s.writebyte(hide_type);
		s.writebyte(hide_pos_on);
		s.writebyte(hide_area_on);
		s.writebyte(unk772);
		s.writefloat(hide_area[0]);
		s.writefloat(hide_area[1]);
		s.writefloat(hide_area[2]);
		s.writefloat(hide_area[3]);
		s.writefloat(hide_area[4]);
		s.writefloat(hide_area[5]);
		s.writefloat(hide_area[6]);
		s.writefloat(hide_area[7]);
		s.writefloat(hide_pos[0]);
		s.writefloat(hide_pos[1]);
		s.writefloat(hide_pos[2]);
		s.writelong(unk774);
		s.writelong(cam_no);
		}
	else {
		s.writefloat(hide_pos[0]);
		s.writefloat(hide_pos[1]);
		s.writefloat(hide_pos[2]);
		if (re4_2007) {s.writelong(0x0000803F);}
		s.writebyte(hide_type);
		s.writebyte(hide_pos_on);
		s.writebyte(hide_area_on);
		s.writebyte(unk772);
		s.writefloat(hide_area[0]);
		s.writefloat(hide_area[1]);
		s.writefloat(hide_area[2]);
		s.writefloat(hide_area[3]);
		s.writefloat(hide_area[4]);
		s.writefloat(hide_area[5]);
		s.writefloat(hide_area[6]);
		s.writefloat(hide_area[7]);
		s.writelong(unk774);
		s.writelong(cam_no);
		}
	}

void fmtAEV_Hide::write_ini () {
	ini->integer("hide_type", hide_type);
	if (hide_pos_on > 0) {
		ini->boolean("hide_pos_on", true);
		} 
	else {
		ini->boolean("hide_pos_on", false);
		}
	
	if (hide_pos_on > 0) {
		ini->vector3("hide_pos", hide_pos[0], hide_pos[1], hide_pos[2]);
		}
	if (hide_area_on > 0) {
		ini->boolean("hide_area_on", true);
		}
	else {
		ini->boolean("hide_area_on", false);
		}
	
	if (hide_area_on > 0) {
		ini->vector2("hide_area_corner0_pos", hide_area[0], hide_area[1], false);
		ini->vector2("hide_area_corner1_pos", hide_area[2], hide_area[3], false);
		ini->vector2("hide_area_corner2_pos", hide_area[4], hide_area[5], false);
		ini->vector2("hide_area_corner3_pos", hide_area[6], hide_area[7], false);
		}
	ini->integer("cam_no", cam_no);
	}

void fmtAEV_Hide::read_ini (std::string &secname) {
	hide_pos_on = 0;
	if (ini->get_boolean(secname, "hide_pos_on")) {
		hide_pos_on = 1;
		}
	hide_area_on = 0;
	if (ini->get_boolean(secname, "hide_area_on")) {
		hide_area_on = 1;
		}
	hide_type = (uint8_t)ini->get_integer(secname, "hide_type");
	unk772 = (uint8_t)ini->get_integer(secname, "unk772");
	ini->get_vector2(secname, "hide_area_corner0_pos", hide_area[0], hide_area[1]);
	ini->get_vector2(secname, "hide_area_corner1_pos", hide_area[2], hide_area[3]);
	ini->get_vector2(secname, "hide_area_corner2_pos", hide_area[4], hide_area[5]);
	ini->get_vector2(secname, "hide_area_corner3_pos", hide_area[6], hide_area[7]);
	ini->get_vector3(secname, "hide_pos", hide_pos[0], hide_pos[1], hide_pos[2]);
	unk774 = (uint32_t)ini->get_integer(secname, "unk774");
	cam_no = (uint32_t)ini->get_integer(secname, "cam_no");
	}

fmtAEV_Jump_Position::fmtAEV_Jump_Position () {
	jump_pos[0] = 0.0f;
	jump_pos[1] = 0.0f;
	jump_pos[2] = 0.0f;
	jump_ang = 0.0f;
	}

void fmtAEV_Jump_Position::read_type13 (bytestream &f) {
	jump_pos[0] = f.readfloat();
	jump_pos[1] = f.readfloat();
	jump_pos[2] = f.readfloat();
	jump_ang = f.readfloat();
	}

void fmtAEV_Jump_Position::write_type13 (bytestream &s) {
	s.writefloat(jump_pos[0]);
	s.writefloat(jump_pos[1]);
	s.writefloat(jump_pos[2]);
	s.writefloat(jump_ang);
	}

void fmtAEV_Jump_Position::write_ini () {
	ini->vector3("jump_pos", jump_pos[0], jump_pos[1], jump_pos[2], false);
	ini->fraction("jump_ang", (float)(jump_ang * app->radian_to_degree));
	}

void fmtAEV_Jump_Position::read_ini (std::string &secname) {
	ini->get_vector3(secname, "jump_pos", jump_pos[0], jump_pos[1], jump_pos[2]);
	jump_ang = (float)(ini->get_fraction(secname, "jump_ang") * app->degree_to_radian);
	}

fmtAEV_Grapple::fmtAEV_Grapple () {
	ShotPoint[0] = 0.0;
	ShotPoint[1] = 0.0;
	ShotPoint[2] = 0.0;
	DestinationPoint[0] = 0.0;
	DestinationPoint[1] = 0.0;
	DestinationPoint[2] = 0.0;
	CameraParameter[0] = 0.0;
	CameraParameter[1] = 0.0;
	CameraParameter[2] = 0.0;
	CameraAngle = 0.0;
	unk810 = 0;
	unk811 = 0;
	unk812 = 0;
	unk813 = 0;
	}

void fmtAEV_Grapple::read_type15 (bytestream &f, bool re4_2007) {
	if (!re4_2007) {
		ShotPoint[0] = f.readfloat();
		ShotPoint[1] = f.readfloat();
		ShotPoint[2] = f.readfloat();
		DestinationPoint[0] = f.readfloat();
		DestinationPoint[1] = f.readfloat();
		DestinationPoint[2] = f.readfloat();
		CameraParameter[0] = f.readfloat();
		CameraParameter[1] = f.readfloat();
		CameraParameter[2] = f.readfloat();
		CameraAngle = f.readfloat();
		unk810 = f.readUbyte();
		unk811 = f.readUbyte();
		unk812 = f.readUbyte();
		unk813 = f.readUbyte();

		}
	else {

		ShotPoint[0] = f.readfloat();
		ShotPoint[1] = f.readfloat();
		ShotPoint[2] = f.readfloat();
		if (re4_2007) {f.readUlong();} // 1.0
		DestinationPoint[0] = f.readfloat();
		DestinationPoint[1] = f.readfloat();
		DestinationPoint[2] = f.readfloat();
		if (re4_2007) {f.readUlong();} // 1.0
		CameraParameter[0] = f.readfloat();
		CameraParameter[1] = f.readfloat();
		CameraParameter[2] = f.readfloat();
		if (re4_2007) {f.readUlong();} // 1.0
		CameraAngle = f.readfloat();
		unk810 = f.readUbyte();
		unk811 = f.readUbyte();
		unk812 = f.readUbyte();
		unk813 = f.readUbyte();

		}
	}

void fmtAEV_Grapple::write_type15 (bytestream &s, bool re4_2007) {
	if (!re4_2007) {
		s.writefloat(ShotPoint[0]);
		s.writefloat(ShotPoint[1]);
		s.writefloat(ShotPoint[2]);
		s.writefloat(DestinationPoint[0]);
		s.writefloat(DestinationPoint[1]);
		s.writefloat(DestinationPoint[2]);
		s.writefloat(CameraParameter[0]);
		s.writefloat(CameraParameter[1]);
		s.writefloat(CameraParameter[2]);
		s.writefloat(CameraAngle);
		s.writebyte(unk810);
		s.writebyte(unk811);
		s.writebyte(unk812);
		s.writebyte(unk813);

		}
	else {
		s.writefloat(ShotPoint[0]);
		s.writefloat(ShotPoint[1]);
		s.writefloat(ShotPoint[2]);
		if (re4_2007) {s.writelong(0x0000803F);}
		s.writefloat(DestinationPoint[0]);
		s.writefloat(DestinationPoint[1]);
		s.writefloat(DestinationPoint[2]);
		if (re4_2007) {s.writelong(0x0000803F);}
		s.writefloat(CameraParameter[0]);
		s.writefloat(CameraParameter[1]);
		s.writefloat(CameraParameter[2]);
		if (re4_2007) {s.writelong(0x0000803F);}
		s.writefloat(CameraAngle);
		s.writebyte(unk810);
		s.writebyte(unk811);
		s.writebyte(unk812);
		s.writebyte(unk813);

		}
	}

void fmtAEV_Grapple::write_ini () {
	ini->vector3("hook_pos", ShotPoint[0], ShotPoint[1], ShotPoint[2], false);
	ini->vector3("jump_pos", DestinationPoint[0], DestinationPoint[1], DestinationPoint[2], false);
	ini->vector3("cam_pos", CameraParameter[0], CameraParameter[1], CameraParameter[2], false);
	ini->fraction("cam_ang", (float)(CameraAngle * app->radian_to_degree));
	}

void fmtAEV_Grapple::read_ini (std::string &secname) {
	ini->get_vector3(secname, "hook_pos", ShotPoint[0], ShotPoint[1], ShotPoint[2]);
	ini->get_vector3(secname, "jump_pos", DestinationPoint[0], DestinationPoint[1], DestinationPoint[2]);
	ini->get_vector3(secname, "cam_pos", CameraParameter[0], CameraParameter[1], CameraParameter[2]);
	CameraAngle = ini->get_fraction(secname, "cam_ang");
	}

void fmtAEV_Region::clear () {
	area.clear();
	unk016 = 3;
	type = 0;
	index = 0;
	hit_type = 0;
	trigger_type = 0;
	target_type = 0;
	unk021 = 0;
	unk022 = 0;
	unk023 = 0;
	unk024 = 0;
	priority = 0;
	unk025b = 0;
	unk025c = 0;
	unk025d = 0;
	hit_angle = 0;
	open_angle = 0;
	action_type = 0;
	unk026 = 0;
	unk027 = 0;
	unk028 = 0;
	unk029 = 0;
	msg_flag = 0;
	msg_type = 0;
	unk030 = 0;
	unk031 = 0;
//	if (data_type00 != NULL) {delete data_type00; data_type00 = NULL;}
//	if (data_type01 != NULL) {delete data_type01; data_type01 = NULL;}
//	if (data_type02 != NULL) {delete data_type02; data_type02 = NULL;}
//	if (data_type04 != NULL) {delete data_type04; data_type04 = NULL;}
//	if (data_type05 != NULL) {delete data_type05; data_type05 = NULL;}
//	if (data_type07 != NULL) {delete data_type07; data_type07 = NULL;}
//	if (data_type08 != NULL) {delete data_type08; data_type08 = NULL;}
//	if (data_type09 != NULL) {delete data_type09; data_type09 = NULL;}
//	if (data_type0A != NULL) {delete data_type0A; data_type0A = NULL;}
//	if (data_type0B != NULL) {delete data_type0B; data_type0B = NULL;}
//	if (data_type0C != NULL) {delete data_type0C; data_type0C = NULL;}
//	if (data_type0D != NULL) {delete data_type0D; data_type0D = NULL;}
//	if (data_type10 != NULL) {delete data_type10; data_type10 = NULL;}
//	if (data_type11 != NULL) {delete data_type11; data_type11 = NULL;}
//	if (data_type12 != NULL) {delete data_type12; data_type12 = NULL;}
//	if (data_type13 != NULL) {delete data_type13; data_type13 = NULL;}
//	if (data_type15 != NULL) {delete data_type15; data_type15 = NULL;}
	}

fmtAEV_Region::fmtAEV_Region () {
	area.clear();
	unk016 = 3;
	type = 0;
	index = 0;
	hit_type = 0;
	trigger_type = 0;
	target_type = 0;
	unk021 = 0;
	unk022 = 0;
	unk023 = 0;
	unk024 = 0;
	priority = 0;
	unk025b = 0;
	unk025c = 0;
	unk025d = 0;
	hit_angle = 0;
	open_angle = 45;
	action_type = 0;
	unk026 = 0;
	unk027 = 0;
	unk028 = 0;
	unk029 = 0;
	msg_flag = 0;
	msg_type = 0;
	unk030 = 0;
	unk031 = 0;

	// create a char* array of 64bytes to write the rest of the AEV data to
	//data.resize(64);
//	data_type00 = NULL;
//	data_type01 = NULL;
//	data_type02 = NULL;
//	data_type04 = NULL;
//	data_type05 = NULL;
//	data_type07 = NULL;
//	data_type08 = NULL;
//	data_type09 = NULL;
//	data_type0A = NULL;
//	data_type0B = NULL;
//	data_type0C = NULL;
//	data_type0D = NULL;
//	data_type10 = NULL;
//	data_type11 = NULL;
//	data_type12 = NULL;
//	data_type13 = NULL;
//	data_type15 = NULL;
	}

fmtAEV_Region::~fmtAEV_Region () {
	//data.close();
//	if (data_type00 != NULL) {delete data_type00;}
//	if (data_type01 != NULL) {delete data_type01;}
//	if (data_type02 != NULL) {delete data_type02;}
//	if (data_type04 != NULL) {delete data_type04;}
//	if (data_type05 != NULL) {delete data_type05;}
//	if (data_type07 != NULL) {delete data_type07;}
//	if (data_type08 != NULL) {delete data_type08;}
//	if (data_type09 != NULL) {delete data_type09;}
//	if (data_type0A != NULL) {delete data_type0A;}
//	if (data_type0B != NULL) {delete data_type0B;}
//	if (data_type0C != NULL) {delete data_type0C;}
//	if (data_type0D != NULL) {delete data_type0D;}
//	if (data_type10 != NULL) {delete data_type10;}
//	if (data_type11 != NULL) {delete data_type11;}
//	if (data_type12 != NULL) {delete data_type12;}
//	if (data_type13 != NULL) {delete data_type13;}
//	if (data_type15 != NULL) {delete data_type15;}
	}

void fmtAEV_Region::read_region (bytestream &f, bool re4_2007) {

	// 52 bytes
	area.read_area(f);

	// 40 bytes
	unk016 = f.readUbyte();
	type = f.readUbyte();
	index = f.readUbyte();
	hit_type = f.readUbyte();
	trigger_type = f.readUbyte();
	target_type = f.readUbyte();
	unk021 = f.readUbyte();
	unk022 = f.readUbyte();
	unk023 = f.readUlong();
	unk024 = f.readUlong();
	priority = f.readUbyte();
	unk025b = f.readUbyte();
	unk025c = f.readUbyte();
	unk025d = f.readUbyte();
	hit_angle = f.readbyte();
	open_angle = f.readUbyte();
	action_type = f.readUbyte();
	unk026 = f.readUbyte();
	unk027 = f.readUlong();
	unk028 = f.readUbyte();
	unk029 = f.readUbyte();
	msg_flag = f.readUbyte();
	msg_type = f.readUbyte();
	unk030 = f.readUlong();
	unk031 = f.readUlong();

	if (re4_2007) {f.readUlong();} // Skip 4 Bytes
	size_t p = f.tell();
	// read the 64bytes from the aev into a char* array
	//data.copy(f.stream, 64, p);

	switch (type) {
		case 0x00: { 		// NORMAL
//			if (data_type00 != NULL) {delete data_type00;}
//			data_type00 = new fmtAEV_Normal;
			data_type00.read_type00(f);
			break;
			}
		case 0x01: { 			// DOOR
//			if (data_type01 != NULL) {delete data_type01;}
//			data_type01 = new fmtAEV_Door;
			data_type01.read_type01(f);
			break;
			}
		case 0x02: { 		// EXEC
//			if (data_type02 != NULL) {delete data_type02;}
//			data_type02 = new fmtAEV_Cut_Scene;
			data_type02.read_type02(f);
			break;
			}
		case 0x04: { 			// FLAG
//			if (data_type04 != NULL) {delete data_type04;}
//			data_type04 = new fmtAEV_Flag;
			data_type04.read_type04(f);
			break;
			}
		case 0x05: { 			// MESSAGE
//			if (data_type05 != NULL) {delete data_type05;}
//			data_type05 = new fmtAEV_Message;
			data_type05.read_type05(f);
			break;
			}
		//case 0x06: {break;}										// PLANTER
		case 0x07: {// JUMP
//			if (data_type07 != NULL) {delete data_type07;}
//			data_type07 = new fmtAEV_Jump;
			data_type07.read_type07(f);
			break;
			}
		case 0x08: { 			// SAVE
//			if (data_type08 != NULL) {delete data_type08;}
//			data_type08 = new fmtAEV_Save;
			data_type08.read_type08(f);
			break;
			}
		case 0x09: { 			// SHD_DISP
//			if (data_type09 != NULL) {delete data_type09;}
//			data_type09 = new fmtAEV_Shadow_Display;
			data_type09.read_type09(f);
			break;
			}
		case 0x0A: { 		// DAMAGE
//			if (data_type0A != NULL) {delete data_type0A;}
//			data_type0A = new fmtAEV_Damage;
			data_type0A.read_type0A(f);
			break;
			}
		case 0x0B: { 		// SCR_AT
//			if (data_type0B != NULL) {delete data_type0B;}
//			data_type0B = new fmtAEV_Scenario;
			data_type0B.read_type0B(f);
			break;
			}
		case 0x0C: { 		// VIEW CONTROL
//			if (data_type0C != NULL) {delete data_type0C;}
//			data_type0C = new fmtAEV_View_Control;
			data_type0C.read_type0C(f);
			break;
			}											// VIEW_CTRL
		case 0x0D: { 		// FIELD_INFO
//			if (data_type0D != NULL) {delete data_type0D;}
//			data_type0D = new fmtAEV_Field_Info;
			data_type0D.read_type0D(f);
			break;
			}
		//case 0x0E: {break;} //data_type0E->read_type0E(f); break;} 	// STOOP
		//case 0x0F: {break;} 											// SMALL_KEY
		case 0x10: { 			// LADDER
//			if (data_type10 != NULL) {delete data_type10;}
//			data_type10 = new fmtAEV_Ladder;
			data_type10.read_type10(f, re4_2007);
			break;
			}
		case 0x11: { 			// USE
//			if (data_type11 != NULL) {delete data_type11;}
//			data_type11 = new fmtAEV_Use;
			data_type11.read_type11(f);
			break;
			}
		case 0x12: { 			// HIDE
//			if (data_type12 != NULL) {delete data_type12;}
//			data_type12 = new fmtAEV_Hide;
			data_type12.read_type12(f, re4_2007);
			break;
			}
		case 0x13: { 			// POS_JUMP
//			if (data_type13 != NULL) {delete data_type13;}
//			data_type13 = new fmtAEV_Jump_Position;
			data_type13.read_type13(f);
			break;
			}
		case 0x15: { 			// GRAPPLE HOOK
//			if (data_type15 != NULL) {delete data_type15;}
//			data_type15 = new fmtAEV_Grapple;
			data_type15.read_type15(f, re4_2007);
			break;
			}

		}

	f.seek(p + 64);
	}

void fmtAEV_Region::write_region (bytestream &s, bool re4_2007) {
	area.write_area(s);
	s.writebyte(unk016);
	s.writebyte(type);
	s.writebyte(index);
	s.writebyte(hit_type);
	s.writebyte(trigger_type);
	s.writebyte(target_type);
	s.writebyte(unk021);
	s.writebyte(unk022);
	s.writelong(unk023);
	s.writelong(unk024);
	s.writebyte(priority);
	s.writebyte(unk025b);
	s.writebyte(unk025c);
	s.writebyte(unk025d);
	s.writebyte(hit_angle);
	s.writebyte(open_angle);
	s.writebyte(action_type);
	s.writebyte(unk026);
	s.writelong(unk027);
	s.writebyte(unk028);
	s.writebyte(unk029);
	s.writebyte(msg_flag);
	s.writebyte(msg_type);
	s.writelong(unk030);
	s.writelong(unk031);


	if (re4_2007) {s.writelong(0);}
	// copy back the 64byes from our char* array back to the file buffer
	//s.copy(data.stream, 64, 0, s.tell());
	size_t p = s.tell();

	switch (type) {
		case 0x00: {data_type00.write_type00(s); break;} 		// NORMAL
		case 0x01: {data_type01.write_type01(s); break;} 			// DOOR
		case 0x02: {data_type02.write_type02(s); break;} 		// EXEC
		case 0x04: {data_type04.write_type04(s); break;} 			// FLAG
		case 0x05: {data_type05.write_type05(s); break;} 			// MESSAGE
		//case 0x06: {break;}										// PLANTER
		case 0x07: {data_type07.write_type07(s); break;}// JUMP
		case 0x08: {data_type08.write_type08(s); break;} 			// SAVE
		case 0x09: {data_type09.write_type09(s); break;} 			// SHD_DISP
		case 0x0A: {data_type0A.write_type0A(s); break;} 		// DAMAGE
		case 0x0B: {data_type0B.write_type0B(s); break;} 		// SCR_AT
		case 0x0C: {data_type0C.write_type0C(s); break;}			 		// VIEW CONTROL								// VIEW_CTRL
		case 0x0D: {data_type0D.write_type0D(s); break;} 		// FIELD_INFO
		//case 0x0E: {break;} //data_type0E->write_type0E(s); break;} 	// STOOP
		//case 0x0F: {break;} 											// SMALL_KEY
		case 0x10: {data_type10.write_type10(s, re4_2007); break;} 			// LADDER
		case 0x11: {data_type11.write_type11(s); break;} 			// USE
		case 0x12: {data_type12.write_type12(s, re4_2007); break;} 			// HIDE
		case 0x13: {data_type13.write_type13(s); break;} 			// POS_JUMP
		case 0x15: {data_type15.write_type15(s, re4_2007); break;} 			// GRAPPLE HOOK
		}
	unsigned int pad = 64 - (s.tell() - p);
	for (unsigned int i = 0; i < pad; i++) {
		s.writebyte(0);
		}
	}

void fmtAEV_Region::export_region (std::wstring outfile, std::string secname) {

	// create text
	std::string cmt;

	ini->clear();
	ini->header("Atari Events", secname);

	ini->separator("Interaction");
	/* TYPE */ {
		switch (type) {
			case 0x00: {cmt = "NORMAL"; break;}
			case 0x01: {cmt = "DOOR"; break;}
			case 0x02: {cmt = "EXEC"; break;}
			case 0x04: {cmt = "FLG"; break;}
			case 0x05: {cmt = "MESSAGE"; break;}
			case 0x06: {cmt = "PLANTER"; break;}
			case 0x07: {cmt = "JUMP"; break;}
			case 0x08: {cmt = "SAVE"; break;}
			case 0x09: {cmt = "SHD_DISP"; break;}
			case 0x0A: {cmt = "DAMAGE"; break;}
			case 0x0B: {cmt = "SCR_AT"; break;}
			case 0x0C: {cmt = "VIEW_CTRL"; break;}
			case 0x0D: {cmt = "FIELD_INFO"; break;}
			case 0x0E: {cmt = "STOOP"; break;}
			case 0x0F: {cmt = "SMALL_KEY"; break;}
			case 0x10: {cmt = "LADDER"; break;}
			case 0x11: {cmt = "USE"; break;}
			case 0x12: {cmt = "HIDE"; break;}
			case 0x13: {cmt = "POS_JUMP"; break;}
			case 0x14: {cmt = "ITEM_PARENT"; break;}
			case 0x15: {cmt = "ADA_GRAPPLE"; break;}
			default: {cmt = "Doesn't Do Anything?";}
			}
		ini->hexnumber("type", type, 2, cmt);
		}

	/* INDEX */ {
		ini->integer("index", index, "Index to call scripted event");
		}

	/* PRIORITY */ {
		ini->integer("priority", priority, "0:low - 15:high, 2=default");
		}

	/* TRIGGER_TYPE */ {
		switch (trigger_type) {
			case 0x00: {cmt = "NotSet"; break;}
			case 0x01: {cmt = "AUTO"; break;}
			case 0x02: {cmt = "MANUAL"; break;}
			case 0x04: {cmt = "SEMIAUTO"; break;}
			case 0x08: {cmt = "ACTION_BUTTON"; break;}
			case 0x80: {cmt = "ONLY_ONCE\n"; break;}
			case 0x81: {cmt = "AUTO (Single Use)"; break;}
			case 0x82: {cmt = "MANUAL (Single Use)"; break;}
			case 0x84: {cmt = "SEMIAUTO (Single Use)"; break;}
			case 0x88: {cmt = "ACTION_BUTTON (Single Use)"; break;}
			default: {cmt = "Doesn't Do Anything?";}
			}
		ini->hexnumber("trigger_type", trigger_type, 2, cmt);
		}

	/* TARGET_TYPE */ {
		switch (target_type) {
			case 0x00: {cmt = "NotSet"; break;}
			case 0x01: {cmt = "PL"; break;}
			case 0x02: {cmt = "EM"; break;}
			case 0x03: {cmt = "PL+EM"; break;}
			case 0x04: {cmt = "OBJ"; break;}
			case 0x05: {cmt = "PL+OBJ"; break;}
			case 0x06: {cmt = "EM+OBJ"; break;}
			case 0x07: {cmt = "PL+EM+OBJ"; break;}
			case 0x08: {cmt = "SUB"; break;}
			case 0x09: {cmt = "PL+SUB"; break;}
			case 0x0A: {cmt = "EM+SUB"; break;}
			case 0x0B: {cmt = "PL+EM+SUB"; break;}
			case 0x0C: {cmt = "OBJ+SUB"; break;}
			case 0x0D: {cmt = "PL+OBJ+SUB"; break;}
			case 0x0E: {cmt = "EM+OBJ+SUB"; break;}
			case 0x0F: {cmt = "PL+EM+OBJ+SUB"; break;}
			default: {cmt = "Doesn't Do Anything?";}
			}
		ini->hexnumber("target_type", target_type, 2, cmt);
		}

	/* HIT_TYPE */ {
		switch (hit_type) {
			case 0x00: {cmt = "UNDER"; break;}
			case 0x01: {cmt = "FRONT"; break;}
			case 0x02: {cmt = "UNDER+ANGLE"; break;}
			case 0x03: {cmt = "FRONT+ANGLE"; break;}
			default: {cmt = "Doesn't Do Anything?";}
			}
		ini->integer("hit_type", hit_type);
		}

	/* HIT_ANGLE */ {
		if (hit_type == 2 || hit_type == 3) {
			ini->string("hit_angle", to_string((float)hit_angle * 2.0f), "Direction of Detection (-180 to 180 Degrees)");
			}
		}

	/* OPEN_ANGLE */ {
		if (hit_type == 2 || hit_type == 3) {
			ini->string("open_angle", to_string((float)open_angle * 2.0f), "View Angle of Detection (0 to 180 Degrees)");
			}
		}

	/* ACTION_TYPE */ {
		if (trigger_type == 0x08 || trigger_type == 0x88) {
			switch (action_type) {
				case 0x00: {cmt = "Talk"; break;}
				case 0x01: {cmt = "Check"; break;}
				case 0x02: {cmt = "Jump Out"; break;}
				case 0x03: {cmt = "Jump In"; break;}
				case 0x04: {cmt = "Jump Down"; break;}
				case 0x05: {cmt = "Jump Over"; break;}
				case 0x06: {cmt = "Push"; break;}
				case 0x07: {cmt = "Kick"; break;}
				case 0x08: {cmt = "Climb Up"; break;}
				case 0x09: {cmt = "Climb Down"; break;}
				case 0x0A: {cmt = "Knock Down"; break;}
				case 0x0B: {cmt = "Raise Up"; break;}
				case 0x0C: {cmt = "Jump"; break;}
				case 0x0D: {cmt = "Look"; break;}
				case 0x0E: {cmt = "Look Down"; break;}
				case 0x0F: {cmt = "Back To The Wall"; break;}
				case 0x10: {cmt = "Open"; break;}
				case 0x11: {cmt = "Swim"; break;}
				case 0x12: {cmt = "Jump Over"; break;}
				case 0x13: {cmt = "Crouch"; break;}
				case 0x14: {cmt = "Operate"; break;}
				case 0x15: {cmt = "Help"; break;}
				case 0x16: {cmt = "Piggyback"; break;}
				case 0x17: {cmt = "Throw"; break;}
				case 0x18: {cmt = "Sprint19"; break;}
				case 0x1A: {cmt = "Jump"; break;}
				case 0x1B: {cmt = "Slide Down"; break;}
				case 0x1C: {cmt = "Catch"; break;}
				case 0x1D: {cmt = "Pull Up"; break;}
				case 0x1E: {cmt = "Wait"; break;}
				case 0x1F: {cmt = "Stand Back"; break;}
				case 0x20: {cmt = "Hide"; break;}
				case 0x21: {cmt = "Follow Me"; break;}
				case 0x22: {cmt = "Give Me A Hand"; break;}
				case 0x23: {cmt = "Get On"; break;}
				case 0x24: {cmt = "Get Off"; break;}
				case 0x25: {cmt = "Dodge"; break;}
				case 0x26: {cmt = "Hide"; break;}
				case 0x27: {cmt = "Crawl"; break;}
				case 0x28: {cmt = "Take"; break;}
				case 0x29: {cmt = "Cut"; break;}
				case 0x2A: {cmt = "Rotate"; break;}
				case 0x2B: {cmt = "Shake Off"; break;}
				case 0x2C: {cmt = "Suplex"; break;}
				case 0x2D: {cmt = "Dummy"; break;}
				case 0x2E: {cmt = "Begin"; break;}
				case 0x2F: {cmt = "Save"; break;}
				case 0x30: {cmt = "(Blank)"; break;}
				case 0x31: {cmt = "Accelerate"; break;}
				case 0x32: {cmt = "?"; break;}
				case 0x33: {cmt = "Send Ashley"; break;}
				case 0x34: {cmt = "?"; break;}
				case 0x35: {cmt = "Knock Over"; break;}
				case 0x36: {cmt = "Respond"; break;}
				case 0x37: {cmt = "Infiltrate"; break;}
				case 0x38: {cmt = "Fan Kick"; break;}
				case 0x39: {cmt = "Back Kick"; break;}
				case 0x3A: {cmt = "Knee"; break;}
				case 0x3B: {cmt = "Neck Breaker"; break;}
				case 0x3C: {cmt = "Thrust Punch"; break;}
				case 0x3D: {cmt = "Chikyo Chagi"; break;}
				case 0x3E: {cmt = "Jump"; break;}
				case 0x3F: {cmt = "Ring"; break;}
				case 0x40: {cmt = "Hop Down"; break;}
				case 0x41: {cmt = "Fire"; break;}
				case 0x42: {cmt = "Rotate"; break;}
				case 0x43: {cmt = "Hook Shot"; break;}
				case 0x44: {cmt = "Aaa"; break;}
				default: {cmt = "Doesn't Do Anything?";}
				}
			ini->hexnumber("action_type", action_type, 2, cmt);
			}
		}

	/* MESSAGE TYPE */ {
		ini->integer("msg_type", msg_type, "text colour: 0 = normal, 1 = green, 2 = red");
		}

	/* ATARI */ {
		area.write_ini();
		}

	/* EVENTS */ {
		switch (type) {
			case 0x00: {cmt = "Normal"; break;}
			case 0x01: {cmt = "Door"; break;}
			case 0x02: {cmt = "Cut Scene"; break;}
			case 0x04: {cmt = "Flag Edit"; break;}
			case 0x05: {cmt = "Message Prompt"; break;}
			case 0x06: {cmt = "Player"; break;}
			case 0x07: {cmt = "Move Player"; break;}
			case 0x08: {cmt = "Save Game"; break;}
			case 0x09: {cmt = "Shadow Display"; break;}
			case 0x0A: {cmt = "Damage Player"; break;}
			case 0x0B: {cmt = "Collision Edit"; break;}
			case 0x0C: {cmt = "Camera View"; break;}
			case 0x0D: {cmt = "Field Info"; break;}
			case 0x0E: {cmt = "Stoop Zone"; break;}
			case 0x0F: {cmt = "Small Key"; break;}
			case 0x10: {cmt = "Climb Ladder"; break;}
			case 0x11: {cmt = "Item Use"; break;}
			case 0x12: {cmt = "Hide Zone"; break;}
			case 0x13: {cmt = "Move & Rotate Player"; break;}
			case 0x14: {cmt = "Item Parenting"; break;}
			case 0x15: {cmt = "Ada's Grapple Hook"; break;}
			default: cmt = "";
			}
		if (cmt.length() > 0) {
			ini->separator(cmt + " - Event Data");
			}
		else {
			ini->separator("Event Data");
			}

		switch (type) {
			case 0x00: {data_type00.write_ini(); break;}	// NORMAL
			case 0x01: {data_type01.write_ini(); break;}	// DOOR
			case 0x02: {data_type02.write_ini(); break;}	// EXEC
			case 0x04: {data_type04.write_ini(); break;}	// FLAG
			case 0x05: {data_type05.write_ini(); break;}	// MESSAGE
			case 0x07: {data_type07.write_ini(); break;}	// JUMP
			case 0x08: {data_type08.write_ini(); break;}	// SAVE
			case 0x09: {data_type09.write_ini(); break;}	// SHD_DISP
			case 0x0A: {data_type0A.write_ini(); break;}	// DAMAGE
			case 0x0B: {data_type0B.write_ini(); break;}	// SCR_AT
			case 0x0C: {data_type0C.write_ini(); break;}	// VIEW CONTROL
			case 0x0D: {data_type0D.write_ini(); break;}	// FIELD_INFO
			case 0x10: {data_type10.write_ini(); break;}	// LADDER
			case 0x11: {data_type11.write_ini(); break;}	// USE
			case 0x12: {data_type12.write_ini(); break;}	// HIDE
			case 0x13: {data_type13.write_ini(); break;}	// POS_JUMP
			case 0x15: {data_type15.write_ini(); break;}	// GRAPPLE HOOK
			}
		}

	// write text file
	ini->log(outfile);
	}

void fmtAEV_Region::import_region (std::string secname) {

	type = (uint8_t)ini->get_integer(secname, "type");
	index = (uint8_t)ini->get_integer(secname, "index");
	hit_type = (uint8_t)ini->get_integer(secname, "hit_type");
	trigger_type = (uint8_t)ini->get_integer(secname, "trigger_type");
	target_type = (uint8_t)ini->get_integer(secname, "target_type");
	unk021 = (uint8_t)ini->get_integer(secname, "unk021");
	priority = (uint8_t)ini->get_integer(secname, "priority");
	unk025b = (uint8_t)ini->get_integer(secname, "unk025b");
	hit_angle = (int8_t)ini->get_integer(secname, "hit_angle") / 2;
	open_angle = (uint8_t)ini->get_integer(secname, "open_angle") / 2;
	action_type = (uint8_t)ini->get_integer(secname, "action_type");

	unk026 = (uint8_t)ini->get_integer(secname, "unk026");
	unk027 = (uint32_t)ini->get_integer(secname, "unk027");
	unk028 = (uint8_t)ini->get_integer(secname, "unk028");
	unk029 = (uint8_t)ini->get_integer(secname, "unk029");
	msg_flag = (uint8_t)ini->get_integer(secname, "msg_flag");
	msg_type = (uint8_t)ini->get_integer(secname, "msg_type");
	unk030 = (uint32_t)ini->get_integer(secname, "unk030");
	unk031 = (uint32_t)ini->get_integer(secname, "unk031");

	area.clear();
	area.type = 1;
	area.read_ini(secname);
//
//	if (data_type00 != NULL) {delete data_type00; data_type00 = NULL;}	// NORMAL
//	if (data_type01 != NULL) {delete data_type01; data_type01 = NULL;}	// DOOR
//	if (data_type02 != NULL) {delete data_type02; data_type02 = NULL;}	// EXEC
//	if (data_type04 != NULL) {delete data_type04; data_type04 = NULL;}	// FLAG
//	if (data_type05 != NULL) {delete data_type05; data_type05 = NULL;}	// MESSAGE
//	if (data_type07 != NULL) {delete data_type07; data_type07 = NULL;}	// JUMP
//	if (data_type08 != NULL) {delete data_type08; data_type08 = NULL;}	// SAVE
//	if (data_type09 != NULL) {delete data_type09; data_type09 = NULL;}	// SHD_DISP
//	if (data_type0A != NULL) {delete data_type0A; data_type0A = NULL;}	// DAMAGE
//	if (data_type0B != NULL) {delete data_type0B; data_type0B = NULL;}	// SCR_AT
//	if (data_type0C != NULL) {delete data_type0C; data_type0C = NULL;}	// VIEW CONTROL
//	if (data_type0D != NULL) {delete data_type0D; data_type0D = NULL;}	// FIELD_INFO
//	if (data_type10 != NULL) {delete data_type10; data_type10 = NULL;}	// LADDER
//	if (data_type11 != NULL) {delete data_type11; data_type11 = NULL;}	// USE
//	if (data_type12 != NULL) {delete data_type12; data_type12 = NULL;}	// HIDE
//	if (data_type13 != NULL) {delete data_type13; data_type13 = NULL;}	// POS_JUMP
//	if (data_type15 != NULL) {delete data_type15; data_type15 = NULL;}	// GRAPPLE HOOK

	switch (type) {
		case 0x00: {data_type00.read_ini(secname); break;}	// NORMAL
		case 0x01: {data_type01.read_ini(secname); break;}	// DOOR
		case 0x02: {data_type02.read_ini(secname); break;}	// EXEC
		case 0x04: {data_type04.read_ini(secname); break;}	// FLAG
		case 0x05: {data_type05.read_ini(secname); break;}	// MESSAGE
		case 0x07: {data_type07.read_ini(secname); break;}	// JUMP
		case 0x08: {data_type08.read_ini(secname); break;}	// SAVE
		case 0x09: {data_type09.read_ini(secname); break;}	// SHD_DISP
		case 0x0A: {data_type0A.read_ini(secname); break;}	// DAMAGE
		case 0x0B: {data_type0B.read_ini(secname); break;}	// SCR_AT
		case 0x0C: {data_type0C.read_ini(secname); break;}	// VIEW CONTROL
		case 0x0D: {data_type0D.read_ini(secname); break;}	// FIELD_INFO
		case 0x10: {data_type10.read_ini(secname); break;}	// LADDER
		case 0x11: {data_type11.read_ini(secname); break;}	// USE
		case 0x12: {data_type12.read_ini(secname); break;}	// HIDE
		case 0x13: {data_type13.read_ini(secname); break;}	// POS_JUMP
		case 0x15: {data_type15.read_ini(secname); break;}	// GRAPPLE HOOK
		}
	}

fmtAEV::fmtAEV () {
	type[0] = 0x41;
	type[1] = 0x45;
	type[2] = 0x56;
	type[3] = 0x00;
	version = 0x0104;
	count = 0;
	unk003 = 0;
	unk004 = 0;
	data.clear();
	}

size_t fmtAEV::size (bool re4_2007) {
	int entry_stride = 156;
	if (re4_2007) {entry_stride = 160;}
	size_t nsize = 16 + (count * entry_stride);
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

bool fmtAEV::validate (bytestream &f, bool &re4_2007, bool verbose) {

	// set initial success state
	bool isGood = false;

	// assume file is NOT RE4 2007
	re4_2007 = false;

	// get start position; so we can return back after
	size_t pos = f.tell();

	// check file is large enough
	if (pos + 16 <= f.size) {

		// read the file id
		uint32_t chk1 = f.readUlong(); // fileid is always in little endian
		if (chk1 == 0x00564541 || chk1 == 0x41455600) {

			// check version
			uint16_t chk2 = f.readUshort();

			// correct endian
			if (chk2 == 0x0401) {

				// change endian
				f.islilEndian = !f.islilEndian;

				// Update Check Value
				f.seek(pos + 4);
				chk2 = f.readUshort();
				}

			// Check version is correct
			if (chk2 == 0x0104) {

				// read count
				uint16_t chk3 = f.readUshort();

				// Check Count is not Null
				if (chk3 > 0) {

					// check for overrun
					if ((pos + 16 + (chk3 * 156)) <= f.size) {

						// Set validation state to true
						isGood = true;


						// check if (file is from RE4 2007 by doing further signature checks
						if (!re4_2007 && f.islilEndian && (pos + 16 + (chk3 * 160)) <= f.size) {
							/*
								the signature check is pretty weak; all I can check for
								is the 4 bytes padding they added specifically after the
								first data entry.

								Unfortunately this is before a reserved buffer that can
								be nulled.

								This means the check at the padding can return false
								positives and is not ideal.

								The only way to decrease false positives is to read more
								then the first entry

								Since thats not always a guarantee; the check i'm doing
								is extremely weak if (there is only ONE entry

							*/


							// Jump to the Padding they added
							f.seek(108);

							// Read padding; should be 0
							uint32_t chk6 = f.readUlong(); // should be 0

							// Check padding is 0
							if (chk6 == 0) {

								// Set RE4 2007 State to True
								re4_2007 = true;


								// Do additional checking if (more entries are available
								uint8_t chk7 = 0;

								for (unsigned int i = 0; i < count; i++) {

									// Check for signature 1
									f.seek(pos + (i * 160) + 68);
									chk7 = f.readUbyte(); // should always be 3 {remove this check if (causing issues}

									// Check for Signature 2
									f.seek(pos + (i * 160) + 108);
									chk6 = f.readUlong(); // should always be 0; this is the padding they added


									// Check Signature
									if (chk6 != 0 || chk7 != 3) {

										// Signature Fail; switch re4 2007 state back to false
										re4_2007 = false;

										// stop checking
										break;
										}
									}
								}
							}
						} else {if (verbose) {std::cout << "AEV Validation Error:\n\tFile Table Exceeds file Length\n\n";}}
					} else {if (verbose) {std::cout << "AEV Validation Error:\n\tFile is Empty [" << f.size << "] :: " << f.file << "\n\n";}}
				} else {if (verbose) {std::cout << "AEV Validation Error:\n\tInvalid Version [" << chk2 << "]\n\n";}}
			} else {if (verbose) {std::cout << "AEV Validation Error:\n\tInvalid File Type [" << chk1 << "]\n\n";}}
		} else {if (verbose) {std::cout << "AEV Validation Error:\n\tInvalid File Size\n\n";}}

	// Return to where we began
	f.seek(pos);
	return isGood;
	}

void fmtAEV::read_aev (bytestream &f) {
	// get start of the file
	size_t pos = f.tell();

	// init state of
	bool re4_2007 = false;
	if (validate(f, re4_2007)) {

		type[0] = f.readUbyte();
		type[1] = f.readUbyte();
		type[2] = f.readUbyte();
		type[3] = f.readUbyte();
		version = f.readUshort();
		count = f.readUshort();
		unk003 = f.readUlong();
		unk004 = f.readUlong();


		if (count > 0) {

			data = std::vector<fmtAEV_Region>(count);
			int entry_stride = 156;
			if (re4_2007) {entry_stride = 160;}
			for (unsigned int i = 0; i < count; i++) {
				f.seek(pos + 0x10 + (i * entry_stride));
				data[i].read_region(f, re4_2007);
				}
			}
		} else {std::cout << "Error:\tInvalid aev\n";}
	}

void fmtAEV::write_aev (bytestream &s, bool re4_2007) {
	s.writebyte(type[0]);
	s.writebyte(type[1]);
	s.writebyte(type[2]);
	s.writebyte(type[3]);
	s.writeshort(version);
	s.writeshort(count = data.size());
	s.writelong(unk003);
	s.writelong(unk004);

	for (unsigned int i = 0; i < count; i++) {
		data[i].write_region(s, re4_2007);
		}
	unsigned int pad = (32-((s.tell()) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0xCD);} // pad to 32
	}

void fmtAEV::open_aev (std::wstring file) {

	bytestream f;
	if (f.openFileW(file)) {

		read_aev(f);

		f.close();
		} else {std::wcout << L"Failed to open File {" << file << L"}\n";}
	}

void fmtAEV::save_aev (std::wstring savefile, bool re4_2007) {

	count = data.size();

	if (count > 0) {

		// Calculate File Size
		size_t nsize = size(re4_2007);

		bytestream s;
		s.resize(nsize);
		write_aev(s, re4_2007);
		if (!s.writeFileW(savefile)) {
			std::cout << "Failed to Write AEV File\n";
			}
		s.close();
		} else {std::cout << "No Data?\n";}
	}

void fmtAEV::export_txt (std::wstring outpath, std::wstring prefix, std::wstring subfolder) {

	if (count > 0) {

		// Create folder
		if (!win::doesFileExistW(outpath)) {
			win::makeDirW(outpath);
			}

		// Create subfolder
		std::wstring aev_path = outpath + L"\\" + subfolder;
		if (!win::doesFileExistW(aev_path)) {
			win::makeDirW(aev_path);
			}

		// Create text file
		ini->clear();
		ini->header("Area Event Config", "AREA_EVENT_PATH", "Set path to aev data, paths may be relative or absolute");
		ini->newline();
		ini->wstring("aev_path", subfolder);
		ini->log(outpath + prefix + L".txt");


		// write files
		for (unsigned int i = 0; i < count; i++) {
			data.at(i).export_region(
				aev_path + L"\\" + prefix + L"_" + \
				string_to_wstring(padString(to_string(i), 3, "0")) + L"_" + \
				string_to_wstring(padString(to_string((int)data.at(i).type), 2, "0")) + L".txt"
				);
			}

		}

	}

