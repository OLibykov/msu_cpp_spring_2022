CC=g++-10
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

format_str: format_str.cpp
	$(CC) $(FLAGS) format_str.cpp -c

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp -c

test_bin: format_str.o test.o
	$(CC) $(FLAGS) test.o format_str.o -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o main test_bin

