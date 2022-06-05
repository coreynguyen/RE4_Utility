#include "fmtDAT.h"

fmtDAT::fmtDAT () {
	count = 0;
	addr = NULL;
	type = NULL;
	data = NULL;
	}

fmtDAT::~fmtDAT () {
	count = 0;
	if (addr != NULL) {delete[] addr;}
	if (type != NULL) {delete[] type;}
	if (data != NULL) {
		for (unsigned int i = 0; i < count; i++) {
			data[i].close();
			}
		delete[] data;
		}
	}

void fmtDAT::close () {
	count = 0;
	if (addr != NULL) {delete[] addr; addr = NULL;}
	if (type != NULL) {delete[] type; type = NULL;}
	if (data != NULL) {
		for (unsigned int i = 0; i < count; i++) {
			data[i].close();
			}
		delete[] data;
		data = NULL;
		}
	}

bool fmtDAT::validate (bytestream &f) {

    // Set Default Return State
    bool isGood = true;

	// Get Starting Position
    size_t pos = f.tell();

	//std::cout << "pos: \t" << pos << std::endl;
	//std::cout << "filesize: \t" << f.size << std::endl;

    // Check that the file is large enough
    if (f.size < 16) {
    	std::cout << "Error: \tInsufficient File Size: \t" << f.size << std::endl;
		return false;
		}

    // Check the first Int for its type
    uint32_t check1 = f.readUlong();
	//std::cout << "check1: \t" << check1 << std::endl;

    // Check type is not NULL
    if (check1 == 0) {
		std::cout << "Error: \tCount is NULL: \t" << check1 << std::endl;
		return false;
		}

    // Check that the file is not
    if (check1 != 0x58414347) { // GCAX Archive used in RE4 PC 2007 Version

		// Check if the first int in big endian
        if (check1 >= 0x00008000) {
            f.islilEndian = !f.islilEndian;
            f.seek(pos);
            check1 = f.readUlong();
            }


        // Check the Second Int
        uint32_t check2 = f.readUlong();



		unsigned int addr_off = 16;
        // If Second Int is not 0 then update
        if (check2 > 0) {
			addr_off = 4;
			}

		// Default the Table Address
        unsigned int addr_pos = pos + addr_off;

        // Check if file table is within bounds
        if (addr_pos + (check1 * 8) > f.size) {
			//std::cout << "Warning: \tFile Table Out of Bounds: \t" << addr_pos + (check1 * 8) << std::endl;
			// in older files, they write the file size here, not the count

			f.seek(addr_pos);

			while (f.tell() < f.size) {
				check1 = f.readUlong();
				if (check1 == 0 || check1 >= 0x41414100) {
					break;
					}
				}
			check1 = (f.tell() - pos - addr_off - 4) / 4;
			//std::cout << "1new count: \t" << check1 << std::endl;

			//return false;
			}

        // Check each Address in in Bounds
        f.seek(addr_pos);
        uint32_t check3;
        for (unsigned int i = 0; i < check1; i++) {
            check3 = f.readUlong();
            if (pos + check3 > f.size) {
            	std::cout << "Error: \tAddress Out of Bounds: \t" << pos + check3 << std::endl;
				return false;
				}
            }

        f.seek(addr_pos + (check1 * 4));
        unsigned int charlen = 4;
        int check4;
        for (unsigned int i = 0; i < check1; i++) {
            for (unsigned int c = 0; c < charlen; c++) {
                check4 = f.readUbyte();
                if (check4 != 0 && (check4 > 90 && check4 < 65)) {
					std::cout << "Error: \tFile Extension Appears Invalid: \t" << check4 << " \t @ " << (f.tell() - 1) << std::endl;
					return false;
                    }
                }
            }

        }
	else {
		std::cout << "Error: \tFile May Be GCAX Archive: \t" << check1 << std::endl;
		return false;
		}

    return isGood;
    }

bool fmtDAT::read (bytestream &f, size_t fsize) {

	bool success = false;

	// Save Start Position
	size_t pos = f.tell();


	// check if a custom size was provided, update if not 0
	if (fsize == 0) {
		fsize = f.size;
		}

	// Validate File is True
	if (validate(f)) {

		// Return to Start of File
		f.seek(pos);

		// Read File Count
		count = f.readUlong();

		// Table Offset
		unsigned int table_off = 16;

		// Check if there is padding
		uint32_t padding = f.readUlong();
		if (padding > 0) {

			// update table address, archive may be without padding
			table_off = 4;
			}

		// Default Table Address
		uint32_t table_addr = pos + table_off;

        // Check if file table is within bounds
        if (table_addr + (count * 8) > fsize) {
			//std::cout << "Warning: \tFile Table Out of Bounds: \t" << table_addr + (count * 8) << std::endl;
			// in older files, they write the file size here, not the count

			f.seek(table_addr);

			// Update FileSize?
			fsize = count;

			while (f.tell() < fsize) {
				count = f.readUlong();
				if (count == 0 || count >= 0x41414100) {
					break;
					}
				}
			count = (f.tell() - pos - table_off - 4) / 4;
			//std::cout << "new count: \t" << count << std::endl;

			//return false;
			}

		// seek to table
		f.seek(table_addr);

		// Dimension Arrays
		addr = new uint32_t[count];
		type = new std::string[count];
		data = new bytestream[count];

		// Read File Addresses
		for (unsigned int i = 0; i < count; i++) {
			addr[i] = f.readUlong();
			}

		// Read File Extensions
		for (unsigned int i = 0; i < count; i++) {
			type[i] = f.readstring(4);
			}


		// Get Unique Addresses
		std::vector<int> addrs;
		for (unsigned int i = 0; i < count; i++) {

			// Only Include if not NULL
			if (addr[i] > 0) {

				// Search if value is already in Array
				if (std::find(addrs.begin(), addrs.end(), addr[i]) == addrs.end()) {

					// Value is Unique, Add to the Array
					addrs.push_back(addr[i]);
					}
				}
			}




		// Append File Size
		addrs.push_back(fsize - pos);

		// Sort Addresses
		std::sort(addrs.begin(), addrs.end());


		// Dimension File Sizes
		std::vector<int>::iterator itr;
		size_t file_size;

		for (unsigned int i = 0; i < count; i++) {

			// Check address is NOT NULL
			if (addr[i] > 0) {

				// Search if Value is in array
				itr = std::find(addrs.begin(), addrs.end(), addr[i]);

				// Check if index is valid
				if (itr != addrs.cend()) {

					// generate size
					file_size = addrs[std::distance(addrs.begin(), itr) + 1] - addr[i];

					// dimension file buffer if size is greater then 0
					if (file_size > 0) {
						data[i].resize(file_size);
						}
					}
				}
			}

		// Read File Data
		for (unsigned int i = 0; i < count; i++) {

			// check if addr is NULL
			if (addr[i] > 0) {

				// Seek to file
				f.seek(pos + addr[i]);

				// Copy Bytes from main buffer to individual file buffer
				for (unsigned int b = 0; b < data[i].size; b++) {
					data[i].stream[b] = f.readbyte();
					}
				}
			}

		// set success state to true
		success = true;
		} else {std::cout << "Error:\tInvalid dat\n";}


	return success;
	}

bool fmtDAT::open (std::wstring filenameW) {
	std::wcout << L"filenameW: \t" << filenameW << std::endl;
	bool success = false;

	// create char buffer
	bytestream f;
	if (f.openFileW(filenameW)) {

		read(f);

		// close main buffer
		f.close();

		success = true;
		}
	else {std::cout << "failed to open file\n";}
	return success;
	}

void fmtDAT::write (std::string filename, bool isLittleEndian, bool hasPadding) {

	// Calculate new buffer size
	size_t new_size = 4 + (count * 8);
	if (hasPadding) {
		new_size += 12;
		}
	new_size += (32-(new_size % 32)) % 32;
	for (unsigned int i = 0; i < count; i++) {
		new_size += data[i].size;
		}
	new_size += (32-(new_size % 32)) % 32;

	if (new_size > 0) {

		// Create Char buffer
		bytestream s;

		// dimension char buffer
		s.resize(new_size);
		s.seek(0);

		// set byte order
		s.islilEndian = isLittleEndian;

		// default table addr
		size_t addr_pos = 4;

		// write header
		s.writelong(count);
		if (hasPadding) {
			addr_pos = 16;
			s.writelong(0);
			s.writelong(0);
			s.writelong(0);
			}

		// update table addr
		addr_pos += count * 8;
		unsigned int addr_pos_padding = (32-(new_size % 32)) % 32;
		addr_pos += addr_pos_padding;

		// write new addresses
		for (unsigned int i = 0; i < count; i++) {
			if (data[i].size > 0) {
				s.writelong(addr_pos);
				}
			else {
				s.writelong(0);
				}
			addr_pos += data[i].size;
			}

		// write file types
		for (unsigned int i = 0; i < count; i++) {
			if (data[i].size > 0) {
				s.writestring(type[i], 4);
				}
			else {
				s.writelong(0);
				}
			}

		// write padding
		for (unsigned int i = 0; i < addr_pos_padding; i++) {
			s.writebyte(0);
			}

		// write file buffers
		size_t pos;
		for (unsigned int i = 0; i < count; i++) {
			if (data[i].size > 0) {
				pos = s.tell();
				for (unsigned int b = 0; b < data[i].size; b++) {
					s.stream[pos + b] = data[i].stream[b];
					}
				s.seek(pos + data[i].size);
				}
			}

		// write end padding
		pos = s.tell();
		size_t end_padding = (32-(pos % 32)) % 32;
		for (unsigned int i = 0; i < end_padding; i++) {
			s.writebyte(0xCD);
			}
		}
	}

void fmtDAT::unpack (std::wstring outdirW, std::wstring prefixW) {

	// Check if path exists
	if (!win::doesFileExistW(outdirW)) {

		// if not, create path
		win::makeDirW(outdirW);
		}

	// loop through each file
	for (unsigned int i = 0; i < count; i++) {

		// write file
		data[i].writeFileW(
			outdirW + L"\\" +
			prefixW + L"_" +
			string_to_wstring(padString(to_string(i), 4)) + L"." +
			string_to_wstring(type[i])
			);
		}
	}

