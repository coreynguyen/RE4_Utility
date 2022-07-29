#include "fmtLIT.h"



fmtLIT_Light_Emit_Shine::fmtLIT_Light_Emit_Shine () {
	unk1 = 0;
	unk2 = 0;
	speed[0] = 0.0f;
	speed[1] = 0.0f;
	speed[2] = 0.0f;
	}

void fmtLIT_Light_Emit_Shine::read_light_emit_shine (bytestream &f) {
	unk1 = f.readUlong();
	unk2 = f.readUlong();
	speed[0] = f.readfloat();
	speed[1] = f.readfloat();
	speed[2] = f.readfloat();
	}

void fmtLIT_Light_Emit_Shine::write_light_emit_shine (bytestream &s) {
	s.writeUlong(unk1);
	s.writeUlong(unk2);
	s.writefloat(speed[0]);
	s.writefloat(speed[1]);
	s.writefloat(speed[2]);
	}


fmtLIT_Light_Emit_Path_Fade::fmtLIT_Light_Emit_Path_Fade () {
	start = 0.0;
	speed = 0.0;
	}

void fmtLIT_Light_Emit_Path_Fade::read_light_emit_fade (bytestream &f) {
	start = f.readfloat();
	speed = f.readfloat();
	}

void fmtLIT_Light_Emit_Path_Fade::write_light_emit_fade (bytestream &s) {
	s.writefloat(start);
	s.writefloat(speed);
	}

fmtLIT_Light_Emit_Path_Flag::fmtLIT_Light_Emit_Path_Flag () {
	loop_off = false;
	inverse_on = false;
	path_flag3 = false;
	path_flag4 = false;
	path_flag5 = false;
	path_flag6 = false;
	path_flag7 = false;
	path_flag8 = false;
	}

void fmtLIT_Light_Emit_Path_Flag::read_light_emit_path_flag (uint32_t val) {
	loop_off = bit::get(val, 1);
	inverse_on = bit::get(val, 2);
	path_flag3 = bit::get(val, 3);
	path_flag4 = bit::get(val, 4);
	path_flag5 = bit::get(val, 5);
	path_flag6 = bit::get(val, 6);
	path_flag7 = bit::get(val, 7);
	path_flag8 = bit::get(val, 8);
	}

void fmtLIT_Light_Emit_Path_Flag::write_light_emit_path_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, loop_off);
	val = bit::set(val, 2, inverse_on);
	val = bit::set(val, 3, path_flag3);
	val = bit::set(val, 4, path_flag4);
	val = bit::set(val, 5, path_flag5);
	val = bit::set(val, 6, path_flag6);
	val = bit::set(val, 7, path_flag7);
	val = bit::set(val, 8, path_flag8);
	s.writeUbyte(val);
	}

fmtLIT_Light_Emit_Path::fmtLIT_Light_Emit_Path () {
	unk1 = 0;
	unk2 = 0;
	unk3 = 0;
	unk4 = 0;
	unk5 = 0;
	path_index = 0;
	}

void fmtLIT_Light_Emit_Path::read_light_emit_path (bytestream &f) {
	unk1 = f.readUlong();
	unk2 = f.readUlong();
	flag.read_light_emit_path_flag(f.readUbyte());
	unk3 = f.readUbyte();
	unk4 = f.readUbyte();
	unk5 = f.readUbyte();
	path_index = f.readUbyte();
	}

void fmtLIT_Light_Emit_Path::write_light_emit_path (bytestream &s) {
	s.writeUlong(unk1);
	s.writeUlong(unk2);
	flag.write_light_emit_path_flag(s);
	s.writeUbyte(unk3);
	s.writeUbyte(unk4);
	s.writeUbyte(unk5);
	s.writeUbyte(path_index);
	}

fmtLIT_Light_Emit_Shadow_Flag::fmtLIT_Light_Emit_Shadow_Flag () {
	use_tex = false;
	shdw_flag2 = false;
	invert_tex = false;
	shdw_flag4 = false;
	shdw_flag5 = false;
	shdw_flag6 = false;
	shdw_flag7 = false;
	shdw_flag8 = false;
	}

void fmtLIT_Light_Emit_Shadow_Flag::read_light_emit_shadow_flag (uint32_t val) {
	use_tex = bit::get(val, 1);
	shdw_flag2 = bit::get(val, 2);
	invert_tex = bit::get(val, 3);
	shdw_flag4 = bit::get(val, 4);
	shdw_flag5 = bit::get(val, 5);
	shdw_flag6 = bit::get(val, 6);
	shdw_flag7 = bit::get(val, 7);
	shdw_flag8 = bit::get(val, 8);
	}

void fmtLIT_Light_Emit_Shadow_Flag::write_light_emit_shadow_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, use_tex);
	val = bit::set(val, 2, shdw_flag2);
	val = bit::set(val, 3, invert_tex);
	val = bit::set(val, 4, shdw_flag4);
	val = bit::set(val,5, shdw_flag5);
	val = bit::set(val, 6, shdw_flag6);
	val = bit::set(val, 7, shdw_flag7);
	val = bit::set(val, 8, shdw_flag8);
	s.writeUbyte(val);
	}

fmtLIT_Light_Emit_Shadow::fmtLIT_Light_Emit_Shadow () {
	unk1 = 0;
	type = 0;
	tex_no = 0;
	gnd_dist = 0;
	unk2 = 0;
	unk3 = 0;
	unk4 = 0;
	unk5 = 0;
	unk6 = 0;
	unk7 = 0;
	unk8[0] = 0.0f;
	unk8[1] = 0.0f;
	unk8[2] = 0.0f;
	unk9 = 0;
	}

void fmtLIT_Light_Emit_Shadow::read_light_emit_shadow (bytestream &f) {
	unk1 = f.readUbyte();
	tex_flag.read_light_emit_shadow_flag(f.readUbyte());
	type = f.readUbyte();
	switch (type) {
		case 5: {gnd_dist = f.readbyte(); break;}
		default: {tex_no = f.readUbyte();}
		}
	unk2 = f.readUshort();
	unk3 = f.readUshort();
	unk4 = f.readUbyte();
	unk5 = f.readUbyte();
	unk6 = f.readUbyte();
	unk7 = f.readUbyte();
	unk8[0] = f.readfloat();
	unk8[1] = f.readfloat();
	unk8[2] = f.readfloat();
	unk9 = f.readUlong();
	}

void fmtLIT_Light_Emit_Shadow::write_light_emit_shadow (bytestream &s) {
	s.writeUbyte(unk1);
	tex_flag.write_light_emit_shadow_flag(s);
	s.writeUbyte(type);
	switch (type) {
		case 5: {s.writebyte(gnd_dist); break;}
		default: {s.writeUbyte(tex_no);}
		}
	s.writeUshort(unk2);
	s.writeUshort(unk3);
	s.writeUbyte(unk4);
	s.writeUbyte(unk5);
	s.writeUbyte(unk6);
	s.writeUbyte(unk7);
	s.writefloat(unk8[0]);
	s.writefloat(unk8[1]);
	s.writefloat(unk8[2]);
	s.writeUlong(unk9);
	}

fmtLIT_Light_Emit_Spot::fmtLIT_Light_Emit_Spot () {
	rotation[0] = 0.0f;
	rotation[1] = 0.0f;
	rotation[2] = 0.0f;
	}

void fmtLIT_Light_Emit_Spot::read_light_emit_spot (bytestream &f) {
	rotation[0] = f.readfloat();
	rotation[1] = f.readfloat();
	rotation[2] = f.readfloat();
	}

void fmtLIT_Light_Emit_Spot::write_light_emit_spot (bytestream &s) {
	s.writefloat(rotation[0]);
	s.writefloat(rotation[1]);
	s.writefloat(rotation[2]);
	}

fmtLIT_Light_Emit_Wave::fmtLIT_Light_Emit_Wave () {
	center = 0.0f;
	range = 0.0f;
	speed = 1.0f;
	unk1 = 1.0f;
	}

void fmtLIT_Light_Emit_Wave::read_light_emit_wave (bytestream &f) {
	center = f.readfloat();
	range = f.readfloat();
	speed = f.readfloat();
	unk1 = f.readfloat();
	}
void fmtLIT_Light_Emit_Wave::write_light_emit_wave (bytestream &s) {
	s.writefloat(center);
	s.writefloat(range);
	s.writefloat(speed);
	s.writefloat(unk1);
	}

fmtLIT_Light_Emit_Flicker::fmtLIT_Light_Emit_Flicker () {
	colour[0] = 0;
	colour[1] = 0;
	colour[2] = 0;
	colour[3] = 255;
	rate = 0;
	}

void fmtLIT_Light_Emit_Flicker::read_light_emit_flicker (bytestream &f) {
	colour[0] = f.readUbyte();
	colour[1] = f.readUbyte();
	colour[2] = f.readUbyte();
	colour[3] = f.readUbyte();
	rate = f.readUbyte();
	}

void fmtLIT_Light_Emit_Flicker::write_light_emit_flicker (bytestream &s) {
	s.writeUbyte(colour[0]);
	s.writeUbyte(colour[1]);
	s.writeUbyte(colour[2]);
	s.writeUbyte(colour[3]);
	s.writeUbyte(rate);
	}

fmtLIT_Light_Type_Local::fmtLIT_Light_Type_Local () {
	smooth_edge = 0.0;
	}

void fmtLIT_Light_Type_Local::read_light_type_local (bytestream &f) {
	smooth_edge = f.readfloat();
	}

void fmtLIT_Light_Type_Local::write_light_type_local (bytestream &s) {
	s.writefloat(smooth_edge);
	}

fmtLIT_Light_Type_Spot_quad::fmtLIT_Light_Type_Spot_quad () {
	direction[0] = 0.0f;
	direction[1] = 0.0f;
	direction[2] = 0.0f;
	distance = 0.0f;
	smooth_edge = 0.0f;
	}

void fmtLIT_Light_Type_Spot_quad::read_light_type_spot_quad (bytestream &f) {
	direction[0] = f.readfloat();
	direction[1] = f.readfloat();
	direction[2] = f.readfloat();
	distance = f.readfloat();
	smooth_edge = f.readfloat();
	}

void fmtLIT_Light_Type_Spot_quad::write_light_type_spot_quad (bytestream &s) {
	s.writefloat(direction[0]);
	s.writefloat(direction[1]);
	s.writefloat(direction[2]);
	s.writefloat(distance);
	s.writefloat(smooth_edge);
	}


fmtLIT_Light_Type_Para::fmtLIT_Light_Type_Para () {
	direction[0] = 0.0f;
	direction[1] = 0.0f;
	direction[2] = 0.0f;
	is_dir_auto = 0;
	smooth_edge = 0.0f;
	}

void fmtLIT_Light_Type_Para::read_light_type_para (bytestream &f) {
	direction[0] = f.readfloat();
	direction[1] = f.readfloat();
	direction[2] = f.readfloat();
	is_dir_auto = f.readUlong();
	smooth_edge = f.readfloat();
	}

void fmtLIT_Light_Type_Para::write_light_type_para (bytestream &s) {
	s.writefloat(direction[0]);
	s.writefloat(direction[1]);
	s.writefloat(direction[2]);
	s.writeUlong(is_dir_auto);
	s.writefloat(smooth_edge);
	}

fmtLIT_Light_Type_Spot::fmtLIT_Light_Type_Spot () {
	direction[0] = 0.0f;
	direction[1] = 0.0f;
	direction[2] = 0.0f;
	distance = 0.0f;	// range [1.0 - 90.0] must be greater then 1.0
	smooth_edge = 0.0f;
	}

void fmtLIT_Light_Type_Spot::read_light_type_spot (bytestream &f) {
	direction[0] = f.readfloat();
	direction[1] = f.readfloat();
	direction[2] = f.readfloat();
	distance = f.readfloat();
	smooth_edge = f.readfloat();
	}

void fmtLIT_Light_Type_Spot::write_light_type_spot (bytestream &s) {
	s.writefloat(direction[0]);
	s.writefloat(direction[1]);
	s.writefloat(direction[2]);
	s.writefloat(distance);
	s.writefloat(smooth_edge);
	}

fmtLIT_Light_Type_Quad::fmtLIT_Light_Type_Quad () {
	smooth_edge = 0.0f;
	direction[0] = 0.0f;
	direction[1] = 0.0f;
	direction[2] = 0.0f;
	unk1 = 0.0f;
	}

void fmtLIT_Light_Type_Quad::read_light_type_quad (bytestream &f) {
	smooth_edge = f.readfloat();
	direction[0] = f.readfloat();
	direction[1] = f.readfloat();
	direction[2] = f.readfloat();
	unk1 = f.readfloat();
	}

void fmtLIT_Light_Type_Quad::write_light_type_quad (bytestream &s) {
	s.writefloat(smooth_edge);
	s.writefloat(direction[0]);
	s.writefloat(direction[1]);
	s.writefloat(direction[2]);
	s.writefloat(unk1);
	}

fmtLIT_Light_Type_Linear::fmtLIT_Light_Type_Linear () {
	direction[0] = 0.0f;
	direction[1] = 0.0f;
	direction[2] = 0.0f;
	is_dir_auto = 0;
	}

void fmtLIT_Light_Type_Linear::read_light_type_linear (bytestream &f) {
	direction[0] = f.readfloat();
	direction[1] = f.readfloat();
	direction[2] = f.readfloat();
	is_dir_auto = f.readUbyte();
	}

void fmtLIT_Light_Type_Linear::write_light_type_linear (bytestream &s) {
	s.writefloat(direction[0]);
	s.writefloat(direction[1]);
	s.writefloat(direction[2]);
	s.writeUbyte(is_dir_auto);
	}

fmtLIT_Light_Type_Constant::fmtLIT_Light_Type_Constant () {
	unk1 = 0;
	unk2 = 0;
	unk3 = 0;
	unk4 = 0;
	unk5 = 0;
	unk6 = 0.0f;
	}

void fmtLIT_Light_Type_Constant::read_light_type_constant (bytestream &f) {
	unk1 = f.readUbyte();
	unk2 = f.readUbyte();
	unk3 = f.readUbyte();
	unk4 = f.readUbyte();
	unk5 = f.readUlong();
	unk6 = f.readfloat();
	}

void fmtLIT_Light_Type_Constant::write_light_type_constant (bytestream &s) {
	s.writeUbyte(unk1);
	s.writeUbyte(unk2);
	s.writeUbyte(unk3);
	s.writeUbyte(unk4);
	s.writeUlong(unk5);
	s.writefloat(unk6);
	}

fmtLIT_Light_Interact_Flag::fmtLIT_Light_Interact_Flag () {
	on_player = false;
	on_enemy = false;
	on_object = false;
	on_effect = false;
	on_room = false;
	on_item = false;
	on_subchar = false;
	on_thermo = false;
	}

void fmtLIT_Light_Interact_Flag::read_light_mask_flag (uint32_t val) {
	on_player = bit::get(val, 1);
	on_enemy = bit::get(val, 2);
	on_object = bit::get(val, 3);
	on_effect = bit::get(val, 4);
	on_room = bit::get(val, 5);
	on_item = bit::get(val, 6);
	on_subchar = bit::get(val, 7);
	on_thermo = bit::get(val, 8);
	}

void fmtLIT_Light_Interact_Flag::write_light_mask_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, on_player);
	val = bit::set(val, 2, on_enemy);
	val = bit::set(val, 3, on_object);
	val = bit::set(val, 4, on_effect);
	val = bit::set(val, 5, on_room);
	val = bit::set(val, 6, on_item);
	val = bit::set(val, 7, on_subchar);
	val = bit::set(val, 8, on_thermo);
	s.writeUbyte(val);
	}

fmtLIT_Light_Attribute::fmtLIT_Light_Attribute () {
	no_tune = false;
	elec_light = false;
	taimatu = false;
	attr_flag4 = false;
	attr_flag5 = false;
	attr_flag6 = false;
	attr_flag7 = false;
	attr_flag8 = false;
	}

void fmtLIT_Light_Attribute::read_light_attribute_flag (uint32_t val) {
	no_tune = bit::get(val, 1);
	elec_light = bit::get(val, 2);
	taimatu = bit::get(val, 3);
	attr_flag4 = bit::get(val, 4);
	attr_flag5 = bit::get(val, 5);
	attr_flag6 = bit::get(val,6);
	attr_flag7 = bit::get(val, 7);
	attr_flag8 = bit::get(val, 8);
	}

void fmtLIT_Light_Attribute::write_light_attribute_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, no_tune);
	val = bit::set(val, 2, elec_light);
	val = bit::set(val, 3, taimatu);
	val = bit::set(val, 4, attr_flag4);
	val = bit::set(val, 5, attr_flag5);
	val = bit::set(val, 6, attr_flag6);
	val = bit::set(val, 7, attr_flag7);
	val = bit::set(val, 8, attr_flag8);
	s.writeUbyte(val);
	}

fmtLIT_Light_Unknown::fmtLIT_Light_Unknown () {
	unk021 = 0;
	unk022 = 0.0;
	unk023 = 0;
	unk024 = 0;
	unk025 = 0;
	unk026 = 0;
	unk027 = 0;
	unk028 = 0;
	unk029 = 0;
	unk030 = 0;
	unk031 = 0;
	unk032 = 0;
	unk033 = 0;
	unk034 = 0;
	unk035 = 0;
	unk036 = 0;
	unk037 = 0;
	unk038 = 0;
	unk039 = 0;
	unk040 = 0;
	unk041 = 0;
	unk042 = 0;
	unk043 = 0;
	}

void fmtLIT_Light_Unknown::read_light_unkdata (bytestream &f) {
	unk021 = f.readUlong();
	unk022 = f.readfloat();
	unk023 = f.readUbyte();
	unk024 = f.readUbyte();
	unk025 = f.readUbyte();
	unk026 = f.readUbyte();
	unk027 = f.readUshort();
	unk028 = f.readUshort();
	unk029 = f.readUlong();
	unk030 = f.readUlong();
	unk031 = f.readUlong();
	unk032 = f.readUlong();
	unk033 = f.readUlong();
	unk034 = f.readUlong();
	unk035 = f.readUlong();
	unk036 = f.readUlong();
	unk037 = f.readUlong();
	unk038 = f.readUbyte();
	unk039 = f.readUbyte();
	unk040 = f.readUbyte();
	unk041 = f.readUbyte();
	unk042 = f.readUlong();
	unk043 = f.readUlong();
	}

void fmtLIT_Light_Unknown::write_light_unkdata (bytestream &s) {
	s.writeUlong(unk021);
	s.writefloat(unk022);
	s.writeUbyte(unk023);
	s.writeUbyte(unk024);
	s.writeUbyte(unk025);
	s.writeUbyte(unk026);
	s.writeUshort(unk027);
	s.writeUshort(unk028);
	s.writeUlong(unk029);
	s.writeUlong(unk030);
	s.writeUlong(unk031);
	s.writeUlong(unk032);
	s.writeUlong(unk033);
	s.writeUlong(unk034);
	s.writeUlong(unk035);
	s.writeUlong(unk036);
	s.writeUlong(unk037);
	s.writeUbyte(unk038);
	s.writeUbyte(unk039);
	s.writeUbyte(unk040);
	s.writeUbyte(unk041);
	s.writeUlong(unk042);
	s.writeUlong(unk043);
	}

fmtLIT_Light_Flag::fmtLIT_Light_Flag () {
	lit_flag1 = true;
	lit_flag2 = true;
	lit_flag3 = false;
	lit_flag4 = false;
	lit_flag5 = false;
	lit_flag6 = false;
	lit_flag7 = false;
	lit_flag8 = false;
	}

void fmtLIT_Light_Flag::read_light_flag (uint32_t val) {
	lit_flag1 = bit::get(val, 1);
	lit_flag2 = bit::get(val, 2);
	lit_flag3 = bit::get(val, 3);
	lit_flag4 = bit::get(val, 4);
	lit_flag5 = bit::get(val, 5);
	lit_flag6 = bit::get(val, 6);
	lit_flag7 = bit::get(val, 7);
	lit_flag8 = bit::get(val, 8);
	}

void fmtLIT_Light_Flag::write_light_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, lit_flag1);
	val = bit::set(val, 2, lit_flag2);
	val = bit::set(val, 3, lit_flag3);
	val = bit::set(val, 4, lit_flag4);
	val = bit::set(val, 5, lit_flag5);
	val = bit::set(val, 6, lit_flag6);
	val = bit::set(val, 7, lit_flag7);
	val = bit::set(val, 8, lit_flag8);
	s.writeUbyte(val);
	}

fmtLIT_Light::fmtLIT_Light () {
	type = 0;
	emit_type = 0;
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;
	radius = 0.0;
	colour[0] = 0;
	colour[1] = 0;
	colour[2] = 0;
	colour[3] = 255;
	intensity = 0.0;
	parent_type = 0;
	kind = 0;
	priority = 0;
	parent_part_id = 0;
	parent_model_id = 0;
	hit_radius = 0;
	unk3 = 0;
	unk4 = 0;
	unk5 = 0.0;
	//for (unsigned int i = 0; i < 12; i++) {reserve0[i] = 0;}
	for (unsigned int i = 0; i < 64; i++) {reserve1[i] = 0;}
	for (unsigned int i = 0; i < 64; i++) {reserve2[i] = 0;}
	for (unsigned int i = 0; i < 64; i++) {reserve3[i] = 0;}
	for (unsigned int i = 0; i < 64; i++) {reserve4[i] = 0;}
	}

void fmtLIT_Light::read_light (bytestream &f) {

	flag.read_light_flag(f.readUbyte());
	type = f.readUbyte();
	emit_type = f.readUbyte();
	mask_flag.read_light_mask_flag(f.readUbyte());
	position[0] = f.readfloat();
	position[1] = f.readfloat();
	position[2] = f.readfloat();
	radius = f.readfloat();
	colour[0] = f.readUbyte();
	colour[1] = f.readUbyte();
	colour[2] = f.readUbyte();
	colour[3] = f.readUbyte();
	intensity = f.readfloat();
	parent_type = f.readUbyte();
	kind = f.readUbyte();
	attr.read_light_attribute_flag(f.readUbyte());
	priority = f.readUbyte();
	parent_part_id = f.readUshort();
	parent_model_id = f.readUshort();
	hit_radius = f.readUshort();
	unk3 = f.readUbyte();
	unk4 = f.readUbyte();
	unk5 = f.readfloat();


	switch (type) {
		case 0: {type_constant.read_light_type_constant(f); break;}	// CONSTANT
		case 1: {type_linear.read_light_type_linear(f); break;}	// LINEAR
		case 2: {type_quad.read_light_type_quad(f); break;}	// QUADRATIC
		case 3: {type_spot.read_light_type_spot(f); break;}	// SPOT_LIGHT
		//case 4: (break;);	// CUSTOM
		case 5: {type_para.read_light_type_para(f); break;}	// PARALLEL
		case 6: {type_spot_quad.read_light_type_spot_quad(f); break;}	// SPOT_QUAD
		case 7: {type_local.read_light_type_local(f); break;}	// LOCAL_AMBIENT
		}
	for (unsigned int i = 0; i < 64; i++) {reserve1[i] = f.readUbyte();}



	switch (emit_type) {
		//case 0: {break;}	// NORMAL
		case 1: {emit_flicker.read_light_emit_flicker(f); break;}	// FLICKER
		case 2: {emit_wave.read_light_emit_wave(f); break;}	// WAVE
		case 3: {emit_spot.read_light_emit_spot(f); break;}	// SPOT_ROTATE
		case 4: {emit_shadow.read_light_emit_shadow(f); break;}	// SHADOW
		case 5: {emit_path.read_light_emit_path(f); break;}	// PATH
		case 6: {emit_fade.read_light_emit_fade(f); break;}	// FADE
		case 7: {emit_shine.read_light_emit_shine(f); break;}	// SHINE
		//case 8: {break;}	// SPOT_LOCK
		//case 9: {break;}	// RESERVED
		}
	for (unsigned int i = 0; i < 64; i++) {reserve2[i] = f.readUbyte();}
	for (unsigned int i = 0; i < 64; i++) {reserve3[i] = f.readUbyte();}
	for (unsigned int i = 0; i < 64; i++) {reserve4[i] = f.readUbyte();}
	}

void fmtLIT_Light::write_light (bytestream &s) {
	size_t pos = 0;
	flag.write_light_flag(s);
	s.writeUbyte(type);
	s.writeUbyte(emit_type);
	mask_flag.write_light_mask_flag(s);
	s.writefloat(position[0]);
	s.writefloat(position[1]);
	s.writefloat(position[2]);
	s.writefloat(radius);
	s.writeUbyte(colour[0]);
	s.writeUbyte(colour[1]);
	s.writeUbyte(colour[2]);
	s.writeUbyte(colour[3]);
	s.writefloat(intensity);
	s.writeUbyte(parent_type);
	s.writeUbyte(kind);
	attr.write_light_attribute_flag(s);
	s.writeUbyte(priority);
	s.writeUshort(parent_part_id);
	s.writeUshort(parent_model_id);
	s.writeUshort(hit_radius);
	s.writeUbyte(unk3);
	s.writeUbyte(unk4);
	s.writefloat(unk5);
	pos = s.tell() + 64;
	switch (type) {
		case 0: {type_constant.write_light_type_constant(s); break;}
		case 1: {type_linear.write_light_type_linear(s); break;}
		case 2: {type_quad.write_light_type_quad(s); break;}
		case 3: {type_spot.write_light_type_spot(s); break;}
		case 5: {type_para.write_light_type_para(s); break;}
		case 6: {type_spot_quad.write_light_type_spot_quad(s); break;}
		case 7: {type_local.write_light_type_local(s); break;}
		}
	unsigned int pad = pos - (s.tell());
	for (unsigned int i = 0; i < pad; i++) {s.writeUbyte(0);}
	pos = s.tell() + 192;
	switch (emit_type) {
		case 1: {emit_flicker.write_light_emit_flicker(s); break;}
		case 2: {emit_wave.write_light_emit_wave(s); break;}
		case 3: {emit_spot.write_light_emit_spot(s); break;}
		case 4: {emit_shadow.write_light_emit_shadow(s); break;}
		case 5: {emit_path.write_light_emit_path(s); break;}
		case 6: {emit_fade.write_light_emit_fade(s); break;}
		case 7: {emit_shine.write_light_emit_shine(s); break;}
		}
	pad = pos - (s.tell());
	for (unsigned int i = 0; i < pad; i++) {s.writeUbyte(0);}
	}

fmtLIT_Entry::fmtLIT_Entry () {
	room_ambient[0] = 0;
	room_ambient[1] = 0;
	room_ambient[2] = 0;
	room_ambient[3] = 255;
	light_count = 0;
	fog_type = 0;
	fog_start = 0.0;
	fog_end = 0.0;
	fog_colour[0] = 0;
	fog_colour[1] = 0;
	fog_colour[2] = 0;
	fog_colour[3] = 255;
	mfog_type = 0;
	mfog_start = 0.0;
	mfog_end = 0.0;
	mfog_colour[0] = 0;
	mfog_colour[1] = 0;
	mfog_colour[2] = 0;
	mfog_colour[3] = 255;
	focus_dist = 0;
	unk011 = 0;
	focus_level = 0;
	focus_mode = 0;
	blur_affect = 0;
	tune_src = 0;
	unk012 = 0;
	unk013 = 0;
	unk014 = 0;
	tune_light_colour[0] = 0;
	tune_light_colour[1] = 0;
	tune_light_colour[2] = 0;
	tune_light_colour[3] = 255;
	tune_ambient_colour[0] = 0;
	tune_ambient_colour[1] = 0;
	tune_ambient_colour[2] = 0;
	tune_ambient_colour[3] = 255;
	tune_effect_colour[0] = 0;
	tune_effect_colour[1] = 0;
	tune_effect_colour[2] = 0;
	tune_effect_colour[3] = 255;
	tev_scale_model = 0;
	tev_scale_player = 0;
	unk016c = 0;
	unk016d = 0;
	fog_thickness = 0.0;
	hokan = 0;
	unk018b = 0;
	unk018c = 0;
	unk018d = 0;
	unk051 = 0.0;
	unk052 = 0.0;
	unk053 = 0.0;
	unk054 = 0.0;
	unk055 = 0;
	unk056 = 0.0;
	unk057a = 0;
	unk057b = 0;
	unk057c = 0;
	unk057d = 0;
	unk058 = 0.0;
	wind_dir = 0.0;
	wind_power = 0.0;
	wind_frequency = 0.0;
	unk059d = 0;
	blur_type = 0;
	blur_power = 0;
	mipmap_min_lod = 0;
	mipmap_max_lod = 0;
	mipmap_aniso_type = 0;
	contrast_level = 0;
	contrast_power = 0;
	contrast_bias = 0;
	mipmap_lod_bias = 0.0;
	object_ambient[0] = 0;
	object_ambient[1] = 0;
	object_ambient[2] = 0;
	object_ambient[3] = 255;
	effect_ambient[0] = 0;
	effect_ambient[1] = 0;
	effect_ambient[2] = 0;
	effect_ambient[3] = 255;
	light_array.clear();
	}

void fmtLIT_Entry::read_lit_entry (bytestream &f) {
	size_t pos = 0;
	room_ambient[0] = f.readUbyte();
	room_ambient[1] = f.readUbyte();
	room_ambient[2] = f.readUbyte();
	room_ambient[3] = f.readUbyte();
	light_count = f.readUlong();
	fog_type = f.readUlong();
	fog_start = f.readfloat();
	fog_end = f.readfloat();
	fog_colour[0] = f.readUbyte();
	fog_colour[1] = f.readUbyte();
	fog_colour[2] = f.readUbyte();
	fog_colour[3] = f.readUbyte();
	mfog_type = f.readUlong();
	mfog_start = f.readfloat();
	mfog_end = f.readfloat();
	mfog_colour[0] = f.readUbyte();
	mfog_colour[1] = f.readUbyte();
	mfog_colour[2] = f.readUbyte();
	mfog_colour[3] = f.readUbyte();
	focus_dist = f.readlong();
	unk011 = f.readUbyte();
	focus_level = f.readUbyte();
	focus_mode = f.readUbyte();
	blur_affect = f.readUbyte();
	tune_src = f.readUbyte();
	unk012 = f.readUbyte();
	unk013 = f.readUbyte();
	unk014 = f.readUbyte();
	tune_light_colour[0]= f.readUbyte();
	tune_light_colour[1] = f.readUbyte();
	tune_light_colour[2] = f.readUbyte();
	tune_light_colour[3] = f.readUbyte();
	tune_ambient_colour[0] = f.readUbyte();
	tune_ambient_colour[1] = f.readUbyte();
	tune_ambient_colour[2] = f.readUbyte();
	tune_ambient_colour[3] = f.readUbyte();
	tune_effect_colour[0] = f.readUbyte();
	tune_effect_colour[1] = f.readUbyte();
	tune_effect_colour[2] = f.readUbyte();
	tune_effect_colour[3] = f.readUbyte();
	tev_scale_model = f.readUbyte();
	tev_scale_player = f.readUbyte();
	unk016c = f.readUbyte();
	unk016d = f.readUbyte();
	fog_thickness = f.readfloat();
	hokan = f.readUbyte();
	unk018b = f.readUbyte();
	unk018c = f.readUbyte();
	unk018d = f.readUbyte();
	unkdata1.read_light_unkdata(f);
	unkdata2.read_light_unkdata(f);
	unk051 = f.readfloat();
	unk052 = f.readfloat();
	unk053 = f.readfloat();
	unk054 = f.readfloat();
	unk055 = f.readUlong();
	unk056 = f.readfloat();
	unk057a = f.readUbyte();
	unk057b = f.readUbyte();
	unk057c = f.readUbyte();
	unk057d = f.readUbyte();
	unk058 = f.readfloat();
	wind_dir = f.readbyte() * 0.0247369500282660884918318376636f;
	wind_power = f.readUbyte() * 0.2f;
	wind_frequency = f.readUbyte() * 0.0104706f;
	unk059d = f.readUbyte();
	blur_type = f.readUbyte();
	blur_power = f.readUbyte();
	mipmap_min_lod = f.readUbyte();
	mipmap_max_lod = f.readUbyte();
	mipmap_aniso_type = f.readUbyte();
	contrast_level = f.readUbyte();
	contrast_power = f.readUbyte();
	contrast_bias = f.readUbyte();
	mipmap_lod_bias = f.readfloat();
	object_ambient[0] = f.readUbyte();
	object_ambient[1] = f.readUbyte();
	object_ambient[2] = f.readUbyte();
	object_ambient[3] = f.readUbyte();
	effect_ambient[0] = f.readUbyte();
	effect_ambient[1] = f.readUbyte();
	effect_ambient[2] = f.readUbyte();
	effect_ambient[3] = f.readUbyte();

	if (light_count > 0) {
		pos = f.tell();
		light_array = std::vector<fmtLIT_Light>(light_count);
		for (unsigned int i = 0; i < light_count; i++) {
			f.seek((pos + (i * 0x012C)));
			light_array[i].read_light(f);
			}
		}
	}

void fmtLIT_Entry::write_fmtLIT_Entry (bytestream &s) {
	s.writeUbyte(room_ambient[0]);
	s.writeUbyte(room_ambient[1]);
	s.writeUbyte(room_ambient[2]);
	s.writeUbyte(room_ambient[3]);
	s.writeUlong(light_count);
	s.writeUlong(fog_type);
	s.writefloat(fog_start);
	s.writefloat(fog_end);
	s.writeUbyte(fog_colour[0]);
	s.writeUbyte(fog_colour[1]);
	s.writeUbyte(fog_colour[2]);
	s.writeUbyte(fog_colour[3]);
	s.writeUlong(mfog_type);
	s.writefloat(mfog_start);
	s.writefloat(mfog_end);
	s.writeUbyte(mfog_colour[0]);
	s.writeUbyte(mfog_colour[1]);
	s.writeUbyte(mfog_colour[2]);
	s.writeUbyte(mfog_colour[3]);
	s.writelong(focus_dist);
	s.writeUbyte(unk011);
	s.writeUbyte(focus_level);
	s.writeUbyte(focus_mode);
	s.writeUbyte(blur_affect);
	s.writeUbyte(tune_src);
	s.writeUbyte(unk012);
	s.writeUbyte(unk013);
	s.writeUbyte(unk014);
	s.writeUbyte(tune_light_colour[0]);
	s.writeUbyte(tune_light_colour[1]);
	s.writeUbyte(tune_light_colour[2]);
	s.writeUbyte(tune_light_colour[3]);
	s.writeUbyte(tune_ambient_colour[0]);
	s.writeUbyte(tune_ambient_colour[1]);
	s.writeUbyte(tune_ambient_colour[2]);
	s.writeUbyte(tune_ambient_colour[3]);
	s.writeUbyte(tune_effect_colour[0]);
	s.writeUbyte(tune_effect_colour[1]);
	s.writeUbyte(tune_effect_colour[2]);
	s.writeUbyte(tune_effect_colour[3]);
	s.writeUbyte(tev_scale_model);
	s.writeUbyte(tev_scale_player);
	s.writeUbyte(unk016c);
	s.writeUbyte(unk016d);
	s.writefloat(fog_thickness);
	s.writeUbyte(hokan);
	s.writeUbyte(unk018b);
	s.writeUbyte(unk018c);
	s.writeUbyte(unk018d);
	unkdata1.write_light_unkdata(s);
	unkdata2.write_light_unkdata(s);
	s.writefloat(unk051);
	s.writefloat(unk052);
	s.writefloat(unk053);
	s.writefloat(unk054);
	s.writeUlong(unk055);
	s.writefloat(unk056);
	s.writeUbyte(unk057a);
	s.writeUbyte(unk057b);
	s.writeUbyte(unk057c);
	s.writeUbyte(unk057d);
	s.writefloat(unk058);
	s.writeUbyte((signed int)(wind_dir * 40.4253555453414152852964758966f));// {127.0 * {1.0 / pi}}
	s.writeUbyte((unsigned int)(wind_power * 5.0));
	s.writeUbyte((unsigned int)(wind_frequency * 95.5055));
	s.writeUbyte(unk059d);
	s.writeUbyte(blur_type);
	s.writeUbyte(blur_power);
	s.writeUbyte(mipmap_min_lod);
	s.writeUbyte(mipmap_max_lod);
	s.writeUbyte(mipmap_aniso_type);
	s.writeUbyte(contrast_level);
	s.writeUbyte(contrast_power);
	s.writeUbyte(contrast_bias);
	s.writefloat(mipmap_lod_bias);
	s.writeUbyte(object_ambient[0]);
	s.writeUbyte(object_ambient[1]);
	s.writeUbyte(object_ambient[2]);
	s.writeUbyte(object_ambient[3]);
	s.writeUbyte(effect_ambient[0]);
	s.writeUbyte(effect_ambient[1]);
	s.writeUbyte(effect_ambient[2]);
	s.writeUbyte(effect_ambient[3]);
	for (unsigned int i = 0; i < light_count; i++) {
		light_array[i].write_light(s);
		}
	}

fmtLIT::fmtLIT () {
	area_count = 0;
	litVersion = 44;
	nMaxLights = 0;
	}

void fmtLIT::read_lit (bytestream &f) {
	size_t pos = f.tell();

	area_count = f.readUshort();
	litVersion = f.readUbyte();
	nMaxLights = f.readUbyte();

	//std::cout << "area_count:\t%\n" area_count

	if (area_count > 0) {

		area_addrs = std::vector<uint32_t>(area_count);
		for (unsigned int i = 0; i < area_count; i++) {
			area_addrs[i] = f.readUlong();
			}

		areas = std::vector<fmtLIT_Entry>(area_count);
		for (unsigned int i = 0; i < area_count; i++) {
			if (area_addrs[i] > 0) {
				f.seek((pos + area_addrs[i]));
				areas[i].read_lit_entry(f);
				}
			}
		}
	}

size_t fmtLIT::recalc_pointers () {
	size_t ptr = 4; // header size

	// amend count
	area_count = areas.size();

	// clear max num of lights count
	nMaxLights = 0;

	// add size of pointer table
	ptr += areas.size() * 4;

	// redim pointer table
	if (area_count > 0 && area_count != area_addrs.size()) {
		area_addrs.clear();
		area_addrs = std::vector<uint32_t> (area_count);
		for (unsigned int i = 0; i < area_count; i++) {
			// I use the pointer as a write flag; 0 to skip; 1 {>0} to write
			area_addrs[i] = 1;
			}
		}

	// amend pointer table
	for (unsigned int i = 0; i < area_count; i++) {
		if (area_addrs[i] > 0) {
			area_addrs[i] = ptr;

			// amend light count
			areas[i].light_count = areas[i].light_array.size();

			// collect max light count
			if (areas[i].light_count > nMaxLights) {
				nMaxLights = areas[i].light_count;
				}

			// append next size
			ptr += 260 + (areas[i].light_count * 300);
			}
		}
	return ptr;
	}

void fmtLIT::write_lit (bytestream &s) {

	// Recalculate Counts and Addresses
	size_t nsize = recalc_pointers();
	if (nsize == 0) {std::cout << "failed to write file\n"; return;}
	s.resize(nsize);

	// Write Header
	s.writeUshort(area_count);
	s.writeUbyte(litVersion);
	s.writeUbyte(nMaxLights);

	// Write Address Table
	for (unsigned int i = 0; i < area_count; i++) {
		s.writeUlong(area_addrs[i]);
		}

	// Write Data Blocks
	for (unsigned int i = 0; i < area_count; i++) {
		areas[i].write_fmtLIT_Entry(s);
		}

	// Write Padding to 32 Bytes
	unsigned int pad = (32-((s.tell()) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {
		s.writeUbyte(0xCD);
		}
	}

