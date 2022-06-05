#include "fmtEST.h"

fmtEST_Effect_Flags::fmtEST_Effect_Flags () {
	flag01 = false;
	flag02 = false;
	flag03 = false;
	flag04 = false;
	flag05 = false;
	flag06 = false;
	flag07 = false;
	flag08 = false;
	flag09 = false;
	flag10 = false;
	flag11 = false;
	flag12 = false;
	flag13 = false;
	flag14 = false;
	flag15 = false;
	flag16 = false;
	flag17 = false;
	flag18 = false;
	flag19 = false;
	flag20 = false;
	flag21 = false;
	flag22 = false;
	flag23 = false;
	flag24 = false;
	flag25 = false;
	flag26 = false;
	flag27 = false;
	flag28 = false;
	flag29 = false;
	flag30 = false;
	flag31 = false;
	flag32 = false;
	}

void fmtEST_Effect_Flags::get_esp_flags (uint32_t val) {
	flag01 = bit::get(val,  1);
	flag02 = bit::get(val,  2);
	flag03 = bit::get(val,  3);
	flag04 = bit::get(val,  4);
	flag05 = bit::get(val,  5);
	flag06 = bit::get(val,  6);
	flag07 = bit::get(val,  7);
	flag08 = bit::get(val,  8);
	flag09 = bit::get(val,  9);
	flag10 = bit::get(val, 10);
	flag11 = bit::get(val, 11);
	flag12 = bit::get(val, 12);
	flag13 = bit::get(val, 13);
	flag14 = bit::get(val, 14);
	flag15 = bit::get(val, 15);
	flag16 = bit::get(val, 16);
	flag17 = bit::get(val, 17);
	flag18 = bit::get(val, 18);
	flag19 = bit::get(val, 19);
	flag20 = bit::get(val, 20);
	flag21 = bit::get(val, 21);
	flag22 = bit::get(val, 22);
	flag23 = bit::get(val, 23);
	flag24 = bit::get(val, 24);
	flag25 = bit::get(val, 25);
	flag26 = bit::get(val, 26);
	flag27 = bit::get(val, 27);
	flag28 = bit::get(val, 28);
	flag29 = bit::get(val, 29);
	flag30 = bit::get(val, 30);
	flag31 = bit::get(val, 31);
	flag32 = bit::get(val, 32);
	}

void fmtEST_Effect_Flags::read_esp_flags (bytestream &f) {
	get_esp_flags(f.readUlong());
	}

uint32_t fmtEST_Effect_Flags::set_esp_flags () {
	uint32_t val = 0;
	val = bit::set(val,  1, flag01);
	val = bit::set(val,  2, flag02);
	val = bit::set(val,  3, flag03);
	val = bit::set(val,  4, flag04);
	val = bit::set(val,  5, flag05);
	val = bit::set(val,  6, flag06);
	val = bit::set(val,  7, flag07);
	val = bit::set(val,  8, flag08);
	val = bit::set(val,  9, flag09);
	val = bit::set(val, 10, flag10);
	val = bit::set(val, 11, flag11);
	val = bit::set(val, 12, flag12);
	val = bit::set(val, 13, flag13);
	val = bit::set(val, 14, flag14);
	val = bit::set(val, 15, flag15);
	val = bit::set(val, 16, flag16);
	val = bit::set(val, 17, flag17);
	val = bit::set(val, 18, flag18);
	val = bit::set(val, 19, flag19);
	val = bit::set(val, 20, flag20);
	val = bit::set(val, 21, flag21);
	val = bit::set(val, 22, flag22);
	val = bit::set(val, 23, flag23);
	val = bit::set(val, 24, flag24);
	val = bit::set(val, 25, flag25);
	val = bit::set(val, 26, flag26);
	val = bit::set(val, 27, flag27);
	val = bit::set(val, 28, flag28);
	val = bit::set(val, 29, flag29);
	val = bit::set(val, 30, flag30);
	val = bit::set(val, 31, flag31);
	val = bit::set(val, 32, flag32);
	return val;
	}

void fmtEST_Effect_Flags::write_esp_flags (bytestream &s) {
	s.writelong(set_esp_flags());
	}

void fmtEST_Effect::clear () {
	state = 1;
	esp_id = 0;
	tex_id = 0;
	unk13 = 0;
	time = 0;
	parent = 0xFE;
	part_id = 0;
	flag.get_esp_flags(0);
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;
	rand[0] = 0.0f;
	rand[1] = 0.0f;
	rand[2] = 0.0f;
	speed[0] = 0.0f;
	speed[1] = 0.0f;
	speed[2] = 0.0f;
	speed_d = 1.0f;
	rand_speed[0] = 0.0f;
	rand_speed[1] = 0.0f;
	rand_speed[2] = 0.0f;
	speed_acceleration[0] = 0.0f;
	speed_acceleration[1] = 0.0f;
	speed_acceleration[2] = 0.0f;
	rand_speed_acceleration[0] = 0.0f;
	rand_speed_acceleration[1] = 0.0f;
	rand_speed_acceleration[2] = 0.0f;
	rotation[0] = 0.0f;
	rotation[1] = 0.0f;
	rotation[2] = 0.0f;
	rand_rotation[0] = 0.0f;
	rand_rotation[1] = 0.0f;
	rand_rotation[2] = 0.0f;
	rotation_acceleration[0] = 0.0f;
	rotation_acceleration[1] = 0.0f;
	rotation_acceleration[2] = 0.0f;
	rand_rotation_acceleration[0] = 0.0f;
	rand_rotation_acceleration[1] = 0.0f;
	rand_rotation_acceleration[2] = 0.0f;
	width = 200.0f;
	height = 200.0f;
	r_size = 0.0f;
	plus = 0.0f;
	d_plus = 1.0f;
	rgba[0] = 0xFF;
	rgba[1] = 0xFF;
	rgba[2] = 0xFF;
	rgba[3] = 0xFF;
	d_rgba[0] = 1.0f;
	d_rgba[1] = 1.0f;
	d_rgba[2] = 1.0f;
	d_rgba[3] = 1.0f;
	color_end_frame = 0;
	color_start_frame = 0;
	unk14 = 0;
	size_start_frame = 0;
	life_time = 0;
	unk15 = 0;
	unk16 = 0;
	unk17 = 0;
	animation_rate = 0;
	unk18 = 0;
	unk19 = 0;
	release_trigger = 0;
	unk20 = 0;
	blend_mode = 0;
	sim_type = 0;
	sim_power = 0;
	tex_mask = 0;
	color_in = 0;
	color_out = 0;
	work0 = 0;
	work1 = 0;
	work2 = 0;
	work3 = 0;
	work4 = 0;
	work5 = 0;
	work6 = 0;
	vec0[0] = 0.0f;
	vec0[1] = 0.0f;
	vec0[2] = 0.0f;
	vec1[0] = 0.0f;
	vec1[1] = 0.0f;
	vec1[2] = 0.0f;
	vec2[0] = 0.0f;
	vec2[1] = 0.0f;
	vec2[2] = 0.0f;
	sp0 = 0;
	sp1 = 0;
	sp2 = 0;
	sp3 = 0;
	unk21 = 0;
	path_own = 0;
	path_no = 0;
	path_st = 0;
	path_rnd = 0;
	kind = 0;
	ctr_id = 0;
	unk22 = 0;
	id_flag = 0;
	inter = 0;
	num = 0;
	rp = 0;
	unk23 = 0;
	life = 0;
	unk24 = 0;
	unk25 = 0;
	unk26 = 0;
	path_scale[0] = 0.0f;
	path_scale[1] = 0.0f;
	path_scale[2] = 0.0f;
	d_size = 0;
	d_speed = 0;
	d_alpha = 0;
	d_inter = 0;
	r_inter = 0;
	path_rotation_x = 0;
	path_rotation_y = 0;
	path_flag = 0;
	}

fmtEST_Effect::fmtEST_Effect () {
	clear();
	}

void fmtEST_Effect::read_esp_data (bytestream &f) {
	state = f.readUbyte();
	esp_id = f.readUbyte();
	tex_id = f.readUbyte();
	unk13 = f.readUbyte();
	time = f.readUshort();
	part_id = f.readUbyte();
	parent = f.readUbyte();
	flag.read_esp_flags(f);
	position[0] = f.readfloat();
	position[1] = f.readfloat();
	position[2] = f.readfloat();
	rand[0] = f.readfloat();
	rand[1] = f.readfloat();
	rand[2] = f.readfloat();
	speed[0] = f.readfloat();
	speed[1] = f.readfloat();
	speed[2] = f.readfloat();
	speed_d = f.readfloat();
	rand_speed[0] = f.readfloat();
	rand_speed[1] = f.readfloat();
	rand_speed[2] = f.readfloat();
	speed_acceleration[0] = f.readfloat();
	speed_acceleration[1] = f.readfloat();
	speed_acceleration[2] = f.readfloat();
	rand_speed_acceleration[0] = f.readfloat();
	rand_speed_acceleration[1] = f.readfloat();
	rand_speed_acceleration[2] = f.readfloat();
	rotation[0] = f.readfloat();
	rotation[1] = f.readfloat();
	rotation[2] = f.readfloat();
	rand_rotation[0] = f.readfloat();
	rand_rotation[1] = f.readfloat();
	rand_rotation[2] = f.readfloat();
	rotation_acceleration[0] = f.readfloat();
	rotation_acceleration[1] = f.readfloat();
	rotation_acceleration[2] = f.readfloat();
	rand_rotation_acceleration[0] = f.readfloat();
	rand_rotation_acceleration[1] = f.readfloat();
	rand_rotation_acceleration[2] = f.readfloat();
	width = f.readfloat();
	height = f.readfloat();
	r_size = f.readfloat();
	plus = f.readfloat();
	d_plus = f.readfloat();
	rgba[0] = f.readUbyte();
	rgba[1] = f.readUbyte();
	rgba[2] = f.readUbyte();
	rgba[3] = f.readUbyte();
	d_rgba[0] = f.readfloat();
	d_rgba[1] = f.readfloat();
	d_rgba[2] = f.readfloat();
	d_rgba[3] = f.readfloat();
	color_end_frame = f.readUshort();
	color_start_frame = f.readUshort();
	unk14 = f.readUshort();
	size_start_frame = f.readUshort();
	life_time = f.readUshort();
	unk15 = f.readUbyte();
	unk16 = f.readUbyte();
	unk17 = f.readUbyte();
	animation_rate = f.readUbyte();
	unk18 = f.readUbyte();
	unk19 = f.readUbyte();
	release_trigger = f.readUbyte();
	unk20 = f.readUbyte();
	blend_mode = f.readUbyte();
	sim_type = f.readUbyte();
	sim_power = f.readUbyte();
	tex_mask = f.readUbyte();
	color_in = f.readUbyte();
	color_out = f.readUbyte();
	work0 = f.readUbyte();
	work1 = f.readUbyte();
	work2 = f.readUbyte();
	work3 = f.readUbyte();
	work4 = f.readUlong();
	work5 = f.readUlong();
	work6 = f.readUlong();
	vec0[0] = f.readfloat();
	vec0[1] = f.readfloat();
	vec0[2] = f.readfloat();
	vec1[0] = f.readfloat();
	vec1[1] = f.readfloat();
	vec1[2] = f.readfloat();
	vec2[0] = f.readfloat();
	vec2[1] = f.readfloat();
	vec2[2] = f.readfloat();
	sp0 = f.readUbyte();
	sp1 = f.readUbyte();
	sp2 = f.readUbyte();
	sp3 = f.readUbyte();
	unk21 = f.readUlong();
	path_own = f.readUbyte();
	path_no = f.readUbyte();
	path_st = f.readUbyte();
	path_rnd = f.readUbyte();
	kind = f.readUbyte();
	ctr_id = f.readUbyte();
	unk22 = f.readUbyte();
	id_flag = f.readUbyte();
	inter = f.readUbyte();
	num = f.readUbyte();
	rp = f.readUbyte();
	unk23 = f.readUbyte();
	life = f.readUshort();
	unk24 = f.readUshort();
	unk25 = f.readUshort();
	unk26 = f.readUshort();
	path_scale[0] = f.readfloat();
	path_scale[1] = f.readfloat();
	path_scale[2] = f.readfloat();
	d_size = f.readUbyte();
	d_speed = f.readUbyte();
	d_alpha = f.readUbyte();
	d_inter = f.readUbyte();
	r_inter = f.readUbyte();
	path_rotation_x = f.readUbyte();
	path_rotation_y = f.readUbyte();
	path_flag = f.readUbyte();
	}

void fmtEST_Effect::write_esp_data (bytestream &s) {
	s.writebyte(state);
	s.writebyte(esp_id);
	s.writebyte(tex_id);
	s.writebyte(unk13);
	s.writeshort(time);
	s.writebyte(part_id);
	s.writebyte(parent);
	flag.write_esp_flags(s);
	s.writefloat(position[0]);
	s.writefloat(position[1]);
	s.writefloat(position[2]);
	s.writefloat(rand[0]);
	s.writefloat(rand[1]);
	s.writefloat(rand[2]);
	s.writefloat(speed[0]);
	s.writefloat(speed[1]);
	s.writefloat(speed[2]);
	s.writefloat(speed_d);
	s.writefloat(rand_speed[0]);
	s.writefloat(rand_speed[1]);
	s.writefloat(rand_speed[2]);
	s.writefloat(speed_acceleration[0]);
	s.writefloat(speed_acceleration[1]);
	s.writefloat(speed_acceleration[2]);
	s.writefloat(rand_speed_acceleration[0]);
	s.writefloat(rand_speed_acceleration[1]);
	s.writefloat(rand_speed_acceleration[2]);
	s.writefloat(rotation[0]);
	s.writefloat(rotation[1]);
	s.writefloat(rotation[2]);
	s.writefloat(rand_rotation[0]);
	s.writefloat(rand_rotation[1]);
	s.writefloat(rand_rotation[2]);
	s.writefloat(rotation_acceleration[0]);
	s.writefloat(rotation_acceleration[1]);
	s.writefloat(rotation_acceleration[2]);
	s.writefloat(rand_rotation_acceleration[0]);
	s.writefloat(rand_rotation_acceleration[1]);
	s.writefloat(rand_rotation_acceleration[2]);
	s.writefloat(width);
	s.writefloat(height);
	s.writefloat(r_size);
	s.writefloat(plus);
	s.writefloat(d_plus);
	s.writebyte(rgba[0]);
	s.writebyte(rgba[1]);
	s.writebyte(rgba[2]);
	s.writebyte(rgba[3]);
	s.writefloat(d_rgba[0]);
	s.writefloat(d_rgba[1]);
	s.writefloat(d_rgba[2]);
	s.writefloat(d_rgba[3]);
	s.writeshort(color_end_frame);
	s.writeshort(color_start_frame);
	s.writeshort(unk14);
	s.writeshort(size_start_frame);
	s.writeshort(life_time);
	s.writebyte(unk15);
	s.writebyte(unk16);
	s.writebyte(unk17);
	s.writebyte(animation_rate);
	s.writebyte(unk18);
	s.writebyte(unk19);
	s.writebyte(release_trigger);
	s.writebyte(unk20);
	s.writebyte(blend_mode);
	s.writebyte(sim_type);
	s.writebyte(sim_power);
	s.writebyte(tex_mask);
	s.writebyte(color_in);
	s.writebyte(color_out);
	s.writebyte(work0);
	s.writebyte(work1);
	s.writebyte(work2);
	s.writebyte(work3);
	s.writelong(work4);
	s.writelong(work5);
	s.writelong(work6);
	s.writefloat(vec0[0]);
	s.writefloat(vec0[1]);
	s.writefloat(vec0[2]);
	s.writefloat(vec1[0]);
	s.writefloat(vec1[1]);
	s.writefloat(vec1[2]);
	s.writefloat(vec2[0]);
	s.writefloat(vec2[1]);
	s.writefloat(vec2[2]);
	s.writebyte(sp0);
	s.writebyte(sp1);
	s.writebyte(sp2);
	s.writebyte(sp3);
	s.writelong(unk21);
	s.writebyte(path_own);
	s.writebyte(path_no);
	s.writebyte(path_st);
	s.writebyte(path_rnd);
	s.writebyte(kind);
	s.writebyte(ctr_id);
	s.writebyte(unk22);
	s.writebyte(id_flag);
	s.writebyte(inter);
	s.writebyte(num);
	s.writebyte(rp);
	s.writebyte(unk23);
	s.writeshort(life);
	s.writeshort(unk24);
	s.writeshort(unk25);
	s.writeshort(unk26);
	s.writefloat(path_scale[0]);
	s.writefloat(path_scale[1]);
	s.writefloat(path_scale[2]);
	s.writebyte(d_size);
	s.writebyte(d_speed);
	s.writebyte(d_alpha);
	s.writebyte(d_inter);
	s.writebyte(r_inter);
	s.writebyte(path_rotation_x);
	s.writebyte(path_rotation_y);
	s.writebyte(path_flag);
	}

void fmtEST_Effect::repr () {
	std::cout << (int)state << "\t" << (int)esp_id << "\t";
	std::cout << (int)tex_id << "\t" << unk13 << "\t";
	std::cout << time << "\t" << (int)parent << "\t";
	std::cout << (int)part_id << "\t" << flag.set_esp_flags() << "\n[";
	std::cout << position[0] << "\t" << position[1] << "\t" << position[2] << "]\t[";
	std::cout << rand[0] << "\t" << rand[1] << "\t" << rand[2] << "]\n[";
	std::cout << speed[0] << "\t" << speed[1] << "\t" << speed[2] << "]\t" << speed_d << "\n";
	std::cout << rand_speed[0] << "\t" << rand_speed[1] << "\t" << rand_speed[2] << "\t";
	std::cout << speed_acceleration[0] << "\t" << speed_acceleration[1] << "\t" << speed_acceleration[2] << "\n";
	std::cout << rand_speed_acceleration[0] << "\t" << rand_speed_acceleration[1] << "\t" << rand_speed_acceleration[2] << "\t";
	std::cout << rotation[0] << "\t" << rotation[1] << "\t" << rotation[2] << "\t";
	std::cout << rand_rotation[0] << "\t" << rand_rotation[1] << "\t" << rand_rotation[2] << "\n";
	std::cout << rotation_acceleration[0] << "\t" << rotation_acceleration[1] << "\t" << rotation_acceleration[2] << "\t";
	std::cout << rand_rotation_acceleration[0] << "\t" << rand_rotation_acceleration[1] << "\t" << rand_rotation_acceleration[2] << "\n";
	std::cout << width << "\t" << height << "\t";
	std::cout << r_size << "\t" << plus << "\t";
	std::cout << d_plus << "\t" << rgba[0] << "\n";
	std::cout << d_rgba << "\t" << color_end_frame << "\t";
	std::cout << color_start_frame << "\t" << unk14 << "\t";
	std::cout << size_start_frame << "\t" << life_time << "\n";
	std::cout << (int)unk15 << "\t" << (int)unk16 << "\t" << (int)unk17 << "\t";
	std::cout << (int)animation_rate << "\t" << (int)unk18 << "\t";
	std::cout << (int)unk19 << "\n" << (int)release_trigger << "\t";
	std::cout << (int)unk20 << "\t" << (int)blend_mode << "\t";
	std::cout << (int)sim_type << "\t" << (int)sim_power << "\t";
	std::cout << (int)tex_mask << "\n" << (int)color_in << "\t";
	std::cout << (int)color_out << "\t" << (int)work0 << "\t";
	std::cout << (int)work1 << "\t" << (int)work2 << "\t" << (int)work3 << "\n";
	std::cout << work4 << "\t" << work5 << "\t" << work6 << "\t";
	std::cout << vec0[0] << "\t" << vec1[0] << "\t" << vec2[0] << "\n";
	std::cout << (int)sp0 << "\t" << (int)sp1 << "\t" << (int)sp2 << "\t";
	std::cout << (int)sp3 << "\t" << unk21 << "\t" << (int)path_own << "\n";
	std::cout << (int)path_no << "\t" << (int)path_st << "\t";
	std::cout << (int)path_rnd << "\t" << (int)kind << "\t";
	std::cout << (int)ctr_id << "\t" << (int)unk22 << "\n" << (int)id_flag << "\t";
	std::cout << (int)inter << "\t" << (int)num << "\t" << (int)rp << "\t";
	std::cout << (int)unk23 << "\t" << life << "\n" << unk24 << "\t";
	std::cout << unk25 << "\t" << unk26 << "\t" << path_scale[0] << "\t" << path_scale[1] << "\t" << path_scale[2] << "\n" << (int)d_size << "\t";
	std::cout << (int)d_speed << "\t" << (int)d_alpha << "\t" << (int)d_inter << "\t" << (int)r_inter << "\t";
	std::cout << (int)path_rotation_x << "\t" << (int)path_rotation_y << "\t" << (int)path_flag << std::endl;
	}

bool fmtEST_Effect::export_txt (std::wstring savefile, bool hide_unset) {
	int padlen = 65;
	int varlen = 21;
	int dc_len = 6;
	std::stringstream ss;
	std::string lne;
	std::string txt = "; =============================================================\n";
	txt += ";      Resident Evil 4 Ultimate HD Edition - Sprite Data\n";
	txt += ";             Generated from re4eff by mariokart64n\n";
	txt += "; -------------------------------------------------------------\n;\n";
	txt += "; * Where otherwise noted, units for size and distance are\n";
	txt += ";   in millmetres and time in decisecond (1/10th of a Second)\n;\n";
	txt += "; =============================================================\n\n";
	txt += "[SST]\n";

	/* STATE */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 15, " ", false) + "Sprite Settings\n";

		lne = padString("  state", varlen, " ", false) + " = " + to_string((int)state);
		txt += padString(lne, padlen, " ", false) + "; ";
		if (state > 0) {
			txt += "Enabled\n";
			}
		else {
			txt += "Disabled\n";
			}
		}

	/* ESP ID */ {
		ss.str(std::string());
		ss << std::uppercase << TO_HEX(esp_id, false, 2);
		lne = padString("  esp_id", varlen, " ", false) + " = 0x" + ss.str();
		txt += padString(lne, padlen, " ", false) + "; ";

		switch (esp_id) {
			case 0x00: {txt += "2D Sprite (can work in screen space)\n"; break;}
			case 0x01: {txt += "Translating 2D Sprite [wk0=speed, wk1=size] (can work in screen space)\n"; break;}
			case 0x02: {txt += "3D Sprite, center is the bottom edge of texture\n"; break;}
			case 0x03: {txt += "Translating 3D Sprite [wk0=speed, wk1=??{0, 1}]\n"; break;}
			case 0x04: {txt += "Tile 2D Sprite in Screen Space (Only works in screen space)\n"; break;}
			case 0x05: {txt += "3D sprite, with additive blend mode forced on?\n"; break;}
			case 0x06: {txt += "2D sprite, follows path\n"; break;}
			case 0x07: {txt += "3D Sprite with Collisions\n"; break;}
			case 0x08: {txt += "Translating 3D Sprite on custom shape (shape generated from spline)\n"; break;}
			case 0x09: {txt += "3D Plane that translates then fades out\n"; break;}
			case 0x0A: {txt += "3D Sprite with trailing\n"; break;}
			case 0x0B: {txt += "2D Sprite with random rotation\n"; break;}
			case 0x0C: {txt += "Preset Effects\n"; break;}
			case 0x0D: {txt += "2D Sprite Moves Around in Volume\n"; break;}
			case 0x0E: {txt += "3D Screen Fade (Radius sets active area, cone is the direction of the fill)\n"; break;}
			case 0x0F: {txt += "2D Sprite, Texture Converted to Grey Scale\n"; break;}
			case 0x10: {txt += "2D Sprite Spawns on Floor (Floor Detection)\n"; break;}
			case 0x11: {txt += "Light Emitter (Colour Alpha Acts as Intensity)\n"; break;}
			case 0x12: {txt += "Pulsating Star Mesh\n"; break;}
			case 0x13: {txt += "Invalid on GC\n"; break;}
			case 0x14: {txt += "Floor Reflection\n"; break;}
			case 0x15: {txt += "2D Sprites Along Y Plane (Requires Random Volume Y to be > 0)\n"; break;}
			case 0x16: {txt += "2D Sprite, with Wobble Distortion\n"; break;}
			case 0x17: {txt += "2D Sprite Spawns in Screen Space (Requires Full Random Volume)\n"; break;}
			case 0x18: {txt += "2D Sprite RGB is Black (for shadows?)\n"; break;}
			case 0x19: {txt += "Line\n"; break;}
			case 0x1A: {txt += "<failed to work no parent error>\n"; break;}
			case 0x1B: {txt += "2D Sprite with Stretcher\n"; break;}
			case 0x40: {txt += "? dont see a difference\n"; break;}
			case 0x41: {txt += "? dont see a difference\n"; break;}
			case 0x42: {txt += "?\n"; break;}
			case 0x43: {txt += "? dont see a difference\n"; break;}
			case 0x44: {txt += "??\n"; break;}
			case 0x45: {txt += "same as 0E creates screen fade within an area\n"; break;}
			case 0x46: {txt += "? sprites are arranged in a quad\n"; break;}
			case 0x47: {txt += "? sprites are arranged in a quad\n"; break;}
			case 0x48: {txt += "2D Sprite with 3D rotation Controls\n"; break;}
			case 0x49: {txt += "? dont see a difference\n"; break;}
			case 0x4A: {txt += "Bumps Camera wk0=type{0,1,2} VEC0[2]=triggerZone_radius\n"; break;}
			case 0x4B: {txt += "2D Sprite, with Frame Selector (isolate a frame in texture sprite animation)\n"; break;}
			case 0x4C: {txt += "? dont see a difference\n"; break;}
			case 0x4D: {txt += "? dont see a difference\n"; break;}
			case 0x4E: {txt += "Cloth Physics (3d flag changes mesh generation?)\n"; break;}
			case 0x4F: {txt += "? dont see a difference\n"; break;}
			case 0xFC: {txt += "3D Screen Mesh (TEX_ID is replaced with SCR_MODEL_NO ? models in room?)\n"; break;}
			case 0xFD: {txt += "3D Effect Mesh Affected By Gravity\n"; break;}
			case 0xFE: {txt += "3D Effect Mesh Slingshot (position is the spawn position)\n"; break;}
			case 0xFF: {txt += "3D Effect Mesh as 3D Sprite (TEX_ID is replaced with EFM_ID ? models in core?)\n"; break;}
			default: {txt += "Doesn't Do Anything?\n";}
			}
		}

	/* TEX ID */ {
		ss.str(std::string());
		ss << std::uppercase << TO_HEX(tex_id, false, 2);
		lne = padString("  tex_id", varlen, " ", false) + " = 0x" + ss.str();
		txt += padString(lne, padlen, " ", false) + "; ";
		if (esp_id == 0xFF) {
			switch (tex_id) {
				case  0x01: {txt += "Wood plank\n"; break;}
				case  0x08: {txt += "Rock\n"; break;}
				case  0x0E: {txt += "Piece of wood\n"; break;}
				case  0x10: {txt += "Piece of glass\n"; break;}
				case  0x25: {txt += "Pick aura\n"; break;}
				case  0x3E: {txt += "Roach\n"; break;}
				default: {txt += "Internal Model\n";}
				}
			}
		else {
			switch (tex_id) {
				case 0x00: {txt += "Blood Splat 1\n"; break;}
				case 0x01: {txt += "Blood Splat 2\n"; break;}
				case 0x03: {txt += "Blood Splat 3\n"; break;}
				case 0x04: {txt += "Blood Spot 1\n"; break;}
				case 0x05: {txt += "Blood Spot 2\n"; break;}
				case 0x06: {txt += "Blood Splat 4\n"; break;}
				case 0x07: {txt += "Blood Splat 5\n"; break;}
				case 0x08: {txt += "Specular 1\n"; break;}
				case 0x09: {txt += "Blood Splat 6\n"; break;}
				case 0x0A: {txt += "Explosion 1\n"; break;}
				case 0x0B: {txt += "V Shaped Gradient\n"; break;}
				case 0x0C: {txt += "Blood Splat 7\n"; break;}
				case 0x0E: {txt += "Blood Splat 8\n"; break;}
				case 0x0F: {txt += "Blood Splat 9\n"; break;}
				case 0x10: {txt += "Blood Splat 10\n"; break;}
				case 0x12: {txt += "Bullet Hole\n"; break;}
				case 0x13: {txt += "Specular 2\n"; break;}
				case 0x16: {txt += "Blood Splat 11\n"; break;}
				case 0x17: {txt += "Specular 3\n"; break;}
				case 0x18: {txt += "Blood Splat 12\n"; break;}
				case 0x19: {txt += "Blood Splat 13\n"; break;}
				case 0x1B: {txt += "Water Ripple\n"; break;}
				case 0x1C: {txt += "Specular 4\n"; break;}
				case 0x1D: {txt += "Smoke 1\n"; break;}
				case 0x1E: {txt += "Smoke 2\n"; break;}
				case 0x1F: {txt += "Smoke 3\n"; break;}
				case 0x20: {txt += "Explosion 2\n"; break;}
				case 0x22: {txt += "Explosion 3\n"; break;}
				case 0x23: {txt += "Explosion 4\n"; break;}
				case 0x25: {txt += "Vertical Gradient\n"; break;}
				case 0x26: {txt += "Flame 1\n"; break;}
				case 0x28: {txt += "Flame 2\n"; break;}
				case 0x2C: {txt += "Explosion 5\n"; break;}
				case 0x2E: {txt += "Explosion 6\n"; break;}
				case 0x32: {txt += "Blended Square\n"; break;}
				case 0x50: {txt += "Dish\n"; break;}
				case 0x51: {txt += "Smoke 4\n"; break;}
				case 0x52: {txt += "Smoke 5\n"; break;}
				case 0x53: {txt += "Smoke 6\n"; break;}
				case 0x56: {txt += "Splash 1\n"; break;}
				case 0x57: {txt += "Splash 2\n"; break;}
				case 0x58: {txt += "Splash 3\n"; break;}
				case 0x59: {txt += "Splash 4\n"; break;}
				case 0x5A: {txt += "Splash 5\n"; break;}
				case 0x5F: {txt += "Splash 6\n"; break;}
				case 0x6F: {txt += "Bubbles\n"; break;}
				case 0x72: {txt += "Screen Static\n"; break;}
				case 0x79: {txt += "Specular 5\n"; break;}
				case 0x96: {txt += "Web\n"; break;}
				case 0xB1: {txt += "Transparent Circle\n"; break;}
				case 0xB2: {txt += "Circle\n"; break;}
				case 0xCD: {txt += "Smoke 7\n"; break;}
				case 0xCE: {txt += "Splash 7\n"; break;}
				case 0xE2: {txt += "Splash 8\n"; break;}
				case 0xE9: {txt += "Highlighted Gradient\n"; break;}
				case 0xF7: {txt += "Square\n"; break;}
				case 0xFC: {txt += "Square Smoke\n"; break;}
				case 0xFF: {txt += "Blended Circle\n"; break;}
				default: {txt += "Internal Texture\n";}
				}
			}
		}

	/* BLEND MODE */ {
		lne = padString("  blend_mode", varlen, " ", false) + " = " + to_string((int)blend_mode);
		txt += padString(lne, padlen, " ", false) + "; ";
		switch (blend_mode) {
			case 0x00: {txt += "Blend\n"; break;}
			case 0x01: {txt += "Additive\n"; break;}
			case 0x02: {txt += "Additive2\n"; break;}
			case 0x03: {txt += "Additive3\n"; break;}
			case 0x04: {txt += "Multiply\n"; break;}
			case 0x05: {txt += "Blend2\n"; break;}
			default: {txt += "Invalid Blend Mode?\n";}
			}
		}

	/* PARENT */ {
		lne = padString("  parent", varlen, " ", false) + " = " + to_string((int)parent);
		if (parent < 247) {
			txt += lne + "\n";
			}
		else {
			txt += padString(lne, padlen, " ", false) + "; ";
			switch (parent) {
				case 0xF8: {txt += "SCR_FST[6]\n"; break;}
				case 0xF9: {txt += "SCR_PREV2[4]\n"; break;}
				case 0xFA: {txt += "SCR_PREV1[5]\n"; break;}
				case 0xFB: {txt += "SCR_AFTER2[1]\n"; break;}
				case 0xFC: {txt += "SCR_AFTER1[2] SA\n"; break;}
				case 0xFD: {txt += "SCREEN[3] SC\n"; break;}
				case 0xFE: {txt += "WORLD WD\n"; break;}
				case 0xFF: {txt += "NULL NL\n"; break;}
				}
			}
		}

	/* PART ID */ {
		txt += padString("  part_id", varlen, " ", false) + " = " + to_string((int)part_id) + "\n";
		}

	/* FLAGS */ {
		if (!hide_unset || flag.flag01) {
			lne = padString("  enable_3d", varlen, " ", false) + " = ";
			if (flag.flag01) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Sprite orientation can be set\n";
			}
		if (!hide_unset || flag.flag02) {
			lne = padString("  flip_x", varlen, " ", false) + " = ";
			if (flag.flag02) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Sprite is flipped on along x axis\n";
			}
		if (!hide_unset || flag.flag03) {
			lne = padString("  flip_y", varlen, " ", false) + " = ";
			if (flag.flag03) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Sprite is flipped on along y axis\n";
			}
		if (!hide_unset || flag.flag04) {
			lne = padString("  flip_rnd_x", varlen, " ", false) + " = ";
			if (flag.flag04) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Sprite is flipped randomly on along x axis\n";
			}
		if (!hide_unset || flag.flag05) {
			lne = padString("  flip_rnd_y", varlen, " ", false) + " = ";
			if (flag.flag05) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Sprite is flipped randomly on along y axis\n";
			}
		if (!hide_unset || flag.flag06) {
			txt += padString("  null_mode", varlen, " ", false) + " = ";
			if (flag.flag06) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag07) {
			lne = padString("  light_on", varlen, " ", false) + " = ";
			if (flag.flag07) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Enables Lights on 3D Models\n";
			}
		if (!hide_unset || flag.flag08) {
			lne = padString("  color_x4", varlen, " ", false) + " = ";
			if (flag.flag08) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Multiplies RGB Channel by 4\n";
			}
		if (!hide_unset || flag.flag09) {
			txt += padString("  fp_no_disp", varlen, " ", false) + " = ";
			if (flag.flag09) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag10) {
			txt += padString("  fp_disp", varlen, " ", false) + " = ";
			if (flag.flag10) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag11) {
			txt += padString("  ot_underwater", varlen, " ", false) + " = ";
			if (flag.flag11) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag12) {
			txt += padString("  ot_water", varlen, " ", false) + " = ";
			if (flag.flag12) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag13) {
			txt += padString("  sim_lit", varlen, " ", false) + " = ";
			if (flag.flag13) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag14) {
			txt += padString("  nega", varlen, " ", false) + " = ";
			if (flag.flag14) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag15) {
			lne = padString("  enable_mask", varlen, " ", false) + " = ";
			if (flag.flag15) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Replaces Sprite Alpha with another\n";
			}
		if (!hide_unset || flag.flag16) {
			txt += padString("  alpha_draw", varlen, " ", false) + " = ";
			if (flag.flag16) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag17) {
			txt += padString("  tex_render", varlen, " ", false) + " = ";
			if (flag.flag17) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag18) {
			lne = padString("  alpha_x4", varlen, " ", false) + " = ";
			if (flag.flag18) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Multiplies A Channel by 4\n";
			}
		if (!hide_unset || flag.flag19) {
			txt += padString("  low_priority", varlen, " ", false) + " = ";
			if (flag.flag19) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag20) {
			lne = padString("  enable_25d", varlen, " ", false) + " = ";
			if (flag.flag20) {lne += "true";} else {lne += "false";}
			txt += padString(lne, padlen, " ", false) + "; Sprite Only Active on X, Z Axis\n";
			}
		if (!hide_unset || flag.flag21) {
			txt += padString("  alpha_clip", varlen, " ", false) + " = ";
			if (flag.flag21) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag22) {
			txt += padString("  z_draw", varlen, " ", false) + " = ";
			if (flag.flag22) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag23) {
			txt += padString("  ot_first", varlen, " ", false) + " = ";
			if (flag.flag23) {txt += "true\n";} else {txt += "false\n";}
			}
		if (!hide_unset || flag.flag24) {
			txt += padString("  alpha_draw2", varlen, " ", false) + " = ";
			if (flag.flag24) {txt += "true\n";} else {txt += "false\n";}
			}
		}

	/* TIME */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 18, " ", false) + "Animation Settings\n";

		lne = padString("  time", varlen, " ", false) + " = " + to_string(time);
		txt += padString(lne, padlen, " ", false) + "; Animation Start Time (10th of a second)\n";
		}

	/* LIFE TIME */ {
		lne = padString("  life_time", varlen, " ", false) + " = " + to_string(life_time);
		txt += padString(lne, padlen, " ", false) + "; Duration before unspawning (10th of a second)\n";
		}

	/* RELEASE TRIGGER */ {
		txt += padString("  release_trigger", varlen, " ", false) + " = " + to_string((int)release_trigger) + "\n";
		}

	/* ANIMATION RATE */ {
		txt += padString("  animation_rate", varlen, " ", false) + " = " + to_string((int)animation_rate) + "\n";
		}

	/* KIND (ENABLE CTRL) */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 16, " ", false) + "Control Settings\n";

		lne = padString("  kind", varlen, " ", false) + " = " + to_string((int)kind);
		txt += padString(lne, padlen, " ", false) + "; Enables Controls, such as spray and guided paths\n";
		}

	/* CTRL ID */ {
		if (kind == 1) {
			lne = padString("  ctr_id", varlen, " ", false) + " = " + to_string((int)ctr_id);
			txt += padString(lne, padlen, " ", false) + "; ";
			switch (path_no) {
				case 0x00: {txt += "Spray\n"; break;}
				case 0x01: {txt += "?\n"; break;}
				case 0x02: {txt += "Follow Path\n"; break;}
				case 0x42: {txt += "?\n"; break;}
				case 0x43: {txt += "?\n"; break;}
				case 0x44: {txt += "?\n"; break;}
				case 0x45: {txt += "?\n"; break;}
				case 0x4C: {txt += "?\n"; break;}
				case 0xFF: {txt += "?\n"; break;}
				default: {txt += "Invalid 'ctrl_id'\n";}
				}
			}
		}

	/* LIFE */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  life", varlen, " ", false) + " = " + to_string(life);
			txt += padString(lne, padlen, " ", false) + "; Duration before next spawn\n";
			}
		}

	/* INTERVAL */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  inter", varlen, " ", false) + " = " + to_string((int)inter);
			txt += padString(lne, padlen, " ", false) + "; Spawn Interval (10th a second)\n";
			}
		}

	/* RANDOM INTERVAL */ {
		if (inter != 0 && kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  r_inter", varlen, " ", false) + " = " + to_string((int)r_inter);
			txt += padString(lne, padlen, " ", false) + "; Random Spawn Interval (10th a second)\n";
			}
		}

	/* NUMBER */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  num", varlen, " ", false) + " = " + to_string((int)num);
			txt += padString(lne, padlen, " ", false) + "; Number of Spawns (0=auto)\n";
			}
		}

	/* ID FLAG */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  id_flag", varlen, " ", false) + " = " + to_string((int)id_flag);
			txt += padString(lne, padlen, " ", false) + "; ? Known Values (0, 1, 2, 3, 4)\n";
			}
		}

	/* DAMPEN SIZE */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  d_size", varlen, " ", false) + " = " + to_string((int)d_size) + "\n";
			}
		}

	/* DAMPEN SPEED */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  d_speed", varlen, " ", false) + " = " + to_string((int)d_speed) + "\n";
			}
		}

	/* DAMPEN COLOR */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  d_alpha", varlen, " ", false) + " = " + to_string((int)d_alpha) + "\n";
			}
		}

	/* DAMPEN INTERVAL */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  d_inter", varlen, " ", false) + " = " + to_string((int)d_inter) + "\n";
			}
		}

	/* PATH OWNER */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			// Separator
			txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
			txt += padString("", padlen - 4 - 13, " ", false) + "Path Settings\n";

			txt += padString("  path_own", varlen, " ", false) + " = " + to_string((int)path_own) + "\n";
			}
		}

	/* PATH NO */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  path_no", varlen, " ", false) + " = " + to_string((int)path_no);
			txt += padString(lne, padlen, " ", false) + "; ";
			switch (path_no) {
				case 0x00: {txt += "Tapered Spiral\n"; break;}
				case 0x01: {txt += "Circle\n"; break;}
				case 0x02: {txt += "Line\n"; break;}
				case 0x03: {txt += "Line (Center Aligned)\n"; break;}
				case 0x04: {txt += "S-Curve\n"; break;}
				case 0x05: {txt += "Tapered Line\n"; break;}
				case 0x06: {txt += "Quarter Circle\n"; break;}
				case 0x07: {txt += "Quarter Circle (Center Aligned)\n"; break;}
				case 0x08: {txt += "Half Circle\n"; break;}
				case 0x09: {txt += "Half Circle (Center Aligned)\n"; break;}
				case 0x0A: {txt += "Torus Knot\n"; break;}
				default: {txt += "Internal Spine Path\n";}
				}
			}
		}

	/* RANDOM PATH NO */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  rp", varlen, " ", false) + " = " + to_string((int)rp);
			txt += padString(lne, padlen, " ", false) + "; Random Path\n";
			}
		}

	/* PATH START */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  path_st", varlen, " ", false) + " = " + to_string((int)path_st);
			txt += padString(lne, padlen, " ", false) + "; normalize 0 -255, value is the distance along the spline the particle spawns)\n";
			}
		}

	/* PATH RANDOM */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			lne = padString("  path_rnd", varlen, " ", false) + " = " + to_string((int)path_rnd);
			txt += padString(lne, padlen, " ", false) + "; random range to position path_st, set to 255 to have the particle spawn all along the spline\n";
			}
		}

	/* PATH SCALE */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			ss.str(std::string());
			ss  << std::fixed << std::setprecision(dc_len) << path_scale[0];
			txt += padString("  path_scale", varlen, " ", false) + " = [";
			txt += ss.str() + ", ";
			ss.str(std::string());
			ss  << std::fixed << std::setprecision(dc_len) << path_scale[1];
			txt += ss.str() + ", ";
			ss.str(std::string());
			ss  << std::fixed << std::setprecision(dc_len) << path_scale[2];
			txt += ss.str() + "]\n";
			}
		}

	/* PATH ROTATION X */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  path_rotation_x", varlen, " ", false) + " = " + to_string((int)path_rotation_x) + "\n";
			}
		}

	/* PATH ROTATION Y */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  path_rotation_y", varlen, " ", false) + " = " + to_string((int)path_rotation_y) + "\n";
			}
		}

	/* PATH FLAG */ {
		if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  path_flag", varlen, " ", false) + " = " + to_string((int)path_flag) + "\n";
			}
		}

	/* POSITION */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 15, " ", false) + "Sprite Location\n";

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << position[0];
		txt += padString("  position", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << position[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << position[2];
		txt += ss.str() + "]\n";
		}

	/* RANDOM POSITION */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand[0];
		txt += padString("  rand", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand[2];
		txt += ss.str() + "]\n";
		}

	/* WIDTH */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 17, " ", false) + "Sprite Dimensions\n";

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << width;
		lne = padString("  width", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Width of Sprite Plane (MilliMetres)\n";
		}

	/* HEIGHT */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << width;
		lne = padString("  height", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Height of Sprite Plane (MilliMetres)\n";
		}

	/* RANDOM SIZE */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << r_size;
		lne = padString("  r_size", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Random Size Factor\n";
		}

	/* PLUS SIZE */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << plus;
		lne = padString("  plus", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Size Increase Factor\n";
		}

	/* PLUS SIZE DELAY */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << d_plus;
		lne = padString("  d_plus", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Size Increase Factor\n";
		}

	/* SPEED */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 15, " ", false) + "Sprite Movement\n";

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << speed[0];
		txt += padString("  speed", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << speed[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << speed[2];
		txt += ss.str() + "]\n";
		}

	/* SPEED DEAMPENING */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << speed_d;
		txt += padString("  speed_d", varlen, " ", false) + " = ";
		txt += ss.str() + "\n";
		}

	/* RANDOM SPEED */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_speed[0];
		txt += padString("  rand_speed", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_speed[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_speed[2];
		txt += ss.str() + "]\n";
		}

	/* SPEED ACCELERATION */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << speed_acceleration[0];
		txt += padString("  speed_accel", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << speed_acceleration[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << speed_acceleration[2];
		txt += ss.str() + "]\n";
		}

	/* RANDOM SPEED ACCELERATION */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_speed_acceleration[0];
		txt += padString("  rand_speed_accel", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_speed_acceleration[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_speed_acceleration[2];
		txt += ss.str() + "]\n";
		}

	/* ROTATION */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 18, " ", false) + "3D Sprite Rotation\n";

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rotation[0];
		txt += padString("  rotation", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rotation[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rotation[2];
		txt += ss.str() + "]\n";
		}

	/* RANDOM ROTATION */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_rotation[0];
		txt += padString("  rand_rotation", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_rotation[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_rotation[2];
		txt += ss.str() + "]\n";
		}

	/* ROTATION ACCELERATION */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rotation_acceleration[0];
		txt += padString("  rotation_accel", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rotation_acceleration[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rotation_acceleration[2];
		txt += ss.str() + "]\n";
		}

	/* RANDOM ROTATION ACCELERATION */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_rotation_acceleration[0];
		txt += padString("  rand_rotation_accel", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_rotation_acceleration[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rand_rotation_acceleration[2];
		txt += ss.str() + "]\n";
		}

	/* RGBA */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 13, " ", false) + "Sprite Colour\n";

		ss.str(std::string());
		ss << std::uppercase << TO_HEX(rgba[0], false, 1) << TO_HEX(rgba[1], false, 1) << TO_HEX(rgba[2], false, 1) << TO_HEX(rgba[3], false, 1);
		lne = padString("  rgba", varlen, " ", false) + " = 0x" + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Colour Tint\n";
		}

	/* D_RGBA[0] */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << d_rgba[0];
		lne = padString("  d_red", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Red Dampening\n";
		}

	/* D_RGBA[1] */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << d_rgba[1];
		lne = padString("  d_green", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Green Dampening\n";
		}

	/* D_RGBA[2] */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << d_rgba[2];
		lne = padString("  d_blue", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Blue Dampening\n";
		}

	/* D_RGBA[3] */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << d_rgba[3];
		lne = padString("  d_alpha", varlen, " ", false) + " = " + ss.str();
		txt += padString(lne, padlen, " ", false) + "; Alpha Dampening\n";
		}

	/* COLOR END FRAME */ {
		txt += padString("  color_end_frame", varlen, " ", false) + " = " + to_string(color_end_frame) + "\n";
		}

	/* COLOR START FRAME */ {
		txt += padString("  color_start_frame", varlen, " ", false) + " = " + to_string(color_start_frame) + "\n";
		}

	/* SIZE START FRAME */ {
		txt += padString("  size_start_frame", varlen, " ", false) + " = " + to_string(size_start_frame) + "\n";
		}

	/* SIM TYPE */ {
		lne = padString("  sim_type", varlen, " ", false) + " = " + to_string((int)sim_type);
		txt += padString(lne, padlen, " ", false) + "; ";
		switch (sim_type) {
			case 0x00: {txt += "NONE\n"; break;}
			case 0x01: {txt += "NORMAL\n"; break;}
			case 0x02: {txt += "OFFSET\n"; break;}
			case 0x03: {txt += "REPLACE\n"; break;}
			default: {txt += "Invalid Sim Type?\n";}
			}
		}

	/* SIM POWER */ {
		txt += padString("  sim_power", varlen, " ", false) + " = " + to_string((int)sim_power) + "\n";
		}

	/* SIM MASK */ {
		txt += padString("  tex_mask", varlen, " ", false) + " = " + to_string((int)tex_mask) + "\n";
		}

	/* COLOR IN */ {
		txt += padString("  color_in", varlen, " ", false) + " = " + to_string((int)color_in) + "\n";
		}

	/* COLOR OUT */ {
		txt += padString("  color_out", varlen, " ", false) + " = " + to_string((int)color_out) + "\n";
		}

	/* VEC0 */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 19, " ", false) + "'ESP_ID' Parameters\n";

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec0[0];
		lne = padString("  vec0_x", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Scale X\n"; break;}
			case 0x0B: {txt += padString(lne, padlen, " ", false) + "; Wobble X\n"; break;}
			case 0x0E: {txt += padString(lne, padlen, " ", false) + "; Delay\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Plane Width\n"; break;}
			case 0x16: {txt += padString(lne, padlen, " ", false) + "; Wobble X Direction\n"; break;}
			case 0x19: {
				if ((int)(vec0[0] * 10000.0f) != 0 && (int)(vec0[1] * 10000.0f) != 0 && (int)(vec0[2] * 10000.0f) != 0) {
					txt += padString(lne, padlen, " ", false) + "; Line End X Position\n"; break;
					} else {txt += lne + "; 0=auto to end point\n";}
				}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Upper Right Stretch X Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Rotation X\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; Plane Width\n"; break;}
			case 0xFD: {txt += padString(lne, padlen, " ", false) + "; Mesh X Scale\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; Start X Position\n"; break;}
			default: {txt += lne + "\n";}
			}
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec0[1];
		lne = padString("  vec0_y", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Scale Y\n"; break;}
			case 0x0B: {txt += padString(lne, padlen, " ", false) + "; Wobble Y\n"; break;}
			case 0x0E: {txt += padString(lne, padlen, " ", false) + "; Type?\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Leave as 0\n"; break;}
			case 0x16: {txt += padString(lne, padlen, " ", false) + "; Wobble Y Direction\n"; break;}
			case 0x19: {
				if ((int)(vec0[0] * 10000.0f) != 0 && (int)(vec0[1] * 10000.0f) != 0 && (int)(vec0[2] * 10000.0f) != 0) {
					txt += padString(lne, padlen, " ", false) + "; Line End Y Position\n"; break;
					} else {txt += lne + "\n";}
				}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Upper Right Stretch Y Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Speed X\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; Plane Height\n"; break;}
			case 0xFD: {txt += padString(lne, padlen, " ", false) + "; Mesh Y Scale\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; Start Y Position\n"; break;}
			default: {txt += lne + "\n";}
			}
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec0[2];
		lne = padString("  vec0_z", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Scale Z\n"; break;}
			case 0x0B: {txt += padString(lne, padlen, " ", false) + "; Texture Scale\n"; break;}
			case 0x0E: {txt += padString(lne, padlen, " ", false) + "; Radius\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Plane Height\n"; break;}
			case 0x16: {txt += padString(lne, padlen, " ", false) + "; Wobble Z Direction\n"; break;}
			case 0x19: {
				if ((int)(vec0[0] * 10000.0f) != 0 && (int)(vec0[1] * 10000.0f) != 0 && (int)(vec0[2] * 10000.0f) != 0) {
					txt += padString(lne, padlen, " ", false) + "; Line End Z Position\n"; break;
					} else {txt += lne + "\n";}
				}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Upper Right Stretch Z Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Amplitude X\n"; break;}
			case 0x4A: {txt += padString(lne, padlen, " ", false) + "; Trigger Zone Radius\n"; break;}
			case 0xFD: {txt += padString(lne, padlen, " ", false) + "; Mesh Z Scale\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; Start Z Position\n"; break;}
			default: {txt += lne + "\n";}
			}

		}


	/* VEC1 */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec1[0];
		lne = padString("  vec1_x", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Rotation X\n"; break;}
			case 0x0E: {txt += padString(lne, padlen, " ", false) + "; Leave as 0\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Plane X Position\n"; break;}
			case 0x19: {txt += padString(lne, padlen, " ", false) + "; Line Length\n"; break;}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Lower Right Stretch X Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Rotation Y\n"; break;}
			default: {txt += lne + "\n";}
			}

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec1[0];
		lne = padString("  vec1_y", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Rotation Y\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Plane Y Position\n"; break;}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Lower Right Stretch Y Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Speed Y\n"; break;}
			default: {txt += lne + "\n";}
			}

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec1[0];
		lne = padString("  vec1_y", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Rotation Z\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Plane Z Position\n"; break;}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Lower Right Stretch Y Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Amplitude Y\n"; break;}
			default: {txt += lne + "\n";}
			}

		}


	/* VEC2 */ {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec2[0];
		lne = padString("  vec2_x", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Rotation X\n"; break;}
			case 0x0E: {txt += padString(lne, padlen, " ", false) + "; Leave as 0\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Plane X Position\n"; break;}
			case 0x19: {txt += padString(lne, padlen, " ", false) + "; Line Length\n"; break;}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Lower Right Stretch X Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Rotation Y\n"; break;}
			default: {txt += lne + "\n";}
			}

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec2[1];
		lne = padString("  vec2_y", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Rotation Y\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Plane Y Position\n"; break;}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Lower Right Stretch Y Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Speed Y\n"; break;}
			default: {txt += lne + "\n";}
			}

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << vec2[2];
		lne = padString("  vec2_z", varlen, " ", false) + " = " + ss.str();
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Path Rotation Z\n"; break;}
			case 0x14: {txt += padString(lne, padlen, " ", false) + "; Plane Z Position\n"; break;}
			case 0x1B: {txt += padString(lne, padlen, " ", false) + "; Lower Right Stretch Z Position\n"; break;}
			case 0x48: {txt += padString(lne, padlen, " ", false) + "; Amplitude Y\n"; break;}
			default: {txt += lne + "\n";}
			}

		}


	/* WORK0 */ {


		ss.str(std::string());
		lne = padString("  work0", varlen, " ", false) + " = " + to_string((int)work0);

		switch (esp_id) {
			case 0x01: {txt += padString(lne, padlen, " ", false) + "; Speed\n"; break;}
			case 0x03: {txt += padString(lne, padlen, " ", false) + "; Speed\n"; break;}
			case 0x04: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (work0) {
					case 0: {txt += "upper left quarter only\n"; break;}
					case 1: {txt += "upper half only\n"; break;}
					case 2: {txt += "left only\n"; break;}
					case 3: {txt += "full\n"; break;}
					default: {txt += "Invalid Value?\n";}
					}
				break;
				}
			case 0x08: {txt += padString(lne, padlen, " ", false) + "; Texture Tiling X\n"; break;}
			case 0x0C: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (work0) {
					case 0x00: {txt += "NONE\n"; break;}
					case 0x01: {txt += "ROOM\n"; break;}
					case 0x02: {txt += "EM3A\n"; break;}
					case 0x03: {txt += "? parts\n"; break;}
					case 0x04: {txt += "PL01\n"; break;}
					case 0x05: {txt += "PL02\n"; break;}
					case 0x06: {txt += "PL03\n"; break;}
					case 0x07: {txt += "PL04\n"; break;}
					case 0x08: {txt += "PL05\n"; break;}
					case 0x09: {txt += "PL06\n"; break;}
					case 0x0A: {txt += "PL07\n"; break;}
					case 0x0B: {txt += "PL0A\n"; break;}
					case 0x0C: {txt += "PL0B\n"; break;}
					case 0x0D: {txt += "PL0D\n"; break;}
					case 0x0E: {txt += "PL0E\n"; break;}
					case 0x0F: {txt += "PL0F\n"; break;}
					case 0x10: {txt += "EM10\n"; break;}
					case 0x11: {txt += "EM12\n"; break;}
					case 0x12: {txt += "EM15\n"; break;}
					case 0x13: {txt += "EM16\n"; break;}
					case 0x14: {txt += "EM17\n"; break;}
					case 0x15: {txt += "EM18\n"; break;}
					case 0x16: {txt += "EM19\n"; break;}
					case 0x17: {txt += "EM1A\n"; break;}
					case 0x18: {txt += "EM1B\n"; break;}
					case 0x19: {txt += "EM20\n"; break;}
					case 0x1A: {txt += "EM22\n"; break;}
					case 0x1B: {txt += "EM23\n"; break;}
					case 0x1C: {txt += "EM24\n"; break;}
					case 0x1D: {txt += "EM25\n"; break;}
					case 0x1E: {txt += "EM26\n"; break;}
					case 0x1F: {txt += "EM27\n"; break;}
					case 0x20: {txt += "EM28\n"; break;}
					case 0x21: {txt += "EM29\n"; break;}
					case 0x22: {txt += "EM2A\n"; break;}
					case 0x23: {txt += "EM2B\n"; break;}
					case 0x24: {txt += "EM2C\n"; break;}
					case 0x25: {txt += "EM2D\n"; break;}
					case 0x26: {txt += "EM2E\n"; break;}
					case 0x27: {txt += "EM2F\n"; break;}
					case 0x28: {txt += "EM30\n"; break;}
					case 0x29: {txt += "EM31\n"; break;}
					case 0x2A: {txt += "EM32\n"; break;}
					case 0x2B: {txt += "EM34\n"; break;}
					case 0x2C: {txt += "EM35\n"; break;}
					case 0x2D: {txt += "EM36\n"; break;}
					case 0x2E: {txt += "EM38\n"; break;}
					case 0x2F: {txt += "EM39\n"; break;}
					case 0x30: {txt += "EM3B\n"; break;}
					case 0x31: {txt += "EM3C\n"; break;}
					case 0x32: {txt += "EM3D\n"; break;}
					case 0x33: {txt += "EM3E\n"; break;}
					case 0x34: {txt += "WEP00\n"; break;}
					case 0x35: {txt += "WEP01\n"; break;}
					case 0x36: {txt += "PARTS_NO[3]\n"; break;}
					case 0x37: {txt += "WEP03\n"; break;}
					case 0x38: {txt += "WEP04\n"; break;}
					case 0x39: {txt += "WEP05\n"; break;}
					case 0x3A: {txt += "WEP06\n"; break;}
					case 0x3B: {txt += "WEP07\n"; break;}
					case 0x3C: {txt += "WEP08\n"; break;}
					case 0x3D: {txt += "WEP09\n"; break;}
					case 0x3E: {txt += "WEP0A\n"; break;}
					case 0x3F: {txt += "WEP0B\n"; break;}
					case 0x40: {txt += "WEP0C\n"; break;}
					case 0x41: {txt += "WEP0D\n"; break;}
					case 0x42: {txt += "WEP0E\n"; break;}
					case 0x43: {txt += "WEP0F\n"; break;}
					case 0x44: {txt += "WEP10\n"; break;}
					case 0x45: {txt += "WEP11\n"; break;}
					case 0x46: {txt += "WEP12\n"; break;}
					case 0x47: {txt += "WEP13\n"; break;}
					case 0x48: {txt += "WEP14\n"; break;}
					case 0x49: {txt += "WEP15\n"; break;}
					case 0x4A: {txt += "WEP16\n"; break;}
					case 0x4B: {txt += "WEP17\n"; break;}
					case 0x4C: {txt += "WEP18\n"; break;}
					case 0x4D: {txt += "WEP19\n"; break;}
					case 0x4E: {txt += "WEP26\n"; break;}
					case 0x4F: {txt += "WEP27\n"; break;}
					case 0x50: {txt += "WEP28\n"; break;}
					case 0x51: {txt += "WEP29\n"; break;}
					case 0x52: {txt += "WEP30\n"; break;}
					case 0x53: {txt += "WEP33\n"; break;}
					case 0x54: {txt += "ET00\n"; break;}
					case 0x55: {txt += "ET01\n"; break;}
					case 0x56: {txt += "ET02\n"; break;}
					case 0x57: {txt += "ET03\n"; break;}
					case 0x58: {txt += "ET04\n"; break;}
					case 0x59: {txt += "ET05\n"; break;}
					case 0x5A: {txt += "ET06\n"; break;}
					case 0x5B: {txt += "ET07\n"; break;}
					case 0x5C: {txt += "ET08\n"; break;}
					case 0x5D: {txt += "ET09\n"; break;}
					case 0x5E: {txt += "ET0A\n"; break;}
					case 0x5F: {txt += "ET0B\n"; break;}
					case 0x60: {txt += "ET0C\n"; break;}
					case 0x61: {txt += "ET0D\n"; break;}
					case 0x62: {txt += "ET0E\n"; break;}
					case 0x63: {txt += "ET0F\n"; break;}
					case 0x64: {txt += "ET10\n"; break;}
					case 0x65: {txt += "ET11\n"; break;}
					case 0x66: {txt += "ET12\n"; break;}
					case 0x67: {txt += "ET13\n"; break;}
					case 0x68: {txt += "ET14\n"; break;}
					case 0x69: {txt += "ET15\n"; break;}
					case 0x6A: {txt += "ET16\n"; break;}
					case 0x6B: {txt += "ET17\n"; break;}
					case 0x6C: {txt += "ET18\n"; break;}
					case 0x6D: {txt += "ET19\n"; break;}
					case 0x6E: {txt += "ET1A\n"; break;}
					case 0x6F: {txt += "ET1B\n"; break;}
					case 0x70: {txt += "ET1C\n"; break;}
					case 0x71: {txt += "ET1D\n"; break;}
					case 0x72: {txt += "ET1E\n"; break;}
					case 0x73: {txt += "ET1F\n"; break;}
					case 0x74: {txt += "ET20\n"; break;}
					case 0x75: {txt += "ET21\n"; break;}
					case 0x76: {txt += "ET22\n"; break;}
					case 0x77: {txt += "ET23\n"; break;}
					case 0x78: {txt += "ET24\n"; break;}
					case 0x79: {txt += "ET25\n"; break;}
					case 0x7A: {txt += "ET26\n"; break;}
					case 0x7B: {txt += "ET27\n"; break;}
					case 0x7C: {txt += "ET28\n"; break;}
					case 0x7D: {txt += "ET29\n"; break;}
					case 0x7E: {txt += "ET2A\n"; break;}
					case 0x7F: {txt += "ET2B\n"; break;}
					case 0x80: {txt += "ET2C\n"; break;}
					case 0x81: {txt += "ET2D\n"; break;}
					case 0x82: {txt += "ET2E\n"; break;}
					case 0x83: {txt += "ET2F\n"; break;}
					case 0x84: {txt += "ET30\n"; break;}
					case 0x85: {txt += "ET31\n"; break;}
					case 0x86: {txt += "ET32\n"; break;}
					case 0x87: {txt += "ET33\n"; break;}
					case 0x88: {txt += "ET34\n"; break;}
					case 0x89: {txt += "ET35\n"; break;}
					case 0x8A: {txt += "ET36\n"; break;}
					case 0x8B: {txt += "ET37\n"; break;}
					case 0x8C: {txt += "ET38\n"; break;}
					case 0x8D: {txt += "ET39\n"; break;}
					case 0x8E: {txt += "ET3A\n"; break;}
					case 0x8F: {txt += "ET3B\n"; break;}
					case 0x90: {txt += "ET3C\n"; break;}
					case 0x91: {txt += "ET3D\n"; break;}
					case 0x92: {txt += "ET3E\n"; break;}
					case 0x93: {txt += "ET3F\n"; break;}
					case 0x94: {txt += "ET40\n"; break;}
					case 0x95: {txt += "ET41\n"; break;}
					case 0x96: {txt += "ET42\n"; break;}
					case 0x97: {txt += "ET43\n"; break;}
					case 0x98: {txt += "ET44\n"; break;}
					case 0x99: {txt += "ET45\n"; break;}
					case 0x9A: {txt += "ET46\n"; break;}
					case 0x9B: {txt += "ET47\n"; break;}
					case 0x9C: {txt += "ET48\n"; break;}
					case 0x9D: {txt += "ET49\n"; break;}
					case 0x9E: {txt += "ET4A\n"; break;}
					case 0x9F: {txt += "ET4B\n"; break;}
					case 0xA0: {txt += "ET4C\n"; break;}
					case 0xA1: {txt += "ET4D\n"; break;}
					case 0xA2: {txt += "ET4E\n"; break;}
					case 0xA3: {txt += "ET4F\n"; break;}
					case 0xA4: {txt += "ET50\n"; break;}
					case 0xA5: {txt += "ET51\n"; break;}
					case 0xA6: {txt += "ET52\n"; break;}
					case 0xA7: {txt += "ET53\n"; break;}
					case 0xA8: {txt += "ET54\n"; break;}
					case 0xA9: {txt += "ET55\n"; break;}
					case 0xAA: {txt += "ET56\n"; break;}
					case 0xAB: {txt += "ET57\n"; break;}
					case 0xAC: {txt += "ET58\n"; break;}
					case 0xAD: {txt += "ET59\n"; break;}
					case 0xAE: {txt += "ET5A\n"; break;}
					case 0xAF: {txt += "ET5B\n"; break;}
					case 0xB0: {txt += "ET5C\n"; break;}
					case 0xB1: {txt += "ET5D\n"; break;}
					case 0xB2: {txt += "ET5E\n"; break;}
					case 0xB3: {txt += "ET5F\n"; break;}
					case 0xB4: {txt += "ET60\n"; break;}
					case 0xB5: {txt += "ET61\n"; break;}
					case 0xB6: {txt += "ET62\n"; break;}
					case 0xB7: {txt += "ET63\n"; break;}
					case 0xB8: {txt += "ET64\n"; break;}
					case 0xB9: {txt += "ET65\n"; break;}
					case 0xBA: {txt += "ET66\n"; break;}
					case 0xBB: {txt += "ET67\n"; break;}
					case 0xBC: {txt += "ET68\n"; break;}
					case 0xBD: {txt += "ET69\n"; break;}
					case 0xBE: {txt += "ET6A\n"; break;}
					case 0xBF: {txt += "ET6B\n"; break;}
					case 0xC0: {txt += "ET6C\n"; break;}
					case 0xC1: {txt += "ET6D\n"; break;}
					case 0xC2: {txt += "ET6E\n"; break;}
					case 0xC3: {txt += "ET6F\n"; break;}
					case 0xC4: {txt += "EV00\n"; break;}
					case 0xC5: {txt += "EV01\n"; break;}
					case 0xC6: {txt += "EV02\n"; break;}
					case 0xC7: {txt += "EV03\n"; break;}
					case 0xC8: {txt += "OBM1F\n"; break;}
					case 0xC9: {txt += "OBM2B\n"; break;}
					case 0xCA: {txt += "OBM34\n"; break;}
					case 0xCB: {txt += "OBM4C\n"; break;}
					case 0xCC: {txt += "OBM66\n"; break;}
					case 0xCD: {txt += "OBM83\n"; break;}
					case 0xCE: {txt += "SUBSCR\n"; break;}
					case 0xCF: {txt += "DEBUG\n"; break;}
					case 0xD0: {txt += "NONE\n"; break;}
					default: {txt += "Invalid Value?\n";}
					}
				break;
				}
			case 0x0D: {txt += padString(lne, padlen, " ", false) + "; Speed\n"; break;}
			case 0x0F: {txt += padString(lne, padlen, " ", false) + "; Power\n"; break;}
			case 0x11: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (work0) {
					case 0: {txt += "Lights from Lit File\n"; break;}
					case 2: {txt += "Lights ON\n"; break;}
					case 3: {txt += "Lights OFF\n"; break;}
					default: {txt += "Invalid Value?\n";}
					}
				break;
				}
			case 0x12: {txt += padString(lne, padlen, " ", false) + "; Speed\n"; break;}
			case 0x16: {txt += padString(lne, padlen, " ", false) + "; Wobble Type\n"; break;}
			case 0x4B: {txt += padString(lne, padlen, " ", false) + "; Texture Frame Index\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; Mass\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; Force\n"; break;}
			default: {txt += lne + "\n";}
			}
		}


	/* WORK1 */ {
		ss.str(std::string());
		lne = padString("  work1", varlen, " ", false) + " = " + to_string((int)work1);

		switch (esp_id) {
			case 0x01: {txt += padString(lne, padlen, " ", false) + "; Size\n"; break;}
			case 0x03: {txt += padString(lne, padlen, " ", false) + "; Size\n"; break;}
			case 0x06: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (work1) {
					case 0x00: {txt += "Tapered Spiral\n"; break;}
					case 0x01: {txt += "Circle\n"; break;}
					case 0x02: {txt += "Line\n"; break;}
					case 0x03: {txt += "Line (Center Aligned)\n"; break;}
					case 0x04: {txt += "S-Curve\n"; break;}
					case 0x05: {txt += "Tapered Line\n"; break;}
					case 0x06: {txt += "Quarter Circle\n"; break;}
					case 0x07: {txt += "Quarter Circle (Center Aligned)\n"; break;}
					case 0x08: {txt += "Half Circle\n"; break;}
					case 0x09: {txt += "Half Circle (Center Aligned)\n"; break;}
					case 0x0A: {txt += "Torus Knot\n"; break;}
					default: {txt += "Internal Spine Path\n";}
					}
				break;
				}
			case 0x08: {txt += padString(lne, padlen, " ", false) + "; Texture Tiling X\n"; break;}
			case 0x0A: {txt += padString(lne, padlen, " ", false) + "; TransType{0} must be 0?\n"; break;}
			case 0x0C: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (work1) {
					case 0x00: {txt += "Blood Spurt\n"; break;}
					case 0x01: {txt += "Blood Splat\n"; break;}
					case 0x02: {txt += "Blood Splat 2\n"; break;}
					case 0x03: {txt += "Red Laser\n"; break;}
					case 0x04: {txt += "Water Splash\n"; break;}
					case 0x05: {txt += "Water Splash 2\n"; break;}
					case 0x06: {txt += "Screen Glare\n"; break;}
					case 0x07: {txt += "Screen Glare 2\n"; break;}
					case 0x08: {txt += "Screen Glare 3\n"; break;}
					case 0x09: {txt += "Screen Glare 4\n"; break;}
					case 0x0A: {txt += "Water Surface Explosion\n"; break;}
					case 0x0B: {txt += "Explosion with Debris\n"; break;}
					case 0x0C: {txt += "Burst of Smoke\n"; break;}
					case 0x0D: {txt += "Explosion with Debris 2\n"; break;}
					case 0x0E: {txt += "Water Surface Splash\n"; break;}
					case 0x0F: {txt += "Water Surface Splash 2\n"; break;}
					case 0x10: {txt += "Fire Explosion, Black Smoke\n"; break;}
					case 0x11: {txt += "Water Surface Splash 2\n"; break;}
					case 0x12: {txt += "Water Surface Ripples\n"; break;}
					case 0x13: {txt += "Water Surface Splash 3\n"; break;}
					case 0x14: {txt += "Water Surface Splash 4\n"; break;}
					case 0x15: {txt += "Water Surface Explosion 2\n"; break;}
					case 0x16: {txt += "Small Smoke Cloud\n"; break;}
					case 0x17: {txt += "Small Smoke Cloud 2\n"; break;}
					case 0x18: {txt += "Small Explosion\n"; break;}
					case 0x19: {txt += "Water Surface Splash 4\n"; break;}
					case 0x1A: {txt += "Ground Scurched Black\n"; break;}
					case 0x1B: {txt += "Screen Grain Effect\n"; break;}
					case 0x1C: {txt += "Blood Drop on Ground\n"; break;}
					case 0x1E: {txt += "Screen goes black\n"; break;}
					case 0x1F: {txt += "Mid Smoke Cloud\n"; break;}
					case 0x20: {txt += "Small Smoke Cloud Rotated randomly\n"; break;}
					case 0x21: {txt += "Pulsating Sparkle\n"; break;}
					case 0x22: {txt += "Small Water Surface Explosion\n"; break;}
					case 0x24: {txt += "Pulsating Sparkle 2\n"; break;}
					case 0x25: {txt += "Pulsating Sparkle 3\n"; break;}
					case 0x26: {txt += "Ground Scurched Black 2 With Fire\n"; break;}
					case 0x27: {txt += "Fire Explosion, Black Smoke 2\n"; break;}
					case 0x28: {txt += "Water Surface Explosion 3\n"; break;}
					case 0x2C: {txt += "Blue Pickup Aura\n"; break;}
					case 0x2E: {txt += "Blue Pickup Aura, Shrinks\n"; break;}
					case 0x2F: {txt += "Red Pickup Aura\n"; break;}
					case 0x30: {txt += "Red Pickup Aura, Shrinks\n"; break;}
					case 0x31: {txt += "Green Pickup Aura\n"; break;}
					case 0x32: {txt += "Green Pickup Aura, Shrinks\n"; break;}
					case 0x33: {txt += "White Pickup Aura\n"; break;}
					case 0x34: {txt += "Blood Drop on Ground 2\n"; break;}
					case 0x36: {txt += "Explosion with Debris 3\n"; break;}
					case 0x39: {txt += "Water Surface Explosion 4\n"; break;}
					case 0x3A: {txt += "Water Surface Splash 5\n"; break;}
					case 0x3B: {txt += "Multiple Sparks\n"; break;}
					case 0x3C: {txt += "Violent Screen Flashes (Lightning)\n"; break;}
					case 0x3D: {txt += "Short Burst Sparkle\n"; break;}
					case 0x3F: {txt += "Slow Screen Flashes (Lightning)\n"; break;}
					case 0x40: {txt += "Tiny Water Splash\n"; break;}
					case 0x41: {txt += "Tiny Water Splash 2\n"; break;}
					case 0x42: {txt += "Mid Water Splash, Leaves Residue\n"; break;}
					case 0x43: {txt += "Mid Water Splash, Leaves Residue (Vertical)\n"; break;}
					case 0x44: {txt += "Small Water Splash, Leaves Residue (Vertical)\n"; break;}
					case 0x45: {txt += "Green Splashes\n"; break;}
					case 0x46: {txt += "Light Blue item Pickup\n"; break;}
					case 0x47: {txt += "Light Blue item Pickup (Shrinks)\n"; break;}
					case 0x4D: {txt += "Extend Time Pickup\n"; break;}
					case 0x4E: {txt += "Flashing Red Dot\n"; break;}
					case 0x4F: {txt += "Flashing Red Dot 1\n"; break;}
					case 0x50: {txt += "Flashing Red Dot 2\n"; break;}
					case 0x51: {txt += "Screen Flashing White\n"; break;}
					case 0x52: {txt += "Yellow Shooting Plane, Random Orientation\n"; break;}
					case 0x57: {txt += "Small Explosion 2\n"; break;}
					case 0x58: {txt += "Blood Drop on Ground 3\n"; break;}
					case 0x87: {txt += "Black on White Dot, oscillating size\n"; break;}
					case 0x8E: {txt += "Circle Made of Dots\n"; break;}
					case 0xF3: {txt += "Thermal Vision Screen (Noisy Purple Screen)\n"; break;}
					case 0xF5: {txt += "Amber Screen\n"; break;}
					case 0xF6: {txt += "Amber Screen + Lava on Floor\n"; break;}
					case 0xF9: {txt += "Falling Green Smoke\n"; break;}
					case 0xFA: {txt += "Enveloping Grey Smoke\n"; break;}
					case 0xFB: {txt += "Dark Brown Smoke + Slime and God Rays\n"; break;}
					default: {txt += "Internal Effect\n";}
					}
				break;
				}
			case 0x11: {txt += padString(lne, padlen, " ", false) + "; Lit_ID\n"; break;}
			case 0x16: {txt += padString(lne, padlen, " ", false) + "; Wobble X Axis\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; Friction\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; Delay\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* WORK2 */ {
		ss.str(std::string());
		lne = padString("  work2", varlen, " ", false) + " = " + to_string((int)work2);
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; ?\n"; break;}
			case 0x08: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (work2) {
					case 0x00: {txt += "Texture Mask Moves\n"; break;}
					case 0x01: {txt += "Texture Mask is Fixed\n"; break;}
					default: {txt += "Invalid Value?\n";}
					}
				break;
				}
			case 0x0A: {txt += padString(lne, padlen, " ", false) + "; Blend Mode\n"; break;}
			case 0x0C: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (work2) {
					case 0x00: {txt += "TransTypeX: NORMAL\n"; break;}
					case 0x01: {txt += "TransTypeX: NEGA\n"; break;}
					case 0x02: {txt += "TransTypeX: R-NRML\n"; break;}
					case 0x03: {txt += "TransTypeX: R-OFST\n"; break;}
					default: {txt += "Invalid Value?\n";}
					}
				break;
				}
			case 0x11: {txt += padString(lne, padlen, " ", false) + "; LightId\n"; break;}
			case 0x16: {txt += padString(lne, padlen, " ", false) + "; Wobble Y Axis\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; ?\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; ?\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* WORK3 */ {
		ss.str(std::string());
		lne = padString("  work3", varlen, " ", false) + " = " + to_string((int)work3);
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; ?\n"; break;}
			case 0x0A: {txt += padString(lne, padlen, " ", false) + "; Blend Mode\n"; break;}
			case 0x0C: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (work3) {
					case 0x00: {txt += "TransTypeY: NORMAL\n"; break;}
					case 0x01: {txt += "TransTypeY: NEGA\n"; break;}
					case 0x02: {txt += "TransTypeY: R-NRML\n"; break;}
					case 0x03: {txt += "TransTypeY: R-OFST\n"; break;}
					default: {txt += "Invalid Value?\n";}
					}
				break;
				}
			case 0x10: {txt += padString(lne, padlen, " ", false) + "; TransType{0,1,2}\n"; break;}
			case 0x11: {txt += padString(lne, padlen, " ", false) + "; LightType\n"; break;}
			case 0x16: {txt += padString(lne, padlen, " ", false) + "; Alpha Dampen\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; ?\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; Spin\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* WORK4 */ {
		ss.str(std::string());
		lne = padString("  work4", varlen, " ", false) + " = " + to_string((int)work4);
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Speed\n"; break;}
			case 0x08: {txt += padString(lne, padlen, " ", false) + "; SpeedX\n"; break;}
			case 0x16: {txt += padString(lne, padlen, " ", false) + "; Alpha Decay?\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; ?\n"; break;}
			case 0xFC: {txt += padString(lne, padlen, " ", false) + "; Ambient\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; Gravity\n"; break;}
			case 0xFF: {txt += padString(lne, padlen, " ", false) + "; Ambient\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* WORK5 */ {
		ss.str(std::string());
		lne = padString("  work5", varlen, " ", false) + " = " + to_string((int)work5);
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Acceleration\n"; break;}
			case 0x08: {txt += padString(lne, padlen, " ", false) + "; SpeedY\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; ?\n"; break;}
			case 0xFE: {txt += padString(lne, padlen, " ", false) + "; Bounce\n"; break;}
			case 0xFF: {txt += padString(lne, padlen, " ", false) + "; TextureMap Override\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* WORK6 */ {
		ss.str(std::string());
		lne = padString("  work6", varlen, " ", false) + " = " + to_string((int)work6);
		switch (esp_id) {
			case 0x06: {txt += padString(lne, padlen, " ", false) + "; Random Acceleration\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; Gravity?\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* SP0 */ {
		// Separator
		txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
		txt += padString("", padlen - 4 - 17, " ", false) + "Sprite Parameters\n";

		ss.str(std::string());
		lne = padString("  sp0", varlen, " ", false) + " = " + to_string((int)sp0);

		switch (esp_id) {
			case 0x07: {
				txt += padString(lne, padlen, " ", false) + "; ";
				switch (sp0) {
					case 0: {txt += "collides with floor\n"; break;}
					case 1: {txt += "disabled,collides with room\n"; break;}
					case 2: {txt += "collide with room\n"; break;}
					default: {txt += "Invalid Value?\n";}
					}
				break;
				}
			case 0x10: {txt += padString(lne, padlen, " ", false) + "; Leave as 0\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* SP1 */ {
		ss.str(std::string());
		lne = padString("  sp1", varlen, " ", false) + " = " + to_string((int)sp1);

		switch (esp_id) {
			case 0x07: {txt += padString(lne, padlen, " ", false) + "; EstCall\n"; break;}
			case 0x4E: {txt += padString(lne, padlen, " ", false) + "; Wind\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* SP2 */ {
		ss.str(std::string());
		lne = padString("  sp2", varlen, " ", false) + " = " + to_string((int)sp2);

		switch (esp_id) {
			case 0x07: {txt += padString(lne, padlen, " ", false) + "; SeType\n"; break;}
			default: {txt += lne + "\n";}
			}
		}

	/* LIFE1 */ {
		//if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  sp3", varlen, " ", false) + " = " + to_string(unk24) + "\n";
		//	}
		}

	/* LIFE2 */ {
		//if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  sp4", varlen, " ", false) + " = " + to_string(unk25) + "\n";
		//	}
		}

	/* LIFE3 */ {
		//if (kind == 1 && (ctr_id == 0 || ctr_id == 2)) {
			txt += padString("  sp5", varlen, " ", false) + " = " + to_string(unk26) + "\n";
		//	}
		}

	if (savefile == L"") {
		std::cout << txt << std::endl;

		}
	else {

		bytestream s;
		s.writeFileW(savefile, 0, txt.size(), (char*)txt.c_str());

		}


	return true;
	}

bool fmtEST_Effect::import_txt (std::wstring openfileW) {
	bool isGood = false;
	bytestream f;

	if (f.openFileW(openfileW)) {
		unsigned long i;
		std::string s;
		std::string key;
		std::string val;
		std::vector<std::string> ss;
		int log = 0;
		while (!f.eos()) {

			// Read Line
			s = f.readline();

			// Remove Comment
			i = s.find(";");
			if (i != std::string::npos) {
				s = s.substr(0, i);
				}

			// Remove White Space
			s = trim(s);

			// Parse Line
			i = s.find("=");
			if (i != std::string::npos) {
				// Key = Value

				// Check Log state
				if (log == 1) {

					// split key from value
					key = tolower(trim(s.substr(0, i)));
					val = "";
					if (i + 1 < s.size()) {
						val = trim(s.substr(i + 1));
						}

					if (val != "") {
						if (key =="state") {state = convert_to<int>(val);}
						else if (key =="esp_id") {esp_id = convert_to<int>(val);}
						else if (key =="tex_id") {tex_id = convert_to<int>(val);}
						else if (key =="time") {time = convert_to<int>(val);}
						else if (key =="part_id") {part_id = convert_to<int>(val);}
						else if (key =="parent") {parent = convert_to<int>(val);}
						else if (key =="enable_3d") {flag.flag01 = convert_to<bool>(tolower(val));}
						else if (key =="flip_x") {flag.flag02 = convert_to<bool>(tolower(val));}
						else if (key =="flip_y") {flag.flag03 = convert_to<bool>(tolower(val));}
						else if (key =="flip_rnd_x") {flag.flag04 = convert_to<bool>(tolower(val));}
						else if (key =="flip_rnd_y") {flag.flag05 = convert_to<bool>(tolower(val));}
						else if (key =="null_mode") {flag.flag06 = convert_to<bool>(tolower(val));}
						else if (key =="light_on") {flag.flag07 = convert_to<bool>(tolower(val));}
						else if (key =="color_x4") {flag.flag08 = convert_to<bool>(tolower(val));}
						else if (key =="fp_no_disp") {flag.flag09 = convert_to<bool>(tolower(val));}
						else if (key =="fp_disp") {flag.flag10 = convert_to<bool>(tolower(val));}
						else if (key =="ot_underwater") {flag.flag11 = convert_to<bool>(tolower(val));}
						else if (key =="ot_water") {flag.flag12 = convert_to<bool>(tolower(val));}
						else if (key =="sim_lit") {flag.flag13 = convert_to<bool>(tolower(val));}
						else if (key =="nega") {flag.flag14 = convert_to<bool>(tolower(val));}
						else if (key =="enable_mask") {flag.flag15 = convert_to<bool>(tolower(val));}
						else if (key =="alpha_draw") {flag.flag16 = convert_to<bool>(tolower(val));}
						else if (key =="tex_render") {flag.flag17 = convert_to<bool>(tolower(val));}
						else if (key =="alpha_x4") {flag.flag18 = convert_to<bool>(tolower(val));}
						else if (key =="low_priority") {flag.flag19 = convert_to<bool>(tolower(val));}
						else if (key =="enable_25d") {flag.flag20 = convert_to<bool>(tolower(val));}
						else if (key =="alpha_clip") {flag.flag21 = convert_to<bool>(tolower(val));}
						else if (key =="z_draw") {flag.flag22 = convert_to<bool>(tolower(val));}
						else if (key =="ot_first") {flag.flag23 = convert_to<bool>(tolower(val));}
						else if (key =="alpha_draw2") {flag.flag24 = convert_to<bool>(tolower(val));}
						else if (key =="position") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								position[0] = convert_to<float>(ss.at(0));
								position[1] = convert_to<float>(ss.at(1));
								position[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="rand") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								rand[0] = convert_to<float>(ss.at(0));
								rand[1] = convert_to<float>(ss.at(1));
								rand[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="speed") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								speed[0] = convert_to<float>(ss.at(0));
								speed[1] = convert_to<float>(ss.at(1));
								speed[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="speed_d") {speed_d = convert_to<float>(ss.at(0));}
						else if (key =="rand_speed") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								rand_speed[0] = convert_to<float>(ss.at(0));
								rand_speed[1] = convert_to<float>(ss.at(1));
								rand_speed[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="speed_accel") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								speed_acceleration[0] = convert_to<float>(ss.at(0));
								speed_acceleration[1] = convert_to<float>(ss.at(1));
								speed_acceleration[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="rand_speed_accel") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								rand_speed_acceleration[0] = convert_to<float>(ss.at(0));
								rand_speed_acceleration[1] = convert_to<float>(ss.at(1));
								rand_speed_acceleration[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="rotation") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								rotation[0] = convert_to<float>(ss.at(0));
								rotation[1] = convert_to<float>(ss.at(1));
								rotation[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="rand_rotation") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								rand_rotation[0] = convert_to<float>(ss.at(0));
								rand_rotation[1] = convert_to<float>(ss.at(1));
								rand_rotation[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="rotation_accel") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								rotation_acceleration[0] = convert_to<float>(ss.at(0));
								rotation_acceleration[1] = convert_to<float>(ss.at(1));
								rotation_acceleration[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="rand_rotation_accel") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								rand_rotation_acceleration[0] = convert_to<float>(ss.at(0));
								rand_rotation_acceleration[1] = convert_to<float>(ss.at(1));
								rand_rotation_acceleration[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="width") {width = convert_to<float>(ss.at(0));}
						else if (key =="height") {height = convert_to<float>(ss.at(0));}
						else if (key =="r_size") {r_size = convert_to<float>(ss.at(0));}
						else if (key =="plus") {plus = convert_to<float>(ss.at(0));}
						else if (key =="d_plus") {d_plus = convert_to<float>(ss.at(0));}
						else if (key =="rgba") {
							uint32_t rgba_long = convert_to<unsigned long>(val);
							rgba[0] =(rgba_long >> 24) & 0xFF;
							rgba[1] = (rgba_long >> 16) & 0xFF;
							rgba[2] = (rgba_long >> 8) & 0xFF;
							rgba[3] = rgba_long & 0xFF;
							}
						else if (key =="d_red") {d_rgba[0] = convert_to<float>(val);}
						else if (key =="d_green") {d_rgba[1] = convert_to<float>(val);}
						else if (key =="d_blue") {d_rgba[2] = convert_to<float>(val);}
						else if (key =="d_alpha") {d_rgba[3] = convert_to<float>(val);}
						else if (key =="color_end_frame") {color_end_frame = convert_to<int>(val);}
						else if (key =="color_start_frame") {color_start_frame = convert_to<int>(val);}
						else if (key =="size_start_frame") {size_start_frame = convert_to<int>(val);}
						else if (key =="life_time") {life_time = convert_to<int>(val);}
						else if (key =="animation_rate") {animation_rate = convert_to<int>(val);}
						else if (key =="release_trigger") {release_trigger = convert_to<int>(val);}
						else if (key =="blend_mode") {blend_mode = convert_to<int>(val);}
						else if (key =="sim_type") {sim_type = convert_to<int>(val);}
						else if (key =="sim_power") {sim_power = convert_to<int>(val);}
						else if (key =="tex_mask") {tex_mask = convert_to<int>(val);}
						else if (key =="color_in") {color_in = convert_to<int>(val);}
						else if (key =="color_out") {color_out = convert_to<int>(val);}
						else if (key =="work0") {work0 = convert_to<int>(val);}
						else if (key =="work1") {work1 = convert_to<int>(val);}
						else if (key =="work2") {work2 = convert_to<int>(val);}
						else if (key =="work3") {work3 = convert_to<int>(val);}
						else if (key =="work4") {work4 = convert_to<int>(val);}
						else if (key =="work5") {work5 = convert_to<int>(val);}
						else if (key =="work6") {work6 = convert_to<int>(val);}
						else if (key =="vec0_x") {vec0[0] = convert_to<float>(val);}
						else if (key =="vec0_y") {vec0[1] = convert_to<float>(val);}
						else if (key =="vec0_z") {vec0[2] = convert_to<float>(val);}
						else if (key =="vec1_x") {vec1[0] = convert_to<float>(val);}
						else if (key =="vec1_y") {vec1[1] = convert_to<float>(val);}
						else if (key =="vec1_z") {vec1[2] = convert_to<float>(val);}
						else if (key =="vec2_x") {vec2[0] = convert_to<float>(val);}
						else if (key =="vec2_y") {vec2[1] = convert_to<float>(val);}
						else if (key =="vec2_z") {vec2[2] = convert_to<float>(val);}
						else if (key =="sp0") {sp0 = convert_to<int>(val);}
						else if (key =="sp1") {sp1 = convert_to<int>(val);}
						else if (key =="sp2") {sp2 = convert_to<int>(val);}
						else if (key =="sp3") {sp3 = convert_to<int>(val);}
						else if (key =="path_own") {path_own = convert_to<int>(val);}
						else if (key =="path_no") {path_no = convert_to<int>(val);}
						else if (key =="path_st") {path_st = convert_to<int>(val);}
						else if (key =="path_rnd") {path_rnd = convert_to<int>(val);}
						else if (key =="kind") {kind = convert_to<int>(val);}
						else if (key =="ctr_id") {ctr_id = convert_to<int>(val);}
						else if (key =="id_flag") {id_flag = convert_to<int>(val);}
						else if (key =="inter") {inter = convert_to<int>(val);}
						else if (key =="num") {num = convert_to<int>(val);}
						else if (key =="rp") {rp = convert_to<int>(val);}
						else if (key =="life") {life = convert_to<int>(val);}
						else if (key =="sp4") {unk24 = convert_to<int>(val);}
						else if (key =="sp5") {unk25 = convert_to<int>(val);}
						else if (key =="sp6") {unk26 = convert_to<int>(val);}
						else if (key =="path_scale") {
							ss = split(val, " ,[{()}]");
							if (ss.size() >= 3) {
								path_scale[0] = convert_to<float>(ss.at(0));
								path_scale[1] = convert_to<float>(ss.at(1));
								path_scale[2] = convert_to<float>(ss.at(2));
								}
							}
						else if (key =="d_size") {d_size = convert_to<int>(val);}
						else if (key =="d_speed") {d_speed = convert_to<int>(val);}
						else if (key =="d_alpha") {d_alpha = convert_to<int>(val);}
						else if (key =="d_inter") {d_inter = convert_to<int>(val);}
						else if (key =="r_inter") {r_inter = convert_to<int>(val);}
						else if (key =="path_rotation_x") {path_rotation_x = convert_to<int>(val);}
						else if (key =="path_rotation_y") {path_rotation_y = convert_to<int>(val);}
						else if (key =="path_flag") {path_flag = convert_to<int>(val);}







						}
					}
				}
			else if (s.find("[") != std::string::npos && s.find("]") != std::string::npos) {
				// Section

				// check if section is valid
				if (toupper(s) == "[SST]") {
					log = 1;
					}
				else {
					log = 0;
					}
				}

			}

		isGood = true;
		f.close();
		} else {std::wcout << L"failed to open file: \t" << openfileW << std::endl;}
	return isGood;
	}

fmtEST::fmtEST () {
	table0_count = 0;
	table1_count = 0;
	table2_count = 0;
	table3_count = 0;
	unk05 = 0;
	unk06 = 0;
	unk07 = 254;
	unk08 = 0; // Always 0
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;
	rotation[0] = 0.0f;
	rotation[1] = 0.0f;
	rotation[2] = 0.0f;
	unk40 = 0;
	unk41 = 16;
	unk42 = 0;
	unk43 = 0;
	unk44 = 0;
	unk45 = 0;
	}

size_t fmtEST::size () {
	/*
		calculate block size
	*/
	size_t nsize = 48 + ((table0.size() + table1.size() + table2.size() + table3.size()) * 300);
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

void fmtEST::read_est_entry (bytestream &f) {
	//size_t p = f.tell();
	table0_count = f.readUshort();
	table1_count = f.readUshort();
	table2_count = f.readUshort();
	table3_count = f.readUshort();
	unk05 = f.readUbyte();
	unk06 = f.readUbyte();
	unk07 = f.readUbyte();
	unk08 = f.readUbyte();
	position[0] = f.readfloat();
	position[1] = f.readfloat();
	position[2] = f.readfloat();
	rotation[0] = f.readfloat();
	rotation[1] = f.readfloat();
	rotation[2] = f.readfloat();
	unk40 = f.readUbyte();
	unk41 = f.readUbyte();
	unk42 = f.readUbyte();
	unk43 = f.readUbyte();
	unk44 = f.readUlong();
	unk45 = f.readUlong();

	if (table0_count > 0) {
		table0 = std::vector<fmtEST_Effect>(table0_count);
		for (unsigned int i = 0; i < table0_count; i++) {
			table0.at(i).read_esp_data(f);
			}
		}

	if (table1_count > 1) {
		table1 = std::vector<fmtEST_Effect>(table1_count);
		for (unsigned int i = 0; i < table1_count; i++) {
			table1.at(i).read_esp_data(f);
			}
		}

	if (table2_count > 2) {
		table2 = std::vector<fmtEST_Effect>(table2_count);
		for (unsigned int i = 0; i < table2_count; i++) {
			table2.at(i).read_esp_data(f);
			}
		}

	if (table3_count > 3) {
		table3 = std::vector<fmtEST_Effect>(table3_count);
		for (unsigned int i = 0; i < table3_count; i++) {
			table3.at(i).read_esp_data(f);
			}
		}

	}

void fmtEST::write_est_entry (bytestream &s) {
	size_t pos = s.tell();
	s.writeshort(table0_count = table0.size());
	s.writeshort(table1_count = table1.size());
	s.writeshort(table2_count = table2.size());
	s.writeshort(table3_count = table3.size());
	s.writebyte(unk05);
	s.writebyte(unk06);
	s.writebyte(unk07);
	s.writebyte(unk08);
	s.writefloat(position[0]);
	s.writefloat(position[1]);
	s.writefloat(position[2]);
	s.writefloat(rotation[0]);
	s.writefloat(rotation[1]);
	s.writefloat(rotation[2]);
	s.writebyte(unk40);
	s.writebyte(unk41);
	s.writebyte(unk42);
	s.writebyte(unk43);
	s.writelong(unk44);
	s.writelong(unk45);
	for (unsigned int i = 0; i < table0_count; i++) {table0[i].write_esp_data(s);}
	for (unsigned int i = 0; i < table1_count; i++) {table1[i].write_esp_data(s);}
	for (unsigned int i = 0; i < table2_count; i++) {table2[i].write_esp_data(s);}
	for (unsigned int i = 0; i < table3_count; i++) {table3[i].write_esp_data(s);}
	unsigned int pad = (32-((s.tell() - pos) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0);}
	}

void fmtEST::repr () {
	std::cout << "CoordSpace:   \t" << unk07 << std::endl;
	std::cout << "Position: \t[" << position[0] << ", " << position[1] << ", " << position[2] << "]" << std::endl;
	std::cout << "Rotation: \t[" << rotation[0] << ", " << rotation[1] << ", " << rotation[2] << "]" << std::endl;
	std::cout << "____________________________________________" << std::endl;
	std::cout << "table0:   \t" << table0_count << std::endl;
	std::cout << "\tstate\tesp_id\ttex_id\tunk13\ttime\tparent\tpart_id\t";
	std::cout << "flag\tposition\trand\tspeed\tspeed_d\trand_speed\t";
	std::cout << "speed_acceleration\trand_speed_acceleration\trotation\t";
	std::cout << "rand_rotation\trotation_acceleration\t";
	std::cout << "rand_rotation_acceleration\twidth\theight\t";
	std::cout << "r_size\tplus\td_plus\trgba\td_rgba\tcolor_end_frame\t";
	std::cout << "color_start_frame\tunk14\tsize_start_frame\tlife_time\t";
	std::cout << "unk15\tunk16\tunk17\tanimation_rate\tunk18\tunk19\t";
	std::cout << "release_trigger\tunk20\tblend_mode\tsim_type\tsim_power\t";
	std::cout << "tex_mask\tcolor_in\tcolor_out\twork0\twork1\twork2\t";
	std::cout << "work3\twork4\twork5\twork6\tvec0\tvec1\tvec2\tsp0\t";
	std::cout << "sp1\tsp2\tsp3\tunk21\tpath_own\tpath_no\tpath_st\t";
	std::cout << "path_rnd\tkind\tctr_id\tunk22\tid_flag\tinter\tnum\t";
	std::cout << "rp\tunk23\tlife\tunk24\tunk25\tunk26\tpath_scale\t";
	std::cout << "d_size\td_speed\td_alpha\td_inter\tr_inter\t";
	std::cout << "path_rotation_x\tpath_rotation_y\tpath_flag\t\n" << std::endl;
	for (unsigned int i = 0; i < table0_count; i++) {table0[i].repr();}
	std::cout << "____________________________________________" << std::endl;
	std::cout << "table1:   \t" << table1_count << std::endl;
	std::cout << "\tstate\tesp_id\ttex_id\tunk13\ttime\tparent\tpart_id\t";
	std::cout << "flag\tposition\trand\tspeed\tspeed_d\trand_speed\t";
	std::cout << "speed_acceleration\trand_speed_acceleration\trotation\t";
	std::cout << "rand_rotation\trotation_acceleration\t";
	std::cout << "rand_rotation_acceleration\twidth\theight\t";
	std::cout << "r_size\tplus\td_plus\trgba\td_rgba\tcolor_end_frame\t";
	std::cout << "color_start_frame\tunk14\tsize_start_frame\tlife_time\t";
	std::cout << "unk15\tunk16\tunk17\tanimation_rate\tunk18\tunk19\t";
	std::cout << "release_trigger\tunk20\tblend_mode\tsim_type\tsim_power\t";
	std::cout << "tex_mask\tcolor_in\tcolor_out\twork0\twork1\twork2\t";
	std::cout << "work3\twork4\twork5\twork6\tvec0\tvec1\tvec2\tsp0\t";
	std::cout << "sp1\tsp2\tsp3\tunk21\tpath_own\tpath_no\tpath_st\t";
	std::cout << "path_rnd\tkind\tctr_id\tunk22\tid_flag\tinter\tnum\t";
	std::cout << "rp\tunk23\tlife\tunk24\tunk25\tunk26\tpath_scale\t";
	std::cout << "d_size\td_speed\td_alpha\td_inter\tr_inter\t";
	std::cout << "path_rotation_x\tpath_rotation_y\tpath_flag\t\n" << std::endl;
	for (unsigned int i = 0; i < table1_count; i++) {table1[i].repr();}
	std::cout << "____________________________________________" << std::endl;
	std::cout << "table2:   \t" << table0_count << std::endl;
	std::cout << "\tstate\tesp_id\ttex_id\tunk13\ttime\tparent\tpart_id\t";
	std::cout << "flag\tposition\trand\tspeed\tspeed_d\trand_speed\t";
	std::cout << "speed_acceleration\trand_speed_acceleration\trotation\t";
	std::cout << "rand_rotation\trotation_acceleration\t";
	std::cout << "rand_rotation_acceleration\twidth\theight\t";
	std::cout << "r_size\tplus\td_plus\trgba\td_rgba\tcolor_end_frame\t";
	std::cout << "color_start_frame\tunk14\tsize_start_frame\tlife_time\t";
	std::cout << "unk15\tunk16\tunk17\tanimation_rate\tunk18\tunk19\t";
	std::cout << "release_trigger\tunk20\tblend_mode\tsim_type\tsim_power\t";
	std::cout << "tex_mask\tcolor_in\tcolor_out\twork0\twork1\twork2\t";
	std::cout << "work3\twork4\twork5\twork6\tvec0\tvec1\tvec2\tsp0\t";
	std::cout << "sp1\tsp2\tsp3\tunk21\tpath_own\tpath_no\tpath_st\t";
	std::cout << "path_rnd\tkind\tctr_id\tunk22\tid_flag\tinter\tnum\t";
	std::cout << "rp\tunk23\tlife\tunk24\tunk25\tunk26\tpath_scale\t";
	std::cout << "d_size\td_speed\td_alpha\td_inter\tr_inter\t";
	std::cout << "path_rotation_x\tpath_rotation_y\tpath_flag\t\n" << std::endl;
	for (unsigned int i = 0; i < table2_count; i++) {table2[i].repr();}
	std::cout << "____________________________________________" << std::endl;
	std::cout << "table3:   \t" << table0_count << std::endl;
	std::cout << "\tstate\tesp_id\ttex_id\tunk13\ttime\tparent\tpart_id\t";
	std::cout << "flag\tposition\trand\tspeed\tspeed_d\trand_speed\t";
	std::cout << "speed_acceleration\trand_speed_acceleration\trotation\t";
	std::cout << "rand_rotation\trotation_acceleration\t";
	std::cout << "rand_rotation_acceleration\twidth\theight\t";
	std::cout << "r_size\tplus\td_plus\trgba\td_rgba\tcolor_end_frame\t";
	std::cout << "color_start_frame\tunk14\tsize_start_frame\tlife_time\t";
	std::cout << "unk15\tunk16\tunk17\tanimation_rate\tunk18\tunk19\t";
	std::cout << "release_trigger\tunk20\tblend_mode\tsim_type\tsim_power\t";
	std::cout << "tex_mask\tcolor_in\tcolor_out\twork0\twork1\twork2\t";
	std::cout << "work3\twork4\twork5\twork6\tvec0\tvec1\tvec2\tsp0\t";
	std::cout << "sp1\tsp2\tsp3\tunk21\tpath_own\tpath_no\tpath_st\t";
	std::cout << "path_rnd\tkind\tctr_id\tunk22\tid_flag\tinter\tnum\t";
	std::cout << "rp\tunk23\tlife\tunk24\tunk25\tunk26\tpath_scale\t";
	std::cout << "d_size\td_speed\td_alpha\td_inter\tr_inter\t";
	std::cout << "path_rotation_x\tpath_rotation_y\tpath_flag\t\n" << std::endl;
	for (unsigned int i = 0; i < table3_count; i++) {table3[i].repr();}
	}

void fmtEST::export_est (std::wstring outpath, int padlen, int varlen, int dc_len) {

	// Create Folder
	if (!win::doesFolderExistW(outpath)) {
		win::makeDirW(outpath);
		}

	// Create Text
	std::cout << "EST's: \t" << table0_count << " \t " << " \t " << table1_count << " \t " << table2_count << " \t " << table3_count << std::endl;
    if (table0_count + table1_count + table2_count + table3_count > 0) {

		std::stringstream ss;
		std::string txt = "; =============================================================\n";
		txt += "; Resident Evil 4 Ultimate HD Edition - Effects Data\n; Generated from re4eff by mariokart64n\n;\n";
		txt += "; * Defines Paths to Resource Folders\n;   both relative and absolute paths are allowed\n";
		txt += "; =============================================================\n\n";
		txt += "[EFF_GROUP_PATHS]\n\n";





		ss.str(std::string());
		ss << std::uppercase << TO_HEX(unk07, false, 2);
		std::string lne = padString("  parent", varlen, " ", false) + " = 0x" + ss.str();
		if (unk07 < 247) {
			txt += lne + "\n";
			}
		else {
			txt += padString(lne, padlen, " ", false) + "; ";
			switch (unk07) {
				case 0xF8: {txt += "SCR_FST[6]\n"; break;}
				case 0xF9: {txt += "SCR_PREV2[4]\n"; break;}
				case 0xFA: {txt += "SCR_PREV1[5]\n"; break;}
				case 0xFB: {txt += "SCR_AFTER2[1]\n"; break;}
				case 0xFC: {txt += "SCR_AFTER1[2] SA\n"; break;}
				case 0xFD: {txt += "SCREEN[3] SC\n"; break;}
				case 0xFE: {txt += "WORLD WD\n"; break;}
				case 0xFF: {txt += "NULL NL\n"; break;}
				}
			}



		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << position[0];
		txt += padString("  position", varlen, " ", false) + " = [";
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << position[1];
		txt += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << position[2];
		txt += ss.str() + "]\n";

		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << rotation[1];
		txt += padString("  rotation", varlen, " ", false) + " = ";
		txt += ss.str() + "\n";

		std::wstring layer_path;
		std::string layer_name;
		if (table0_count > 0) {
			layer_name = "layer0";
			txt += padString("  layer_path       0", varlen, " ", false) + " = " + layer_name + "\n";


			layer_path = outpath + string_to_wstring(layer_name) + L"\\";
			if (!win::doesFolderExistW(layer_path)) {
				win::makeDirW(layer_path);
				}

			for (unsigned int i = 0; i < table0_count; i++) {
				table0[i].export_txt(layer_path + L"sprite_0" + string_to_wstring(padString(to_string(i), 2, "0")) + L".txt");
				}
			}
		if (table1_count > 0) {
			layer_name = "layer1";
			txt += padString("  layer_path       1", varlen, " ", false) + " = " + layer_name + "\n";

			layer_path = outpath + string_to_wstring(layer_name) + L"\\";
			if (!win::doesFolderExistW(layer_path)) {
				win::makeDirW(layer_path);
				}

			for (unsigned int i = 0; i < table1_count; i++) {
				table1[i].export_txt(layer_path + L"sprite_1" + string_to_wstring(padString(to_string(i), 2, "0")) + L".txt");
				}

			}
		if (table2_count > 0) {
			layer_name = "layer2";
			txt += padString("  layer_path       2", varlen, " ", false) + " = " + layer_name + "\n";

			layer_path = outpath + string_to_wstring(layer_name) + L"\\";
			if (!win::doesFolderExistW(layer_path)) {
				win::makeDirW(layer_path);
				}

			for (unsigned int i = 0; i < table1_count; i++) {
				table2[i].export_txt(layer_path + L"sprite_2" + string_to_wstring(padString(to_string(i), 2, "0")) + L".txt");
				}
			}
		if (table3_count > 0) {
			layer_name = "layer3";
			txt += padString("  layer_path       3", varlen, " ", false) + " = " + layer_name + "\n";

			layer_path = outpath + string_to_wstring(layer_name) + L"\\";
			if (!win::doesFolderExistW(layer_path)) {
				win::makeDirW(layer_path);
				}


			for (unsigned int i = 0; i < table1_count; i++) {
				table3[i].export_txt(layer_path + L"sprite_3" + string_to_wstring(padString(to_string(i), 2, "0")) + L".txt");
				}
			}


		bytestream s;
		s.writeFileW(outpath + L"grp.txt", 0, txt.size(), (char*)txt.c_str());






		}




	}
