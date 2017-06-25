CXX = clang++

war: main.o
	$(CXX) -g -Wall -o war main.o

main.o: main.cc
	$(CXX) -g -Wall -pedantic -std=c++11 -o main.o -c main.cc
