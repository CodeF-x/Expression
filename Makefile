CC=g++
CFLAGS=-c -std=c++17 -Wall


all: tests differentiator

tests: tests.o #expression.o
	$(CC) tests.o -o tests
	
differentiator: differentiator.o# expression.o
	$(CC) differentiator.o  -o differentiator

differentiator.o: differentiator.cpp
	$(CC) $(CFLAGS) differentiator.cpp

#expression.o: expression.hpp
#	$(CC) $(CFLAGS) expression.hpp

tests.o: tests.cpp
	$(CC) $(CFLAGS) tests.cpp
	
clean:
	rm -rf tests.o differentiator.o
