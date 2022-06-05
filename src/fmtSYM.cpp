#include "fmtSYM.h"

fmtSYM_Entry::fmtSYM_Entry () {
	unk01 = 0;
	unk02 = 0;
	unk03 = 0;
	unk04 = 0;
	addr = 0;
	name = "";
	}

void fmtSYM_Entry::read (bytestream &f) {
	unk01 = f.readUlong();
	unk02 = f.readUlong();
	unk03 = f.readUshort();
	unk04 = f.readUshort();
	addr = f.readUlong();
	}

fmtSYM::fmtSYM () {
	count = 0;
	table_addr = 0;
	name_addr = 0;
	buffer_addr = 0;
	name_table1 = 0;
	name_table2 = 0;
	}

void fmtSYM::read (bytestream &f) {
	f.setBigEndian();
	size_t pos = f.tell();

	count = f.readUlong();
	table_addr = f.readUlong();
	name_addr = f.readUlong();
	buffer_addr = f.readUlong();
	name_table1 = f.readUlong();
	name_table2 = f.readUlong();

	if (count > 0) {

		f.seek(pos + name_addr + name_table1);
		append(names, f.readstring());

		f.seek(pos + name_addr + name_table2);
		append(names, f.readstring());


		table = std::vector<fmtSYM_Entry>(count);
		f.seek(pos + table_addr);
		for (unsigned int i = 0; i < count; i++) {
			table[i].read(f);
			}

		for (unsigned int i = 0; i < count; i++) {
			f.seek(pos + buffer_addr + table[i].addr);
			table[i].name = f.readstring();
			if (findItem(buffer, table[i].name) == -1) {
				append(buffer, table[i].name);
				}
			}
		}
	}

void fmtSYM::open (std::wstring file) {
	bytestream f;

	if (f.openFileW(file)) {
		read(f);
		f.close();
		}
	else {std::wcout << L"Error:\tFailed to load file:\t" << file << std::endl;}
	}
