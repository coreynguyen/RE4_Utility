#include "fmtXSB.h"


fmtXSB_Event_Info::fmtXSB_Event_Info () {
	flag = 1;
	time_stamp = 0;
	unk13 = 32;
	random_time_offset = 0;
	unk13b = -1;
	gen_flag = 0;
	wav_index = 0;
	unk13e = 0;
	}

void fmtXSB_Event_Info::read_Event_Info (bytestream &f) {
	flag = f.readUbyte();
	time_stamp = f.readUshort();
	unk13 = f.readUbyte();
	random_time_offset = f.readUshort();
	unk13b = f.readUbyte();
	gen_flag = f.readUbyte();
	wav_index = f.readUshort();
	unk13e = f.readUbyte();
	}

void fmtXSB_Event_Info::write_Event_Info (bytestream &s) {
	s.writeUbyte(flag);
	s.writeUshort(time_stamp);
	s.writeUbyte(unk13);
	s.writeUshort(random_time_offset);
	s.writeUbyte(unk13b);
	s.writeUbyte(gen_flag);
	s.writeUshort(wav_index);
	s.writeUbyte(unk13e);
	}

fmtXSB_Event_Playwave::fmtXSB_Event_Playwave () {
	loop_count = -1;
	threesixty_pan_min = 0;
	threesixty_pan_max = 0;
	}

void fmtXSB_Event_Playwave::read_Event_Playwave (bytestream &f) {
	loop_count = f.readbyte();
	threesixty_pan_min = f.readUshort();
	threesixty_pan_max = f.readUshort();
	}

void fmtXSB_Event_Playwave::write_Event_Playwave (bytestream &s) {
	s.writebyte(loop_count);
	s.writeUshort(threesixty_pan_min);
	s.writeUshort(threesixty_pan_max);
	}

void fmtXSB_Event_Playwave::repr () {
	std::cout << "Playwave: " << threesixty_pan_min << "\t" << threesixty_pan_max << "\n";
	}

fmtXSB_Variable::fmtXSB_Variable () {
	pitch_min = 0;
	pitch_max = 0;
	volume_min = 0x97;
	volume_max = 0xD6;
	filter_freq_min = 1000.0;
	filter_freq_max = 1000.0;
	filter_q_min = 30.0;
	filter_q_max = 30.0;
	var_flag = 0;
	}

void fmtXSB_Variable::read_xsb_pitch (bytestream &f) {
	pitch_min = f.readshort();
	pitch_max = f.readshort();
	volume_min = f.readUbyte();
	volume_max = f.readUbyte();
	filter_freq_min = f.readfloat();
	filter_freq_max = f.readfloat();
	filter_q_min = f.readfloat();
	filter_q_max = f.readfloat();
	var_flag = f.readUshort();
	}

void fmtXSB_Variable::write_xsb_pitch (bytestream &s) {
	s.writeshort(pitch_min);
	s.writeshort(pitch_max);
	s.writeUbyte(volume_min);
	s.writeUbyte(volume_max);
	s.writefloat(filter_freq_min);
	s.writefloat(filter_freq_max);
	s.writefloat(filter_q_min);
	s.writefloat(filter_q_max);
	s.writeUshort(var_flag);
	}

void fmtXSB_Variable::repr () {
	std::cout << "Variable: \t" << pitch_min << " \t" << pitch_max;
	std::cout << " \t" <<  volume_min << " \t" << volume_max;
	std::cout << " \t" << filter_freq_min << " \t" << filter_freq_max;
	std::cout << " \t" << filter_q_min  << " \t" << filter_q_max << " \t" << var_flag << std::endl;
	}

fmtXSB_Event::fmtXSB_Event () {
	event_count = 1;
	}

bool fmtXSB_Event::read_Event (bytestream &f) {
	bool readSuccess = true;
	event_count = f.readUbyte();
	if (event_count > 0) {
		int event_type = 0;
		for (unsigned int i = 0; i < event_count; i++) {
			events.read_Event_Info(f);
			event_type = events.flag; //bit.and events[i].flag 0xFF
			switch (event_type) { // event id in lower 5 bits
				case 1: { // EventPlayWave
					playwave.read_Event_Playwave(f);
					break;
					}
				case 4: { // PitchVolumeFilterVariation
					playwave.read_Event_Playwave(f);
					variable.read_xsb_pitch(f);
					break;
					}
				default: {
					std::cout << "Unsupported Event:\t" << event_type << std::endl;
					readSuccess = false;
					}
				}
			}
		}
	return readSuccess;
	}

void fmtXSB_Event::write_Event (bytestream &s) {
	s.writeUbyte(event_count);
	if (event_count > 0) {
		int event_type = 0;
		for (unsigned int i = 0; i < event_count; i++) {
			events.write_Event_Info(s);
			event_type = events.flag;//bit.and events[i].flag 0xFF
			switch (event_type) { // event id in lower 5 bits
				case 1: {playwave.write_Event_Playwave(s); break;}
				case 4: {
					playwave.write_Event_Playwave(s);
					variable.write_xsb_pitch(s); // PitchVolumeFilterVariation
					break;
					}
				}
			}
		}
	}

fmtXSB_Track_Flag::fmtXSB_Track_Flag () {
	enable_filter = false;
	band_pass = false;
	high_pass = false;
	}

void fmtXSB_Track_Flag::set_track_flag (uint32_t val) {
	enable_filter = bit::get(val, 1);
	band_pass = bit::get(val, 2);
	high_pass = bit::get(val, 3);
	}

uint32_t fmtXSB_Track_Flag::get_track_flag () {
	uint32_t val = 0;
	val = bit::set(val, 1, enable_filter);
	val = bit::set(val, 2, band_pass);
	val = bit::set(val, 3, high_pass);
	return val;
	}

void fmtXSB_Track_Flag::repr () {
	std::cout << "enable_filter: \t" << enable_filter << std::endl;
	std::cout << "band_pass: \t" << band_pass << std::endl;
	std::cout << "high_pass: \t" << high_pass << std::endl;
	std::cout << "low_pass: \t" << (!band_pass && !high_pass) << std::endl;
	}

fmtXSB_Track::fmtXSB_Track () {
	volume = 0;
	event_addr = 0;
	filter_q = 0x5DC0;
	filter_freq = 0x03E8;
	}

float fmtXSB_Track::volume_as_db () {
	/*
	they did something fucking weird with the volume
	its like they chopped up the ranges; so the weight
	factors are different across a different range of
	bit values

	note that this algo is different then the other volume mixer which seemed to be a logarithmic

	6 = FF	255	75
	5 = F0	240	60
	4 = E3	227	47
	3 = D6	214	34
	2 = CA	202	22
	1 = BF	191	11
	0 = B4	180	0
	//////////////////////////////////
	If the value is above 180
	-6= 7F	127

	uint8 convert to dB
	{{{227 - 180} / 75.0} * 6.0} = 4.8

	convert dB to uint8
	{{4.8 / 6.0} * 127} + 180

	// DIFF 75


	////////////////////////////////-
	if (value is above 127

	uint8 convert to dB
	{{{{153 - 127} / 53.0} * 6.0} - 6} =



	//////////////////////////////////-
	if (value below 127


	uint8 convert to dB
	{{{28 / 127.0} * 90} + 6 } * -1 =

	convert dB to uint8
	{{{-25.8425 * -1} - 6} / 90.0} * 127


	*/
	float v = volume;
	if (volume < 127) {
		v = (((v / 127.0f) * 90.0f) + 6.0f) * -1.0f;
		}
	else if (volume > 180) {
		v = ((v - 180.0f) / 75.0f) * 6.0f;
		}
	else {
		v = (((v - 127.0f) / 53.0f) * 6.0f) - 6.0f;
		}
	return v;
	}

bool fmtXSB_Track::read_Track (bytestream &f) {
	size_t p = f.tell();
	bool readSuccess = true;
	volume = f.readUbyte(); // volume mixer {6 to -96}
	event_addr = f.readUlong(); // this data just appears right after anyway; pointer seems a bit much

	uint16_t filter_q_mask = f.readUshort(); // filter Q {0.67 - 30.0} {bitmasked with the mode}
	flags.set_track_flag(filter_q_mask);
	filter_q = (filter_q_mask >> 3) / 100.0f;

	filter_freq = f.readUshort(); // filter frequency {20 - 20 000}

	if (event_addr > 0) {
		// check if (data was skipped over
		if (f.tell() != event_addr) {
			readSuccess = false;
			std::cout << "ERROR:\n\tUnknown Data Stream in Track Data: " << p << std::endl;
			std::cout << "\tHeader Ended at '" << p << "' but event data started at '" << event_addr << "'" << std::endl;
			}
		f.seek(event_addr);
		readSuccess = event.read_Event(f);
		}

	return readSuccess;
	}

void fmtXSB_Track::write_Track (bytestream &s) {
	s.writeUbyte(volume); // volume mixer {6 to -96}
	s.writeUlong(event_addr);

	s.writeUshort((unsigned int)(flags.get_track_flag() + (((unsigned int)(filter_q * 100.0)) << 3)));
	if (event.event_count > 0) {
		event.write_Event(s);
		}

	s.writeUshort(filter_freq);
	}

fmtXSB_RPC_Table::fmtXSB_RPC_Table () {
	extraLen = 7;
	unk04 = 1;
	unk05 = 0xD3;
	}

void fmtXSB_RPC_Table::read_RPC_Table (bytestream &f) {
	extraLen = f.readUshort(); // size of entry
	unk04 = f.readUbyte();
	unk05 = f.readUlong();
	}

void fmtXSB_RPC_Table::write_RPC_Table (bytestream &s) {
	s.writeUshort(extraLen); // size of entry
	s.writeUbyte(unk04);
	s.writeUlong(unk05);
	}

fmtXSB_Sound_flag::fmtXSB_Sound_flag () {
	hasComplexSound = true;
	flag02 = true;
	flag03 = false;
	flag04 = false;
	flag05 = false;
	flag06 = false;
	flag07 = false;
	flag08 = false;
	}

void fmtXSB_Sound_flag::read_sound_flag (bytestream &f) {
	uint32_t val = f.readUbyte();
	hasComplexSound = bit::get(val, 1);
	flag02 = bit::get(val, 2);
	flag03 = bit::get(val, 3);
	flag04 = bit::get(val, 4);
	flag05 = bit::get(val, 5);
	flag06 = bit::get(val, 6);
	flag07 = bit::get(val, 7);
	flag08 = bit::get(val, 8);
	}

void fmtXSB_Sound_flag::write_sound_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, hasComplexSound);
	val = bit::set(val, 2, flag02);
	val = bit::set(val, 3, flag03);
	val = bit::set(val, 4, flag04);
	val = bit::set(val, 5, flag05);
	val = bit::set(val, 6, flag06);
	val = bit::set(val, 7, flag07);
	val = bit::set(val, 8, flag08);
	s.writeUbyte(val);
	}

void fmtXSB_Sound_flag::repr () {
	std::cout << "Flags: \t " << hasComplexSound << " \t" << flag02;
	std::cout << " \t" << flag03 << " \t" << flag04 << " \t";
	std::cout << " \t" << flag05 << " \t" << flag06 << " \t";
	std::cout << " \t" << flag07 << " \t" << flag08 << std::endl;
	}

fmtXSB_Sound::fmtXSB_Sound () {
	category = 1;
	volume = 0x5A;
	pitch = 0;
	priority = 0;
	entryLength = 0;
	track_count = 0;
	trackIndex = 0;
	waveBankIndex = 0;
	}

float fmtXSB_Sound::volume_as_db () {
	/*
		this is only an estimated value; i'm not sure how
		to derive the proper log of the db values.

		return values seem to be within 5% ish of there
		correct values.
	*/
	float r = (float)(std::pow((1.0 - volume / 254.0) * 0.09564054, std::pow((volume / 254.0) + 0.000637738, 0.3) - 0.11));
	return ((r - 1) * -102) - 96;
	}

bool fmtXSB_Sound::read_Sound (bytestream &f) {
	size_t pos = f.tell();
	bool readSuccess = true;

	flags.read_sound_flag(f);
	category = f.readUshort();
	volume = f.readUbyte();
	pitch = f.readUshort();
	priority = f.readUbyte();
	entryLength = f.readUshort();

	if (flags.hasComplexSound) {
		// Flag is 3 {Complex}
		track_count = f.readUbyte();
		}
	else {
		// Flag is 2 {Simple}
		trackIndex = f.readUshort();
		waveBankIndex = f.readUbyte();
		}

	// RPC: Runtime Parameter Control
	// DSP: Digital Signal Processing
	if (flags.flag02) {		// RPC Table
		rpc_table1.read_RPC_Table(f);
		}
	if (flags.flag03) {		// RPC Table
		rpc_table2.read_RPC_Table(f);
		}
	if (flags.flag04) {		// RPC Table
		rpc_table3.read_RPC_Table(f);
		}
	if (track_count > 0) {

		tracks = std::vector<fmtXSB_Track>(track_count);
		for (unsigned int i = 0; i < track_count; i++) {
			if (!tracks[i].read_Track(f) && readSuccess) {
				readSuccess = false;
				}
			}
		}

	if (readSuccess && (flags.flag03 || flags.flag04 || flags.flag05 || flags.flag06 || flags.flag07 || flags.flag08)) {
		readSuccess = false;
		}
	f.seek(pos + entryLength);
	return readSuccess;
	}

bool fmtXSB_Sound::write_Sound (bytestream &s) {

	bool readSuccess = true;

	flags.write_sound_flag(s);
	s.writeUshort(category);
	s.writeUbyte(volume);
	s.writeUshort(pitch);
	s.writeUbyte(priority);
	s.writeUshort(entryLength);

	if (flags.hasComplexSound) {
		s.writeUbyte(track_count);
		}
	else {
		s.writeUshort(trackIndex);
		s.writeUbyte(waveBankIndex);
		}

	// RPC: Runtime Parameter Control
	// DSP: Digital Signal Processing
	if (flags.flag02) {		// RPC Table
		rpc_table1.write_RPC_Table(s);
		}

	if (flags.flag03) {		// RPC Table
		rpc_table2.write_RPC_Table(s);
		}

	if (flags.flag04) {		// RPC Table
		rpc_table3.write_RPC_Table(s);
		}

	for (unsigned int i = 0; i < track_count; i++) {
		tracks[i].write_Track(s);
		}

	return readSuccess;
	}

fmtXSB_Simple_Flag::fmtXSB_Simple_Flag () {
	flag01 = false;
	flag02 = false;
	flag03 = true;
	flag04 = false;
	flag05 = false;
	flag06 = false;
	flag07 = false;
	flag08 = false;
	}

void fmtXSB_Simple_Flag::read_simple_flag (bytestream &f) {
	auto val = f.readUbyte();
	flag01 = bit::get(val, 1);
	flag02 = bit::get(val, 2);
	flag03 = bit::get(val, 3);
	flag04 = bit::get(val, 4);
	flag05 = bit::get(val, 5);
	flag06 = bit::get(val, 6);
	flag07 = bit::get(val, 7);
	flag08 = bit::get(val, 8);
	}

void fmtXSB_Simple_Flag::write_simple_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, flag01);
	val = bit::set(val, 2, flag02);
	val = bit::set(val, 3, flag03);
	val = bit::set(val, 4, flag04);
	val = bit::set(val, 5, flag05);
	val = bit::set(val, 6, flag06);
	val = bit::set(val, 7, flag07);
	val = bit::set(val, 8, flag08);
	s.writeUbyte(val);
	}

void fmtXSB_Simple_Flag::repr () {
	std::cout << "Flags: \t" << flag01 << " \t" << flag02;
	std::cout << " \t" << flag03 << " \t" << flag04;
	std::cout << " \t" << flag05 << " \t" << flag06;
	std::cout << " \t" << flag07 << " \t" << flag08 << std::endl;
	}

fmtXSB_Simplecue_Table::fmtXSB_Simplecue_Table () {
	sound_offset = 0;
	}

void fmtXSB_Simplecue_Table::read_simplecue_table (bytestream &f) {
	flags.read_simple_flag(f);
	sound_offset = f.readUlong();
	}

void fmtXSB_Simplecue_Table::write_simplecue_table (bytestream &s, std::vector<uint32_t> &sound_buffer_addrs) {
	flags.write_simple_flag(s);
	s.writeUlong(sound_buffer_addrs[sound_offset]);
	}

fmtXSB_Complexcue_Flag::fmtXSB_Complexcue_Flag () {
	flag01 = true;
	flag02 = false;
	flag03 = true;
	flag04 = false;
	flag05 = false;
	flag06 = false;
	flag07 = false;
	flag08 = false;
	}

void fmtXSB_Complexcue_Flag::read_complexcue_flag (bytestream &f) {
	uint32_t val = f.readUbyte();
	flag01 = bit::get(val, 1);
	flag02 = bit::get(val, 2);
	flag03 = bit::get(val, 3);
	flag04 = bit::get(val, 4);
	flag05 = bit::get(val, 5);
	flag06 = bit::get(val, 6);
	flag07 = bit::get(val, 7);
	flag08 = bit::get(val, 8);
	}

void fmtXSB_Complexcue_Flag::write_complexcue_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, flag01);
	val = bit::set(val, 2, flag02);
	val = bit::set(val, 3, flag03);
	val = bit::set(val, 4, flag04);
	val = bit::set(val, 5, flag05);
	val = bit::set(val, 6, flag06);
	val = bit::set(val, 7, flag07);
	val = bit::set(val, 8, flag08);
	s.writeUbyte(val);
	}

void fmtXSB_Complexcue_Flag::repr () {
	std::cout << "Flags: \t" << flag01 << " \t" << flag02;
	std::cout << " \t" << flag03 << " \t" << flag04;
	std::cout << " \t" << flag05 << " \t" << flag06;
	std::cout << " \t" << flag07 << " \t" << flag08 << std::endl;
	}

fmtXSB_Instance_Limit::fmtXSB_Instance_Limit () {
	limit = 1;
	fade_in = 0;
	fade_out = 0;
	flag = 32;
	}

void fmtXSB_Instance_Limit::read_instace_limit (bytestream &f) {
	limit = f.readUbyte();
	fade_in = f.readUshort();
	fade_out = f.readUshort();
	flag = f.readUbyte();
	}

void fmtXSB_Instance_Limit::write_instace_limit (bytestream &s) {
	s.writeUbyte(limit);
	s.writeUshort(fade_in);
	s.writeUshort(fade_out);
	s.writeUbyte(flag);
	}

fmtXSB_Complexcue_Table::fmtXSB_Complexcue_Table () {
	sound_offset = -1;
	unk1 = 0;
	variation_offset = -1;
	transition_offset = -1;
	}

bool fmtXSB_Complexcue_Table::read_complexcue_table (bytestream &f) {
	bool readSuccess = true;
	flags.read_complexcue_flag(f); // 1 byte

	if (flags.flag03) {
		sound_offset = f.readUlong();
		unk1 = f.readUlong();
		}
	else {
		variation_offset = f.readUlong();
		transition_offset = f.readUlong();
		}
	instances.read_instace_limit(f);
	if (flags.flag02 || flags.flag04 || flags.flag05 || flags.flag06 || flags.flag07 || flags.flag08) {
		std::cout << "unknown flag\n";
		readSuccess = false;
		}
	return readSuccess;
	}

void fmtXSB_Complexcue_Table::write_complexcue_table (bytestream &s, std::vector<uint32_t> &sound_buffer_addrs, std::vector<uint32_t> &variation_addrs) {
	flags.write_complexcue_flag(s);
	if (flags.flag03) {
		if (sound_offset > 0 && sound_offset != 0xFFFFFFFF) {
			s.writeUlong(sound_buffer_addrs[sound_offset]);
			}
		else {
			s.writeUlong(sound_offset);
			}
		s.writeUlong(unk1);
		}
	else {
		if (variation_offset > 0 && variation_offset != -1) {
			s.writeUlong(variation_addrs[variation_offset]);
			}
		else {
			s.writeUlong(variation_offset);
			}
		s.writeUlong(transition_offset);
		}
	instances.write_instace_limit(s);
	}

fmtXSB_String_Table::fmtXSB_String_Table () {
	addr = 0;
	unk1 = -1;
	}

void fmtXSB_String_Table::read_String_Table (bytestream &f) {
	addr = f.readUlong();
	unk1 = f.readshort();
	}

void fmtXSB_String_Table::write_String_Table (bytestream &s) {
	s.writeUlong(addr);
	s.writeshort(unk1);
	}

fmtXSB_Variation_Mix::fmtXSB_Variation_Mix () {
	sound_offset = 0;
	sound_unk = 0;
	sound_weight = 0;
	}

void fmtXSB_Variation_Mix::read_Variation_Mix (bytestream &f) {
	sound_offset = f.readUlong();
	sound_unk = f.readUbyte();
	sound_weight = f.readbyte();
	}

void fmtXSB_Variation_Mix::write_Variation_Mix (bytestream &s, std::vector<uint32_t> &sound_buffer_addrs) {
	s.writeUlong(sound_buffer_addrs[sound_offset]);
	s.writeUbyte(sound_unk);
	s.writebyte(sound_weight);
	}

fmtXSB_Variation_Flags::fmtXSB_Variation_Flags () {
	isNoRepeat = true;
	isRandom = true;
	isShuffled = false;
	flag04 = true;
	hasTransition = false;
	flag06 = false;
	flag07 = false;
	flag08 = false;
	flag09 = false;
	flag10 = false;
	flag11 = false;
	flag12 = false;
	flag13 = false;
	flag14 = false;
	flag15 = false;
	flag16 = false;
	}

void fmtXSB_Variation_Flags::read_variation_flag (bytestream &f) {
	uint32_t val = f.readUbyte();
	isNoRepeat = bit::get(val, 1);
	isRandom = bit::get(val, 2);
	isShuffled = bit::get(val, 3);
	flag04 = bit::get(val, 4);
	hasTransition = bit::get(val, 5);
	flag06 = bit::get(val, 6);
	flag07 = bit::get(val, 7);
	flag08 = bit::get(val, 8);
	flag09 = bit::get(val, 9);
	flag10 = bit::get(val, 10);
	flag11 = bit::get(val, 11);
	flag12 = bit::get(val, 12);
	flag13 = bit::get(val, 13);
	flag14 = bit::get(val, 14);
	flag15 = bit::get(val, 15);
	flag16 = bit::get(val, 16);
	}

void fmtXSB_Variation_Flags::write_variation_flag (bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, isNoRepeat);
	val = bit::set(val, 2, isRandom);
	val = bit::set(val, 3, isShuffled);
	val = bit::set(val, 4, flag04);
	val = bit::set(val, 5, hasTransition);
	val = bit::set(val, 6, flag06);
	val = bit::set(val, 7, flag07);
	val = bit::set(val, 8, flag08);
	val = bit::set(val, 9, flag09);
	val = bit::set(val, 10, flag10);
	val = bit::set(val, 11, flag11);
	val = bit::set(val, 12, flag12);
	val = bit::set(val, 13, flag13);
	val = bit::set(val, 14, flag14);
	val = bit::set(val, 15, flag15);
	val = bit::set(val, 16, flag16);
	s.writeUbyte(val);
	}

void fmtXSB_Variation_Flags::set_variation_flag (uint32_t val) {
	isNoRepeat = bit::get(val, 1);
	isRandom = bit::get(val, 2);
	isShuffled = bit::get(val, 3);
	flag04 = bit::get(val, 4);
	hasTransition = bit::get(val, 5);
	flag06 = bit::get(val, 6);
	flag07 = bit::get(val, 7);
	flag08 = bit::get(val, 8);
	flag09 = bit::get(val, 9);
	flag10 = bit::get(val, 10);
	flag11 = bit::get(val, 11);
	flag12 = bit::get(val, 12);
	flag13 = bit::get(val, 13);
	flag14 = bit::get(val, 14);
	flag15 = bit::get(val, 15);
	flag16 = bit::get(val, 16);
	}

uint32_t fmtXSB_Variation_Flags::get_variation_flag () {
	uint32_t val = 0;
	val = bit::set(val, 1, isNoRepeat);
	val = bit::set(val, 2, isRandom);
	val = bit::set(val, 3, isShuffled);
	val = bit::set(val, 4, flag04);
	val = bit::set(val, 5, hasTransition);
	val = bit::set(val, 6, flag06);
	val = bit::set(val, 7, flag07);
	val = bit::set(val, 8, flag08);
	val = bit::set(val, 9, flag09);
	val = bit::set(val, 10, flag10);
	val = bit::set(val, 11, flag11);
	val = bit::set(val, 12, flag12);
	val = bit::set(val, 13, flag13);
	val = bit::set(val, 14, flag14);
	val = bit::set(val, 15, flag15);
	val = bit::set(val, 16, flag16);
	return val;
	}

fmtXSB_Variation::fmtXSB_Variation () {
	mix_count = 0;
	unk1 = 0;
	unk2 = 0;
	}

bool fmtXSB_Variation::read_Variation (bytestream &f) {
	bool readWasASuccess = true;
	unsigned int mix_count = 0;

	/*
	there is no block size here; any change in
	the flags cause specialized data to appear
	NOT GOOD!

	Luckily RE4 only uses 2 flags
	0x20000001 or 0x20000004

	So I can program around those safely

	However this means that I'll need to halt
	the program if (I come across a unsupported
	type
	*/

	mix_count = f.readUlong();
	flags.set_variation_flag(mix_count >> 16);
	mix_count = mix_count & 0xFFFF;
	unk1 = f.readshort();
	unk2 = f.readshort();


	//std::cout << "mix_count:\t%\n" mix_count
	//std::cout << "hasTransition:\t%\n" flags.hasTransition
	if (!flags.hasTransition) {
		if (mix_count > 0) {
			variation_mix = std::vector<fmtXSB_Variation_Mix>(mix_count);
			for (unsigned int i = 0; i < mix_count; i++) {
				variation_mix[i].read_Variation_Mix(f);
				}
			}
		}
	else {
		readWasASuccess = false;
		std::cout << "transitions not supported {" << f.tell() << "}\n";
		}

	return readWasASuccess;
	}

void fmtXSB_Variation::write_Variation (bytestream &s, std::vector<uint32_t> &sound_buffer_addrs) {
	s.writeUlong(((flags.get_variation_flag()) << 16) + mix_count);
	s.writeshort(unk1);
	s.writeshort(unk2);
	if (!flags.hasTransition) {
		for (unsigned int i = 0; i < mix_count; i++) {
			variation_mix[i].write_Variation_Mix(s, sound_buffer_addrs);
			}
		}
	}

fmtXSB::fmtXSB () {
	filetype = 0x4B424453;
	tool_version = 46;
	file_version = 43;
	crc = 0;
	lastModified = 0;
	platform = 1;
	numSimpleCues = 0;
	numComplexCues = 0;
	unkn3 = 0;
	cue_order_count = 0;
	wave_bank_count = 1;
	sound_count = 0;
	cue_name_buffer_size = 0;
	simpleCuesOffset = 0;
	complexCuesOffset = 0;
	cue_name_buffer_addr = 0;
	unknOffset = -1;
	variationTablesOffset = 0;
	unknOffset2 = -1;
	wave_bank_table_addr = 0;
	cue_order_addr = 0;
	cue_name_table_addr = 0;
	sound_buffer_addr = 0;
	sound_bank_name = "";
	}

bool fmtXSB::read_xsb (bytestream &f) {
	/*
	the format heavily uses pointers which makes dealing
	with repacking a mess...

	anyway to make the data more friendly to directly
	access from a UI control; all addresses are converted
	to indices. This will make accessing and adding data
	alot easier then dealing with pointers
	*/
	size_t pos = f.tell();

	std::vector<uint32_t> sound_entry_addrs;
	std::vector<uint32_t> complexcue_trans_addrs;
	std::vector<uint32_t> cue_name_addrs;
	std::vector<uint32_t> variation_addrs;
	bool variationReadSuccess = true;
	bool soundReadSuccess = true;
	bool complexReadSuccess = true;
	std::vector<uint32_t> variation_tmp;
	std::vector<uint32_t> transition_tmp;

	f.setLittleEndian();

	filetype = f.readUlong();

	if (filetype == 0x5344424B) { // Check if (file is in BIG Endian
		f.setBigEndian();
		f.seek(pos);
		filetype = f.readUlong();
		}

	if (filetype == 0x4B424453) { // 'SDBK'
		tool_version = f.readUshort();
		file_version = f.readUshort();
		crc = f.readUshort();
		lastModified = f.readUlonglong();
		platform = f.readUbyte();
		numSimpleCues = f.readUshort();
		numComplexCues = f.readUshort();
		unkn3 = f.readUshort();
		cue_order_count = f.readUshort();
		wave_bank_count = f.readUbyte();
		sound_count = f.readUshort();
		cue_name_buffer_size = f.readUlong();
		simpleCuesOffset = f.readUlong();
		complexCuesOffset = f.readUlong();
		cue_name_buffer_addr = f.readUlong();
		unknOffset = f.readUlong();
		variationTablesOffset = f.readUlong();
		unknOffset2 = f.readUlong();
		wave_bank_table_addr = f.readUlong();
		cue_order_addr = f.readUlong();
		cue_name_table_addr = f.readUlong();
		sound_buffer_addr = f.readUlong();
		unsigned int p = f.tell() + 64;
		sound_bank_name = f.readstring();
		f.seek(p);

		/*
		following data requires addresses from header section to read
		*/

		// Wave Bank Names
		if (wave_bank_table_addr > 0 && wave_bank_count > 0) {
			f.seek(pos + wave_bank_table_addr);
			wave_banks = std::vector<std::string>(wave_bank_count);
			for (unsigned int i = 0; i < wave_bank_count; i++) {
				p = f.tell() + 64;
				wave_banks[i] = f.readstring();
				f.seek(p);
				}
			}

		// Sound
		if (sound_buffer_addr > 0 && sound_count > 0) {
			/*
			This Data is read by either the simple or complex cue table
			by a pointer spcificed in ther simple / complex table.

			For that reason I am logging each entry position; and
			the complex / simple pointers are converted to indices.

			addresses are stored for temp lookup in 'sound_entry_addrs'

			Caution!
			parser is only designed to work with stock RE4 files;
			*/
			f.seek(pos + sound_buffer_addr);
			sound_buffer = std::vector<fmtXSB_Sound>(sound_count);
			sound_entry_addrs = std::vector<uint32_t>(sound_count);
			for (unsigned int i = 0; i < sound_count; i++) {
				sound_entry_addrs[i] = f.tell(); // log position, so can rebuild pointers as indices
				if (!(sound_buffer[i].read_Sound(f)) && soundReadSuccess) {
					soundReadSuccess = false;
					}
				}
			}

		// Simple Cues that point to a sound from the sound table
		if (simpleCuesOffset > 0 && numSimpleCues > 0) {
			/*
			contains an offset to the sound table
			*/
			f.seek(pos + simpleCuesOffset);
			simpleCueTable = std::vector<fmtXSB_Simplecue_Table>(numSimpleCues);
			for (unsigned int i = 0; i < numSimpleCues; i++) {
				simpleCueTable[i].read_simplecue_table(f);

				// pointer to the sound table is converted to an index
				simpleCueTable[i].sound_offset = findItem<uint32_t>(sound_entry_addrs, simpleCueTable[i].sound_offset);
				}
			}

		// Complex Cues that point to a sound from the sound table
		if (complexCuesOffset > 0 && numComplexCues > 0) {
			/*
			contains an offset to the sound table {like the simple cue table}
			however also contains a few additional values
			*/
			f.seek(pos + complexCuesOffset);
			complexCueTable = std::vector<fmtXSB_Complexcue_Table>(numComplexCues);
			for (unsigned int i = 0; i < numComplexCues; i++) {

				if (!(complexCueTable[i].read_complexcue_table(f)) && complexReadSuccess) {
					complexReadSuccess = false;
					}
				// pointer to the sound table is converted to an index
				if (complexCueTable[i].sound_offset > 0) {
					complexCueTable[i].sound_offset = findItem<uint32_t>(sound_entry_addrs, complexCueTable[i].sound_offset);
					}
				}
			}

		// this accessed only by the complex cue
		unsigned int variation_count = 0;
		unsigned int transition_count = 0;
		if (variationTablesOffset > 0) {
			for (unsigned int i = 0; i < numComplexCues; i++) {
				if (complexCueTable[i].variation_offset > 0 && complexCueTable[i].variation_offset != -1) {
					appendIfUnique<uint32_t>(variation_tmp, complexCueTable[i].variation_offset);
					}
				if (complexCueTable[i].transition_offset > 0 && complexCueTable[i].transition_offset  != -1) {
					appendIfUnique<uint32_t>(transition_tmp, complexCueTable[i].transition_offset);
					}
				}

			variation_count = variation_tmp.size();
			transition_count = transition_tmp.size();
			if (variation_count > 0) {
				variationTable = std::vector<fmtXSB_Variation>(variation_count);
				variation_addrs = std::vector<uint32_t>(variation_count);
				f.seek(pos + variationTablesOffset);
				for (unsigned int i = 0; i < variation_count; i++) {
					variation_addrs[i] = f.tell();
					if (!(variationTable[i].read_Variation(f)) && variationReadSuccess) {
						variationReadSuccess = false;
						}
					for (unsigned int ii = 0; ii < variationTable[i].variation_mix.size(); ii++) {
						variationTable[i].variation_mix[ii].sound_offset = findItem<uint32_t>(sound_entry_addrs, variationTable[i].variation_mix[ii].sound_offset);
						}
					}
				for (unsigned int i = 0; i < numComplexCues; i++) {
					// pointer to the sound table is converted to an index
					complexCueTable[i].variation_offset = findItem<uint32_t>(variation_addrs, complexCueTable[i].variation_offset);
					}
				}
			}

		if (cue_order_addr > 0 && cue_order_count > 0) {
			/*
			this table is bizzare; at mimium it will always have
			16 indices set to -1

			once cue entries are added they replace the indices
			existing in the table. Once the count exceeds the count
			of 16 then the table expands with the number of entries.

			Whats weird as how indices are written into this reserved
			sorting area. The new indices are not store at the start; but
			rather anywhere within the reserved area.

			Meaning they are evaluating the string as a number between
			0 - 15 then storing the index for the cue list into this
			reserved space. This would naturally put the list into a sorted
			arrangment.

			In one example an index for a cue item was completly missing
			from the reserved area. So like I dont know what the shit
			this area is for. From what I can tell its a piece of crap thats
			useless even at sorting

			I'm hoping I can just set the count to 0 for this area and just
			NOT write it...
			*/
			f.seek(pos + cue_order_addr);
			cue_order_indices = std::vector<int16_t>(cue_order_count);
			for (unsigned int i = 0; i < cue_order_count; i++) {
				cue_order_indices[i] = f.readshort();
				}
			}

		// String Buffer Table
		unsigned int cut_count = numSimpleCues + numComplexCues;
		if (cue_name_table_addr > 0 && cut_count > 0) {
			/*
			contains a list of address; that point to each string in
			the next table
			*/
			f.seek(pos + cue_name_table_addr);
			cue_name_table = std::vector<fmtXSB_String_Table>(cut_count);
			for (unsigned int i = 0; i < cut_count; i++) {
				cue_name_table[i].read_String_Table(f);
				}
			}

		// String Buffer
		if (cue_name_buffer_addr > 0 && cue_name_buffer_size > 0 && cut_count > 0) {
			/*
			This Data is read by the 'cue_name_buffer'
			*/
			f.seek(pos + cue_name_buffer_addr);

			cue_name_buffer = std::vector<std::string>(cut_count);
			cue_name_addrs = std::vector<uint32_t>(cut_count);


			// run a while loop just enswitch (there more strings then sound files
			unsigned int i = 0;
			while (f.tell() < (cue_name_buffer_addr + cue_name_buffer_size)) {
				cue_name_addrs[i] = f.tell();
				cue_name_buffer[i] = f.readstring();
				i++;
				}

			// pointer to the string table is converted to an index
			for (unsigned int i = 0; i < cue_name_table.size(); i++) {
				cue_name_table[i].addr = findItem<uint32_t>(cue_name_addrs, cue_name_table[i].addr);
				}
			}
		/*
		these address were not seen in my samples
		so I did not complete structs for them
			unknOffset
			unknOffset2
		*/

		if (!variationReadSuccess || !soundReadSuccess || !complexReadSuccess || transition_count > 0) {
			std::cout << "Errors:\n\tRead Complex:\t" << complexReadSuccess;
			std::cout  << "\n\tRead Sound:\t" << soundReadSuccess;
			std::cout  << "\n\tRead Variations:\t" << variationReadSuccess;
			std::cout  << "\n\tRead Transitions:\t" << transition_count << "\n\n";
			//messagebox "Some Data Was Not Read Currently\nSaving File May Result In corruption"
			}
		} else {std::cout << "Unsupported File\n";}
	return (variationReadSuccess && soundReadSuccess && complexReadSuccess);
	}

size_t fmtXSB::recalc_addresses (std::vector<uint32_t> &sound_buffer_addrs, std::vector<uint32_t> &variation_addrs) {

	size_t ptr = 0;

	// Copy Array Counts to Count Variables
	unsigned int wave_bank_count = wave_banks.size();
	unsigned int numSimpleCues = simpleCueTable.size();
	unsigned int numComplexCues = complexCueTable.size();
	signed int cue_order_count = cue_order_indices.size();
	unsigned int sound_count = sound_buffer.size();

	// Check that the sorting buffer has atleast 16 entries
	if (cue_order_count < 16) {
		for (unsigned int i = cue_order_count; i < 16; i++) {
			cue_order_indices.push_back(-1);
			}
		cue_order_count = cue_order_indices.size();
		}

	// Recalculate Addresses
	ptr = 0x8A; // set start of pointer at the wave bank table

	// Add Size of WaveBanks
	ptr += wave_bank_count * 64;

	// Add Size of Sounds {Only 3 Are supported; 19; 43; 67}
	if (sound_count > 0) {
		sound_buffer_addrs = std::vector<uint32_t>(sound_count);
		for (unsigned int i = 0; i < sound_count; i++) {
			sound_buffer_addrs[i] = ptr;
			ptr += 9; //sound entry
			if (sound_buffer[i].flags.hasComplexSound) {
				ptr += 1; // track count
				}
			else {
				ptr += 3; // track index
				}
			if (sound_buffer[i].flags.flag02) {		// RPC Table1
				ptr += sound_buffer[i].rpc_table1.extraLen;
				}
			if (sound_buffer[i].flags.flag03) {		// RPC Table2
				ptr += sound_buffer[i].rpc_table2.extraLen;
				}
			if (sound_buffer[i].flags.flag04) {		// RPC Table3
				ptr += sound_buffer[i].rpc_table3.extraLen;
				}
			for (unsigned int ii = 0; ii < sound_buffer[i].tracks.size(); ii++) {
				ptr += 9; // track size
				sound_buffer[i].tracks[ii].event_addr = ptr;
				ptr += 12;
				switch (((unsigned int)sound_buffer[i].tracks[ii].event.events.flag & 0xFF)) { // event id in lower 5 bits
					case 1: {ptr += 5; break;} // EventPlayWave
					case 4: {ptr += 29; break;} // PitchVolumeFilterVariation
					}

				}
			}
		}

	// Add Size of Simple Cues
	ptr += numSimpleCues * 5;

	// Add Size of Complex Cues
	ptr += numComplexCues * 15;

	// Add Size of Complex Cue Variations
	for (unsigned int i = 0; i < variationTable.size(); i++) {
		variation_addrs[i] = ptr;
		ptr += 8;
		if (!variationTable[i].flags.hasTransition) {
			variationTable[i].mix_count = variationTable[i].variation_mix.size();
			ptr += variationTable[i].mix_count * 6;
			}
		}

	// Add Size of Sorting Buffer
	ptr += cue_order_count * 2;

	// Add Size of String Table
	ptr += cue_name_buffer.size() * 6;
	if (cue_name_buffer.size() > 0) {

		for (unsigned int i = 0; i < cue_name_buffer.size(); i++) {

			if (i + 1 > cue_name_table.size()) {
				cue_name_table.push_back(fmtXSB_String_Table());
				}
			cue_name_table[i].addr = ptr;
			if (cue_name_buffer[i] == "") {
				ptr += 1;
				}
			else {
				ptr += cue_name_buffer[i].size() + 1;
				}
			}
		}
	return ptr;
	}

void fmtXSB::write_xsb (bytestream &s) {
	std::vector<uint32_t> sound_buffer_addrs;
	std::vector<uint32_t> variation_addrs;
	size_t nsize = recalc_addresses(sound_buffer_addrs, variation_addrs);

	s.writeUlong(0x4B424453);
	s.writeUshort(tool_version);
	s.writeUshort(file_version);
	s.writeUshort(0xFFFF);
	//lastModified.setCurrentDate(); // Don't Update so I can do intergrity testes on newly written files
	s.writeUlonglong(lastModified);
	s.writeUbyte(platform);
	s.writeUshort(numSimpleCues);
	s.writeUshort(numComplexCues);
	s.writeUshort(unkn3);
	s.writeUshort(cue_order_count);
	s.writeUbyte(wave_bank_count);
	s.writeUshort(sound_count);
	s.writeUlong(cue_name_buffer_size);
	s.writeUlong(simpleCuesOffset);
	s.writeUlong(complexCuesOffset);
	s.writeUlong(cue_name_buffer_addr);
	s.writeUlong(unknOffset);
	s.writeUlong(variationTablesOffset);
	s.writeUlong(unknOffset2);
	s.writeUlong(wave_bank_table_addr);
	s.writeUlong(cue_order_addr);
	s.writeUlong(cue_name_table_addr);
	s.writeUlong(sound_buffer_addr);
	s.writestring(sound_bank_name, 64);

	for (unsigned int i = 0; i < wave_bank_count; i++) {
		s.writestring(wave_banks[i], 64);
		}

	for (unsigned int i = 0; i < sound_count; i++) {
		sound_buffer[i].write_Sound(s);
		}

	for (unsigned int i = 0; i < numSimpleCues; i++) {
		simpleCueTable[i].write_simplecue_table(s, sound_buffer_addrs);
		}

	for (unsigned int i = 0; i < numComplexCues; i++) {
		complexCueTable[i].write_complexcue_table(s, sound_buffer_addrs, variation_addrs);
		}

	for (unsigned int i = 0; i < variationTable.size(); i++) {
		variationTable[i].write_Variation(s, sound_buffer_addrs);
		}

	for (unsigned int i = 0; i < cue_order_count; i++) {
		s.writeshort(cue_order_indices[i]);
		}

	unsigned int cue_count = cue_name_table.size();
	for (unsigned int i = 0; i < cue_count; i++) {
		cue_name_table[i].write_String_Table(s);
		}

	for (unsigned int i = 0; i < cue_name_buffer.size(); i++) {
		if (cue_name_buffer[i] == "") {
			s.writeUbyte(0);
			}
		else {
			s.writestring(cue_name_buffer[i]);
			}
		}

	uint32_t xsb_hash = s.fcs16(0x12, nsize - 0x12);
	s.seek(8);
	s.writeUshort(xsb_hash);
	}

void fmtXSB::write_xap (std::wstring file) {
	/*
		simple cues are not seen in re4; therefore
		I don't even bother dealing with them.

		if (there is a simple cue present then this function
		will just exit
	*/

	if ((numSimpleCues + numComplexCues) > 0) {



		std::vector<std::string> wav_files;
		std::stringstream ss;
		// Generate Wav filenames {serialized from 0 on wards... 0; 1; 2 etc}
		if (sound_count > 0) {
			wav_files = std::vector<std::string>(sound_count);
			for (unsigned int i = 0; i < sound_count; i++) {
				ss.str(std::string());
				ss << std::hex << i;
				wav_files[i] = padString(ss.str(), 8, "0", true);
				}
			}

		// Get Audio Indices
		std::vector<signed int> snd_order;
		std::vector<bool> snd_is_bgm;
		if (sound_count > 0) {
			snd_is_bgm = std::vector<bool>(sound_count);
			snd_order = std::vector<signed int> (sound_count);
			for (unsigned int i = 0; i < sound_count; i++) {
				snd_order[i] = 0;
				snd_is_bgm[i] = true;
				if (sound_buffer[i].track_count == 0) {
					snd_order[i] = sound_buffer[i].trackIndex;

					snd_is_bgm[i] = false;
					}
				else {
					snd_order[i] = sound_buffer[i].tracks[0].event.events.wav_index;

					snd_is_bgm[i] = true;
					}

				}

			}



		// Header
		std::string xap = "Signature = XACT3;\nVersion = 18;\nContent Version = 46;\nRelease = February 2010;\n\n";

		// Options
		xap += "Options\n{\n    Verbose Report = 0;\n    Generate C/C++ Headers = 1;\n}\n\n";

		// Global Settings
		xap += "Global Settings\n{\n    Xbox File = Xbox\\bio4_project.xgs;\n    ";
		xap += "Windows File = Win\\bio4_project.xgs;\n    Header File = bio4_project.h;\n    ";
		xap += "Exclude Category Names = 0;\n    Exclude Variable Names = 0;\n    ";
		xap += "Last Modified Low = 0;\n    Last Modified High = 0;\n\n    ";

		// Global Category
		xap += "Category\n    {\n        Name = Global;\n        Public = 1;\n        Background Music = 0;\n        Volume = 0;\n\n        ";
		xap += "Category Entry\n        {\n        }\n\n        Instance Limit\n        {\n            Max Instances = 255;\n            ";
		xap += "Behavior = 0;\n\n            Crossfade\n            {\n                Fade In = 0;\n                Fade Out = 0;\n                ";
		xap += "Crossfade Type = 0;\n            }\n        }\n    }\n\n    ";

		// Default Category
		xap += "Category\n    {\n        Name = Default;\n        Public = 1;\n        Background Music = 0;\n        Volume = 0;\n\n        ";
		xap += "Category Entry\n        {\n            Name = Global;\n        }\n\n        Instance Limit\n        {\n            Max Instances = 255;\n            ";
		xap += "Behavior = 0;\n\n            Crossfade\n            {\n                Fade In = 0;\n                Fade Out = 0;\n                ";
		xap += "Crossfade Type = 0;\n            }\n        }\n    }\n\n    ";

		// Music Category
		xap += "Category\n    {\n        Name = Music;\n        Public = 1;\n        Background Music = 1;\n        Volume = 0;\n\n        ";
		xap += "Category Entry\n        {\n            Name = Global;\n        }\n\n        Instance Limit\n        {\n            Max Instances = 255;\n            ";
		xap += "Behavior = 0;\n\n            Crossfade\n            {\n                Fade In = 0;\n                Fade Out = 0;\n                ";
		xap += "Crossfade Type = 0;\n            }\n        }\n    }\n\n    ";

		// OrientationAngle Variable
		xap += "Variable\n    {\n        Name = OrientationAngle;\n        Public = 1;\n        Global = 0;\n        Internal = 0;\n        ";
		xap += "External = 0;\n        Monitored = 1;\n        Reserved = 1;\n        Read Only = 0;\n        Time = 0;\n        ";
		xap += "Value = 0.000000;\n        Initial Value = 0.000000;\n        Min = -180.000000;\n        Max = 180.000000;\n    }\n\n    ";

		// DopplerPitchScalar Variable
		xap += "Variable\n    {\n        Name = DopplerPitchScalar;\n        Public = 1;\n        Global = 0;\n        Internal = 0;\n        ";
		xap += "External = 0;\n        Monitored = 1;\n        Reserved = 1;\n        Read Only = 0;\n        Time = 0;\n        ";
		xap += "Value = 1.000000;\n        Initial Value = 1.000000;\n        Min = 0.000000;\n        Max = 4.000000;\n    }\n\n    ";

		// SpeedOfSound Variable
		xap += "Variable\n    {\n        Name = SpeedOfSound;\n        Public = 1;\n        Global = 1;\n        Internal = 0;\n        ";
		xap += "External = 1;\n        Monitored = 0;\n        Reserved = 1;\n        Read Only = 0;\n        Time = 0;\n        ";
		xap += "Value = 343.500000;\n        Initial Value = 343.500000;\n        Min = 0.000000;\n        Max = 1000000.000000;\n    }\n\n    ";

		// ReleaseTime Variable
		xap += "Variable\n    {\n        Name = ReleaseTime;\n        Public = 1;\n        Global = 0;\n        Internal = 1;\n        ";
		xap += "External = 1;\n        Monitored = 1;\n        Reserved = 1;\n        Read Only = 1;\n        Time = 1;\n        ";
		xap += "Value = 0.000000;\n        Initial Value = 0.000000;\n        Min = 0.000000;\n        Max = 15000.000000;\n    }\n\n    ";

		// AttackTime Variable
		xap += "Variable\n    {\n        Name = AttackTime;\n        Public = 1;\n        Global = 0;\n        Internal = 1;\n        ";
		xap += "External = 1;\n        Monitored = 1;\n        Reserved = 1;\n        Read Only = 1;\n        Time = 1;\n        ";
		xap += "Value = 0.000000;\n        Initial Value = 0.000000;\n        Min = 0.000000;\n        Max = 15000.000000;\n    }\n\n    ";

		// NumCueInstances Variable
		xap += "Variable\n    {\n        Name = NumCueInstances;\n        Public = 1;\n        Global = 0;\n        Internal = 1;\n        ";
		xap += "External = 1;\n        Monitored = 1;\n        Reserved = 1;\n        Read Only = 1;\n        Time = 0;\n        ";
		xap += "Value = 0.000000;\n        Initial Value = 0.000000;\n        Min = 0.000000;\n        Max = 1024.000000;\n    }\n\n    ";

		// Distance Variable
		xap += "Variable\n    {\n        Name = Distance;\n        Public = 1;\n        Global = 0;\n        Internal = 0;\n        ";
		xap += "External = 0;\n        Monitored = 1;\n        Reserved = 1;\n        Read Only = 0;\n        Time = 0;\n        ";
		xap += "Value = 0.000000;\n        Initial Value = 0.000000;\n        Min = 0.000000;\n        Max = 1000000.000000;\n    }\n\n    ";

		// BIO4 Volume Variable
		xap += "Variable\n    {\n        Name = bio4_volume;\n        Public = 1;\n        Global = 0;\n        Internal = 0;\n        ";
		xap += "External = 0;\n        Monitored = 0;\n        Reserved = 0;\n        Read Only = 0;\n        Time = 0;\n        ";
		xap += "Value = 0.000000;\n        Initial Value = 0.000000;\n        Min = -1000.000000;\n        Max = 100.000000;\n    }\n\n    ";

		// Realtime Parameter Control
		xap += "RPC\n    {\n        Name = bio4_volume;\n\n        RPC Curve\n        {\n            ";
		xap += "Name = Sound::75f44141-822d-42c5-925f-de2b61a22511;\n            ";
		xap += "Property = 0;\n            Sound = 1;\n            Line Color = 4279721113;\n            Viewable = 1;\n\n            ";
		xap += "Variable Entry\n            {\n                Name = bio4_volume;\n            }\n\n            ";
		xap += "RPC Point\n            {\n                X = -904.000000;\n                Y = -9600.000000;\n                Curve = 0;\n            }\n\n            ";
		xap += "RPC Point\n            {\n                X = 0.000030;\n                Y = 0.000000;\n                Curve = 0;\n            }\n\n            ";
		xap += "RPC Point\n            {\n                X = 100.000000;\n                Y = 600.000000;\n                Curve = 0;\n            }\n        }\n    }\n}\n\n";

		// Wave Bank
		xap += "Wave Bank\n{\n    Name = " + sound_bank_name;
		xap += ";\n    Xbox File = Xbox\\" + sound_bank_name;
		xap += ".xwb;\n    Windows File = Win\\" + sound_bank_name;
		xap += ".xwb;\n    Xbox Bank Path Edited = 0;\n    Windows Bank Path Edited = 0;\n    Seek Tables = 1;\n    ";
		xap += "Compression Preset Name = <none>;\n    Xbox Bank Last Modified Low = 0;\n    Xbox Bank Last Modified High = 0;\n    ";
		xap += "PC Bank Last Modified Low = 0;\n    PC Bank Last Modified High = 0;\n    Header Last Modified Low = 0;\n    ";
		xap += "Header Last Modified High = 0;\n    Bank Last Revised Low = 0;\n    Bank Last Revised High = 0;\n";


		// Wav Files
		for (unsigned int i = 0; i < sound_count; i++) {
			xap += "\n    Wave\n    {\n        Name = " + wav_files[i];
			xap += ";\n        File = Audio\\" + wav_files[i];
			xap += ".wav;\n        Build Settings Last Modified Low = 0;\n        ";
			xap += "Build Settings Last Modified High = 0;\n    }\n";
			}
		xap += "}\n\n";

		// Sound Bank
		xap += "Sound Bank\n{\n    Name = " + sound_bank_name;
		xap += ";\n    Xbox File = Xbox\\" + sound_bank_name;
		xap += ".xsb;\n    Windows File = Win\\" + sound_bank_name;
		xap += ".xsb;\n    Xbox Bank Path Edited = 0;\n    Windows Bank Path Edited = 0;\n    Bank Last Modified Low = 0;\n    ";
		xap += "Bank Last Modified High = 0;\n    Header Last Modified High = 0;\n    Header Last Modified Low = 0;\n\n";

		// Sounds

		for (unsigned int i = 0; i < sound_count; i++) {
			xap += "    Sound\n    {\n        Name = " + to_string(snd_order[i]); //? audio index
			xap += ";\n        Volume = " + to_string((unsigned int)((sound_buffer[i].volume_as_db()) * 100.0f));
			xap += ";\n        Pitch = " + to_string(sound_buffer[i].pitch);
			xap += ";\n        Priority = " + to_string(sound_buffer[i].priority);
			xap += ";\n\n        Category Entry\n        {\n            Name = Default;\n        }\n\n        ";
			xap += "RPC Entry\n        {\n            RPC Name = bio4_volume;\n        }\n";

			// Tracks
			if (sound_buffer[i].track_count > 0) {
				for (unsigned int t = 0; t < 2; t++) {

					xap += "\n        Track\n        {\n            ";

					xap += "Volume = " + to_string((unsigned int)((sound_buffer[i].tracks[0].volume_as_db()) * 100.0f));

					xap += ";\n            Use Filter = ";

					if (sound_buffer[i].tracks[0].flags.enable_filter) {xap += "1";} else {xap += "2";}

					// Vars
					if (sound_buffer[i].tracks[0].flags.enable_filter) {
						xap += "            Filter Mode = ";

						if (sound_buffer[i].tracks[0].flags.band_pass) {
							xap += "1";
							}
						else if (sound_buffer[i].tracks[0].flags.high_pass) {
							xap += "2";
							}
						else {
							xap += "0";
							}

						xap += ";\n            Filter Frequency = " + to_string(sound_buffer[i].tracks[0].filter_freq);
						xap += ";\n            Filter Q Factor = "  + to_string(sound_buffer[i].tracks[0].filter_q) + ";";
						}

					if (t == 0) {
						xap += "\n\n            Play Wave Event\n            {\n                ";
						xap += "Break Loop = 0;\n                Use Speaker Position = ";
						if (bit::get(sound_buffer[i].tracks[t].event.events.gen_flag, 2)) {xap += "1";} else {xap += "0";}
						xap += ";\n                Use Center Speaker = ";
						if (bit::get(sound_buffer[i].tracks[t].event.events.gen_flag, 3)) {xap += "1";} else {xap += "0";}
						xap += ";\n                New Speaker Position On Loop = ";
						if (bit::get(sound_buffer[i].tracks[t].event.events.gen_flag, 4)) {xap += "1";} else {xap += "0";}
						xap += ";\n                Speaker Position Angle = " + to_string(sound_buffer[i].tracks[t].event.playwave.threesixty_pan_min  / 100.0);
						xap += ";\n                Speaker Position Arc = " + to_string(sound_buffer[i].tracks[t].event.playwave.threesixty_pan_max  / 100.0);
						xap += ";\n\n                Event Header\n                {\n                    ";
						xap += "Timestamp = " + to_string((unsigned int)sound_buffer[i].tracks[t].event.events.time_stamp);
						xap += ";\n                    Relative = 0;\n                    Random Recurrence = 0;\n                    ";
						xap += "Random Offset = " + to_string((unsigned int)sound_buffer[i].tracks[t].event.events.random_time_offset);
						xap += ";\n                }\n\n";

						if (sound_buffer[i].flags.hasComplexSound) {
							if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 13)) {
								xap += "                Pitch Variation\n                {\n";
								xap += "                    Min = " + to_string(sound_buffer[i].tracks[t].event.variable.pitch_min);
								xap += ";\n                    Max = " + to_string(sound_buffer[i].tracks[t].event.variable.pitch_max);
								xap += ";\n                    Operator = ";
								if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 1)) {xap += "1";} else {xap += "0";}
								xap += ";\n                    New Variation On Loop = ";
								if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 9)) {xap += "1";} else {xap += "0";}
								xap += ";\n                }\n\n";
								}

							if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 14)) {
								xap += "                Volume Variation\n                {\n";
								xap += "                    Min = " + to_string(sound_buffer[i].tracks[t].event.variable.volume_min);
								xap += ";\n                    Max = " + to_string(sound_buffer[i].tracks[t].event.variable.volume_max);
								xap += ";\n                    Operator = ";
								if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 3)) {xap += "1";} else {xap += "0";}
								xap += ";\n                    New Variation On Loop = ";
								if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 10)) {xap += "1";} else {xap += "0";}
								xap += ";\n                }\n\n";
								}

							if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 15)) {
								xap += "                Frequency Variation\n                {\n";
								xap += "                    Min = " + to_string(sound_buffer[i].tracks[t].event.variable.filter_freq_min);
								xap += ";\n                    Max = " + to_string(sound_buffer[i].tracks[t].event.variable.filter_freq_max);
								xap += ";\n                    Operator = ";
								if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 5)) {xap += "1";} else {xap += "0";}
								xap += ";\n                    New Variation On Loop = ";
								if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 11)) {xap += "1";} else {xap += "0";}
								xap += ";\n                }\n\n";
								}

							if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 16)) {
								xap += "                Q Factor Variation\n                {\n";
								xap += "                    Min = " + to_string(sound_buffer[i].tracks[t].event.variable.filter_q_min);
								xap += ";\n                    Max = " + to_string(sound_buffer[i].tracks[t].event.variable.filter_q_max);
								xap += ";\n                    Operator = ";
								if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 7)) {xap += "1";} else {xap += "0";}
								xap += ";\n                    New Variation On Loop = ";
								if (bit::get(sound_buffer[i].tracks[t].event.variable.var_flag, 12)) {xap += "1";} else {xap += "0";}
								xap += ";\n                }\n\n";
								}


							}
						xap += "                Wave Entry\n                {\n                    ";
						xap += "Bank Name = " + sound_bank_name;
						xap += ";\n                    Bank Index = 0;\n                    ";
						xap += "Entry Name = " + wav_files[snd_order[i]];
						xap += ";\n                    Entry Index = " + to_string(snd_order[i]); //? audio index
						xap += ";\n                    Weight = 255;\n                    Weight Min = 0;\n                }\n            }";
						}

					xap += "\n        }\n";
					}

				}
			else {





				xap += "        Track\n        {\n            Volume = 0;\n            Use Filter = 0;\n\n            ";
				xap += "Play Wave Event\n            {\n                Break Loop = 0;\n                ";
				xap += "Use Speaker Position = 0;\n                Use Center Speaker = 0;\n                ";
				xap += "New Speaker Position On Loop = 1;\n                Speaker Position Angle = 0.000000;\n                ";
				xap += "Speaker Position Arc = 0.000000;\n\n                Event Header\n                {\n                    ";
				xap += "Timestamp = 0;\n                    Relative = 0;\n                    Random Recurrence = 0;\n                    ";
				xap += "Random Offset = 0;\n                }\n\n                Wave Entry\n                {\n                    ";
				xap += "Bank Name = " + sound_bank_name;
				xap += ";\n                    Bank Index = 0;\n                    ";
				xap += "Entry Name = " + wav_files[snd_order[i]];
				xap += ";\n                    ";
				xap += "Entry Index = " + to_string(snd_order[i]); //? audio index
				xap += ";\n                    Weight = 255;\n                    Weight Min = 0;\n                }\n            }\n        }\n";
				}
			xap += "    }\n\n";
			}

		// Cues
		for (unsigned int i = 0; i < complexCueTable.size(); i++) {
			xap += "    Cue\n    {\n        Name = " + cue_name_buffer[i];
			xap += ";\n\n        Variation\n        {\n            Variation Type = 0;\n            Variation Table Type = 1;\n            ";
			xap += "New Variation on Loop = 0;\n        }\n\n        Sound Entry\n        {\n            ";
			xap += "Name = " + to_string(snd_order[complexCueTable[i].sound_offset]);
			xap += ";\n            Index = " + to_string(complexCueTable[i].sound_offset);
			xap += ";\n            Weight Min = 0;\n            Weight Max = 255;\n        }\n\n        ";
			xap += "Instance Limit\n        {\n            Max Instances = " + to_string((int)complexCueTable[i].instances.limit);
			xap += ";\n            ";
			if (complexCueTable[i].instances.flag > 0) {
				xap += "Behavior = 4";
				}
			else {
				xap += "Behavior = 0";
				}
			xap += ";\n\n            Crossfade\n            {\n                ";
			xap += "Fade In = " + to_string(complexCueTable[i].instances.fade_in);
			xap += ";\n                Fade Out = " + to_string(complexCueTable[i].instances.fade_out);
			xap += ";\n                Crossfade Type = 0";
			xap += ";\n            }\n        }\n    }\n\n    ";
			}
		xap += "}\n";

		if (xap.size() > 0) {
			bytestream s;
			s.writeFileW(file, 0, xap.size(), (char*)xap.c_str());
			} else {std::cout << "XAP is Empty\n";}


		}
	else if (numSimpleCues == 0) {
		std::cout << "Erorr: \tSimple Cues Are Present" << std::endl;
		}
	}

