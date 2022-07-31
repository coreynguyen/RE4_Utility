#include "fmtWAV.h"


fmtWAV_Chunk::fmtWAV_Chunk () {
	type = 0;
	size = 0;
	pos = 0;
	end = 0;
	}

void fmtWAV_Chunk::read_wav_chunk (bytestream &f) {
	type = f.readUlong();
	size = f.readUlong();
	pos = f.tell();
	end = pos + size;
	}

fmtWAV_Sampler_Loop::fmtWAV_Sampler_Loop () {
	point_id = 0;
	type = 0;
	start = 0;
	end = 0;
	fraction = 0;
	play_count = 0;
	}

void fmtWAV_Sampler_Loop::read_wav_sampler_loop (bytestream &f) {
	point_id = f.readUlong();
	type = f.readUlong();
	start = f.readUlong();
	end = f.readUlong();
	fraction = f.readUlong();
	play_count = f.readUlong();
	}

void fmtWAV_Sampler_Loop::write_wav_sampler_loop (bytestream &s) {
	s.writeUlong(point_id);
	s.writeUlong(type);
	s.writeUlong(start);
	s.writeUlong(end);
	s.writeUlong(fraction);
	s.writeUlong(play_count);
	}

fmtWAV_Sampler::fmtWAV_Sampler () {
	manufacturer = 0;
	product = 0;
	sample_period = 0;
	midi_unity_note = 0x3C;
	midi_pitch_fraction = 0;
	smpte_format = 0;
	smpte_offset = 0;
	num_sample_loops = 0;
	sampler_data = 0;
	}

void fmtWAV_Sampler::read_wav_sampler (bytestream &f) {
	manufacturer = f.readUlong();
	product = f.readUlong();
	sample_period = f.readUlong();
	midi_unity_note = f.readUlong();
	midi_pitch_fraction = f.readUlong();
	smpte_format = f.readUlong();
	smpte_offset = f.readUlong();
	num_sample_loops = f.readUlong();
	sampler_data = f.readUlong();
	sample_loops.clear();
	if (num_sample_loops > 0) {
		sample_loops = std::vector<fmtWAV_Sampler_Loop>(num_sample_loops);

		for (unsigned int i = 0; i < num_sample_loops; i++) {
			sample_loops[i].read_wav_sampler_loop(f);
			}
		}
	}

void fmtWAV_Sampler::write_wav_sampler (bytestream &s) {
	s.writeUlong(manufacturer);
	s.writeUlong(product);
	s.writeUlong(sample_period);
	s.writeUlong(midi_unity_note);
	s.writeUlong(midi_pitch_fraction);
	s.writeUlong(smpte_format);
	s.writeUlong(smpte_offset);
	s.writeUlong(num_sample_loops);
	s.writeUlong(sampler_data);
	for (unsigned int i = 0; i < num_sample_loops; i++) {
		sample_loops[i].write_wav_sampler_loop(s);
		}
	}

fmtWAV_Format::fmtWAV_Format () {
	type = 1;
	channels = 0;
	sample_rate = 0;
	byte_rate = 0;
	alignment = 0;
	bits_per_sample = 0;
	}

void fmtWAV_Format::read_wav_fmt (bytestream &f) {
	type = f.readUshort();
	channels = f.readUshort();
	sample_rate = f.readUlong();
	byte_rate = f.readUlong();
	alignment = f.readUshort();
	bits_per_sample = f.readUshort();
	}

void fmtWAV_Format::write_wav_fmt (bytestream &s) {
	s.writeUshort(type);
	s.writeUshort(channels);
	s.writeUlong(sample_rate);
	s.writeUlong(byte_rate);
	s.writeUshort(alignment);
	s.writeUshort(bits_per_sample);
	}

size_t fmtWAV::size () {
	size_t nsize = 44 + data.size;
	if (smpl.sample_loops.size() > 0) {
		nsize += 40 + (smpl.sample_loops.size() * 24);
		}
	return nsize;
	}

void fmtWAV::read_riff (bytestream &f) {
	if (f.size > 16) {
		fmtWAV_Chunk riff;
		riff.read_wav_chunk(f);

		if (riff.type == 0x46464952 && riff.size > 0) { // 'RIFF'

			uint32_t contents = f.readUlong();
			if (contents == 0x45564157) { // 'WAVE'
				fmtWAV_Chunk chunk;
				do {
					chunk.read_wav_chunk(f);
					if (chunk.size == 0) {continue;}
					switch (chunk.type) {
						case 0x20746D66: { // 'fmt'
							fmt.read_wav_fmt(f);
							break;
							}
						case 0x61746164: { // 'data'
							data.copy(f.stream, chunk.size);
							break;
							}
						case 0x6C706D73: { // 'smpl'
							smpl.read_wav_sampler(f);
							break;
							}
						}
					} while (f.tell() < riff.end);
				} else {std::cout << "unsupported chunk\n";}
			}
		} else {std::cout << "Invalid File Size\n";}
	}

void fmtWAV::write_riff (bytestream &s) {

	s.resize(size());

	s.writeUlong(0x46464952); // 'RIFF'
	s.writeUlong(size() - 8);
	s.writeUlong(0x45564157); // 'WAVE'

	s.writeUlong(0x20746D66); // 'fmt'
	s.writeUlong(16);
	fmt.write_wav_fmt(s);

	s.writeUlong(0x61746164); // 'data'
	s.writeUlong(data.size);

	size_t pos = s.tell();
	s.copy(data.stream, data.size, 0, pos);

	if (smpl.sample_loops.size() > 0) {
		s.seek(pos + data.size);
		s.writeUlong(0x6C706D73); // 'smpl'
		s.writeUlong(32 + (smpl.sample_loops.size() * 24));
		smpl.write_wav_sampler(s);
		}
	}
