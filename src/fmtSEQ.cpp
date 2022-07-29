#include "fmtSEQ.h"


fmtSEQ_Entry::fmtSEQ_Entry () {
	time = 0;
	index = 0;
	flag = 0;
	}

size_t fmtSEQ_Entry::size () {
	return 4;
	}

void fmtSEQ_Entry::read (bytestream &f, bool re4_2007) {
	if (!re4_2007) {
		time = f.readUshort();
		index = f.readUbyte();
		flag = f.readUbyte();
		}
	else {
		index = f.readUbyte();
		flag = f.readUbyte();
		time = f.readUshort();
		}
	}

void fmtSEQ_Entry::write (bytestream &s, bool re4_2007) {
	if (!re4_2007) {
		s.writeshort(time);
		s.writebyte(index);
		s.writebyte(flag);
		}
	else {
		s.writebyte(index);
		s.writebyte(flag);
		s.writeshort(time);
		}
	}

void fmtSEQ_Entry::repr () {
	std::cout << time / 64.0 << "\t" << index << "\t" << flag << "\n";
	}

void fmtSEQ_Entry::write_ini (std::wstring outfile, std::string secname) {
	ini->clear();
	ini->header("Sequences", secname);

	ini->integer("time", time);
	ini->integer("index", index);
	ini->integer("flag", flag);

	// write text file
	ini->log(outfile);
	}

void fmtSEQ_Entry::read_ini (std::string &secname) {
	time = (uint16_t)ini->get_integer(secname, "time");
	index = (uint8_t)ini->get_integer(secname, "index");
	flag = (uint8_t)ini->get_integer(secname, "flag");
	}

fmtSEQ::fmtSEQ () {
	count = 0;
	unk0 = 0;
	}

size_t fmtSEQ::size () {
	size_t nsize = ((data.size() + 1) * 4);
	nsize += (32-(nsize % 32)) % 32;
	return nsize;
	}

bool fmtSEQ::validate (bytestream &f, bool &re4_2007, bool verbose) {

	// default state of re4 2007
	re4_2007 = false;

	// get start position
	size_t pos = f.tell();

	// set fail state
	bool isGood = false;

	// check the file is large enough
	if (pos + 8 <= f.size) {

		unsigned int chk1 = f.readUshort();

		// check count is not zero
		if (chk1 != 0) {

			// get byte swapped number
			unsigned int chk2 = bit::swapBytes(chk1, 1, 2);

			// check if swapped number is smaller or larger
			if (chk1 > chk2) {

				// swap endian
				f.islilEndian = !f.islilEndian;

				// update count
				f.seek(pos);
				chk1 = f.readUshort();
				}

			// check count doesn't overflow
			if ((chk1 + 1) * 4 <= f.size) {

				// count number of times the left is greater then the right

				unsigned int chk3;
				unsigned int chk4;
				unsigned int chk5;
				unsigned int chk6;
				unsigned int chk7 = 0;
				f.seek(4);
				for (unsigned int i = 0; i < chk1; i++) {

					chk3 = f.readUbyte();
					chk4 = f.readUbyte();
					chk5 = f.readUbyte();
					chk6 = f.readUbyte();

					if (chk3 + chk4 > chk5 + chk6) {
						chk7++;
						}
					}

				// create a ratio
				float chk8 = (float)chk7 / (float)chk1;

				// guess if the file is re4 2007

				if (f.islilEndian && chk8 < 0.2f) {
					re4_2007 = true;
					}


				// set pass state
				isGood = true;

				} else {if (verbose) {std::cout << "SEQ Validation Failure:\n\tentries out of bounds\n";}}
			} else {if (verbose) {std::cout << "SEQ Validation Failure:\n\tFile is Empty?\n";}}
		} else {if (verbose) {std::cout << "SEQ Validation Failure:\n\tInvalid File Size\n";}}
	f.seek(pos);
	return isGood;
	}

void fmtSEQ::read (bytestream &f) {
	bool re4_2007 = false;
	if (validate(f, re4_2007)) {
		count = f.readUshort();
		unk0 = f.readUshort();
		data.clear();
		if (count > 0) {
			data = std::vector<fmtSEQ_Entry>(count);
			for (unsigned int i = 0; i < count; i++) {
				data[i].read(f, re4_2007);
				}
			}
		} else {std::wcout << L"Error:\n\tSEQ Validation Failed: \t" << f.fileW << std::endl;}
	}

void fmtSEQ::write (bytestream &s, bool re4_2007) {
	//size_t pos = s.tell();

	s.writeshort(count = data.size());
	s.writeshort(unk0);

	for (unsigned int i = 0; i < count; i++) {
		data[i].write(s, re4_2007);
		}

	size_t p = (32-(s.tell() % 32)) % 32;
	for (unsigned int i = 0; i < p; i++) {
		s.writebyte(0xCD);
		}
	}

void fmtSEQ::repr () {
	for (unsigned int i = 0; i < data.size(); i++) {
		data[i].repr();
		}
	}

void fmtSEQ::export_txt (std::wstring outpath, std::string subfolder, std::string prefix) {

	if (count > 0) {

		if (!win::doesFolderExistW(outpath)) {
			win::makeDirW(outpath);
			}

		std::wstring seq_path = outpath + string_to_wstring(subfolder) + L"\\";
		if (!win::doesFolderExistW(seq_path)) {
			win::makeDirW(seq_path);
			}

		// Create text file
		ini->clear();
		ini->header("Sequence Config", "SEQUENCE_PATH", "Set path to seq data, paths may be relative or absolute");
		ini->newline();
		ini->wstring("seq_path", string_to_wstring(subfolder));
		ini->log(outpath + string_to_wstring(prefix) + L".txt");


		// write files
		seq_path += string_to_wstring(prefix) + L"_" ;
		for (unsigned int i = 0; i < count; i++) {
			data.at(i).write_ini(
				seq_path + \
				string_to_wstring(padString(to_string(i), 3, "0")) + L"_" + \
				string_to_wstring(padString(to_string((int)data.at(i).index), 2, "0")) + L".txt",
				"SEQUENCE"
				);
			}

		}

	}

void fmtSEQ::import_txt (std::wstring txt_path, std::string secname) {

	// Open ini
	ini->open(txt_path);

	// get path to data
	std::wstring subfolder = ini->get_wstring(secname, "seq_path");

	if (subfolder.length() == 0) {
		// not path, exit?
		return;
		}


	// get files from path
	std::vector<std::wstring> files;
	getFilesW(subfolder + L"*.txt", files);

	// check that files were collected
	if (files.size()) {


		// Create Empty Entry
		fmtSEQ_Entry entry;

		// loop through entries
		for (unsigned int i = 0; i < files.size(); i++) {

			// Open Ini
			ini->open(files.at(i));

			// Look for Section
			if (ini->find_section(secname)) {

				// init entry
				fmtSEQ_Entry entry;

				// read ini
				entry.read_ini(secname);

				// append to array
				data.push_back(entry);
				}
			}
		}
	}
