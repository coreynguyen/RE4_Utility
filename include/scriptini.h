#ifndef SCRIPTINI_H
#define SCRIPTINI_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "bytestream.h"
#include "wregistry.h"
#include "stringext.h"
#include "stringenc.h"



class scriptini {
public:
	std::string txt; // string buffer for writing ini
	std::string cchar;
	int padlen;
	int varlen;
	int idxlen;
	int dc_len;
	scriptini();
	virtual ~scriptini();
	void clear ();
	void log (std::wstring outfile = L"");
	void separator (std::string label);
	void newline ();
	void section (std::string section_name);
	void header (std::string title, std::string section_name = "", std::string notes = "");
	void integer (std::string var_name, long signed int var_value, std::string notes = "");
	void boolean (std::string var_name, bool var_value, std::string notes = "");
	void string (std::string var_name, std::string var_value, std::string notes = "", signed int index = -1);
	void wstring (std::string var_name, std::wstring var_value, std::string notes = "", signed int index = -1);
	void fraction (std::string var_name, float var_value, std::string notes = "");
	void hexnumber (std::string var_name, long unsigned int var_value, unsigned int bytelen = 8, std::string notes = "");
	void vector2 (std::string var_name, float var_value_x, float var_value_y, bool sep_lines = false, std::string notes = "");
	void vector3 (std::string var_name, float var_value_x, float var_value_y, float var_value_z, bool sep_lines = false, std::string notes = "");
	void open (std::wstring file);
	std::string get_string (std::string secname, std::string varname);
	std::wstring get_wstring (std::string secname, std::string varname);
	signed long long get_integer (std::string secname, std::string varname);
	bool get_boolean (std::string secname, std::string varname);
	float get_fraction (std::string secname, std::string varname);
	void get_vector2 (std::string secname, std::string varname, float &vec1, float &vec2);
	void get_vector3 (std::string secname, std::string varname, float &vec1, float &vec2, float &vec3);
	bool find_section (std::string secname);

protected:

private:
	};

extern scriptini* ini;

#endif // SCRIPTINI_H
