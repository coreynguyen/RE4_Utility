#include "fmtXGS.h"


fmtXGS_Category::fmtXGS_Category () {
	max_instances = 0;
	fade_in = 0;
	fade_out = 0;
	flag = 0;
	unk003 = 0;
	unk004 = 0;
	volume_db = 0;
	unk005 = 0;
	name = "";
	unk006 = -1;
	}

void fmtXGS_Category::read_xgs_category (bytestream &f) {
	max_instances = f.readbyte();
	fade_in = f.readUshort();
	fade_out = f.readUshort();
	flag = f.readUbyte();
	unk003 = f.readbyte();
	unk004 = f.readbyte();
	volume_db = f.readbyte();
	unk005 = f.readbyte();
	}

void fmtXGS_Category::write_xgs_category (bytestream &s) {
	s.writebyte(max_instances);
	s.writeUshort(fade_in);
	s.writeUshort(fade_out);
	s.writeUbyte(flag);
	s.writebyte(unk003);
	s.writebyte(unk004);
	s.writebyte(volume_db);
	s.writebyte(unk005);
	}

fmtXGS_Varaible::fmtXGS_Varaible () {
	flag = 1;
	init_val = 343.50f;
	var_range_start = 0.0f;
	var_range_end = 1000000.0f;
	name = "";
	unk006 = -1;
	}

void fmtXGS_Varaible::read_xgs_variable (bytestream &f) {
	flag = f.readUbyte();
	init_val = f.readfloat();
	var_range_start = f.readfloat();
	var_range_end = f.readfloat();
	}

void fmtXGS_Varaible::write_xgs_variable (bytestream &s) {
	s.writeUbyte(flag);
	s.writefloat(init_val);
	s.writefloat(var_range_start);
	s.writefloat(var_range_end);
	}

fmtXGS_RPC_Curve::fmtXGS_RPC_Curve () {
	value = 0.0;
	parameter = 0.0;
	curvature = 0;
	}

void fmtXGS_RPC_Curve::read_rpc_curve (bytestream &f) {
	value = f.readfloat();
	parameter = f.readfloat();
	curvature = f.readUbyte();
	}

void fmtXGS_RPC_Curve::write_rpc_curve (bytestream &s) {
	s.writefloat(value);
	s.writefloat(parameter);
	s.writeUbyte(curvature);
	}

fmtXGS_RPC::fmtXGS_RPC () {
	varaible_type = 7;
	num_curve_points = 2;
	parameter_type = 0;
	points.clear();
	}

void fmtXGS_RPC::read_rpc (bytestream &f) {
	varaible_type = f.readUshort();
	num_curve_points = f.readUbyte();
	parameter_type = f.readUshort();
	points.clear();
	if (num_curve_points > 0) {
		points = std::vector<fmtXGS_RPC_Curve>(num_curve_points);
		for (unsigned int i = 0; i < num_curve_points; i++) {
			points[i].read_rpc_curve(f);
			}
		}
	}

void fmtXGS_RPC::write_rpc (bytestream &s) {
	s.writeUshort(varaible_type);
	s.writeUbyte(num_curve_points = points.size());
	s.writeUshort(parameter_type);
	for (unsigned int i = 0; i < num_curve_points; i++) {
		points[i].write_rpc_curve(s);
		}
	}


fmtXGS::fmtXGS () {
	filetype = 0x46534758;
	tool_version = 46;
	file_version = 43;
	crc = 0;
	lastModified = 0;
	platform = 1;
	categories_count = 0;
	variables_count = 0;
	unknown1_count = 0;
	unknown2_count = 0;
	param_ctrls_count = 0;
	dsp_presets_count = 0;
	dsp_params_count = 0;
	categories_addr = 0;
	variables_addr = 0;
	unknown1_addr = 0;
	category_name_addr = 0;
	unknown2_addr = 0;
	variable_name_addr = 0;
	category_names_addr = 0;
	variable_names_addr = 0;
	param_ctrls_addr = 0;
	dsp_presets_addr = 0;
	dsp_params_addr = 0;
	}

void fmtXGS::read_xgs (bytestream &f) {
	size_t pos = f.tell();

	f.setLittleEndian();

	filetype = f.readUlong();
	if (filetype == 0x58475346) { // Check if (file is in BIG Endian
		f.setBigEndian();
		f.seek(pos);
		filetype = f.readUlong();
		}

	if (filetype == 0x46534758) { // 'XGSF'
		tool_version = f.readUshort();
		file_version = f.readUshort();
		crc = f.readUshort();
		lastModified = f.readUlonglong();
		platform = f.readUbyte();
		categories_count = f.readUshort();
		variables_count = f.readUshort();
		unknown1_count = f.readUshort();
		unknown2_count = f.readUshort();
		param_ctrls_count = f.readUshort();
		dsp_presets_count = f.readUshort();
		dsp_params_count = f.readUshort();
		categories_addr = f.readlong();
		variables_addr = f.readlong();
		unknown1_addr = f.readlong();
		category_name_addr = f.readlong();
		unknown2_addr = f.readlong();
		variable_name_addr = f.readlong();
		category_names_addr = f.readlong();
		variable_names_addr = f.readlong();
		param_ctrls_addr = f.readlong();
		dsp_presets_addr = f.readlong();
		dsp_params_addr = f.readlong();

		categories.clear();
		if (categories_addr > 0 && categories_count > 0) {
			categories = std::vector<fmtXGS_Category>(categories_count);

			f.seek(pos + categories_addr);
			for (unsigned int i = 0; i < categories_count; i++) {
				categories[i].read_xgs_category(f);
				}

			if (category_name_addr > 0) {

				uint32_t cate_name_addr = 0;
				for (unsigned int i = 0; i < categories_count; i++) {
					f.seek(pos + category_name_addr + (i * 6));

					cate_name_addr = f.readUlong();
					categories[i].unk006 = f.readUshort();
					if (cate_name_addr > 0) {
						f.seek(pos + cate_name_addr);
						categories[i].name = f.readstring();
						}

					}


				}


			}

		variables.clear();
		if (variables_addr > 0 && variables_count > 0) {
			variables = std::vector<fmtXGS_Varaible>(variables_count);

			f.seek(pos + variables_addr);
			for (unsigned int i = 0; i < variables_count; i++) {

				variables[i].read_xgs_variable(f);

				}

			if (variable_name_addr > 0) {

				uint32_t var_name_addr = 0;
				for (unsigned int i = 0; i < variables_count; i++) {
					f.seek(pos + variable_name_addr + (i * 6));

					var_name_addr = f.readUlong();
					variables[i].unk006 = f.readUshort();
					if (var_name_addr > 0) {
						f.seek(pos + var_name_addr);
						variables[i].name = f.readstring();
						}

					}


				}


			}

		param_ctrls.clear();
		if (param_ctrls_addr > 0 && param_ctrls_count > 0) {

			param_ctrls = std::vector<fmtXGS_RPC>(param_ctrls_count);

			f.seek(pos + param_ctrls_addr);
			for (unsigned int i = 0; i < param_ctrls_count; i++) {

				param_ctrls[i].read_rpc(f);

				}

			}

		unknown1.clear();
		if (unknown1_addr > 0 && unknown1_count > 0) {

			unknown1 = std::vector<int16_t>(unknown1_count);

			f.seek(pos + unknown1_addr);
			for (unsigned int i = 0; i < unknown1_count; i++) {
				unknown1[i] = f.readshort();
				}
			}

		unknown2.clear();
		if (unknown2_addr > 0 && unknown2_count > 0) {

			unknown2 = std::vector<int16_t>(unknown2_count);

			f.seek(pos + unknown2_addr);
			for (unsigned int i = 0; i < unknown2_count; i++) {
				unknown2[i] = f.readshort();
				}
			}
		}
	}

void fmtXGS::write_xgs (bytestream &s) {

	size_t nsize = 77; // header size

	s.writeUlong(filetype = 0x46534758);
	s.writeUshort(tool_version);
	s.writeUshort(file_version);
	s.writeUshort(crc);
	s.writeUlonglong(lastModified);
	s.writeUbyte(platform);

	s.writeUshort(categories_count = categories.size());
	s.writeUshort(variables_count = variables.size());
	s.writeUshort(unknown1_count = unknown1.size());
	s.writeUshort(unknown2_count = unknown2.size());
	s.writeUshort(param_ctrls_count = param_ctrls.size());
	s.writeUshort(dsp_presets_count);
	s.writeUshort(dsp_params_count);

	// Null all the addresses
	categories_addr = -1;
	variables_addr = -1;
	param_ctrls_addr = -1;
	dsp_presets_addr = -1;
	dsp_params_addr = -1;
	unknown1_addr = -1;
	category_name_addr = -1;
	unknown2_addr = -1;
	variable_name_addr = -1;
	category_names_addr = -1;
	variable_names_addr = -1;

	// Recalc the addresses
	if (categories_count > 0) {
		categories_addr = nsize;
		nsize += categories_count * 10;
		}
	if (variables_count > 0) {
		variables_addr = nsize;
		nsize += variables_count * 13;
		}
	if (param_ctrls_count > 0) {
		param_ctrls_addr = nsize;
		for (unsigned int i = 0; i < param_ctrls_count; i++) {
			nsize += 5 + (param_ctrls[i].points.size() * 9);
			}
		}

	//dsp_presets_addr
	//dsp_params_addr

	if (unknown1_count > 0) {
		unknown1_addr = nsize;
		nsize += unknown1_count * 2;
		}

	std::vector<uint32_t> category_name_addrs;
	if (categories_count > 0) {
		category_name_addrs = std::vector<uint32_t>(categories_count);
		category_name_addr = nsize;
		nsize += categories_count * 6;

		category_names_addr = nsize;
		for (unsigned int i = 0; i < categories_count; i++) {
			category_name_addrs[i] = nsize;
			nsize += categories[i].name.size() + 1;
			}
		}

	if (unknown2_count > 0) {
		unknown2_addr = nsize;
		nsize += unknown2_count * 2;
		}

	std::vector<uint32_t> variable_name_addrs;
	if (variables_count > 0) {
		variable_name_addrs = std::vector<uint32_t>(variables_count);
		variable_name_addr = nsize;
		nsize += variables_count * 6;

		variable_names_addr = nsize;
		for (unsigned int i = 0; i < variables_count; i++) {
			variable_name_addrs[i] = nsize;
			nsize += variables[i].name.size() + 1;
			}
		}

	// Write Addresses
	s.writelong(categories_addr);
	s.writelong(variables_addr);
	s.writelong(unknown1_addr);
	s.writelong(category_name_addr);
	s.writelong(unknown2_addr);
	s.writelong(variable_name_addr);
	s.writelong(category_names_addr);
	s.writelong(variable_names_addr);
	s.writelong(param_ctrls_addr);
	s.writelong(dsp_presets_addr);
	s.writelong(dsp_params_addr);

	for (unsigned int i = 0; i < categories_count; i++) {
		categories[i].write_xgs_category(s);
		}
	for (unsigned int i = 0; i < variables_count; i++) {
		variables[i].write_xgs_variable(s);
		}
	for (unsigned int i = 0; i < param_ctrls_count; i++) {
		param_ctrls[i].write_rpc(s);
		}
	for (unsigned int i = 0; i < unknown1_count; i++) {
		s.writeshort(unknown1[i]);
		}
	for (unsigned int i = 0; i < categories_count; i++) {
		s.writelong(category_name_addrs[i]); // string addr
		s.writeshort(categories[i].unk006);
		}
	for (unsigned int i = 0; i < categories_count; i++) {
		s.writestring(categories[i].name);
		}
	for (unsigned int i = 0; i < unknown2_count; i++) {
		s.writeshort(unknown2[i]);
		}
	for (unsigned int i = 0; i < variables_count; i++) {
		s.writelong(variable_name_addrs[i]); // string addr
		s.writeshort(variables[i].unk006);
		}
	for (unsigned int i = 0; i < variables_count; i++) {
		s.writestring(variables[i].name);
		}
	std::cout << "NewSize: \t" << nsize << std::endl;
	}

