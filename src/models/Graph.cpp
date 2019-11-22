#include <list>
#include <string>
#include <algorithm>
#include ".\Graph.hpp"

using namespace std;

Graph::Graph(){}

void Graph::Create(int V)
{
	this->V = V;
	adj = new list<int>[V];	
}

void Graph::AddEdge(int v1, int v2)
{	
	bool found_first = find(adj[v1].begin(), adj[v1].end(), v2) != adj[v1].end();
	if(!found_first)
		adj[v1].push_back(v2);	

	bool found_second = find(adj[v2].begin(), adj[v2].end(), v1) != adj[v2].end();		
	if(!found_second)
    	adj[v2].push_back(v1);		
}