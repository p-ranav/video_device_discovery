all:
	g++ -std=c++17 -Iinclude -o app src/main.cpp src/video_device_info.cpp src/helpers.cpp -lstdc++fs

clean:
	rm app
