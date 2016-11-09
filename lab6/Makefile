CXXFLAGS = -std=c++11 -Wall

all : test-regex

test-regex : test-regex.o engine.o regex.o testbase.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean :
	rm -f test-regex *.o *~

.PHONY : all clean
