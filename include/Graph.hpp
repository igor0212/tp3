#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <string>

using namespace std;

class Graph 
{ 
    public: 
        int V;
	    list<int>* adj;
        Graph();
        void Create(int V);
	    void AddEdge(int v1, int v2);
}; 

#endif