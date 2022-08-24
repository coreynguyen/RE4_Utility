#include "fmtXWB.h"


fmtXWB_Segment::fmtXWB_Segment() {
	addr = 0;
	size = 0;
	}

void fmtXWB_Segment::read_fmtXWB_Segment(bytestream &f) {
	addr = f.readUlong();
	size = f.readUlong();
	}

fmtXWB_Audio::fmtXWB_Audio() {
	addr = 0;
	size = 0;
	has_readahead = false;
	has_loopcache = false;
	has_nolooptail = false;
	has_loopskip = false;
	duration = 0;
	loop_start = 0;
	loop_end = 0;
	type = 0;
	channels = 0;
	samples_per_section = 0;
	alignment = 0;
	bit_depth = 0;
	data.close();
	}

void fmtXWB_Audio::read_fmtXWB_Audio(bytestream &f) {
	uint32_t val = 0;
	val = f.readUlong();
	has_readahead = bit::get(val, 1);
	has_loopcache = bit::get(val, 2);
	has_nolooptail = bit::get(val, 3);
	has_loopskip = bit::get(val, 4);
	duration = (val >> 4) & ((1 << 28) - 1);
	val = f.readUlong();
	type = val & ((1 << 2) - 1);
	channels = (val >> 2) & ((1 << 3) - 1);
	samples_per_section = (val >> 5) & ((1 << 18) - 1);
	alignment = (val >> 23) & ((1 << 8) - 1);
	bit_depth = (((val >> 31) & ((1 << 1) - 1)) + 1) * 8;
	addr = f.readUlong();
	size = f.readUlong();
	loop_start = f.readUlong();
	loop_end = f.readUlong();
	}

void fmtXWB_Audio::write_as_wav(bytestream &s) {

	fmtWAV wav;
	wav.fmt.type = 1;	// 1 for PCM
	wav.fmt.channels = channels;
	wav.fmt.sample_rate = samples_per_section;
	wav.fmt.byte_rate = (unsigned int)(samples_per_section * channels * bit_depth / 8.0);
	wav.fmt.alignment = (unsigned int)(channels * bit_depth / 8.0);
	wav.fmt.bits_per_sample = bit_depth;
	wav.data.copy(data.stream, data.size);
	if (loop_start > 0 || loop_end > 0) {
		fmtWAV_Sampler_Loop smpl;
		smpl.start = loop_start;
		smpl.end = loop_start + loop_end + 1;
		wav.smpl.sample_loops.push_back(smpl);
		wav.smpl.num_sample_loops = 1;
		}
	//wav.wave.duration = data.size() / {wav.wave.bits_per_sample * wav.wave.channels} / wav.wave.bits_per_sample / 1000

	wav.write_riff(s);
	}

fmtXWB_Bank::fmtXWB_Bank() {
	has_streaming = false;
	flag02 = false;
	flag03 = false;
	flag04 = false;
	flag05 = false;
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
	has_entrynames = false;
	has_compact_fmt = false;
	has_disabled_async = false;
	has_seektables = true;
	flag21 = false;
	flag22 = false;
	flag23 = false;
	flag24 = false;
	flag25 = false;
	flag26 = false;
	flag27 = false;
	flag28 = false;
	flag29 = false;
	flag30 = false;
	flag31 = false;
	flag32 = false;
	}

void fmtXWB_Bank::read_bank_flag(bytestream &f) {
	uint32_t val = f.readUlong();
	has_streaming = bit::get(val, 1);
	flag02 = bit::get(val, 2);
	flag03 = bit::get(val, 3);
	flag04 = bit::get(val, 4);
	flag05 = bit::get(val, 5);
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
	has_entrynames = bit::get(val, 17);
	has_compact_fmt = bit::get(val, 18);
	has_disabled_async = bit::get(val, 19);
	has_seektables = bit::get(val, 20);
	flag21 = bit::get(val, 21);
	flag22 = bit::get(val, 22);
	flag23 = bit::get(val, 23);
	flag24 = bit::get(val, 24);
	flag25 = bit::get(val, 25);
	flag26 = bit::get(val, 26);
	flag27 = bit::get(val, 27);
	flag28 = bit::get(val, 28);
	flag29 = bit::get(val, 29);
	flag30 = bit::get(val, 30);
	flag31 = bit::get(val, 31);
	flag32 = bit::get(val, 32);
	}

void fmtXWB_Bank::write_bank_flag(bytestream &s) {
	uint32_t val = 0;
	val = bit::set(val, 1, has_streaming);
	val = bit::set(val, 2, flag02);
	val = bit::set(val, 3, flag03);
	val = bit::set(val, 4, flag04);
	val = bit::set(val, 5, flag05);
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
	val = bit::set(val, 17, has_entrynames);
	val = bit::set(val, 18, has_compact_fmt);
	val = bit::set(val, 19, has_disabled_async);
	val = bit::set(val, 20, has_seektables);
	val = bit::set(val, 21, flag21);
	val = bit::set(val, 22, flag22);
	val = bit::set(val, 23, flag23);
	val = bit::set(val, 24, flag24);
	val = bit::set(val, 25, flag25);
	val = bit::set(val, 26, flag26);
	val = bit::set(val, 27, flag27);
	val = bit::set(val, 28, flag28);
	val = bit::set(val, 29, flag29);
	val = bit::set(val, 30, flag30);
	val = bit::set(val, 31, flag31);
	val = bit::set(val, 32, flag32);
	s.writeUlong(val);
	}

fmtXWB::fmtXWB() {
	fileid = 0x444E4257;
	tool_version = 46;
	file_version = 44;
	audio_count = 0;
	bank_name = "";
	meta_size = 0;
	name_size = 64;
	alignment = 0;
	compact_fmt = 0;
	build_time = 0;
	bank_addr = 0;
	bank_size = 0;
	bank.clear();
	}

void fmtXWB::read_xwb(bytestream &f) {
	size_t pos = f.tell();
	size_t name_pos = 0;
	if ((fileid = f.readUlong()) == 0x444E4257) {
		tool_version = f.readUlong();
		if ((file_version = f.readUlong()) >= 44) {
			for (unsigned int i = 0; i < 5; i++) {
				segments[i].read_fmtXWB_Segment(f);
				}
			for (unsigned int seg = 0; seg < 5; seg++) {
				if (segments[seg].addr > 0) {
					f.seek((pos + segments[seg].addr));
					switch (seg) {
						case 0: {	// Bank Information
							bank_info.read_bank_flag(f);
							audio_count = f.readUlong();
							name_pos = f.tell();
							bank_name = f.readstring(64);
							f.seek(name_pos + 64);
							meta_size = f.readUlong();
							name_size = f.readUlong();
							alignment = f.readUlong();
							compact_fmt = f.readUlong();
							build_time = f.readUlonglong();
							break;
							}
						case 1: {	// Audio Bank Table
							if (audio_count > 0) {
								bank = std::vector<fmtXWB_Audio>(audio_count);
								for (unsigned int i = 0; i < audio_count; i++) {
									bank[i].read_fmtXWB_Audio(f);
									}
								}
							break;
							}
						case 2: {	// Audio Bank Address
							bank_addr = segments[seg].addr;
							break;
							}
						case 3: {break; }	// Empty?
						case 4: {	// Audio Bank

							for (unsigned int i = 0; i < audio_count; i++) {
								bank[i].data.copy(f.stream, bank[i].size, pos + bank_addr + bank[i].addr);
								}
							break;
							}
						}
					}
				}
			} else { std::cout << "Unsupported Version" << std::endl; }
		} else { std::cout << "Unsupported File" << std::endl; }
	}

void fmtXWB::dump_xwb(std::wstring fpath, std::wstring wav_name) {

	unsigned int c = 0;

	// check fpath has a trailing slash
	if (fpath != L"") {

		std::wstring n = fpath.substr(fpath.size() - 1, 1);

		if (n != L"\\" && n != L"/") {
			fpath += L"\\";
			}

		if (!win::doesFileExistW(fpath)) {
			win::makeDirW(fpath);
			}

		unsigned int num_wav = bank.size();
		std::wstring wavfile;
		if (num_wav > 0) {



			std::stringstream ss;
			for (unsigned int i = 0; i < num_wav; i++) {
				if (bank[i].data.size > 0) {

					// generate file names
					ss.str(std::string());
					ss << std::hex << i;

					wavfile = fpath + wav_name + string_to_wstring(padString(ss.str(), 8, "0", true)) + L".wav";


					bytestream s;
					bank[i].write_as_wav(s);
					if (!s.writeFileW(wavfile)) {
						std::wcout << L"Error: Failed to Write Wav File [" << wavfile << L"]\n";
						}
					s.close();
					c += 1;
					}
				}
			} else { std::cout << "Error: XWB Contains No Wav Files\n"; }

		if (c == 0) {
			std::cout << "error: \tnothing to dump\n";
			}
		}
	}
