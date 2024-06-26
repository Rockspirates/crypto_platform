# Define the compiler
CXX = g++

# Define the flags for the compiler
CXXFLAGS = -Wall -Wextra -std=c++17

# Define the output file
OUTPUT = main.o

# Get all cpp files in the current directory
SOURCES = $(wildcard *.cpp)

# The default target
all: $(OUTPUT)

# The rule to build the output file
$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# The clean target to remove generated files
clean:
	rm -f $(OUTPUT)

# Phony targets
.PHONY: all clean
