CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

main: bin/main
test: bin/test

bin/main: src/main.cpp src/Node.hpp src/Graph.hpp src/Edge.hpp
	${CXX} ${CXX_FLAGS} src/main.cpp -o $@

bin/test: tests/tests.cpp src/Node.hpp src/Graph.hpp src/Edge.hpp
	${CXX} ${CXX_FLAGS} tests/tests.cpp -o bin/test

obj/catch.o: tests/tests.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

.DEFAULT_GOAL := test

clean:
	rm -fr bin/* obj/*