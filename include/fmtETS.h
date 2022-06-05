/*	======================================================================

	Title:		[PC] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		June 07 2020

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Modify ETS (Etc Spawn) data

	Change Log:

	[2022-05-06]
		Replaced native read function with bytestream

	[2020-06-07]
		wrote it !

	======================================================================	*/

#ifndef FMTETS_H
#define FMTETS_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "bytestream.h"
#include "stringext.h"

struct fmtETS_Entry {
	uint16_t model_id;// types? Range [0 to 105]
	uint16_t index; // ids? Range [0 to 60]
	float scale[3]; // floats? Range [-0.975741 to 20.0]
	float rotation[3]; // Range [-4.71225 to 6.289]
	float position[3]; // Range [-351000.0 to 241338.0]
	fmtETS_Entry ();
	void read_ets_entry (bytestream &f, bool re4_2007 = false);
	void write_ets_entry (bytestream &s, bool re4_2007 = false);
	size_t size (bool re4_2007 = false);
	};

struct fmtETS {
	uint16_t count; // Range [0 to 57]
	uint16_t unk01;	// Always 0
	uint32_t unk02;	// Always 0
	uint32_t unk03;	// Always 0
	uint32_t unk04;	// Always 0
	std::vector<fmtETS_Entry> data;
	fmtETS ();
	bool validate (bytestream &f, bool &re4_2007);
	void read_ets (bytestream &f);
	void write_ets (bytestream &s, bool re4_2007 = false);
	size_t size (bool re4_2007 = false);
	};


#endif // FMTETS_H
