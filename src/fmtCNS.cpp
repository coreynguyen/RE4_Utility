#include "fmtCNS.h"


fmtCNS_Enable::fmtCNS_Enable () {
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
	val13 = false;
	val14 = false;
	val15 = false;
	val16 = false;
	val17 = false;
	val18 = false;
	val19 = false;
	val20 = false;
	val21 = false;
	val22 = false;
	val23 = false;
	val24 = false;
	val25 = false;
	val26 = false;
	val27 = false;
	val28 = false;
	val29 = false;
	val30 = false;
	val31 = false;
	val32 = false;
	}

void fmtCNS_Enable::read_cns_room_flag (uint32_t val) {
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
	val13 = bit::get(val, 13);
	val14 = bit::get(val, 14);
	val15 = bit::get(val, 15);
	val16 = bit::get(val, 16);
	val17 = bit::get(val, 17);
	val18 = bit::get(val, 18);
	val19 = bit::get(val, 19);
	val20 = bit::get(val, 20);
	val21 = bit::get(val, 21);
	val22 = bit::get(val, 22);
	val23 = bit::get(val, 23);
	val24 = bit::get(val, 24);
	val25 = bit::get(val, 25);
	val26 = bit::get(val, 26);
	val27 = bit::get(val, 27);
	val28 = bit::get(val, 28);
	val29 = bit::get(val, 29);
	val30 = bit::get(val, 30);
	val31 = bit::get(val, 31);
	val32 = bit::get(val, 32);
	}

uint32_t fmtCNS_Enable::get_cns_room_flag () {
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
	val = bit::set(val, 13, val13);
	val = bit::set(val, 14, val14);
	val = bit::set(val, 15, val15);
	val = bit::set(val, 16, val16);
	val = bit::set(val, 17, val17);
	val = bit::set(val, 18, val18);
	val = bit::set(val, 19, val19);
	val = bit::set(val, 20, val20);
	val = bit::set(val, 21, val21);
	val = bit::set(val, 22, val22);
	val = bit::set(val, 23, val23);
	val = bit::set(val, 24, val24);
	val = bit::set(val, 25, val25);
	val = bit::set(val, 26, val26);
	val = bit::set(val, 27, val27);
	val = bit::set(val, 28, val28);
	val = bit::set(val, 29, val29);
	val = bit::set(val, 30, val30);
	val = bit::set(val, 31, val31);
	val = bit::set(val, 32, val32);
	return val;
	}

fmtCNS::fmtCNS () {
	count = 0;
	enable.read_cns_room_flag(0);
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
    for (int i = 0; i < 20; i++) {value[i] = 0;}
	}

void fmtCNS::read_cns (bytestream &f) {

	count = f.readUlong();
	enable.read_cns_room_flag(f.readUlong());
    if (count > 0) enemy_num        = f.readUlong();
    if (count > 1) obj_num          = f.readUlong();
    if (count > 2) esp_num          = f.readUlong();
    if (count > 3) espgen_num       = f.readUlong();
    if (count > 4) ctrl_num         = f.readUlong();
    if (count > 5) light_num        = f.readUlong();
    if (count > 6) parts_num        = f.readUlong();
    if (count > 7) modelinfo_num    = f.readUlong();
    if (count > 8) prim_num         = f.readUlong();
    if (count > 9) evt_num          = f.readUlong();
    if (count >10) sat_num          = f.readUlong();
    if (count >11) eat_num          = f.readUlong();
    if (count >12) {
        int c = count - 12;
        for (int i = 0; i < c; i++) {
            value[i] = f.readUlong();
            }
        }
	}

void fmtCNS::write_cns (bytestream &s) {
	uint32_t val = enable.get_cns_room_flag();
	uint32_t n = val;
    count = 0;
    while (n) {
        n >>= 1; // shift bits to the right
        count++;
        }
	s.writeUlong(count);
	s.writeUlong(val);

    if (count > 0) s.writeUlong(enemy_num);
    if (count > 1) s.writeUlong(obj_num);
    if (count > 2) s.writeUlong(esp_num);
    if (count > 3) s.writeUlong(espgen_num);
    if (count > 4) s.writeUlong(ctrl_num);
    if (count > 5) s.writeUlong(light_num);
    if (count > 6) s.writeUlong(parts_num);
    if (count > 7) s.writeUlong(modelinfo_num);
    if (count > 8) s.writeUlong(prim_num);
    if (count > 9) s.writeUlong(evt_num);
    if (count >10) s.writeUlong(sat_num);
    if (count >11) s.writeUlong(eat_num);
    if (count >12) {
        int c = count - 12;
        for (int i = 0; i < c; i++) {
            s.writeUlong(value[i]);
            }
        }

	unsigned int pad = (32-((s.tell()) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writeUbyte(0xCD);} // pad to 32
	}
