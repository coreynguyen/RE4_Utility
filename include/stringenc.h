#ifndef STRINGENC_H
#define STRINGENC_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <string>
#include <windows.h>
#include "stringext.h"

std::wstring shift_jis_to_utf_16(const std::string& str);
std::string UTF8toSjis2(std::string srcUTF8);
std::string SjistoUTF82(std::string srcSjis);
std::string sjis2utf8(const std::string& sjis);
std::string utf_16_to_shift_jis(const std::wstring& str);
std::string char_utf_16_to_shift_jis(const char* str);
std::string unicode_2_utf8 (uint32_t x);
std::wstring utf8_2_unicode (std::string &str);

#endif // STRINGENC_H
