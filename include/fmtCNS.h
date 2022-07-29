#ifndef FMTCNS_H
#define FMTCNS_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"


struct fmtCNS_Room {
	bool enemy_enabled;
	bool obj_enabled;
	bool esp_enabled;
	bool espgen_enabled;
	bool ctrl_enabled;
	bool light_enabled;
	bool parts_enabled;
	bool modelinfo_enabled;
	bool prim_enabled;
	bool evt_enabled;
	bool sat_enabled;
	bool eat_enabled;
	fmtCNS_Room ();
	void read_cns_room_flag (uint32_t val);
	uint32_t get_cns_room_flag ();
	};

struct fmtCNS_Core {
	bool unk1_enabled;
	bool unk2_enabled;
	bool unk3_enabled;
	bool unk4_enabled;
	fmtCNS_Core ();
	void read_cns_core_flag (uint32_t val);
	uint32_t get_cns_core_flag ();
	};

struct fmtCNS {
	uint32_t flag1;
	uint32_t flag2;
	fmtCNS_Room room_flag;
	uint32_t enemy_num;		// Range [0 - 200]
	uint32_t obj_num;			// Range [0 - 800]
	uint32_t esp_num;			// Range [0 - 16384]
	uint32_t espgen_num;		// Range [0 - 1000]
	uint32_t ctrl_num;			// Range [0 - 200]
	uint32_t light_num;			// Range [0 - 200]
	uint32_t parts_num;			// Range [0 - 5000]
	uint32_t modelinfo_num;	// Range [0 - 3000]
	uint32_t prim_num;			// Range [0 - 8388608]
	uint32_t evt_num;			// Range [0 - 100]
	uint32_t sat_num;			// Range [0 - 200]
	uint32_t eat_num;			// Range [0 - 200]
	fmtCNS_Core core_flag;
	uint32_t unk1;
	uint32_t unk2;
	uint32_t unk3;
	uint32_t unk4;
	fmtCNS ();
	void read_cns (bytestream &f);
	void write_cns (bytestream &s);
	};


#endif // FMTCNS_H