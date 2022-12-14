

CXX=clang++
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -O0 -Wall -Wextra -Werror

exec: bin/exec
tests: bin/tests

bin/exec: ./src/main.cpp ./src/Graph.cpp ./src/Node.cpp ./src/Edge.cpp ./src/Dijkstra.cpp ./src/Betweenness.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

bin/tests: ./tests/tests.cpp ./src/Graph.cpp ./src/Node.cpp ./src/Edge.cpp ./src/Dijkstra.cpp ./src/Betweenness.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: exec clean tests

clean:
	rm -rf bin/*