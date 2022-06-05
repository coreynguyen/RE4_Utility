#ifndef FMTSYM_H
#define FMTSYM_H


#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "filesystem.h"
#include "wstringext.h"
#include "vectorext.h"

struct fmtSYM_Entry {
	uint32_t unk01;
	uint32_t unk02;
	uint16_t unk03;
	uint16_t unk04;
	uint32_t addr; // string pos
	std::string name;
	fmtSYM_Entry ();
	void read (bytestream &f);
	};

struct fmtSYM {
	uint32_t count;
	uint32_t table_addr;
	uint32_t name_addr;
	uint32_t buffer_addr;
	uint32_t name_table1;
	uint32_t name_table2;
	std::vector<fmtSYM_Entry> table;
	std::vector<std::string> names;
	std::vector<std::string> buffer;
	fmtSYM ();
	void read (bytestream &f);
	void open (std::wstring file);
	};

#endif // FMTSYM_H
