#include "scriptini.h"

scriptini* ini;

scriptini::scriptini() {
	//ctor
	txt = "";
	cchar = "; ";
	padlen = 65;
	varlen = 21;
	idxlen = 6;
	dc_len = 6;
	}

scriptini::~scriptini()
{
	//dtor
}


void scriptini::clear () {
	txt = "";
	}

void scriptini::log (std::wstring outfile) {
	if (outfile == L"") {
		std::cout << txt << std::endl;
		}
	else {
		bytestream s;
		s.writeFileW(outfile, 0, txt.size(), (char*)txt.c_str());
		}
	clear();
	}

void scriptini::separator (std::string label) {
	txt += "\n; " + padString("", padlen - 4, "_", false) + "\n; ";
	txt += padString("", padlen - 4 - label.size(), " ", false) + label + "\n";
	}

void scriptini::newline () {
	txt += "\n";
	}

void scriptini::section (std::string section_name) {
	if (section_name.length() > 64) {
		section_name = section_name.substr(0, 64);
		}
	if (section_name.length() == 0) {
		section_name = "NOTSET";
		}
	unsigned int horz_marg = (64 - section_name.length()) / 2;
	txt += padString("", horz_marg, " ") + "[" + section_name + "]\n";
	}

void scriptini::header (std::string title, std::string section_name, std::string notes) {

	if (title.length() > 22) {
		title = title.substr(0, 22);
		}

	unsigned int horz_marg = (22 - title.length()) / 2;
	std::vector<std::string> ss;
	txt += cchar + "=============================================================\n";
	txt += cchar + padString("", horz_marg, " ") + "Resident Evil 4 Ultimate HD Edition - " + title + "\n";
	txt += cchar + "            Generated from RE4 Utility by mariokart64n\n";

	if (notes.length() > 0) {
		txt += "; -------------------------------------------------------------\n;\n";


		ss = split(notes, "\n");

		unsigned int line_w = 56;
		//float line_count_f;
		unsigned int line_count;
		std::string tmp_line;
		std::string tmp_line2;
		unsigned int c_index;

		// number of comments
		for (unsigned int c = 0; c < ss.size(); c++) {




			//line_count_f = (float)ss.at(c).length() / (float)line_w;
			line_count = ss.at(c).length() / line_w;


			if ((line_count * line_w) < ss.at(c).length()) {
				line_count += 1;
				}


			for (unsigned int i = 0; i < line_count; i++) {


				if (ss.at(c).length() > line_w) {




					tmp_line = ss.at(c).substr(0, line_w);
					c_index = tmp_line.find_last_of(" ");
					if (c_index != std::string::npos) {
						tmp_line = ss.at(c).substr(0, c_index);
						}

					ss.at(c) = ss.at(c).substr(c_index + 1);
					}
				else {
					tmp_line = ss.at(c).substr(0);
					ss.at(c) = "";

					}


				if (i == 0) {

					txt += cchar + "* " + tmp_line + "\n";
					}
				else {

					txt += cchar + "  " + tmp_line + "\n";
					}
				}

			txt += cchar + "\n";
			}


		txt += cchar.substr(0) + "=============================================================\n\n";
		}
	else {
		txt += cchar + "=============================================================\n\n";
		}
	if (section_name.length() > 0) {
		section(section_name);
		}

	}

void scriptini::integer (std::string var_name, long signed int var_value, std::string notes) {
	std::string lne = padString("  " + var_name, varlen, " ", false) + " = " + to_string(var_value);
	if (notes.length() > 0) {
		txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
		}
	else {
		txt += lne + "\n";
		}
	}

void scriptini::boolean (std::string var_name, bool var_value, std::string notes) {
	std::string lne = padString("  " + var_name, varlen, " ", false) + " = ";
	if (var_value) {lne += "true";} else {lne += "false";}
	if (notes.length() > 0) {
		txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
		}
	else {
		txt += lne + "\n";
		}
	}

void scriptini::string (std::string var_name, std::string var_value, std::string notes, signed int index) {
	std::string lne = "";
	if (index > -1) {
		lne = padString("  " + var_name, varlen - idxlen, " ", false);
		lne += padString(to_string(index), idxlen, " ", true) + " = " + var_value;
		}
	else {
		lne = padString("  " + var_name, varlen, " ", false) + " = " + var_value;
		}
	if (notes.length() > 0) {
		txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
		}
	else {
		txt += lne + "\n";
		}
	}

void scriptini::wstring (std::string var_name, std::wstring var_value, std::string notes, signed int index) {
	if (var_value.length() > 0) {
		std::string utf8str = "";
		utf8str.reserve(var_value.length() * 3);
		for (unsigned int i = 0; i < var_value.length(); i++) {
			utf8str += unicode_2_utf8(var_value[i]);
			}
		std::string lne = "";
		if (index > -1) {
			lne = padString("  " + var_name, varlen - idxlen, " ", false);
			lne += padString(to_string(index), idxlen, " ", true) + " = " + utf8str;
			}
		else {
			lne = padString("  " + var_name, varlen, " ", false) + " = " + utf8str;
			}
		if (notes.length() > 0) {
			txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
			}
		else {
			txt += lne + "\n";
			}
		}
	}

void scriptini::fraction (std::string var_name, float var_value, std::string notes) {
	std::stringstream ss;
	ss.str(std::string());
	ss << std::fixed << std::setprecision(dc_len) << var_value;
	std::string lne = padString("  " + var_name, varlen, " ", false) + " = " + ss.str();
	if (notes.length() > 0) {
		txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
		}
	else {
		txt += lne + "\n";
		}
	}

void scriptini::hexnumber (std::string var_name, long unsigned int var_value, unsigned int bytelen, std::string notes) {
	std::stringstream ss;
	ss.str(std::string());
	ss << std::uppercase << TO_HEX(var_value, false, bytelen);
	std::string lne = padString("  " + var_name, varlen, " ", false) + " = 0x" + ss.str();
	if (notes.length() > 0) {
		txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
		}
	else {
		txt += lne + "\n";
		}
	}

void scriptini::vector2 (std::string var_name, float var_value_x, float var_value_y, bool sep_lines, std::string notes) {
	std::stringstream ss;
	std::string lne = "";

	if (sep_lines) {
		ss.str(std::string());


		ss << std::fixed << std::setprecision(dc_len) << var_value_x;
		lne = padString("  " + var_name + "_x", varlen, " ", false) + " = " + ss.str();


		if (notes.length() > 0) {
			txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
			}
		else {
			txt += lne + "\n";
			}

		ss.str(std::string());
		ss << std::fixed << std::setprecision(dc_len) << var_value_y;
		txt += padString("  " + var_name + "_y", varlen, " ", false) + " = " + ss.str() + "\n";


		}
	else {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << var_value_x;
		lne += padString("  " + var_name, varlen, " ", false) + " = (";
		lne += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << var_value_y;
		lne += ss.str() + ")";
		if (notes.length() > 0) {
			txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
			}
		else {
			txt += lne + "\n";
			}

		}

	}

void scriptini::vector3 (std::string var_name, float var_value_x, float var_value_y, float var_value_z, bool sep_lines, std::string notes) {
	std::stringstream ss;
	std::string lne = "";

	if (sep_lines) {
		ss.str(std::string());


		ss << std::fixed << std::setprecision(dc_len) << var_value_x;
		lne = padString("  " + var_name + "_x", varlen, " ", false) + " = " + ss.str();


		if (notes.length() > 0) {
			txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
			}
		else {
			txt += lne + "\n";
			}

		ss.str(std::string());
		ss << std::fixed << std::setprecision(dc_len) << var_value_y;
		txt += padString("  " + var_name + "_y", varlen, " ", false) + " = " + ss.str() + "\n";

		ss.str(std::string());
		ss << std::fixed << std::setprecision(dc_len) << var_value_z;
		txt += padString("  " + var_name + "_z", varlen, " ", false) + " = " + ss.str() + "\n";


		}
	else {
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << var_value_x;
		lne += padString("  " + var_name, varlen, " ", false) + " = (";
		lne += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << var_value_y;
		lne += ss.str() + ", ";
		ss.str(std::string());
		ss  << std::fixed << std::setprecision(dc_len) << var_value_z;
		lne += ss.str() + ")";
		if (notes.length() > 0) {
			txt += padString(lne, padlen, " ", false) + cchar + notes + "\n";
			}
		else {
			txt += lne + "\n";
			}

		}

	}

void scriptini::open (std::wstring file) {

	// open file
	bytestream f;
	if (f.openFileW(file) && f.size > 3) {

		// clear previous text
		txt = "";

		// check for byte order mark
		unsigned int bom = f.readUshort();
		switch (bom) {
			case 0xFEFF: { // 16bit LE
				unsigned int read_len = (f.size - 2) / 2;
				if (read_len > 0) {
					f.setLittleEndian();
					txt.reserve(read_len);
					for (unsigned int i = 0; i < read_len; i++) {
						txt+= unicode_2_utf8(f.readUshort());
						}
					}
				break;
				}
			case 0xFFFE: { // 16bit BE
				unsigned int read_len = (f.size - 2) / 2;
				if (read_len > 0) {
					f.setBigEndian();
					txt.reserve(read_len);
					for (unsigned int i = 0; i < read_len; i++) {
						txt+= unicode_2_utf8(f.readUshort());
						}
					}
				break;
				}
			default: {	// UTF-8
				if (f.size > 2) {
					txt.reserve(f.size);
					for (unsigned int i = 0; i < f.size; i++) {
						txt += f.readUbyte();
						}
					}
				}
			}
		}
	}

std::string scriptini::get_string (std::string secname, std::string varname) {
	std::string v;
	std::istringstream iss(txt);
	unsigned int c;
	unsigned int b;
	unsigned int bb;
	bool chk = false;

	secname = tolower(secname);
	varname = tolower(varname);


	for (std::string line; std::getline(iss, line); ) {

		if (line.length() == 0) {continue;}

		// check for comment
		c = line.find(";");
		if (c != std::string::npos) {
			if (c == 0) {
				// skip
				continue;
				}
			else {
				// remove comment
				line = line.substr(0, c);
				}
			}



		if (chk) {

			// Check for variable
			b = line.find("=");
			if (b != std::string::npos && b > 0) {


				// extract variable name
				v = tolower(trim(line.substr(0, b)));

				// check variable
				if (varname == v) {
					if (line.length() > 0 && b + 1 < line.length()) {
						return trim(line.substr(b + 1));
						}

					}
				}
			}
		else {


			if ((b = line.find("[")) != std::string::npos && (bb = line.find("]")) != std::string::npos) {

				if (b + 1 < line.length() && bb > b) {
					v = tolower(trim(line.substr(b + 1, bb - b - 1)));

					if (v == secname) {
						chk = true;
						}

					}
				}
			}
		}
	return "";
	}

std::wstring scriptini::get_wstring (std::string secname, std::string varname) {
	std::string val = get_string(secname, varname);
	if (val.length() > 0) {return utf8_2_unicode(val);}
	return L"";
	}

signed long long scriptini::get_integer (std::string secname, std::string varname) {
	std::string val = get_string(secname, varname);
	if (val.length() > 0) {
		std::stringstream ss;
		signed long long v = 0;
		unsigned int x = 0;
		x = val.find("x");
		if (x != std::string::npos && x > 0) {
 			ss << std::hex << val.substr(x + 1);
			}
		else {
			ss << val;
			}
		ss >> v;
		return v;
		}
	return 0;
	}

bool scriptini::get_boolean (std::string secname, std::string varname) {
	std::string val = get_string(secname, varname);
	if (val.length() > 0) {return convert_to<bool>(val);}
	return false;
	}

float scriptini::get_fraction (std::string secname, std::string varname) {
	std::string val = get_string(secname, varname);
	if (val.length() > 0) {return convert_to<float>(val);}
	return 0.0f;
	}

void scriptini::get_vector2 (std::string secname, std::string varname, float &vec1, float &vec2) {
	std::string val = get_string(secname, varname);

	if (val.length() > 0) {
		std::vector<std::string> ss = split(val, " ,[{()}]");
		if (ss.size() >= 2) {
			vec1 = convert_to<float>(ss.at(0));
			vec2 = convert_to<float>(ss.at(1));
			}
		}
	}

void scriptini::get_vector3 (std::string secname, std::string varname, float &vec1, float &vec2, float &vec3) {
	std::string val = get_string(secname, varname);
	if (val.length() > 0) {
		std::vector<std::string> ss = split(val, " ,[{()}]");
//		std::cout << "ss: " << ss.size() << std::endl;
//		std::cout << "val: " << val << std::endl;
//		std::cout << "val0: " << ss.at(0) << std::endl;
//		std::cout << "val1: " << ss.at(1) << std::endl;
//		std::cout << "val2: " << ss.at(2) << std::endl;

		if (ss.size() >= 3) {
			vec1 = convert_to<float>(ss.at(0));
			vec2 = convert_to<float>(ss.at(1));
			vec3 = convert_to<float>(ss.at(2));
			}
		}
	}

bool scriptini::find_section (std::string secname) {

	std::istringstream iss(txt);
	unsigned int c;
	unsigned int b;
	unsigned int bb;

	secname = tolower(secname);
	for (std::string line; std::getline(iss, line); ) {

		b = line.find("[");
		if (b != std::string::npos && (bb = line.find("]")) != std::string::npos) {

			c = line.find(";");
			if (c != std::string::npos) {
				if ( c < b) {
					// skip
					continue;
					}
				else {
					// remove comment
					line = line.substr(0, c);
					std::cout << "line: \t" << line << std::endl;
					}
				}

			if (tolower(trim(line.substr(b + 1, bb - b - 1))) == secname) {
				return true;
				}
			}

		}
	return false;
	}
