CXX=g++
CXXFLAGS=-std=c++17

all: main

main: tests.o test_runner.o parser.o main.o
	$(CXX) $(CXXFLAGS) -o my_parser tests.o test_runner.o parser.o main.o
    
test: my_parser
	./my_parser

tests.o: ./Tests/tests.cpp
	$(CXX) $(CXXFLAGS) -c ./Tests/tests.cpp

test_runner.o: ./Tests/TestTemplate/test_runner.cpp
	$(CXX) $(CXXFLAGS) -c ./Tests/TestTemplate/test_runner.cpp

parser.o: ./Parser/parser.cpp
	$(CXX) $(CXXFLAGS) -c ./Parser/parser.cpp

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp

clean: 
	rm -rf *.o
