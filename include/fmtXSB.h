#ifndef FMTXSB_H
#define FMTXSB_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"
#include "vectorext.h"
#include "filesystem.h"

struct fmtXSB_Event_Info { // 11 bytes
	uint8_t flag; // either 1 or 4 for pitch varaible controls
	uint16_t time_stamp; // Time Stamp and out the last 3 bits and divide by 1000 to get seconds
	uint8_t unk13; // always 32
	uint16_t random_time_offset; // Random Offset { Divide by 1000.0 to get seconds }
	int8_t unk13b; //  { -1 }
	uint8_t gen_flag; //  flag
	/*
		87654321  hex	field
		////////////////////////////////////////
		00000000    00	? Unused ?
		00000001    01	Loop Play Release On
		00000010    02	360 Pan Enabled
		00000100    04	360 Pan Center Speaker On
		00001000    08	360 Pan New on Loop On
		00010000    10	? Unused ?
		00100000    20	? Unused ?
		01000000    40	? Unused ?
		10000000    80	? Unused ?

		> enabling flags don't alter the current structure
	*/
	uint16_t wav_index; // sound index
	uint8_t unk13e; // 0 ?
	fmtXSB_Event_Info ();
	void read_Event_Info (bytestream &f);
	void write_Event_Info (bytestream &s);
	};

struct fmtXSB_Event_Playwave { // 5 bytes
	uint8_t loop_count; // loop count { -1 usually; if (negative then is set as infinite}
	uint16_t threesixty_pan_min; // Pan 360 Upper Limit (Angle)
	uint16_t threesixty_pan_max; // Pan 360 Lower Limit (Arc)
	fmtXSB_Event_Playwave ();
	void read_Event_Playwave (bytestream &f);
	void write_Event_Playwave (bytestream &s);
	void repr ();
	};

struct fmtXSB_Variable { // 24 bytes {shows up when eventInfo contains a 4}
	// i fucked up its not variable, its variation
	int16_t pitch_min; 					// Pitch Variable Min Range [-1200 to 1200]
	int16_t pitch_max; 					// Pitch Variable Max Range [-1200 to 1200]
	uint8_t volume_min; 				// Volume Variable Min Range; Always 0x97
	uint8_t volume_max; 				// Volume Variable Max Range; Always 0xD6
	float filter_freq_min; 				// Filter Frequency Variable Min Range; Always 1000
	float filter_freq_max; 				// Filter Frequency Variable Max Range; Always 1000
	float filter_q_min; 				// Filter Q Variable Min Range; Always 1000
	float filter_q_max; 				// Filter Q Variable Max Range; Always 1000
	uint16_t var_flag; 			// Flag
	/*
		6543210
		1111111987654321  hex	field
		////////////////////////////////////////
		0000000000000000    0000  	    ?? Unused ??
		0000000000000001    0001  	vol var operation: Add ON
		0000000000000010    0002  	    ?? Unused ??
		0000000000000100    0004  	pitch var operation: Add ON
		0000000000001000    0008  	    ?? Unused ??
		0000000000010000    0010  	Filter  freq add ON
		0000000000100000    0020  	    ?? Unused ??
		0000000001000000    0040  	Filter  q add ON
		0000000010000000    0080  	    ?? Unused ??

		0000000100000000    0100  	Pitch New on loop
		0000001000000000    0200  	Vol New On Loop
		0000010000000000    0400  	Filter Freq new on loop
		0000100000000000    0800  	Filter q new on loop

		0001000000000000    1000  	Pitch ON
		0010000000000000    2000  	Vol ON
		0100000000000000    4000  	Filter Freq ON
		1000000000000000    8000  	Filter Q ON

		> enabling flags don't alter the current structure
	*/
	fmtXSB_Variable ();
	void read_xsb_pitch (bytestream &f);
	void write_xsb_pitch (bytestream &s);
	void repr();
	};

struct fmtXSB_Event {	// 1 bytes + n
	uint8_t event_count; 			// Always 1; only ever contains either playwave or pitch event
	fmtXSB_Event_Info events; // i used an array because I assumed there could be multiple events; but i've only seen 1 event at most
	fmtXSB_Event_Playwave playwave; // should probably be an array if (more events are used
	fmtXSB_Variable variable;// should probably be an array if (more events are used
	fmtXSB_Event ();
	bool read_Event (bytestream &f);
	void write_Event (bytestream &s);
	};

struct fmtXSB_Track_Flag { // bit masked
	bool enable_filter; // always false
	bool band_pass; // always false
	bool high_pass; // always false

	//low_pass is true if (band pass or high pass are disabled
	fmtXSB_Track_Flag ();
	void set_track_flag (uint32_t val);
	uint32_t get_track_flag ();
	void repr();
	};

struct fmtXSB_Track { // 9 bytes + n
	uint8_t volume; 					// ?? range:[0x9C; 0xB4; 0xCB; 0xD9; 0xE8; 0xEF]
	uint32_t event_addr; 					// goes to a lower table
	float filter_q; 			// Always 0x5DC0 {the last 6 bits are a bit mask} {{bit.shift 24000 -3} / 1000.0}
	/*
		321   Hex	Field
	//////////////////////////////////////////////
		000    00	Low Pass
		001    01	Filter Enabled
		010    02
		100    04
	*/
	uint16_t filter_freq; 			// Always 0x03E8
	fmtXSB_Track_Flag flags;
	fmtXSB_Event event;

	fmtXSB_Track ();
	float volume_as_db ();
	bool read_Track (bytestream &f);
	void write_Track (bytestream &s);
	};

struct fmtXSB_RPC_Table {
	uint16_t extraLen;				// Always 7
	uint8_t unk04; 					// Always 1
	uint32_t unk05; 				// Always 0xD3
	fmtXSB_RPC_Table ();
	void read_RPC_Table (bytestream &f);
	void write_RPC_Table (bytestream &s);
	};

struct fmtXSB_Sound_flag { // 1 byte {only 2 flags are observed in re4; 2; 3}
	bool hasComplexSound;
	bool flag02;
	bool flag03; // always false
	bool flag04; // always false
	bool flag05; // always false
	bool flag06; // always false
	bool flag07; // always false
	bool flag08; // always false
	fmtXSB_Sound_flag ();
	void read_sound_flag (bytestream &f);
	void write_sound_flag (bytestream &s);
	void repr();
	};

struct fmtXSB_Sound {	// 9 + n + n+n +n ++ n +n +n+ n+ +n+ bytes {only 3 sizes are observed in re4; 19; 43; 67}
	/*uint8_t*/fmtXSB_Sound_flag flags;
	uint16_t category;				// Always 1; 0 = Global; 1 = Default; 2 = Music
	uint8_t volume;					// ?? Either [0 or 1200]
	uint16_t pitch;					// pitch range:[50 - 180] maybe the divide by 100
	uint8_t priority;					// index?? range [-121 to 115]
	uint16_t entryLength;			// Known sizes are {19; 43; 67}

	// below is varaible {meaning this shit ant there sometimes}
	uint8_t track_count;				// 0 or 1; based on the flags
	uint16_t trackIndex; 	// range 0 to 255
	uint8_t waveBankIndex; // Either 0 or 1
	fmtXSB_RPC_Table rpc_table1;
	fmtXSB_RPC_Table rpc_table2;
	fmtXSB_RPC_Table rpc_table3;
	std::vector<fmtXSB_Track> tracks;
	// data in between here is not clear

	fmtXSB_Sound ();
	float volume_as_db();
	bool read_Sound (bytestream &f);
	bool write_Sound (bytestream &s);
	};

struct fmtXSB_Simple_Flag { // 1 byte
	bool flag01; // always false
	bool flag02; // always false
	bool flag03; // always true
	bool flag04; // always false
	bool flag05; // always false
	bool flag06; // always false
	bool flag07; // always false
	bool flag08; // always false
	fmtXSB_Simple_Flag ();
	void read_simple_flag (bytestream &f);
	void write_simple_flag (bytestream &s);
	void repr ();
	};

struct fmtXSB_Simplecue_Table {	// 5 bytes
	/*uint8_t*/fmtXSB_Simple_Flag flags;
	uint16_t sound_offset;
	fmtXSB_Simplecue_Table ();
	void read_simplecue_table (bytestream &f);
	void write_simplecue_table (bytestream &s, std::vector<uint32_t> &sound_buffer_addrs);
	};

struct fmtXSB_Complexcue_Flag { // 1 byte {only seen flag 1; 5}
	bool flag01;
	bool flag02;
	bool flag03;
	bool flag04;
	bool flag05;
	bool flag06;
	bool flag07;
	bool flag08;
	fmtXSB_Complexcue_Flag ();
	void read_complexcue_flag (bytestream &f);
	void write_complexcue_flag (bytestream &s);
	void repr();
	};

struct fmtXSB_Instance_Limit {
	uint8_t limit;
	uint16_t fade_in; // range [0 - 65535]; divide by 1000.0 to get seconds
	uint16_t fade_out; // range [0 - 65535]; divide by 1000.0 to get seconds
	uint8_t flag;
	/*
		instance limiting flag

		when limit is reached
		000 000 fail to play
		001 000 queue
		100 000 replace

		replace instance with:
		100 000 lowest priority
		010 000 Oldest
		011 000 quiestest

		cross fade type
		100 000 linear
		100 001 logarithmic
		100 010 equal power
	*/
	fmtXSB_Instance_Limit ();
	void read_instace_limit (bytestream &f);
	void write_instace_limit (bytestream &s);
	};

struct fmtXSB_Complexcue_Table { // 15 bytes
	/*uint8_t*/fmtXSB_Complexcue_Flag flags;
	uint32_t sound_offset;
	uint32_t unk1; 	// always 0
	int32_t variation_offset;
	int32_t transition_offset; // always -1 in all my samples
	fmtXSB_Instance_Limit instances;
	fmtXSB_Complexcue_Table ();
	bool read_complexcue_table (bytestream &f);
	void write_complexcue_table (bytestream &s, std::vector<uint32_t> &sound_buffer_addrs, std::vector<uint32_t> &variation_addrs);
	};

struct fmtXSB_String_Table { // 6 bytes
	uint32_t addr;
	int16_t unk1; 	// seen mostly as NULL {-1} other wise ranges [4 - 280]
	fmtXSB_String_Table ();
	void read_String_Table (bytestream &f);
	void write_String_Table (bytestream &s);
	};

struct fmtXSB_Variation_Mix { // 6 bytes
	uint32_t sound_offset;
	uint8_t sound_unk; 	// always 0
	uint8_t sound_weight; 	// always -1
	fmtXSB_Variation_Mix ();
	void read_Variation_Mix (bytestream &f);
	void write_Variation_Mix (bytestream &s, std::vector<uint32_t> &sound_buffer_addrs);
	};

struct fmtXSB_Variation_Flags { // bitmasked; {flags: 11}
	bool isNoRepeat;
	bool isRandom;
	bool isShuffled;
	bool flag04;
	bool hasTransition;
	bool flag06;
	bool flag07;
	bool flag08;
	bool flag09;
	bool flag10;
	bool flag11;
	bool flag12;
	bool flag13;
	bool flag14;
	bool flag15;
	bool flag16;
	fmtXSB_Variation_Flags ();
	void read_variation_flag (bytestream &f);
	void write_variation_flag (bytestream &s);
	void set_variation_flag (uint32_t val);
	uint32_t get_variation_flag ();
	};

struct fmtXSB_Variation { // 8 bytes + n
	/*uint32_t*/fmtXSB_Variation_Flags flags;
	uint32_t mix_count; // always 2
	uint16_t unk1; // always -1 ?
	uint16_t unk2; // always -1 ?
	std::vector<fmtXSB_Variation_Mix> variation_mix; // always has two entries
	fmtXSB_Variation ();
	bool read_Variation (bytestream &f);
	void write_Variation (bytestream &s, std::vector<uint32_t> &sound_buffer_addrs) ;
	};

struct fmtXSB {	// 138 bytes + n
	// https://wiki.multimedia.cx/index.php/XACT
	uint32_t filetype;					// "SDBK"
	uint16_t tool_version;							// 0x2E
	uint16_t file_version;							// 0x2B
	uint16_t crc;										// fcs16 checksum of all following data after the date stamp
	uint64_t lastModified;				// 100 NanoSeconds since January 1; 1601 Windows FILETIME
	uint8_t platform;								// 1:PC; 3:XBOX
	uint16_t numSimpleCues;						// Number of Simple sound_buffer
	uint16_t numComplexCues;					// Number of Complex sound_buffer
	uint16_t unkn3;									// Always 0
	uint16_t cue_order_count;						// index buffer? used to store sorted order of names therefore must be atleast 16 ? {**Not always equal to numSimpleCues + numComplexCues}
	uint8_t wave_bank_count;					// Number of WaveBanks {Should Always be 1?}
	uint16_t sound_count;							// Number of sound_buffer
	uint32_t cue_name_buffer_size;				// Length of String Buffer
	uint32_t simpleCuesOffset;					// Simple Sound Address Table
	uint32_t complexCuesOffset;					// Complex Sound Address Table {Includes Extra Info}
	uint32_t cue_name_buffer_addr;				// Address to String Buffer
	int32_t unknOffset;							// Always -1
	uint32_t variationTablesOffset;				// ? some like random ass data
	int32_t unknOffset2;							// Always -1
	uint32_t wave_bank_table_addr;				// Address to Bank Name
	uint32_t cue_order_addr;						// sound_buffer Indices ? {Indexes the sound data to the names?}
	uint32_t cue_name_table_addr;				// Address to String Buffer Table
	uint32_t sound_buffer_addr;					// Address to Sound Buffer {Accessed by the Simple and Complex Tables}
	/*char[64]*/std::string sound_bank_name;					// Bank Name String

	// Arrays
	std::vector<std::string> wave_banks;							// Bank Name String Array {Same as Bank Name}
	std::vector<fmtXSB_Sound> sound_buffer;						// Sound Buffer **{this is read using the other tables}
	std::vector<fmtXSB_Simplecue_Table> simpleCueTable;					// Simple Sound Array
	std::vector<fmtXSB_Complexcue_Table> complexCueTable;					// Complex Sound Array
	std::vector<int16_t> cue_order_indices;					// Sound Index Array
	std::vector<fmtXSB_String_Table> cue_name_table;					// String Address Array
	std::vector<std::string> cue_name_buffer;						// String Buffer **{this is read using the other tables}
	std::vector<fmtXSB_Variation> variationTable;
	fmtXSB ();
	bool read_xsb (bytestream &f);
	size_t recalc_addresses (std::vector<uint32_t> &sound_buffer_addrs, std::vector<uint32_t> &variation_addrs);
	void write_xsb (bytestream &s);
	void write_xap (std::wstring file);
	};

#endif // FMTXSB_H
