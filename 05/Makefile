CC=g++-10
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

Serializer_Deserializer.o: Serializer_Deserializer.cpp Serializer_Deserializer.hpp templ.tpp
	$(CC) $(FLAGS) Serializer_Deserializer.cpp -c

test.o: test.cpp Serializer_Deserializer.hpp templ.tpp
	$(CC) $(FLAGS) test.cpp -c

test_bin: Serializer_Deserializer.o test.o
	$(CC) $(FLAGS) Serializer_Deserializer.o test.o -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o main test_bin

