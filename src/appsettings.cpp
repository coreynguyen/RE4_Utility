#include "appsettings.h"

appsettings* app;

ini_names::ini_names () {
	esl_path      = "ESL_DIR";
	esl_path_desc = "Enemy Spawn List Path";

	esl           = "ESL";
	esl_desc      = "Enemy Spawn List";
	}

appsettings::appsettings() {

	degree_to_radian = 0.017453292519943295769236907684886127134428718885417f;
	radian_to_degree = 57.295779513082320876798154814105170332405472466564f;
	meters_to_milli = 1000.0f;
	milli_to_meters = 0.001f;
	centi_to_milli = 10.0f;
	milli_to_centi = 0.1f;
	eslrot_to_degree = 0.010986332551700724487745603456244676035f;
	degree_to_eslrot = 0.00019174767574620779644429946175175338444f;
	bio_path = L"";

	read_settings();
	std::wcout << bio_path << std::endl;

	}

appsettings::~appsettings() {
	//dtor

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

void appsettings::save_settings () {

	if (bio_path.length() > 0) {
		// try to read settings
		ini->clear();
		ini->header("App Settings", "SETTINGS");
		ini->newline();
		ini->wstring("bio4_path", bio_path);
		ini->log(getFilenamePathW(getexepathW()) + L"settings.ini");

		}

	}

void appsettings::read_settings () {

	ini->open(getFilenamePathW(getexepathW()) + L"settings.ini");
	bio_path = ini->get_wstring("SETTINGS", "bio4_path");
	ini->clear();

	if (bio_path.length() == 0) {
		bio_path = getBio4InstallPathW();
		if (bio_path.length() > 0) {
			save_settings();
			}
		}


	}



