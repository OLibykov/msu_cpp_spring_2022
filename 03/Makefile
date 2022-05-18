CC=g++-10
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean valgrind

all: test_bin

My_Matrix.o: My_Matrix.cpp
	$(CC) $(FLAGS) My_Matrix.cpp -c

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp -c

test_bin: My_Matrix.o test.o
	$(CC) $(FLAGS) My_Matrix.o test.o -o test_bin $(TEST_LIBS)

test:
	./test_bin

valgrind: test_bin
	valgrind ./test_bin
clean:
	rm -f *.o main test_bin

