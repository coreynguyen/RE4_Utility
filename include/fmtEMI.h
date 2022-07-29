#ifndef FMTEMI_H
#define FMTEMI_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"

struct fmtEMI_Entry {	// 64 bytes
	uint8_t work_type;	// Work Type
	/*
	0x00:	DISABLED
	0x01:	EM10 Hide Pos
	0x02:	EM2F Route Pos
	0x03:	EM2B House Pos
	0x04:	EM2B Rock Pos
	0x05:	Ashley Take Away
	0x06:	Rock Roll Route
	0x07:	Rock Escape Pos
	0x08:	Rock Start Pos
	0x09:	Ashley Jump Point
	0x0A:	Dog Bark Pos
	0x0B	Ashley Route Point
	0x0C:	Return Start Pos
	0x0D:	EM2B Catch Dir
	0x0E:	No.3 Snipe Pos
	0x0F:	EM10 Goto Pos
	0x10:	EM2D No Wall
	0x11:	EM32 Jump Pos
	0x12:	EM32 Ceiling Pos
	0x13:	EM3A Route
	*/
	uint8_t work0;	// work0
	uint8_t work1;	// work1
	uint8_t work2;	// work2
	float position[3];	// pos
	float dir;	// direction {radians}
	uint8_t reserve[44]; // ? 44bytes; always blank?
	fmtEMI_Entry ();
	void read_emi_entry (bytestream &f);
	void write_emi_entry (bytestream &s);
	};

struct fmtEMI {
	uint32_t count;
	uint32_t unk01; // always 0?
	std::vector<fmtEMI_Entry> data;
	fmtEMI ();
	void read_emi (bytestream &f);
	void write_emi (bytestream &s);
	};

#endif // FMTEMI_H
