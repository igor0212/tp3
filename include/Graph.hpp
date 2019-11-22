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
        vector<int> sudokuTable;
        Graph();
        void Create(int V);
	    void AddEdge(int v1, int v2);
}; 

#endif