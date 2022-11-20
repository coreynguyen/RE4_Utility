#include "stringenc.h"


std::wstring shift_jis_to_utf_16(const std::string& str) {
	//https://qiita.com/yumetodo/items/453d14eff41b805d8fc4
    static_assert(sizeof(wchar_t) == 2, "this function is windows only");
    const int len = ::MultiByteToWideChar(932/*CP_ACP*/, 0, str.c_str(), -1, nullptr, 0);
    std::wstring re(len * 2 + 2, L'\0');
    if (!::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &re[0], len)) {
        const auto ec = ::GetLastError();
        switch (ec)
        {
        case ERROR_INSUFFICIENT_BUFFER:
            throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INSUFFICIENT_BUFFER"); break;
        case ERROR_INVALID_FLAGS:
            throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_FLAGS"); break;
        case ERROR_INVALID_PARAMETER:
            throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_PARAMETER"); break;
        case ERROR_NO_UNICODE_TRANSLATION:
            throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_NO_UNICODE_TRANSLATION"); break;
        default:
            throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + to_string(ec) + ')'); break;
            //throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + std::to_string(ec) + ')'); break;
        	}
    	}
    const std::size_t real_len = std::wcslen(re.c_str());
    re.resize(real_len);
    re.shrink_to_fit();
    return re;
	}

std::string UTF8toSjis2(std::string srcUTF8){
	// http://sayahamitt.net/utf8%E3%81%AAstring%E5%85%A5%E3%82%8C%E3%81%9F%E3%82%89shiftjis%E3%81%AAstring%E5%87%BA%E3%81%A6%E3%81%8F%E3%82%8B%E9%96%A2%E6%95%B0%E4%BD%9C%E3%81%A3%E3%81%9F/
	int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(),srcUTF8.size() + 1, NULL, 0);
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];
	MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1,bufUnicode, lenghtUnicode);
	int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
	char* bufShiftJis = new char[lengthSJis];
	WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);
	std::string strSJis(bufShiftJis);
	delete bufUnicode;
	delete bufShiftJis;
	return strSJis;
	}

std::string SjistoUTF82(std::string srcSjis){
	// http://sayahamitt.net/utf8%E3%81%AAstring%E5%85%A5%E3%82%8C%E3%81%9F%E3%82%89shiftjis%E3%81%AAstring%E5%87%BA%E3%81%A6%E3%81%8F%E3%82%8B%E9%96%A2%E6%95%B0%E4%BD%9C%E3%81%A3%E3%81%9F/
	int lenghtUnicode = MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, NULL, 0);
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];
	MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, bufUnicode, lenghtUnicode);
	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
	char* bufUTF8 = new char[lengthUTF8];
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUnicode + 1, bufUTF8, lengthUTF8, NULL, NULL);
	std::string strUTF8(bufUTF8);
	delete bufUnicode;
	delete bufUTF8;
	return strUTF8;
	}

std::string sjis2utf8(const std::string& sjis) {
	//VC++ SJIS string ‚ð utf-8‚Ìstring‚É•ÏŠ·‚·‚é
	std::string utf8_string;

	//ˆê’USJIS‚©‚çutf-16‚Ö•ÏŠ·
	LPCCH pSJIS = (LPCCH)sjis.c_str();
	int utf16size = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, pSJIS, -1, 0, 0);
	if (utf16size != 0) {
		LPWSTR pUTF16 = new WCHAR[utf16size];
		if (::MultiByteToWideChar(CP_ACP, 0, (LPCCH)pSJIS, -1, pUTF16, utf16size) != 0) {
			//ŽŸ‚Éutf-16‚©‚çutf-8‚Ö•ÏŠ·
			int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, pUTF16, -1, 0, 0, 0, 0);
			if (utf8size != 0) {
				char* pUTF8 = new char[utf8size + 16];
				ZeroMemory(pUTF8, utf8size + 16);
				if (::WideCharToMultiByte(CP_UTF8, 0, pUTF16, -1, pUTF8, utf8size, 0, 0) != 0) {
					utf8_string = std::string(pUTF8);
					}
				delete pUTF8;
				}
			}
		delete pUTF16;
		}
	return utf8_string;
	}

std::string utf_16_to_shift_jis(const std::wstring& str) {
	//https://qiita.com/yumetodo/items/453d14eff41b805d8fc4
    static_assert(sizeof(wchar_t) == 2, "this function is windows only");
    const int len = ::WideCharToMultiByte(932/*CP_ACP*/, 0, str.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string re(len * 2, '\0');
    if (!::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, &re[0], len, nullptr, nullptr)) {
        const auto ec = ::GetLastError();
        switch (ec) {
			case ERROR_INSUFFICIENT_BUFFER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INSUFFICIENT_BUFFER"); break;
			case ERROR_INVALID_FLAGS:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_FLAGS"); break;
			case ERROR_INVALID_PARAMETER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_PARAMETER"); break;
			default:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + to_string(ec) + ')'); break;
				//throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + std::to_string(ec) + ')'); break;
			}
		}
    const std::size_t real_len = strlen(re.c_str());
    re.resize(real_len);
    re.shrink_to_fit();
    return re;
	}

std::string char_utf_16_to_shift_jis(const char* str) {
	//https://qiita.com/yumetodo/items/453d14eff41b805d8fc4
    static_assert(sizeof(wchar_t) == 2, "this function is windows only");
    const int len = ::WideCharToMultiByte(932/*CP_ACP*/, 0, (LPCWSTR)str, -1, nullptr, 0, nullptr, nullptr);
    std::string re(len * 2, '\0');
    if (!::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)str, -1, &re[0], len, nullptr, nullptr)) {
        const auto ec = ::GetLastError();
        switch (ec) {
			case ERROR_INSUFFICIENT_BUFFER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INSUFFICIENT_BUFFER"); break;
			case ERROR_INVALID_FLAGS:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_FLAGS"); break;
			case ERROR_INVALID_PARAMETER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_PARAMETER"); break;
			default:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + to_string(ec) + ')'); break;
				//throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + std::to_string(ec) + ')'); break;
			}
		}
    const std::size_t real_len = strlen(re.c_str());
    re.resize(real_len);
    re.shrink_to_fit();
    return re;
	}

std::string unicode_2_utf8 (uint32_t x) {
	// https://rosettacode.org/wiki/UTF-8_encode_and_decode#VBA
	uint32_t r;
	std::string y;
	if (x <= 0x0000007F) {
		y.resize(1);
		y[0] = x;
		}
	else if (x <= 0x000007FF) {
		y.resize(2);
		y[0] = 192 + x / 64;
		y[1] = 128 + x % 64;
		}
	else if (x <= 0x00007FFF) {
		y.resize(3);
		y[2] = 128 + x % 64;
		r = x / 64;
		y[1] = 128 + r % 64;
		y[0] = 224 + r / 64;
		}
	else if (x <= 0x0000FFFF) {
		y.resize(3);
		y[2] = 128 + x % 64;
		r = x / 64;
		y[1] = 128 + r % 64;
		y[0] = 224 + r / 64;
		}
	else if (x <= 0x0000FFFF) {
		y.resize(3);
		y[2] = 128 + x % 64;
		r = x / 64;
		y[1] = 128 + r % 64;
		y[0] = 224 + r / 64;
		}
	else if (x <= 0x0010FFFF) {
		y.resize(4);
		y[3] = 128 + x % 64;
		r = x / 64;
		y[2] = 128 + r % 64;
		r = r / 64;
		y[1] = 128 + r % 64;
		y[0] = 240 + r / 64;
		}
	return y;
	}

std::string unicode_to_utf8 (std::wstring str) {
    std::string utf8str = "";
    if (str.length() > 0) {
        utf8str.reserve(str.length() * 3);
        for (unsigned int i = 0; i < str.length(); i++) {
            utf8str.append(unicode_2_utf8(str[i]));
            }
        }
    return utf8str;
    }

std::wstring utf8_2_unicode (std::string &str) {
	std::wstring w;
	uint8_t byte;
	uint32_t uni;

	unsigned long i = 0;
	while (i < str.size()) {
		byte = str[i];
		if (byte <= 0x7F) {
			w += str[i];
			}
		else if (byte <= 0xDF) {
			uni = (((str[i] & 0x1F) << 6) & ((str[i + 1] & 0x3F)));
			w += uni;
			i++;
			}
		else if (byte <= 0xEF) {
			uni = (((str[i] & 0x0F) << 12) | ((str[i + 1] & 0x3F) << 6)  |  ((str[i + 2] & 0x3F) )  );
			w += uni;
			i+=2;
			}
		else if (byte <= 0xF7) {
			uni = (((str[i] & 0x07) << 18) | ((str[i + 1] & 0x3F) << 12)  |  ((str[i + 2] & 0x3F) << 6)    |  ((str[i + 3] & 0x3F) )  );
			w += uni;
			i+=3;
			}
		i++;
		}
	return w;
	}
