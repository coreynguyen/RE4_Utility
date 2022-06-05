#ifndef FMTSEQ_H
#define FMTSEQ_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "filesystem.h"
#include "wstringext.h"

struct fmtSEQ_Entry { // 4 Bytes
	uint16_t time; // ? animation timing
	uint8_t index; // seen as either 0, 1, 2 ? se index
	uint8_t flag; // always 0? flag
	fmtSEQ_Entry ();
	size_t size ();
	void read (bytestream &f, bool re4_2007 = false);
	void write (bytestream &s, bool re4_2007 = false);
	void repr ();
	void write_ini (std::wstring outfile, std::string secname);
	void read_ini (std::string &secname);
	};

struct fmtSEQ { // 4 Bytes + n Bytes
	uint16_t count;
	uint16_t unk0; // ?? always 0
	std::vector<fmtSEQ_Entry> data;
	// File is Padded to a alignment of 32 using 0xCD
	fmtSEQ ();
	size_t size ();
	bool validate (bytestream &f, bool &re4_2007, bool verbose = true);
	void read (bytestream &f);
	void write (bytestream &s, bool re4_2007 = false);
	void repr ();
	void export_txt (std::wstring outpath, std::string subfolder, std::string prefix = "seq");
	void import_txt (std::wstring txt_path, std::string secname);
	};


#endif // FMTSEQ_H
