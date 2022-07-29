#include "fmtCNS.h"


fmtCNS_Room::fmtCNS_Room () {
	enemy_enabled = false;
	obj_enabled = false;
	esp_enabled = false;
	espgen_enabled = false;
	ctrl_enabled = false;
	light_enabled = false;
	parts_enabled = false;
	modelinfo_enabled = false;
	prim_enabled = false;
	evt_enabled = false;
	sat_enabled = false;
	eat_enabled = false;
	}

void fmtCNS_Room::read_cns_room_flag (uint32_t val) {
	enemy_enabled = bit::get(val, 1);
	obj_enabled = bit::get(val, 2);
	esp_enabled = bit::get(val, 3);
	espgen_enabled = bit::get(val, 4);
	ctrl_enabled = bit::get(val, 5);
	light_enabled = bit::get(val, 6);
	parts_enabled = bit::get(val, 7);
	modelinfo_enabled = bit::get(val, 8);
	prim_enabled = bit::get(val, 9);
	evt_enabled = bit::get(val, 10);
	sat_enabled = bit::get(val, 11);
	eat_enabled = bit::get(val, 12);
	}

uint32_t fmtCNS_Room::get_cns_room_flag () {
	uint32_t val = 0;
	val = bit::set(val, 1, enemy_enabled);
	val = bit::set(val, 2, obj_enabled);
	val = bit::set(val, 3, esp_enabled);
	val = bit::set(val, 4, espgen_enabled);
	val = bit::set(val, 5, ctrl_enabled);
	val = bit::set(val, 6, light_enabled);
	val = bit::set(val, 7, parts_enabled);
	val = bit::set(val, 8, modelinfo_enabled);
	val = bit::set(val, 9, prim_enabled);
	val = bit::set(val, 10, evt_enabled);
	val = bit::set(val, 11, sat_enabled);
	val = bit::set(val, 12, eat_enabled);
	return val;
	}

fmtCNS_Core::fmtCNS_Core () {
	unk1_enabled = false;
	unk2_enabled = false;
	unk3_enabled = false;
	unk4_enabled = false;
	}

void fmtCNS_Core::read_cns_core_flag (uint32_t val) {
	unk1_enabled = bit::get(val, 1);
	unk2_enabled = bit::get(val, 2);
	unk3_enabled = bit::get(val, 3);
	unk4_enabled = bit::get(val, 4);
	}

uint32_t fmtCNS_Core::get_cns_core_flag () {
	uint32_t val = 0;
	val = bit::set(val, 1, unk1_enabled);
	val = bit::set(val, 2, unk2_enabled);
	val = bit::set(val, 3, unk3_enabled);
	val = bit::set(val, 4, unk4_enabled);
	return val;
	}

fmtCNS::fmtCNS () {
	flag1 = 0;
	enemy_num = 0;
	obj_num = 0;
	esp_num = 0;
	espgen_num = 0;
	ctrl_num = 0;
	light_num = 0;
	parts_num = 0;
	modelinfo_num = 0;
	prim_num = 0;
	evt_num = 0;
	sat_num = 0;
	eat_num = 0;
	core_flag = fmtCNS_Core();
	unk1 = 0;
	unk2 = 0;
	unk3 = 0;
	unk4 = 0;
	}

void fmtCNS::read_cns (bytestream &f) {

	flag1 = f.readUlong();
	flag2 = f.readUlong();

	if (flag2 > 0) {
		room_flag.read_cns_room_flag(flag2);
		enemy_num = f.readUlong();
		obj_num = f.readUlong();
		esp_num = f.readUlong();
		espgen_num = f.readUlong();
		ctrl_num = f.readUlong();
		light_num = f.readUlong();
		parts_num = f.readUlong();
		modelinfo_num = f.readUlong();
		prim_num = f.readUlong();
		evt_num = f.readUlong();
		sat_num = f.readUlong();
		eat_num = f.readUlong();
		}

	if ((flag2 = f.readUlong()) > 0) {
		core_flag.read_cns_core_flag(flag2);
		unk1 = f.readUlong();
		unk2 = f.readUlong();
		unk3 = f.readUlong();
		unk4 = f.readUlong();
		}
	}

void fmtCNS::write_cns (bytestream &s) {
	flag1 = room_flag.get_cns_room_flag();
	s.writeUlong(flag1);
	if (flag1 > 0) {
		s.writeUlong(enemy_num);
		s.writeUlong(obj_num);
		s.writeUlong(esp_num);
		s.writeUlong(espgen_num);
		s.writeUlong(ctrl_num);
		s.writeUlong(light_num);
		s.writeUlong(parts_num);
		s.writeUlong(modelinfo_num);
		s.writeUlong(prim_num);
		s.writeUlong(evt_num);
		s.writeUlong(sat_num);
		s.writeUlong(eat_num);
		}
	flag2 = core_flag.get_cns_core_flag();
	s.writeUlong(flag2);
	if (flag2 > 0) {
		s.writeUlong(unk1);
		s.writeUlong(unk2);
		s.writeUlong(unk3);
		s.writeUlong(unk4);
		}
	unsigned int pad = (32-((s.tell()) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writeUbyte(0xCD);} // pad to 32
	}
