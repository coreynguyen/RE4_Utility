/*	======================================================================

	Title:		String Helper Library
	Author:		mariokart64n
	Version:	0.1
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		General string helper class

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2019-01-28]
		wrote it!

	======================================================================	*/

#ifndef STRINGEXT_H
#define STRINGEXT_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <cctype>		// needed for std::iswspace()
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>	// for find_if
#include <vector>
#include <windows.h>
#include <time.h>
#include <shlwapi.h>	// needed for PathIsDirectoryW() add linker flags -lshlwapi -lwinmm
#include <Shlobj.h>


template <typename T> std::string to_string ( T Number ) {
		std::ostringstream ss; ss << Number; return ss.str();
		}

template <typename T> std::string floatToString ( T Number ) {std::ostringstream ss; ss << std::fixed << std::setprecision(3) << Number; return ss.str();}
//template <typename T> std::string to_integer ( T String ) {std::ostringstream ss; ss << Number; return ss.str();}
template <typename T> T convert_to (const std::string str) {	// double D = convert_to <double>("13.37");
    std::istringstream ss(str);
    T num;
    ss >> num;
    return num;
	}
template <typename I> std::string n2hexstr(I w, size_t hex_len = sizeof(I)<<1) {
    static const char* digits = "0123456789ABCDEF";
    std::string rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
	}
template<typename T, typename baseT=uint32_t> struct tohex_t {
	// https://stackoverflow.com/a/48897563
	// TO_HEX(1, true, 4) = 0x0001
    T num_;
    uint32_t width_;
    bool showbase_;
    tohex_t(T num, bool showbase = false, uint32_t width = 0) { num_ = num; showbase_ = showbase; width_ = width; }
    friend std::ostream& operator<< (std::ostream& stream, const tohex_t& num) {
        uint32_t w; baseT val;
        if (num.showbase_) { stream << "0x";}
        if (num.width_ == 0) {
            w = 0;
            val = static_cast<baseT>(num.num_);
            do { w += 2; val = val >> 8; } while (val > 0);
			} else {w = num.width_;}
        stream << std::hex << std::setfill('0') << std::setw(w) << static_cast<baseT>(num.num_);
        return stream;
		}
	};
template<typename T> tohex_t<T> TO_HEX(T const &num, bool showbase = false, uint32_t width = 0) { return tohex_t<T>(num, showbase, width); }

std::string rtrim(std::string str);
std::string ltrim(std::string str);
std::string padString (std::string str, unsigned int len, std::string pad = "0", bool addToLeft = true);
std::string toupper(const std::string & s);
std::string tolower(const std::string &s);
std::string openfilename(const char* filter = "All Files (*.*)\0*.*\0", HWND owner = NULL);
std::string savefilename(const char* filter = "All Files (*.*)\0*.*\0", HWND owner = NULL);
std::string getSavePath(std::string defaultPath = "", const char* szCaption = "Browse for folder...", unsigned int flags = BIF_USENEWUI, HWND hOwner = NULL);
std::string getexepath();
std::string getFilenameType(std::string const & path );
std::string getFilenamePathRoot(const std::string &str);
std::string getFilenamePath (const std::string &str);
std::string filenameFromPath(const std::string &str);
std::string getFilenameFile(const std::string &str);
std::vector <std::string> split(std::string str, std::string token);
std::string trim(const std::string& str, const std::string& whitespace = " \t");
std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
std::string get_part_date(const std::string &datepart, time_t now = time(0));
std::string IntToHexString(int number, int length);
std::string wstring_to_string (std::wstring ws);
void getFiles (std::string pattern, std::vector<std::string> &v);
void pause (bool useSystem = false);

#endif // STRINGEXT_H
