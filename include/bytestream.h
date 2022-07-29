/*	======================================================================

	Title:		I/O Helper Library
	Author:		mariokart64n
	Version:	0.1
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		General Binary i/o helper class

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:
	[2022-07-13]
		> added fcs16

	[2022-04-02]
		> kept more information about the filename and path
		> added read size on open
		> added CRC32 checksum

	[2019-01-28]
		wrote it!


	======================================================================	*/

#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#include <iostream>
#include <string>
#include <cmath>		// needed for pow()
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <windows.h>
#include <type_traits>

extern uint16_t fcs16_lut[256];



// For floating point types
/*
template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* p = nullptr>
constexpr T modulo(const T x, const T y) {return (x < T() ? T(-1) : T(1)) * ((x < T() ? -x : x) - static_cast<long long int>((x/y < T() ? -x/y : x/y)) * (y < T() ? -y : y));}
// For non-floating point types
template<typename T>
using TypeToCast = typename std::conditional<std::is_floating_point<T>::value, int, T>::type;
template<typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type* p = nullptr>
constexpr T modulo(const T x, const T y) {return (static_cast<TypeToCast<T>>(x) % static_cast<TypeToCast<T>>(y));}
*/
enum seek {set, cur, end};


namespace bit { // bitwise function which mimic the maxscript api
	//unsigned int and (unsigned int a, unsigned int b);
	//unsigned int or (unsigned int a, unsigned int b);
	//unsigned int xor (unsigned int a, unsigned int b);
	//unsigned int not (unsigned int a);
	float IntAsFloat (unsigned long b);
	unsigned long FloatAsInt (float b);
	unsigned int shift (unsigned int number, int offset);
	bool get (int number, int position);
	unsigned int flip (unsigned int number, unsigned int position);
	unsigned int set (unsigned int n, unsigned int p, bool b);
	unsigned long swapBytes (unsigned long num, const unsigned int pos1, const unsigned int pos2);
	//std::string IntAsHex (unsigned long b);
	};

class bytestream {
  public:

	std::wstring fpathW;
	std::wstring fnameW;
	std::wstring fextW;
	std::wstring fileW;
	std::string fpath;
	std::string fname;
	std::string fext;
	std::string file;
	size_t pos;
	unsigned long size;
	char* stream;
	bool islilEndian;
	bytestream ();
	~bytestream ();
	size_t getFileSizeW(std::wstring fileName);
	bool doesFolderExistW (std::wstring dirName_in);
	bool doesFileExistW (std::wstring fileName);
	bool doesFileExist (std::string fileName);
	bool makeDirW(std::wstring wsPath);
	std::wstring getFilenamePathW (const std::wstring &str);
	std::wstring getFilenameFileW(const std::wstring &str);
	std::wstring getFilenameTypeW (std::wstring const &path );
	std::string getFilenamePath (const std::string &str);
	std::string getFilenameFile(const std::string &str);
	std::string getFilenameType (std::string const &path );
	void setBigEndian ();
	void setLittleEndian ();
	void close ();
	bool openFile (std::string filename, size_t file_size = 0);
	bool openFileW (std::wstring filename, size_t file_size = 0);
	bool openResource (int resource_id, const char* resource_class);
	bool amendFile (std::wstring filename, size_t &offset);
	bool writeFile (std::string filename, size_t offset = 0, size_t wsize = 0, char* data = NULL);
	bool writeFileW (std::wstring filename, size_t offset = 0, size_t wsize = 0, char* data = NULL);
	bool createFile (unsigned long bufferSize);
	//size_t size();
	bool eos (); // end of stream;
	void resize (size_t newsize, bool flush = false);
	void copy (char* src_buf, size_t src_len, size_t src_pos = 0, size_t tar_dest = 0);
	size_t tell ();
	void seek (unsigned long offset = 0, char dir = 0);
	signed long unsigned_to_signed(unsigned long n, char nbits);
	uint32_t crc32 (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t crc32b (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t adler32 (size_t crc_pos = 0, size_t crc_len = 0, uint32_t seed = 1);
	uint32_t fnv1_32 (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t fnv1a_32 (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t joaat32 (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t djb2_32 (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t djb2_32a (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t sdbm_32 (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t aod_32 (size_t crc_pos = 0, size_t crc_len = 0);
	uint32_t fcs16 (size_t crc_pos = 0, size_t crc_len = 0);
	std::string base64_encode (size_t crc_pos = 0, size_t crc_len = 0);
	void base64_decode (std::string &input, size_t tar_pos = 0);

	uint8_t readUbyte ();
	uint16_t readUshort ();
	uint32_t readUlong ();
	uint64_t readUlonglong ();
	int8_t readbyte ();
	int16_t readshort ();
	int32_t readlong ();
	int64_t readlonglong ();
	std::string readline ();
	std::wstring readlineW ();
	std::string readstring (int length = -1, unsigned char term = 0x00);
	std::wstring readstringW (int length = -1, wchar_t term = L'\0');
	float readfloat ();
	double readdouble ();
	void writebyte (unsigned char val);
	void writeshort (unsigned short val);
	void writelong (unsigned long val);
	void writeUbyte (unsigned char val);
	void writeUshort (unsigned short val);
	void writeUlong (unsigned long val);
	void writeUlonglong (unsigned long long val);
	void writefloat (float val);
	void writedouble (double val);
	void writestring (std::string str, signed long length = -1);
	};

#endif // BYTESTREAM_H
