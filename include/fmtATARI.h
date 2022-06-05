/*	======================================================================

	Title:		[PC] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		January 30 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Editing of the Atari Blocks

	Change Log:

	[2022-01-30]
		wrote it !

	======================================================================	*/

#ifndef FMTATARI_H
#define FMTATARI_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"

struct fmtATARI {	// 52 Bytes
	/*
		in the sar file, these 4 bytes suggest they
		configure what can enter the zone..

		however its not claer if (this is apart of the zone
		class, or it was something that was defined outside of it
	*/
	uint8_t unk1;	// Range [0 to 252]
	uint8_t unk2;	// Always 0? else active range:[0:OFF 1:ON] Range [0 to 248]
	uint8_t unk3;	// Always 0? else player no# range:[0 - 254] {-1 means off} range 0, 48, 101, 194, 237, 251
	uint8_t unk4;	// Always 0? else enemy no# range:[0 - 254] {-1 means off} range 0, 128, 129
	uint8_t unk5;	// Always 1
	uint8_t type; // Range [1: Box, 2: Circle, 3: Sphere]
	uint8_t unk7;	// Always 0
	uint8_t unk8;	// Always 0
	float pos_z;
	float height;
	float radius;
	float pos[8];

	//								|	BOX				|	CIRCLE			|	Cylinder					|
	//								|______________________	|______________________	|______________________________	|
	//dim[1] = f.readfloat()	// |	POS1 X			|	NULL1			|	CONE ANG X			|
	//dim[2] = f.readfloat()	// |	POS1 Y			|	NULL2			|	CONE ANG Y			|
	//dim[3] = f.readfloat()	// |	POS2 X			|	NULL3			|	NULL1					|
	//dim[4] = f.readfloat()	// |	POS2 Y			|	NULL4			|	CONE OPEN ANG	|
	//dim[5] = f.readfloat()	// |	POS3 X			|	NULL5			|	NULL2					|
	//dim[6] = f.readfloat()	// |	POS3 Y			|	NULL6			|	NULL3					|

	fmtATARI ();
	void clear ();
	void read_area (bytestream &f);
	void write_area (bytestream &s);
	void write_ini ();
	void read_ini (std::string &secname);
	};


#endif // FMTATARI_H
