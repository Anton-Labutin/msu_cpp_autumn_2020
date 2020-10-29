CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wno-unused-variable

all: main

main: tests.o test_runner.o matrix.o main.o
	$(CXX) $(CXXFLAGS) -o my_matrix tests.o test_runner.o matrix.o main.o
    
test: my_matrix
	./my_matrix

tests.o: ./Tests/tests.cpp
	$(CXX) $(CXXFLAGS) -c ./Tests/tests.cpp

test_runner.o: ./Tests/TestTemplate/test_runner.cpp
	$(CXX) $(CXXFLAGS) -c ./Tests/TestTemplate/test_runner.cpp

matrix.o: ./Matrix/matrix.cpp
	$(CXX) $(CXXFLAGS) -c ./Matrix/matrix.cpp

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -rf *.o my_matrix
