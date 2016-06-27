CXXFLAGS = -std=c++11 -Wall -O3 -fopenmp

bron_kerbosch.x: example.o bron_kerbosch.o
	g++ $(CXXFLAGS) -obron_kerbosch.x example.o bron_kerbosch.o

example.o: example.cpp
	g++  -c example.cpp
	
bron_kerbosch.o: bron_kerbosch.cpp
	g++  $(CXXFLAGS) -c bron_kerbosch.cpp
	
install:
	cp bron_kerbosch.x /usr/local/bin

uninstall:
	rm /usr/local/bin/bron_kerbosch.x

clean:
	rm *.o *.x
