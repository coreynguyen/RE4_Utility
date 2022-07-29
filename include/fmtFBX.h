#ifndef FMTFBX_H
#define FMTFBX_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <sstream>
#include <string>
#include <vector>

#include "bytestream.h"
#include "stringext.h"
#include "filesystem.h"


/*


need to write empty scenes, that are compliant for each version


-models

1.) add an entry to the connections list
2.) update counts int Definitions
3.) store mesh data in Objects

-textures

are stored in the media block as a video lol



?
Seems fbx does not supports splines so i'll need to use obj for that lol
im not even sure if it supports vertex colors, probably 3dsmax hacks it
and stores them to the UV channels, since they state that they reserve
channel0 for colors.

what it does show as supported is
- geometry
- animation
- morphs
- skin (weights)

clearly it is an asset for animation, really sucks

need to test vertex colours and the material systems


 * I should create a complex scene in the oldest version of 3dsmax
   then I can carry it through a newer max and see how they re-organize
   the data. since so far the fbx format seems all over the place

	actually its so shit it makes blenders blend format look god tier

 - Mesh
 - Materials
 - Textures
 - Cameras
 - Lights
 - Animations
 - Bones
 - Parented Meshes
 - Vertex Colors
 - weird transforms
 - Morphs
 - Different Objects (Mesh, Poly, Shape)


*/


struct fmtFBX_Block {
	uint64_t addr_end; // absolute
	uint64_t num_prop;
	uint64_t prop_size;
	uint64_t name_len;
	std::string name;
	bytestream buffer;

	size_t addr;
	size_t size;
	size_t prop_addr;

	fmtFBX_Block () {
		addr = 0;
		size = 0;
		addr_end = 0;
		num_prop = 0;
		prop_size = 0;
		name_len = 0;
		name = "";
		}
	~fmtFBX_Block () {
		buffer.close();
		}
	bool read (bytestream &f, uint32_t version, uint32_t level, int32_t par, int index, bool storeData = true, bool verbose = true) {
		bool isGood = false;
		addr = f.tell();
		if (addr + 13 < f.size) {

			if (version < 7500) {
				addr_end = f.readUlong();
				num_prop = f.readUlong();
				prop_size = f.readUlong();
				}
			else {
				addr_end = f.readUlonglong();
				num_prop = f.readUlonglong();
				prop_size = f.readUlonglong();
				}

			name_len = f.readUbyte();
			if (addr_end > 0) {
				isGood = true;
				}

			std::string pad;
			if (name_len > 0 && f.tell() + name_len < f.size) {
				name = f.readstring(name_len);
				if (verbose) {
					pad = "";
					for (unsigned int i = 0; i < level; i++) {
						pad += "    ";
						}
					std::cout << pad << par << " " << name << " (";

					}
				unsigned char dt;
				prop_addr = f.tell();

				if (num_prop > 0 && prop_size > 0 && prop_addr + prop_size < f.size) {



					if (storeData) {
						buffer.copy(f.stream, prop_size, prop_addr);

						buffer.seek(0);
						for (unsigned int i = 0; i < num_prop; i++) {
							dt = buffer.readUbyte();
							std::cout << dt << ":: ";
							switch (dt) {
								case 'Y': std::cout << "\t " << buffer.readshort(); break; // 0x59
								case 'C': std::cout << "\t " << (int)buffer.readbyte(); break; // 0x43 Char
								case 'I': std::cout << "\t " << buffer.readlong(); break; // 0x49 Integer
								case 'F': std::cout << "\t " << buffer.readfloat(); break; // 0x46 Float
								case 'D': std::cout << "\t " << buffer.readdouble(); break; // 0x44 Double
								case 'L': std::cout << "\t " << buffer.readlonglong(); break; // 0x4C LongLong
								case 'f': break; // 0x66
								case 'd': break; // 0x64
								case 'l': break; // 0x6C
								case 'i': break; // 0x69
								case 'b': break; // 0x62
								case 'S': std::cout << "\t " << buffer.readstring(buffer.readUlong()); break; // 0x53 String
								case 'R': break; // 0x52 Raw
								default: {
									std::cout << "\nERROR:\n\tUnknown Data Type [" << (int)dt << "] \t @ " << (f.tell() - 1) << std::endl;;
									isGood = false;
									f.seek(-1, 1);
									}
								}
							}




						}



					/*
					for (unsigned int i = 0; i < num_prop; i++) {
						data_type = f.readUbyte();
						switch (data_type) {
							case 'Y': f.seek(                2, 1); break; // 0x59
							case 'C': f.seek(                1, 1); break; // 0x43 Char
							case 'I': f.seek(                4, 1); break; // 0x49 Integer
							case 'F': f.seek(                4, 1); break; // 0x46 Float
							case 'D': f.seek(                8, 1); break; // 0x44 Double
							case 'L': f.seek(                8, 1); break; // 0x4C LongLong
							case 'f': f.seek(f.readUbyte() * 4, 1); break; // 0x66
							case 'd': f.seek(f.readUbyte() * 8, 1); break; // 0x64
							case 'l': f.seek(f.readUbyte() * 8, 1); break; // 0x6C
							case 'i': f.seek(f.readUbyte() * 4, 1); break; // 0x69
							case 'b': f.seek(f.readUbyte()    , 1); break; // 0x62
							case 'S': f.seek(f.readUlong()    , 1); break; // 0x53 String
							case 'R': f.seek(f.readUlong()    , 1); break; // 0x52 Raw
							default: {
								std::cout << "ERROR:\n\tUnknown Data Type [" << data_type << "] \t @ " << (f.tell() - 1) << std::endl;;
								isGood = false;
								f.seek(-1, 1);
								}
							}
						}
					*/


					f.seek(prop_addr + prop_size);
					}
				if (verbose) {std::cout  << ")    " << index <<  std::endl;;}

				}
			size = addr_end - addr;



			}
		return isGood;
		}

	};

struct fmtFBX_Footer {
	uint32_t unk001; // 0xE0A6B211
	uint32_t unk002; // 0xCBD6C978
	uint32_t unk003; // 0xAE6AE69F
	uint32_t unk004; // 0x02E13765

	// on newer verison
	uint8_t unk005[6];

	uint32_t unk006;
	uint32_t unk007; // size of data, -20 ?
	uint32_t unk008; // version
	uint8_t unk009[120];
	uint32_t unk010; // 0xE2409670
	uint32_t unk011; // 0xC4EFC364
	uint32_t unk012; // 0xF6F316F9
	uint32_t unk013; // 0x6F953311

	fmtFBX_Block* Properties;
	fmtFBX_Footer () {
		unk001 = 0xE0A6B211;
		unk002 = 0xCBD6C978;
		unk003 = 0xAE6AE69F;
		unk004 = 0x02E13765;
		// on newer verison

		for (unsigned int i = 0; i < 6; i++) {unk005[i] = 0;}
		unk005[1] = 0;
		unk005[2] = 0;
		unk005[3] = 0;
		unk005[4] = 0;
		unk005[5] = 0;
		unk006 = 0;
		unk007 = 0; // size of data, -20 ?
		unk008 = 0; // version
		for (unsigned int i = 0; i < 120; i++) {unk009[i] = 0;}
		unk010 = 0xE2409670;
		unk011 = 0xC4EFC364;
		unk012 = 0xF6F316F9;
		unk013 = 0x6F953311;
		Properties = NULL;
		}
	~fmtFBX_Footer () {
		if (Properties != NULL) {delete[] Properties;}
		}

	};

struct fmtFBX {
	// https://code.blender.org/2013/08/fbx-binary-file-format-specification/

	std::string FileType = "Kaydara FBX Binary  ";
	uint8_t unk001; // 0
	uint8_t unk002; // 26
	uint8_t unk003; // 0
	uint32_t FileVersion; // after 7400, the default for ints is 64bit instead of 32bit
	uint32_t FileCount;
	fmtFBX_Block* FileScene;




	fmtFBX () {
		FileType = "Kaydara FBX Binary  ";
		unk001 = 0;
		unk002 = 0;
		unk003 = 0;
		FileVersion = 0;
		FileCount = 0;
		FileScene = NULL;
		}

	~fmtFBX () {
		if (FileScene != NULL) {delete[] FileScene;}
		}

	void read_block (bytestream &f, uint32_t &count, uint32_t level, int32_t par, uint32_t &version, bool storeData = true, bool verbose = true) {

		// Check pointer is in bounds
		if (!f.eos()) {

			if (!storeData) {
				// Read Block
				fmtFBX_Block b;
				bool isGood = b.read(f, version, level, par, count, storeData, verbose);


				if (isGood) {


					// count
					count++;


					// Read Children
					if (f.tell() < b.addr_end) {

						read_block(f, count, level+1, count - 1, version, storeData, verbose);
						}

					// go to next block
					f.seek(b.addr_end);



					// Read Next Bloc
					read_block(f, count, level, par, version, storeData, verbose);


					}
				else {
					if (verbose) {
						std::cout << "------------------------------------------------------\n";
						}

					f.seek(f.size);
					}

				}
			else {

				// Read Block
				bool isGood = FileScene[count].read(f, version, level, par, count, storeData, verbose);


				if (isGood) {



					// count
					size_t endpos = FileScene[count].addr_end;
					count++;


					// Read Children
					if (f.tell() < endpos) {

						read_block(f, count, level+1, count - 1, version, storeData, verbose);
						}

					// go to next block
					f.seek(endpos);



					// Read Next Bloc
					read_block(f, count, level, par, version, storeData, verbose);


					}
				else {
					if (verbose) {
						std::cout << "------------------------------------------------------\n";
						}

					f.seek(f.size);
					}


				}
			}

		}

	void read_binary (bytestream &f) {


		FileType = f.readstring(20);
		unk001 = f.readUbyte();
		unk002 = f.readUbyte();
		unk003 = f.readUbyte();
		FileVersion = f.readUlong();
		FileCount = 0;
		if (FileScene != NULL) {delete[] FileScene; FileScene = NULL;}
		size_t pos = f.tell();
		unsigned int level = 0;

		signed int par = -1;

		read_block(f, FileCount, 0, -1, FileVersion, false);
		std::cout << "LastRead: \t" << f.tell() << std::endl;
		std::cout << "FileCount: \t" << FileCount << std::endl;

		if (FileCount > 0) {
			FileCount++;
			FileScene = new fmtFBX_Block[FileCount];

			f.seek(pos);
			unsigned int index = 0;
			par = -1;
			read_block(f, index, level, par, FileVersion, true);


			}

		}
	void read_ascii (bytestream &f) {
		}
	bool validate (bytestream &f, bool &isAscii) {
		size_t pos = f.tell();
		bool isGood = false;

		if (f.size > 20) {
			FileType = f.readstring(20);
			if (FileType == "Kaydara FBX Binary  ") {
				isGood = true;
				isAscii = false;
				}
			else {
				f.seek(0);
				std::string s = "";
				while (!not f.eos()) {
					s = f.readline();
					if (s.find("FBX") != std::string::npos) {
						isGood = true;
						isAscii = true;
						break;
						}
					}
				}
			} else {std::cout << "Validation Error:\n\tInvalid File Size\n";}
		f.seek(pos);
		return isGood;
		}
	void read (bytestream &f) {
		bool isAscii = false;
		if (validate(f, isAscii)) {
			if (isAscii) {read_ascii(f);}
			else {read_binary(f);}
			} else {std::cout << "Validation Error:\n\tInvalid Filen\n";}
		}

	};

#endif // FMTFBX_H
