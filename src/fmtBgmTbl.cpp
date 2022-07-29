#include "fmtBgmTbl.h"


fmtBgmTbl_Table1_Entry::fmtBgmTbl_Table1_Entry () {
	unk01 = 0;
	unk02 = 0;
	unk03 = 0;
	unk04 = 0;
	unk05 = 0;
	unk06 = 0;
	unk07 = 0;
	unk08 = 0;
	unk09 = 0;
	unk10 = 0;
	unk11 = 0;
	unk12 = 0;
	unk13 = 0;
	}

void fmtBgmTbl_Table1_Entry::read_bgmtbl_table1_entry (bytestream &f) {
	unk01 = f.readUlong();
	unk02 = f.readUlong();
	unk03 = f.readUlong();
	unk04 = f.readUlong();
	unk05 = f.readUlong();
	unk06 = f.readUlong();
	unk07 = f.readUlong();
	unk08 = f.readUlong();
	unk09 = f.readUlong();
	unk10 = f.readUlong();
	unk11 = f.readUlong();
	unk12 = f.readUlong();
	unk13 = f.readUlong();
	}

void fmtBgmTbl_Table1_Entry::write_bgmtbl_table1_entry (bytestream &s) {
	s.writeUlong(unk01);
	s.writeUlong(unk02);
	s.writeUlong(unk03);
	s.writeUlong(unk04);
	s.writeUlong(unk05);
	s.writeUlong(unk06);
	s.writeUlong(unk07);
	s.writeUlong(unk08);
	s.writeUlong(unk09);
	s.writeUlong(unk10);
	s.writeUlong(unk11);
	s.writeUlong(unk12);
	s.writeUlong(unk13);
	}

fmtBgmTbl_Table1::fmtBgmTbl_Table1 () {
	count = 0;
	}

size_t fmtBgmTbl_Table1::size () {
	count = item.size();
	return (4 + (count * 52));
	}

void fmtBgmTbl_Table1::read_bgmtbl_table1 (bytestream &f) {
	count = f.readUlong();
	item.clear();
	if (count > 0) {
		item = std::vector<fmtBgmTbl_Table1_Entry>(count);
		for (unsigned int i = 0; i < count; i++) {
			item[i].read_bgmtbl_table1_entry(f);
			}
		}
	}

void fmtBgmTbl_Table1::write_bgmtbl_table1 (bytestream &s) {
	count = item.size();
	s.writeUlong(count);
	for (unsigned int i = 0; i < count; i++) {
		item[i].write_bgmtbl_table1_entry(s);
		}
	}

fmtBgmTbl_Table2::fmtBgmTbl_Table2 () {
	index1 = -1;
	index2 = -1;
	}

void fmtBgmTbl_Table2::read_bgmtbl_table2 (bytestream &f) {
	index1 = f.readbyte();
	index2 = f.readbyte();
	}

void fmtBgmTbl_Table2::write_bgmtbl_table2 (bytestream &s) {
	s.writebyte(index1);
	s.writebyte(index2);
	}

fmtBgmTbl::fmtBgmTbl () {
	block1_addr = 32;
	block2_addr = 0;
	}

size_t fmtBgmTbl::size () {
	unsigned int table1_count = table1.size();
	size_t nsize = 32 + (table1_count * 4);

	for (unsigned int i = 0; i < table1_count; i++) {
		nsize += table1[i].size();
		}
	nsize += (32-(nsize % 32)) % 32;
	unsigned int table2_count = table2.size();
	nsize += (table2_count + 1) * 2;
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

void fmtBgmTbl::read_bgmtbl (bytestream &f) {
	block1_addr = f.readUlong();
	block2_addr = f.readUlong();
	table1_addrs.clear();
	if (block1_addr > 0) {

		f.seek(block1_addr);
		unsigned int block1_end = f.size;
		size_t addr = 0;

		while (f.tell() < block1_end) {

			addr = f.readUlong();

			if (addr + 32 < block1_end) {
				block1_end = addr + 32;
				}
			table1_addrs.push_back(addr);
			}
		}

	table1.clear();
	unsigned int table1_count = table1_addrs.size();
	if (table1_count > 0) {
		table1 = std::vector<fmtBgmTbl_Table1>(table1_count);

		for (unsigned int i = 0; i < table1_count;  i++) {
			f.seek(32 + table1_addrs[i]);
			table1[i].read_bgmtbl_table1(f);
			}
		}

	table2.clear();
	if (block2_addr > 0) {
		fmtBgmTbl_Table2 idx;
		f.seek(block2_addr);
		while (f.tell() < f.size) {
			fmtBgmTbl_Table2 idx;
			idx.read_bgmtbl_table2(f);
			if (idx.index1 != -1 && idx.index2 != -1) {
				table2.push_back(idx);
				}
			else {
				break;
				}
			}
		}
	}

void fmtBgmTbl::write_bgmtbl (bytestream &s) {
	s.writeUlong(32);
	unsigned int table1_count = table1.size();
	size_t nsize = table1_count * 4;

	for (unsigned int i = 0; i < table1_count; i++) {
		nsize += table1[i].size();
		}
	nsize += (32-(nsize % 32)) % 32;
	s.writeUlong(nsize + 32);
	for (unsigned int i = 0; i < 24; i++) { // padding
		s.writebyte(0);
		}
	nsize = table1_count * 4;
	for (unsigned int i = 0; i < table1_count; i++) {
		s.writeUlong(nsize);
		nsize += table1[i].size();
		}
	for (unsigned int i = 0; i < table1_count; i++) {
		table1[i].write_bgmtbl_table1(s);
		}
	unsigned int pad = (32-(nsize % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {
		s.writebyte(0);
		}
	unsigned int table2_count = table2.size();
	for (unsigned int i = 0; i < table2_count; i++) {
		table2[i].write_bgmtbl_table2(s);
		}
	s.writeshort(-1);
	nsize += pad + (table2_count + 1) * 2;
	pad = (32-(nsize % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {
		s.writebyte(0);
		}
	}


