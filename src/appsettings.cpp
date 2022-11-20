#include "appsettings.h"

appsettings* app = nullptr;

ini_names::ini_names () {
	esl_path      = "ESL_DIR";
	esl_path_desc = "Enemy Spawn List Path";

	esl           = "ESL";
	esl_desc      = "Enemy Spawn List";
	}

appsettings::appsettings() {
    save_on_exit = false;

	degree_to_radian = 0.017453292519943295769236907684886127134428718885417f;
	radian_to_degree = 57.295779513082320876798154814105170332405472466564f;
	meters_to_milli = 1000.0f;
	milli_to_meters = 0.001f;
	centi_to_milli = 10.0f;
	milli_to_centi = 0.1f;
	eslrot_to_degree = 0.010986332551700724487745603456244676035f;
	degree_to_eslrot = 0.00019174767574620779644429946175175338444f;
	bio_path = L"";
	useDarkTheme = false;

	read_settings();
	std::wcout << bio_path << std::endl;

	}

appsettings::~appsettings() {
	if (save_on_exit) {
        save_settings();
        }

	}

std::wstring appsettings::steamInstallPathW () {

	// https://forums.cgsociety.org/t/get-system-information/1376115/2
	// https://stackoverflow.com/a/34091380

	std::wstring steamPath = L"";
	wreg::read_string(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Valve\\Steam", L"InstallPath", steamPath); // 32bit
	if (steamPath == L"") {
		wreg::read_string(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Wow6432Node\\Valve\\Steam", L"InstallPath", steamPath); // 64 bit
		}

	return steamPath;
	}

std::wstring appsettings::getBio4InstallPathW () {
	std::wstring exepath = L"";
	std::wstring steamPath = steamInstallPathW();
	std::string path = "";
	if (steamPath == L"") {return L"";}
	bytestream f;
	if (f.openFileW(steamPath + L"\\steamapps\\libraryfolders.vdf")) {
		std::string line = "";
		std::string temp;
		unsigned int index;
		while (!f.eos()) {
			line = f.readline();
			index = line.find("\"path\"");
			if (index != std::string::npos) {
				temp = line.substr(index + 6);
				index = temp.find("\"");
				temp = temp.substr(index + 1);
				index = temp.find_last_of("\"");
				temp = temp.substr(0, index);

				}
			else if (line.find("\"254700\"") != std::string::npos) {
				path = ReplaceAll(temp, "\\\\", "\\");;
				break;
				}
			}
		f.close();
		}



	if (path == "") {return L"";}
	steamPath = utf8_2_unicode(path);
	if (f.openFileW(steamPath + L"\\steamapps\\appmanifest_254700.acf")) {

		unsigned int index;
		std::string line = "";
		while (!f.eos()) {
			line = f.readline();
			index = line.find("\"installdir\"");
			if (index != std::string::npos) {
				line = line.substr(index + 12);
				index = line.find("\"");
				line = line.substr(index + 1);
				index = line.find_last_of("\"");
				line = line.substr(0, index);
				exepath = steamPath + L"\\steamapps\\common\\" + utf8_2_unicode(line) + L"\\";
				break;
				}
			}


		f.close();
		}




	return exepath;

	}

bool appsettings::is_light_theme() {
    // based on https://stackoverflow.com/questions/51334674/how-to-detect-windows-10-light-dark-mode-in-win32-application

    // The value is expected to be a REG_DWORD, which is a signed 32-bit little-endian
    auto buffer = std::vector<char>(4);
    auto cbData = static_cast<DWORD>(buffer.size() * sizeof(char));
    auto res = RegGetValueW(
        HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme",
        RRF_RT_REG_DWORD, // expected value type
        nullptr,
        buffer.data(),
        &cbData
        );

    if (res != ERROR_SUCCESS) {
        throw std::runtime_error("Error: error_code=" + std::to_string(res));
        }

    // convert bytes written to our buffer to an int, assuming little-endian
    auto i = int(buffer[3] << 24 | buffer[2] << 16 | buffer[1] << 8 | buffer[0]);

    return i == 1;
    }

std::wstring appsettings::getBio4Path () {return bio_path;}
bool appsettings::getDarkTheme () {return useDarkTheme;}

void appsettings::setBio4Path (std::wstring newpath) {
    if (newpath != L"" && bio_path != newpath) {
        bio_path = newpath;
        save_on_exit = true;
        }
    }

void appsettings::setDarkTheme (bool enable_dark_mode) {
    if (enable_dark_mode != useDarkTheme) {
        useDarkTheme = enable_dark_mode;
        save_on_exit = true;
        }
    }

void appsettings::save_settings () {

	if (bio_path.length() > 0) {

		// clear string buffer
		ini->clear();

		// start new string buffer
		ini->header("App Settings", "SETTINGS");
		ini->newline();

		// save settings to buffer
		ini->wstring("bio4_path", bio_path);
		ini->boolean("dark_theme", useDarkTheme);

        // try to save buffer to file
        ini->newline();
		ini->log(getFilenamePathW(getexepathW()) + L"settings.ini");
		}

	}

void appsettings::read_settings () {

    // Open INI
	if (!ini->open(getFilenamePathW(getexepathW()) + L"settings.ini")) {

        bio_path = steamInstallPathW();
        useDarkTheme = !is_light_theme();
        save_settings();

        return;
        }

    // save state to write a new ini
    save_on_exit = false;

    // Variable Check
    std::string chk;

    // Read Bio4 Directory
    chk = ini->get_string("SETTINGS", "bio4_path");
    if (chk.length() > 0) {bio_path = ini->get_wstring("SETTINGS", "bio4_path");}
    else {bio_path = steamInstallPathW(); save_on_exit = true;}

    // Read Dark Theme
    chk = ini->get_string("SETTINGS", "dark_theme");
    if (chk.length() > 0) {useDarkTheme = ini->get_boolean("SETTINGS", "dark_theme");}
    else {useDarkTheme = !is_light_theme(); save_on_exit = true;}
    std::cout << "useDarkTheme: \t" << useDarkTheme << std::endl;

    // Close Ini
    ini->clear();

    // Save new INI if state is true
    if (save_on_exit) {
        save_settings();
        save_on_exit = false;
        }
	}



