#ifndef GRAPHUTILITIES_H
#define GRAPHUTILITIES_H

#include <Graph.hpp>
#include <string>

using namespace std;

Graph GetGraphFromFile(string sudokuFile);

void GreedyColoring(Graph graph);

#endif