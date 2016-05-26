# Set the default ssh host to upload to
UPLOAD_TARGET ?= 101-pi:

ifneq ($(UPLOAD_TARGET),none)
	upload = scp bin/$(1) $(UPLOAD_TARGET)
endif

avc:
	pi-g++ src/*.cpp lib/inih/cpp/INIReader.cpp lib/inih/ini.cpp -g -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o ./bin/avc
	$(call upload,avc)

ir_test:
	pi-g++ sandbox/ir_test.cpp src/ir.cpp -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o bin/ir_test
	$(call upload,ir_test)

camera_test:
	pi-g++ sandbox/camera_test.cpp src/camera.cpp -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o bin/camera_test
	$(call upload,camera_test)

drive_test:
	pi-g++ sandbox/drive_test.cpp src/actuators.cpp lib/inih/ini.cpp lib/inih/cpp/INIReader.cpp src/utils.cpp -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o bin/drive_test
	$(call upload,drive_test)

gate_test:
	pi-g++ sandbox/gate_test.cpp -Wall -std=c++11 -Llib -lE101 -lmmal -lbcm_host -Wl,-rpath,./lib -o bin/gate_test
	$(call upload,gate_test)

reporter_test_local:
	g++ sandbox/reporter_test.cpp src/utils.cpp -Wall -std=c++11 -o bin/reporter_test

reporter_test:
	pi-g++ sandbox/reporter_test.cpp src/utils.cpp -Wall -std=c++11 -o bin/reporter_test
	$(call upload,reporter_test)
