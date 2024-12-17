PROGRAMS=\
parser \
$(NULL)

# Compiler
#CXX = g++
CXXFLAGS=-std=c++17 -O0 -fno-inline -g -Wall -Wextra -Wpedantic -Werror -pedantic-errors
LDFLAGS=-std=c++17

## for gcov
#CXXFLAGS:=$(CXXFLAGS) -fprofile-arcs -ftest-coverage
#LDFLAGS:=$(LDFLAGS) -fprofile-arcs

all: $(PROGRAMS)

$(PROGRAMS): %: %.o
	g++ $(LDFLAGS) $< -o $@

%.o: %.cpp *.hpp Makefile
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf test.log *~ .vscode/*~ *.o *.dSYM $(PROGRAMS) *.gcda *.gcno *.gcov callgrind.out.*