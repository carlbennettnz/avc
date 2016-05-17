avc:
	pi-g++ src/*.cpp lib/inih/cpp/INIReader.cpp lib/inih/ini.cpp -g -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o ./bin/avc
	scp ./bin/avc 101-pi:
