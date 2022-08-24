//#include <iostream>
//#include <string>
#include <cstring>
//#include <cstddef>
//#include <windows.h>
//#include <shlwapi.h>
//#include <cmath>
//#include <tchar.h>
//#include <vector>
//#include <iomanip> // needed for setprecision
//#include <sstream>
//#include <fstream>
//#include <time.h>	// needed for get_part_date

#include <windows.h>
#include <math.h>       /* pow */
#include "bytestream.h"


//unsigned int bit::and (unsigned int a, unsigned int b) {
//	return (a & b);
//	}

//unsigned int bit::or (unsigned int a, unsigned int b) {
//	return (a | b);
//	}

//unsigned int bit::xor (unsigned int a, unsigned int b) {
//	return (a ^ b);
//	}

//unsigned int bit::not (unsigned int a) {
//	return ~a;
//	}
uint16_t fcs16_lut[256] = {
	0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF,
	0x8C48, 0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7,
	0x1081, 0x0108, 0x3393, 0x221A, 0x56A5, 0x472C, 0x75B7, 0x643E,
	0x9CC9, 0x8D40, 0xBFDB, 0xAE52, 0xDAED, 0xCB64, 0xF9FF, 0xE876,
	0x2102, 0x308B, 0x0210, 0x1399, 0x6726, 0x76AF, 0x4434, 0x55BD,
	0xAD4A, 0xBCC3, 0x8E58, 0x9FD1, 0xEB6E, 0xFAE7, 0xC87C, 0xD9F5,
	0x3183, 0x200A, 0x1291, 0x0318, 0x77A7, 0x662E, 0x54B5, 0x453C,
	0xBDCB, 0xAC42, 0x9ED9, 0x8F50, 0xFBEF, 0xEA66, 0xD8FD, 0xC974,
	0x4204, 0x538D, 0x6116, 0x709F, 0x0420, 0x15A9, 0x2732, 0x36BB,
	0xCE4C, 0xDFC5, 0xED5E, 0xFCD7, 0x8868, 0x99E1, 0xAB7A, 0xBAF3,
	0x5285, 0x430C, 0x7197, 0x601E, 0x14A1, 0x0528, 0x37B3, 0x263A,
	0xDECD, 0xCF44, 0xFDDF, 0xEC56, 0x98E9, 0x8960, 0xBBFB, 0xAA72,
	0x6306, 0x728F, 0x4014, 0x519D, 0x2522, 0x34AB, 0x0630, 0x17B9,
	0xEF4E, 0xFEC7, 0xCC5C, 0xDDD5, 0xA96A, 0xB8E3, 0x8A78, 0x9BF1,
	0x7387, 0x620E, 0x5095, 0x411C, 0x35A3, 0x242A, 0x16B1, 0x0738,
	0xFFCF, 0xEE46, 0xDCDD, 0xCD54, 0xB9EB, 0xA862, 0x9AF9, 0x8B70,
	0x8408, 0x9581, 0xA71A, 0xB693, 0xC22C, 0xD3A5, 0xE13E, 0xF0B7,
	0x0840, 0x19C9, 0x2B52, 0x3ADB, 0x4E64, 0x5FED, 0x6D76, 0x7CFF,
	0x9489, 0x8500, 0xB79B, 0xA612, 0xD2AD, 0xC324, 0xF1BF, 0xE036,
	0x18C1, 0x0948, 0x3BD3, 0x2A5A, 0x5EE5, 0x4F6C, 0x7DF7, 0x6C7E,
	0xA50A, 0xB483, 0x8618, 0x9791, 0xE32E, 0xF2A7, 0xC03C, 0xD1B5,
	0x2942, 0x38CB, 0x0A50, 0x1BD9, 0x6F66, 0x7EEF, 0x4C74, 0x5DFD,
	0xB58B, 0xA402, 0x9699, 0x8710, 0xF3AF, 0xE226, 0xD0BD, 0xC134,
	0x39C3, 0x284A, 0x1AD1, 0x0B58, 0x7FE7, 0x6E6E, 0x5CF5, 0x4D7C,
	0xC60C, 0xD785, 0xE51E, 0xF497, 0x8028, 0x91A1, 0xA33A, 0xB2B3,
	0x4A44, 0x5BCD, 0x6956, 0x78DF, 0x0C60, 0x1DE9, 0x2F72, 0x3EFB,
	0xD68D, 0xC704, 0xF59F, 0xE416, 0x90A9, 0x8120, 0xB3BB, 0xA232,
	0x5AC5, 0x4B4C, 0x79D7, 0x685E, 0x1CE1, 0x0D68, 0x3FF3, 0x2E7A,
	0xE70E, 0xF687, 0xC41C, 0xD595, 0xA12A, 0xB0A3, 0x8238, 0x93B1,
	0x6B46, 0x7ACF, 0x4854, 0x59DD, 0x2D62, 0x3CEB, 0x0E70, 0x1FF9,
	0xF78F, 0xE606, 0xD49D, 0xC514, 0xB1AB, 0xA022, 0x92B9, 0x8330,
	0x7BC7, 0x6A4E, 0x58D5, 0x495C, 0x3DE3, 0x2C6A, 0x1EF1, 0x0F78
	};
unsigned int bit::shift (unsigned int number, int offset) {
	if (offset < 0) {
		return (number >> offset);
		}
	else {
		return (number << offset);
		}
	}

bool bit::get (int number, int position) {
	return (number & (1 << (position - 1))) ? true : false;
	}

unsigned int bit::flip (unsigned int number, unsigned int position) {
	return (number ^ 1UL << (position - 1));
	}

unsigned int bit::set (unsigned int n, unsigned int p, bool b) {
	p -= 1;
	int mask = 1 << p;
	return ((n & ~mask) | ((int)b << p));
	}
unsigned long bit::swapBytes (unsigned long num, const unsigned int pos1, const unsigned int pos2) {
	unsigned long v1 = (num & (0xFF << ((pos1 - 1) * 8))) >> ((pos1 - 1) * 8);
	unsigned long v2 = (num & (0xFF << ((pos2 - 1) * 8))) >> ((pos2 - 1) * 8);
	num -= num & (0xFF << ((pos2 - 1) * 8));
	num -= num & (0xFF << ((pos1 - 1) * 8));
	num += v1 << ((pos2 - 1) * 8);
	num += v2 << ((pos1 - 1) * 8);
	return num;
	}
float bit::IntAsFloat (unsigned long b) {
	float result = 0.0;
	memcpy(&result, &b, 4);
	return result;
	}
unsigned long bit::FloatAsInt (float b) {
	unsigned long result = 0;
	memcpy(&result, &b, 4);
	return result;
	}


bytestream::bytestream () {
	pos = 0;
	size = 0;
	stream = NULL;
	islilEndian = true;
	}
bytestream::~bytestream () {
	if (stream != NULL) {delete[] stream;}
	}
size_t bytestream::getFileSizeW(std::wstring fileName) {
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesExW((wchar_t*)fileName.c_str(), GetFileExInfoStandard, &fad))
		return -1; // error condition, could call GetLastError to find out more
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return (size_t)size.QuadPart;
	}
bool bytestream::doesFileExist (std::string fileName) {
	DWORD dwAttrib = GetFileAttributesA(fileName.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
bool bytestream::doesFileExistW (std::wstring fileName) {
	DWORD dwAttrib = GetFileAttributesW((wchar_t*)fileName.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
bool bytestream::doesFolderExistW (std::wstring dirName_in) {
	//DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	DWORD ftyp = GetFileAttributesW((wchar_t*)dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) {
		return false;  //something is wrong with your path!
		}
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
		return true;   // this is a directory!
		}
	return false;    // this is not a directory!
	}
bool bytestream::makeDirW(std::wstring wsPath) {
	// https://www.codeguru.com/cpp/w-p/files/article.php/c4439/CreatePath--Full-Path-Creation-wstring-version.htm
	unsigned long attr;
	size_t pos;
	bool result = false;
	std::wstring tmp;

	if (wsPath.length() > 0) {
		if (wsPath[wsPath.length() - 1] != '\\') {
			wsPath += L"\\";
			}
		// Look for existing object:
		attr = GetFileAttributesW(wsPath.c_str());
		if (attr == 0xFFFFFFFF) { // doesn't exist yet - create it!
			pos = wsPath.find_last_of(L"\\", wsPath.length() - 2);
			if (pos != std::wstring::npos) {
				// Create parent dirs:
				result = makeDirW(wsPath.substr(0, pos + 1));
				}
			// Create node:
			result = result && CreateDirectoryW(wsPath.c_str(), NULL);
			CreateDirectoryW(wsPath.c_str(), NULL);
			}
		else if (FILE_ATTRIBUTE_DIRECTORY != attr) {
			// object already exists, but is not a dir
			result = false;
			}
		}
	return result;
	}
std::wstring bytestream::getFilenamePathW (const std::wstring &str) {
	// getFilenamePath file   -- returns: "g:\subdir1\subdir2\"
	size_t found;
	std::wstring strt;
	found = str.find_last_of(L"/\\");
	if (found != std::wstring::npos) {
		strt = str.substr(0, found);
		return (strt + L"\\");
		}
	else {
		return L"";
		}
	}
std::wstring bytestream::getFilenameFileW(const std::wstring &str) {
	// getFilenameFile file   -- returns: "myImage"
	size_t found;
	std::wstring strt;
	found = str.find_last_of(L"/\\");
	if (found < str.size()) {
		strt = str.substr(found + 1, -1);
		found = strt.find(L".");
		if (found < strt.size()) {
			strt = strt.substr(0, found);
			}
		//return strt;
		}
	else {
		strt = str;
		//return str;
		}
	size_t lastdot = strt.find_last_of(L".");
	if (lastdot == std::string::npos) return strt;
	return strt.substr(0, lastdot);
	}
std::wstring bytestream::getFilenameTypeW (std::wstring const &path ) {
	// getFilenameType file -- returns: ".jpg"
	std::wstring ext;
	size_t dotIdx = path.find_last_of( L"." );
	if ( dotIdx != std::wstring::npos ) {
		size_t dirSepIdx = path.find_last_of( L"/\\" );
		if ( dotIdx > dirSepIdx + 1 ) {
			ext = path.substr( dotIdx );
			}
		}
	return ext;
	}
std::string bytestream::getFilenamePath (const std::string &str) {
	// getFilenamePath file   -- returns: "g:\subdir1\subdir2\"
	unsigned int found = 0;
	std::string strt;
	found = str.find_last_of("/\\");
	if (found != std::string::npos) {
		strt = str.substr(0, found);
		return (strt + "\\");
		}
	else {
		return "";
		}
	}
std::string bytestream::getFilenameFile(const std::string &str) {
	// getFilenameFile file   -- returns: "myImage"
	unsigned int found = 0;
	std::string strt;
	found = str.find_last_of("/\\");
	if (found < str.size()) {
		strt = str.substr(found + 1, -1);
		found = strt.find(".");
		if (found < strt.size()) {
			strt = strt.substr(0, found);
			}
		//return strt;
		}
	else {
		strt = str;
		//return str;
		}
	unsigned int lastdot = strt.find_last_of(".");
	if (lastdot == std::string::npos) return strt;
	return strt.substr(0, lastdot);
	}
std::string bytestream::getFilenameType (std::string const &path ) {
	// getFilenameType file -- returns: ".jpg"
	std::string ext;
	unsigned int dotIdx = path.find_last_of( "." );
	if ( dotIdx != std::string::npos ) {
		unsigned int dirSepIdx = path.find_last_of( "/\\" );
		if ( dotIdx > dirSepIdx + 1 ) {
			ext = path.substr( dotIdx );
			}
		}
	return ext;
	}
void bytestream::setBigEndian () {islilEndian = false;}
void bytestream::setLittleEndian () {islilEndian = true;}
void bytestream::close () {
	if (stream != NULL) {delete[] stream;}
	pos = 0;
	size = 0;
	stream = NULL;
	islilEndian = true;
	}
bool bytestream::openFile(std::string filename, size_t file_size) {
	bool result = openFileW(std::wstring(filename.begin(), filename.end()), file_size);
	if (result) {
		// extract components of file path
		file = filename;
		fpath = getFilenamePath(filename);
		fname = getFilenameFile(filename);
		fext = getFilenameType(filename);
		}
	return result;
	}
bool bytestream::openFileW (std::wstring filename, size_t file_size) {
	HANDLE hFile = CreateFileW(
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
		);

	// check that file was opened successfully
	if (hFile == INVALID_HANDLE_VALUE) {
		//std::wcout << L"Failed to Open File {" << filename << L"}\n";
		return false;
		}

	// Clear old buffer
	close();

	// get / check file size is larger then 0
	size = GetFileSize(hFile, NULL);
	if (file_size > 0 && file_size < size) {
		size = file_size;
		}

	if (size == 0) {
		std::cout << "Failed to read file. File is Empty?\n";
		return false;
		}

	// size char for buffer
	stream = new char[size];

	// attempt to read file contents into memory
	unsigned long dwBytesRead = 0;
	if(ReadFile(hFile, stream, size, &dwBytesRead, NULL) == FALSE || dwBytesRead != size) {
		std::cout << "Failed to copy file into memory\n";
		CloseHandle(hFile);
		close();
		return false;
		}

	// close out handle :-)
	CloseHandle(hFile);

	// extract components of file path
	fileW = filename;
	fpathW = getFilenamePathW(filename);
	fnameW = getFilenameFileW(filename);
	fextW = getFilenameTypeW(filename);

	return true;
	}

bool bytestream::openResource (int resource_id, const char* resource_class) {

	/*
	https://mklimenko.github.io/english/2018/06/23/embed-resources-msvc/
	https://stackoverflow.com/questions/16527973/load-resource-as-byte-array-programmaticaly-in-c

	usage:
	openResource(IDR_DATA1, "RCDATA");
	*/

	HRSRC hResource = FindResourceA(NULL, MAKEINTRESOURCEA(resource_id), resource_class);
	if (hResource == NULL) {
		std::cout << "failed To Find Resource" << std::endl;
		return false;
		}

	HGLOBAL hMemory = LoadResource(NULL, hResource);
	if (hMemory == NULL) {
		std::cout << "failed To Load Resource" << std::endl;
		return false;
		}

	DWORD dwSize = SizeofResource(NULL, hResource);
	LPVOID lpAddress = LockResource(hMemory);

	if (dwSize == 0) {
		std::cout << "file is empty" << std::endl;
		return false;
		}

	if (stream != NULL) {
		delete[] stream;
		}

	size = dwSize;
	stream = new char[dwSize];
	memcpy(stream, lpAddress, dwSize);
	return true;
	}

bool bytestream::amendFile (std::wstring filename, size_t &offset) {

	HANDLE hFile = CreateFileW (
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
		);

	// check that file was opened successfully
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to Open File\n";
		return false;
		}
	//std::cout << offset << std::endl;
	// get / check file size is larger then 0
	size_t fsize = GetFileSize(hFile, NULL);
	if (fsize == 0 || offset + fsize > size) {
		std::cout << "Failed to read file. File is Empty?\n";
		return false;
		}

	// attempt to read file contents into memory
	unsigned long dwBytesRead = 0;
	if(ReadFile(hFile, &stream[offset], fsize, &dwBytesRead, NULL) == FALSE || dwBytesRead != fsize) {
		std::cout << "Failed to copy file into memory\n";
		CloseHandle(hFile);
		return false;
		}

	offset += fsize;

	// close out handle :-)
	CloseHandle(hFile);

	return true;
	}
bool bytestream::writeFile (std::string filename, size_t offset, size_t wsize, char* data ) {
	//std::wcout << "filename:\t" << filename << std::endl;
	if (data == NULL) {
		if (wsize < 1) {wsize = size - offset;}
		if (offset + wsize > size) {wsize = size - offset;}
		}
	else if (wsize == 0) {
		return false;
		}

	unsigned long dwBytesWritten = 0;
	unsigned long dwPos = 0;

	//std::wcout << L"File: " << filename << std::endl;
	HANDLE hFile = CreateFileA(
		filename.c_str(),			// open One.txt
		GENERIC_WRITE,						// open for reading
		FILE_SHARE_READ,					// do not share
		NULL,								// no security
		CREATE_ALWAYS,							// existing file only
		FILE_ATTRIBUTE_NORMAL,				// normal file
		NULL								// no attr. template
		);

	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << L"failed to write file:\n\t" << filename << std::endl;
		return false;
		}

	dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
	LockFile(hFile, dwPos, 0, wsize, 0);
	if (data == NULL) {
		WriteFile(hFile, stream + offset, wsize, &dwBytesWritten, NULL);
		}
	else {
		WriteFile(hFile, data, wsize, &dwBytesWritten, NULL);
		}

	UnlockFile(hFile, dwPos, 0, wsize, 0);
	CloseHandle(hFile);
	return true;
	}
bool bytestream::writeFileW (std::wstring filename, size_t offset, size_t wsize, char* data ) {
	//std::wcout << "filename:\t" << filename << std::endl;
	if (data == NULL) {
		if (wsize < 1) {wsize = size - offset;}
		if (offset + wsize > size) {wsize = size - offset;}
		}
	else if (wsize == 0) {
		return false;
		}

	unsigned long dwBytesWritten = 0;
	unsigned long dwPos = 0;

	//std::wcout << L"File: " << filename << std::endl;

	HANDLE hFile = CreateFileW(
		filename.c_str(),			// open One.txt
		GENERIC_WRITE,						// open for reading
		FILE_SHARE_READ,					// do not share
		NULL,								// no security
		CREATE_ALWAYS,							// existing file only
		FILE_ATTRIBUTE_NORMAL,				// normal file
		NULL								// no attr. template
		);

	if (hFile == INVALID_HANDLE_VALUE) {
		std::wcout << L"failed to write file:\n\t" << filename << std::endl;
		return false;
		}

	dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
	LockFile(hFile, dwPos, 0, wsize, 0);
	if (data == NULL) {
		WriteFile(hFile, stream + offset, wsize, &dwBytesWritten, NULL);
		}
	else {
		WriteFile(hFile, data, wsize, &dwBytesWritten, NULL);
		}

	UnlockFile(hFile, dwPos, 0, wsize, 0);
	CloseHandle(hFile);
	return true;
	}

//bool bytestream::size () {return size;}

bool bytestream::eos () {
	if (pos >= size) {
		return true;
		}
	else {
		return false;
		}
	}
bool bytestream::createFile (unsigned long bufferSize) {
	if (bufferSize > 0) {
		close();
		size = bufferSize;
		stream = new char[bufferSize];
		return true;
		}
	return false;
	}
void bytestream::resize (size_t newsize, bool flush) {
	if (newsize <= 0) {return;}
	if (newsize > size && stream != NULL) {
		delete[] stream;
		if (pos > newsize) {pos = 0;}
		size = newsize;
		stream = new char[size];
		}
	else if (stream != NULL && newsize < size) {
		size = newsize;
		if (pos > newsize) {pos = 0;}
		}
	else {
		if (stream != NULL) {delete[] stream;}
		size = newsize;
		if (pos > newsize) {pos = 0;}
		stream = new char[size];
		}
	if (flush) {
		for (unsigned int i = 0; i < size; i++) {
			stream[i] = 0;
			}
		}
	}
/** @brief copy's bytes from a char array to the bytestream
 *  @param {src_buf} char array to copy from
 *  @param {src_len} size of the char array coping from
 *  @param {src_pos, Default:0} position in the char array to read from
 *  @param {tar_dest, Default:0} position in bytestream to write to
 *  @return {VOID}
 */
void bytestream::copy (char* src_buf, size_t src_len, size_t src_pos, size_t tar_dest) {



	// Check Array is Not Empty
	if (src_buf == NULL) {
		std::cout << "Input Buffer is invalid\n";
		return;
		}

	// Check if Resize is needed
	if (tar_dest + src_len > size) {
		resize(tar_dest + src_len);
		}

	// Copy Char Arrays
	bool useStdCopy = true;
	if (useStdCopy) {
		std::copy(&src_buf[src_pos], &src_buf[src_pos + src_len], &stream[tar_dest]);
		}
	else {
		for (unsigned int i = 0; i < src_len; i++) {

			stream[tar_dest + i] = src_buf[src_pos + i];
			}
		}


	}
size_t bytestream::tell () {return pos;}
void bytestream::seek (unsigned long offset, char dir) {
	switch (dir) {
		case 0: pos = offset; break;	// abs
		case 1: pos += offset; break;	// rel
		case 2: pos -= offset; break;	// end
		}
	if (pos > size) {pos = size;}
	}
signed long bytestream::unsigned_to_signed (unsigned long n, char nbits) {	// unsigned_to_signed 0x80 8 = -128
	signed long result = n;
	if (n > pow(2.0f, nbits) / 2.0f) {
		result = (signed long)(n - pow(2.0f, nbits));
		}
	return result;
	}

uint32_t bytestream::crc32 (size_t crc_pos, size_t crc_len) { // Cyclic Redundancy Check

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	// http://www.hackersdelight.org/hdcodetxt/crc.c.txt
	uint32_t crc = 0xFFFFFFFF;
	unsigned int b = 8;
	for (unsigned int i = crc_pos; i < crc_end; i++) {
		crc = crc ^ (uint8_t)stream[i];
		for (unsigned int j = 0; j < b; j++) {
			crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1));
			}
		}
	return (crc ^ 0xFFFFFFFF);
	}

uint32_t bytestream::adler32 (size_t crc_pos, size_t crc_len, uint32_t seed) { //  Mark Adler

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	const uint32_t MOD_ADLER = 0xFFF1;
    uint32_t a = seed & 0xFFFF;
    uint32_t b = (seed >> 16) & 0xFFFF;

    for (unsigned int i = crc_pos; i < crc_end; i++) {
        a = (a + (unsigned char)stream[i]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
		}
    return (b << 16) | a;
	}

uint32_t bytestream::fnv1_32 (size_t crc_pos, size_t crc_len) { //  Fowler Noll Vo

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	uint32_t FNV_prime = 0x01000193;
	uint32_t hash = 0x811C9DC5;


	for (unsigned int i = crc_pos; i < crc_end; i++) {
		hash = hash * FNV_prime;
		hash = hash ^ (unsigned char)stream[i];
		}
	return hash;
	}

uint32_t bytestream::fnv1a_32 (size_t crc_pos, size_t crc_len) { //  Fowler Noll Vo (Variant A)

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	uint32_t FNV_prime = 0x01000193;
	uint32_t hash = 0x811C9DC5;


	for (unsigned int i = crc_pos; i < crc_end; i++) {
		hash = hash ^ (unsigned char)stream[i];
		hash = hash * FNV_prime;
		}
	return hash;
	}

uint32_t bytestream::joaat32 (size_t crc_pos, size_t crc_len) { //  Jenkins One At A Time
	// https://en.wikipedia.org/wiki/Jenkins_hash_function
	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	uint32_t hash = 0;
	for (unsigned int i = crc_pos; i < crc_end; i++) {
		hash += (unsigned char)stream[i];
		hash += hash << 10;
		hash ^= hash >> 6;
		}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return hash;
	}

uint32_t bytestream::djb2_32 (size_t crc_pos, size_t crc_len) { //  Daniel Julius Bernstein

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	uint32_t hash = 0x00001505;
	for (unsigned int i = crc_pos; i < crc_end; i++) {
		hash = (hash * 33) + (unsigned char)stream[i];
		}
	return hash;
	}

uint32_t bytestream::djb2_32a (size_t crc_pos, size_t crc_len) { //  Daniel Julius Bernstein (Variant A)

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	uint32_t hash = 0x00001505;
	for (unsigned int i = crc_pos; i < crc_end; i++) {
		//hash = bit.xor ((bit.shift hash 5) + hash) (bit.CharAsInt str[i])
		hash = (hash * 33) ^ (unsigned char)stream[i];
		}
	return hash;
	}

uint32_t bytestream::sdbm_32 (size_t crc_pos, size_t crc_len) { //   Small Data Base Manager

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	uint32_t hash = 0x00001505;
	for (unsigned int i = crc_pos; i < crc_end; i++) {

		hash = (unsigned char)stream[i] + (hash << 6) + (hash << 16) - hash;
		//hash = hash * 65599 + (bit.CharAsInt lstr[i])

		}
	return hash;
	}

uint32_t bytestream::aod_32 (size_t crc_pos, size_t crc_len) { //   Angel of Darkness Hash Algo

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	uint32_t hash = crc_len;
	for (unsigned int i = crc_pos; i < crc_end; i++) {
		hash ^= (hash >> 2) + 32 * hash + (unsigned char)stream[i];
		}
	return hash;
	}

uint32_t bytestream::fcs16 (size_t crc_pos, size_t crc_len) { //   Frame Check Sequence 16Bit

	if (crc_len == 0) {crc_len = size - crc_pos;}
	size_t crc_end = crc_pos + crc_len;

	uint32_t hash = 0xFFFF;
	for (unsigned int i = crc_pos; i < crc_end; i++) {
		hash = fcs16_lut[(((unsigned char)stream[i] ^ hash) & 0xFF)] ^ (hash >> 8);
		}
	hash ^= 0xFFFF;
	return hash;
	}

void bytestream::md5 (uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, size_t crc_pos, size_t crc_len, bool verbose) {

	if (crc_len == 0) {crc_len = size - crc_pos;}

	uint8_t SHIFT_AMTS[16] = {7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21};
	uint32_t TABLE_T[64];
	for (uint32_t i = 0; i < 64; i++) {TABLE_T[i] = 0x100000000 * abs(sin(i + 1));}
	uint32_t numBlocks = ((crc_len + 8) >> 6) + 1;
	uint32_t totalLen = numBlocks << 6;
	uint32_t messageLenBits = crc_len << 3;

	uint32_t paddingLen = totalLen - crc_len;
	uint8_t* paddingBytes = NULL;
	if (paddingLen > 0) {paddingBytes = new uint8_t[paddingLen];}
	paddingBytes[0] = 0x80;
	for (uint32_t i = 1; i < paddingLen; i++) {paddingBytes[i] = 0;}
	for (uint32_t i = 0; i < 8; i++) {
		paddingBytes[paddingLen - 8 + i] = (uint8_t)messageLenBits;
		messageLenBits = messageLenBits >> 8;
		}


	uint32_t INIT_A = 0x67452301;
	uint32_t INIT_B = 0xEFCDAB89;
	uint32_t INIT_C = 0x98BADCFE;
	uint32_t INIT_D = 0x10325476;

	a = INIT_A;
	b = INIT_B;
	c = INIT_C;
	d = INIT_D;

	uint32_t buffer[16];
	uint32_t index = 0;
	uint32_t originalA = INIT_A;
	uint32_t originalB = INIT_B;
	uint32_t originalC = INIT_C;
	uint32_t originalD = INIT_D;
	uint32_t div16 = 0;
	uint32_t f = 0;
	uint32_t bufferIndex = 0;
	uint32_t temp = 0;
	uint32_t temp2 = 0;
	for (uint32_t i = 0; i < numBlocks; i++) {
		index = i << 6;
		for (uint32_t j = 0; j < 64; j++) {

			if (index < crc_len) {temp = (uint32_t)stream[index + crc_pos];}
			else {temp = (uint32_t)paddingBytes[index - crc_len];}
			buffer[j >> 2] = (temp << 24) | (buffer[j >> 2] >> 8);
			index++;
			}
		originalA = a;
		originalB = b;
		originalC = c;
		originalD = d;
		for (uint32_t j = 0; j < 64; j++) {
			div16 = j >> 4;

			f = 0;
			bufferIndex = j;
			switch (div16) {
				case 0: {f = (b & c) | ((~b) & d); break;}
				case 1: {f = (b & d) | (c & ~d); bufferIndex = (bufferIndex * 5 + 1) & 0x0F; break;}
				case 2: {f = (b ^ c) ^ d; bufferIndex = (bufferIndex * 3 + 5) & 0x0F; break;}
				case 3: {f = c ^ (b | ~d); bufferIndex = (bufferIndex * 7) & 0x0F; break;}
				}

			temp2 = SHIFT_AMTS[(div16 << 2) | (j & 3)];
			temp = a + f + buffer[bufferIndex] + TABLE_T[j];
			temp = b + ((temp << temp2) | ((temp >> (32 - temp2)) & ((1 << temp2) - 1)));

			a = d;
			d = c;
			c = b;
			b = temp;
			}
		a += originalA;
		b += originalB;
		c += originalC;
		d += originalD;
		}
	if (paddingBytes != NULL) {delete[] paddingBytes;}
	if (verbose) {
		// requires #include  <iomanip>
		//uint32_t n;
		//n = a;
		//std::cout << "0x";
		//for (uint32_t j = 0; j < 4; j++) {std::cout << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (n & 0xFF); n = n >> 8;}
		//n = b; for (uint32_t j = 0; j < 4; j++) {std::cout << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (n & 0xFF); n = n >> 8;}
		//n = c; for (uint32_t j = 0; j < 4; j++) {std::cout << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (n & 0xFF); n = n >> 8;}
		//n = d; for (uint32_t j = 0; j < 4; j++) {std::cout << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (n & 0xFF); n = n >> 8;}
		//std::cout << std::endl;
		}
	}


std::string bytestream::base64_encode (size_t crc_pos, size_t crc_len) {

	if (crc_len == 0) {crc_len = size - crc_pos;}

	const std::string chset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	unsigned int nblocks = crc_len / 3;
	unsigned int p = crc_pos;
	std::string str = "";
	if (crc_len > 0) {

		// calculate size
		// bit.and ((4.0 * 8 / 3.0) + 3.0) (bit.not 3)
		// 4.0 * (Ceil (8 / 3.0))
		unsigned int len = ((4 * crc_len / 3) + 3) & ~3;
		str = std::string (len, '=');

		uint32_t d = 0;
		unsigned int x = 0;
		for (unsigned int i = 0; i < nblocks; i++) {
			d = (unsigned char)stream[p + 2] + ((unsigned char)stream[p + 1] << 8) + ((unsigned char)stream[p + 0] << 16);
			for (unsigned int b = 4; b-- > 0; ) {
				str[x++] = chset[(d >> (6 * b)) & 0x3F];
				}
			p+=3;
			}
		unsigned char pad = 0;
		switch (crc_len - (nblocks * 3)) {
			case 1: {
				d = ((unsigned char)stream[p + 0] << 16);
				p+=1;
				pad = 2;
				break;
				}
			case 2: {
				d = ((unsigned char)stream[p + 1] << 8) + ((unsigned char)stream[p + 0] << 16);
				p+=2;
				pad = 1;
				break;
				}
			}
		if (pad > 0) {
			for (unsigned int b = 4; b-- > pad; ) {str[x++] = chset[(d >> (6 * b)) & 0x3F];}
			//for (unsigned char i = 0; i < pad; i++) {str[x++] = '=';}
			}
		}

	return str;
	}

void bytestream::base64_decode (std::string &input, size_t tar_pos) {
	size_t out_len = 0;
	if (input.length() > 0) {
		out_len = (input.length() / 4) * 3;
		for (unsigned char i = 0; i < 2; i++) {
			if (input.substr(input.length() - (i + 1), 1) == "=") {
				out_len -= 1;
				}
			}
		}
	if (out_len > 0) {
		if (tar_pos + out_len > size) {
			resize(tar_pos + out_len);
			}
		const std::string chset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		unsigned int w1, w2, w3, w4;
		unsigned int count = input.length() / 4;
		for (unsigned int i = 0; i < count; i++) {
			w1 = chset.find(input.substr((i * 4) + 0, 1));
			w2 = chset.find(input.substr((i * 4) + 1, 1));
			w3 = chset.find(input.substr((i * 4) + 2, 1));
			w4 = chset.find(input.substr((i * 4) + 3, 1));
			if (w2 != std::string::npos) {stream[tar_pos++] = (unsigned char)(w1 *  4 + (w2 / 16)) & 0xFF;}
			if (w3 != std::string::npos) {stream[tar_pos++] = (unsigned char)(w2 * 16 + (w3 /  4)) & 0xFF;}
			if (w4 != std::string::npos) {stream[tar_pos++] = (unsigned char)(w3 * 64 +  w4      ) & 0xFF;}
			}
		}
	}

uint8_t bytestream::readUbyte () {
	uint8_t result = 0xFF;
	if (pos + 1 <= size) {
		result = (uint8_t)stream[pos];
		pos += 1;
		}
	return result;
	}
uint16_t bytestream::readUshort () {
	unsigned char byteOrder[] = {0, 1};
	if (!islilEndian) {byteOrder[0] = 1; byteOrder[1] = 0;}
	uint16_t result = 0xFFFF;
	if (pos + 2 <= size) {
		//result = (uint16_t)((uint8_t)stream[pos + byteOrder[0]] * 0x0001);
		//result += (uint16_t)((uint8_t)stream[pos + byteOrder[1]] * 0x0100);
		result = ((unsigned short)stream[pos + byteOrder[1]] << 8) | (unsigned char)stream[pos + byteOrder[0]];
		pos += 2;
		}
	return result;
	}
uint32_t bytestream::readUlong () {
	unsigned char byteOrder[] = {0, 1, 2, 3};
	if (!islilEndian) {
		byteOrder[0] = 3; byteOrder[1] = 2;
		byteOrder[2] = 1; byteOrder[3] = 0;
		}
	uint32_t result = 0xFFFFFFFF;
	if (pos + 4 <= size) {
		result = (uint32_t)((uint8_t)stream[pos + byteOrder[0]] * 0x00000001);
		result += (uint32_t)((uint8_t)stream[pos + byteOrder[1]] * 0x00000100);
		result += (uint32_t)((uint8_t)stream[pos + byteOrder[2]] * 0x00010000);
		result += (uint32_t)((uint8_t)stream[pos + byteOrder[3]] * 0x01000000);



/*
int a = int((unsigned char)(buffer[0]) << 24 |
            (unsigned char)(buffer[1]) << 16 |
            (unsigned char)(buffer[2]) << 8 |
            (unsigned char)(buffer[3]));

*/



		pos += 4;
		}
	return result;
	}
uint64_t bytestream::readUlonglong () {
	unsigned char byteOrder[] = {0, 1, 2, 3, 4, 5, 6, 7};
	if (!islilEndian) {
		byteOrder[0] = 7; byteOrder[1] = 6; byteOrder[2] = 5;
		byteOrder[3] = 4; byteOrder[4] = 3; byteOrder[5] = 2;
		byteOrder[6] = 1; byteOrder[7] = 0;
		}
	unsigned long long result = {
		((uint8_t)stream[pos + byteOrder[0]] * (unsigned long long)0x0000000000000001) + \
		((uint8_t)stream[pos + byteOrder[1]] * (unsigned long long)0x0000000000000100) + \
		((uint8_t)stream[pos + byteOrder[2]] * (unsigned long long)0x0000000000010000) + \
		((uint8_t)stream[pos + byteOrder[3]] * (unsigned long long)0x0000000001000000) + \
		((uint8_t)stream[pos + byteOrder[4]] * (unsigned long long)0x0000000100000000) + \
		((uint8_t)stream[pos + byteOrder[5]] * (unsigned long long)0x0000010000000000) + \
		((uint8_t)stream[pos + byteOrder[6]] * (unsigned long long)0x0001000000000000) + \
		((uint8_t)stream[pos + byteOrder[7]] * (unsigned long long)0x0100000000000000)
		};
	pos += 8;
	return result;
	}
int8_t bytestream::readbyte() {return (int8_t)unsigned_to_signed(readUbyte(), 8);}
int16_t bytestream::readshort() {return (int16_t)unsigned_to_signed(readUshort(), 16);}
int32_t bytestream::readlong() {return (int32_t)unsigned_to_signed(readUlong(), 32);}
int64_t bytestream::readlonglong() {return (int64_t)unsigned_to_signed((unsigned long)readUlonglong(), 64);}
std::string bytestream::readstring (int length, unsigned char term) {
	std::string result = "";
	unsigned char letter;
	bool isTerm = false;
	if (length < 0) {
		while (isTerm == false && pos < size) {
			if (pos < size) {
				letter = stream[pos];
				pos++;
				}
			else {
				isTerm = true;
				}
			if (letter == term) {isTerm = true;}
			if (isTerm == false) {result += letter;}
			}
		}
	else {
		if (length > 0 && (pos + length) <= size) {
			result.reserve(length);
			for (int i = 0; i < length; ++i) {
				letter = stream[pos + i];
				if (letter == 0) {isTerm = true;}
				if (isTerm == false) {result += letter;}
				}
			pos += length;
			}
		}
	return result;
	}
std::wstring bytestream::readstringW (int length, wchar_t term) {
	std::wstring result = L"";
	wchar_t letter;
	bool isTerm = false;
	if (length < 0) {
		while (isTerm == false && pos < size) {
			if (pos < size) {
				letter = readUshort();
				}
			else {
				isTerm = true;
				}
			if (letter == term) {isTerm = true;}
			if (isTerm == false) {
				result += letter;
				}
			}
		}
	else {
		if (length > 0 && (pos + length) <= size) {
			size_t jump = pos + length;
			result.reserve(length);
			for (int i = 0; i < length; ++i) {
				letter = readUshort();
				if (letter == 0) {
					isTerm = true;
					break;
					}
				if (isTerm == false) {result += letter;}
				}
			pos = jump;
			}
		}
	return result;
	}
std::string bytestream::readline () {
	uint32_t startpoint = pos;
	std::string line = "";
	while (pos < size && stream[pos] != 0x0A && stream[pos] != 0x0D) {
		pos++;
		}
	if (pos > startpoint) {
		line = std::string(&stream[startpoint], pos - startpoint);
		}
	while (pos < size && (stream[pos] == 0x0A || stream[pos] == 0x0D)) {
		pos++;
		}
	return line;
	}
std::wstring bytestream::readlineW () {
	std::wstring line = L"";
	uint16_t b;
	while (!eos()) {
		b = readUshort();
		if (b == 0x0A || b == 0x0D) {
			break;
			}
		line += b;
		}
	return line;
	}
float bytestream::readfloat () {
	float result = 0.0;
	unsigned long b = readUlong();
	memcpy(&result, &b, 4);
	return result;
	}
double bytestream::readdouble () {
	double result = 0.0;
	unsigned long long b = readUlonglong();
	memcpy(&result, &b, 8);
	return result;
	}
void bytestream::writebyte (unsigned char val) {
	stream[pos] = val;
	pos++;
	}
void bytestream::writeshort (unsigned short val) {
	if (!islilEndian) {
		stream[pos + 1] = val & 0x00FF;
		stream[pos + 0] = (val & 0xFF00) >> 8;
		}
	else {
		stream[pos + 1] = (val & 0xFF00) >> 8;
		stream[pos + 0] = val & 0x00FF;
		}
	pos+=2;
	}
void bytestream::writelong (unsigned long val) {
	if (!islilEndian) {
		stream[pos + 3] = (uint8_t)(val & 0x00FF);
		stream[pos + 2] = (uint8_t)((val & 0xFF00) >> 0x08);
		stream[pos + 1] = (uint8_t)((val & 0xFF0000) >> 0x10);
		stream[pos + 0] = (uint8_t)((val & 0xFF000000) >> 0x18);
		}
	else {
		stream[pos + 3] = (uint8_t)((val & 0xFF000000) >> 0x18);
		stream[pos + 2] = (uint8_t)((val & 0xFF0000) >> 0x10);
		stream[pos + 1] = (uint8_t)((val & 0xFF00) >> 0x08);
		stream[pos + 0] = (uint8_t)(val & 0x00FF);
		}
	pos+=4;
	}
void bytestream::writeUbyte (unsigned char val) {
	stream[pos] = val;
	pos++;
	}
void bytestream::writeUshort (unsigned short val) {
	if (!islilEndian) {
		stream[pos + 1] = val & 0x00FF;
		stream[pos + 0] = (val & 0xFF00) >> 8;
		}
	else {
		stream[pos + 1] = (val & 0xFF00) >> 8;
		stream[pos + 0] = val & 0x00FF;
		}
	pos+=2;
	}
void bytestream::writeUlong (unsigned long val) {
	if (!islilEndian) {
		stream[pos + 3] = (uint8_t)(val & 0x00FF);
		stream[pos + 2] = (uint8_t)((val & 0xFF00) >> 0x08);
		stream[pos + 1] = (uint8_t)((val & 0xFF0000) >> 0x10);
		stream[pos + 0] = (uint8_t)((val & 0xFF000000) >> 0x18);
		}
	else {
		stream[pos + 3] = (uint8_t)((val & 0xFF000000) >> 0x18);
		stream[pos + 2] = (uint8_t)((val & 0xFF0000) >> 0x10);
		stream[pos + 1] = (uint8_t)((val & 0xFF00) >> 0x08);
		stream[pos + 0] = (uint8_t)(val & 0x00FF);
		}
	pos+=4;
	}
void bytestream::writeUlonglong (unsigned long long val) {
	if (!islilEndian) {
		stream[pos + 7] = (uint8_t)(val & 0x00FF);
		stream[pos + 6] = (uint8_t)((val & 0xFF00) >> 8);
		stream[pos + 5] = (uint8_t)((val & 0xFF0000) >> 16);
		stream[pos + 4] = (uint8_t)((val & 0xFF000000) >> 24);
		stream[pos + 3] = (uint8_t)((val & 0xFF00000000) >> 32);
		stream[pos + 2] = (uint8_t)((val & 0xFF0000000000) >> 40);
		stream[pos + 1] = (uint8_t)((val & 0xFF000000000000) >> 48);
		stream[pos + 0] = (uint8_t)((val & 0xFF00000000000000) >> 56);
		}
	else {
		stream[pos + 7] = (uint8_t)((val & 0xFF00000000000000) >> 56);
		stream[pos + 6] = (uint8_t)((val & 0xFF000000000000) >> 48);
		stream[pos + 5] = (uint8_t)((val & 0xFF0000000000) >> 40);
		stream[pos + 4] = (uint8_t)((val & 0xFF00000000) >> 32);
		stream[pos + 3] = (uint8_t)((val & 0xFF000000) >> 24);
		stream[pos + 2] = (uint8_t)((val & 0xFF0000) >> 16);
		stream[pos + 1] = (uint8_t)((val & 0xFF00) >> 8);
		stream[pos + 0] = (uint8_t)(val & 0x00FF);
		}
	pos+=8;
	}
//void bytestream::writefloat (float val) {
//	unsigned char* c = (unsigned char*) &val;
//	if (!islilEndian) {
//		stream[pos + 3] = c[0];
//		stream[pos + 2] = c[1];
//		stream[pos + 1] = c[2];
//		stream[pos + 0] = c[3];
//		}
//	else {
//		stream[pos + 3] = c[3];
//		stream[pos + 2] = c[2];
//		stream[pos + 1] = c[1];
//		stream[pos + 0] = c[0];
//		}
//	pos+=4;
//	}
void bytestream::writestring (std::string str, signed long length) {
	if (length > -1) {
		unsigned long len = length;
		for (unsigned long i = 0; i < len; i++) {
			if (i < str.size()) {
				writebyte(str[i]);
				}
			else {
				writebyte(0);
				}
			}
		}
	else {
		if (str.size() > 0) {
			for (unsigned long i = 0; i < str.size(); i++) {
				writebyte(str[i]);
				}
			}
		writebyte(0);
		}
	}
void bytestream::writefloat (float val) {
	unsigned char* c = (unsigned char*) &val;
	unsigned char order[4] = {0, 1, 2, 3};
	if (!islilEndian) {
		order[0] = 3; order[1] = 2;
		order[2] = 1; order[3] = 0;
		}
	for (int i = 0; i < 4; i++) {
		stream[pos + order[i]] = c[i];
		}
	pos+=4;
	}
void bytestream::writedouble (double val) {
	unsigned char* c = (unsigned char*) &val;
	char order[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	for (int i = 0; i < 8; i++) {
		stream[pos + order[i]] = c[i];
		}
	pos+=8;
	}
