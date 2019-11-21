#ifndef GRAPHUTILITIES_H
#define GRAPHUTILITIES_H

#include <Graph.hpp>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> GetRegions(vector<vector<int>> vertices, int N, int I, int J);

Graph AddEdge(Graph graph, vector<vector<int>> vertices, int N, int I, int J);

Graph GetGraphFromFile(string sudokuFile);

void GreedyColoring(Graph graph);

#endif