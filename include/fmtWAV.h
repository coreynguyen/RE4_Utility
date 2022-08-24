/*	======================================================================

	Maxscript:    [PC] Resident Evil 4
	Author:        mariokart64n
	Date:           September 29 2020

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Editing of the WAV files (Wave Audio File)

	Change Log:
		2022-08-02
		 - fixed the size function, it was calculating the wrong WAV size

		2020-09-29
		 - Wrote IT!

	======================================================================	*/

#ifndef FMTWAV_H
#define FMTWAV_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <sstream>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"
#include "vectorext.h"
#include "filesystem.h"


struct fmtWAV_Chunk {
	uint32_t type;
	uint32_t size;

	// stuff for seeking
	size_t pos;
	size_t end;
	fmtWAV_Chunk ();
	void read_wav_chunk (bytestream &f);
	};

struct fmtWAV_Sampler_Loop { // 24 bytes
	uint32_t point_id;
	uint32_t type;
	uint32_t start;
	uint32_t end;
	uint32_t fraction;
	uint32_t play_count;
	fmtWAV_Sampler_Loop ();
	void read_wav_sampler_loop (bytestream &f);
	void write_wav_sampler_loop (bytestream &s);
	};

struct fmtWAV_Sampler { // 32 + n bytes
	uint32_t manufacturer;
	uint32_t product;
	uint32_t sample_period;
	uint32_t midi_unity_note;
	uint32_t midi_pitch_fraction;
	uint32_t smpte_format;
	uint32_t smpte_offset;
	uint32_t num_sample_loops;
	uint32_t sampler_data; // size of additional data
	std::vector<fmtWAV_Sampler_Loop> sample_loops;

	fmtWAV_Sampler ();
	void read_wav_sampler (bytestream &f);
	void write_wav_sampler (bytestream &s);
	};

struct fmtWAV_Format { // 16 bytes
	uint16_t type;	// 1 for PCM
	uint16_t channels;
	uint32_t sample_rate;
	uint32_t byte_rate;	// SampleRate * NumChannels * BitsPerSample/8
	uint16_t alignment; // NumChannels * BitsPerSample/8
	uint16_t bits_per_sample;
	fmtWAV_Format ();
	void read_wav_fmt (bytestream &f);
	void write_wav_fmt (bytestream &s);
	};

struct fmtWAV {
	fmtWAV_Format fmt;
	fmtWAV_Sampler smpl;
	bytestream data;
	size_t size ();
	void read_riff (bytestream &f);
	void write_riff (bytestream &s);
	};

#endif // FMTWAV_H
