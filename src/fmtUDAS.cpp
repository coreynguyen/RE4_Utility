#include "fmtUDAS.h"


fmtUDAS_Entry::fmtUDAS_Entry () {
	type = 0x20BEB6CA;
	size = 0x20BEB6CA;
	unk003 = 0x20BEB6CA;
	addr = 0x20BEB6CA;
	unk005 = 0x20BEB6CA;
	unk006 = 0x20BEB6CA;
	unk007 = 0x20BEB6CA;
	unk008 = 0x20BEB6CA;
	}

fmtUDAS_Entry::~fmtUDAS_Entry () {
	data.close();
	}

void fmtUDAS_Entry::read_udas_entry (bytestream &f) {
	type = f.readUlong();
	size = f.readUlong();
	unk003 = f.readUlong();
	addr = f.readUlong();
	unk005 = f.readUlong();
	unk006 = f.readUlong();
	unk007 = f.readUlong();
	unk008 = f.readUlong();
	}

fmtUDAS::fmtUDAS () {
	count = 0;
	entry = NULL;
	}

fmtUDAS::~fmtUDAS () {
	if (entry != NULL) {delete[] entry;}
	count = 0;
	entry = NULL;
	}

bool fmtUDAS::read_udas (std::wstring filenameW) {


	bytestream f;

	if (f.openFileW(filenameW)) {

		// check that file is larger then minimal size
		if (f.size < 32) {return false;}

		// start read at beginning of file
		f.pos = 0;

		// check type
		magic = f.readlong();

		// reading the magic isn't reliable, try to read the first address
		f.pos = 44;
		if (f.readlong() >= 0x00040000) {
			f.islilEndian = !f.islilEndian;
			}

		//if (magic != 0xCAB6BE20 && magic != 0x20BEB6CA) {return false;}

		// clear entry buffer
		count = 0;
		if (entry != NULL) {delete[] entry;}
		entry = NULL;

		// go to file table
		f.pos = 32;

		// count entries
		uint32_t term = 0x7FFFFFFF;
		uint32_t type;
		while (f.pos < f.size ) {

			// read type
			type = f.readUlong();

			// check if termination is found
			if (type > term) {
				break;
				}

			// skip to next entry
			f.pos += 28;

			// increment
			count++;
			}

		// check if any thing was countered
		if (count == 0) {return false;}

		// dimension array
		entry = new fmtUDAS_Entry[count];

		// create size lookup
		unsigned long* sizes = new unsigned long[count + 1];
		sizes[count] = f.size;

		// seek to table again
		f.pos = 32;

		// read entries
		for (unsigned long i = 0; i < count; i++) {

			// read udas entry
			entry[i].read_udas_entry(f);

			// log addr
			sizes[i] = entry[i].addr;

			//if (entry[i].addr > f.size) {
			//	isLilEndian = false;
			//	}
			}

		// halt if endian difference
		//if (!isLilEndian) {
		//	delete[] sizes;
		//	return false;
		//	}

		// sort sizes
		std::sort(sizes, sizes + (count + 1));

		// rebuild sizes
		for (unsigned long i = 0; i < count; i++) {
			//std::cout << "Size" << i << ":\t" << sizes[i] << std::endl;
			if (entry[i].size == 0) {
				for (unsigned long x = count; x --> 0; ) {
					if (entry[i].addr == sizes[x]) {
						entry[i].size = sizes[x + 1] - entry[i].addr;
						}
					}
				}
			}
		delete[] sizes;

		for (unsigned long i = 0; i < count; i++) {
			entry[i].data.copy(f.stream, entry[i].size, entry[i].addr);
			}



		}
	else {std::cout << "failed to read file\n";}
	return true;
	}

void fmtUDAS::unpack_udas (std::wstring fpathW, std::wstring filenameW) {

	// create path
	win::makeDirW(fpathW + filenameW);

	// Create text file
	ini->clear();
	ini->header("Data Assets", "DATASSET_PATH", "Set path to das data, paths may be relative or absolute");
	ini->newline();
	ini->wstring("das_path", filenameW);
	ini->log(fpathW + filenameW + L"\\das.txt");
	std::wcout << filenameW << L"\\das.txt" << std::endl;

	// take a dump
	fmtDAT dat;
	int digits2 = 0;
	std::wstring dat_name;
	std::wstring newname;
	std::ostringstream ss;
	ss.str("");
	ss << (count - 1);
	int digits = ss.str().size();
	ss.str(""); ss.clear();

	for (unsigned long i = 0; i < count; i++) {

		// and.. still assembling the filename
		ss.str(""); ss.clear();
		ss << std::right << std::setfill('0') << std::setw(digits) << i;
		//std::cout << entry[i].size << std::endl;


		newname = filenameW + L"_" + string_to_wstring(ss.str());

		switch (entry[i].type) {
			case 0: {	// Unpack resource archive
				entry[i].data.seek(0);
				if (dat.read(entry[i].data)) {

					// check count
					if (dat.count > 0) {

						// create subfolder
						win::makeDirW(fpathW + filenameW + L"\\" + newname);

						ss.str(""); ss.clear();
						ss << (dat.count - 1);
						digits2 = ss.str().size();
						for (unsigned long x = 0; x < dat.count; x++) {
							ss.str("");
							ss.clear();
							ss << std::right << std::setfill('0') << std::setw(digits2) << x;
							dat_name = string_to_wstring(ss.str()) + L"." + toLowerW(string_to_wstring(dat.type[x]));

							dat.data[x].writeFileW(
								fpathW + filenameW + L"\\" +
								newname + L"\\" +
								newname + L"_" + dat_name
								);
							}
						}
					}
				else {
					dat.data[i].writeFileW(fpathW + filenameW + L"\\" + newname + L".dat");
					}
				break;
				}
			case 1: {
				dat.data[i].writeFileW(fpathW + filenameW + L"\\" + newname + L".hed");
				break;
				}
			case 2: {
				dat.data[i].writeFileW(fpathW + filenameW + L"\\" + newname + L".snd");
				break;
				}
			case 4: {	// GC DAS (what son of persia calls a SND)
				dat.data[i].writeFileW(fpathW + filenameW + L"\\" + newname + L".das");
				break;
				}
			default: {
				dat.data[i].writeFileW(fpathW + filenameW + L"\\" + newname + L".bin");
				}
			}
		}
	}
