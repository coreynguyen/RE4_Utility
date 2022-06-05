/*	======================================================================

	Maxscript:    [PC] Resident Evil 4
	Author:        mariokart64n
	Date:           August 28 2021

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Editing of the FCV files

	Change Log:
		2022-05-16
			- switched native read functions over to bytestream

		2022-01-16
			- Re-arranged the UI
			- Right-Click Context added for Tracks and Keyframes to
			   reduce the size of the UI.
			- Duplicated the function that creates a new FCV from the
			   scene. Right-Click uses the old function, Copy Keys button
			   uses the new function.. new function detections keyframe
			   X Y Z changes to reduce written frames
			- changed the data type support from 0x00 to 0x15 and 0x50
			   which should provided slightly smaller FCV outputs
			- Add / Delete functions completed, and + / - buttons are now
			   enabled
			- Added Function to read the skeleton from a BIN mesh and
			  Import the skeleton
			- Function that reads animation from the scene updated to work
			   with the imported BIN mesh skeleton. Essentially axis
			   swapping is removed from the function as the skeleton importer
			   doesn't swap.
			- Added function to copy transforms and paste them, encase
			  I need it for copying an animation
			- importing and exporting FCV to the Bin Mesh skeleton
			   tweaked to work togetehr now

		2022-01-14
			- Added function to automatically apply rotaiton constraints
			   to leon's model and the ganado from Unreal Engine
			- Add function that creates a new FCV by reading the animations
			   of a skeleton in the scene. Relies on Son of Persia's
			   SMD Skeleton which use a specific naming system
			- Added a function that builds a copy of leon's skeleton
			   from pl00

		2021-08-28
			- Wrote IT!

	TODO:
	 check known types, skip track if type is not supported
	 make function to construct points in animation

	 add a string block
		file expansion
		names

		Filename, if none, adopts the name of the filename
		bone names
		track names

		at the end of the pointers table add a 4cc
		like
		ESTR or STRE

		then follow by version, size, count1, count2
		animation name
		notes
		then string table1 bone names
		string table 2 track names

		enrty
		index to element as short
		lenghth of string as byte


	======================================================================	*/
#ifndef FMTFCV_H
#define FMTFCV_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "vectorext.h"

struct fmtFCV_Value {
	uint16_t num_keys;
	std::vector<uint16_t> keys;
	std::vector<std::vector<float>> values;
	/*
		data types are dynamic, to make it easier
		I just convert them all to floats.
	*/
	fmtFCV_Value ();
	size_t block_size (uint16_t &data_type);
	void read (bytestream &f, uint16_t &data_type);
	void write (bytestream &s, uint16_t &data_type);
	};

struct fmtFCV_Track {
	unsigned int index; // not apart of the format spec; i just store the block order here
	fmtFCV_Value x;
	fmtFCV_Value y;
	fmtFCV_Value z;
	fmtFCV_Track ();
	void read (bytestream &f, uint16_t &data_type);
	size_t block_size (uint16_t &data_type);
	void write (bytestream &s, uint16_t &data_type);
	};

struct fmtFCV {
	uint16_t num_frames;
	uint8_t num_tracks;
	std::vector<uint16_t> config;
	std::vector<uint8_t> nodes; // buffer is padded to an alignment of 4
	uint32_t filesize; // excluding padding at the end of the file
	/*
		Endian is swapped in UHD
		NGC: Big    Endian
		2K7: Little Endian
		UHD: Big    Endian
	*/
	std::vector<uint32_t> addrs; // address to each track {address is absolute; from the start of file}
	std::vector<fmtFCV_Track> tracks;
	// file is padded to byte alignment of 32; pad character is 0xCD
	fmtFCV ();
	bool validate (bytestream &f, bool verbose = false);
	void recalc_addrs ();
	size_t size ();
	std::vector<uint32_t> calcBlockEnds (size_t &fsize, std::vector<uint32_t> &addrs);
	void read (bytestream &f);
	void write (bytestream &s, bool swap_filesize = false);
	void open (std::wstring file);
	void save (std::wstring file);
	};



#endif // FMTFCV_H
