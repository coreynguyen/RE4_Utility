#ifndef FMTFIX_H
#define FMTFIX_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "filesystem.h"
#include "stringext.h"
#include "wstringext.h"

struct fmtFIX_Entry {
	uint32_t index; // sometimes the endian switches around
	uint32_t size;
	uint32_t addr;
	bytestream data;
	fmtFIX_Entry ();
	void clear ();
	void read (bytestream &f);
	void write (bytestream &s);
	};

struct fmtFIX {
	std::vector<fmtFIX_Entry> dds_info;
	void read (bytestream &f, bool storeData = true);
	void dump (std::wstring outdir, std::wstring prefix = L"");
	void import_txt (std::wstring &fnameW, std::wstring &fpathW, std::wstring &fextW);
	void export_txt (std::wstring outpath, std::wstring prefix = L"fix", std::wstring subfolder = L"images");
	void write (std::wstring outfile);
	};



#endif // FMTFIX_H
