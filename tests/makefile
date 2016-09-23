all: unittest

unittest: test_runner.cpp
	g++ tests/test_runner.cpp tests/datetime/test_greg_calendar_base.cpp -Isrc -I/home/LyDD/include -std=c++14 -L/home/LyDD/lib/boost -lboost_unit_test_framework -L/home/LyDD/lib/boost -lboost_timer
