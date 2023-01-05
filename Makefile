CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = wordrange.o utils.o

all: wordrange compare

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ wordrange.o utils.o

wordrange.o: wordrange.cpp utils.h utils.cpp
	$(CXX) -g $(CXXFLAGS) -c wordrange.cpp

utils.o: utils.cpp utils.h
	$(CXX) -g $(CXXFLAGS) -c utils.cpp

clean:
	rm *.o
	rm wordrange
	rm compare

compare: comparefiles.o
	$(CXX) -g $(CXXFLAGS) -o $@ comparefiles.o

comparefiles.o: comparefiles.cpp
	$(CXX) -g $(CXXFLAGS) -c comparefiles.cpp
