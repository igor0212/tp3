#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <string>

using namespace std;

class Graph 
{ 
    public: 
        int V;
	    list<int>* adj;
        vector<int> vertices;
        int maxColors;
        Graph();
        void Create(int V, int N);
	    void AddEdge(int v1, int v2);
        bool Coloring(int u);
        bool IsSafe(int u, int color);
        void Print();
}; 

#endif