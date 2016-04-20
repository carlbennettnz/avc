avc:
	pi-g++ main.cpp -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o ./bin/avc
	scp ./bin/avc 101-pi:
