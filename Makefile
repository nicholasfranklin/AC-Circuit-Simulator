# PHYS30762 INTRO TO OOP PROJECT
# MAKEFILE 
# STUDENT ID: 11120960
# MAY 2025 

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -IMNA/include -IExamples

# Source files 
CPP_SRCS = $(wildcard Examples/*.cpp)
CXX_SRCS = $(wildcard MNA/src/*.cxx) $(wildcard Examples/*.cxx)
SRCS = $(CPP_SRCS) $(CXX_SRCS)

# Object files
OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.cxx=.o)

# Target
TARGET = main.exe

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile .cpp files to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .cxx files to .o
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts (Windows-style)
clean:
	del /q /f MNA\src\*.o Examples\*.o *.exe 2>nul

.PHONY: all clean