#include "fmtSND.h"


fmtHED_Block5::fmtHED_Block5 () {
	count = 0;
	}

size_t fmtHED_Block5::size () {
	size_t nsize = 0;
	count = data.size();
	if (count > 0) {
		nsize += (data.size() + 1) * 4;

		for (unsigned int i = 0; i < data.size(); i++) {
			nsize += data[i].size;
			}
		//nsize += (32-(nsize % 32)) % 32
		}
	return nsize;
	}

void fmtHED_Block5::read_hed_block5 (bytestream &f, size_t endpos) {

	// Get Start Position
	size_t pos = f.tell();

	// Read Count
	count = f.readUlong();

	// Check Count is Valid
	addrs.clear();
	data.clear();
	std::vector<uint32_t> sizes;
	if (count > 0) {

		// Read Addresses
		addrs = std::vector<uint32_t>(count);
		sizes = std::vector<uint32_t>(count + 1);
		sizes[count] = endpos - pos;
		for (unsigned int i = 0; i < count; i++) {
			addrs[i] = f.readUlong();
			sizes[i] = addrs[i];
			}

		// Create a Size Map
		sort(sizes.begin(), sizes.end());


		// Read Each Buffer
		uint32_t bsize = 0;

		data = std::vector<bytestream>(count);

		for (unsigned int i = 0; i < count; i++) {

			bsize = sizes[(findItem<uint32_t>(sizes, addrs[i])) + 1] - addrs[i];
			if (bsize > 0) {
				data[i].resize(bsize);

				f.seek(pos + addrs[i]);
				for (unsigned int x = 0; x < bsize; x++) {
					data[i].stream[x] = f.readUbyte();
					}
				}
			}
		}
	}

size_t fmtHED_Block5::write_hed_block5 (bytestream &s) {
	size_t ptr = 0;
	count = data.size();
	if (count > 0) {
		ptr += (count + 1) * 4;
		s.writelong(count);
		for (unsigned int i = 0; i < count; i++) {
			s.writelong(ptr);
			ptr += data[i].size;
			}
		for (unsigned int i = 0; i < count; i++) {
			for (unsigned int x = 0; x < data[i].size; x++) {
				s.writebyte(data[i].stream[x]);
				}
			}
		//local pad = (32-(ptr % 32)) % 32
		//for (unsigned int i = 0; i < pad) {s.writebyte(0}}
		////ptr += pad
		}
	return ptr;
	}

fmtHED_SIT::fmtHED_SIT () {
	note = 0;
	lim = 0;
	id2 = 20;
	prio = 127;
	pan = 64;
	vol = 110;
	aux_a = -1 ;
	id1 = 0;
	vol_flag = -1;
	pitch_l = 0;
	pitch_h = 0;
	enc_vol = 0;
	grob = 0;
	srd_type = 1;
	span = 128;
	svol = 110;
	free1 = 0;
	free2 = 0;
	free3 = 0;
	flag = 0x4001;
	}

void fmtHED_SIT::read_sit (bytestream &f) {
	note = f.readUshort();
	lim = f.readbyte();
	id2 = f.readUbyte();
	prio = f.readbyte();
	pan = f.readbyte();
	vol = f.readbyte();
	aux_a = f.readbyte();
	id1 = f.readUbyte();
	vol_flag = f.readbyte();
	pitch_l = f.readshort();
	pitch_h = f.readshort();
	enc_vol = f.readbyte();
	grob = f.readbyte();
	srd_type = f.readUbyte();
	span = f.readbyte();
	svol = f.readbyte();
	free1 = f.readbyte();
	free2 = f.readbyte();
	free3 = f.readbyte();
	flag = f.readUshort();
	}

void fmtHED_SIT::write_sit (bytestream &s) {
	s.writeUshort(note);
	s.writebyte(lim);
	s.writeUbyte(id2);
	s.writebyte(prio);
	s.writebyte(pan);
	s.writebyte(vol);
	s.writebyte(aux_a);
	s.writeUbyte(id1);
	s.writebyte(vol_flag);
	s.writeshort(pitch_l);
	s.writeshort(pitch_h);
	s.writebyte(enc_vol);
	s.writebyte(grob);
	s.writeUbyte(srd_type);
	s.writebyte(span);
	s.writebyte(svol);
	s.writebyte(free1);
	s.writebyte(free2);
	s.writebyte(free3);
	s.writeUshort(flag);
	}

fmtHED_WTADPCM::fmtHED_WTADPCM () {
	for (unsigned int i = 0; i < 16; i++) {
		unk050[i] = 0;
		}
	gain = 0;
	pred_scale = 0;
	yn1 = 0;
	yn2 = 0;
	loop_pred_scale = 1;
	loop_yn1 = 0;
	loop_yn2 = 4;
	}

void fmtHED_WTADPCM::read_wt_adpcm (bytestream &f) {
	for (unsigned int i = 0; i < 16; i++) {
		unk050[i] = f.readshort();
		}
	gain = f.readshort();
	pred_scale = f.readshort();
	yn1 = f.readshort();
	yn2 = f.readshort();
	loop_pred_scale = f.readshort();
	loop_yn1 = f.readshort();
	loop_yn2 = f.readshort();
	}

void fmtHED_WTADPCM::write_wt_adpcm (bytestream &s) {

	for (unsigned int i = 0; i < 16; i++) {
		s.writeshort(unk050[i]);
		}
	s.writeshort(gain);
	s.writeshort(pred_scale);
	s.writeshort(yn1);
	s.writeshort(yn2);
	s.writeshort(loop_pred_scale);
	s.writeshort(loop_yn1);
	s.writeshort(loop_yn2);
	}

fmtHED_WTSAMPLE::fmtHED_WTSAMPLE () {
	format = 0;
	sampleRate = 32000;
	offset = 0;
	length = 0;
	adpcmIndex = 0;
	unk043 = 0;
	}

void fmtHED_WTSAMPLE::read_wt_sample (bytestream &f) {
	format = f.readUshort();
	sampleRate = f.readUshort();
	offset = f.readUlong();
	length = f.readUlong();
	adpcmIndex = f.readUshort();
	unk043 = f.readUshort();
	}

void fmtHED_WTSAMPLE::write_wt_sample (bytestream &s) {
	s.writeshort(format);
	s.writeshort(sampleRate);
	s.writelong(offset);
	s.writelong(length);
	s.writeshort(adpcmIndex);
	s.writeshort(unk043);
	}


fmtHED_WTART::fmtHED_WTART () {
    lfoFreq = 0;
    lfoDelay = 0;
    lfoAtten = 0;
    lfoPitch = 0;
    lfoMod2Atten = 0;
    lfoMod2Pitch = 0;
    eg1Attack = 0;
    eg1Decay = 0;
    eg1Sustain = 0;
    eg1Release = 0;
    eg1Vel2Attack = 0;
    eg1Key2Decay = 0;
    eg2Attack = 0;
    eg2Decay = 0;
    eg2Sustain = 0;
    eg2Release = 0;
    eg2Vel2Attack = 0;
    eg2Key2Decay = 0;
    eg2Pitch = 0;
    pan = 0;
	}

void fmtHED_WTART::read_wt_art (bytestream &f) {
	lfoFreq = f.readlong();
	lfoDelay = f.readlong();
	lfoAtten = f.readlong();
	lfoPitch = f.readlong();
	lfoMod2Atten = f.readlong();
	lfoMod2Pitch = f.readlong();
	eg1Attack = f.readlong();
	eg1Decay = f.readlong();
	eg1Sustain = f.readlong();
	eg1Release = f.readlong();
	eg1Vel2Attack = f.readlong();
	eg1Key2Decay = f.readlong();
	eg2Attack = f.readlong();
	eg2Decay = f.readlong();
	eg2Sustain = f.readlong();
	eg2Release = f.readlong();
	eg2Vel2Attack = f.readlong();
	eg2Key2Decay = f.readlong();
	eg2Pitch = f.readlong();
	pan = f.readlong();
	}

void fmtHED_WTART::write_wt_art (bytestream &s) {
    s.writelong(lfoFreq);
    s.writelong(lfoDelay);
    s.writelong(lfoAtten);
    s.writelong(lfoPitch);
    s.writelong(lfoMod2Atten);
    s.writelong(lfoMod2Pitch);
    s.writelong(eg1Attack);
    s.writelong(eg1Decay);
    s.writelong(eg1Sustain);
    s.writelong(eg1Release);
    s.writelong(eg1Vel2Attack);
    s.writelong(eg1Key2Decay);
    s.writelong(eg2Attack);
    s.writelong(eg2Decay);
    s.writelong(eg2Sustain);
    s.writelong(eg2Release);
    s.writelong(eg2Vel2Attack);
    s.writelong(eg2Key2Decay);
    s.writelong(eg2Pitch);
    s.writelong(pan);
	}

fmtHED_WTREGION::fmtHED_WTREGION () {
	unityNote = 0;
	keyGroup = 0;
	fineTune = 0;
	attn = 0;
	loopStart = 0;
	loopLength = 0;
	articulationIndex = 0;
	sampleIndex = 0;
	}

void fmtHED_WTREGION::read_wt_region (bytestream &f) {
	unityNote = f.readUbyte();
	keyGroup = f.readUbyte();
	fineTune = f.readshort();
	attn = f.readlong();
	loopStart = f.readUlong();
	loopLength = f.readUlong();
	articulationIndex = f.readUlong();
	sampleIndex = f.readUlong();
	}

void fmtHED_WTREGION::write_wt_region (bytestream &s) {
	s.writeUbyte(unityNote);
	s.writeUbyte(keyGroup);
	s.writeshort(fineTune);
	s.writelong(attn);
	s.writeUlong(loopStart);
	s.writeUlong(loopLength);
	s.writeUlong(articulationIndex);
	s.writeUlong(sampleIndex);
	}

fmtHED_WTFILEHEADER::fmtHED_WTFILEHEADER () {
	offsetPercussiveInst = 0;
	offsetMelodicInst = 0;
	offsetRegions = 0;
	offsetArticulations = 0;
	offsetSamples = 0;
	offsetAdpcmContext = 0;
	}

size_t fmtHED_WTFILEHEADER::size () {
	/*
		recalculates the pointers aswell
	*/

	size_t nsize = 24; // pointer table

	offsetPercussiveInst = nsize;

	// table1 {indicies}
	offsetMelodicInst = nsize;
	nsize += table1.size() * 2;
	nsize += (4-(nsize % 4)) % 4;

	// region
	offsetRegions = nsize;
	nsize += region.size() * 24;

	// art
	offsetArticulations = nsize;
	nsize += art.size() * 80;

	// sample
	offsetSamples = nsize;
	nsize += sample.size() * 16;

	// adpcm
	offsetAdpcmContext = nsize;
	nsize += adpcm.size() * 46;

	// pad block to 16
	//nsize += mod {16-{mod {adpcm.size() * 46} 16}} 16

	return nsize;
	}

void fmtHED_WTFILEHEADER::read_wt_fileheader (bytestream &f, size_t end_pos) {
	size_t pos = f.tell();

	offsetPercussiveInst = f.readUlong();

	if (offsetPercussiveInst == 24) {

		offsetMelodicInst = f.readUlong();
		offsetRegions = f.readUlong();
		offsetArticulations = f.readUlong();
		offsetSamples = f.readUlong();
		offsetAdpcmContext = f.readUlong();

		unsigned int count1 = (unsigned int)((offsetRegions - offsetMelodicInst) / 2);
		if (offsetMelodicInst > 0 && count1 > 0) {
			f.seek(pos + offsetMelodicInst);
			table1 = std::vector<int16_t>(count1);

			for (unsigned int i = 0; i < count1; i++) {
				table1[i] = f.readshort();
				}

			// check last index is not 0, it may be a dummy
			if (table1[count1 - 1] == 0) {
				table1.pop_back();
				count1--;
				}
			}

		unsigned int count2 = (unsigned int)((offsetArticulations - offsetRegions) / 24);
		if (offsetRegions > 0 && count2 > 0) {

			f.seek(pos + offsetRegions);
			region = std::vector<fmtHED_WTREGION>(count2);
			for (unsigned int i = 0; i < count2; i++) {
				region[i].read_wt_region(f);
				}
			}

		unsigned int count3 = (unsigned int)((offsetSamples - offsetArticulations) / 80);
		if (offsetArticulations > 0 && count3 > 0) {

			f.seek(pos + offsetArticulations);
			art = std::vector<fmtHED_WTART>(count3);
			for (unsigned int i = 0; i < count3; i++) {
				art[i].read_wt_art(f);
				}
			}

		unsigned int count4 = (unsigned int)((offsetAdpcmContext - offsetSamples) / 16);
		if (offsetSamples > 0 && count4 > 0) {
			f.seek(pos + offsetSamples);
			sample = std::vector<fmtHED_WTSAMPLE>(count4);
			for (unsigned int i = 0; i < count4; i++) {
				sample[i].read_wt_sample(f);
				}
			}

		unsigned int count5 = (unsigned int)((end_pos - (pos + offsetAdpcmContext)) / 46);
		if (offsetAdpcmContext > 0 && count5 > 0) {

			f.seek(pos + offsetAdpcmContext);
			adpcm = std::vector<fmtHED_WTADPCM>(count5);
			for (unsigned int i = 0; i < count5; i++) {
				adpcm[i].read_wt_adpcm(f);
				}
			}


		} else {std::cout << "ERROR: \tUnexpected Table Address {" << offsetPercussiveInst << "}\n";}

	}

size_t fmtHED_WTFILEHEADER::write_wt_fileheader (bytestream &s) {


	size_t nsize = 24;

	s.writelong(offsetPercussiveInst = nsize);

	s.writelong(offsetMelodicInst = nsize);
	nsize += table1.size() * 2;
	size_t table1_pad = (4-(nsize % 4)) % 4;
	nsize += table1_pad;

	s.writelong(offsetRegions = nsize);
	nsize += region.size() * 24;

	s.writelong(offsetArticulations = nsize);
	nsize += art.size() * 80;

	s.writelong(offsetSamples = nsize);
	nsize += sample.size() * 16;

	s.writelong(offsetAdpcmContext = nsize);
	nsize += adpcm.size() * 46;

	//local adpcm_pad = mod {16-{mod {adpcm.size() * 46} 16}} 16
	//nsize += adpcm_pad
	//std::cout << "adpcm_pad Check: \t%\n" nsize

	for (unsigned int i = 0; i < table1.size(); i++) {
		s.writeshort(table1[i]);
		}

	for (unsigned int i = 0; i < table1_pad; i++) {
		s.writebyte(0);
		}

	for (unsigned int i = 0; i < region.size(); i++) {
		region[i].write_wt_region(s);
		}

	for (unsigned int i = 0; i < art.size(); i++) {
		art[i].write_wt_art(s);
		}

	for (unsigned int i = 0; i < sample.size(); i++) {
		sample[i].write_wt_sample(s);
		}

	for (unsigned int i = 0; i < adpcm.size(); i++) {
		adpcm[i].write_wt_adpcm(s);
		}

	//for (unsigned int i = 0; i < adpcm_pad) {
	//	s.writebyte{0}
	//	}

	return nsize;
	}

fmtHED_Block2_Entry::fmtHED_Block2_Entry () {
	index = -1;
	count = 0;
	unk004 = -1;
	}

size_t fmtHED_Block2_Entry::size () {
	size_t nsize = 0;
	if (unk005.size() > 0) {
		nsize = 4 + (unk005.size() * 2);
		}
	return nsize;
	}

void fmtHED_Block2_Entry::read_hed_block2_entry (bytestream &f) {
	count = f.readshort();
	unk004 = f.readshort();

	if (unk004 != -1) {
		std::cout << "Unexpected Count {" << unk004 << "}\n" ;
		}

	unk005.clear();
	if (count > 0) {
		unk005 = std::vector<uint16_t>(count);
		for (unsigned int i = 0; i < count; i++) {
			unk005[i] = f.readshort();
			}
		}
	}

void fmtHED_Block2_Entry::write_hed_block2_entry (bytestream &s) {
	count = unk005.size();
	if (count > 0) {
		s.writeshort(count);
		s.writeshort(unk004);
		for (unsigned int i = 0; i < count; i++) {
			s.writeshort(unk005[i]);
			}
		}
	}

fmtHED_Block2::fmtHED_Block2 () {
	forceWrite = false;
	}

size_t fmtHED_Block2::size () {
	size_t nsize = 0;
	unsigned int count = entry.size();
	for (unsigned int i = 0; i < count; i++) {
		nsize += entry[i].size();
		}
	if (nsize > 0 || forceWrite) {
		nsize += 128;
		nsize += (32-(nsize % 32)) % 32;
		}
	return nsize;
	}

void fmtHED_Block2::read_hed_block2 (bytestream &f) {
	size_t pos = f.tell();
	uint32_t addrs[32];
	unsigned int count = 0;
	for (unsigned int i = 0; i < 32; i++) {
		addrs[i] = f.readUlong();
		if (addrs[i] > 0) {
			count++;
			}
		}
	entry.clear();
	if (count > 0) {
		entry = std::vector<fmtHED_Block2_Entry>(count);
		unsigned int index = 0;
		for (unsigned int i = 0; i < 32; i++) {
			if (addrs[i] > 0) {
				f.seek(pos + addrs[i]);
				entry[index].read_hed_block2_entry(f);
				entry[index].index = i;
				index++;
				}
			}
		}
	}

size_t fmtHED_Block2::write_hed_block2 (bytestream &s) {
	size_t ptr = 0;


	if (size() > 0 || forceWrite) {

		// Add Header Size
		ptr = 128;

		// Recalculate Addresses

		uint32_t addrs[32];
		for (unsigned int i = 0; i < 32; i++) {addrs[i] = 0;}

		unsigned int count = entry.size();

		std::vector<bool> writeblocks;
		if (count > 0) {

			std::vector<uint32_t> used_indices;
			int index = 0;
			size_t bsize = 0;
			writeblocks = std::vector<bool>(count);
			for (unsigned int i = 0; i < count; i++) {
				writeblocks[i] = false;

				if (entry[i].index > -1 && entry[i].index < 32) {
					index = findItem<uint32_t>(used_indices, entry[i].index);

					bsize = entry[i].size();

					if (index == -1 && bsize > 0) {
						addrs[entry[i].index] = ptr;
						ptr += bsize;
						writeblocks[i] = true;
						used_indices.push_back(index);
						}
					}
				}
			}

		// Write Address Table
		for (unsigned int i = 0; i < 32; i++) {
			s.writelong(addrs[i]);
			}

		// Write Data
		for (unsigned int i = 0; i < count; i++) {
			if (writeblocks[i]) {
				entry[i].write_hed_block2_entry(s);
				}
			}

		// Write Padding
		size_t pad = (32-(ptr % 32)) % 32;
		for (unsigned int i = 0; i < pad; i++) {
			s.writebyte(0);
			}

		ptr += pad;
		}

	return ptr;
	}

fmtHED_Block1::fmtHED_Block1 () {
	count = 0;
	block3_addr = 16;
	sit_addr = 0;
	block5_addr = 0;
	}

size_t fmtHED_Block1::size () {
	size_t nsize = 16;
	nsize += block3.size();
	nsize += (16-((block3.size()) % 16)) % 16; // pad

	nsize += sit.size() * 24;
	nsize += (16-((sit.size() * 24) % 16)) % 16; // pad

	nsize += block5.size();
	nsize += (16-((block5.size()) % 16)) % 16; // pad

	return nsize;
	}

void fmtHED_Block1::read_hed_block1 (bytestream &f, size_t endpos) {
	size_t pos = f.tell();

	count = f.readUlong();
	block3_addr = f.readUlong();
	sit_addr = f.readUlong();
	block5_addr = f.readUlong();

	sit.clear();
	if (count > 0) {

		if (block3_addr > 0) {
			f.seek(pos + block3_addr);
			block3.read_wt_fileheader(f, pos + sit_addr);
			}

		if (sit_addr > 0) {
			f.seek(pos + sit_addr);
			sit = std::vector<fmtHED_SIT>(count);
			for (unsigned int i = 0; i < count; i++) {
				sit[i].read_sit(f);
				}
			}

		if (block5_addr > 0) {
			f.seek(pos + block5_addr);
			block5.read_hed_block5(f, endpos); // I need to stick the end size here
			}

		}
	}

size_t fmtHED_Block1::write_hed_block1 (bytestream &s) {
	size_t bsize = 0;
	size_t ptr = 16;

	// Sub Header
	count = sit.size();
	s.writelong(count);

	// Block3 Addr
	bsize = block3.size();
	if (bsize > 0) {s.writelong(block3_addr = ptr);} else {s.writelong(0);}

	size_t block3_pad = (16-(bsize % 16)) % 16;
	ptr += bsize + block3_pad;

	// Block4 Addr
	bsize = count * 24;
	if (bsize > 0) {s.writelong(sit_addr = ptr);} else {s.writelong(0);}
	size_t block4_pad = (16-(bsize % 16)) % 16;
	ptr += bsize + block4_pad;

	// Block5 Addr
	bsize = block5.size();
	if (bsize > 0) {s.writelong(block5_addr = ptr);} else {s.writelong(0);}
	size_t block5_pad = (16-(bsize % 16)) % 16;
	ptr += bsize + block5_pad;

	// Block 3
	block3.write_wt_fileheader(s);
	for (unsigned int i = 0; i < block3_pad; i++) {s.writebyte(0);}

	// Block 4
	for (unsigned int i = 0; i < count; i++) {sit[i].write_sit(s);}
	for (unsigned int i = 0; i < block4_pad; i++) {s.writebyte(0);}

	// Block 5
	block5.write_hed_block5(s);
	for (unsigned int i = 0; i < block5_pad; i++) {s.writebyte(0);}

	return ptr;
	}

fmtHED::fmtHED () {
	block1_addr = 32;
	block2_addr = 0;
	}

size_t fmtHED::size () {
	size_t nsize = 0;
	size_t bsize = block2.size();
	if (bsize > 0) {nsize = 32;}

	nsize += block1.size();
	nsize += (32-(nsize % 32)) % 32;


	if (bsize > 0) {
		nsize += bsize;
		nsize += (32-(nsize % 32)) % 32;
		}

	return nsize;
	}

void fmtHED::read_hed (bytestream &f, size_t endpos) {
	size_t pos = f.tell();

	block1_addr = f.readUlong();
	block2_addr = f.readUlong();

	if (block1_addr == 0x20 && block2_addr != 0x10) {

		if (block1_addr > 0) {
			f.seek(pos + block1_addr);

			size_t block2_end = block2_addr;
			if (block2_end > 0) {
				block2_end += pos;
				}
			else {
				block2_end = endpos;
				}

			block1.read_hed_block1(f, block2_end);

			}

		if (block2_addr > 0) {
			f.seek(pos + block2_addr);

			block2.read_hed_block2(f);
			block2.forceWrite = true;
			}
		}
	else {
		block1_addr = 0;
		block2_addr = 0;
		f.seek(pos);
		block1.read_hed_block1(f, endpos);
		}
	}

size_t fmtHED::write_hed (bytestream &s) {

	size_t ptr = 32;

	// Sub Header
	unsigned int block1_size = block1.size();
	unsigned int block2_size = block2.size();
	size_t block1_pad = 0;
	size_t block2_pad = 0;

	if (block2_size > 0) { // Write Header
		s.writelong(block1_addr = ptr);
		ptr += block1_size;
		block1_pad = (32-(ptr % 32)) % 32;
		ptr += block1_pad;

		if (block2_size > 0) {
			s.writelong(block2_addr = ptr);
			ptr += block2_size;
			block2_pad = (32-(ptr % 32)) % 32;
			ptr += block2_pad;
			}
		else {
			s.writelong(0);
			}

		for (unsigned int i = 0; i < 6; i++) {s.writelong(0);} // padd to 32 bytes
		}

	// Block 1
	block1.write_hed_block1(s);
	for (unsigned int i = 0; i < block1_pad; i++) {s.writebyte(0);} // padd to 32 bytes

	if (block2_size > 0) {
		block2.write_hed_block2(s);
		for (unsigned int i = 0; i < block2_pad; i++) {s.writebyte(0);}
		}
	return ptr;
	}

size_t fmtDSP::size () {
	return buffer.size;
	}

void fmtDSP::read_dsp (bytestream &f, size_t bsize) {
	buffer.close();
	if (bsize > 0) {
		buffer.resize(bsize);
		for (unsigned int i = 0; i < bsize; i++) {
			buffer.stream[i] = f.readUbyte();
			}
		}
	}

size_t fmtDSP::write_dsp (bytestream &s) {
	size_t bsize = buffer.size;
	for (unsigned int i = 0; i < bsize; i++) {
		s.writebyte(buffer.stream[i]);
		}
	return bsize;
	}

fmtSND_Entry::fmtSND_Entry () {
	id = 0;
	}

void fmtSND_Entry::read_snd_entry (bytestream &f, size_t &pos, fmtUDAS_Entry &hed_entry, fmtUDAS_Entry &dsp_entry) {
	id = hed_entry.unk005;

	f.seek(pos + hed_entry.addr);
	hed.read_hed(f, pos + hed_entry.addr + hed_entry.size);

	f.seek(pos + dsp_entry.addr);
	dsp.read_dsp(f, dsp_entry.size);
	}

void fmtSND_Entry::write_snd_hed_entry (bytestream &s) {
	hed.write_hed(s);
	}

void fmtSND_Entry::write_snd_dsp_entry (bytestream &s) {
	dsp.write_dsp(s);
	}

fmtSND::fmtSND () {
	fileid = 0;
	}

size_t fmtSND::size () {
	unsigned int count = playlists.size();
	size_t nsize = ((count * 2) + 2) * 32;
	nsize += (1024-(nsize % 1024)) % 1024;
	for (unsigned int i = 0; i < count; i++) {
		nsize += playlists[i].hed.size();
		nsize += (32-((playlists[i].hed.size()) % 32)) % 32;

		nsize += playlists[i].dsp.size();
		nsize += (32-((playlists[i].dsp.size()) % 32)) % 32;
		}
	return nsize;
	}

bool fmtSND::read_snd (bytestream &f) {

	// Set Default Pass State
	bool isGood = false;

	// Get Start Position
	size_t pos = f.tell();

	// Check Position is valid
	if (f.size > 0 && pos < f.size) {


		// Read Das
		isGood = das.read_udas(f);

		// Look for the Audio Pairs; Header + Data
		signed int hed_index = -1;
		signed int dsp_index = -1;
		unsigned int count = das.asset.size();
		unsigned int audio_count = 0;
		for (unsigned int i = 0; i < count; i++) {
			if (das.asset[i].addr > 0) {
				switch (das.asset[i].type) {
					case 1: {hed_index = i; break;} // HED
					case 2: {dsp_index = i; break;} // DSP
					}
				if (hed_index > -1 && dsp_index > -1) {audio_count++;}
				}
			}
		if (audio_count > 0) {
			playlists = std::vector<fmtSND_Entry>(audio_count);
			unsigned int audio_index = 0;
			for (unsigned int i = 0; i < count; i++) {

				// This number is unknown; store it for later
				fileid = das.asset[i].unk006;

				// Check that address is Valid {Size May be 0}
				if (das.asset[i].addr > 0) {

					// Assign Indices of each pair
					switch (das.asset[i].type) {
						case 1: {hed_index = i; break;} // HED
						case 2: {dsp_index = i; break;} // DSP
						}

					// When both Indices are valid; then we assume they are paired {this is probably not the ideal way to match pairs}
					if (hed_index > -1 && dsp_index > -1) {

						// Seek to Asset Position
						f.seek(pos + das.asset[i].addr);

						// Read Audio

						playlists[audio_index].read_snd_entry(f, pos, das.asset[hed_index], das.asset[dsp_index]);

						// Null Indices again to restart the pairing process
						hed_index = -1;
						dsp_index = -1;

						audio_index++;
						}
					}
				}

			}
		}
	return isGood;
	}

void fmtSND::write_snd (bytestream &s) {
	/*
		update all the pointers
	*/

	// Write DAS Header
	unsigned int count = playlists.size();
	uint32_t magic = 3400973856;
	size_t ptr = ((count * 2) + 2) * 32;

	size_t pad = (1024-(ptr % 1024)) % 1024;
	ptr += pad;
	size_t init_addr = ptr;

	for (unsigned int i = 0; i < 8; i++) {
		s.writeUlong(magic);
		}

	// Write Data Entries
	size_t bsize = 0;
	for (unsigned int i = 0; i < count; i++) {
		bsize = playlists[i].hed.size();
		s.writelong(1); // type
		s.writelong(bsize); // size
		s.writelong(0); // flag
		s.writelong(ptr); // addr
		s.writelong(playlists[i].id);
		s.writelong(fileid);
		s.writelong(0);
		s.writelong(0);
		ptr += bsize;
		ptr += (32-(bsize % 32)) % 32;

		bsize = playlists[i].dsp.size();
		s.writelong(2);
		s.writelong(bsize);
		s.writelong(0);
		if (bsize > 0) {s.writelong(ptr);} else {s.writelong(init_addr);}
		s.writelong(playlists[i].id);
		s.writelong(fileid);
		s.writelong(0);
		s.writelong(0);
		ptr += bsize;
		ptr += (32-(bsize % 32)) % 32;
		}

	// Write Terminator
	s.writelong(-1);
	for (unsigned int i = 0; i < 7; i++) {
		s.writelong(0);
		}

	// Write Padding
	for (unsigned int i = 0; i < pad; i++) {
		s.writebyte(0);
		}

	// Write Each Resource
	for (unsigned int i = 0; i < count; i++) {
		playlists[i].hed.write_hed(s);
		pad = (32-((playlists[i].hed.size()) % 32)) % 32;
		for (unsigned int p = 0; p < pad; p++) {s.writebyte(0);}

		if (playlists[i].dsp.size() > 0) {
			playlists[i].dsp.write_dsp(s);
			pad = (32-((playlists[i].dsp.size()) % 32)) % 32;
			for (unsigned int p = 0; p < pad; p++) {s.writebyte(0);}
			}

		}


	}

size_t fmtDAT_SND_Package::size () {
	size_t nsize = 0;
	for (unsigned int i = 0; i < snd.size(); i++) {
		nsize += snd[i].size();
		}
	return nsize;
	}

bool fmtDAT_SND_Package::read_dat_snd (bytestream &f) {
	bool isGood = false;
	size_t pos = f.tell();
	if (f.size > pos + 32) {
		// Read UDAS, get Largest Address in order to skip past it.
		size_t udas_pos;
		size_t max_addr;
		unsigned long udas_count = 0;
		signed long res_flag;
		size_t res_addr;
		size_t res_size;
		bool udas_valid;
		while (!f.eos()) {
			udas_pos = f.tell();
			max_addr = udas_pos;
			udas_valid = true;
			uint32_t c1 = f.readlong();
			uint32_t c2;
			for (unsigned int i = 0; i < 7; i++) {
				c2 = f.readUlong();
				if (c1 != c2) {
					udas_valid = false;
					break;
					}
				}
			f.seek(udas_pos);
			if (udas_valid) {
				max_addr = 32;
				f.seek(udas_pos + max_addr);
				while (f.tell() + 64 < f.size) {
					res_flag = f.readlong();
					if (res_flag == -1) {break;}
					res_size = f.readUlong();
					f.seek(4, seek::cur);
					res_addr = f.readUlong();
					f.seek(16, seek::cur);

					if (res_size > 0 && res_addr + res_size > max_addr) {
						max_addr = res_addr + res_size;
						}

					}
				udas_count++;
				f.seek(udas_pos + max_addr + ((32-((max_addr) % 32)) % 32));
				}
			else {
				std::cout << "ERROR: \tUDAS Signature Failure\n";
				break;
				}
			}
		if (udas_count > 0) {

			f.seek(pos);
			unsigned int c = 0;
			size_t endpos = 0;
			size_t bsize = 0;
			snd = std::vector<fmtSND>(udas_count);
			while (f.tell() + 64 < f.size) {
				pos = f.tell();


				//std::cout << "SND Found At: \t" << pos << std::endl;
				if (!snd[c].read_snd(f)) {

					std::cout << "ERROR: \tFailed to Read DAS; Aborted\n";
					//break;

					}

				endpos = pos;

				for (unsigned int i = 0; i < snd[c].das.asset.size(); i++) {
					bsize = pos + snd[c].das.asset[i].addr + snd[c].das.asset[i].size;
					if (bsize > endpos) {
						endpos = bsize;
						}
					}

				f.seek(endpos + ((32-(endpos % 32)) % 32));

				c++;
				}

			}

		} else {std::cout << "Insufficient File Size\n";}
	return isGood;
	}

void fmtDAT_SND_Package::write_dat_snd (bytestream &s) {
	for (unsigned int i = 0; i < snd.size(); i++) {
		snd[i].write_snd(s);
		}
	size_t pad = (32-((s.tell()) % 32)) % 32;
	for (unsigned int i = 0; i < pad; i++) {s.writebyte(0);}
	}

void fmtDAT_SND_Package::xml_export (std::wstring file) {
	/* copies the variables into an XML text */

	std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

	unsigned int udas_count = snd.size();
	if (udas_count == 0) {return;}

	// XML header


	// XML Root Node
	xml += "<snd name=\"" + wstring_to_string(getFilenameFileW(file)) + ".snd\" files=\"" + to_string(udas_count) + "\">\n";

	// Define SND, as there may be multiple embedded ones
	unsigned int audio_pair_count = 0;
	unsigned int table_count = 0;
	unsigned int subtable_count = 0;
	const unsigned int b64_stride = 64;
	unsigned int b64_breaks;
	unsigned int b64_len;
	unsigned int data_len;
	unsigned int b64_leftover = 0;
	std::string data;
	for (unsigned int i = 0; i < snd.size(); i++) {
		xml += "    <file room=\"" + to_string(snd[i].fileid) + "\">\n";

		// Define the HED and DSP pairs within the SND
		audio_pair_count = snd[i].playlists.size();
		for (unsigned int x = 0; x < audio_pair_count; x++) {
			xml += "        <asset id=\"" + to_string(snd[i].playlists[x].id) + "\">\n";

			table_count = snd[i].playlists[x].hed.block1.block3.table1.size();
			if (table_count > 0) {
				xml += "            <block1 count=\"" + to_string(table_count) + "\">\n                <!-- 2 Bytes Per-->\n";
				for (unsigned int d = 0; d < table_count; d++) {
					xml += "                <entry>" + to_string(snd[i].playlists[x].hed.block1.block3.table1[d]) + "</entry>\n";
					}
				xml += "            </block1>\n";
				}

			table_count = snd[i].playlists[x].hed.block1.block3.region.size();
			if (table_count > 0) {
				xml += "            <region count=\"" + to_string(table_count) + "\">\n                <!--24 Bytes Per-->\n";
				for (unsigned int d = 0; d < table_count; d++) {
					xml += "                <entry index=\"" + to_string(d) + "\">\n";
					xml += "                    <unityNote>" + to_string((int)snd[i].playlists[x].hed.block1.block3.region[d].unityNote) + "</unityNote>\n";
					xml += "                    <keyGroup>" + to_string((int)snd[i].playlists[x].hed.block1.block3.region[d].keyGroup) + "</keyGroup>\n";
					xml += "                    <fineTune>" + to_string(snd[i].playlists[x].hed.block1.block3.region[d].fineTune) + "</fineTune>\n";
					xml += "                    <attn>" + to_string(snd[i].playlists[x].hed.block1.block3.region[d].attn) + "</attn>\n";
					xml += "                    <loopStart>" + to_string(snd[i].playlists[x].hed.block1.block3.region[d].loopStart) + "</loopStart>\n";
					xml += "                    <loopLength>" + to_string(snd[i].playlists[x].hed.block1.block3.region[d].loopLength) + "</loopLength>\n";
					xml += "                    <articulationIndex>" + to_string(snd[i].playlists[x].hed.block1.block3.region[d].articulationIndex) + "</articulationIndex>\n";
					xml += "                    <sampleIndex>" + to_string(snd[i].playlists[x].hed.block1.block3.region[d].sampleIndex) + "</sampleIndex>\n";
					xml += "                </entry>\n";
					}
				xml += "            </region>\n";
				}


			table_count = snd[i].playlists[x].hed.block1.block3.art.size();
			if (table_count > 0) {
				xml += "            <articulation count=\"" + to_string(table_count) + "\">\n                <!--80 Bytes Per-->\n";
				for (unsigned int d = 0; d < table_count; d++) {
					xml += "                <entry index=\"" + to_string(d) + "\">\n";
					xml += "                    <lfoFreq>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].lfoFreq) + "</lfoFreq>\n";
					xml += "                    <lfoDelay>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].lfoDelay) + "</lfoDelay>\n";
					xml += "                    <lfoAtten>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].lfoAtten) + "</lfoAtten>\n";
					xml += "                    <lfoPitch>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].lfoPitch) + "</lfoPitch>\n";
					xml += "                    <lfoMod2Atten>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].lfoMod2Atten) + "</lfoMod2Atten>\n";
					xml += "                    <lfoMod2Pitch>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].lfoMod2Pitch) + "</lfoMod2Pitch>\n";
					xml += "                    <eg1Attack>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg1Attack) + "</eg1Attack>\n";
					xml += "                    <eg1Decay>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg1Decay) + "</eg1Decay>\n";
					xml += "                    <eg1Sustain>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg1Sustain) + "</eg1Sustain>\n";
					xml += "                    <eg1Release>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg1Release) + "</eg1Release>\n";
					xml += "                    <eg1Vel2Attack>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg1Vel2Attack) + "</eg1Vel2Attack>\n";
					xml += "                    <eg1Key2Decay>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg1Key2Decay) + "</eg1Key2Decay>\n";
					xml += "                    <eg2Attack>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg2Attack) + "</eg2Attack>\n";
					xml += "                    <eg2Decay>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg2Decay) + "</eg2Decay>\n";
					xml += "                    <eg2Sustain>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg2Sustain) + "</eg2Sustain>\n";
					xml += "                    <eg2Release>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg2Release) + "</eg2Release>\n";
					xml += "                    <eg2Vel2Attack>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg2Vel2Attack) + "</eg2Vel2Attack>\n";
					xml += "                    <eg2Key2Decay>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg2Key2Decay) + "</eg2Key2Decay>\n";
					xml += "                    <eg2Pitch>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].eg2Pitch) + "</eg2Pitch>\n";
					xml += "                    <pan>" + to_string(snd[i].playlists[x].hed.block1.block3.art[d].pan) + "</pan>\n";
					xml += "                </entry>\n";
					}
				xml += "            </articulation>\n";
				}

			table_count = snd[i].playlists[x].hed.block1.block3.sample.size();
			if (table_count > 0) {
				xml += "            <sample count=\"" + to_string(table_count) + "\">\n                <!--16 Bytes Per-->\n";
				for (unsigned int d = 0; d < table_count; d++) {
					xml += "                <entry index=\"" + to_string(d) + "\">\n";
					xml += "                    <format>" + to_string(snd[i].playlists[x].hed.block1.block3.sample[d].format) + "</format>\n";
					xml += "                    <sampleRate>" + to_string(snd[i].playlists[x].hed.block1.block3.sample[d].sampleRate) + "</sampleRate>\n";
					xml += "                    <offset>" + to_string(snd[i].playlists[x].hed.block1.block3.sample[d].offset) + "</offset>\n";
					xml += "                    <length>" + to_string(snd[i].playlists[x].hed.block1.block3.sample[d].length) + "</length>\n";
					xml += "                    <adpcmIndex>" + to_string(snd[i].playlists[x].hed.block1.block3.sample[d].adpcmIndex) + "</adpcmIndex>\n";
					xml += "                    <unk043>" + to_string(snd[i].playlists[x].hed.block1.block3.sample[d].unk043) + "</unk043>\n";
					xml += "                </entry>\n";
					}
				xml += "            </sample>\n";
				}


			table_count = snd[i].playlists[x].hed.block1.block3.adpcm.size();
			if (table_count > 0) {
				xml += "            <adpcm count=\"" + to_string(table_count) + "\">\n                <!--46 Bytes Per-->\n";
				for (unsigned int d = 0; d < table_count; d++) {
					xml += "                <entry index=\"" + to_string(d) + "\">\n";
					subtable_count = 16;



					//xml += "                    <unk050 count=\"" + to_string(subtable_count) + "\">\n";
					//for (unsigned int j = 0; j < subtable_count; j++) {
					//	xml += "                        <data>" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].unk050[j]) +"</data>\n";
					//	}
					//xml += "                    </unk050>\n";

					for (unsigned int j = 0; j < subtable_count; j++) {
						xml += "                    <unk0" + to_string(50 + j) + ">" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].unk050[j]) + "</unk0" + to_string(50 + j) + ">\n";
						}
					xml += "                    <gain>" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].gain) + "</gain>\n";
					xml += "                    <pred_scale>" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].pred_scale) + "</pred_scale>\n";
					xml += "                    <yn1>" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].yn1) + "</yn1>\n";
					xml += "                    <yn2>" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].yn2) + "</yn2>\n";
					xml += "                    <loop_pred_scale>" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].loop_pred_scale) + "</loop_pred_scale>\n";
					xml += "                    <loop_yn1>" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].loop_yn1) + "</loop_yn1>\n";
					xml += "                    <loop_yn2>" + to_string(snd[i].playlists[x].hed.block1.block3.adpcm[d].loop_yn2) + "</loop_yn2>\n";
					xml += "                </entry>\n";
					}
				xml += "            </adpcm>\n";
				}


			table_count = snd[i].playlists[x].hed.block1.sit.size();
			if (table_count > 0) {
				xml += "            <sit count=\"" + to_string(table_count) + "\">\n                <!--24 Bytes Per-->\n";
				for (unsigned int d = 0; d < table_count; d++) {
					xml += "                <entry index=\"" + to_string(d) + "\">\n";
					xml += "                    <note>" + to_string(snd[i].playlists[x].hed.block1.sit[d].note) + "</note>\n";
					xml += "                    <lim>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].lim) + "</lim>\n";
					xml += "                    <id2>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].id2) + "</id2>\n";
					xml += "                    <prio>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].prio) + "</prio>\n";
					xml += "                    <pan>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].pan) + "</pan>\n";
					xml += "                    <vol>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].vol) + "</vol>\n";
					xml += "                    <aux_a>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].aux_a) + "</aux_a>\n";
					xml += "                    <id1>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].id1) + "</id1>\n";
					xml += "                    <vol_flag>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].vol_flag) + "</vol_flag>\n";
					xml += "                    <pitch_l>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].pitch_l) + "</pitch_l>\n";
					xml += "                    <pitch_h>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].pitch_h) + "</pitch_h>\n";
					xml += "                    <enc_vol>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].enc_vol) + "</enc_vol>\n";
					xml += "                    <grob>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].grob) + "</grob>\n";
					xml += "                    <srd_type>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].srd_type) + "</srd_type>\n";
					xml += "                    <span>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].span) + "</span>\n";
					xml += "                    <svol>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].svol) + "</svol>\n";
					xml += "                    <free1>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].free1) + "</free1>\n";
					xml += "                    <free2>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].free2) + "</free2>\n";
					xml += "                    <free3>" + to_string((int)snd[i].playlists[x].hed.block1.sit[d].free3) + "</free3>\n";
					xml += "                    <flag>" + to_string(snd[i].playlists[x].hed.block1.sit[d].flag) + "</flag>\n";
					xml += "                </entry>\n";
					}
				xml += "            </sit>\n";
				}

			table_count = snd[i].playlists[x].hed.block2.entry.size();
			if (table_count > 0 || snd[i].playlists[x].hed.block2.forceWrite) {
				xml += "            <block7 count=\"" + to_string(table_count) + "\">\n                <!--128 + N Bytes Per-->\n";
				for (unsigned int d = 0; d < table_count; d++) {
					xml += "                <entry index=\"" + to_string(d) + "\">\n";
					xml += "                    <index>" + to_string(snd[i].playlists[x].hed.block2.entry[d].index) + "</index>\n";
					xml += "                    <unk004>" + to_string(snd[i].playlists[x].hed.block2.entry[d].unk004) + "</unk004>\n";
					subtable_count = snd[i].playlists[x].hed.block2.entry[d].unk005.size();

					xml += "                    <unk005 count=\"" + to_string(subtable_count) + "\">\n";
					for (unsigned int j = 0; j < subtable_count; j++) {
						xml += "                        <data>" + to_string(snd[i].playlists[x].hed.block2.entry[d].unk005[j]) +"</data>\n";
						}
					xml += "                    </unk005>\n";

					xml += "                </entry>\n";
					}
				xml += "            </block7>\n";
				}


			table_count = snd[i].playlists[x].hed.block1.block5.data.size();
			if (table_count > 0) {
				xml += "            <block8 count=\"" + to_string(table_count) + "\">\n                <!-- N Bytes Per-->\n";
				for (unsigned int d = 0; d < table_count; d++) {
					b64_len = 0;
					data_len = snd[i].playlists[x].hed.block1.block5.data[d].size;
					if (data_len > 0) {
						data = snd[i].playlists[x].hed.block1.block5.data[d].base64_encode();
						b64_len = data.size();
						xml += "                <entry index=\"" + to_string(d) + "\"  encoding=\"base64\" size=\"" + to_string(data_len) + "\">";
						if (b64_len > 0) {
							b64_breaks = b64_len / b64_stride;
							b64_leftover = b64_len - (b64_breaks * b64_stride);

							for (unsigned int c = 0; c < b64_breaks; c++) {

								xml += "\n                    ";
								for (unsigned int j = 0; j < b64_stride; j++) {
									xml += data[(c * b64_stride) + j];
									}
								}
							if (b64_leftover > 0) {

								xml += "\n                    ";
								for (unsigned int j = 0; j < b64_leftover; j++) {
									xml += data[b64_breaks + j];
									}
								}
							}
						}
					xml += "\n                </entry>\n";
					data.clear();
					}
				xml += "            </block8>\n";
				}

			data_len = snd[i].playlists[x].dsp.buffer.size;
			if (data_len > 0) {
				data = snd[i].playlists[x].dsp.buffer.base64_encode();
				b64_len = data.size();
				if (b64_len > 0) {
					xml += "            <block9 encoding=\"base64\" size=\"" + to_string(data_len) + "\">\n                <!-- N Bytes -->";
					b64_breaks = b64_len / b64_stride;
					b64_leftover = b64_len - (b64_breaks * b64_stride);

					for (unsigned int d = 0; d < b64_breaks; d++) {

						xml += "\n                ";
						for (unsigned int j = 0; j < b64_stride; j++) {
							xml += data[(d * b64_stride) + j];
							}
						}
					if (b64_leftover > 0) {

						xml += "\n                ";
						for (unsigned int j = 0; j < b64_leftover; j++) {
							xml += data[b64_breaks + j];
							}
						}

					xml += "\n            </block9>\n";
					data.clear();
					}
				}


			xml += "        </asset>\n";
			}

		xml += "    </file>\n";
		}


	// Close XML Root Node
	xml += "</snd>\n";

	// Save File
	bytestream s;
	s.writeFileW(file, 0, xml.size(), (char*)xml.c_str());

	}

void fmtDAT_SND_Package::xml_import (rapidxml::xml_document<> &doc) {

	// Check Root Node
	rapidxml::xml_node<>* NODE_SND = doc.first_node("snd");
	if (NODE_SND == NULL) {return;}

	// Count File Nodes
	int FILE_NUM = 0;
	for (rapidxml::xml_node<>* NODE_FILE = NODE_SND->first_node("file"); NODE_FILE; NODE_FILE = NODE_FILE->next_sibling()) {
		FILE_NUM++;
		}
	if (FILE_NUM == 0) {return;}

	// Dimension File Array
	snd = std::vector<fmtSND>(FILE_NUM);

	// Loop Through Each File
	int FILE_INDEX = 0;
	for (rapidxml::xml_node<>* NODE_FILE = NODE_SND->first_node("file"); NODE_FILE; NODE_FILE = NODE_FILE->next_sibling()) {
		// FILE NODE, START


		// Check for Room Attribute
		rapidxml::xml_attribute<>* NODE_FILE_ATTR = NODE_FILE->first_attribute("room");
		if (NODE_FILE_ATTR != NULL) {
			snd[FILE_INDEX].fileid = convert_to<int32_t>(std::string(NODE_FILE_ATTR->value()));
			}

		// Count Assets in Current File
		int ASSET_NUM = 0;
		for (rapidxml::xml_node<>* NODE_ASSET = NODE_FILE->first_node("asset"); NODE_ASSET; NODE_ASSET = NODE_ASSET->next_sibling()) {
			ASSET_NUM++;
			}
		if (ASSET_NUM == 0) {continue;}


		// Dimension Asset Array
		snd[FILE_INDEX].playlists = std::vector<fmtSND_Entry>(ASSET_NUM);

		// Loop Through Each Asset
		int ASSET_INDEX = 0;
		for (rapidxml::xml_node<>* NODE_ASSET = NODE_FILE->first_node("asset"); NODE_ASSET; NODE_ASSET = NODE_ASSET->next_sibling()) {
			// ASSET NODE, START



			// Check for Asset Attribute
			rapidxml::xml_attribute<>* NODE_ASSET_ATTR = NODE_ASSET->first_attribute("id");
			if (NODE_ASSET_ATTR != NULL) {
				snd[FILE_INDEX].playlists[ASSET_INDEX].id = convert_to<int16_t>(std::string(NODE_ASSET_ATTR->value()));
				}

			// Check for BLOCK1 NODE
			rapidxml::xml_node<>* NODE_BLOCK1 = NODE_ASSET->first_node("block1");
			if (NODE_BLOCK1 != NULL) {
				// BLOCK1 NODE, START



				// Count Block1 Elements
				int UNK001_NUM = 0;
				for (rapidxml::xml_node<>* NODE_UNK001 = NODE_BLOCK1->first_node("entry"); NODE_UNK001; NODE_UNK001 = NODE_UNK001->next_sibling()) {
					UNK001_NUM++;
					}

				if (UNK001_NUM) {

					// Dimension Block1 Array
					snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.table1 = std::vector<int16_t>(UNK001_NUM);

					// Loop Through Unk001 Entries
					int UNK001_INDEX = 0;
					for (rapidxml::xml_node<>* NODE_UNK001 = NODE_BLOCK1->first_node("entry"); NODE_UNK001; NODE_UNK001 = NODE_UNK001->next_sibling()) {
						// UNK001 NODE, START

						snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.table1[UNK001_INDEX] = convert_to<int16_t>(std::string(NODE_UNK001->value()));

						UNK001_INDEX++;
						} // UNK001 NODE, END
					}

				} // BLOCK1 NODE, END



			// Check for BLOCK2 NODE, REGION
			rapidxml::xml_node<>* NODE_BLOCK2 = NODE_ASSET->first_node("region");
			if (NODE_BLOCK2 != NULL) {


				// Count Entries
				int ENTRY_NUM = 0;
				for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK2->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {ENTRY_NUM++;}
				if (ENTRY_NUM > 0) {

					// Dimension Array
					snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region = std::vector<fmtHED_WTREGION>(ENTRY_NUM);

					int ENTRY_INDEX = 0;
					rapidxml::xml_node<>* NODE_ITEM;
					for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK2->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
						// NODE ENTRY, START


						if ((NODE_ITEM = NODE_ENTRY->first_node("unityNote")) != NULL) {
							//std::cout << "unityNote: \tStr(" << (int)convert_to<uint8_t>(std::string(NODE_ITEM->value())) << "), \tInt(" << (int)convert_to<uint8_t>(std::string(NODE_ITEM->value())) ")" << std::endl;
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region[ENTRY_INDEX].unityNote = (
								(uint8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("keyGroup")) != NULL) {
							//std::cout << "keyGroup: \t" << (int)convert_to<uint8_t>(std::string(NODE_ITEM->value())) << std::endl;
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region[ENTRY_INDEX].keyGroup = (
								(uint8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("fineTune")) != NULL) {
							//std::cout << "fineTune: \tStr(" << std::string(NODE_ITEM->value()) << "), \tInt(" << ()convert_to<int>(std::string(NODE_ITEM->value())) << ")" << std::endl;
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region[ENTRY_INDEX].fineTune = (
								convert_to<int16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("attn")) != NULL) {
							//std::cout << "attn: \t" << (int)convert_to<uint8_t>(std::string(NODE_ITEM->value())) << std::endl;
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region[ENTRY_INDEX].attn = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("loopStart")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region[ENTRY_INDEX].loopStart = (
								convert_to<uint32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("loopLength")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region[ENTRY_INDEX].loopLength = (
								convert_to<uint32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("articulationIndex")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region[ENTRY_INDEX].articulationIndex = (
								convert_to<uint32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("sampleIndex")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.region[ENTRY_INDEX].sampleIndex = (
								convert_to<uint32_t>(std::string(NODE_ITEM->value()))
								);
							}


						ENTRY_INDEX++;
						} // NODE ENTRY, END
					}


				}



			// Check for BLOCK3 NODE, ARTICULATION
			rapidxml::xml_node<>* NODE_BLOCK3 = NODE_ASSET->first_node("articulation");
			if (NODE_BLOCK3 != NULL) {


				// Count Entries
				int ENTRY_NUM = 0;
				for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK3->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {ENTRY_NUM++;}
				if (ENTRY_NUM > 0) {

					// Dimension Array
					snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art = std::vector<fmtHED_WTART>(ENTRY_NUM);

					int ENTRY_INDEX = 0;
					rapidxml::xml_node<>* NODE_ITEM;
					for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK3->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
						// NODE ENTRY, START


						if ((NODE_ITEM = NODE_ENTRY->first_node("lfoFreq")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].lfoFreq = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("lfoDelay")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].lfoDelay = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("lfoAtten")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].lfoAtten = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("lfoPitch")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].lfoPitch = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("lfoMod2Atten")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].lfoMod2Atten = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("lfoMod2Pitch")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].lfoMod2Pitch = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg1Attack")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg1Attack = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg1Decay")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg1Decay = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg1Sustain")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg1Sustain = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg1Release")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg1Release = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg1Vel2Attack")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg1Vel2Attack = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg1Key2Decay")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg1Key2Decay = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg2Attack")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg2Attack = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg2Decay")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg2Decay = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg2Sustain")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg2Sustain = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg2Release")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg2Release = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg2Vel2Attack")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg2Vel2Attack = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg2Key2Decay")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg2Key2Decay = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("eg2Pitch")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].eg2Pitch = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("pan")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.art[ENTRY_INDEX].pan = (
								convert_to<int32_t>(std::string(NODE_ITEM->value()))
								);
							}



						ENTRY_INDEX++;
						} // NODE ENTRY, END
					}


				}



			// Check for BLOCK4 NODE, SAMPLE
			rapidxml::xml_node<>* NODE_BLOCK4 = NODE_ASSET->first_node("sample");
			if (NODE_BLOCK4 != NULL) {


				// Count Entries
				int ENTRY_NUM = 0;
				for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK4->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {ENTRY_NUM++;}
				if (ENTRY_NUM > 0) {

					// Dimension Array
					snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.sample = std::vector<fmtHED_WTSAMPLE>(ENTRY_NUM);

					int ENTRY_INDEX = 0;
					rapidxml::xml_node<>* NODE_ITEM;
					for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK4->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
						// NODE ENTRY, START


						if ((NODE_ITEM = NODE_ENTRY->first_node("format")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.sample[ENTRY_INDEX].format = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("sampleRate")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.sample[ENTRY_INDEX].sampleRate = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("offset")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.sample[ENTRY_INDEX].offset = (
								convert_to<uint32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("length")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.sample[ENTRY_INDEX].length = (
								convert_to<uint32_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("adpcmIndex")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.sample[ENTRY_INDEX].adpcmIndex = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("unk043")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.sample[ENTRY_INDEX].unk043 = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}


						ENTRY_INDEX++;
						} // NODE ENTRY, END
					}


				}



			// Check for BLOCK5 NODE, ADPCM
			rapidxml::xml_node<>* NODE_BLOCK5 = NODE_ASSET->first_node("adpcm");
			if (NODE_BLOCK5 != NULL) {


				// Count Entries
				int ENTRY_NUM = 0;
				for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK5->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {ENTRY_NUM++;}
				if (ENTRY_NUM > 0) {

					// Dimension Array
					snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm = std::vector<fmtHED_WTADPCM>(ENTRY_NUM);

					int ENTRY_INDEX = 0;
					rapidxml::xml_node<>* NODE_ITEM;
					for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK5->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
						// NODE ENTRY, START


						//if ((NODE_ITEM = NODE_ASSET->first_node("unk050")) != NULL) {
						//
						//	// Loop Through Elements
						//	int UNK050_INDEX = 0;
						//	for (rapidxml::xml_node<>* NODE_UNK050 = NODE_ENTRY->first_node("data"); NODE_UNK050; NODE_UNK050 = NODE_UNK050->next_sibling()) {

						//		if (UNK050_INDEX > 15) {continue;}
						//		snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[UNK050_INDEX] = (
						//			convert_to<uint16_t>(std::string(NODE_UNK050->value()))
						//			);

						//		UNK050_INDEX++;
						//		}
						//	}

						if ((NODE_ITEM = NODE_ENTRY->first_node("unk050")) != NULL) {

							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 0] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk051")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 1] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk052")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 2] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk053")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 3] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk054")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 4] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk055")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 5] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk056")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 6] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk057")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 7] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk058")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 8] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk059")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[ 9] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk060")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[10] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk061")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[11] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk062")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[12] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk063")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[13] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk064")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[14] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}
						if ((NODE_ITEM = NODE_ENTRY->first_node("unk065")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].unk050[15] = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}


						if ((NODE_ITEM = NODE_ENTRY->first_node("gain")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].gain = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("pred_scale")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].pred_scale = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("yn1")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].yn1 = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("yn2")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].yn2 = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("loop_pred_scale")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].loop_pred_scale = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("loop_yn1")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].loop_yn1 = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("loop_yn2")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block3.adpcm[ENTRY_INDEX].loop_yn2 = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}



						ENTRY_INDEX++;
						} // NODE ENTRY, END
					}


				}



			// Check for BLOCK6 NODE
			rapidxml::xml_node<>* NODE_BLOCK6 = NODE_ASSET->first_node("sit");
			if (NODE_BLOCK6 != NULL) {


				// Count Entries
				int ENTRY_NUM = 0;
				for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK6->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {ENTRY_NUM++;}
				if (ENTRY_NUM > 0) {

					// Dimension Array
					snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit = std::vector<fmtHED_SIT>(ENTRY_NUM);

					int ENTRY_INDEX = 0;
					rapidxml::xml_node<>* NODE_ITEM;
					for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK6->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
						// NODE ENTRY, START


						if ((NODE_ITEM = NODE_ENTRY->first_node("note")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].note = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("lim")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].lim = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("id2")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].id2 = (
								(uint8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("prio")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].prio = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("pan")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].pan = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("vol")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].vol = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("aux_a")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].aux_a = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("id1")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].id1 = (
								(uint8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("vol_flag")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].vol_flag = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("pitch_l")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].pitch_l = (
								convert_to<int16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("pitch_h")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].pitch_h = (
								convert_to<int16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("enc_vol")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].enc_vol = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("grob")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].grob = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("srd_type")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].srd_type = (
								(uint8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("span")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].span = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("svol")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].svol = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("free1")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].free1 = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("free2")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].free2 = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("free3")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].free3 = (
								(int8_t)convert_to<int>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("flag")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.sit[ENTRY_INDEX].flag = (
								convert_to<uint16_t>(std::string(NODE_ITEM->value()))
								);
							}

						ENTRY_INDEX++;
						} // NODE ENTRY, END
					}


				}



			// Check for BLOCK7 NODE
			rapidxml::xml_node<>* NODE_BLOCK7 = NODE_ASSET->first_node("block7");
			if (NODE_BLOCK7 != NULL) {

				// If present in an capacity force writing to the binary file
				snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block2.forceWrite = true;

				// Count Entries
				int ENTRY_NUM = 0;
				for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK7->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {ENTRY_NUM++;}
				if (ENTRY_NUM > 0) {

					// Dimension Array
					snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block2.entry = std::vector<fmtHED_Block2_Entry>(ENTRY_NUM);

					std::cout << "COUNT: \t" << snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block2.entry.size() << std::endl;


					int ENTRY_INDEX = 0;
					rapidxml::xml_node<>* NODE_ITEM;
					for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK7->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
						// NODE ENTRY, START


						if ((NODE_ITEM = NODE_ENTRY->first_node("index")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block2.entry[ENTRY_INDEX].index = (
								convert_to<int16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("unk004")) != NULL) {
							snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block2.entry[ENTRY_INDEX].unk004 = (
								convert_to<int16_t>(std::string(NODE_ITEM->value()))
								);
							}

						if ((NODE_ITEM = NODE_ENTRY->first_node("unk005")) != NULL) {

							int UNK005_NUM = 0;
							for (rapidxml::xml_node<>* NODE_UNK005 = NODE_ITEM->first_node("data"); NODE_UNK005; NODE_UNK005 = NODE_UNK005->next_sibling()) {UNK005_NUM++;}
							if (UNK005_NUM > 0) {

								snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block2.entry[ENTRY_INDEX].unk005 = std::vector<uint16_t>(UNK005_NUM);
								snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block2.entry[ENTRY_INDEX].count = UNK005_NUM;

								int UNK005_INDEX = 0;
								for (rapidxml::xml_node<>* NODE_UNK005 = NODE_ITEM->first_node("data"); NODE_UNK005; NODE_UNK005 = NODE_UNK005->next_sibling()) {






									snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block2.entry[ENTRY_INDEX].unk005[UNK005_INDEX] = (
										convert_to<uint16_t>(std::string(NODE_UNK005->value()))
										);



									UNK005_INDEX++;
									}
								}
							}


						ENTRY_INDEX++;
						} // NODE ENTRY, END
					}


				}


			std::string b64_data;


			// Check for BLOCK8 NODE
			rapidxml::xml_node<>* NODE_BLOCK8 = NODE_ASSET->first_node("block8");
			if (NODE_BLOCK8 != NULL) {


				// Count Entries
				int ENTRY_NUM = 0;
				for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK8->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {ENTRY_NUM++;}
				if (ENTRY_NUM > 0) {

					// Dimension Array
					snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block5.data = std::vector<bytestream>(ENTRY_NUM);

					int ENTRY_INDEX = 0;
					for (rapidxml::xml_node<>* NODE_ENTRY = NODE_BLOCK8->first_node("entry"); NODE_ENTRY; NODE_ENTRY = NODE_ENTRY->next_sibling()) {
						// NODE ENTRY, START

						b64_data = reduce(std::string(NODE_ENTRY->value()), "", "\n\r\t ");
						snd[FILE_INDEX].playlists[ASSET_INDEX].hed.block1.block5.data[ENTRY_INDEX].base64_decode(b64_data);
						b64_data.clear();

						ENTRY_INDEX++;
						} // NODE ENTRY, END
					}


				}


			// Check for BLOCK9 NODE
			rapidxml::xml_node<>* NODE_BLOCK9 = NODE_ASSET->first_node("block9");
			if (NODE_BLOCK9 != NULL) {
				b64_data = reduce(std::string(NODE_BLOCK9->value()), "", "\n\r\t ");
				snd[FILE_INDEX].playlists[ASSET_INDEX].dsp.buffer.base64_decode(b64_data);
				b64_data.clear();
				}


			ASSET_INDEX++;
			} // ASSET NODE, END


		FILE_INDEX++;
		} // FILE NODE, END

	}
