/*	======================================================================

	Title:		[PC-Steam] Resident Evil 4
	Author:		mariokart64n
	Version:	0.1
	Date:		April 19 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		re4 file utility

	======================================================================	*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "FL\Fl.H"

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"
#include "wstringext.h"
#include "filesystem.h"
#include "fmtATARI.h"	// Atari (aka Area)
#include "fmtEST.h" 	// Effects Sprite
#include "fmtEFF.h" 	// Effects Animation
#include "fmtITA.h" 	// Item Area
#include "fmtFCV.h" 	// Frame Curve Values?
#include "fmtETS.h"
#include "fmtSEQ.h" 	// Sequences
#include "fmtDAT.h" 	// Data Package
#include "fmtFIX.h" 	// Chinese Language Fix
//#include "fmtFBX.h" 	// Film Box Scene Save
#include "fmtFNT.h" 	// Font
#include "fmtUDAS.h" 	// Data Asset Package
#include "fmtPACK.h" 	// Texture Package
#include "fmtAEV.h" 	// Area Events
#include "fmtSND.h"		// Sound
#include "fmtXSB.h"

#include "wregistry.h"
#include "stringenc.h"
#include "vectorext.h"

#include "resource.h"
#include "version.h"


//#include "FL\Fl.H"
//#include "win_esl.h"


using namespace std;
/*
// blocks 1 to 5
void write_table (bytestream &f, uint32_t addr, bool write_int2, std::wstring sfile) {
	if (addr < 32) {return;}

	f.seek(addr);
	uint32_t block01_count = f.readUlong();

	if (block01_count == 0) {return;}

	uint16_t block01_entry1;
	uint16_t block01_entry2;
	//uint16_t block01_entry3;
	//uint16_t block01_entry4;

	std::string table_0 = "EntryCount = " + to_string(block01_count) + "\n";
	std::stringstream sstr;



	char *cstr = NULL;

	for (uint32_t i = 0; i < block01_count; i++) {


		block01_entry1 = f.readUshort();
		block01_entry2 = f.readUshort();
		f.readUshort();//block01_entry3 = f.readUshort();
		f.readUshort();//block01_entry4 = f.readUshort();





		if (!write_int2) {


			sstr.str(std::string());
			//sstr << TO_HEX(block01_entry1, true, 4);
			sstr << "0x" << std::uppercase << std::hex << block01_entry1;
			table_0 += "Entry_" + to_string(i) + " = " + sstr.str() + "\n";

			}
		else {
			sstr.str(std::string());
			//sstr << TO_HEX(block01_entry1, true, 4);
			sstr << "0x" << std::uppercase << std::hex << block01_entry1;
			table_0 += "\nEntry_" + to_string(i) + "_index = " + sstr.str() + "\n";


			sstr.str(std::string());
			//sstr << TO_HEX(block01_entry2, true, 4);
			sstr << "0x" << std::uppercase << std::hex << block01_entry2;
			table_0 += "Entry_" + to_string(i) + "_unknown = " + sstr.str() + "\n";
			}
		}



	cstr = new char[table_0.length() + 1];
	strcpy(cstr, table_0.c_str());
	f.writeFileW(sfile, 0, table_0.length(), cstr);
	delete[] cstr;

	}

void write_tex_table (bytestream &f, uint32_t addr, std::wstring sfile) {
	if (addr < 32) {return;}

	f.seek(addr);
	uint32_t block01_count = f.readUlong();

	if (block01_count == 0) {return;}
	uint32_t ptr;
	uint16_t Height;
	uint16_t Width;
	uint16_t EffectHeight;
	uint16_t EffectWidth;
	uint16_t EffectTextureCount;
	uint8_t Offset_10;
	uint8_t Offset_11;

	std::string table_0 = "TextureCount = " + to_string(block01_count);

	for (uint32_t i = 0; i < block01_count; i++) {
		f.seek(addr + ((i + 1) * 4));
		ptr = f.readUlong();
		f.seek(addr + ptr);

		Height = f.readUshort();
		Width = f.readUshort();
		EffectHeight = f.readUshort();
		EffectWidth = f.readUshort();
		EffectTextureCount = f.readUshort();
		Offset_10 = f.readUbyte();
		Offset_11 = f.readUbyte();
		f.readUlong();
		f.readUlong();
		f.readUlong();
		f.readUlong();
		f.readUlong();

		table_0 += "\n\n# Texture " + to_string(i) + " Data\n";

		table_0 += "\nHeight = " + to_string(Height);
		table_0 += "\nWidth = " + to_string(Width);
		table_0 += "\nEffectHeight = " + to_string(EffectHeight);
		table_0 += "\nEffectWidth = " + to_string(EffectWidth);
		table_0 += "\nEffectTextureCount = " + to_string(EffectTextureCount);
		table_0 += "\nOffset[10] = " + to_string((int)Offset_10);
		table_0 += "\nOffset[11] = " + to_string((int)Offset_11);

		}


	char *cstr = new char[table_0.length() + 1];
	strcpy(cstr, table_0.c_str());
	f.writeFileW(sfile, 0, table_0.length(), cstr);
	delete[] cstr;

	}

// block 7
uint32_t get_block_size (std::vector<uint32_t> sizes, uint32_t addr) {


	uint32_t file_size = 0;

	if (addr > 0) {

		// Search if Value is in array
		std::vector<uint32_t>::iterator itr = std::find(sizes.begin(), sizes.end(), addr);

		// Check if index is valid
		if (itr != sizes.cend()) {

			// generate size
			file_size = sizes[std::distance(sizes.begin(), itr) + 1] - addr;

			}
		}
	return file_size;
	}
void write_tpls (bytestream &f, uint32_t addr, uint32_t end_addr, std::wstring spath) {


	if (addr < 32) {return;}

	f.seek(addr);
	uint32_t count = f.readUlong();

	if (count == 0) {return;}


	std::vector<uint32_t> sizes;
	std::vector<uint32_t> addrs(count);
	for (uint32_t i = 0; i < count; i++) {
		f.seek(addr + ((i + 1) * 4));
		addrs.at(i) = f.readUlong();
		// Only Include if not NULL
		if (addrs.at(i) > 0) {

			// Search if value is already in Array
			if (std::find(sizes.begin(), sizes.end(), addrs.at(i)) == sizes.end()) {

				// Value is Unique, Add to the Array
				sizes.push_back(addrs.at(i));
				}
			}
		}

	// Append File Size
	sizes.push_back(end_addr);

	// Sort sizes
	std::sort(sizes.begin(), sizes.end());

	for (uint32_t i = 0; i < count; i++) {
		f.seek();

		f.writeFileW(spath + L"\\" + string_to_wstring(to_string(i)) + L".tpl", addr + addrs.at(i), get_block_size(sizes, addrs.at(i)));
		}


	}


void unpack_eff (std::wstring filenameW) {

	// open file
	bytestream f;
	if (!f.openFileW(filenameW))
		{std::cout << "failed to open file\n";
		return;
		}


	// read count
	uint32_t count = f.readUlong();
	if (count != 11) {
		std::cout << "Error: \tfile count was unexpected\n";
		return;
		}

	// read pointer table
	std::vector<uint32_t> addrs(count);
	for (uint32_t i = 0; i < count; i++) {
		addrs.at(i) = f.readUlong();
		}


	// Collect Unique Addresses
	std::vector<uint32_t> sizes;
	for (uint32_t i = 0; i < count; i++) {

		// Only Include if not NULL
		if (addrs[i] > 0) {

			// Search if value is already in Array
			if (std::find(sizes.begin(), sizes.end(), addrs[i]) == sizes.end()) {

				// Value is Unique, Add to the Array
				sizes.push_back(addrs[i]);
				}
			}
		}

	// Append File Size
	sizes.push_back(f.size);

	// Sort sizes
	std::sort(sizes.begin(), sizes.end());


	// Create Sub Folder
	std::wstring eff_folder = f.fpathW + f.fnameW;
	std::wstring eff_folder_tables = f.fpathW + f.fnameW + L"\\Tables";
	std::wstring eff_folder_effect_tpl = f.fpathW + f.fnameW + L"\\Effect TPL";






	// write tables

	// Blocks 1, 2
	if (!f.doesFolderExistW(eff_folder)) {
		win::makeDirW(eff_folder);
		}

	// Blocks 1, 2
	if (!f.doesFolderExistW(eff_folder_tables)) {
		win::makeDirW(eff_folder_tables);
		}
	for (uint32_t i = 0; i < 2; i++) {
		write_table (f, addrs[i], false, eff_folder_tables + L"\\Table_" + string_to_wstring(to_string(i)) + L".txt");
		}

	// Blocks 3, 4, 5
	for (uint32_t i = 2; i < 5; i++) {

		write_table (f, addrs[i], true, eff_folder_tables + L"\\Table_" + string_to_wstring(to_string(i)) + L".txt");

		}

	// Blocks 6
	if (!f.doesFolderExistW(eff_folder_effect_tpl)) {
		win::makeDirW(eff_folder_effect_tpl);
		}
	write_tpls (f, addrs[5], get_block_size(sizes, addrs[5]), eff_folder_effect_tpl);



	// Blocks 7
	write_tex_table (f, addrs[6], eff_folder_tables + L"\\TextureData.txt");





	}

*/

void init () {
	if (!ini) {ini = new scriptini();}
	if (!app) {app = new appsettings();}
	}

void convert_file (std::wstring fileW, std::wstring fpathW = L"") {
	init ();
	bytestream f;
	if (fileW != L"" && f.openFileW(fileW)) {


		// get parts of the file path
		std::wstring fnameW = getFilenameFileW(fileW);
		std::wstring fextW = toLowerW(getFilenameTypeW(fileW));
		if (fpathW == L"") {
			fpathW = getFilenamePathW(fileW);
			}
		//std::wcout << L"fnameW: \t" << fnameW << std::endl;
		//std::wcout << L"fpathW: \t" << fpathW << std::endl;
		//std::wcout << L"fextW: \t" << fextW << std::endl;
		//std::wcout << L"Input: \t" << fileW << std::endl;

		if (fextW == L".ita") {
			fmtITA ita;
			ita.read_ita(f);

			bytestream s;
			s.resize(ita.size());
			s.seek(0);
			ita.write_ita(s);
			s.setLittleEndian();
			s.writeFileW(fpathW + fnameW + L"_uhd.ita");

			s.setBigEndian();
			s.seek(0);
			ita.write_ita(s);
			s.writeFileW(fpathW + fnameW + L"_ngc.ita");

			s.close();
			s.resize(ita.size(true));
			s.seek(0);
			ita.write_ita(s, true);
			s.setLittleEndian();
			s.writeFileW(fpathW + fnameW + L"_2k7.ita");
			}
		else if (fextW == L".ets") {
			fmtETS ets;
			ets.read_ets(f);

			bytestream s;
			s.resize(ets.size());
			s.seek(0);
			ets.write_ets(s);
			s.setLittleEndian();
			s.writeFileW(fpathW + fnameW + L"_uhd.ets");

			s.setBigEndian();
			s.seek(0);
			ets.write_ets(s);
			s.writeFileW(fpathW + fnameW + L"_ngc.ets");

			s.close();
			s.resize(ets.size(true));
			s.seek(0);
			ets.write_ets(s, true);
			s.setLittleEndian();
			s.writeFileW(fpathW + fnameW + L"_2k7.ets");
			}
		else if (fextW == L".eff") {
			fmtEFF eff;
			eff.read_eff(f);

			eff.export_eff(fpathW + fnameW + L"\\");
//					if (eff.spline_block.table.count > 0) {
//						for (unsigned int i = 0; i < eff.spline_block.table.count; i++) {
//
//							eff.spline_block.entry.at(i).export_obj(L"", );
//
//
//							}
//						}


			}
		else if (fextW == L".est") {
			fmtEST_Effect est;

			est.read_esp_data(f);
			//est.repr();
			//est.import_txt(argvW[1]);
			//est.export_txt("");
			}
		else if (fextW == L".fnt") {
			fmtFNT fnt;

			fnt.open(fileW);
			fnt.export_txt(fpathW + fnameW + L"\\");


			}
		else if (fextW == L".fix") {
			fmtFIX fix;

			fix.read(f, f.size);

			fix.write(fpathW + fnameW + L"_new.fix");
			//fix.export_txt(fpathW + fnameW + L"\\", fnameW);

			}
		else if (fextW == L".fcv") {
			fmtFCV fcv;

			fcv.read(f);

			std::wstring subfolder = L"";

			//fcv.export_txt(fpathW + fnameW + L"\\", fnameW);
			//std::wstring subfolder = L"\\" + fnameW;
			std::cout << "FileSize: \t" << fcv.size() << std::endl;
			bytestream s;
			s.resize(fcv.size());
			s.seek(0);
			fcv.write(s, true);
			s.setLittleEndian();
			s.writeFileW(fpathW + fnameW + subfolder + L"_uhd.fcv");

			s.setBigEndian();
			s.seek(0);
			fcv.write(s);
			s.writeFileW(fpathW + fnameW + subfolder + L"_ngc.fcv");

			s.close();
			s.resize(fcv.size());
			s.seek(0);
			fcv.write(s);
			s.setLittleEndian();
			s.writeFileW(fpathW + fnameW + subfolder + L"_2k7.fcv");

			s.close();
			}
		else if (fextW == L".pack") {
			fmtPACK pak;

				pak.read(f, true);
			//pak.dump_pack(fpathW + fnameW + L"\\");
			pak.export_txt(fpathW + fnameW + L"\\");
			}
		else if (fextW == L".dat") {
			fmtDAT dat;

			// read DAT
			if (dat.open(fileW)) {

				// Dump Contents of DAT
				dat.unpack(fpathW + fnameW, fnameW);
				std::wcout << fpathW << fnameW << std::endl;
				}
			else {
				std::wcout << L"file failed to open\n";
				}
			// Close DAT
			dat.close();
			}
		else if (fextW == L".aev") {
			fmtAEV aev;

			aev.read_aev(f);

			aev.export_txt(fpathW + fnameW + L"\\", fnameW);

			bytestream s;
			s.resize(aev.size());
			s.seek(0);
			aev.write_aev(s);
			s.setLittleEndian();
			s.writeFileW(fpathW + fnameW + L"\\" + fnameW + L"_uhd.aev");

			s.setBigEndian();
			s.seek(0);
			aev.write_aev(s);
			s.writeFileW(fpathW + fnameW + L"\\" + fnameW + L"_ngc.aev");

			s.close();
			s.resize(aev.size(true));
			s.seek(0);
			aev.write_aev(s, true);
			s.setLittleEndian();
			s.writeFileW(fpathW + fnameW + L"\\" + fnameW + L"_2k7.aev");

			s.close();
			}
		else if (fextW == L".seq") {
			fmtSEQ seq;

			seq.read(f);

			std::wstring subfolder = L"";

//			subfolder = fnameW + L"\\";
//			seq.export_txt(fpathW + subfolder, "sequences");


			bytestream s;
			s.resize(seq.size());
			s.seek(0);
			seq.write(s);
			s.setLittleEndian();
			s.writeFileW(fpathW + subfolder + fnameW + L"_uhd.seq");

			s.setBigEndian();
			s.seek(0);
			seq.write(s);
			s.writeFileW(fpathW + subfolder + fnameW + L"_ngc.seq");

			s.close();
			s.resize(seq.size());
			s.seek(0);
			seq.write(s, true);
			s.setLittleEndian();
			s.writeFileW(fpathW + subfolder + fnameW + L"_2k7.seq");

			s.close();
			}
		else if (fextW == L".snd") {
			fmtDAT_SND_Package snd;
			snd.read_dat_snd(f);
			snd.xml_export(fpathW + fnameW + L"_new.xml");

			//bytestream s;
			//s.resize(snd.size(), true);
			//snd.write_dat_snd(s);
			//s.writeFileW(fileW + L"_new.snd");

			}
		else if (fextW == L".udas" || fextW == L".das" || fextW == L".drs") {
			fmtUDAS udas;
			udas.open_udas(fileW);
			udas.unpack_udas(fpathW, fnameW);
			}
		else if (fextW == L".txt" && ini != NULL) {

			// Open Ini
			ini->open(fileW);

			// Look for Section
			if (ini->find_section("ATARI_EVENT")) {

				// Create Empty AEV
				fmtAEV aev;
				aev.data = std::vector<fmtAEV_Region>(1);
				aev.count = 1;
				aev.data[0].import_region("ATARI_EVENT");

				// Save Binary
				bytestream s;
				s.resize(aev.size());
				s.seek(0);
				aev.write_aev(s);
				s.setLittleEndian();
				s.writeFileW(fpathW + fnameW + L"_uhd.aev");

				s.setBigEndian();
				s.seek(0);
				aev.write_aev(s);
				s.writeFileW(fpathW + fnameW + L"_ngc.aev");

				s.close();
				s.resize(aev.size(true));
				s.seek(0);
				aev.write_aev(s, true);
				s.setLittleEndian();
				s.writeFileW(fpathW + fnameW + L"_2k7.aev");



				}
			else if (ini->find_section("AREA_EVENT_PATH")) {

				std::wstring aev_path = ini->get_wstring("AREA_EVENT_PATH", "aev_path");
				if (aev_path.length() > 0) {

					if (aev_path.substr(aev_path.length() - 1) != L"\\" && aev_path.substr(aev_path.length() - 1) != L"/") {
						aev_path += L"\\";
						}



					}

				// Test if path is relative
				if (win::doesFolderExistW(fpathW + aev_path)) {

					// update path
					aev_path = fpathW + aev_path;
					}

				if (win::doesFolderExistW(aev_path)) {



					// get files

					std::vector<std::wstring> files;
					getFilesW(aev_path + L"*.txt", files);

					if (files.size()) {

						// Create Empty AEV
						fmtAEV aev;
						fmtAEV_Region aevreg;
						//aev.count = files.size();
						//aev.data = std::vector<fmtAEV_Region>(aev.count);

						for (unsigned int i = 0; i < files.size(); i++) {


							// Open Ini
							ini->open(files.at(i));


							//aev.data.emplace_back();

							// Look for Section
							if (ini->find_section("ATARI_EVENT")) {
								fmtAEV_Region aevreg;
								aevreg.import_region("ATARI_EVENT");
								aev.data.push_back(aevreg);




								}




							}

						aev.count = aev.data.size();
						if (aev.count > 0) {

							// Save Binary
							bytestream s;
							s.resize(aev.size());
							s.seek(0);
							aev.write_aev(s);
							s.setLittleEndian();
							s.writeFileW(fpathW + fnameW + L"_uhd.aev");

							s.setBigEndian();
							s.seek(0);
							aev.write_aev(s);
							s.writeFileW(fpathW + fnameW + L"_ngc.aev");

							s.close();
							s.resize(aev.size(true));
							s.seek(0);
							aev.write_aev(s, true);
							s.setLittleEndian();
							s.writeFileW(fpathW + fnameW + L"_2k7.aev");

							}



						}

					}
				}

			}
		else if (fextW == L".xsb") {
			fmtXSB xsb;
			xsb.read_xsb(f);
			xsb.write_xap(fpathW + fnameW + L".xap");
			}
		else if (fextW == L".xml") {




			// Read the xml file into a vector
			std::vector<char> buffer(f.stream, f.stream + f.size);
			//std::cout << "size:\t" << theFile.tellg() << std::endl;

			// Store Termination Character
			buffer.push_back('\0');
			rapidxml::xml_document<> doc;
			// Parse the buffer using the xml file parsing library into doc
			doc.parse < rapidxml::parse_full | rapidxml::parse_no_data_nodes >(&buffer[0]);
			//doc.parse<0>(&buffer[0]);

			// check root node
			rapidxml::xml_node<>* rootNode = doc.first_node("snd");
			if (rootNode != NULL) {
				fmtDAT_SND_Package snd;
				snd.xml_import(doc);


				bytestream s;
				s.resize(snd.size());
				snd.write_dat_snd(s);
				s.writeFileW(fpathW + L"NEW_SND_FROM_XML.snd");

				}


			doc.clear();
			}
		f.close();
		} else {std::cout << "failed to open file\n";}
	}

void scan_aev (std::wstring filepath) {
	if (filepath.length() > 1) {

		if (filepath[filepath.length() - 1] != L'\\') {
			filepath += L"\\";
			}

		std::vector<std::wstring> files;
		getFilesW(filepath + L"*.aev", files);

		unsigned int count = files.size();

		if (count == 0) {return;}

		std::vector<uint8_t> collection;
		signed int index;

		for (unsigned int i = 0; i < count; i++) {

			fmtAEV aev;
			aev.open_aev(files.at(i));

			if (aev.count == 0) {continue;}


			for (unsigned int d = 0; d < aev.count; d++) {

				index = findItem(collection, aev.data.at(i).type);
				if (index > -1) {
					append(collection, aev.data.at(i).type);
					std::wcout << L"Discovered Type [" << aev.data.at(i).type << L"] in file {" << getFilenameFileW(files.at(i)) << std::endl;
					}
				}
			}
		}
	}

int test_base64 () {
	bytestream f;
//	f.resize(16);
//	f.stream[0] = 0x53;
//	f.stream[1] = 0x47;
//	f.stream[2] = 0x56;
//	f.stream[3] = 0x73;
//	f.stream[4] = 0x62;
//	f.stream[5] = 0x47;
//	f.stream[6] = 0x38;
//	f.stream[7] = 0x67;
//	f.stream[8] = 0x49;
//	f.stream[9] = 0x43;
//	f.stream[10] = 0x41;
//	f.stream[11] = 0x67;
//	f.stream[12] = 0x49;
//	f.stream[13] = 0x43;
//	f.stream[14] = 0x41;
//	f.stream[15] = 0x3D;
	//f.openFile("G:\\SteamLibrary\\steamapps\\common\\Resident_Evil_4_Tools\\Bio4(Stripped)\\Data\\Bgm\\hello.txt");
	std::string test = "SGVsbG8gICAgICA=";
	f.base64_decode(test);
	f.seek(0);
	f.writeFile("G:\\SteamLibrary\\steamapps\\common\\Resident_Evil_4_Tools\\Bio4(Stripped)\\Data\\Bgm\\hello_new.txt");

	f.close();


	return 1;
	}

int main(int argc, char* argv[]) {

	SetConsoleTitleA(appver);
//
//	std::wcout << "BIO4: \t" << app->getBio4InstallPathW() << std::endl;
//	std::cout << app->test << std::endl;
//	app->test = "Bye";
//	std::cout << app->test << std::endl;




	//Fl_Double_Window* w = win_esl();
	//w->begin();// Add children to window
	//w->show(1, argv);
	//return Fl::run();

	// get args as wchar
	int argcW; LPWSTR *argvW = CommandLineToArgvW(GetCommandLineW(), &argcW); if (argcW == 0) {return 0;} // Get UNICODE Command line

	// Check Inputs
	if (argcW > 1) {

		init();






		//fmtFBX fbx;
		//bytestream f;
		//f.openFileW(argvW[1]);
		//fbx.read(f);

		//return 1;



		// loop through given files
		std::wstring fileW;
		std::wstring fpathW;
		//std::vector<std::wstring> files;
		for (int i = 1; i < argcW; i++) {
			fileW = std::wstring(argvW[i]);
			if (fileW == L"") {continue;}
			fpathW = getFilenamePathW(fileW);

			if (fpathW.find(L":") == std::wstring::npos && fpathW.find(L"\\\\") == std::wstring::npos) {
				fpathW = getFilenamePathW(getexepathW());
				fileW = fpathW + fileW;
				}
			/*
			if (win::doesFolderExistW(fileW)) {

				if (fileW.substr(fileW.length() - 1, 1) != L"\\") {
					fileW += L"\\";

					}


				files.clear();
				getFilesW(fileW + L"*.*", files);

				for (unsigned ii = 0; ii < files.size(); ii++) {
					convert_file(files[ii], fpathW);
					}

				}
			else {
				convert_file(argvW[i], fpathW);
				}
			*/
			convert_file(argvW[i]);

			}
		}
	else {
		// No Inputs, Print Message
		std::cout << "=====================================================================\n";
		std::cout << "Resident Evil 4 EFF Tool\n\n";
		std::cout << "Written By:\tmariokart64n\n";
		std::cout << "Released:\tApril 19 2022\n\n";
		std::cout << "Usage:\n\tre4eff.exe <file>\n\n";
		std::cout << "=====================================================================\n";
		std::cout << "Press ENTER to continue...\n";
		//std::cin.clear();
		//std::cin.sync();
		//std::cin.get();
		convert_file(
			openfilenameW(
				L"All Supported Files \0*.aev;*.dat;*.eff;*.snd;*.seq;*.esl;*.est;*.ets;*.ita;*.fcv*.fnt;*.fix;*.pack;*.tpl;*.udas;*.xsb;*.xml\0\
				Atari Events (*.aev)\0*.aev\0\
				Data Package (*.dat)\0*.dat\0\
				Effects Package (*.eff)\0*.eff\0\
				Enemy Spawn List (*.esl)\0*.esl\0\
				Effect Sprite (*.est)\0*.est\0\
				Frames Curve Values (*.fcv)\0*.fcv\0\
				Font (*.fnt)\0*.fnt\0\
				Sequences (*.seq)\0*.seq\0\
				Sound Data (*.snd)\0*.snd\0\
				Fix for Chinese (*.fix)\0*.fix\0\
				Item Location (*.ita)\0*.ita\0\
				Texture Pack List (*.tpl)\0*.tpl\0\
				Texture Pack (*.pack)\0*.pack\0\
				Data Asset (*.udas)\0*.udas\0\
				Xbox Sound Bank (*.xsb)\0*.xsb\0\
				Xtensible Markup Language (*.xml)\0*.xml\0\
				All Files (*.*)\0*.*\0",
				NULL,
				OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT
				)
			);
		}

	// CleanUp
	LocalFree(argvW); // Free memory allocated for CommandLineToArgvW arguments.
	//system("pause");
    return 0;
	}
