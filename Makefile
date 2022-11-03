CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cc src/Node.hpp src/Graph.hpp src/Edge.hpp
	${CXX} ${CXX_FLAGS} src/main.cc src/Node.hpp src/Graph.hpp src/Edge.hpp -o bin/exec

bin/tests: tests/tests.hpp obj/catch.o src/Node.hpp src/Graph.hpp src/Edge.hpp
	${CXX} ${CXX_FLAGS} obj/catch.o tests/tests.hpp src/Node.hpp src/Graph.hpp src/Edge.hpp -o bin/tests

obj/catch.o: tests/catch.cc
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*