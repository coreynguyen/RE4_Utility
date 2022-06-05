#ifndef FMTFNT_H
#define FMTFNT_H


#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>


#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "fmtTPL.h"


struct fmtFNT {
	uint32_t addrs[8];
	fmtTPL tpl;
	std::vector<uint16_t> codepage;
	void read (bytestream &f);
	void open (std::wstring file);
	void export_txt (std::wstring outpath);
	};


#endif // FMTFNT_H
