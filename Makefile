all:
	g++ -std=c++17 -Iinclude -o app src/main.cpp -lstdc++fs

clean:
	rm app
