CC=g++
FLAGS=-std=c++17

all: main

main: tests.o test_runner.o my_allocator.o main.o
	$(CC) $(FLAGS) -o my_allocator tests.o test_runner.o my_allocator.o main.o
    
test: my_allocator
	./my_allocator

tests.o: ./Tests/tests.cpp
	$(CC) $(FLAGS) -c ./Tests/tests.cpp

test_runner.o: ./Tests/TestTemplate/test_runner.cpp
	$(CC) $(FLAGS) -c ./Tests/TestTemplate/test_runner.cpp

my_allocator.o: ./Allocator/my_allocator.cpp
	$(CC) $(FLAGS) -c ./Allocator/my_allocator.cpp

main.o: main.cpp 
	$(CC) $(FLAGS) -c main.cpp

clean: 
	rm -rf *.o my_allocator
