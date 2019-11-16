#include <list>
#include <string>
#include <map>
#include ".\Graph.hpp"
#include <iostream>
#include <sstream> 

using namespace std;

Graph::Graph(){}

void Graph::Create(int V)
{
	this->V = V;
	adj = new list<int>[V];	
}

void Graph::AddEdge(int v1, int v2)
{	
	adj[v1].push_back(v2);
    adj[v2].push_back(v1);
}