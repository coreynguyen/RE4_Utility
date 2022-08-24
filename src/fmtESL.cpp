#include "fmtESL.h"


fmtESL_BE::fmtESL_BE () {
	be_alive = true;
	be_set = false;
	be_flg3 = false;
	be_flg4 = false;
	be_flg5 = false;
	be_flg6 = false;
	be_flg7 = false;
	be_die = false;
	}

void fmtESL_BE::set_be_flag (uint8_t val) {
	be_alive = bit::get(val, 1);
	be_set = bit::get(val, 2);
	be_flg3 = bit::get(val, 3);
	be_flg4 = bit::get(val, 4);
	be_flg5 = bit::get(val, 5);
	be_flg6 = bit::get(val, 6);
	be_flg7 = bit::get(val, 7);
	be_die = bit::get(val, 8);
	}

uint8_t fmtESL_BE::get_be_flag () {
	int val = 0;
	val = bit::set(val, 1, be_alive);
	val = bit::set(val, 2, be_set);
	val = bit::set(val, 3, be_flg3);
	val = bit::set(val, 4, be_flg4);
	val = bit::set(val, 5, be_flg5);
	val = bit::set(val, 6, be_flg6);
	val = bit::set(val, 7, be_flg7);
	val = bit::set(val, 8, be_die);
	return val;
	}

void fmtESL_BE::read_be_flag (bytestream &f) {
	set_be_flag(f.readUbyte());
	}

void fmtESL_BE::write_be_flag (bytestream &s) {
	s.writebyte(get_be_flag());
	}

fmtESL_EM::fmtESL_EM () {
	em_flg01 = false;
	em_flg02 = false;
	em_flg03 = false;
	em_flg04 = false;
	em_flg05 = false;
	em_flg06 = false;
	em_flg07 = false;
	em_flg08 = false;
	em_flg09 = false;
	em_flg10 = false;
	em_flg11 = false;
	em_flg12 = false;
	em_flg13 = false;
	em_flg14 = false;
	em_flg15 = false;
	em_flg16 = false;
	em_flg17 = false;
	em_flg18 = false;
	em_flg19 = false;
	em_flg20 = false;
	em_flg21 = false;
	em_flg22 = false;
	em_flg23 = false;
	em_flg24 = false;
	em_flg25 = false;
	em_flg26 = false;
	em_flg27 = false;
	em_flg28 = false;
	em_flg29 = false;
	em_flg30 = false;
	em_flg31 = false;
	em_flg32 = false;
	}

void fmtESL_EM::set_em_flag (uint32_t val) {
	em_flg01 = bit::get(val,  1);
	em_flg02 = bit::get(val,  2);
	em_flg03 = bit::get(val,  3);
	em_flg04 = bit::get(val,  4);
	em_flg05 = bit::get(val,  5);
	em_flg06 = bit::get(val,  6);
	em_flg07 = bit::get(val,  7);
	em_flg08 = bit::get(val,  8);
	em_flg09 = bit::get(val,  9);
	em_flg10 = bit::get(val, 10);
	em_flg11 = bit::get(val, 11);
	em_flg12 = bit::get(val, 12);
	em_flg13 = bit::get(val, 13);
	em_flg14 = bit::get(val, 14);
	em_flg15 = bit::get(val, 15);
	em_flg16 = bit::get(val, 16);
	em_flg17 = bit::get(val, 17);
	em_flg18 = bit::get(val, 18);
	em_flg19 = bit::get(val, 19);
	em_flg20 = bit::get(val, 20);
	em_flg21 = bit::get(val, 21);
	em_flg22 = bit::get(val, 22);
	em_flg23 = bit::get(val, 23);
	em_flg24 = bit::get(val, 24);
	em_flg25 = bit::get(val, 25);
	em_flg26 = bit::get(val, 26);
	em_flg27 = bit::get(val, 27);
	em_flg28 = bit::get(val, 28);
	em_flg29 = bit::get(val, 29);
	em_flg30 = bit::get(val, 30);
	em_flg31 = bit::get(val, 31);
	em_flg32 = bit::get(val, 32);
	}

uint32_t fmtESL_EM::get_em_flag () {
	unsigned int val = 0;
	val = bit::set(val,  1, em_flg01);
	val = bit::set(val,  2, em_flg02);
	val = bit::set(val,  3, em_flg03);
	val = bit::set(val,  4, em_flg04);
	val = bit::set(val,  5, em_flg05);
	val = bit::set(val,  6, em_flg06);
	val = bit::set(val,  7, em_flg07);
	val = bit::set(val,  8, em_flg08);
	val = bit::set(val,  9, em_flg09);
	val = bit::set(val, 10, em_flg10);
	val = bit::set(val, 11, em_flg11);
	val = bit::set(val, 12, em_flg12);
	val = bit::set(val, 13, em_flg13);
	val = bit::set(val, 14, em_flg14);
	val = bit::set(val, 15, em_flg15);
	val = bit::set(val, 16, em_flg16);
	val = bit::set(val, 17, em_flg17);
	val = bit::set(val, 18, em_flg18);
	val = bit::set(val, 19, em_flg19);
	val = bit::set(val, 20, em_flg20);
	val = bit::set(val, 21, em_flg21);
	val = bit::set(val, 22, em_flg22);
	val = bit::set(val, 23, em_flg23);
	val = bit::set(val, 24, em_flg24);
	val = bit::set(val, 25, em_flg25);
	val = bit::set(val, 26, em_flg26);
	val = bit::set(val, 27, em_flg27);
	val = bit::set(val, 28, em_flg28);
	val = bit::set(val, 29, em_flg29);
	val = bit::set(val, 30, em_flg30);
	val = bit::set(val, 31, em_flg31);
	val = bit::set(val, 32, em_flg32);
	return val;
	}

void fmtESL_EM::read_em_flag (bytestream &f) {
	set_em_flag(f.readUlong());
	}

void fmtESL_EM::write_em_flag (bytestream &s) {
	s.writelong(get_em_flag());
	}

fmtESL_Spawn::fmtESL_Spawn () {
	be_flag.set_be_flag(0);
	modelID = 0;
	type = 0;
	anim_set = 0;
	em_flag.set_em_flag(0);
	healthPoints = 0;
	unk1 = 0;
	chara = 0;
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	rotation[0] = 0;
	rotation[1] = 0;
	rotation[2] = 0;
	roomID = 0;
	guard_radius = 0;
	unk4 = 0;
	unk5 = 0;
	unk6 = 0;
	unk7 = 0;
	}

void fmtESL_Spawn::read_esl_spawn (bytestream &f) {
	//const double GUARDRAD_SCALE = 1000.0; //  converts meters to millimeters
	//const double POSITION_SCALE = 10.0; //  cm converts to millimeters
	//const double ROTATION_SCALE = 0.010986332551700724487745603456244676035; // converts whatever to degrees
	//const double ROTATION_SCALE2 = 0.00019174767574620779644429946175175338444; // converts whatever to radians

	be_flag.read_be_flag(f);
	modelID = f.readUbyte();
	type = f.readUbyte();
	anim_set = f.readUbyte();
	em_flag.read_em_flag(f);
	healthPoints = f.readUshort(); // set to 0, enemy will ignore player and cannot die
	unk1 = f.readUbyte();
	chara = f.readUbyte();
	position[0] = f.readshort();// * POSITION_SCALE;
	position[1] = f.readshort();// * POSITION_SCALE;
	position[2] = f.readshort();// * POSITION_SCALE;
	rotation[0] = f.readshort();// * ROTATION_SCALE;
	rotation[1] = f.readshort();// * ROTATION_SCALE;
	rotation[2] = f.readshort();// * ROTATION_SCALE;
	roomID = f.readUshort();
	guard_radius = f.readUshort();// * GUARDRAD_SCALE
	// padding
	unk4 = f.readUbyte();
	unk5 = f.readUbyte();
	unk6 = f.readUbyte();
	unk7 = f.readUbyte();
	}

void fmtESL_Spawn::write_esl_spawn (bytestream &s) {
	be_flag.write_be_flag(s);
	s.writebyte(modelID);
	s.writebyte(type);
	s.writebyte(anim_set);
	em_flag.write_em_flag(s);
	s.writeshort(healthPoints);
	s.writebyte(unk1);
	s.writebyte(chara);
	s.writeshort(position[0]);
	s.writeshort(position[1]);
	s.writeshort(position[2]);;
	s.writeshort(rotation[0]);
	s.writeshort(rotation[1]);
	s.writeshort(rotation[2]);
	s.writeshort(roomID);
	s.writeshort(guard_radius);
	s.writebyte(unk4);
	s.writebyte(unk5);
	s.writebyte(unk6);
	s.writebyte(unk7);
	}

bool fmtESL::validate (bytestream &f) {
	bool isGood = false;
	//size_t pos = f.tell();
	if (8160 <= f.size) {
		isGood = true;
		}
	return isGood;
	}

bool fmtESL::read_esl (bytestream &f) {
	bool sucess = false;
	if (validate(f)) {
		unsigned int spawn_count = 255;
		for (unsigned int i = 0; i < spawn_count; i++) {
			spawn[i].read_esl_spawn(f);
			}
		sucess = true;
		}
	return sucess;
	}

void fmtESL::write_esl (bytestream &s) {
	unsigned int spawn_count = 255;
	for (unsigned int i = 0; i < spawn_count; i++) {
		spawn[i].write_esl_spawn(s);
		}
	}


void fmtESL::xml_export (std::wstring file) {
	/* copies the variables into an XML text */

	std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

	unsigned int spawn_count = 255;
	if (spawn_count == 0) {return;}

	// XML header


	// XML Root Node
	xml += "<esl name=\"" + wstring_to_string(getFilenameFileW(file)) + ".esl\" count=\"" + to_string(spawn_count) + "\">\n";
	xml += "    <!-- CANNOT EXCEED 255 ENTRIES -->\n";
	xml += "    <!-- positional units are millimeters and angles are radians -->\n";


	std::stringstream ss;
	std::string state = "FALSE";
	std::string model = "";
	for (unsigned int i = 0; i < spawn_count; i++) {
		xml += "    <entry index=\"" + to_string(i) + "\">\n";
		model = "";
		switch (spawn[i].modelID) {
			case 0x00: {model = " (Invalid 00)"; break;}
			case 0x01: {model = " (Invalid 01)"; break;}
			case 0x02: {model = " (Sub Leon)"; break;}
			case 0x03: {model = " (Sub Ashley)"; break;}
			case 0x04: {model = " (Sub Luis)"; break;}
			case 0x05: {model = " (Sub 5)"; break;}
			case 0x06: {model = " (Sub 6)"; break;}
			case 0x07: {model = " (Sub test)"; break;}
			case 0x08: {model = " (Invalid 8)"; break;}
			case 0x09: {model = " (Invalid 9)"; break;}
			case 0x0A: {model = " (Invalid a)"; break;}
			case 0x0B: {model = " (Invalid b)"; break;}
			case 0x0C: {model = " (Invalid c)"; break;}
			case 0x0D: {model = " (Invalid d)"; break;}
			case 0x0E: {model = " (JetSki)"; break;}
			case 0x0F: {model = " (Ship)"; break;}
			case 0x10: {model = " (Ganado)"; break;}
			case 0x11: {model = " (Ganado)"; break;}
			case 0x12: {model = " (Ganado)"; break;}
			case 0x13: {model = " (Ganado)"; break;}
			case 0x14: {model = " (Ganado)"; break;}
			case 0x15: {model = " (Ganado)"; break;}
			case 0x16: {model = " (Ganado)"; break;}
			case 0x17: {model = " (Ganado)"; break;}
			case 0x18: {model = " (Trader)"; break;}
			case 0x19: {model = " (Ganado)"; break;}
			case 0x1A: {model = " (Ganado)"; break;}
			case 0x1B: {model = " (Ganado)"; break;}
			case 0x1C: {model = " (Ganado)"; break;}
			case 0x1D: {model = " (Ganado)"; break;}
			case 0x1E: {model = " (Ganado)"; break;}
			case 0x1F: {model = " (Ganado)"; break;}
			case 0x20: {model = " (Ganado)"; break;}
			case 0x21: {model = " (Dog)"; break;}
			case 0x22: {model = " (Enemy Dog)"; break;}
			case 0x23: {model = " (Crow)"; break;}
			case 0x24: {model = " (Snake )"; break;}
			case 0x25: {model = " (Parasite)"; break;}
			case 0x26: {model = " (Cow)"; break;}
			case 0x27: {model = " (BlackBass)"; break;}
			case 0x28: {model = " (Chicken)"; break;}
			case 0x29: {model = " (Bat)"; break;}
			case 0x2A: {model = " (Trap)"; break;}
			case 0x2B: {model = " (Elgigante)"; break;}
			case 0x2C: {model = " (InsectBoss)"; break;}
			case 0x2D: {model = " (InsectHuman)"; break;}
			case 0x2E: {model = " (Spider sml)"; break;}
			case 0x2F: {model = " (Salamander)"; break;}
			case 0x30: {model = " (Saddler)"; break;}
			case 0x31: {model = " (Saddler2)"; break;}
			case 0x32: {model = " (U)"; break;}
			case 0x33: {model = " (Invalid3)"; break;}
			case 0x34: {model = " (No. & No.)"; break;}
			case 0x35: {model = " (No. After)"; break;}
			case 0x36: {model = " (Regenerater)"; break;}
			case 0x37: {model = " (Invalid7)"; break;}
			case 0x38: {model = " (No. After)"; break;}
			case 0x39: {model = " (No.)"; break;}
			case 0x3A: {model = " (Seeker)"; break;}
			case 0x3B: {model = " (Truck & Cart)"; break;}
			case 0x3C: {model = " (Armor)"; break;}
			case 0x3D: {model = " (Helicopter)"; break;}
			case 0x3E: {model = " (r22c Mark"; break;}
			}



		ss.str(std::string());
		ss << std::uppercase << TO_HEX(spawn[i].modelID, false, 2);

		xml += "        <!-- ./bio4/Em/em" + padString(ss.str(), 2, "0") + ".udas" + model + " -->\n";
		xml += "        <behavior_flag>\n";
		state = "FALSE"; if (spawn[i].be_flag.be_alive) {state = "TRUE";}
		xml += "            <alive>" + state + "</alive>\n";
		state = "FALSE"; if (spawn[i].be_flag.be_set) {state = "TRUE";}
		xml += "            <set>" + state + "</set>\n";
		state = "FALSE"; if (spawn[i].be_flag.be_flg3) {state = "TRUE";}
		xml += "            <flg3>" + state + "</flg3>\n";
		state = "FALSE"; if (spawn[i].be_flag.be_flg4) {state = "TRUE";}
		xml += "            <flg4>" + state + "</flg4>\n";
		state = "FALSE"; if (spawn[i].be_flag.be_flg5) {state = "TRUE";}
		xml += "            <flg5>" + state + "</flg5>\n";
		state = "FALSE"; if (spawn[i].be_flag.be_flg6) {state = "TRUE";}
		xml += "            <flg6>" + state + "</flg6>\n";
		state = "FALSE"; if (spawn[i].be_flag.be_flg7) {state = "TRUE";}
		xml += "            <flg7>" + state + "</flg7>\n";
		state = "FALSE"; if (spawn[i].be_flag.be_die) {state = "TRUE";}
		xml += "            <die>" + state + "</die>\n";
		xml += "        </behavior_flag>\n";
		xml += "        <modelID>0x" + padString(ss.str(), 2, "0") + "</modelID>\n";
		xml += "        <type>" + to_string((int)spawn[i].type) + "</type>\n";
		xml += "        <anim_set>" + to_string((int)spawn[i].anim_set) + "</anim_set>\n";
		xml += "        <enemy_flag>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg01) {state = "TRUE";}
		xml += "            <flg01>" + state + "</flg01>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg02) {state = "TRUE";}
		xml += "            <flg02>" + state + "</flg02>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg03) {state = "TRUE";}
		xml += "            <flg03>" + state + "</flg03>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg04) {state = "TRUE";}
		xml += "            <flg04>" + state + "</flg04>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg05) {state = "TRUE";}
		xml += "            <flg05>" + state + "</flg05>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg06) {state = "TRUE";}
		xml += "            <flg06>" + state + "</flg06>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg07) {state = "TRUE";}
		xml += "            <flg07>" + state + "</flg07>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg08) {state = "TRUE";}
		xml += "            <flg08>" + state + "</flg08>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg09) {state = "TRUE";}
		xml += "            <flg09>" + state + "</flg09>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg10) {state = "TRUE";}
		xml += "            <flg10>" + state + "</flg10>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg11) {state = "TRUE";}
		xml += "            <flg11>" + state + "</flg11>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg12) {state = "TRUE";}
		xml += "            <flg12>" + state + "</flg12>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg13) {state = "TRUE";}
		xml += "            <flg13>" + state + "</flg13>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg14) {state = "TRUE";}
		xml += "            <flg14>" + state + "</flg14>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg15) {state = "TRUE";}
		xml += "            <flg15>" + state + "</flg15>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg16) {state = "TRUE";}
		xml += "            <flg16>" + state + "</flg16>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg17) {state = "TRUE";}
		xml += "            <flg17>" + state + "</flg17>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg18) {state = "TRUE";}
		xml += "            <flg18>" + state + "</flg18>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg19) {state = "TRUE";}
		xml += "            <flg19>" + state + "</flg19>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg20) {state = "TRUE";}
		xml += "            <flg20>" + state + "</flg20>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg21) {state = "TRUE";}
		xml += "            <flg21>" + state + "</flg21>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg22) {state = "TRUE";}
		xml += "            <flg22>" + state + "</flg22>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg23) {state = "TRUE";}
		xml += "            <flg23>" + state + "</flg23>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg24) {state = "TRUE";}
		xml += "            <flg24>" + state + "</flg24>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg25) {state = "TRUE";}
		xml += "            <flg25>" + state + "</flg25>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg26) {state = "TRUE";}
		xml += "            <flg26>" + state + "</flg26>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg27) {state = "TRUE";}
		xml += "            <flg27>" + state + "</flg27>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg28) {state = "TRUE";}
		xml += "            <flg28>" + state + "</flg28>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg29) {state = "TRUE";}
		xml += "            <flg29>" + state + "</flg29>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg30) {state = "TRUE";}
		xml += "            <flg30>" + state + "</flg30>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg31) {state = "TRUE";}
		xml += "            <flg31>" + state + "</flg31>\n";
		state = "FALSE"; if (spawn[i].em_flag.em_flg32) {state = "TRUE";}
		xml += "            <flg32>" + state + "</flg32>\n";
		xml += "        </enemy_flag>\n";
		xml += "        <healthPoints>" + to_string(spawn[i].healthPoints) + "</healthPoints>\n";
		xml += "        <unk1>" + to_string((int)spawn[i].unk1) + "</unk1>\n";
		xml += "        <chara>" + to_string((int)spawn[i].chara) + "</chara>\n";
		xml += "        <!--ENUM: chara\n";
		xml += "           0    None\n";
		xml += "           1    Keep\n";
		xml += "           2    Rush\n";
		xml += "           3    Stop\n";
		xml += "           4    Escape\n";
		xml += "           5    In Room\n";
		xml += "        -->\n";
		xml += "        <position_x>" + to_string(spawn[i].position[0]) + "</position_x>\n";
		xml += "        <position_y>" + to_string(spawn[i].position[1]) + "</position_y>\n";
		xml += "        <position_z>" + to_string(spawn[i].position[2]) + "</position_z>\n";
		xml += "        <rotation_x>" + to_string(spawn[i].rotation[0]) + "</rotation_x>\n";
		xml += "        <rotation_y>" + to_string(spawn[i].rotation[1]) + "</rotation_y>\n";
		xml += "        <rotation_z>" + to_string(spawn[i].rotation[2]) + "</rotation_z>\n";
		ss.str(std::string());
		ss << std::uppercase << TO_HEX(spawn[i].roomID & 0xFF, false, 2);
		xml += "        <stageID>" + to_string(spawn[i].roomID >> 8) + "</stageID>\n";
		xml += "        <roomID>0x" + padString(ss.str(), 2, "0") + "</roomID>\n";
		xml += "        <guard_radius>" + to_string(spawn[i].guard_radius * 1000) + "</guard_radius>\n";
		xml += "        <unk4>" + to_string((int)spawn[i].unk4) + "</unk4>\n";
		xml += "        <unk5>" + to_string((int)spawn[i].unk5) + "</unk5>\n";
		xml += "        <unk6>" + to_string((int)spawn[i].unk6) + "</unk6>\n";
		xml += "        <unk7>" + to_string((int)spawn[i].unk7) + "</unk7>\n";
		xml += "    </entry>\n";
		}


	// Close XML Root Node
	xml += "</esl>\n";

	// Save File
	bytestream s;
	s.writeFileW(file, 0, xml.size(), (char*)xml.c_str());

	}

void fmtESL::xml_import (rapidxml::xml_document<> &doc) {

	// Check Root Node
	rapidxml::xml_node<>* NODE_ESL = doc.first_node("esl");
	if (NODE_ESL == NULL) {return;}

	// Count Number Stages
	int ESL_NUM = 0;
	for (rapidxml::xml_node<>* NODE_SPAWN = NODE_ESL->first_node("entry"); NODE_SPAWN; NODE_SPAWN = NODE_SPAWN->next_sibling()) {ESL_NUM++;}
	if (ESL_NUM == 0) {return;}

	// Loop Through Each File

	int SPAWN_INDEX = 0;
	rapidxml::xml_node<>* NODE_ITEM;
	rapidxml::xml_node<>* NODE_SUBIT;
	bool state;
	uint16_t roomid;
	std::string str;

	for (rapidxml::xml_node<>* NODE_SPAWN = NODE_ESL->first_node("entry"); NODE_SPAWN; NODE_SPAWN = NODE_SPAWN->next_sibling()) {
		if (SPAWN_INDEX > 255) {break;}

		roomid = 0;


		if ((NODE_ITEM = NODE_SPAWN->first_node("behavior_flag")) != NULL) {

			if ((NODE_SUBIT = NODE_ITEM->first_node("alive")) != NULL) {
				str = toupper(std::string(NODE_SUBIT->value()));
				state = false; if (str == "TRUE" || str == "1") {state = true;}
				spawn[SPAWN_INDEX].be_flag.be_alive = state;
				}
			if ((NODE_SUBIT = NODE_ITEM->first_node("set")) != NULL) {
				str = toupper(std::string(NODE_SUBIT->value()));
				state = false; if (str == "TRUE" || str == "1") {state = true;}
				spawn[SPAWN_INDEX].be_flag.be_set = state;
				}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg3")) != NULL) {
				str = toupper(std::string(NODE_SUBIT->value()));
				state = false; if (str == "TRUE" || str == "1") {state = true;}
				spawn[SPAWN_INDEX].be_flag.be_flg3 = state;
				}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg4")) != NULL) {
				str = toupper(std::string(NODE_SUBIT->value()));
				state = false; if (str == "TRUE" || str == "1") {state = true;}
				spawn[SPAWN_INDEX].be_flag.be_flg4 = state;
				}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg5")) != NULL) {
				str = toupper(std::string(NODE_SUBIT->value()));
				state = false; if (str == "TRUE" || str == "1") {state = true;}
				spawn[SPAWN_INDEX].be_flag.be_flg5 = state;
				}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg6")) != NULL) {
				str = toupper(std::string(NODE_SUBIT->value()));
				state = false; if (str == "TRUE" || str == "1") {state = true;}
				spawn[SPAWN_INDEX].be_flag.be_flg6 = state;
				}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg7")) != NULL) {
				str = toupper(std::string(NODE_SUBIT->value()));
				state = false; if (str == "TRUE" || str == "1") {state = true;}
				spawn[SPAWN_INDEX].be_flag.be_flg7 = state;
				}
			if ((NODE_SUBIT = NODE_ITEM->first_node("die")) != NULL) {
				str = toupper(std::string(NODE_SUBIT->value()));
				state = false; if (str == "TRUE" || str == "1") {state = true;}
				spawn[SPAWN_INDEX].be_flag.be_die = state;
				}

			}
		if ((NODE_ITEM = NODE_SPAWN->first_node("modelID")) != NULL) {spawn[SPAWN_INDEX].modelID = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("type")) != NULL) {spawn[SPAWN_INDEX].type = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("anim_set")) != NULL) {spawn[SPAWN_INDEX].anim_set = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("enemy_flag")) != NULL) {
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg01")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg01 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg02")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg02 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg03")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg03 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg04")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg04 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg05")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg05 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg06")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg06 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg07")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg07 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg08")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg08 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg09")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg09 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg10")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg10 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg11")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg11 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg12")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg12 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg13")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg13 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg14")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg14 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg15")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg15 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg16")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg16 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg17")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg17 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg18")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg18 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg19")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg19 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg20")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg20 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg21")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg21 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg22")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg22 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg23")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg23 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg24")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg24 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg25")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg25 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg26")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg26 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg27")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg27 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg28")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg28 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg29")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg29 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg30")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg30 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg31")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg31 = state;}
			if ((NODE_SUBIT = NODE_ITEM->first_node("flg32")) != NULL) {str = toupper(std::string(NODE_SUBIT->value())); state = false; if (str == "TRUE" || str == "1") {state = true;} spawn[SPAWN_INDEX].em_flag.em_flg32 = state;}

			}
		if ((NODE_ITEM = NODE_SPAWN->first_node("healthPoints")) != NULL) {spawn[SPAWN_INDEX].healthPoints = ((uint16_t)convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("unk1")) != NULL) {spawn[SPAWN_INDEX].unk1 = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("chara")) != NULL) {spawn[SPAWN_INDEX].chara = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("position_x")) != NULL) {spawn[SPAWN_INDEX].position[0] = convert_to<float>(std::string(NODE_ITEM->value()));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("position_y")) != NULL) {spawn[SPAWN_INDEX].position[1] = convert_to<float>(std::string(NODE_ITEM->value()));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("position_z")) != NULL) {spawn[SPAWN_INDEX].position[2] = convert_to<float>(std::string(NODE_ITEM->value()));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("rotation_x")) != NULL) {spawn[SPAWN_INDEX].rotation[0] = convert_to<float>(std::string(NODE_ITEM->value()));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("rotation_y")) != NULL) {spawn[SPAWN_INDEX].rotation[1] = convert_to<float>(std::string(NODE_ITEM->value()));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("rotation_z")) != NULL) {spawn[SPAWN_INDEX].rotation[2] = convert_to<float>(std::string(NODE_ITEM->value()));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("stageID")) != NULL) {roomid += convert_to<int>(std::string(NODE_ITEM->value())) << 8;}
		if ((NODE_ITEM = NODE_SPAWN->first_node("roomID")) != NULL) {roomid += convert_to<int>(std::string(NODE_ITEM->value()));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("guard_radius")) != NULL) {spawn[SPAWN_INDEX].guard_radius = (uint16_t)(convert_to<int>(std::string(NODE_ITEM->value())) / 1000);}
		if ((NODE_ITEM = NODE_SPAWN->first_node("unk4")) != NULL) {spawn[SPAWN_INDEX].unk4 = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("unk5")) != NULL) {spawn[SPAWN_INDEX].unk5 = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("unk6")) != NULL) {spawn[SPAWN_INDEX].unk6 = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		if ((NODE_ITEM = NODE_SPAWN->first_node("unk7")) != NULL) {spawn[SPAWN_INDEX].unk7 = (uint8_t)(convert_to<int>(std::string(NODE_ITEM->value())));}
		spawn[SPAWN_INDEX].roomID = roomid;
		SPAWN_INDEX++;
		} // FILE NODE, END


	}

