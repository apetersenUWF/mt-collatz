CXX = g++
CXXFLAGS = -std=c++2a -Wall -g -pthread

# Object file names
DRIVER = main.o
INCLUDE = stopwatch.o histogram.o mt-collatz.o parse.o

# Executable file names
EXEC = mt-collatz

# Main targets
run: $(INCLUDE) $(DRIVER)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(INCLUDE) $(DRIVER)

clean:
	rm -f $(EXEC) $(INCLUDE) $(DRIVER)

# Object targets
main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

stopwatch.o:
	$(CXX) $(CXXFLAGS) -c stopwatch.cpp -o stopwatch.o

histogram.o:
	$(CXX) $(CXXFLAGS) -c histogram.cpp -o histogram.o

mt-collatz.o:
	$(CXX) $(CXXFLAGS) -c mt-collatz.cpp -o mt-collatz.o

parse.o:
	$(CXX) $(CXXFLAGS) -c parse.cpp -o parse.o