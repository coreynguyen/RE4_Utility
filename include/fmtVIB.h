#ifndef FMTVIB_H
#define FMTVIB_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"


struct fmtVIB_Rumble {	// 8 Bytes
	uint32_t start_frame_pos;	// Range [0 - 2000]
	uint16_t end_frame_pos; 	// Range [0 - 2000]; relative from start
	uint8_t start_vib_level;	// Range [0 - 8]
	uint8_t end_vib_level;		// Range [0 - 8]
	fmtVIB_Rumble ();
	void read_vib_rumble (bytestream &f);
	void write_vib_rumble (bytestream &s);
	};

struct fmtVIB_Entry {
	uint32_t count;		// Range [0 - 64]
	std::vector<fmtVIB_Rumble> rumbles;
	fmtVIB_Entry ();
	void read_vib_entry (bytestream &f);
	void write_vib_entry (bytestream &s);
	};

struct fmtVIB {
	uint32_t count;	// always 64
	std::vector<uint32_t> addrs;
	std::vector<fmtVIB_Entry> vib_layout;
	fmtVIB ();
	void read_vib (bytestream &f);
	void write_vib (bytestream &s);
	};


#endif // FMTVIB_H
