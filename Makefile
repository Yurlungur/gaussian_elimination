# Makefile for the Gaussian Elimination Package
# Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
# Time-stamp: <2013-08-25 14:11:54 (jonah)>

# The default compiler is g++
CXX = g++

# Flags for the compiler. Ask for warnings. Enable the debugger.
CXXFLAGS = -Wall -g

default: gaussian_elimination_test_driver

all: gaussian_elimination_test_driver dynamic_array_test_driver gaussian_system_test_driver

test_suite: all

install: all

gaussian_elimination_test_driver: gaussian_elimination_test_driver.bin
gaussian_elimination_test_driver.bin: gaussian_elimination_test_driver.o gaussian_elimination.o gaussian_system.o
	$(CXX) $(CXXFLAGS) -o $@ $^

gaussian_elimination_test_driver.o: gaussian_system.hpp gaussian_elimination.hpp dynamic_array.hpp

gaussian_elimination.o: gaussian_elimination.hpp gaussian_system.hpp dynamic_array.hpp

gaussian_system_test_driver: gaussian_system_test_driver.bin
gaussian_system_test_driver.bin: gaussian_system_test_driver.o gaussian_system.o
	$(CXX) $(CXXFLAGS) -o $@ $^

gaussian_system_test_driver.o: gaussian_system.hpp dynamic_array.hpp

gaussian_system.o: dynamic_array.hpp gaussian_system.hpp

dynamic_array_test_driver: dynamic_array_test_driver.bin
dynamic_array_test_driver.bin: dynamic_array_test_driver.o
	$(CXX) $(CXXFLAGS) -o $@ $^

dynamic_array_test_driver.o: dynamic_array.hpp

.PHONY: default all test_suite install gaussian_elimination_test_driver gaussian_system_test_driver dynamic_array_test_driver

clean:
	$(RM) *.bin *.o