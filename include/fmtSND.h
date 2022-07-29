/*	======================================================================

	Maxscript:    [PC] Resident Evil 4
	Author:        mariokart64n
	Date:           July 2 2022

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		reads the SND that iss present in the UDAS

	Change Log:
		2022-07-28
		 - wrote xml exporter
		 - renamed some of the class variables with the symbol names provided by emoose

		2022-07-25
		 - testing and debugging

		2022-07-18
		 - noticed that some files have a different structure. the first table is missing
		    and it would appear other tables are now larger then before...

		2022-07-04
		 - finished write back function, departing with this until the XSB / XWB is done.

		2022-07-02
		 - Mr Curious Provided notes from anonymous on how to add a sound entry to
		    the SND. I reversed the SND, to accommodate the supplied information to add
			enties to the SND.



	======================================================================	*/

#ifndef FMTSND_H
#define FMTSND_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "filesystem.h"
#include "vectorext.h"
#include "stringext.h"

#include "fmtUDAS.h"
#include "rapidxml_ext.h"


struct fmtHED_Block5 { // n bytes
	uint32_t count;
	std::vector<uint32_t> addrs;
	std::vector<bytestream> data; // byte array
	fmtHED_Block5 ();
	size_t size ();
	void read_hed_block5 (bytestream &f, size_t endpos);
	size_t write_hed_block5 (bytestream &s);
	};

struct fmtHED_Block4 { // 24 Bytes
	uint16_t unk060;
	uint16_t unk061;
	uint16_t unk062;
	uint16_t unk063;
	uint16_t unk064;
	uint16_t unk065;
	uint16_t unk066;
	uint16_t unk067;
	uint32_t unk068;
	uint32_t unk069;
	fmtHED_Block4 ();
	void read_hed_block4 (bytestream &f);
	void write_hed_block4 (bytestream &s);
	};

struct fmtHED_WTADPCM { // 46 Bytes
	uint16_t unk050[16]; // a[8][2]
	/*
		this section looks like 8 enties of 4 bytes per entry; data seems dense not sure what it is
	*/
	uint16_t gain;
	uint16_t pred_scale;
	uint16_t yn1;
	uint16_t yn2;
	uint16_t loop_pred_scale;
	uint16_t loop_yn1;
	uint16_t loop_yn2;
	fmtHED_WTADPCM ();
	void read_wt_adpcm (bytestream &f);
	void write_wt_adpcm (bytestream &s);
	};

struct fmtHED_WTSAMPLE { // 16 bytes
	/*
		?points to the second entry in the SND {UDAS} which I called DSP
		I would assume they are streams of audio
	*/
	uint16_t format;
	uint16_t sampleRate; // hertz?
	uint32_t offset; // relative address in buffer ?
	uint32_t length;
	uint16_t adpcmIndex;
	uint16_t unk043; // padding?
	fmtHED_WTSAMPLE ();
	void read_wt_sample (bytestream &f);
	void write_wt_sample (bytestream &s);
	};

struct fmtHED_WTART { // 80 bytes
	int32_t lfoFreq;
	int32_t lfoDelay;
	int32_t lfoAtten;
	int32_t lfoPitch;
	int32_t lfoMod2Atten;
	int32_t lfoMod2Pitch;
	int32_t eg1Attack;
	int32_t eg1Decay;
	int32_t eg1Sustain;
	int32_t eg1Release;
	int32_t eg1Vel2Attack;
	int32_t eg1Key2Decay;
	int32_t eg2Attack;
	int32_t eg2Decay;
	int32_t eg2Sustain;
	int32_t eg2Release;
	int32_t eg2Vel2Attack;
	int32_t eg2Key2Decay;
	int32_t eg2Pitch;
	int32_t pan;
	fmtHED_WTART ();
	void read_wt_art (bytestream &f);
	void write_wt_art (bytestream &s);
	};

struct fmtHED_WTREGION { // 24 Bytes
	uint8_t unityNote;
	uint8_t keyGroup;
	int16_t fineTune;
	int32_t attn;
	uint32_t loopStart;
	uint32_t loopLength;
	uint32_t articulationIndex;
	uint32_t sampleIndex; // same as index 1
	fmtHED_WTREGION ();
	void read_wt_region (bytestream &f);
	void write_wt_region (bytestream &s);
	};

struct fmtHED_WTFILEHEADER { // BLUE
	/*
		there isnt a count provided; it needs to be derived from the addresses
	*/
	uint32_t offsetPercussiveInst; // always 24? pointer table size?
	uint32_t offsetMelodicInst; // same as offsetMelodicInst?
	uint32_t offsetRegions;
	uint32_t offsetArticulations;
	uint32_t offsetSamples;
	uint32_t offsetAdpcmContext;

	// Tables
	std::vector<int16_t> table1; // list of indices; 2 bytes per {pad table to 4 bytes}
	std::vector<fmtHED_WTREGION> region;
	std::vector<fmtHED_WTART> art; // articulations
	std::vector<fmtHED_WTSAMPLE> sample;
	std::vector<fmtHED_WTADPCM> adpcm;

	// this block i Not padded to 32?
	fmtHED_WTFILEHEADER ();
	size_t size ();
	void read_wt_fileheader (bytestream &f, size_t end_pos);
	size_t write_wt_fileheader (bytestream &s);
	};

struct fmtHED_Block2_Entry { // 2 + n Bytes ?'SBL_DATA'
	int16_t index; // ID; -1 is not set; range [0  - 32]
	uint16_t count; // ? 'num'
	int16_t unk004; // ? 'call_no'
	std::vector<uint16_t> unk005; // ? 'data'
	fmtHED_Block2_Entry ();
	size_t size ();
	void read_hed_block2_entry (bytestream &f);
	void write_hed_block2_entry (bytestream &s);
	};

struct fmtHED_Block2 { // 128 Bytes  + entries
	/*
		this table begins with 128 bytes reserved for defining 32 address pointers {32bit int}
		I don't bother storing the pointers; isntead I reserve
	*/
	std::vector<fmtHED_Block2_Entry> entry;
	bool forceWrite; // force writting of the table
	fmtHED_Block2 ();
	size_t size ();
	void read_hed_block2 (bytestream &f);
	size_t write_hed_block2 (bytestream &s);
	};

struct fmtHED_Block1 { // RED

	uint32_t count; // this count is only for block4; count for block3 could be derived by reading entries on block4
	uint32_t block3_addr; // block 3 addr
	uint32_t block4_addr; // block 4 addr
	uint32_t block5_addr; // block 5 addr


	// all sub-blocks are byte aligned to 32 from start of this block
	fmtHED_WTFILEHEADER block3;
	std::vector<fmtHED_Block4> block4;
	fmtHED_Block5 block5;
	fmtHED_Block1 ();
	size_t size ();
	void read_hed_block1 (bytestream &f, size_t endpos);
	size_t write_hed_block1 (bytestream &s);
	};

struct fmtHED { // 32 Bytes + Tables GREEN ?'SND_HEADER'

	/*
	[DAT]
	 |
	[DAS] * can be multiple
	  |
	[SND] * can be multiple
	  |
	  L[TABLE1]
	  |	 |
	  |	 L[TABLE2]
	  |	 |	|
	  |	 |	L[TABLE3]
	  |	 | 	| 	|
	  |	 | 	|	L[INDICES1]
	  |	 | 	|	|
	  |	 | 	|	L[INDICES2]
	  |	 | 	|	|
	  |	 | 	|	L[TABLE3]
	  |	 | 	|	|
	  |	 | 	|	L[TABLE4]	////	+
	  |	 | 	|	|						|
	  |	 | 	|	L[UNKNOWN2] 	|
	  |	 | 	|							|
	  |	 | 	L[UNKNOWN3]			|
	  |	 |								|
	  |	 L[UNKNOWN4]			|
	  |	 	|							|
	  |	 	L[UNKNOWN5]			|
	  |	 								|
	  L[BUFFER] //////////-	+

	*/

	uint32_t block1_addr; // ? 'blk_addr'
	uint32_t block2_addr; // goes to block of 0's ?'sbl_addr'

	// all tables are padded to 32 bytes
	fmtHED_Block1 block1;
	fmtHED_Block2 block2; // ?'SBL_DATA'
	fmtHED ();
	size_t size ();
	void read_hed (bytestream &f, size_t endpos);
	size_t write_hed (bytestream &s);
	};

struct fmtDSP { // Sound Data
	bytestream buffer; // byte array
	size_t size ();
	void read_dsp (bytestream &f, size_t bsize);
	size_t write_dsp (bytestream &s);
	};

struct fmtSND_Entry {
	signed int id;
	fmtHED hed;
	fmtDSP dsp; // on PC this is dummied and has the same address as the HED entry
	fmtSND_Entry ();
	void read_snd_entry (bytestream &f, size_t &pos, fmtUDAS_Entry &hed_entry, fmtUDAS_Entry &dsp_entry);
	void write_snd_hed_entry (bytestream &s);
	void write_snd_dsp_entry (bytestream &s);
	};

struct fmtSND {
	fmtUDAS das; // huh probably dont need this here
	int32_t fileid;
	std::vector<fmtSND_Entry> playlists;
	fmtSND ();
	size_t size ();
	bool read_snd (bytestream &f);
	void write_snd (bytestream &s);
	};

struct fmtDAT_SND_Package {
	/*
		the SND is actually a DAS which contain a header and a sound data resource.
		the SND/DAS can also be defined lumped together as there may be several SND/DAS
		written together.

		for that the SND/DAS should be read until the end of the file is reached.

		Therefore never assume a SND is just one DAS; it can be multiple ones
	*/
	std::vector<fmtSND> snd;

	size_t size ();
	bool read_dat_snd (bytestream &f);
	void write_dat_snd (bytestream &s);
	void xml_export (std::wstring file);
	void xml_import (rapidxml::xml_document<> &doc);
	};


#endif // FMTSND_H
