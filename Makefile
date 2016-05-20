avc:
	pi-g++ src/*.cpp lib/inih/cpp/INIReader.cpp lib/inih/ini.cpp -g -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o ./bin/avc
	scp ./bin/avc 101-pi:

ir_test:
	pi-g++ sandbox/ir_test.cpp src/ir.cpp -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o bin/ir_test
	scp bin/ir_test 101-pi:

camera_test:
	pi-g++ sandbox/camera_test.cpp src/camera.cpp -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o bin/camera_test
	scp bin/camera_test 101-pi:

drive_test:
	pi-g++ sandbox/drive_test.cpp src/actuators.cpp src/utils.cpp -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o bin/drive_test
	scp bin/drive_test 101-pi:

gate_test:
	pi-g++ sandbox/gate_test.cpp -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o bin/gate_test
	scp bin/gate_test 101-pi:
