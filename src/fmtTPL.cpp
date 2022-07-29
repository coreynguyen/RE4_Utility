#include "fmtTPL.h"


fmtTPL_Pack::fmtTPL_Pack () {
	fileid = 0;
	texid = 0;
	filename = "";
	}

std::string fmtTPL_Pack::generate_filename () {
	std::stringstream sstr;
	sstr.str(std::string());
	sstr << "0x" << std::uppercase << TO_HEX(fileid, true, 8);
	filename = sstr.str() + ".pack";
	return filename;
	}

void fmtTPL_Pack::read_pack (bytestream &f) {
	fileid = f.readUlong();
	texid = f.readUlong();
	}

void fmtTPL_Pack::write_pack (bytestream &s) {
	s.writelong(fileid);
	s.writelong(texid);
	}

fmtTPL_Palette::fmtTPL_Palette () {
	count = 0;
	is_compressed = 0;
	pad = 0;
	type = 0;
	addr = 0;
	data.clear();
	}

std::string fmtTPL_Palette::enum_pal_type (unsigned int v) {
	switch (v) {
		case 0x00: return "IA8"; // 8 bit
		case 0x01: return "RGB565"; // 16bit
		case 0x02: return "RGB5A3"; // 8 bit
		default: return "UNDEFINED";
		}
	return "UNDEFINED";
	}

void fmtTPL_Palette::read_palette (bytestream &f) {
	count = f.readUshort();
	is_compressed = f.readUbyte();
	pad = f.readUbyte();
	type = f.readUlong();
	addr = f.readUlong();
	}

void fmtTPL_Palette::write_palette (bytestream &s) {
	s.writeshort(count);
	s.writebyte(is_compressed);
	s.writebyte(pad);
	s.writelong(type);
	s.writelong(addr);
	}

size_t fmtTPL_Palette::size () {
	size_t psize = count;
	if (type == 1) {psize = count * 2;}
	psize += (32-(psize % 32)) % 32;
	return psize;
	}

fmtTPL_Image::fmtTPL_Image () {
	width = 0;
	height = 0;
	type = 0;
	addr = 0;
	wrap_s = 0;
	wrap_t = 0;
	min_filter = 0;
	mag_filter = 0;
	lod_bias = 0.0;
	enable_lod = 0;
	min_lod = 0;
	max_lod = 0;
	is_compressed = 0;
	data.clear();
	bbp[0] = 4;
	bbp[1] = 8;
	bbp[2] = 8;
	bbp[3] = 16;
	bbp[4] = 16;
	bbp[5] = 16;
	bbp[6] = 32;
	bbp[7] = 0;
	bbp[8] = 4;
	bbp[9] = 8;
	bbp[10] = 16;
	bbp[11] = 0;
	bbp[12] = 0;
	bbp[13] = 0;
	bbp[14] = 4;
	}

size_t fmtTPL_Image::size () {
	/*
		0	I4 {4 bit intensity 8x8 tiles}
		1	I8 {8 bit intensity 8x4 tiles}
		2	IA4 {4 bit intensity with 4 bit alpha 8x4 tiles}
		3	IA8 {8 bit intensity with 8 bit alpha 4x4 tiles}
		4	RGB565 {4x4 tiles}
		5	RGB5A3 {*} {4x4 tiles}
		6	RGBA8 {4x4 tiles in two cache lines - first is AR and second is GB}
		8	CI4 {4 bit color index 8x8 tiles}
		9	CI8 {8 bit color index 8x4 tiles}
		10	CI14X2 {14 bit color index 4x4 tiles}
		14	CMP {S3TC compressed 2x2 blocks of 4x4 tiles}
	*/
	if (type < 15 && addr > 0) {
		float texel[2];
		texel[0] = 4;
		texel[1] = 4;
		switch (type) {
			case 0	: {texel[0] = 8; texel[1] = 8; break;}
			case 1	: {texel[0] = 8; texel[1] = 4; break;}
			case 2	: {texel[0] = 8; texel[1] = 4; break;}
			case 3	: {texel[0] = 4; texel[1] = 4; break;}
			case 4	: {texel[0] = 4; texel[1] = 4; break;}
			case 5	: {texel[0] = 4; texel[1] = 4; break;}
			case 6	: {texel[0] = 4; texel[1] = 4; break;}
			case 8	: {texel[0] = 8; texel[1] = 8; break;}
			case 9	: {texel[0] = 8; texel[1] = 4; break;}
			case 10	: {texel[0] = 4; texel[1] = 4; break;}
			case 14	: {texel[0] = 8; texel[1] = 8; break;}
			}
		return (size_t)((ceil(height / texel[0]) * texel[0]) * (ceil(width / texel[1]) * texel[1]) * (bbp[type] / 8.0));
		}

	//format "Image Size[%: % x %]: \t%\n" type width height nsize
	return 0;
	}

void fmtTPL_Image::read_image (bytestream &f) {
	width = f.readUshort();
	height = f.readUshort();
	type = f.readUlong();
	addr = f.readUlong();
	wrap_s = f.readUlong();
	wrap_t = f.readUlong();
	min_filter = f.readUlong();
	mag_filter = f.readUlong();
	lod_bias = f.readfloat();
	enable_lod = f.readUbyte();
	min_lod = f.readUbyte();
	max_lod = f.readUbyte();
	is_compressed = f.readUbyte();
	}

void fmtTPL_Image::write_image (bytestream &s) {
	s.writeshort(width);
	s.writeshort(height);
	s.writelong(type);
	s.writelong(addr);
	s.writelong(wrap_s);
	s.writelong(wrap_t);
	s.writelong(min_filter);
	s.writelong(mag_filter);
	s.writefloat(lod_bias);
	s.writebyte(enable_lod);
	s.writebyte(min_lod);
	s.writebyte(max_lod);
	s.writebyte(is_compressed);
	}

fmtTPL_Entry::fmtTPL_Entry () {
	image_addr = 0;
	palette_addr = 0;
	}

void fmtTPL_Entry::read_table (bytestream &f) {
	image_addr = f.readUlong();
	palette_addr = f.readUlong();
	}

void fmtTPL_Entry::write_table (bytestream &s) {
	s.writelong(image_addr);
	s.writelong(palette_addr);
	}

fmtTPL::fmtTPL () {
	fileid = 0x30AF2000;
	image_count = 0;
	table_addr = 12;
	addr_offset = 0;
	table.clear();
	image.clear();
	palette.clear();
	pack.clear();
	}

unsigned int fmtTPL::removeFillerNumber (unsigned int num, unsigned int fill, unsigned int bytes) {
	unsigned int v = 0;
	unsigned int n = 0;
	unsigned int x = 0;
	unsigned int m = 0;
	unsigned int r = 0;
	unsigned int f = 0;
	for (unsigned int i = 0; i < bytes; i++) {
		f = (bytes - (i + 1)) * 8;
		m = 0xFFL << f;
		n = num & m;
		v = n >> f;
		r = v << f;
		if (v != fill) {
			x += r;
			}
		}
	return x;
	}

size_t fmtTPL::recalc_pointers () {
	size_t ptr = 0;
	unsigned int count = image.size();
	table.clear();
	if (count > 0) {

		table_addr = 12;
		ptr = table_addr + (count * 8);

		// init table
		table = std::vector<fmtTPL_Entry>(count);
		for (unsigned int i = 0; i < count; i++) {
			table[i].image_addr = 0;
			table[i].palette_addr = 0;
			}

		// add image data blocks
		for (unsigned int i = 0; i < count; i++) {
			if (i < image.size() && image[i].width > 0 && image[i].height > 0) {
				table[i].image_addr = ptr;
				ptr += 36;
				}
			}

		// add palette data blocks
		for (unsigned int i = 0; i < count; i++) {
			if (i < palette.size() && palette[i].count > 0) {
				if (palette[i].count > 0 && (palette[i].type == 8 || palette[i].type == 9 || palette[i].type == 10)) {
					table[i].image_addr = ptr;
					ptr += 12 + (count * 1); // ?
					}
				}
			}

		// addr pack blocks
		for (unsigned int i = 0; i < image.size(); i++) {
			image[i].addr = ptr;
			ptr += 8;
			}
		}
	return ptr;
	}

bool fmtTPL::read (bytestream &f) {

	bool isGood = false;

	// Get Start Position of file required if (file is embedded
	size_t pos = f.tell();

	// Check File size
	if (pos + 12 <= f.size) {


		// Read Header
		fileid = f.readUlong(); // Read File ID
		image_count = f.readUlong();
		table_addr = f.readUlong();

		// Check if (header is obfuscated with filling the 0's with 32's
		bool is_filled = false;
		if (fileid == 0x30AF2020 || fileid == 0x2020AF30) {
			is_filled = true;
			fileid = removeFillerNumber(fileid, 0x20, 4);
			image_count = removeFillerNumber(image_count, 0x20, 4);
			table_addr = removeFillerNumber(table_addr, 0x20, 4);
			}

		// Check Byte Order
		if (image_count >= 0x01000000 || image_count < 0) {


			// Correct byte order for file id variable
			f.seek(pos);
			f.islilEndian = !f.islilEndian;

			fileid = f.readUlong();
			image_count = f.readUlong();
			table_addr = f.readUlong();
			}

		//format "fileid: \t%\n" fileid
		//format "image_count: \t%\n" image_count
		//format "table_addr: \t%\n" table_addr

		// Check that table is within bounds
		if (image_count > 0 && pos + 12 + (image_count * 8) <= f.size) {

			// Check Endian
			if (fileid == 0x002724C0 || fileid == 0xC0242700 || fileid == 0x0000AF30 || fileid == 0x0020AF30 || fileid == 0x30AF2000) { // Normal TPL


				// Read Address Entroes for the First Image
				size_t first_addr = f.readUlong();
				size_t second_addr = f.readUlong();

				// Correct Addresses if (they are obfuscated
				if (is_filled) {first_addr = removeFillerNumber(first_addr, 0x20, 4);}
				if (is_filled) {second_addr = removeFillerNumber(second_addr, 0x20, 4);}

				// Take the smallest address of the two addresses and assign it to 'first_addr'
				if (second_addr > 0 && second_addr < first_addr) {
					first_addr = second_addr;
					}

				// Calculate Starting Address of the Image Table
				size_t image_addr_start = table_addr + (image_count * 8);
				if (first_addr > image_addr_start) {

					// usually is 12548356 {padding is added?}
					addr_offset = first_addr - image_addr_start;
					}

				//format "addr_offset: \t%\n" addr_offset
				if (image_count > 0) {

					f.seek(pos + table_addr);

					// Read Address Table
					table = std::vector<fmtTPL_Entry>(image_count);
					for (unsigned int i = 0; i < image_count; i++) {

						table[i].read_table(f);

						if (is_filled) {
							table[i].image_addr = removeFillerNumber(table[i].image_addr, 0x20, 4);
							table[i].palette_addr = removeFillerNumber(table[i].palette_addr, 0x20, 4);
							}

						// Correct the obfuscated addresses
						if (table[i].image_addr > 0) {
							table[i].image_addr -= addr_offset;
							}
						if (table[i].palette_addr > 0) {
							table[i].palette_addr -= addr_offset;
							}

						}

					// Read Palette Entries
					palette = std::vector<fmtTPL_Palette>(image_count);
					for (unsigned int i = 0; i < image_count; i++) {
						f.seek(pos + table[i].palette_addr);

						palette[i].read_palette(f);

						if (is_filled) {
							palette[i].count = removeFillerNumber(palette[i].count, 0x20, 2);
							palette[i].is_compressed = removeFillerNumber(palette[i].is_compressed, 0x20, 1);
							palette[i].pad = removeFillerNumber(palette[i].pad, 0x20, 1);
							palette[i].type = removeFillerNumber(palette[i].type, 0x20, 4);
							palette[i].addr = removeFillerNumber(palette[i].addr, 0x20, 4);
							}


						// Correct the obfuscated addresses
						palette[i].addr -= addr_offset;

						if (palette[i].addr > 0 && palette[i].count > 0) {
							f.seek(pos + palette[i].addr);
							switch (palette[i].type) {
								case 0x00: {
									palette[i].data.clear();
									palette[i].data = std::vector<unsigned short>(palette[i].count);
									for (unsigned int b = 0; b < palette[i].count; b++) {
										palette[i].data[i] = f.readUbyte();
										}
									break;
									}
								case 0x01: {
									palette[i].data.clear();
									palette[i].data = std::vector<unsigned short>(palette[i].count);
									for (unsigned int b = 0; b < palette[i].count; b++) {
										palette[i].data[i] = f.readUshort();
										}
									break;
									}
								case 0x02: {
									palette[i].data.clear();
									palette[i].data = std::vector<unsigned short>(palette[i].count);
									for (unsigned int b = 0; b < palette[i].count; b++) {
										palette[i].data[i] = f.readUbyte();
										}
									break;
									}
								default: {
									std::cout << "unsupported palette type[" << palette[i].type << " ] @ \t";
									std::cout << (int)pos << " :: " << f.file << std::endl;
									}
								}
							f.seek(pos + palette[i].addr + palette[i].size());
							}
						}

					// Read Image Entries
					unsigned int img_size = 0;
					unsigned int img_cnt = 0;
					image = std::vector<fmtTPL_Image>(image_count);
					for (unsigned int i = 0; i < image_count; i++) {
						f.seek(pos + table[i].image_addr);
						image[i].read_image(f);

						if (is_filled) {
							image[i].width = removeFillerNumber(image[i].width, 0x20, 2);
							image[i].height = removeFillerNumber(image[i].height, 0x20, 2);
							image[i].type = removeFillerNumber(image[i].type, 0x20, 4);
							image[i].addr = removeFillerNumber(image[i].addr, 0x20, 4);
							image[i].wrap_s = removeFillerNumber(image[i].wrap_s, 0x20, 4);
							image[i].wrap_t = removeFillerNumber(image[i].wrap_t, 0x20, 4);
							image[i].min_filter = removeFillerNumber(image[i].min_filter, 0x20, 4);
							image[i].mag_filter = removeFillerNumber(image[i].mag_filter, 0x20, 4);
							image[i].lod_bias = bit::IntAsFloat(removeFillerNumber(bit::FloatAsInt(image[i].lod_bias), 0x20, 4));
							image[i].enable_lod = removeFillerNumber(image[i].enable_lod, 0x20, 1);
							image[i].min_lod = removeFillerNumber(image[i].min_lod, 0x20, 1);
							image[i].max_lod = removeFillerNumber(image[i].max_lod, 0x20, 1);
							image[i].is_compressed = removeFillerNumber(image[i].is_compressed, 0x20, 1);
							}


						// Correct the obfuscated addresses
						image[i].addr -= addr_offset;

						img_size = image[i].size();
						img_cnt = 0;
						if (img_size > 0) {
							f.seek(pos + image[i].addr);
							if (image[i].type < 15) {

								f.seek(pos + image[i].addr);
								//format "BBP: \t%\n" image[i].bbp[image[i].type + 1]
								switch (image[i].bbp[image[i].type]) {
									case 0x04: {
										img_cnt = img_size;
										if (img_cnt > 0) {
											image[i].data.clear();
											image[i].data = std::vector<unsigned int>(img_cnt * 2);
											for (unsigned int b = 0; b < img_cnt; b++) {
												image[i].data[(b * 2) + 0] = f.readUbyte();
												image[i].data[(b * 2) + 1] = image[i].data[b * 2] & 15;
												image[i].data[(b * 2) + 0] = image[i].data[b * 2] >> 4;
												}
											}
										break;
										}
									case 0x08: {
										img_cnt = img_size;
										if (img_cnt > 0) {
											image[i].data.clear();
											image[i].data = std::vector<unsigned int>(img_cnt);
											for (unsigned int b = 0; b < img_cnt; b++) {
												image[i].data[b] = f.readUbyte();
												}
											}
										break;
										}
									case 0x10: {
										img_cnt = img_size / 2;
										if (img_cnt > 0) {
											image[i].data.clear();
											image[i].data = std::vector<unsigned int>(img_cnt);
											for (unsigned int b = 0; b < img_cnt; b++) {
												image[i].data[b] = f.readUshort();
												}
											}
										break;
										}
									case 0x20: {
										img_cnt = img_size / 4;
										if (img_cnt > 0) {
											image[i].data.clear();
											image[i].data = std::vector<unsigned int>(img_cnt);
											for (unsigned int b = 0; b < img_cnt; b++) {
												image[i].data[b] = f.readUlong();
												}
											}
										break;
										}
									default: {
										std::cout << "unsupported image type[" << image[i].bbp[image[i].type] << "]\n";
										}
									}
								}
							f.seek(pos + image[i].addr + img_size);
							}
						}
					}
				//f.seek {mod {32-{mod {f.tell{}} 32}} 32} seekdir:#seek_cur // align to 32 bytes
				//format "read stop: \t%\n" {f.tell{} as integer}
				isGood = true;
				}
			else if (fileid == 0x78563412 || fileid == 0x12345678) { // Pack TPL


				// Read Address Table
				if (image_count > 0) {

					// Read Address Table
					table = std::vector<fmtTPL_Entry>(image_count);
					for (unsigned int i = 0; i < image_count; i++) {
						f.seek((pos + table_addr + (i * 0x08)));
						table[i].read_table(f);
						}

					// Read Image Entries
					image = std::vector<fmtTPL_Image>(image_count);
					for (unsigned int i = 0; i < image_count; i++) {
						if (table[i].image_addr > 0) {
							f.seek(pos + table[i].image_addr);
							image[i].read_image(f);
							}
						}

					// Read Pallete Entries
					palette = std::vector<fmtTPL_Palette>(image_count);
					for (unsigned int i = 0; i < image_count; i++) {
						if (table[i].palette_addr > 0) {
							f.seek(pos + table[i].palette_addr);
							palette[i].read_palette(f);
							}
						}

					// Read PACK Entries
					pack = std::vector<fmtTPL_Pack>(image_count);
					for (unsigned int i = 0; i < image_count; i++) {
						if (image[i].addr > 0) {
							f.seek(pos + image[i].addr);
							pack[i].read_pack(f);
							}
						}
					}
				//f.seek {mod {32-{mod {f.tell{}} 32}} 32} seekdir:#seek_cur // file padded to 32
				isGood = true;
				} else {std::cout << "invalid file format [" << fileid << "] @ \t" << f.file << std::endl;}
			} else {std::cout << "Error: Invalid TPL Table: \t @ " << pos << " \t:: " << f.file << std::endl;}
		} else {std::cout << "Error: Failed to Read TPL Header\n";}
	return isGood;
	}

void fmtTPL::write (bytestream &s) {
	size_t nsize = recalc_pointers();
	unsigned int pad = (32-(nsize % 32)) % 32;
	s.writelong(0x78563412);
	s.writelong(image_count = table.size());
	s.writelong(0x0C); // address to table always the same
	for (unsigned int i = 0; i < image_count; i++) {
		table[i].write_table(s);
		}
	for (unsigned int i = 0; i < image.size(); i++) {
		if (image[i].width > 0 && image[i].height > 0) {
			image[i].write_image(s);
			}
		}
	for (unsigned int i = 0; i < palette.size(); i++) {
		if (i <= palette.size()) {
			if (palette[i].count > 0 && (palette[i].type == 8 || palette[i].type == 9 || palette[i].type == 10)) {
				palette[i].write_palette(s);
				}
			}
		}
	for (unsigned int i = 0; i < pack.size(); i++) {
		pack[i].write_pack(s);
		}
	for (unsigned int i = 0; i < pad; i++) {
		s.writebyte(0);
		}
	}

size_t fmtTPL::size () {
	/*
		calculate the size of the TPL
		does not work on GC TPLs only on the PC ones
	*/
	size_t fs = 12 + ((image_count = table.size()) * 8);
	for (unsigned int i = 0; i < image_count; i++) {
		if (table[i].image_addr > 0) {
			fs += 36;
			if (pack.size() > 0) {
				fs += 8;
				}
			}
		if (table[i].palette_addr > 0) {
			fs += 12;
			}
		}
	fs += (32-(fs % 32)) % 32;
	for (unsigned int i = 0; i < image.size(); i++) {
		fs += image[i].size();
		fs += (32-(fs % 32)) % 32;
		}
	fs += (32-(fs % 32)) % 32;
	return fs;
	}

void fmtTPL::fetch_images (std::wstring pack_path, std::wstring outpath) {

	// get pack name
	if (pack.size() == 0) {return;}

	// Get Packs required for importing
	std::vector<uint32_t> pack_ids;
	for (unsigned int i = 0; i < pack.size(); i++) {
		appendIfUnique(pack_ids, pack[i].fileid);
		}

	// check if there is a pack to process
	if (pack_ids.size() == 0) {return;}

	// create dir
	if (!win::doesFileExistW(outpath)) {
		win::makeDirW(outpath);
		}

	// loop through packs
	std::wstring pack_name;
	std::stringstream sstr;
	bytestream f;
	for (unsigned int i = 0; i < pack_ids.size(); i++) {

		// generate pack filepath
		sstr.str(std::string());
		sstr << TO_HEX(pack.at(i).fileid, false, 8);
		pack_name = string_to_wstring(sstr.str());

		// init pack
		fmtPACK pac;

		// open pack
		pac.open(pack_path + pack_name + L".pack", true);

		// loop through each texture id for that pack to be extracted
		for (unsigned int x = 0; x < pack.size(); x++) {

			if (pack_ids.at(i) == pack.at(x).fileid) {

				// dump texture
				pac.dump_pack_image (
					pack[x].texid,
					outpath + pack_name + L"_" + string_to_wstring(padString(to_string(pack[x].texid), 4, "0"))
					);
				}

			}





		}








	}
