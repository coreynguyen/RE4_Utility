/*	======================================================================

	Maxscript:    [PC] Resident Evil 4
	Author:        mariokart64n
	Date:           January 29, 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Reads roominfo, which contains spawn points for each room.
		such as;
			- Room ID
			- Room Name
			- Leon's Spawn Position

	Change Log:
		2022-01-29
			- Write IT!
			- data from the roominfo has be embedded into the structs,
			   so I don't need to read the file again

	======================================================================	*/
#ifndef FMTROOM_H
#define FMTROOM_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "bytestream.h"

struct fmtROOMINFO_Waypoint { // 32 bytes
	uint16_t flag; // flag?
	uint16_t room; // room id
	float pos[3];
	float angle; // rotation z only
	uint32_t name_addr; // string offset, room name
	uint32_t artist_addr; // string offset, room artist
	uint32_t coder_addr; // string offset, room coder
	std::string name;
	std::string artist;
	std::string coder;
	fmtROOMINFO_Waypoint (uint16_t r = 0, float x = 0.0f, float y = 0.0f, float  = 0.0f, float t = 0.0f, std::string n = "", std::string a = "", std::string c = "");
	void read (bytestream &f);
	void write (bytestream &s);
	};

struct fmtROOMINFO_Room {
	uint32_t waypoint_count;
	std::vector<fmtROOMINFO_Waypoint> waypoint;
	fmtROOMINFO_Room ();
	void read (bytestream &f);
	void write (bytestream &s);
	size_t size ();
	};

struct fmtROOMINFO { // roominfo.gc
	uint32_t count;
	std::vector<uint32_t> addrs;
	std::vector<fmtROOMINFO_Room> room;
	fmtROOMINFO ();
	void read (std::wstring fileW);
	size_t recalc_addrs ();
	size_t size ();
	void write (std::wstring fileW);
	};

#endif // FMTROOM_H
