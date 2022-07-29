#ifndef FMTDSE_H
#define FMTDSE_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"


struct fmtDSE_Entry {
	uint16_t room_id;	// where the door exits to; range:[256 - 1308] two bytes; STAGE|ROOM
	uint16_t door_se_id;	// range:[0 - 11]
	/*
	I assume the audio for the doors are located here
		/BIO4/snd/doorse00*.xsb

	however adding new clips has no effect;
	maybe there is a table the clips are defined?

	so for now we can only use the 11 preset ones
		0x00:	Outside Large Gate
		0x01:	Outside Large Wood Door
		0x02:	Outside Small Gate
		0x03:	Steal Ladder
		0x04:	Inside Wood Door
		0x05:	Stone Slab
		0x06:	Inside Wood Door2
		0x07:	Eletronic Door
		0x08:	Inside Steal Door
		0x09:	Garbage Shoot
		0x0A:	Metal Ladder2
		0x0B:	Inside Steal Door2

	in the xsb {xbox sound bank} there are 2 audio
	files; one for when the door opens and the
	other is for when the door closes
	*/
	int16_t unk03;	// range:[-1; 2; 4] Could not figure out what these values do
	int16_t unk04;	// Always -1
	int16_t unk05;	// Always -1
	int16_t unk06;	// Always -1
	fmtDSE_Entry ();
	void read_dse_entry (bytestream &f);
	void write_dse_entry (bytestream &s);
	};

struct fmtDSE {
	uint32_t count;
	std::vector<fmtDSE_Entry> data;
	fmtDSE ();
	void read_dse (bytestream &f);
	void write_dse (bytestream &s);
	};


#endif // FMTDSE_H
