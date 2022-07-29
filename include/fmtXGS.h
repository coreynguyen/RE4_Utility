#ifndef FMTXGS_H
#define FMTXGS_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"


struct fmtXGS_Category { // 10 Bytes
	int8_t max_instances; // if ({-1} then disabled
	uint16_t fade_in; // divide by 1000 to get seconds
	uint16_t fade_out; // divide by 1000 to get seconds
	uint8_t flag;
	/*
		87654321
		////////	0x
		00000000	00		Behavior at Max Instance: Fail To Play
		* if (0x01 and 0x02 not set then Crossfade Type: {1} Linear
		00000001	01		Crossfade Type: {2} Logarithmic
		00000010	02		Crossfade Type: {3} Equal Power
		00000100	04
		00001000	08		Behavior at Max Instance: Queue
		* if (any below are active; then Behavior at Max Instance: Replace
		00010000	10		Replace Instance: {2} Oldest
		00100000	20		Replace Instance: {1} Lowest Priority * if (both and 0x08 is on then Replace Instance: {3} Quietest
		01000000	40
		10000000	80
		00100010
	*/
	int8_t unk003;
	int8_t unk004;
	int8_t volume_db;
	int8_t unk005;

	/*char[64]*/std::string name;
	uint16_t unk006; // name length?

	fmtXGS_Category ();
	void read_xgs_category (bytestream &f);
	void write_xgs_category (bytestream &s);
	};

struct fmtXGS_Varaible { // 13 Bytes
	uint8_t flag;
	float init_val;
	float var_range_start;
	float var_range_end ;
	std::string name;
	uint16_t unk006; // name length?
	fmtXGS_Varaible ();
	void read_xgs_variable (bytestream &f);
	void write_xgs_variable (bytestream &s);
	};

struct fmtXGS_RPC_Curve { // 9 Bytes
	float value;
	float parameter;
	uint8_t curvature;
	/*
		0x00 	Linear
		0x01 	Fast
		0x02 	Slow
		0x03 	Sin / Cos
	*/
	fmtXGS_RPC_Curve ();
	void read_rpc_curve (bytestream &f);
	void write_rpc_curve (bytestream &s);
	};

struct fmtXGS_RPC { // 5 Bytes + {n * 9} Realtime Parameter Control
	uint16_t varaible_type;
	/*
		0x07 	CueInstance
		0x06 	Distance
		0x04 	DopplerPitchScaler
		0x00 	NumCueInstances
		0x03 	OrientationAngle
		0x05 	SpeedOfSound
	*/
	uint8_t num_curve_points;
	uint16_t parameter_type;
	/*
		0x03 	Filter Frequency
		0x04 	Filter Q Factor
		0x01 	Ptich
		0x00 	Volume
	*/
	std::vector<fmtXGS_RPC_Curve> points;
	fmtXGS_RPC ();
	void read_rpc (bytestream &f);
	void write_rpc (bytestream &s);
	};

struct fmtXGS { // 77 Bytes {Header} + Varaible {Tables}
	/*
		Xbox Global Settings
		http://wiki.xentax.com/index.php/XACT_XWB_XSB_XGS_Audio#XGS_Format_Specifications
	*/
	uint32_t filetype;					// "XGSF"
	uint16_t tool_version;							// 0x2E
	uint16_t file_version;							// 0x2B
	uint16_t crc;										// fcs16 checksum of all following data after the date stamp
	uint64_t lastModified;				// 100 NanoSeconds since January 1; 1601
	uint8_t platform;								// 1:PC; 3:XBOX
	uint16_t categories_count;
	uint16_t variables_count;
	uint16_t unknown1_count;  								// ?
	uint16_t unknown2_count;  								// ?
	uint16_t param_ctrls_count; // RPC
	uint16_t dsp_presets_count;
	uint16_t dsp_params_count;
	int32_t categories_addr;
	int32_t variables_addr;
	int32_t unknown1_addr;   					// points to "1"
	int32_t category_name_addr;
	int32_t unknown2_addr;   					// points to "2" and "3"
	int32_t variable_name_addr;
	int32_t category_names_addr;
	int32_t variable_names_addr;
	int32_t param_ctrls_addr;  								// "FF FF FF FF" if (there are no RPCs
	int32_t dsp_presets_addr;  					// "FF FF FF FF" if (there are no DSP presets
	int32_t dsp_params_addr;  					// "FF FF FF FF" if (there are no DSP params

	std::vector<fmtXGS_Category> categories;
	std::vector<fmtXGS_Varaible> variables;
	std::vector<fmtXGS_RPC> param_ctrls;
	std::vector<int16_t> unknown1;
	std::vector<int16_t> unknown2;

	fmtXGS ();
	void read_xgs (bytestream &f);
	void write_xgs (bytestream &s);
	};

#endif // FMTXGS_H
