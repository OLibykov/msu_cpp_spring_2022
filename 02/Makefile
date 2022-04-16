CC=g++-10
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean 

all: test_bin

My_Parser.o: My_Parser.cpp
	$(CC) $(FLAGS) My_Parser.cpp -c

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp -c

test_bin: My_Parser.o test.o
	$(CC) $(FLAGS) My_Parser.o test.o -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o main test_bin

