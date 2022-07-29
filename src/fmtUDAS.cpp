#include "fmtUDAS.h"


fmtUDAS_Entry::fmtUDAS_Entry () {
	type = -1;
	size = 0;
	unk003 = 0;
	addr = 0;
	unk005 = 0;
	unk006 = -1;
	unk007 = 0;
	unk008 = 0;
	}

fmtUDAS_Entry::~fmtUDAS_Entry () {
	data.close();
	}

void fmtUDAS_Entry::read_udas_entry (bytestream &f) {
	size_t pos = f.tell();
	type = f.readlong();

	if (type != -1) {
		size = f.readUlong();
		unk003 = f.readUlong();
		addr = f.readUlong();
		unk005 = f.readUlong();
		unk006 = f.readlong();
		unk007 = f.readUlong();
		unk008 = f.readUlong();
		} else {f.seek(pos + 32);}
	}

std::string fmtUDAS_Entry::type_to_ext () {
	std::string fext = ".bin";
	switch (type) {
		case 0: {fext = ".dat"; break;}
		case 1: {fext = ".hed"; break;}
		case 2: {fext = ".dsp"; break;}
		case 4: {fext = ".das"; break;}
		}
	return fext;
	}

void fmtUDAS_Entry::repr () {
	std::cout << type << " \t" << size << " \t" << unk003 << " \t";
	std::cout << addr << " \t" << unk005 << " \t" << unk006 << " \t";
	std::cout << unk007 << " \t" << unk008 << std::endl;
	}

fmtUDAS::fmtUDAS () {
	count = 0;
	}

fmtUDAS::~fmtUDAS () {
	count = 0;
	asset.clear();
	}

bool fmtUDAS::validate_udas (bytestream &f) {
	size_t pos = f.tell();
	bool isGood = false;

	// Check that the file is not EMPTY
	if (f.size - pos > 64) {

		unsigned int chk1 = f.readUlong();

		if (chk1 != 0) {

			// Check that magic is the same for the 32 bytes
			bool chk2 = true;
			unsigned int chk3 = 0;
			for (unsigned int i = 0; i < 7; i++) {
				chk3 = f.readUlong();
				if (chk1 != chk3) {
					chk2 = false;
					break;
					}
				}

			if (chk2) {

				// set pass condition to true
				isGood = true;

				// try to detect endian
				if (chk1 == 549369546) {
					f.islilEndian = !f.islilEndian;
					}

				} else {std::cout << "validation error: \tinvalid 256bit header signature\n";}
			} else {std::cout << "validation error: \tinvalid file id\n";}
		} else {std::cout << "validation error: \tfile too small\n";}
	f.seek(pos);
	return isGood;
	}

bool fmtUDAS::read_udas (bytestream &f) {

	size_t pos = f.tell();
	bool isGood = false;
	if (validate_udas(f)) {

		f.seek(pos + 32);
		// Count Number of Entries
		unsigned int asset_count = 0;
		signed int check = 0;
		while (check != -1 && !f.eos()) {
			check = f.readlong();
			f.seek(0x1C, seek::cur);
			if (check != -1) {
				asset_count++;
				} else {break;}
			}

		if (asset_count > 0) {
			asset = std::vector<fmtUDAS_Entry>(asset_count);

			for (unsigned i = 0; i < asset_count; i++) {
				f.seek(pos + ((i + 1) * 32));
				asset[i].read_udas_entry(f);
				//asset[i].repr();
				}
			for (unsigned i = 0; i < asset_count; i++) {
				if (asset[i].size > 0) {

					asset[i].data.copy(f.stream, asset[i].size, pos + asset[i].addr);
					}
				}
			isGood = true;
			} else {std::cout << "Error: \tno entries in UDAS\n";}
		} else {std::cout << "Error:\tInvalid Udas\n";}
	return isGood;
	}

bool fmtUDAS::open_udas (std::wstring filenameW) {

	bool isGood = false;

	bytestream f;

	if (f.openFileW(filenameW)) {
		isGood = read_udas(f);
		}
	else {std::cout << "failed to read file\n";}
	return isGood;
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
		//std::cout << asset[i].size << std::endl;


		newname = filenameW + L"_" + string_to_wstring(ss.str());

		switch (asset[i].type) {
			case 0: {	// Unpack resource archive
				asset[i].data.seek(0);
				if (dat.read(asset[i].data)) {

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
