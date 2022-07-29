#ifndef FMTBGMTBL_H
#define FMTBGMTBL_H


#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"
#include "filesystem.h"

struct fmtBgmTbl_Table1_Entry { // 52 Bytes
	uint32_t unk01;
	uint32_t unk02;
	uint32_t unk03;
	uint32_t unk04;
	uint32_t unk05;
	uint32_t unk06;
	uint32_t unk07;
	uint32_t unk08;
	uint32_t unk09;
	uint32_t unk10;
	uint32_t unk11;
	uint32_t unk12;
	uint32_t unk13;
	fmtBgmTbl_Table1_Entry ();
	void read_bgmtbl_table1_entry (bytestream &f);
	void write_bgmtbl_table1_entry (bytestream &s);
	};

struct fmtBgmTbl_Table1 { // 4 + {52 * n} Bytes
	uint32_t count;
	std::vector<fmtBgmTbl_Table1_Entry> item;
	fmtBgmTbl_Table1 ();
	size_t size ();
	void read_bgmtbl_table1 (bytestream &f);
	void write_bgmtbl_table1 (bytestream &s);
	};

struct fmtBgmTbl_Table2 { // 2 Bytes
	int8_t index1;
	int8_t index2;
	fmtBgmTbl_Table2 ();
	void read_bgmtbl_table2 (bytestream &f);
	void write_bgmtbl_table2 (bytestream &s);
	};

struct fmtBgmTbl {
	/*
		structure is specific to 'bgmtbl.dat'
	*/
	uint32_t block1_addr;
	std::vector<uint32_t> table1_addrs;
	std::vector<fmtBgmTbl_Table1> table1;
	uint32_t block2_addr;
	std::vector<fmtBgmTbl_Table2> table2;
	fmtBgmTbl ();
	size_t size ();
	void read_bgmtbl (bytestream &f);
	void write_bgmtbl (bytestream &s);
	};



#endif // FMTBGMTBL_H
