CC=g++-10
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp -c

test_bin: test.o
	$(CC) $(FLAGS) test.o -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o main test_bin
