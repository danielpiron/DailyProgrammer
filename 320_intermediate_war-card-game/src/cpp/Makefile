CXX = clang++

testwar: war.o testwar.o
	$(CXX) -g -Wall -pedantic -std=c++11 -o testwar testwar.o war.o -L /usr/local/lib -I /usr/local/include -lgtest

testwar.o: testwar.cc
	$(CXX) -g -Wall -pedantic -std=c++11 -o testwar.o -c testwar.cc

war.o: war.cc
	$(CXX) -g -Wall -pedantic -std=c++11 -o war.o -c war.cc

.PHONY: clean
clean:
	rm *.o testwar
