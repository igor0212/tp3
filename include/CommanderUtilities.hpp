#ifndef COMMANDERUTILITIES_H
#define COMMANDERUTILITIES_H

#include <Graph.hpp>

using namespace std;

int Order(int v, Graph graph, Graph alterGraph);
int GetCommander(Graph graph, list<int> items);

#endif