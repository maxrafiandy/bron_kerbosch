CXXFLAGS = -std=c++11 -Wall -O2 -fopenmp

mmbench.x: bron_kerbosch.cpp
	g++ $(CXXFLAGS) -obron_kerbosch.x bron_kerbosch.cpp

install:
	cp bron_kerbosch.x /usr/local/bin

uninstall:
	rm /usr/local/bin/bron_kerbosch.x

clean:
	rm bron_kerbosch.x
