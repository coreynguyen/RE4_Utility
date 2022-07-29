#include "fmtUWF.h"

fmtUWF_S_Curve::fmtUWF_S_Curve () {
	position[0] = 0.0f;
	position[1] = 0.0f;
	vector_right = 0.0;
	vector_left = 0.0;
	}

void fmtUWF_S_Curve::read (bytestream &f) {
	position[0] = f.readfloat();
	position[1] = f.readfloat();
	vector_right = f.readfloat();
	vector_left = f.readfloat();
	}

void fmtUWF_S_Curve::write (bytestream &s) {
	s.writefloat(position[0]);
	s.writefloat(position[1]);
	s.writefloat(vector_right);
	s.writefloat(vector_left);
	}

fmtUWF_Anim::fmtUWF_Anim () {
	num_curves = 0;
	curves.clear();
	}

void fmtUWF_Anim::read (bytestream &f) {
	num_curves = f.readUlong();
	if (num_curves > 0) {
		curves = std::vector<fmtUWF_S_Curve>(num_curves);
		for (unsigned int i = 0; i < num_curves; i++) {
			curves[i].read(f);
			}
		}
	}

void fmtUWF_Anim::write (bytestream &s) {
	s.writeUlong(num_curves = curves.size());
	for (unsigned int i = 0; i < num_curves; i++) {
		curves[i].write(s);
		}
	}

fmtUWF_Block1::fmtUWF_Block1 () {
	unk041 = 1;
	unk042 = 0;
	unk043 = 0;
	unk044 = 0;
	count = 0;
	data.clear();
	}

void fmtUWF_Block1::read (bytestream &f) {
	unk041 = f.readUbyte();
	unk042 = f.readUbyte();
	unk043 = f.readUbyte();
	unk044 = f.readUbyte();
	count = f.readUlong();
	data.clear();
	if (count > 0) {
		data = std::vector<float>(count * 3);
		unsigned int c = 0;
		for (unsigned int i = 0; i < count; i++) {
			data[c] = f.readfloat();
			data[c + 1] = f.readfloat();
			data[c + 2] = f.readfloat();
			c+=3;
			}
		}
	}

void fmtUWF_Block1::write (bytestream &s) {
	s.writeUbyte(unk041);
	s.writeUbyte(unk042);
	s.writeUbyte(unk043);
	s.writeUbyte(unk044);
	s.writeUlong(count = (unsigned int)(data.size() / 3.0f));
	unsigned int c = 0;
	for (unsigned int i = 0; i < count; i++) {
		s.writefloat(data[c]);
		s.writefloat(data[c + 1]);
		s.writefloat(data[c + 2]);
		c += 3;
		}
	}

fmtUWF_Layer::fmtUWF_Layer () {
	enable_flag = 0;
	mark_id = 0;
	unk004 = 0;
	unk005 = 0;
	unk006 = 0;
	unk007 = 0;
	isGroup = 0;
	unk008 = 0;
	tex_id = 0;
	layout_flag = 0;
	loop_flag = 0;
	axis_flag = 0;
	tex_flag = 0;
	unk009 = 0.0;
	position[0] = 0.0f;
	position[1] = 0.0f;
	unk010[0] = 0.0f;
	unk010[1] = 0.0f;
	unk010[2] = 0.0f;
	unk010[3] = 0.0f;
	unk010[4] = 0.0f;
	unk010[5] = 0.0f;
	unk010[6] = 0.0f;
	unk010[7] = 0.0f;
	unk010[8] = 0.0f;
	unk010[9] = 0.0f;
	unk010[10] = 0.0f;
	unk010[11] = 0.0f;
	unk011 = 0.0;
	size[0] = 0.0f;
	size[1] = 0.0f;
	colour1[0] = 0;
	colour1[1] = 0;
	colour1[2] = 0;
	colour1[3] = 255;
	colour2[0] = 0;
	colour2[1] = 0;
	colour2[2] = 0;
	colour2[3] = 255;
	rotation[0] = 0.0f;
	rotation[1] = 0.0f;
	rotation[2] = 0.0f;
	trans_type = 0;
	trans  = 0;
	mask_tex_id = 0;
	mask_flag = 0;
	trans_power  = 0;
	unk001 = 0;
	unk002 = 0;
	unk003 = 0;
	addr1 = 0;
	addr2 = 0;
	addr3 = 0;
	addr4 = 0;
	addr5 = 0;
	addr6 = 0;
	}

void fmtUWF_Layer::read (bytestream &f) {
	enable_flag = f.readUlong();
	mark_id = f.readUbyte();
	unk004 = f.readUbyte();
	unk005 = f.readUbyte();
	unk006 = f.readUbyte();
	unk007 = f.readUbyte();
	isGroup = f.readUbyte();
	unk008 = f.readUbyte();
	tex_id = f.readUbyte();
	layout_flag = f.readUbyte();
	loop_flag = f.readUbyte();
	axis_flag = f.readUbyte();
	tex_flag = f.readUbyte();
	unk009 = f.readfloat();
	position[0] = f.readfloat();
	position[1] = f.readfloat();
	unk010[0] = f.readfloat();
	unk010[1] = f.readfloat();
	unk010[2] = f.readfloat();
	unk010[3] = f.readfloat();
	unk010[4] = f.readfloat();
	unk010[5] = f.readfloat();
	unk010[6] = f.readfloat();
	unk010[7] = f.readfloat();
	unk010[8] = f.readfloat();
	unk010[9] = f.readfloat();
	unk010[10] = f.readfloat();
	unk010[11] = f.readfloat();
	unk011 = f.readfloat();
	size[0] = f.readfloat();
	size[1] = f.readfloat();
	colour1[0] = f.readUbyte();
	colour1[1] = f.readUbyte();
	colour1[2] = f.readUbyte();
	colour1[3] = f.readUbyte();
	colour2[0] = f.readUbyte();
	colour2[1] = f.readUbyte();
	colour2[2] = f.readUbyte();
	colour2[3] = f.readUbyte();
	rotation[0] = f.readfloat();
	rotation[1] = f.readfloat();
	rotation[2] = f.readfloat();
	trans_type = f.readUbyte();
	trans  = f.readUbyte();
	mask_tex_id = f.readUbyte();
	mask_flag = f.readUbyte();
	trans_power  = f.readUbyte();
	unk001 = f.readUbyte();
	unk002 = f.readUbyte();
	unk003 = f.readUbyte();
	addr1 = f.readUlong();
	addr2 = f.readUlong();
	addr3 = f.readUlong();
	addr4 = f.readUlong();
	addr5 = f.readUlong();
	addr6 = f.readUlong();
	}

void fmtUWF_Layer::write (bytestream &s) {
	s.writeUlong(enable_flag);
	s.writeUbyte(mark_id);
	s.writeUbyte(unk004);
	s.writeUbyte(unk005);
	s.writeUbyte(unk006);
	s.writeUbyte(unk007);
	s.writeUbyte(isGroup);
	s.writeUbyte(unk008);
	s.writeUbyte(tex_id);
	s.writeUbyte(layout_flag);
	s.writeUbyte(loop_flag);
	s.writeUbyte(axis_flag);
	s.writeUbyte(tex_flag);
	s.writefloat(unk009);
	s.writefloat(position[0]);
	s.writefloat(position[1]);
	s.writefloat(unk010[0]);
	s.writefloat(unk010[1]);
	s.writefloat(unk010[2]);
	s.writefloat(unk010[3]);
	s.writefloat(unk010[4]);
	s.writefloat(unk010[5]);
	s.writefloat(unk010[6]);
	s.writefloat(unk010[7]);
	s.writefloat(unk010[8]);
	s.writefloat(unk010[9]);
	s.writefloat(unk010[10]);
	s.writefloat(unk010[11]);
	s.writefloat(unk011);
	s.writefloat(size[0]);
	s.writefloat(size[1]);
	s.writeUbyte(colour1[0]);
	s.writeUbyte(colour1[1]);
	s.writeUbyte(colour1[2]);
	s.writeUbyte(colour1[3]);
	s.writeUbyte(colour2[0]);
	s.writeUbyte(colour2[1]);
	s.writeUbyte(colour2[2]);
	s.writeUbyte(colour2[3]);
	s.writefloat(rotation[0]);
	s.writefloat(rotation[1]);
	s.writefloat(rotation[2]);
	s.writeUbyte(trans_type);
	s.writeUbyte(trans);
	s.writeUbyte(mask_tex_id);
	s.writeUbyte(mask_flag);
	s.writeUbyte(trans_power);
	s.writeUbyte(unk001);
	s.writeUbyte(unk002);
	s.writeUbyte(unk003);
	s.writeUlong(addr1);
	s.writeUlong(addr2);
	s.writeUlong(addr3);
	s.writeUlong(addr4);
	s.writeUlong(addr5);
	s.writeUlong(addr6);
	}

fmtUWF::fmtUWF () {
	type[0] = 0x32;
	type[1] = 0x2E;
	type[2] = 0x30;
	type[3] = 0x30;
	unk000 = 0;
	num_layers = 0;
	layers.clear();
	}

bool fmtUWF::validate (bytestream &f, size_t fsize, bool verbose) {
	auto isGood = false;
	auto pos = f.tell();
	if (fsize == 0) {fsize = f.size;}

	if (pos + 8 <= fsize) {

		auto chk1 = f.readUbyte();
		auto chk2 = f.readUbyte();
		auto chk3 = f.readUbyte();
		auto chk4 = f.readUbyte();

		if (chk1 == 0x32 && chk2 == 0x2E && chk3 == 0x30 && chk4 == 0x30) {

			auto chk5 = f.readUbyte();

			if (chk5 == 0) {

				auto chk6 = f.readUbyte();

				if (pos + 8 + (chk6 * 140) <= fsize) {





					} else {if (verbose) {std::cout << "invalid table1 size\n";}}


				} else {if (verbose) {std::cout << "unexpected header value\n";}}


			} else {if (verbose) {std::cout << "invalid file type\n";}}


		} else {if (verbose) {std::cout << "invalid file size\n";}}

	f.seek(pos);
	return isGood;
	}

void fmtUWF::read_uwf (bytestream &f) {
	// this is ALWAYS little endian
	type[0] = f.readUbyte();
	type[1] = f.readUbyte();
	type[2] = f.readUbyte();
	type[3] = f.readUbyte();

	// Convert the four character code into a string
	std::string type_s = "";
	for (unsigned int i = 0; i < num_layers; i++) {
		type_s += (type[i] & (0xFF << (i * 8))) >> (i * 8);
		}

	if (type_s == "2.00") {
		if ((num_layers = f.readUshort()) > 0) {
			unk000 = f.readUbyte();
			layers = std::vector<fmtUWF_Layer>(num_layers);
			for (unsigned int i = 0; i < num_layers; i++) {
				layers[i].read(f);
				}
			}
		} else {std::cout << "invalid file type\n";}
	}

