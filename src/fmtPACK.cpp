#include "fmtPACK.h"

fmtPACK_Entry::fmtPACK_Entry () {
	size = 0;
	unk001 = 0xFFFFFFFF;
	packid = 0;
	type = 0;
	data.close();
	}

void fmtPACK_Entry::read_entry (bytestream &f, bool storeData) {
	size = f.readUlong();
	unk001 = f.readUlong();
	packid = f.readUlong();
	type = f.readUlong();
	if (storeData) {
		data.copy(f.stream, size, f.tell());
		}
	}

void fmtPACK_Entry::write_entry (bytestream &s) {
	s.writelong(size = data.size);
	s.writelong(unk001);
	s.writelong(packid);
	s.writelong(type);
	if (size > 0) {
		size_t p = s.tell();
		s.copy(data.stream, size, 0, s.tell());
		s.seek(p + size);
		}
	}

fmtPACK::fmtPACK () {
	packid = 0;
	count = 0;
	addrs.clear();
	info.clear();
	}

std::string fmtPACK::getFileExtensionFromFourCC (unsigned int num) {
	/*
		through testing it seems that I can place ANY
		common image format instead of the typical DDS
		of TGA. Regardless of setting the 'type' field
		to something random the game still somehow
		automatically loads the image properly.

		in this case I will write the file extension
		directly over the type field when storing other
		file types.

		such as;
			.bmp
			.png
			.jpg

		to recover the extension I'll check if
		the first character is a period '.'
	*/
	std::string fext = "";
	if (num >> 24 == 0x2E) { // "."
		for (unsigned int i = 0; i < 4; i++) {
			fext += to_string((char)(num & (0xFF << (i * 8))) >> (i * 8));
			}
		}
	return fext;
	}


std::string fmtPACK::guess_extension (unsigned int &id) {
	// 0 = tga
	// 1 = dds
	std::string fext = ".bin";
	switch (id) {
		case 0x00000001: {fext = ".dds"; break;}
		case 0x00000000: {fext = ".tga"; break;}
		default: {fext = getFileExtensionFromFourCC(id);}
		}
	return fext;
	}

std::string fmtPACK::getFilename (unsigned int num) {
	// generate file name
	std::stringstream ss("");
	ss << TO_HEX(info[num].packid, false, 8) << "_" << padString(to_string(num), 4, "0");

	// get file extension
	std::string fext = guess_extension(info[num].type);

	return (ss.str() + fext);
	}

size_t fmtPACK::size () {

	// Header Size
	size_t nsize = 8 + (info.size() * 4);

	// Header Padding
	nsize += (128-((nsize + 16) % 128)) % 128;

	// Data Size
	for (unsigned int i = 0; i < info.size(); i++) {
		nsize += info[i].data.size + 16;
		nsize += (128-((nsize + 16) % 128)) % 128;
		}

	return nsize;
	}

size_t fmtPACK::recalc_addr () {
	count = info.size();
	addrs.clear();
	size_t ptr = 0;
	if (count > 0) {
		ptr = 8 + (count * 4);
		size_t table_padding = (128-((ptr + 16) % 128)) % 128;
		ptr += table_padding;

		addrs = std::vector<uint32_t>(count);
		for (unsigned int i = 0; i < count; i++) {
			addrs[i] = ptr;
			info[i].size = info[i].data.size;
			ptr += info[i].size + 16;
			ptr += (128-((ptr + 16) % 128)) % 128;
			}
		}
	return ptr;
	}

bool fmtPACK::read (bytestream &f, bool storeData) {
	bool isGood = false;
	size_t pos = f.tell();
	packid = f.readUlong();
	addrs.clear();
	info.clear();
	if (packid != 0x584C4452) {
		count = f.readUlong();
		if (count > 0) {
			addrs = std::vector<uint32_t>(count);
			info = std::vector<fmtPACK_Entry>(count);
			for (unsigned int i = 0; i < count; i++) {
				addrs[i] = f.readUlong();
				}
			for (unsigned int i = 0; i < count; i++) {
				f.seek(pos + addrs[i]);
				info[i].read_entry(f, storeData);
				//info[i].index = i - 1
				}
			isGood = true;
			} else {std::cout << "error: \tpack is empty?\n";}
		} else {std::cout << "error: \tpack is compressed\n";}
	return isGood;
	}

void fmtPACK::write (bytestream &s) {

	// Write Header
	s.writelong(packid);
	s.writelong(count);

	// write address table
	size_t table_padding = (128-(((count * 4) + 24) % 128)) % 128;
	for (unsigned int i = 0; i < count; i++) {
		s.writelong(addrs[i]);
		}
	for (unsigned int i = 0; i < table_padding; i++) {
		s.writebyte(0);
		}

	// write data
	for (unsigned int i = 0; i < count; i++) {
		info[i].write_entry(s);
		table_padding = (128-((s.tell()) % 128)) % 128;
		for (unsigned int c = 0; c < table_padding; c++) {
			s.writebyte(0);
			}
		}
	}

bool fmtPACK::open (std::wstring fileW, bool storeData) {
	bool isGood = false;
	bytestream f;

	if (f.openFileW(fileW)){
		isGood = read(f, storeData);
		f.close();
		}
	else {
		std::wcout << L"Failed to open file:\t" << fileW << L"\n";
		}
	return isGood;
	}

void fmtPACK::save (std::wstring fileW) {
	bytestream s;
	s.resize(recalc_addr());
	s.seek(0);
	if (s.size > 0) {write(s);}
	s.close();
	}

void fmtPACK::dump_pack_image (unsigned int index, std::wstring outnameW) {

	// Check if there is data in data buffer
	if (count > 0 && index < count && info[index].data.size > 0) {

		info[index].data.writeFileW(outnameW);
		//std::wcout << outnameW << string_to_wstring(guess_extension(index)) << std::endl;
		}
	}

void fmtPACK::dump_pack (std::wstring out_dirW, std::wstring prefixW) {

	// Check if the pack data is empty
	if (count == 0) {

		// nothing to do, exit
		return;
		}

	// check out path exists
	if (!win::doesFolderExistW(out_dirW)) {
		// create folder

		win::makeDirW(out_dirW);
		}

	std::stringstream num;
	std::wstring fextW;
	for (unsigned int i = 0; i < count; i++) {

		// generate file name
		num.str(std::string());
		num << TO_HEX(info[i].packid, false, 8) << "_" << padString(to_string(i), 4, "0");

		// get file extension
		std::wstring fextW = string_to_wstring(guess_extension(info[i].type));

		// Write file
		dump_pack_image(i, out_dirW + prefixW + string_to_wstring(num.str()) + fextW);
		}
	}

void fmtPACK::repack (uint32_t pack_num, std::wstring imgpath, std::wstring outfile) {

	// check folder
	if (!win::doesFileExistW(imgpath)) {

		// path doesn't exist, exit
		return;
		}

	// collect files
	std::vector<std::wstring> filesW;
	getFilesW(imgpath + L"*.*", filesW);

	// remove non-image files
	std::wstring fextW;
	for (unsigned int i = filesW.size(); i-- > 0; ) {
		fextW = toLowerW(getFilenameTypeW(filesW.at(i)));
		if (fextW != L".dds" && fextW != L".tga" && fextW != L".jpg" && fextW != L".gif" && fextW != L".bmp" && fextW != L".png") {
			filesW.erase(filesW.begin() + i);
			}
		}

	// sort
	std::sort(filesW.begin(), filesW.end());

	// format a new pack
	packid = pack_num;
	count = filesW.size();
	info.clear();
	if (count > 0) {
		info = std::vector<fmtPACK_Entry>(count);
		for (unsigned int i = 0; i < count; i++) {
			fextW = toLowerW(getFilenameTypeW(filesW[i]));
			info[i].data.openFileW(filesW[i]);
			info[i].size = info[i].data.size;
			info[i].packid = pack_num;
			if (fextW == L".dds") {
				info[i].type = 0;
				}
			else if (fextW == L".tga") {
				info[i].type = 1;
				}
			else {
				info[i].type = 0;
				for (unsigned int i = 0; i < fextW.length(); i++) {
					info[i].type += (int)fextW[i] << (i * 8);
					}
				}
			}
		}

	// write pack
	bytestream s;
	s.resize(size());
	write(s);
	s.writeFileW(outfile);
	}

void fmtPACK::export_txt (std::wstring outpath, std::wstring prefix, std::wstring subfolder) {

	// Create Sub Directory to save ini
	if (!win::doesFolderExistW(outpath)) {
		win::makeDirW(outpath);
		}

	// Create Dump Path
	std::wstring img_path = outpath + subfolder + L"\\";
	if (!win::doesFolderExistW(img_path)) {
		win::makeDirW(img_path);
		}

	// Create text file
	ini->clear();
	ini->header("Texture Package", "PACK", "Set path to image data, paths may be relative or absolute");
	ini->newline();
	ini->hexnumber("pack_id", packid, 8);
	ini->wstring("pack_path", subfolder);
	ini->separator("Image Order (" + to_string(count) + ")");
	ini->boolean("use_order", true);
	ini->newline();
	for (unsigned int i = 0; i < count; i++) {
		ini->wstring("file", string_to_wstring(getFilename(i)), "", i);
		}
	ini->log(outpath + prefix + L".txt");

	// dump textures to dump path
	dump_pack (img_path);

	}



