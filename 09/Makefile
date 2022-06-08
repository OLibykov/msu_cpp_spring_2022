CC=g++-10
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

mysort.o: mysort.cpp mysort.hpp
	$(CC) $(FLAGS) mysort.cpp -c

test.o: test.cpp mysort.hpp
	$(CC) $(FLAGS) test.cpp -c

test_bin: mysort.o test.o
	$(CC) $(FLAGS) mysort.o test.o -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o main test_bin
