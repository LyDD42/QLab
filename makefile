CXX = g++
STD = c++14
QLAB_INCLUDE = include
BOOST_INCLUDE = /home/LyDD/local/include
BOOST_LIB_PATH = /home/LyDD/local/lib/boost
BOOST_LIBS = boost_unit_test_framework boost_timer boost_chrono boost_system


INCLUDE = $(QLAB_INCLUDE) $(BOOST_INCLUDE)
CXXFLAGS = -std=$(STD)  $(foreach d, $(INCLUDE), -I$(d))

BOOST_UTF_FLAGS = $(foreach l, $(BOOST_LIBS), -L$(BOOST_LIB_PATH) -l${l})


all: test clean

test: tests/test_runner.cpp test_utilities test_datetime
	$(CXX) $(CXXFLAGS) $(BOOST_UTF_FLAGS) tests/test_runner.cpp test_constrained_value.o test_int_adapter.o test_datetime.o -o test_runner

test_utilities: tests/utilities/test_constrained_value.cpp
	$(CXX) $(CXXFLAGS) $(BOOST_UTF_FLAGS) -g -c -Wall -fPIC tests/utilities/test_constrained_value.cpp -o test_constrained_value.o
	$(CXX) $(CXXFLAGS) $(BOOST_UTF_FLAGS) -g -c -Wall -fPIC tests/utilities/test_int_adapter.cpp -o test_int_adapter.o

test_datetime: tests/datetime/test_greg_calendar_base.cpp
	$(CXX) $(CXXFLAGS) $(BOOST_UTF_FLAGS) -g -c -Wall -fPIC tests/datetime/test_greg_calendar_base.cpp -o test_datetime.o


clean:
	rm *.o
