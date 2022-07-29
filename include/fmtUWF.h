#ifndef FMTUWF_H
#define FMTUWF_H


#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <vector>

#include "appsettings.h"
#include "scriptini.h"
#include "bytestream.h"
#include "stringext.h"


struct fmtUWF_S_Curve {	// 16 bytes
	float position[2];
	float vector_right; // angle from position that influences the s-curve
	float vector_left; // angle from position that influences the s-curve
	fmtUWF_S_Curve ();
	void read (bytestream &f);
	void write (bytestream &s);
	};

struct fmtUWF_Anim { // 4 + {16 x n} bytes
	uint32_t num_curves;
	std::vector<fmtUWF_S_Curve> curves;
	fmtUWF_Anim ();
	void read (bytestream &f);
	void write (bytestream &s);
	};

struct fmtUWF_Block1 {
	uint8_t unk041;
	uint8_t unk042;
	uint8_t unk043;
	uint8_t unk044;
	uint32_t count;
	std::vector<float> data;
	fmtUWF_Block1 ();
	void read (bytestream &f);
	void write (bytestream &s);
	};

struct fmtUWF_Layer {	// 140 bytes
	uint32_t enable_flag;
	uint8_t mark_id;
	uint8_t unk004;
	uint8_t unk005;
	uint8_t unk006;
	uint8_t unk007;
	uint8_t isGroup;
	uint8_t unk008;
	uint8_t tex_id;
	uint8_t layout_flag;
	/*
		Base:
			0x00: CT center
			0x01: LU left upper
			0x02: RU right upper
			0x03: RD right down
			0x04: LD left down

	Grid Spacing is bit masked?:
		0x00; 0x10; 0x20; 0x30; 0x40; 0x50; 0x60; 0x70
	*/
	uint8_t loop_flag;
	/*
	Loop:
		0 = Off; 2 = On; 3 = Pos Loop On; 8 = Rotation Loop On
	*/
	uint8_t axis_flag;
	/*
	Axis:
		0x00 = X-Y; 0x10 = X; 0x20 = Y
	*/
	uint8_t tex_flag;
	/*
	Flag:
		0x00 = TEX
		0x80 = FIX
		0x01 = Rotation; Y Axix
		0x02 = Rotation; Z Axix
	*/
	float unk009;
	float position[2];
	float unk010[12];
	float unk011;
	float size[2];
	uint8_t colour1[4];
	uint8_t colour2[4];
	float rotation[3];
	uint8_t trans_type;
	/*
	Transparency Type
		0=Blend
		1=Additive
		2=Additive2
		3=Additive3
		4=Multiply
	*/
	uint8_t trans;
	/*
	Transparency Tans:
		0=Normal
		1=NEGA
		2=R-Normal
		3=R-Offset
	*/
	uint8_t mask_tex_id;
	uint8_t mask_flag;
	/*
	MaskFlag
		0x01 = SW On
	*/
	uint8_t trans_power;
	uint8_t unk001;
	uint8_t unk002;
	uint8_t unk003;
	uint32_t addr1; // fmtUWF_Block1
	uint32_t addr2; // fmtUWF_Block1
	uint32_t addr3; // fmtUWF_Anim
	uint32_t addr4; // fmtUWF_Anim
	uint32_t addr5; // fmtUWF_Anim
	uint32_t addr6; // null
	fmtUWF_Layer ();
	void read (bytestream &f);
	void write (bytestream &s);
	};

struct fmtUWF {
	uint8_t type[4]; // "2.00"
	uint16_t num_layers;
	uint8_t unk000;
	std::vector<fmtUWF_Layer> layers;
	fmtUWF ();
	bool validate (bytestream &f, size_t fsize = 0, bool verbose = true);
	void read_uwf (bytestream &f);
	};


#endif // FMTUWF_H
