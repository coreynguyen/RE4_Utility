#ifndef FMTXWB_H
#define FMTXWB_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"
#include "filesystem.h"

#include "fmtWAV.h"

struct fmtXWB_Segment {
	uint32_t addr;
	uint32_t size;
	fmtXWB_Segment ();
	void read_fmtXWB_Segment (bytestream &f);
	};

struct fmtXWB_Audio {
	uint32_t addr;	// relative to starting address of segment 3
	uint32_t size;
	bool has_readahead;
	bool has_loopcache;
	bool has_nolooptail;
	bool has_loopskip;
	unsigned int duration; // a ten second long wave sampled at 48KHz would have a duration of 480;000.
	uint32_t loop_start; // loop start position in bits
	uint32_t loop_end; // loop end position in bits
	unsigned int type;		// 0:PCM; 1:XMA; 2:ADPCM; 3:WMA
	unsigned int channels;	// 1 to 6
	unsigned int samples_per_section;
	unsigned int alignment; // rest of bit ranges change if (type is XMA
	unsigned int bit_depth; // either 8bit or 16bit
	bytestream data;
	fmtXWB_Audio ();
	void read_fmtXWB_Audio (bytestream &f);
	void write_as_wav (bytestream &s);
	};

struct fmtXWB_Bank {
	bool has_streaming;
	bool flag02;
	bool flag03;
	bool flag04;
	bool flag05;
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
	bool has_entrynames;
	bool has_compact_fmt;
	bool has_disabled_async;
	bool has_seektables;
	bool flag21;
	bool flag22;
	bool flag23;
	bool flag24;
	bool flag25;
	bool flag26;
	bool flag27;
	bool flag28;
	bool flag29;
	bool flag30;
	bool flag31;
	bool flag32;
	fmtXWB_Bank ();
	void read_bank_flag (bytestream &f);
	void write_bank_flag (bytestream &s);
	};

struct fmtXWB {
	uint32_t fileid;	// 0x444E4257 'XBND'
	uint16_t tool_version;	// Version of the tool that the file was created on
	uint16_t file_version;
	fmtXWB_Segment segments[5]; // table of offests and sizes of each data chunk
	fmtXWB_Bank bank_info;
	uint32_t audio_count;
	/*char[64]*/std::string bank_name;	// limited to 63 characters; 64th is reserved for a null
	uint32_t meta_size;
	uint32_t name_size;
	uint32_t alignment; // need to look into how this is calculated; doc says must be 4 or 2048 for DVD quality?
	uint32_t compact_fmt;
	uint64_t build_time;
	uint32_t bank_addr;
	uint32_t bank_size;
	std::vector<fmtXWB_Audio> bank;
	fmtXWB ();
	void read_xwb (bytestream &f);
	void dump_xwb (std::wstring fpath, std::wstring wav_name = L"");
	};


#endif // FMTXWB_H
