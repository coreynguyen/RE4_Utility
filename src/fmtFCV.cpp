#include "fmtFCV.h"


fmtFCV_Value::fmtFCV_Value () {
	num_keys = 0;
	}

size_t fmtFCV_Value::block_size (uint16_t &data_type) {
	num_keys = 0;
	if (keys.size() > num_keys) {num_keys = keys.size();}
	if (values.size() > num_keys) {num_keys = values.size();}
	size_t bs = 2 + num_keys + num_keys;
	switch ((data_type & 0xFF00) >> 8) {
		case 0x00: {bs += 12 * num_keys; break;}
		case 0x04: {bs += 12 * num_keys; break;}
		case 0x05: {bs += 12 * num_keys; break;}
		case 0x06: {bs += 12 * num_keys; break;}
		case 0x10: {bs += 8 * num_keys; break;}
		case 0x15: {bs += 8 * num_keys; break;}
		case 0x16: {bs += 8 * num_keys; break;}
		case 0x20: {bs += 6 * num_keys; break;}
		case 0x25: {bs += 6 * num_keys; break;}
		case 0x26: {bs += 6 * num_keys; break;}
		case 0x40: {bs += 10 * num_keys; break;}
		case 0x44: {bs += 10 * num_keys; break;}
		case 0x45: {bs += 10 * num_keys; break;}
		case 0x46: {bs += 10 * num_keys; break;}
		case 0x50: {bs += 6 * num_keys; break;}
		case 0x54: {bs += 6 * num_keys; break;}
		case 0x55: {bs += 6 * num_keys; break;}
		case 0x56: {bs += 6 * num_keys; break;}
		case 0x60: {bs += 4 * num_keys; break;}
		case 0x64: {bs += 4 * num_keys; break;}
		case 0x65: {bs += 4 * num_keys; break;}
		case 0x66: {bs += 4 * num_keys; break;}
		case 0x80: {bs += 9 * num_keys; break;}
		case 0x90: {bs += 5 * num_keys; break;}
		case 0x95: {bs += 5 * num_keys; break;}
		case 0x96: {bs += 5 * num_keys; break;}
		case 0xA0: {bs += 3 * num_keys; break;}
		case 0xA4: {bs += 3 * num_keys; break;}
		case 0xA5: {bs += 3 * num_keys; break;}
		case 0xA6: {bs += 3 * num_keys; break;}
		case 0xF0: {bs += 4 * num_keys; break;}
		}
	return bs;
	}

void fmtFCV_Value::read (bytestream &f, uint16_t &data_type) {
	num_keys = f.readUshort();
	if (num_keys > 0) {

		keys = std::vector<uint16_t>(num_keys);
		for (unsigned int i = 0; i < num_keys; i++) {
			keys.at(i) = f.readUshort();
			}

		values = std::vector<std::vector<float>>(num_keys, std::vector<float>(4));

		unsigned int type;
		for (unsigned int i = 0; i < num_keys; i++) {
			type = (data_type & 0xFF00) >> 8;
			switch (type) {
				case 0x00: {values.at(i) = to_vector<float>() << f.readfloat() << f.readfloat() << f.readfloat() << 0.0f; break;}
				case 0x04: {values.at(i) = to_vector<float>() << f.readfloat() << f.readfloat() << f.readfloat() << 0.0f; break;}
				case 0x05: {values.at(i) = to_vector<float>() << f.readfloat() << f.readfloat() << f.readfloat() << 0.0f; break;}
				case 0x06: {values.at(i) = to_vector<float>() << f.readfloat() << f.readfloat() << f.readfloat() << 0.0f; break;}
				case 0x10: {values.at(i) = to_vector<float>() << (float)f.readshort() << (float)f.readshort() << (float)f.readshort() << (float)f.readshort(); break;}
				case 0x15: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x16: {values.at(i) = to_vector<float>() << f.readfloat() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x20: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x25: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x26: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x40: {values.at(i) = to_vector<float>() << (float)f.readUshort() << f.readfloat() << f.readfloat() << 0.0f; break;}
				case 0x44: {values.at(i) = to_vector<float>() << (float)f.readUshort() << f.readfloat() << f.readfloat() << 0.0f; break;}
				case 0x45: {values.at(i) = to_vector<float>() << (float)f.readUshort() << f.readfloat() << f.readfloat() << 0.0f; break;}
				case 0x46: {values.at(i) = to_vector<float>() << (float)f.readUshort() << f.readfloat() << f.readfloat() << 0.0f; break;}
				case 0x50: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x54: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x55: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x56: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x60: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << 0.0f << 0.0f; break;}
				case 0x64: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << 0.0f << 0.0f; break;}
				case 0x65: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << 0.0f << 0.0f; break;}
				case 0x66: {values.at(i) = to_vector<float>() << (float)f.readUshort() << (float)f.readUshort() << 0.0f << 0.0f; break;}
				case 0x80: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << f.readfloat() << (float)f.readUshort() << (float)f.readUshort(); break;}
				case 0x90: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x95: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0x96: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << (float)f.readUshort() << (float)f.readUshort() << 0.0f; break;}
				case 0xA0: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << (float)f.readUbyte() << (float)f.readUbyte() << 0.0f; break;}
				case 0xA4: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << (float)f.readUbyte() << (float)f.readUbyte() << 0.0f; break;}
				case 0xA5: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << (float)f.readUbyte() << (float)f.readUbyte() << 0.0f; break;}
				case 0xA6: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << (float)f.readUbyte() << (float)f.readUbyte() << 0.0f; break;}
				case 0xF0: {values.at(i) = to_vector<float>() << (float)f.readUbyte() << (float)f.readUbyte() << (float)f.readUbyte() << (float)f.readUbyte(); break;}
				default: {
					std::cout << "unknown data type [" << type << "]\n";
					break;
					}
				}
			}
		}
	}

void fmtFCV_Value::write (bytestream &s, uint16_t &data_type) {
	num_keys = 0;
	if (keys.size() > num_keys) {num_keys = keys.size();}
	if (values.size() > num_keys) {num_keys = values.size();}
	if (num_keys > 0) {
		s.writeshort(num_keys);

		for (unsigned int i = 0; i < num_keys; i++) {
			s.writeshort(keys.at(i));
			}
		for (unsigned int i = 0; i < num_keys; i++) {
			switch ((data_type & 0xFF00) >> 8) {
				case 0x00: {
					s.writefloat(values[i][0]);
					s.writefloat(values[i][1]);
					s.writefloat(values[i][2]);
					break;
					}
				case 0x04: {
					s.writefloat(values[i][0]);
					s.writefloat(values[i][1]);
					s.writefloat(values[i][2]);
					break;
					}
				case 0x05: {
					s.writefloat(values[i][0]);
					s.writefloat(values[i][1]);
					s.writefloat(values[i][2]);
					break;
					}
				case 0x06: {
					s.writefloat(values[i][0]);
					s.writefloat(values[i][1]);
					s.writefloat(values[i][2]);
					break;
					}
				case 0x10: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					s.writeshort(values[i][3]);
					break;
					}
				case 0x15: {
					s.writefloat(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x16: {
					s.writefloat(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x20: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x25: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x26: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x40: {
					s.writeshort(values[i][0]);
					s.writefloat(values[i][1]);
					s.writefloat(values[i][2]);
					break;
					}
				case 0x44: {
					s.writeshort(values[i][0]);
					s.writefloat(values[i][1]);
					s.writefloat(values[i][2]);
					break;
					}
				case 0x45: {
					s.writeshort(values[i][0]);
					s.writefloat(values[i][1]);
					s.writefloat(values[i][2]);
					break;
					}
				case 0x46: {
					s.writeshort(values[i][0]);
					s.writefloat(values[i][1]);
					s.writefloat(values[i][2]);
					break;
					}
				case 0x50: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x54: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x55: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x56: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x60: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					break;
					}
				case 0x64: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					break;
					}
				case 0x65: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					break;
					}
				case 0x66: {
					s.writeshort(values[i][0]);
					s.writeshort(values[i][1]);
					break;
					}
				case 0x80: {
					s.writebyte(values[i][0]);
					s.writefloat(values[i][1]);
					s.writeshort(values[i][2]);
					s.writeshort(values[i][3]);
					break;
					}
				case 0x90: {
					s.writebyte(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x95: {
					s.writebyte(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;
					}
				case 0x96: {
					s.writebyte(values[i][0]);
					s.writeshort(values[i][1]);
					s.writeshort(values[i][2]);
					break;}
				case 0xA0: {
					s.writebyte(values[i][0]);
					s.writebyte(values[i][1]);
					s.writebyte(values[i][2]);
					break;
					}
				case 0xA4: {
					s.writebyte(values[i][0]);
					s.writebyte(values[i][1]);
					s.writebyte(values[i][2]);
					break;
					}
				case 0xA5: {
					s.writebyte(values[i][0]);
					s.writebyte(values[i][1]);
					s.writebyte(values[i][2]);
					break;
					}
				case 0xA6: {
					s.writebyte(values[i][0]);
					s.writebyte(values[i][1]);
					s.writebyte(values[i][2]);
					break;
					}
				case 0xF0: {
					s.writebyte(values[i][0]);
					s.writebyte(values[i][1]);
					s.writebyte(values[i][2]);
					s.writebyte(values[i][3]);
					break;
					}
				default: {
					std::cout << "Format Not Supported [" << (int)((data_type & 0xFF00) >> 8) << "]\n";
					break;
					}
				}
			}
		}
	}


fmtFCV_Track::fmtFCV_Track () {
	index = 0;
	}

void fmtFCV_Track::read (bytestream &f, uint16_t &data_type) {
	x.read(f, data_type);
	y.read(f, data_type);
	z.read(f, data_type);
	}

size_t fmtFCV_Track::block_size (uint16_t &data_type) {
	size_t bs = 0;
	bs += x.block_size(data_type);
	bs += y.block_size(data_type);
	bs += z.block_size(data_type);
	return bs;
	}

void fmtFCV_Track::write (bytestream &s, uint16_t &data_type) {
	x.write(s, data_type);
	y.write(s, data_type);
	z.write(s, data_type);
	}

fmtFCV::fmtFCV () {
	num_frames = 0;
	num_tracks = 0;
	filesize = 0;
	}

bool fmtFCV::validate (bytestream &f, bool verbose) {

	// Set Fail State
	bool isGood = false;

	// Get start position
	size_t pos = f.tell();

	// check there is enough room to read the count
	if (pos + 3 < f.size) {

		// read the count
		f.seek(pos + 2);
		unsigned int chk1 = f.readUbyte();

		// check that count is large enough
		if (chk1 > 0) {

			// calculate address to first pointer entry
			size_t chk2 = (chk1 * 3) + 3;
			chk2 += (4-((chk2 - pos) % 4)) % 4;
			chk2 += 4;

			// check that we can read this pointer entry
			if (pos + chk2 + 4 < f.size) {

				// calculate the end of the pointer table
				size_t chk3 = chk2 + (chk1 * 4);

				// check that the end of the pointer table is in bounds
				if (pos + chk3 < f.size) {

					// seek to the pointer table
					f.seek(pos + chk2);

					// read all pointers
					size_t chk4;
					for (unsigned int i = 0; i < chk1; i++) {

						// match if one of the pointers at the end of of the point table
						chk4 = f.readUlong();
						if (chk3 == chk4) {

							// located, exit
							isGood = true;
							break;
							}
						}

					// check state
					if (!isGood) {

						// switch endian
						f.islilEndian = !f.islilEndian;

						// repeat test, seek to the pointer table again
						f.seek(pos + chk2);

						// read all pointers, agian

						for (unsigned int i = 0; i < chk1; i++) {

							// match if one of the pointers at the end of of the point table
							chk4 = f.readUlong();
							if (chk3 == chk4) {

								// located, exit
								isGood = true;
								break;
								}
							}
						if (!isGood) {
							if (verbose) {
								std::cout << "Validation Failure:\n\tUnable To Approximate First Pointer Address\n";
								}
							}
						}
					} else {if (verbose) {std::cout << "Validation Failure:\n\tNo data?\n";}}
				} else {if (verbose) {std::cout << "Validation Failure:\n\tPointer Table not reachable\n";}}
			} else {if (verbose) {std::cout << "Validation Failure:\n\tFile is Empty?\n";}}
		} else {if (verbose) {std::cout << "Validation Failure:\n\tInvalid File Size\n";}}

	// return back
	f.seek(pos);

	// return state
	return isGood;
	}

void fmtFCV::recalc_addrs () {

	if (config.size() < nodes.size()) {
		num_tracks = config.size();
		}
	else {
		num_tracks = nodes.size();
		}
	if (tracks.size() < num_tracks) {
		num_tracks = tracks.size();
		}
	else {
		num_tracks = num_tracks;
		}
	if (num_tracks > 0) {
		size_t ptr = (num_tracks * 3) + 3;
		unsigned int padding = (4-(ptr % 4)) % 4;
		ptr += padding + 4 + (num_tracks * 4);
		filesize = ptr;
		for (unsigned int i = 0; i < num_tracks; i++) {
			filesize += tracks.at(i).block_size(config.at(i));
			}
		padding = (32-(filesize % 32)) % 32;
		filesize += padding;

		/*
			edited to write the blocks in a preserved order
		*/
		std::vector<unsigned int> order = std::vector<unsigned int>(num_tracks);
		std::vector<unsigned int> order_sorted = std::vector<unsigned int>(num_tracks);

		for (unsigned int i = 0; i < num_tracks; i++) {
			order.at(i) = tracks.at(i).index;
			order_sorted.at(i) = tracks.at(i).index;
			}
		std::sort(order_sorted.begin(), order_sorted.end());

		signed int x;
		addrs.clear();
		addrs = std::vector<uint32_t>(num_tracks);
		for (unsigned int i = 0; i < num_tracks; i++) {
			x = findItem(order, order_sorted.at(i));
			addrs.at(x) = ptr;
			ptr += tracks.at(x).block_size(config.at(x));
			}

		}

	}

size_t fmtFCV::size () {
	std::cout << "num_tracks: \t" << (int)num_tracks << std::endl;
	size_t nsize = (num_tracks * 3) + 3;
	std::cout << "header: \t" << nsize << std::endl;

	nsize += (4-(nsize % 4)) % 4;

	std::cout << "header padding: \t" << nsize << std::endl;

	nsize += 4 + (num_tracks * 4);

	std::cout << "pointer table: \t" << nsize << std::endl;


	for (unsigned int i = 0; i < num_tracks; i++) {
		nsize += tracks[i].block_size(config.at(i));
		}


	std::cout << "data: \t" << nsize << std::endl;

	nsize += (32-(nsize % 32)) % 32;
	std::cout << "data padding: \t" << nsize << std::endl;
	return nsize;
	}

std::vector<uint32_t> fmtFCV::calcBlockEnds (size_t &fsize, std::vector<uint32_t> &addrs) {

	std::vector<uint32_t> limits;
	signed int index = 0;

	for (unsigned int i = 0; i < addrs.size(); i++) {
		index = findItem<uint32_t>(limits, addrs.at(i));
		if (index > -1) {
			append(limits, addrs.at(i));
			}
		}
	append(limits, filesize);
	std::sort(limits.begin(), limits.end());
	return limits;
	}

void fmtFCV::read (bytestream &f) {
	if (validate(f)) {
		num_frames = f.readUshort();
		num_tracks = f.readUbyte();
		if (num_tracks > 0) {
			config = std::vector<uint16_t>(num_tracks);
			tracks = std::vector<fmtFCV_Track>(num_tracks);
			nodes = std::vector<uint8_t>(num_tracks);
			addrs = std::vector<uint32_t>(num_tracks);
			std::vector<uint32_t> tmp = std::vector<uint32_t>(num_tracks);

			for (unsigned int i = 0; i < num_tracks; i++) {
				config.at(i) = f.readUshort();
				}

			for (unsigned int i = 0; i < num_tracks; i++) {
				nodes.at(i) = f.readUbyte();
				}

			f.seek((4-(f.tell() % 4)) % 4, seek::cur);

			filesize = f.readUlong();
			for (unsigned int i = 0; i < num_tracks; i++) {
				addrs.at(i) = f.readUlong();
				tmp.at(i) = addrs.at(i);
				}

			// preserve block order
			std::sort(tmp.begin(), tmp.end());

			for (unsigned int i = 0; i < num_tracks; i++) {
				f.seek(addrs.at(i));
				//std::cout << "Track%:\t0x%\t%\n" i {bit.IntAsHex{addrs[i] as integer}} {config[i] as string}

				tracks[i].read(f, config.at(i));
				tracks[i].index = findItem(tmp, addrs.at(i)); // create block order
				}
			}
		} else {std::cout << "Error:\n\tFile Filed Validation: \t" << f.file << std::endl;}
	}

void fmtFCV::write (bytestream &s, bool swap_filesize) {
	num_tracks = 0;
	if (config.size() > num_tracks) {num_tracks = config.size();}
	if (nodes.size() > num_tracks) {num_tracks = nodes.size();}
	if (tracks.size() > num_tracks) {num_tracks = tracks.size();}
	if (num_tracks > 0) {
		s.writeshort(num_frames);
		s.writebyte(num_tracks);
		for (unsigned int i = 0; i < num_tracks; i++) {
			s.writeshort(config.at(i));
			}
		for (unsigned int i = 0; i < num_tracks; i++) {
			s.writebyte(nodes.at(i));
			}
		size_t ptr = (num_tracks * 3) + 3;


		unsigned int padding = (4-(ptr % 4)) % 4;


		for (unsigned int i = 0; i < padding; i++) {
			s.writebyte(0);
			}
		ptr += padding + 4 + (num_tracks * 4);


		filesize = ptr;
		for (unsigned int i = 0; i < num_tracks; i++) {
			filesize += tracks[i].block_size(config.at(i));
			}

		padding = (32-(filesize % 32)) % 32;
		filesize += padding;

		if (swap_filesize) {
			s.writelong(bit::swapBytes(bit::swapBytes(filesize, 1, 4), 2, 3));
			}
		else {
			s.writelong(filesize);
			}

		/*
			edited to write the blocks in a preserved order
		*/
		std::vector<unsigned int > order(num_tracks);
		std::vector<unsigned int > order_sorted(num_tracks);

		for (unsigned int i = 0; i < num_tracks; i++) {
			order[i] = tracks[i].index;
			order_sorted.at(i) = tracks[i].index;
			}
		std::sort(order_sorted.begin(), order_sorted.end());

		signed int x;
		addrs = std::vector<uint32_t>(num_tracks);
		for (unsigned int i = 0; i < num_tracks; i++) {
			x = findItem(order, order_sorted.at(i));
			addrs.at(x) = ptr;
			ptr += tracks.at(x).block_size(config.at(x));
			}

		for (unsigned int i = 0; i < num_tracks; i++) {
			s.writelong(addrs.at(i));
			}

		for (unsigned int i = 0; i < num_tracks; i++) {
			x = findItem(order, order_sorted.at(i));
			tracks.at(x).write(s, config.at(x));
			}
		for (unsigned int i = 0; i < padding; i++) {s.writebyte(0xCD);} // pad to 32
		}
	}

void fmtFCV::open (std::wstring file) {
	bytestream f;
	if (f.openFileW(file)) {

		read(f);

		f.close();
		} else {std::cout << "failed to save file\n";}
	}

void fmtFCV::save (std::wstring file) {
	bytestream s;
	s.resize(size());
	write(s);
	s.writeFileW(file);
	}

