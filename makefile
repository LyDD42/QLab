CXX = g++
STD = c++14

# include
QLAB_INCLUDE = include
BOOST_INCLUDE = /home/LyDD/local/include

# lib
BOOST_LIB_PATH = /home/LyDD/local/lib/boost
BOOST_LIBS = boost_unit_test_framework boost_timer boost_chrono boost_system

INCLUDE = $(QLAB_INCLUDE) $(BOOST_INCLUDE)
CXXFLAGS = -std=$(STD)  $(foreach d, $(INCLUDE), -I$(d))

# LDFLAGS LDLIBS
LDFLAGS = -L $(BOOST_LIB_PATH)
LDLIBS = $(foreach lib, $(BOOST_LIBS), -l$(lib))

vpath %.cpp tests
vpath %.cpp tests/utilities
vpath %.cpp tests/datetime
vpath %.cpp tests/math

# make implicint rules explicit
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -g -c -Wall -fPIC $< -o $@

.PHONY: test_utilities test_datetime test_math clean

all:

run_test: test_runner clean 
	./test_runner -l all

# # using implicit linking rule
# test_runner: $(wildcard, *.o)

# TODO: replace *.o
test_runner: test_utilities test_datetime test_math 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) tests/test_runner.cpp *.o -o test_runner

test_utilities: test_constrained_value.o test_int_adapter.o

test_datetime: test_greg_calendar_base.o

test_math: test_array.o

clean:
	rm *.o
