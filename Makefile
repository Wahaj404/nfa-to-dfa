CXX=g++
CXXFLAGS=-g -c -std=c++17 -Ilibfort
CC=gcc
CFLAGS=-g -c -std=c17

nfa-to-dfa: fa.o dfa.o dfa-state.o nfa.o nfa-state.o fort.o main.o
	$(CXX) fa.o dfa.o dfa-state.o nfa.o nfa-state.o main.o fort.o -o nfa-to-dfa
 
fa.o: fa.hpp fa.cpp util.hpp
	$(CXX) $(CXXFLAGS) fa.cpp -o fa.o

dfa.o: dfa.hpp dfa.cpp dfa-state.hpp util.hpp
	$(CXX) $(CXXFLAGS) dfa.cpp -o dfa.o

dfa-state.o: dfa-state.hpp dfa-state.cpp util.hpp
	$(CXX) $(CXXFLAGS) dfa-state.cpp -o dfa-state.o

nfa.o: nfa.hpp nfa.cpp nfa-state.hpp dfa.hpp dfa-state.hpp util.hpp
	$(CXX) $(CXXFLAGS) nfa.cpp -o nfa.o

nfa-state.o: nfa-state.hpp nfa-state.cpp util.hpp
	$(CXX) $(CXXFLAGS) nfa-state.cpp -o nfa-state.o

main.o: main.cpp nfa.hpp nfa-state.hpp dfa.hpp dfa-state.hpp util.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

fort.o: libfort/fort.hpp libfort/fort.h libfort/fort.c
	$(CC) $(CFLAGS) libfort/fort.c -o fort.o

clean:
	rm -f *.o
	rm -f nfa-to-dfa