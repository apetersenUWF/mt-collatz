CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Object file names
DRIVER = mt-collatz.o
INCLUDE = stopwatch.o histogram.o

# Executable file names
EXEC = mt-collatz

# Main targets
run: $(INCLUDE) $(DRIVER)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(INCLUDE) $(DRIVER)

clean:
	rm -f $(EXEC) $(INCLUDE) $(DRIVER)

# Object targets
stopwatch.o:
	$(CXX) $(CXXFLAGS) -c stopwatch.cpp -o stopwatch.o

histogram.o:
	$(CXX) $(CXXFLAGS) -c histogram.cpp -o histogram.o

mt-collatz.o:
	$(CXX) $(CXXFLAGS) -c mt-collatz.cpp -o mt-collatz.o