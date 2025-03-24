CC=g++
CFLAGS=-c -std=c++17 -Wall


all: tests differentiator

tests: tests.o expression.o#expression.o
	$(CC) tests.o expression.o -o tests
	
differentiator: differentiator.o expression.o# expression.o
	$(CC) differentiator.o expression.o -o differentiator


expression.o: expression.cpp
	$(CC) $(CFLAGS) expression.cpp

differentiator.o: differentiator.cpp
	$(CC) $(CFLAGS) differentiator.cpp
	
#expression.o: expression.hpp
#	$(CC) $(CFLAGS) expression.hpp

tests.o: tests.cpp
	$(CC) $(CFLAGS) tests.cpp
	
clean:
	rm -rf tests.o differentiator.o expression.o

test: tests
	./tests
