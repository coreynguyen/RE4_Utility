#include "fmtFIX.h"

fmtFIX_Entry::fmtFIX_Entry () {
	index = 0;
	size = 0;
	addr = 0;
	}

void fmtFIX_Entry::clear () {
	index = 0;
	size = 0;
	addr = 0;
	data.close();
	}

void fmtFIX_Entry::read (bytestream &f) {
	index = f.readUlong();
	size = f.readUlong();
	addr = f.readUlong();
	}

void fmtFIX_Entry::write (bytestream &s) {
	s.writelong(index);
	s.writelong(size);
	s.writelong(addr);
	}

void fmtFIX::read (bytestream &f, bool storeData) {
	size_t pos = f.tell();
	size_t min_addr = f.size;
	unsigned int i = 0;

	while (!f.eos() && f.tell() < min_addr) {
		// Seek to the image entry
		f.seek(pos + (i * 12));

		// Append entry to array
		fmtFIX_Entry entry;
		dds_info.push_back(entry);

		// read entry
		dds_info.back().read(f);

		// update stop position
		if (dds_info.back().addr > 0 && dds_info.back().addr < min_addr) {
			min_addr = dds_info.back().addr;
			}

		// validate entry
		if (dds_info.back().addr + dds_info.back().size > f.size || dds_info.back().index == 0x20534444) {
			dds_info.pop_back();
			break;
			}
		i++;
		}

	// read image data
	if (storeData) {
		for (i = 0; i < dds_info.size(); i++) {
			dds_info.at(i).data.copy(f.stream, dds_info.at(i).size, dds_info.at(i).addr);
			}
		}
	}

void fmtFIX::dump (std::wstring outdir, std::wstring prefix) {

	if (dds_info.size() > 0) {

		if (!win::doesFolderExistW(outdir)) {
			win::makeDirW(outdir);
			}

		for (unsigned int i = 0; i < dds_info.size(); i++) {

			dds_info.at(i).data.writeFileW(
				outdir + prefix + L"_" + string_to_wstring(padString(to_string(dds_info[i].index), 4, "0")) + L".dds"
				);
			}
		}
	}

void fmtFIX::export_txt (std::wstring outpath, std::wstring prefix, std::wstring subfolder) {

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
	ini->header("Texture Fix", "FIX", "Set path to image data, paths may be relative or absolute");
	ini->newline();
	ini->wstring("fix_path", subfolder);
	ini->separator("Image Order (" + to_string(dds_info.size()) + ")");
	ini->boolean("use_order", true);
	ini->newline();
	for (unsigned int i = 0; i < dds_info.size(); i++) {
		ini->wstring("file", prefix + L"_" + string_to_wstring(padString(to_string(dds_info[i].index), 4, "0")) + L".dds", "", i);
		}
	ini->log(outpath + L"fix.txt");

	// dump textures to dump path
	dump(img_path, prefix);

	}

void fmtFIX::import_txt (std::wstring &fnameW, std::wstring &fpathW, std::wstring &fextW) {

    // Get image path from ini
    std::wstring fix_path = ini->get_wstring("FIX", "fix_path");
    if (fix_path.length() > 0) {

        // test if the path is relative
        if (!win::is_absolute_pathW(fix_path)) {

            // append path
            fix_path = win::fixTrailingSlashW(win::amendRelativePathW(fix_path, fpathW));
            }

        // Check that path Exists
        if (!win::doesFolderExistW(fix_path)) {

            // Failed to Locate Folder
            std::cout << "Failed To Locate Image Path for FIX" << std::endl;
            fix_path = L"";

            }
        }

    // Check if files are explicitly defined
    bool use_order = ini->get_boolean("FIX", "use_order");
    if (ini->get_string("FIX", "use_order") != "" && use_order) {

        // Read Each File Entry
        std::vector<ini_list> files = ini->get_list("FIX", "file");

        // check that list is not empty
        unsigned int list_count = files.size();
        if (list_count > 0) {

            // update count if there is an index larger then count
            if (files.back().index > 0 && (unsigned)(files.back().index + 1) > list_count) {
                list_count = files.back().index + 1;
                }

            fmtFIX fix;
            dds_info = std::vector<fmtFIX_Entry>(list_count);
            unsigned int j;
            for (unsigned int i = 0; i < files.size(); i++) {
                j = files.at(i).index;
                if (files.at(i).index > -1 && j < list_count) {

                    dds_info.at(j).index = i;

                    if (win::is_absolute_path(files.at(i).item)) {

                        dds_info[j].data.openFile(files.at(i).item);
                        }
                    else {
                        dds_info[j].data.openFileW(fix_path + string_to_wstring(files.at(i).item));
                        std::wcout << fix_path + string_to_wstring(files.at(i).item) << std::endl;
                        }
                    }
                }
            write(fpathW + fnameW + L"_new.fix");
            }
        }
    else if (fix_path != L"") {

        // Read All Files From Path




        }
    }

void fmtFIX::write (std::wstring outfile) {

	// check count
	unsigned int count = dds_info.size();
	if (count > 0) {

		// rebuild pointer table
		size_t ptr = count * 12;
		for (unsigned int i = 0; i < count; i++) {
			dds_info.at(i).addr = ptr;
			dds_info.at(i).size = dds_info.at(i).data.size;
			ptr += dds_info.at(i).size;
			}

		// write to file
		bytestream s;
		s.resize(ptr);
		s.seek(0);
		ptr = count * 12;
		for (unsigned int i = 0; i < count; i++) {
			dds_info.at(i).write(s);
			s.copy(dds_info.at(i).data.stream, dds_info.at(i).data.size, 0, ptr);
			ptr += dds_info.at(i).data.size;
			}
		s.writeFileW(outfile);
		}

	}



