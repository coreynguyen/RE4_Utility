#include "fmtFNT.h"


void fmtFNT::read (bytestream &f) {
	if (f.size > 32) {
		addrs[0] = f.readUlong();

		// check endian
		if (addrs[0] >= 0x20000000) {
			f.islilEndian = !f.islilEndian;
			f.seek(0);
			addrs[0] = f.readUlong();
			}

		addrs[1] = f.readUlong();
		addrs[2] = f.readUlong();
		addrs[3] = f.readUlong();
		addrs[4] = f.readUlong();
		addrs[5] = f.readUlong();
		addrs[6] = f.readUlong();
		addrs[7] = f.readUlong();

		if (addrs[0] >= 32) { // tpl
			f.seek(addrs[0]);
			tpl.read(f);
			}

		codepage.clear();
		if (addrs[1] > 0) { // codepage
			f.seek(addrs[1]);
			unsigned int count = (f.tell() - addrs[1]) / 2;
			if (count > 0) {
				codepage = std::vector<uint16_t>(count);
				for (unsigned int i = 0; i < count; i++) {
					codepage.at(i) = f.readUshort();
					}
				}

			}

		}

	}

void fmtFNT::open (std::wstring file) {
	bytestream f;
	if (f.openFileW(file)) {
		read(f);
		f.close();
		} else {std::wcout << L"failed to open file: \t" << file << std::endl;}
	}

void fmtFNT::export_txt (std::wstring outpath) {
		std::wstring bio4 = app->bio_path;


		if (bio4.length() > 0) {
			std::wstring bio4_imagepack = bio4 + L"BIO4\\ImagePack\\";

			tpl.fetch_images(bio4_imagepack, outpath);

			}


		//std::wcout << bio4 << std::endl;

	}
