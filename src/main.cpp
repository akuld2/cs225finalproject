#include "Graph.h"
#include "Edge.h"
#include "Node.h"

#include <iostream>

int main()
{
    std::cout << "hello world" << std::endl;
    Graph* tmpGraph = new Graph("datasets/testDataSet.csv");
    tmpGraph->printGraph();
    std::cout << "\n\n" << std::endl;
    tmpGraph->BFS(tmpGraph->getNodes()->at(0));
    delete tmpGraph;
   
}