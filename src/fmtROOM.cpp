#include "fmtROOM.h"


fmtROOMINFO_Waypoint::fmtROOMINFO_Waypoint (uint16_t r, float x, float y, float z, float t, std::string n, std::string a, std::string c) {
	flag = 0;
	room = r;
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	angle = t;
	name_addr = 0;
	artist_addr = 0;
	coder_addr = 0;
	name = n;
	artist = a;
	coder = c;
	}

void fmtROOMINFO_Waypoint::read (bytestream &f) {
	flag = f.readUshort();
	room = f.readUshort();
	pos[0] = f.readfloat();
	pos[1] = f.readfloat();
	pos[2] = f.readfloat();
	angle = f.readfloat();
	name_addr = f.readUlong();
	artist_addr = f.readUlong();
	coder_addr = f.readUlong();
	f.seek(name_addr);
	name = f.readstring();
	f.seek(artist_addr);
	artist = f.readstring();
	f.seek(coder_addr);
	coder = f.readstring();
	}

void fmtROOMINFO_Waypoint::write (bytestream &s) {
	s.writeshort(flag);
	s.writeshort(room);
	s.writefloat(pos[0]);
	s.writefloat(pos[1]);
	s.writefloat(pos[2]);
	s.writefloat(angle);
	s.writelong(name_addr);
	s.writelong(artist_addr);
	s.writelong(coder_addr);
	}


fmtROOMINFO_Room::fmtROOMINFO_Room () {
	waypoint_count = 0;
	waypoint.clear();
	}

void fmtROOMINFO_Room::read (bytestream &f) {
	waypoint_count = f.readUlong();

	if (waypoint_count > 0) {
		waypoint = std::vector<fmtROOMINFO_Waypoint>(waypoint_count);
		size_t p = f.tell();
		for (unsigned int i = 0; i < waypoint_count; i++) {
			f.seek(p + (i * 0x20));
			waypoint[i].read(f);
			}
		f.seek(p + (waypoint_count * 0x20));
		}
	}

void fmtROOMINFO_Room::write (bytestream &s) {
	s.writelong(waypoint_count = waypoint.size());
	for (unsigned int i = 0; i < waypoint_count; i++) {
		waypoint[i].write(s);
		}
	}

size_t fmtROOMINFO_Room::size () {
	size_t nsize = waypoint.size() * 32;
	if (nsize > 0) {nsize += 4;}
	return nsize;
	}


fmtROOMINFO::fmtROOMINFO () {
	count = 0;
	addrs.clear();
	room = std::vector<fmtROOMINFO_Room>(7);

	room.at(0).waypoint = std::vector<fmtROOMINFO_Waypoint> (11); // Stage 0
	room.at(0).waypoint.at( 0) = fmtROOMINFO_Waypoint(0x0002, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "ATARI TEST ROOM",               "NOBODY",    "NISHIMURA"); // v49
	room.at(0).waypoint.at( 1) = fmtROOMINFO_Waypoint(0x0003, -170.0000f, 3000.0000f, 7000.0000f, -2.83000f, "test",                          "A-ROW",     "");
	room.at(0).waypoint.at( 2) = fmtROOMINFO_Waypoint(0x0004, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "DON BEYA",                      "A-ROW",     "DON SAN");
	room.at(0).waypoint.at( 3) = fmtROOMINFO_Waypoint(0x0015, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "EFFECT TEST",                   "",          "");
	room.at(0).waypoint.at( 4) = fmtROOMINFO_Waypoint(0x0020, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "EFF TEST0{R004}",               "",          "");
	room.at(0).waypoint.at( 5) = fmtROOMINFO_Waypoint(0x0021, -200.0000f, 4000.0000f, -1355.000f, 3.000000f, "EFF TEST1{R208}",               "",          "");
	room.at(0).waypoint.at( 6) = fmtROOMINFO_Waypoint(0x0022, -12.00000f, 4028.0000f, 3180.0000f, 3.000000f, "EFF TEST2{R228}",               "",          "");
	room.at(0).waypoint.at( 7) = fmtROOMINFO_Waypoint(0x0023, -1148.000f, -16159.00f, 16018.000f, 2.325000f, "EFF TEST3{R229}",               "",          "");
	room.at(0).waypoint.at( 8) = fmtROOMINFO_Waypoint(0x0024, 28450.000f, -16798.00f, -40000.00f, -2.49000f, "EFF TEST4{R300}",               "",          "");
	room.at(0).waypoint.at( 9) = fmtROOMINFO_Waypoint(0x0025, -23218.00f, 0.0000000f, -21894.00f, 1.550000f, "EFF TEST5{R303}",               "",          "");
	room.at(0).waypoint.at(10) = fmtROOMINFO_Waypoint(0x0026, 12329.000f, -957.0000f, -5782.000f, 0.000000f, "EFF TEST5{R329}",               "",          "");

	room.at(1).waypoint = std::vector<fmtROOMINFO_Waypoint> (52); // Stage 1
	room.at(1).waypoint.at( 0) = fmtROOMINFO_Waypoint(0x0100, -109483.0f, -618.0000f, 916.00000f, 2.000000f, "MORI",                          "YANO",      "");
	room.at(1).waypoint.at( 1) = fmtROOMINFO_Waypoint(0x0100, 43363.000f, 152.00000f, -7129.000f, 1.680000f, "MORI - BRIDGE",                 "YANO",      "");
	room.at(1).waypoint.at( 2) = fmtROOMINFO_Waypoint(0x0101, -51510.00f, 165.00000f, 21834.000f, 2.330000f, "MURA",                          "HORI",      "");
	room.at(1).waypoint.at( 3) = fmtROOMINFO_Waypoint(0x0101, 2684.0000f, 0.0000000f, -8473.000f, -1.20000f, "MURA - in HOUSE",               "HORI",      "SAKATA");
	room.at(1).waypoint.at( 4) = fmtROOMINFO_Waypoint(0x0102, -18863.00f, 0.0000000f, -18409.00f, 0.000000f, "TIKADOU",                       "HORI",      "");
	room.at(1).waypoint.at( 5) = fmtROOMINFO_Waypoint(0x0103, -47730.00f, 0.0000000f, 7154.0000f, 1.900000f, "FARM",                          "YASUDA",    "");
	room.at(1).waypoint.at( 6) = fmtROOMINFO_Waypoint(0x0103, -41605.00f, 0.0000000f, -7814.000f, -1.61000f, "",                              "",          "");
	room.at(1).waypoint.at( 7) = fmtROOMINFO_Waypoint(0x0104, -3444.000f, 0.0000000f, 12333.000f, -1.58000f, "KANKIN",                        "YANO",      "");
	room.at(1).waypoint.at( 8) = fmtROOMINFO_Waypoint(0x0104, 26840.000f, -70.00000f, -27201.00f, 2.350000f, "DOOR",                          "YANO",      "");
	room.at(1).waypoint.at( 9) = fmtROOMINFO_Waypoint(0x0105, -33790.00f, 0.0000000f, -1578.000f, 2.000000f, "SONTYOU HOUSE",                 "HORI",      "");
	room.at(1).waypoint.at(10) = fmtROOMINFO_Waypoint(0x0105, 18291.000f, 3160.0000f, 3365.0000f, -1.50000f, "HOUSE - FRONT",                 "HORI",      "");
	room.at(1).waypoint.at(11) = fmtROOMINFO_Waypoint(0x0105, 13530.000f, 6343.0000f, -1618.000f, 0.000000f, "HOUSE - MARK",                  "",          "YAMANOUCHI");
	room.at(1).waypoint.at(12) = fmtROOMINFO_Waypoint(0x0106, 11220.000f, -895.0000f, -104.0000f, 0.760000f, "HAISON",                        "NAGANO",    "");
	room.at(1).waypoint.at(13) = fmtROOMINFO_Waypoint(0x0106, 110241.00f, -8344.000f, -24593.00f, 1.830000f, "HAISON - OKU",                  "NAGANO",    "");
	room.at(1).waypoint.at(14) = fmtROOMINFO_Waypoint(0x0107, 30810.000f, -14.00000f, -29142.00f, 2.425000f, "KANKIN_2",                      "YANO",      "");
	room.at(1).waypoint.at(15) = fmtROOMINFO_Waypoint(0x0107, 73285.000f, 188.00000f, -43113.00f, 2.710000f, "KANKIN_2 - 2",                  "YANO",      "");
	room.at(1).waypoint.at(16) = fmtROOMINFO_Waypoint(0x0108, -43898.00f, -36.00000f, -14735.00f, 2.010000f, "TOMB",                          "MINAMI",    "");
	room.at(1).waypoint.at(17) = fmtROOMINFO_Waypoint(0x0108, 21738.000f, 10776.000f, -13370.00f, 1.630000f, "TOMB - GAKE",                   "MINAMI",    "");
	room.at(1).waypoint.at(18) = fmtROOMINFO_Waypoint(0x0109, 96344.000f, 2678.0000f, 12750.000f, 1.000000f, "COLOSSEUM",                     "MINAMI",    "");
	room.at(1).waypoint.at(19) = fmtROOMINFO_Waypoint(0x010A, -58592.00f, 7345.0000f, 69840.000f, 1.450000f, "NUMA",                          "KOUYAMA",   "");
	room.at(1).waypoint.at(20) = fmtROOMINFO_Waypoint(0x010A, 13192.000f, -7500.000f, 84830.000f, 0.800000f, "NUMA - BRIDGE",                 "KOUYAMA",   "");
	room.at(1).waypoint.at(21) = fmtROOMINFO_Waypoint(0x010B, -71350.00f, 2926.0000f, -23802.00f, 1.890000f, "MIZUUMI",                       "KOUYAMA",   "");
	room.at(1).waypoint.at(22) = fmtROOMINFO_Waypoint(0x010B, -59993.00f, -487.0000f, 21450.000f, 1.200000f, "MIZUUMI - BOAT",                "KOUYAMA",   "");
	room.at(1).waypoint.at(23) = fmtROOMINFO_Waypoint(0x010C, -1000.000f, 0.0000000f, -1000.000f, 0.000000f, "TAKI{night}",                   "YANO",      "");
	room.at(1).waypoint.at(24) = fmtROOMINFO_Waypoint(0x010C, 93385.000f, -15002.00f, 39713.000f, -2.00000f, "TAKI - SITA{night}",            "YANO",      "");
	room.at(1).waypoint.at(25) = fmtROOMINFO_Waypoint(0x010D, -381.0000f, -1589.000f, 365.00000f, 3.000000f, "BUKI-SYOUNIN{night}",           "YANO",      "");
	room.at(1).waypoint.at(26) = fmtROOMINFO_Waypoint(0x010E, 37550.000f, -14526.00f, 38538.000f, -0.15700f, "SUIRO{night}",                  "YANO",      "");
	room.at(1).waypoint.at(27) = fmtROOMINFO_Waypoint(0x010E, -41357.00f, -5745.000f, 11584.000f, -0.12300f, "SUIRO-BUKI SYOUNIN",            "",          "");
	room.at(1).waypoint.at(28) = fmtROOMINFO_Waypoint(0x010F, -25153.00f, 4000.0000f, 16554.000f, 1.000000f, "GONDOLA{night}",                "HORI",      "");
	room.at(1).waypoint.at(29) = fmtROOMINFO_Waypoint(0x010F, 21985.000f, 10224.000f, -35920.00f, 1.423000f, "gondola-start",                 "HORI",      "hagiyama");
	room.at(1).waypoint.at(30) = fmtROOMINFO_Waypoint(0x010F, 25490.000f, -23191.00f, -144517.0f, -2.71900f, "gondola-bunki",                 "hori",      "hagiyama");
	room.at(1).waypoint.at(31) = fmtROOMINFO_Waypoint(0x010F, 22178.000f, -18246.00f, -151145.0f, 2.959000f, "gondola-goal",                  "hori",      "hagiyama");
	room.at(1).waypoint.at(32) = fmtROOMINFO_Waypoint(0x0111, 19378.000f, 977.00000f, 2826.0000f, 180.0000f, "MURA{night}",                   "HORI",      "");
	room.at(1).waypoint.at(33) = fmtROOMINFO_Waypoint(0x0112, -4843.000f, -8474.000f, 52524.000f, -2.00000f, "TIKADOU{night}",                "HORI",      "");
	room.at(1).waypoint.at(34) = fmtROOMINFO_Waypoint(0x0113, -43900.00f, 0.0000000f, 5250.0000f, 2.300000f, "FARM {night}",                  "YASUDA",    "");
	room.at(1).waypoint.at(35) = fmtROOMINFO_Waypoint(0x0117, 150.00000f, -1038.000f, 6152.0000f, 3.140000f, "CHURCH{night}",                 "YANO",      "");
	room.at(1).waypoint.at(36) = fmtROOMINFO_Waypoint(0x0117, -3342.000f, 4007.0000f, 6293.0000f, 3.000000f, "CHURCH - SWITCH{night}",        "YANO",      "");
	room.at(1).waypoint.at(37) = fmtROOMINFO_Waypoint(0x0118, 94000.000f, 2314.0000f, 10418.000f, -2.00000f, "TOMB{night}",                   "MINAMI",    "");
	room.at(1).waypoint.at(38) = fmtROOMINFO_Waypoint(0x0118, 23986.000f, 11775.000f, -26602.00f, -1.00000f, "TOMB - kyokai{night}",          "MINAMI",    "");
	room.at(1).waypoint.at(39) = fmtROOMINFO_Waypoint(0x0119, 131876.00f, 2298.0000f, 11466.000f, -2.00000f, "COLOSSEUM{night}",              "MINAMI",    "");
	room.at(1).waypoint.at(40) = fmtROOMINFO_Waypoint(0x011A, 102790.00f, -4700.000f, 57160.000f, -1.44000f, "NUMA{night}",                   "KOUYAMA",   "");
	room.at(1).waypoint.at(41) = fmtROOMINFO_Waypoint(0x011A, 13192.000f, -7500.000f, 84830.000f, 0.800000f, "NUMA - BRIDGE{night}",          "KOUYAMA",   "");
	room.at(1).waypoint.at(42) = fmtROOMINFO_Waypoint(0x011B, 126060.00f, -175.0000f, 175185.00f, 1.860000f, "MIZUUMI {night}",               "KOUYAMA",   "");
	room.at(1).waypoint.at(43) = fmtROOMINFO_Waypoint(0x011B, -59993.00f, -487.0000f, 21450.000f, 1.200000f, "MIZUUMI - BOAT {night}",        "KOUYAMA",   "");
	room.at(1).waypoint.at(44) = fmtROOMINFO_Waypoint(0x011C, 51183.000f, 0.0000000f, -71789.00f, 1.220000f, "ROUZYOU{night}",                "ISHII",     "");
	room.at(1).waypoint.at(45) = fmtROOMINFO_Waypoint(0x011D, -17304.00f, 0.0000000f, -12282.00f, 2.000000f, "SEKISYO{night}",                "YANO",      "");
	room.at(1).waypoint.at(46) = fmtROOMINFO_Waypoint(0x011D, 12155.000f, 3200.0000f, -4395.000f, -3.00000f, "SEKISYO_2{night}",              "YANO",      "");
	room.at(1).waypoint.at(47) = fmtROOMINFO_Waypoint(0x011E, 693.00000f, -26.00000f, 995.00000f, 0.000000f, "HOKORA{night}",                 "YANO",      "");
	room.at(1).waypoint.at(48) = fmtROOMINFO_Waypoint(0x011E, 29056.000f, -25.00000f, 37623.000f, -1.71000f, "",                              "",          "");
	room.at(1).waypoint.at(49) = fmtROOMINFO_Waypoint(0x011F, 12740.000f, -1018.000f, -9795.000f, 1.850000f, "SONTYOU-BOSS{night}",           "HORI",      "");
	room.at(1).waypoint.at(50) = fmtROOMINFO_Waypoint(0x011F, 31200.000f, -8000.000f, -37500.00f, 2.680000f, "sontyousen",                    "hori",      "");
	room.at(1).waypoint.at(51) = fmtROOMINFO_Waypoint(0x0120, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "OPENING",                       "YANO",      "");

	room.at(2).waypoint = std::vector<fmtROOMINFO_Waypoint> (83); // Stage 2
	room.at(2).waypoint.at( 0) = fmtROOMINFO_Waypoint(0x0200, 0.0000000f, 0.0000000f, 0.0000000f, 1.830000f, "WAY TO THE CASTEL",             "SHIMADA",   "");
	room.at(2).waypoint.at( 1) = fmtROOMINFO_Waypoint(0x0200, 82200.000f, 10120.000f, -41822.00f, 3.000000f, "WAY TO THE CASTEL - GATE",      "SHIMADA",   "");
	room.at(2).waypoint.at( 2) = fmtROOMINFO_Waypoint(0x0201, 0.0000000f, 0.0000000f, 0.0000000f, 3.000000f, "HALL",                          "Arow",      "");
	room.at(2).waypoint.at( 3) = fmtROOMINFO_Waypoint(0x0201, 40677.000f, 2000.0000f, -30040.00f, 1.620000f, "HALL-KEY",                      "Arow",      "");
	room.at(2).waypoint.at( 4) = fmtROOMINFO_Waypoint(0x0201, 34784.000f, 2000.0000f, -30248.00f, 1.306000f, "",                              "",          "");
	room.at(2).waypoint.at( 5) = fmtROOMINFO_Waypoint(0x0202, -5644.000f, -9.000000f, -295.0000f, 2.000000f, "BATTLE AREA",                   "NAGANO",    "");
	room.at(2).waypoint.at( 6) = fmtROOMINFO_Waypoint(0x0202, 21631.000f, 10595.000f, -23161.00f, -1.13000f, "BATTLE AREA2",                  "",          "");
	room.at(2).waypoint.at( 7) = fmtROOMINFO_Waypoint(0x0203, -11980.00f, 4223.0000f, -10564.00f, -1.22000f, "CASTLE GATE",                   "YASUDA",    "");
	room.at(2).waypoint.at( 8) = fmtROOMINFO_Waypoint(0x0203, -31578.00f, 4155.0000f, -11870.00f, -1.89000f, "CASTLE GATE 2",                 "",          "");
	room.at(2).waypoint.at( 9) = fmtROOMINFO_Waypoint(0x0204, -210.0000f, 0.0000000f, -1700.000f, 3.000000f, "MAIN ROUKA",                    "Arow",      "");
	room.at(2).waypoint.at(10) = fmtROOMINFO_Waypoint(0x0204, 10049.000f, 6000.0000f, -3156.000f, -1.64000f, "",                              "",          "");
	room.at(2).waypoint.at(11) = fmtROOMINFO_Waypoint(0x0205, -724.0000f, 4000.0000f, 648.00000f, 1.360000f, "PRISON AREA",                   "SHIMADA",   "");
	room.at(2).waypoint.at(12) = fmtROOMINFO_Waypoint(0x0205, 20800.000f, 3996.0000f, 67731.000f, 3.120000f, "PRISON AREA 2",                 "SHIMADA",   "");
	room.at(2).waypoint.at(13) = fmtROOMINFO_Waypoint(0x0205, 48500.000f, 1000.0000f, 46530.000f, -0.47000f, "PRISON AREA 3",                 "SHIMADA",   "");
	room.at(2).waypoint.at(14) = fmtROOMINFO_Waypoint(0x0206, 0.0000000f, 0.0000000f, -750.0000f, 3.000000f, "MAIN HALL",                     "Arow",      "");
	room.at(2).waypoint.at(15) = fmtROOMINFO_Waypoint(0x0206, -7539.000f, 8000.0000f, -4891.000f, 2.110000f, "",                              "",          "");
	room.at(2).waypoint.at(16) = fmtROOMINFO_Waypoint(0x0207, 725.00000f, 127.00000f, 725.00000f, 3.000000f, "HEISYA",                        "YASUDA",    "");
	room.at(2).waypoint.at(17) = fmtROOMINFO_Waypoint(0x0208, -200.0000f, 4000.0000f, -1355.000f, 3.000000f, "WATER HALL",                    "Arow",      "");
	room.at(2).waypoint.at(18) = fmtROOMINFO_Waypoint(0x0208, -400.0000f, 7000.0000f, -40550.00f, 3.000000f, "WATER HALL",                    "Arow",      "");
	room.at(2).waypoint.at(19) = fmtROOMINFO_Waypoint(0x0209, 230.00000f, 0.0000000f, -150.0000f, -1.60000f, "SALON_1",                       "SHIMADA",   "");
	room.at(2).waypoint.at(20) = fmtROOMINFO_Waypoint(0x0209, -55222.00f, 4000.0000f, 7500.0000f, -1.72000f, "SALON_2",                       "",          "");
	room.at(2).waypoint.at(21) = fmtROOMINFO_Waypoint(0x0209, -45225.00f, 4000.0000f, 10690.000f, -1.79000f, "SALON_3",                       "",          "");
	room.at(2).waypoint.at(22) = fmtROOMINFO_Waypoint(0x020A, -50.00000f, 0.0000000f, -360.0000f, 3.000000f, "ROUKA",                         "YASUDA",    "");
	room.at(2).waypoint.at(23) = fmtROOMINFO_Waypoint(0x020A, -30930.00f, 2000.0000f, -54170.00f, -3.08000f, "ROUKA 2",                       "YASUDA",    "");
	room.at(2).waypoint.at(24) = fmtROOMINFO_Waypoint(0x020A, 10850.000f, 0.0000000f, -30868.00f, -1.49000f, "ROUKA 3",                       "YASUDA",    "");
	room.at(2).waypoint.at(25) = fmtROOMINFO_Waypoint(0x020B, -1014.000f, 6046.0000f, -290.0000f, 3.117000f, "BED ROOM",                      "SHIMADA",   "");
	room.at(2).waypoint.at(26) = fmtROOMINFO_Waypoint(0x020C, 65.000000f, 3500.0000f, 340.00000f, -0.15000f, "GALLERY ROOM",                  "YASUDA",    "");
	room.at(2).waypoint.at(27) = fmtROOMINFO_Waypoint(0x020C, 27192.000f, 3500.0000f, 17054.000f, 1.750000f, "FIGHT CLUB",                    "YASUDA",    "");
	room.at(2).waypoint.at(28) = fmtROOMINFO_Waypoint(0x020D, -26850.00f, 0.0000000f, 744.00000f, 1.880000f, "SHITUZI AREA",                  "ISHII",     "");
	room.at(2).waypoint.at(29) = fmtROOMINFO_Waypoint(0x020D, 6567.0000f, -1000.000f, 14359.000f, -1.62000f, "SHITUZI AREA_2",                "",          "");
	room.at(2).waypoint.at(30) = fmtROOMINFO_Waypoint(0x020E, 15622.000f, 0.0000000f, 30357.000f, 1.600000f, "UN-USING AREA",                 "ISHII",     "");
	room.at(2).waypoint.at(31) = fmtROOMINFO_Waypoint(0x020E, 19531.000f, -2402.000f, -14952.00f, 2.960000f, "UN-USING AREA 2",               "ISHII",     "");
	room.at(2).waypoint.at(32) = fmtROOMINFO_Waypoint(0x020F, 41230.000f, 3500.0000f, 26265.000f, 1.570000f, "GALLERY ROOM_2",                "YASUDA",    "");
	room.at(2).waypoint.at(33) = fmtROOMINFO_Waypoint(0x0210, -250.0000f, 0.0000000f, -1000.000f, 3.000000f, "torokko",                       "Arow",      "");
	room.at(2).waypoint.at(34) = fmtROOMINFO_Waypoint(0x0210, -57065.00f, -2000.000f, 244000.00f, 1.400000f, "torokko",                       "Arow",      "");
	room.at(2).waypoint.at(35) = fmtROOMINFO_Waypoint(0x0211, 4503.0000f, 40.000000f, 20791.000f, 3.060000f, "Main Rouka",                    "NAGANO",    "");
	room.at(2).waypoint.at(36) = fmtROOMINFO_Waypoint(0x0212, 3902.0000f, 0.0000000f, 2083.0000f, -1.68000f, "BukiTenji",                     "NAGANO",    "");
	room.at(2).waypoint.at(37) = fmtROOMINFO_Waypoint(0x0212, -2291.000f, 65.000000f, -6391.000f, 0.000000f, "",                              "",          "");
	room.at(2).waypoint.at(38) = fmtROOMINFO_Waypoint(0x0212, -14837.00f, 0.0000000f, -7195.000f, 0.000000f, "",                              "",          "");
	room.at(2).waypoint.at(39) = fmtROOMINFO_Waypoint(0x0213, 25.000000f, 1000.0000f, -445.0000f, 3.000000f, "DANCE HOLE_1F",                 "Arow",      "");
	room.at(2).waypoint.at(40) = fmtROOMINFO_Waypoint(0x0213, 21000.000f, 7000.0000f, -53500.00f, 0.000000f, "DANCE HOLE_2F",                 "",          "");
	room.at(2).waypoint.at(41) = fmtROOMINFO_Waypoint(0x0214, 7457.0000f, 1521.0000f, 38472.000f, -1.59000f, "CLOCKTOWER {outside}",          "NAGANO",    "");
	room.at(2).waypoint.at(42) = fmtROOMINFO_Waypoint(0x0214, 284.00000f, 52.000000f, -22466.00f, 1.370000f, "CLOCKTOWER {outside}_2",        "",          "");
	room.at(2).waypoint.at(43) = fmtROOMINFO_Waypoint(0x0215, 26880.000f, 2960.0000f, 84.000000f, 1.350000f, "LOAD ROOM",                     "ISHII",     "");
	room.at(2).waypoint.at(44) = fmtROOMINFO_Waypoint(0x0215, 26880.000f, 2960.0000f, 84.000000f, 1.350000f, "",                              "",          "");
	room.at(2).waypoint.at(45) = fmtROOMINFO_Waypoint(0x0216, 290.00000f, 0.0000000f, -250.0000f, 1.440000f, "YOROI",                         "YOKOYAMA",  "");
	room.at(2).waypoint.at(46) = fmtROOMINFO_Waypoint(0x0216, 20300.000f, 100.00000f, -20400.00f, 1.320000f, "YOROI",                         "",          "");
	room.at(2).waypoint.at(47) = fmtROOMINFO_Waypoint(0x0217, 4871.0000f, 8054.0000f, -1779.000f, -1.28000f, "CLOCKTOWER {inside}",           "NAGANO",    "");
	room.at(2).waypoint.at(48) = fmtROOMINFO_Waypoint(0x0217, -185.0000f, 19194.000f, 4433.0000f, -0.87000f, "CLOCKTOWER {inside}_2",         "",          "");
	room.at(2).waypoint.at(49) = fmtROOMINFO_Waypoint(0x0218, -30391.00f, -2105.000f, -172.0000f, 0.900000f, "MONBAN",                        "ISHII",     "");
	room.at(2).waypoint.at(50) = fmtROOMINFO_Waypoint(0x0219, -160.0000f, 0.0000000f, 740.00000f, 3.020000f, "torokko-2",                     "Arow",      "");
	room.at(2).waypoint.at(51) = fmtROOMINFO_Waypoint(0x0219, -78700.00f, 0.0000000f, -351315.0f, 3.020000f, "torokko-2",                     "Arow",      "");
	room.at(2).waypoint.at(52) = fmtROOMINFO_Waypoint(0x021A, -25050.00f, 4954.0000f, 74267.000f, 3.102000f, "Dungeon - 1",                   "HORI",      "");
	room.at(2).waypoint.at(53) = fmtROOMINFO_Waypoint(0x021A, -31770.00f, -1573.000f, 34920.000f, 3.064000f, "",                              "",          "");
	room.at(2).waypoint.at(54) = fmtROOMINFO_Waypoint(0x021A, -32460.00f, -1985.000f, -23450.00f, 3.102000f, "",                              "",          "");
	room.at(2).waypoint.at(55) = fmtROOMINFO_Waypoint(0x021B, -232530.0f, -4282.000f, -43912.00f, 1.549000f, "Dungeon - 2",                   "HORI",      "");
	room.at(2).waypoint.at(56) = fmtROOMINFO_Waypoint(0x021B, -201000.0f, -52360.00f, 97930.000f, 0.000000f, "",                              "",          "");
	room.at(2).waypoint.at(57) = fmtROOMINFO_Waypoint(0x021D, -27714.00f, -4000.000f, -39640.00f, 1.000000f, "NARAKU & TOMB",                 "MINAMI",    "");
	room.at(2).waypoint.at(58) = fmtROOMINFO_Waypoint(0x021D, -15235.00f, 8206.0000f, 31995.000f, 0.000000f, "NARAKU & TOMB_2",               "",          "");
	room.at(2).waypoint.at(59) = fmtROOMINFO_Waypoint(0x021D, 9103.0000f, 14655.000f, 90969.000f, 1.640000f, "NARAKU & TOMB_3",               "",          "");
	room.at(2).waypoint.at(60) = fmtROOMINFO_Waypoint(0x0220, 1153.0000f, 1162.0000f, 8267.0000f, -2.00000f, "SAVE_heya",                     "YOKOYAMA",  "");
	room.at(2).waypoint.at(61) = fmtROOMINFO_Waypoint(0x0221, -44053.00f, 724.00000f, 3592.0000f, 1.632000f, "YOUSUIRO-BOSS",                 "MINAMI",    "");
	room.at(2).waypoint.at(62) = fmtROOMINFO_Waypoint(0x0222, 1338.0000f, 54.000000f, -4345.000f, -1.53400f, "BLAZING INFERNO",               "MINAMI",    "");
	room.at(2).waypoint.at(63) = fmtROOMINFO_Waypoint(0x0223, -29901.00f, 4500.0000f, 28415.000f, -2.00000f, "SAIKUTU",                       "YOKOYAMA",  "");
	room.at(2).waypoint.at(64) = fmtROOMINFO_Waypoint(0x0223, -17726.00f, 27.000000f, -27515.00f, 0.400000f, "SAIKUTU_2",                     "YOKOYAMA",  "");
	room.at(2).waypoint.at(65) = fmtROOMINFO_Waypoint(0x0224, -19943.00f, 0.0000000f, -2305.000f, 1.450000f, "YOUKOU-RO",                     "YOKOYAMA",  "");
	room.at(2).waypoint.at(66) = fmtROOMINFO_Waypoint(0x0225, -32000.00f, 1900.0000f, 30.000000f, 2.000000f, "forest",                        "Arow",      "");
	room.at(2).waypoint.at(67) = fmtROOMINFO_Waypoint(0x0225, 72900.000f, 1500.0000f, -6265.000f, 2.520000f, "",                              "",          "");
	room.at(2).waypoint.at(68) = fmtROOMINFO_Waypoint(0x0226, -3415.000f, 5000.0000f, 18565.000f, 2.960000f, "daiseidou",                     "Arow",      "");
	room.at(2).waypoint.at(69) = fmtROOMINFO_Waypoint(0x0226, -6950.000f, 1000.0000f, -16350.00f, -1.93000f, "daiseidou",                     "Arow",      "");
	room.at(2).waypoint.at(70) = fmtROOMINFO_Waypoint(0x0227, 10750.000f, 0.0000000f, 725.00000f, -1.75000f, "SYMBOL TOWER",                  "KOUYAMA",   "");
	room.at(2).waypoint.at(71) = fmtROOMINFO_Waypoint(0x0227, 18041.000f, 28625.000f, -5436.000f, 1.190000f, "SYMBOL TOWER_ELV",              "",          "");
	room.at(2).waypoint.at(72) = fmtROOMINFO_Waypoint(0x0227, 228.00000f, 13500.000f, 4818.0000f, 2.878000f, "",                              "",          "");
	room.at(2).waypoint.at(73) = fmtROOMINFO_Waypoint(0x0228, -12.00000f, 4028.0000f, 3180.0000f, 3.000000f, "SYMBOL TOWER - BOSS",           "KOUYAMA",   "");
	room.at(2).waypoint.at(74) = fmtROOMINFO_Waypoint(0x0229, -1148.000f, -16159.00f, 16018.000f, 2.325000f, "YOUSUIRO",                      "MINAMI",    "");
	room.at(2).waypoint.at(75) = fmtROOMINFO_Waypoint(0x0229, 18883.000f, -15000.00f, -61810.00f, 1.536000f, "",                              "",          "");
	room.at(2).waypoint.at(76) = fmtROOMINFO_Waypoint(0x022A, -160.0000f, 51500.000f, -18850.00f, 3.020000f, "SUIMON",                        "KOUYAMA",   "");
	room.at(2).waypoint.at(77) = fmtROOMINFO_Waypoint(0x022A, 7490.0000f, 26500.000f, -33515.00f, 2.460000f, "SUIMON2",                       "",          "");
	room.at(2).waypoint.at(78) = fmtROOMINFO_Waypoint(0x022A, 19340.000f, -8500.000f, -39230.00f, 1.500000f, "SUIMON3",                       "",          "");
	room.at(2).waypoint.at(79) = fmtROOMINFO_Waypoint(0x022B, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "318&30F",                       "YANO",      "");
	room.at(2).waypoint.at(80) = fmtROOMINFO_Waypoint(0x022C, 0.0000000f, 0.0000000f, 0.0000000f, 3.000000f, "SHOOTING GAME A",               "A-Row",     "");
	room.at(2).waypoint.at(81) = fmtROOMINFO_Waypoint(0x022C, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "SHOOTING GAME B",               "",          "");
	room.at(2).waypoint.at(82) = fmtROOMINFO_Waypoint(0x022C, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "SHOOTING GAME C",               "",          "");

	room.at(3).waypoint = std::vector<fmtROOMINFO_Waypoint> (78); // Stage 3
	room.at(3).waypoint.at( 0) = fmtROOMINFO_Waypoint(0x0300, 28450.000f, -16798.00f, -40000.00f, -2.49000f, "SENNYUU_1",                     "KATAYAMA",  "");
	room.at(3).waypoint.at( 1) = fmtROOMINFO_Waypoint(0x0300, -3356.000f, -12000.00f, -22350.00f, -0.32000f, "SENNYUU2 Before Rock",          "KATAYAMA",  "");
	room.at(3).waypoint.at( 2) = fmtROOMINFO_Waypoint(0x0300, -18343.00f, -18000.00f, 832.00000f, -2.92000f, "gate",                          "katayama",  "ueda");
	room.at(3).waypoint.at( 3) = fmtROOMINFO_Waypoint(0x0301, -8475.000f, -7000.000f, 8169.0000f, -1.94000f, "SENNYUU_2",                     "KATAYAMA",  "");
	room.at(3).waypoint.at( 4) = fmtROOMINFO_Waypoint(0x0301, 17814.000f, -1243.000f, -42488.00f, 1.545700f, "SENNYUU_2 continue point",      "KATAYAMA",  "");
	room.at(3).waypoint.at( 5) = fmtROOMINFO_Waypoint(0x0303, -23218.00f, 0.0000000f, -21894.00f, 1.550000f, "URA-KITCHEN",                   "KTAYAMA",   "");
	room.at(3).waypoint.at( 6) = fmtROOMINFO_Waypoint(0x0304, -17570.00f, 0.0000000f, 1542.0000f, 0.060000f, "monitor_room",                  "KATAYAMA",  "");
	room.at(3).waypoint.at( 7) = fmtROOMINFO_Waypoint(0x0305, 8079.0000f, 0.0000000f, 8505.0000f, -2.51000f, "DUST BOX",                      "KATAYAMA",  "");
	room.at(3).waypoint.at( 8) = fmtROOMINFO_Waypoint(0x0306, 5257.0000f, 1.0000000f, 2392.0000f, -3.12000f, "1F-2F KAIDAN",                  "KATAYAMA",  "");
	room.at(3).waypoint.at( 9) = fmtROOMINFO_Waypoint(0x0307, 1629.0000f, 0.0000000f, 4756.0000f, -1.80000f, "OPE ROOM",                      "KATAYAMA",  "");
	room.at(3).waypoint.at(10) = fmtROOMINFO_Waypoint(0x0307, -1492.000f, 0.0000000f, -1739.000f, 1.820000f, "",                              "",          "");
	room.at(3).waypoint.at(11) = fmtROOMINFO_Waypoint(0x0308, -3070.000f, 0.0000000f, 2680.0000f, 2.802000f, "FREEZER ROOM",                  "YOKOYAMA",  "");
	room.at(3).waypoint.at(12) = fmtROOMINFO_Waypoint(0x0309, -8010.000f, 0.0000000f, -7510.000f, 1.160000f, "LABORATORY",                    "NAGANO",    "");
	room.at(3).waypoint.at(13) = fmtROOMINFO_Waypoint(0x0309, -620.0000f, 0.0000000f, 13803.000f, 2.780000f, "Baiyou",                        "",          "");
	room.at(3).waypoint.at(14) = fmtROOMINFO_Waypoint(0x030A, 236.00000f, -3971.000f, 27394.000f, 1.470000f, "Tsuushin",                      "NAGANO",    "");
	room.at(3).waypoint.at(15) = fmtROOMINFO_Waypoint(0x030A, 37384.000f, 7741.0000f, 27321.000f, -1.82000f, "",                              "",          "");
	room.at(3).waypoint.at(16) = fmtROOMINFO_Waypoint(0x030B, -18633.00f, 1000.0000f, 3407.0000f, 3.130000f, "GomiShori",                     "NAGANO",    "");
	room.at(3).waypoint.at(17) = fmtROOMINFO_Waypoint(0x030B, 18547.000f, 50.000000f, 7228.0000f, -1.76000f, "",                              "",          "");
	room.at(3).waypoint.at(18) = fmtROOMINFO_Waypoint(0x030B, -11580.00f, 1000.0000f, -12830.00f, 0.000000f, "",                              "",          "");
	room.at(3).waypoint.at(19) = fmtROOMINFO_Waypoint(0x030C, 10384.000f, 0.0000000f, 7666.0000f, -3.04000f, "KANKIN",                        "KATAYAMA",  "");
	room.at(3).waypoint.at(20) = fmtROOMINFO_Waypoint(0x030D, -4830.000f, 0.0000000f, -18430.00f, -0.08000f, "UNDERGROUND_1",                 "ISHII",     "");
	room.at(3).waypoint.at(21) = fmtROOMINFO_Waypoint(0x030D, 9100.0000f, 0.0000000f, 24910.000f, 1.490000f, "",                              "",          "");
	room.at(3).waypoint.at(22) = fmtROOMINFO_Waypoint(0x030E, -13600.00f, 1743.0000f, -21981.00f, 3.030000f, "LAB_ROUKA",                     "NAGANO",    "");
	room.at(3).waypoint.at(23) = fmtROOMINFO_Waypoint(0x030E, -1247.000f, -2173.000f, 14540.000f, 2.880000f, "",                              "",          "");
	room.at(3).waypoint.at(24) = fmtROOMINFO_Waypoint(0x030F, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "BULL",                          "YANO",      "");
	room.at(3).waypoint.at(25) = fmtROOMINFO_Waypoint(0x030F, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "",                              "",          "");
	room.at(3).waypoint.at(26) = fmtROOMINFO_Waypoint(0x030F, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "",                              "",          "");
	room.at(3).waypoint.at(27) = fmtROOMINFO_Waypoint(0x030F, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "",                              "",          "");
	room.at(3).waypoint.at(28) = fmtROOMINFO_Waypoint(0x030F, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "",                              "",          "");
	room.at(3).waypoint.at(29) = fmtROOMINFO_Waypoint(0x030F, 52025.000f, -9079.000f, -25145.00f, 1.665000f, "",                              "",          "");
	room.at(3).waypoint.at(30) = fmtROOMINFO_Waypoint(0x0310, -6373.000f, 0.0000000f, -26160.00f, 0.000000f, "DUST",                          "YOKOYAMA",  "");
	room.at(3).waypoint.at(31) = fmtROOMINFO_Waypoint(0x0310, -17693.00f, 0.0000000f, -26153.00f, -1.64570f, "DUST{2}",                       "",          "");
	room.at(3).waypoint.at(32) = fmtROOMINFO_Waypoint(0x0310, -16419.00f, 0.0000000f, -16678.00f, 1.365540f, "DUST{3}",                       "",          "");
	room.at(3).waypoint.at(33) = fmtROOMINFO_Waypoint(0x0311, -7020.000f, 0.0000000f, -16263.00f, 0.885000f, "TEKKYU",                        "YOKOYAMA",  "");
	room.at(3).waypoint.at(34) = fmtROOMINFO_Waypoint(0x0311, 9214.0000f, 0.0000000f, -3019.000f, -0.79974f,  "",                              "",          "");
	room.at(3).waypoint.at(35) = fmtROOMINFO_Waypoint(0x0312, -5452.000f, 0.0000000f, 26310.000f, -1.83000f, "UNDERGROUND_2 { SAVE }",        "ISHII",     "");
	room.at(3).waypoint.at(36) = fmtROOMINFO_Waypoint(0x0313, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "r313 Green Room {Hit Disp}",    "",          ""); // manually inserted v0
	room.at(3).waypoint.at(37) = fmtROOMINFO_Waypoint(0x0314, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "r314 Green Room",               "",          ""); // manually inserted v0
	room.at(3).waypoint.at(38) = fmtROOMINFO_Waypoint(0x0315, 7947.0000f, 0.0000000f, -4510.000f, -0.44000f, "HIROMA_MAE",                    "MINAMI",    "");
	room.at(3).waypoint.at(39) = fmtROOMINFO_Waypoint(0x0316, 244.00000f, 0.0000000f, -7630.000f, -0.34000f, "BOILER",                        "MINAMI",    "");
	room.at(3).waypoint.at(40) = fmtROOMINFO_Waypoint(0x0316, 12870.000f, 2000.0000f, 7252.0000f, 1.466000f, "",                              "",          "");
	room.at(3).waypoint.at(41) = fmtROOMINFO_Waypoint(0x0317, -8077.000f, -5100.000f, -328.0000f, -0.16000f, "Factory",                       "MINAMI",    "");
	room.at(3).waypoint.at(42) = fmtROOMINFO_Waypoint(0x0317, 6900.0000f, 6010.0000f, 740.00000f, -3.14000f, "",                              "",          "");
	room.at(3).waypoint.at(43) = fmtROOMINFO_Waypoint(0x0318, -25167.00f, -1.000000f, 3899.0000f, 1.190000f, "SADDLER ROOM",                  "YASUDA",    "");
	room.at(3).waypoint.at(44) = fmtROOMINFO_Waypoint(0x031A, 2075.0000f, 0.0000000f, -168.0000f, 1.350000f, "UNDER",                         "KOUYAMA",   "");
	room.at(3).waypoint.at(45) = fmtROOMINFO_Waypoint(0x031B, -81958.00f, 3500.0000f, -17320.00f, 1.160000f, "U3_BOSS",                       "KOUYAMA",   "");
	room.at(3).waypoint.at(46) = fmtROOMINFO_Waypoint(0x031B, -21460.00f, 0.0000000f, -4150.000f, 0.140000f, "U3_kontena",                    "",          "");
	room.at(3).waypoint.at(47) = fmtROOMINFO_Waypoint(0x031B, 37500.000f, 4265.0000f, 340.00000f, 0.990000f, "U3_gachi",                      "",          "");
	room.at(3).waypoint.at(48) = fmtROOMINFO_Waypoint(0x031C, 41993.000f, 4000.0000f, 38500.000f, -2.98200f, "KLAUZAR_LAND",                  "HORI",      "");
	room.at(3).waypoint.at(49) = fmtROOMINFO_Waypoint(0x031C, -13334.00f, 0.0000000f, -16766.00f, -3.12000f, "goal",                          "",          "");
	room.at(3).waypoint.at(50) = fmtROOMINFO_Waypoint(0x031C, 7722.0000f, 0.0000000f, 11455.000f, -2.34000f, "start",                         "",          "");
	room.at(3).waypoint.at(51) = fmtROOMINFO_Waypoint(0x031D, -9043.000f, -3134.000f, -2713.000f, 1.440000f, "ISEKI_KLAUZAR_MAE",             "SHIMADA",   "");
	room.at(3).waypoint.at(52) = fmtROOMINFO_Waypoint(0x031D, 8575.0000f, -2.000000f, -5853.000f, 2.130000f, "top",                           "",          "");
	room.at(3).waypoint.at(53) = fmtROOMINFO_Waypoint(0x031D, 19535.000f, -12920.00f, -20263.00f, 2.180000f, "under",                         "",          "");
	room.at(3).waypoint.at(54) = fmtROOMINFO_Waypoint(0x0320, 29182.000f, 6057.0000f, 66850.000f, -2.80600f, "KUUBAKU_1",                     "YANO",      "");
	room.at(3).waypoint.at(55) = fmtROOMINFO_Waypoint(0x0320, 79810.000f, 10351.000f, 5698.0000f, -2.25000f, "",                              "",          "");
	room.at(3).waypoint.at(56) = fmtROOMINFO_Waypoint(0x0320, 51372.000f, 6714.0000f, -2890.000f, -1.67000f, "",                              "",          "");
	room.at(3).waypoint.at(57) = fmtROOMINFO_Waypoint(0x0321, 25220.000f, 6628.0000f, -15370.00f, -2.71300f, "KUUBAKU_2",                     "YANO",      "");
	room.at(3).waypoint.at(58) = fmtROOMINFO_Waypoint(0x0322, 16061.000f, 26165.000f, -35605.00f, 0.535000f, "r322",                           "",          ""); // manually inserted v49
	room.at(3).waypoint.at(59) = fmtROOMINFO_Waypoint(0x0323, -67466.00f, 33423.000f, -26900.00f, 1.297000f, "r323",                           "",          ""); // manually inserted v49
	room.at(3).waypoint.at(60) = fmtROOMINFO_Waypoint(0x0325, 14195.000f, 7557.0000f, -24930.00f, -0.36000f, "ENTRANCE",                      "YOSHITOMI", "");
	room.at(3).waypoint.at(61) = fmtROOMINFO_Waypoint(0x0326, 600.00000f, 3815.0000f, -8026.000f, -1.37000f, "PRISON",                        "YOSHITOMI", "");
	room.at(3).waypoint.at(62) = fmtROOMINFO_Waypoint(0x0327, -6575.000f, 5259.0000f, 25470.000f, 1.400000f, "SOTO_TUURO",                    "ISHII",     "");
	room.at(3).waypoint.at(63) = fmtROOMINFO_Waypoint(0x0327, -27525.00f, 6078.0000f, 15302.000f, 1.440000f, "",                              "",          "");
	room.at(3).waypoint.at(64) = fmtROOMINFO_Waypoint(0x0328, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "r328",                          "",          ""); // manually inserted
	room.at(3).waypoint.at(65) = fmtROOMINFO_Waypoint(0x0329, 12329.000f, -957.0000f, -5782.000f, 0.000000f, "CAPSULE",                       "YOSHITOMI", "");
	room.at(3).waypoint.at(66) = fmtROOMINFO_Waypoint(0x0330, -3510.000f, -1645.000f, -10090.00f, 1.380000f, "OPE",                           "YOSHITOMI", "");
	room.at(3).waypoint.at(67) = fmtROOMINFO_Waypoint(0x0331, -31383.00f, 6581.0000f, 32821.000f, 0.000000f, "FAINAL_BOSS_MAE",               "Arow",      "");
	room.at(3).waypoint.at(68) = fmtROOMINFO_Waypoint(0x0332, -42020.00f, 15811.000f, 47290.000f, 1.470000f, "FAINAL_BOSS",                   "Arow",      "");
	room.at(3).waypoint.at(69) = fmtROOMINFO_Waypoint(0x0333, -647528.0f, -12718.00f, -588505.0f, -1.60000f, "LAST",                          "KOUYAMA",   "");
	room.at(3).waypoint.at(70) = fmtROOMINFO_Waypoint(0x0333, -681185.0f, -26060.00f, -558950.0f, 1.040000f, "noriba",                        "",          "");
	room.at(3).waypoint.at(71) = fmtROOMINFO_Waypoint(0x0333, 449975.00f, -45500.00f, 171979.00f, 0.000000f, "ending",                        "",          "");
	room.at(3).waypoint.at(72) = fmtROOMINFO_Waypoint(0x0334, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "BULL",                          "YANO",      "");
	room.at(3).waypoint.at(73) = fmtROOMINFO_Waypoint(0x0334, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "",                              "",          "");
	room.at(3).waypoint.at(74) = fmtROOMINFO_Waypoint(0x0334, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "",                              "",          "");
	room.at(3).waypoint.at(75) = fmtROOMINFO_Waypoint(0x0334, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "",                              "",          "");
	room.at(3).waypoint.at(76) = fmtROOMINFO_Waypoint(0x0334, -56250.00f, -34520.00f, 108862.00f, 1.389000f, "",                              "",          "");
	room.at(3).waypoint.at(77) = fmtROOMINFO_Waypoint(0x0334, 52025.000f, -9079.000f, -25145.00f, 1.665000f, "",                              "",          "");

	room.at(4).waypoint = std::vector<fmtROOMINFO_Waypoint> (16); // Stage 4
	room.at(4).waypoint.at( 0) = fmtROOMINFO_Waypoint(0x0400, -12400.00f, 2576.0000f, 31080.000f, 2.486000f, "MURA",                          "HORI",      "");
	room.at(4).waypoint.at( 1) = fmtROOMINFO_Waypoint(0x0402, 21035.000f, 3065.0000f, -26370.00f, -1.53000f, "BATTLE AREA",                   "NAGANO",    "");
	room.at(4).waypoint.at( 2) = fmtROOMINFO_Waypoint(0x0403, 31558.000f, 8314.0000f, 38823.000f, 2.345000f, "KUUBAKU_1",                     "YANO",      "");
	room.at(4).waypoint.at( 3) = fmtROOMINFO_Waypoint(0x0403, 58358.000f, 16600.000f, -13455.00f, -0.30000f, "",                              "",          "");
	room.at(4).waypoint.at( 4) = fmtROOMINFO_Waypoint(0x0404, -640.0000f, 0.0000000f, -15890.00f, 3.130000f, "water_world",                   "Arow",      "");
	room.at(4).waypoint.at( 5) = fmtROOMINFO_Waypoint(0x0404, 10820.000f, 7563.0000f, -57308.00f, -1.37000f, "",                              "",          "");
	room.at(4).waypoint.at( 6) = fmtROOMINFO_Waypoint(0x0405, 28450.000f, -16798.00f, -40000.00f, -2.49000f, "SENNYUU_1",                     "KATAYAMA",  "");
	room.at(4).waypoint.at( 7) = fmtROOMINFO_Waypoint(0x0406, -8475.000f, -7000.000f, 8169.0000f, -1.94000f, "SENNYUU_2",                     "KATAYAMA",  "");
	room.at(4).waypoint.at( 8) = fmtROOMINFO_Waypoint(0x040A, 5257.0000f, 1.0000000f, 2392.0000f, -3.12000f, "1F-2F KAIDAN",                  "KATAYAMA",  "");
	room.at(4).waypoint.at( 9) = fmtROOMINFO_Waypoint(0x040B, 1629.0000f, 0.0000000f, 4756.0000f, -1.80000f, "OPE ROOM",                      "KATAYAMA",  "");
	room.at(4).waypoint.at(10) = fmtROOMINFO_Waypoint(0x040C, -3070.000f, 0.0000000f, 2680.0000f, 2.802000f, "FREEZER ROOM",                  "YOKOYAMA",  "");
	room.at(4).waypoint.at(11) = fmtROOMINFO_Waypoint(0x040D, -8010.000f, 0.0000000f, -7510.000f, 1.160000f, "LABORATORY",                    "NAGANO",    "");
	room.at(4).waypoint.at(12) = fmtROOMINFO_Waypoint(0x040E, 236.00000f, -3971.000f, 27394.000f, 1.470000f, "Tsuushin",                      "NAGANO",    "");
	room.at(4).waypoint.at(13) = fmtROOMINFO_Waypoint(0x040F, -18633.00f, 1000.0000f, 3407.0000f, 3.130000f, "GomiShori",                     "NAGANO",    "");
	room.at(4).waypoint.at(14) = fmtROOMINFO_Waypoint(0x0410, 10384.000f, 0.0000000f, 7666.0000f, -3.04000f, "KANKIN",                        "KATAYAMA",  "");
	room.at(4).waypoint.at(15) = fmtROOMINFO_Waypoint(0x0411, -13382.00f, 1743.0000f, -23000.00f, 1.690000f, "LAB_ROUKA",                     "NAGANO",    "");

	room.at(5).waypoint = std::vector<fmtROOMINFO_Waypoint> (41); // Stage 5
	room.at(5).waypoint.at( 0) = fmtROOMINFO_Waypoint(0x0500, 26161.000f, 1111.0000f, 1115.0000f, -1.82000f, "old101_mura",                   "hori",      "");
	room.at(5).waypoint.at( 1) = fmtROOMINFO_Waypoint(0x0501, -18863.00f, 0.0000000f, -18409.00f, 0.000000f, "old102_tikadou",                "hori",      "");
	room.at(5).waypoint.at( 2) = fmtROOMINFO_Waypoint(0x0502, -43898.00f, -36.00000f, -14735.00f, 2.010000f, "old108_tomb",                   "katayama",  "");
	room.at(5).waypoint.at( 3) = fmtROOMINFO_Waypoint(0x0503, 150.00000f, -1038.000f, 6152.0000f, 3.140000f, "old117_church{night}",          "nishihori", "");
	room.at(5).waypoint.at( 4) = fmtROOMINFO_Waypoint(0x0504, -14215.00f, 2690.0000f, 33195.000f, 2.780000f, "old101_mura",                   "hori",      "");
	room.at(5).waypoint.at( 5) = fmtROOMINFO_Waypoint(0x0505, -47730.00f, 0.0000000f, 7154.0000f, 1.900000f, "old103_farm",                   "ueji",      "");
	room.at(5).waypoint.at( 6) = fmtROOMINFO_Waypoint(0x0506, 13853.000f, 6344.0000f, 3893.0000f, -1.47000f, "old105_sontyou house",          "hori",      "");
	room.at(5).waypoint.at( 7) = fmtROOMINFO_Waypoint(0x0507, 11220.000f, -895.0000f, -104.0000f, 0.760000f, "old106_haison",                 "nagano",    "");
	room.at(5).waypoint.at( 8) = fmtROOMINFO_Waypoint(0x0508, 4099.0000f, -16741.00f, -109100.0f, 2.070000f, "old10f_gondola",                "mikami",    "");
	room.at(5).waypoint.at( 9) = fmtROOMINFO_Waypoint(0x0508, 3640.0000f, -16741.00f, -106126.0f, 2.530000f, "old10f_gondola",                "mikami",    "");
	room.at(5).waypoint.at(10) = fmtROOMINFO_Waypoint(0x0509, 105088.00f, -1070.000f, -20800.00f, 2.870000f, "old11c_rouzyou",                "ishii",     "");
	room.at(5).waypoint.at(11) = fmtROOMINFO_Waypoint(0x0509, 104755.00f, -1015.000f, -21150.00f, 2.960000f, "old11c_rouzyou",                "ishii",     "ota1");
	room.at(5).waypoint.at(12) = fmtROOMINFO_Waypoint(0x050A, 63684.000f, -26.00000f, 28504.000f, -1.07000f, "old11e_hokora",                 "nishihori", "kitagaito");
	room.at(5).waypoint.at(13) = fmtROOMINFO_Waypoint(0x050B, 12740.000f, -1018.000f, -9795.000f, 1.850000f, "old11f_sontyou boss",           "hori",      "");
	room.at(5).waypoint.at(14) = fmtROOMINFO_Waypoint(0x050C, 0.0000000f, 0.0000000f, -750.0000f, 3.000000f, "old206_main hall",              "yoshii",    "");
	room.at(5).waypoint.at(15) = fmtROOMINFO_Waypoint(0x050D, -50.00000f, 0.0000000f, -360.0000f, 3.000000f, "old20a_rouka",                  "shimada",   "");
	room.at(5).waypoint.at(16) = fmtROOMINFO_Waypoint(0x050E, -1014.000f, 6046.0000f, -290.0000f, 3.117000f, "old20b_bed room",               "shimada",   "");
	room.at(5).waypoint.at(17) = fmtROOMINFO_Waypoint(0x050F, 65.000000f, 3500.0000f, 340.00000f, -0.15000f, "old20c_gallery room",           "shimada",   "");
	room.at(5).waypoint.at(18) = fmtROOMINFO_Waypoint(0x0510, 41230.000f, 3500.0000f, 26265.000f, 1.570000f, "old20f_gallery room2",          "ueji",      "");
	room.at(5).waypoint.at(19) = fmtROOMINFO_Waypoint(0x0511, 236.00000f, -3971.000f, 27394.000f, 1.470000f, "old30a_tsuushin",               "nagano",    "");
	room.at(5).waypoint.at(20) = fmtROOMINFO_Waypoint(0x0512, -53956.00f, -40516.00f, -4493.000f, -2.95000f, "old30f_omakeA",                 "yano",      "kitagaito");
	room.at(5).waypoint.at(21) = fmtROOMINFO_Waypoint(0x0513, -65595.00f, -2000.000f, -13162.00f, 2.112870f, "old30f_omakeB",                 "yoshii",    "");
	room.at(5).waypoint.at(22) = fmtROOMINFO_Waypoint(0x0514, 39712.000f, 278.00000f, -39180.00f, 1.293000f, "old30f_omakeC",                 "yano",      "");
	room.at(5).waypoint.at(23) = fmtROOMINFO_Waypoint(0x0515, 7947.0000f, 0.0000000f, -4510.000f, -0.44000f, "old315_hiroma mae",             "yoshitomi", "");
	room.at(5).waypoint.at(24) = fmtROOMINFO_Waypoint(0x0516, 244.00000f, 0.0000000f, -7630.000f, -0.34000f, "old316_boiler",                 "yoshitomi", "");
	room.at(5).waypoint.at(25) = fmtROOMINFO_Waypoint(0x0517, -8077.000f, -5100.000f, -328.0000f, -0.16000f, "old317_factory",                "yoshii",    "");
	room.at(5).waypoint.at(26) = fmtROOMINFO_Waypoint(0x0518, 29182.000f, 6057.0000f, 66850.000f, -2.80600f, "old320_kuubaku1",               "nagano",    "");
	room.at(5).waypoint.at(27) = fmtROOMINFO_Waypoint(0x0519, 25220.000f, 6628.0000f, -15370.00f, -2.71300f, "old321_kuubaku2",               "yano",      "");
	room.at(5).waypoint.at(28) = fmtROOMINFO_Waypoint(0x051A, 14195.000f, 7557.0000f, -24930.00f, -0.36000f, "old325_entrance",               "yoshitomi", "");
	room.at(5).waypoint.at(29) = fmtROOMINFO_Waypoint(0x051B, 600.00000f, 3815.0000f, -8026.000f, -1.37000f, "old326_prison",                 "yoshitomi", "");
	room.at(5).waypoint.at(30) = fmtROOMINFO_Waypoint(0x051C, -6576.000f, 5259.0000f, 25470.000f, 1.400000f, "old327_soto tuuro",             "ishii",     "");
	room.at(5).waypoint.at(31) = fmtROOMINFO_Waypoint(0x051D, 11020.000f, 2074.0000f, -11570.00f, -0.91000f, "old329_capsule",                "yoshitomi", "");
	room.at(5).waypoint.at(32) = fmtROOMINFO_Waypoint(0x051E, -17952.00f, 23311.000f, 40133.000f, -0.84000f, "old332_final boss",             "yoshii",    "yamanoguchi");
	room.at(5).waypoint.at(33) = fmtROOMINFO_Waypoint(0x051F, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "movie",                         "",          "");
	room.at(5).waypoint.at(34) = fmtROOMINFO_Waypoint(0x0530, 72410.000f, -2139.000f, -36887.00f, -1.22000f, "old105_e3 st1",                 "hori",      "");
	room.at(5).waypoint.at(35) = fmtROOMINFO_Waypoint(0x0531, -19647.00f, -18000.00f, -6748.000f, -3.09000f, "old300_e3 st2",                 "hori",      "");
	room.at(5).waypoint.at(36) = fmtROOMINFO_Waypoint(0x0532, -66720.00f, -2000.000f, -13000.00f, 2.900000f, "old513_e3 st3",                 "eirou",     "");
	room.at(5).waypoint.at(37) = fmtROOMINFO_Waypoint(0x0532, 23300.000f, -5000.000f, -3100.000f, 0.000000f, "",                              "",          "");
	room.at(5).waypoint.at(38) = fmtROOMINFO_Waypoint(0x0532, 12350.000f, -11000.00f, -6530.000f, 3.140000f, "",                              "",          "");
	room.at(5).waypoint.at(39) = fmtROOMINFO_Waypoint(0x0533, -109483.0f, -618.0000f, 916.00000f, 2.000000f, "MORI",                          "YANO",      "");
	room.at(5).waypoint.at(40) = fmtROOMINFO_Waypoint(0x0534, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "dummy",                         "dummy",     ""); // manually inserted v0

	room.at(6).waypoint = std::vector<fmtROOMINFO_Waypoint> (49); // Stage 6
	room.at(6).waypoint.at( 0) = fmtROOMINFO_Waypoint(0x0600, -51510.00f, 165.00000f, 21834.000f, 2.330000f, "old101_mura",                   "hori",      "");
	room.at(6).waypoint.at( 1) = fmtROOMINFO_Waypoint(0x0601, -18863.00f, 0.0000000f, -18409.00f, 0.000000f, "old102_tikadou",                "hori",      "");
	room.at(6).waypoint.at( 2) = fmtROOMINFO_Waypoint(0x0602, -43898.00f, -36.00000f, -14735.00f, 2.010000f, "old108_tomb",                   "katayama",  "");
	room.at(6).waypoint.at( 3) = fmtROOMINFO_Waypoint(0x0603, 150.00000f, -1038.000f, 6152.0000f, 3.140000f, "old117_church{night}",          "nishihori", "");
	room.at(6).waypoint.at( 4) = fmtROOMINFO_Waypoint(0x0604, -51510.00f, 165.00000f, 21834.000f, 2.330000f, "old101_mura",                   "hori",      "");
	room.at(6).waypoint.at( 5) = fmtROOMINFO_Waypoint(0x0605, -47730.00f, 0.0000000f, 7154.0000f, 1.900000f, "old103_farm",                   "ueji",      "");
	room.at(6).waypoint.at( 6) = fmtROOMINFO_Waypoint(0x0606, -33790.00f, 0.0000000f, -1578.000f, 2.000000f, "old105_sontyou house",          "hori",      "");
	room.at(6).waypoint.at( 7) = fmtROOMINFO_Waypoint(0x0607, 11220.000f, -895.0000f, -104.0000f, 0.760000f, "old106_haison",                 "nagano",    "");
	room.at(6).waypoint.at( 8) = fmtROOMINFO_Waypoint(0x0608, -25153.00f, 4000.0000f, 16554.000f, 1.000000f, "old10f_gondola",                "mikami",    "");
	room.at(6).waypoint.at( 9) = fmtROOMINFO_Waypoint(0x0609, 51183.000f, 0.0000000f, -71789.00f, 1.220000f, "old11c_rouzyou",                "ishii",     "");
	room.at(6).waypoint.at(10) = fmtROOMINFO_Waypoint(0x060A, 693.00000f, -26.00000f, 995.00000f, 0.000000f, "old11e_hokora",                 "nishihori", "");
	room.at(6).waypoint.at(11) = fmtROOMINFO_Waypoint(0x060B, 12740.000f, -1018.000f, -9795.000f, 1.850000f, "old11f_sontyou boss",           "hori",      "");
	room.at(6).waypoint.at(12) = fmtROOMINFO_Waypoint(0x060C, 0.0000000f, 0.0000000f, -750.0000f, 3.000000f, "old206_main hall",              "yoshii",    "");
	room.at(6).waypoint.at(13) = fmtROOMINFO_Waypoint(0x060D, -50.00000f, 0.0000000f, -360.0000f, 3.000000f, "old20a_rouka",                  "shimada",   "");
	room.at(6).waypoint.at(14) = fmtROOMINFO_Waypoint(0x060E, -1014.000f, 6046.0000f, -290.0000f, 3.117000f, "old20b_bed room",               "shimada",   "");
	room.at(6).waypoint.at(15) = fmtROOMINFO_Waypoint(0x060F, 65.000000f, 3500.0000f, 340.00000f, -0.15000f, "old20c_gallery room",           "shimada",   "");
	room.at(6).waypoint.at(16) = fmtROOMINFO_Waypoint(0x0610, 41230.000f, 3500.0000f, 26265.000f, 1.570000f, "old20f_gallery room2",          "ueji",      "");
	room.at(6).waypoint.at(17) = fmtROOMINFO_Waypoint(0x0611, 236.00000f, -3971.000f, 27394.000f, 1.470000f, "old30a_tsuushin",               "nagano",    "");
	room.at(6).waypoint.at(18) = fmtROOMINFO_Waypoint(0x0612, -53350.00f, -40516.00f, -3280.000f, 3.057000f, "old30f_omakeA",                 "yano",      "");
	room.at(6).waypoint.at(19) = fmtROOMINFO_Waypoint(0x0613, -66720.00f, -2000.000f, -13000.00f, 2.900000f, "old30f_omakeB",                 "yoshii",    "");
	room.at(6).waypoint.at(20) = fmtROOMINFO_Waypoint(0x0614, 39712.000f, 278.00000f, -39180.00f, 1.293000f, "old30f_omakeC",                 "yano",      "");
	room.at(6).waypoint.at(21) = fmtROOMINFO_Waypoint(0x0615, 7947.0000f, 0.0000000f, -4510.000f, -0.44000f, "old315_hiroma mae",             "yoshitomi", "");
	room.at(6).waypoint.at(22) = fmtROOMINFO_Waypoint(0x0616, 244.00000f, 0.0000000f, -7630.000f, -0.34000f, "old316_boiler",                 "yoshitomi", "");
	room.at(6).waypoint.at(23) = fmtROOMINFO_Waypoint(0x0617, -8077.000f, -5100.000f, -328.0000f, -0.16000f, "old317_factory",                "yoshii",    "");
	room.at(6).waypoint.at(24) = fmtROOMINFO_Waypoint(0x0618, 29182.000f, 6057.0000f, 66850.000f, -2.80600f, "old320_kuubaku1",               "nagano",    "");
	room.at(6).waypoint.at(25) = fmtROOMINFO_Waypoint(0x0619, 25220.000f, 6628.0000f, -15370.00f, -2.71300f, "old321_kuubaku2",               "yano",      "");
	room.at(6).waypoint.at(26) = fmtROOMINFO_Waypoint(0x061A, 14195.000f, 7557.0000f, -24930.00f, -0.36000f, "old325_entrance",               "yoshitomi", "");
	room.at(6).waypoint.at(27) = fmtROOMINFO_Waypoint(0x061B, 600.00000f, 3815.0000f, -8026.000f, -1.37000f, "old326_prison",                 "yoshitomi", "");
	room.at(6).waypoint.at(28) = fmtROOMINFO_Waypoint(0x061C, -6575.000f, 5259.0000f, 25470.000f, 1.400000f, "old327_soto tuuro",             "ishii",     "");
	room.at(6).waypoint.at(29) = fmtROOMINFO_Waypoint(0x061D, 12329.000f, -957.0000f, -5782.000f, 0.000000f, "old329_capsule",                "yoshitomi", "");
	room.at(6).waypoint.at(30) = fmtROOMINFO_Waypoint(0x061E, -42020.00f, 15811.000f, 47290.000f, 1.470000f, "old332_final boss",             "yoshii",    "");
	room.at(6).waypoint.at(31) = fmtROOMINFO_Waypoint(0x061F, 150.00000f, -1038.000f, 6152.0000f, 3.140000f, "old117_church{night}",          "nishihori", "");
	room.at(6).waypoint.at(32) = fmtROOMINFO_Waypoint(0x0620, -3444.000f, 0.0000000f, 12333.000f, -1.58000f, "old104_KANKIN",                 "YANO",      "");
	room.at(6).waypoint.at(33) = fmtROOMINFO_Waypoint(0x0620, 26840.000f, -70.00000f, -27201.00f, 2.350000f, "old206_DOOR",                   "YANO",      "");
	room.at(6).waypoint.at(34) = fmtROOMINFO_Waypoint(0x0621, 4099.0000f, -16741.00f, -109100.0f, 2.070000f, "old508_gondola",                "mikami",    "");
	room.at(6).waypoint.at(35) = fmtROOMINFO_Waypoint(0x0621, 3640.0000f, -16741.00f, -106126.0f, 2.530000f, "old206_gondola",                "mikami",    "");
	room.at(6).waypoint.at(36) = fmtROOMINFO_Waypoint(0x0622, 0.0000000f, 0.0000000f, -750.0000f, 3.000000f, "old206_MAIN HALL",              "Arow",      "");
	room.at(6).waypoint.at(37) = fmtROOMINFO_Waypoint(0x0622, -7539.000f, 8000.0000f, -4891.000f, 2.110000f, "",                              "",          "");
	room.at(6).waypoint.at(38) = fmtROOMINFO_Waypoint(0x0623, 26880.000f, 2960.0000f, 84.000000f, 1.350000f, "old215_LOAD ROOM",              "ISHII",     "");
	room.at(6).waypoint.at(39) = fmtROOMINFO_Waypoint(0x0623, 26880.000f, 2960.0000f, 84.000000f, 1.350000f, "",                              "",          "");
	room.at(6).waypoint.at(40) = fmtROOMINFO_Waypoint(0x0624, 10750.000f, 0.0000000f, 725.00000f, -1.75000f, "old227_SYMBOL TOWER",           "KOUYAMA",   "");
	room.at(6).waypoint.at(41) = fmtROOMINFO_Waypoint(0x0624, 18041.000f, 28625.000f, -5436.000f, 1.190000f, "old227_SYMBOL TOWER_ELV",       "",          "");
	room.at(6).waypoint.at(42) = fmtROOMINFO_Waypoint(0x0624, 228.00000f, 13500.000f, 4818.0000f, 2.878000f, "",                              "",          "");
	room.at(6).waypoint.at(43) = fmtROOMINFO_Waypoint(0x0625, -8077.000f, -5100.000f, -328.0000f, -0.16000f, "old317_Factory",                "MINAMI",    "");
	room.at(6).waypoint.at(44) = fmtROOMINFO_Waypoint(0x0625, 6900.0000f, 6010.0000f, 740.00000f, -3.14000f, "",                              "",          "");
	room.at(6).waypoint.at(45) = fmtROOMINFO_Waypoint(0x0626, 150.00000f, -1038.000f, 6152.0000f, 3.140000f, "old117_CHURCH{night}",          "YANO",      "");
	room.at(6).waypoint.at(46) = fmtROOMINFO_Waypoint(0x0626, -3342.000f, 4007.0000f, 6293.0000f, 3.000000f, "old117_CHURCH - SWITCH{night}", "YANO",      "");
	room.at(6).waypoint.at(47) = fmtROOMINFO_Waypoint(0x0627, -17570.00f, 0.0000000f, 1542.0000f, 0.060000f, "old304_monitor_room",           "KATAYAMA",  "");
	room.at(6).waypoint.at(48) = fmtROOMINFO_Waypoint(0x0628, 131876.00f, 2298.0000f, 11466.000f, -2.00000f, "old119_COLOSSEUM{night}",       "MINAMI",    "");

	room.at(7).waypoint = std::vector<fmtROOMINFO_Waypoint> (6); // Stage 7
	room.at(7).waypoint.at( 0) = fmtROOMINFO_Waypoint(0x0700, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "Test",                          "",          "");
	room.at(7).waypoint.at( 1) = fmtROOMINFO_Waypoint(0x0701, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "",                               "",         ""); // manually inserted v0
	room.at(7).waypoint.at( 2) = fmtROOMINFO_Waypoint(0x0702, -7734.000f, 3978.0000f, 49115.000f, 1.872000f, "1st",                           "",          "");
	room.at(7).waypoint.at( 3) = fmtROOMINFO_Waypoint(0x0703, 0.0000000f, 0.0000000f, 0.0000000f, 0.000000f, "2st",                           "yano",      "");
	room.at(7).waypoint.at( 4) = fmtROOMINFO_Waypoint(0x0705, 102790.00f, -4700.000f, 57160.000f, -1.44000f, "",                              "",          "");
	room.at(7).waypoint.at( 5) = fmtROOMINFO_Waypoint(0x0706, 102790.00f, -4700.000f, 57160.000f, -1.44000f, "",                              "",          "");
	}

void fmtROOMINFO::read (std::wstring fileW) {

	bytestream f;
	if (f.openFileW(fileW)) {
		size_t pos = f.tell();

		count = f.readUlong();


		if (count > 0x01000000 || count < 0) {
			f.islilEndian = !f.islilEndian;
			f.seek(pos);
			count = f.readUlong();
			}


		if (count > 0) {

			addrs.clear();
			addrs = std::vector<uint32_t>(count);
			for (unsigned int i = 0; i < count; i++) {
				addrs[i] = f.readUlong();
				}
			room.clear();
			room = std::vector<fmtROOMINFO_Room>(count);
			for (unsigned int i = 0; i < count; i++) {
				f.seek(pos + addrs[i]);
				room[i].read(f);
				}
			}

		f.close();
		} else {std::cout << "failed to read file\n";}
	}

size_t fmtROOMINFO::recalc_addrs () {

	size_t ptr = 0;

	count = room.size();

	addrs.clear();
	if (count > 0) {
		addrs = std::vector<uint32_t>(count);
		ptr = count * 4;
		if (ptr > 0) {ptr += 4;}
		for (unsigned int i = 0; i < count; i++) {
			addrs[i] = ptr;
			ptr += room[i].size();
			}
		}

	for (unsigned int i = 0; i < count; i++) {
		room[i].waypoint_count = room[i].waypoint.size();
		for (unsigned int ii = 0; ii < room[i].waypoint_count; ii++) {
			room[i].waypoint[ii].name_addr = ptr;
			room[i].waypoint[ii].artist_addr = (ptr += room[i].waypoint[ii].name.length() + 1);
			room[i].waypoint[ii].coder_addr = (ptr += room[i].waypoint[ii].artist.length() + 1);
			ptr += room[i].waypoint[ii].coder.length() + 1;
			}
		}
	return ptr;
	}

size_t fmtROOMINFO::size () {
	size_t nsize = (room.size() + 1) * 4;
	unsigned int stage_count = room.size();
	unsigned int room_count;
	for (unsigned int i = 0; i < stage_count; i++) {
		nsize += room[i].size();
		}
	for (unsigned int i = 0; i < stage_count; i++) {
		room_count = room[i].waypoint.size();
		for (unsigned int ii = 0; ii < room_count; ii++) {
			nsize += room[i].waypoint[ii].name.length() + 1;
			nsize += room[i].waypoint[ii].artist.length() + 1;
			nsize += room[i].waypoint[ii].coder.length() + 1;
			}
		}
	return nsize;
	}

void fmtROOMINFO::write (std::wstring fileW) {

	size_t nsize = recalc_addrs();
	if (nsize > 4) {
		bytestream s;
		s.resize(nsize);


		s.writelong(count);

		for (unsigned int i = 0; i < count; i++) {
			s.writelong(addrs[i]);
			}

		for (unsigned int i = 0; i < count; i++) {
			room[i].write(s);
			}


		for (unsigned int i = 0; i < count; i++) {
			for (unsigned int ii = 0; ii < room[i].waypoint_count; ii++) {
				s.writestring(room[i].waypoint[ii].name);
				s.writestring(room[i].waypoint[ii].artist);
				s.writestring(room[i].waypoint[ii].coder);
				}
			}
		s.writeFileW(fileW);
		s.close();

		}
	}
