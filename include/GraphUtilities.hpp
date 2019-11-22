#ifndef GRAPHUTILITIES_H
#define GRAPHUTILITIES_H

#include <Graph.hpp>
#include <string>
#include <vector>

using namespace std;

bool Contains(vector<int> vector, int element);

void AddColumn(Graph graph, int N);

void AddRow(Graph graph, int N);

void AddRegion(Graph graph, int N, int I);

Graph AddEdge(Graph graph, int N, int I, int J);

Graph GetGraphFromFile(string sudokuFile);

void GreedyColoring(Graph graph);

#endif