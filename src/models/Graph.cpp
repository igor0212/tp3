#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include ".\Graph.hpp"

using namespace std;

#define MAX_COLORS 1001
vector<int> Color(MAX_COLORS, -1);

Graph::Graph(){}

void Graph::Create(int V, int N)
{
	this->V = V;	
	adj = new list<int>[V];	
	this->maxColors = N;	
}

void Graph::AddEdge(int v1, int v2)
{	
    // Verificando se vertices ja são conectados
	bool found_first = find(adj[v1].begin(), adj[v1].end(), v2) != adj[v1].end();
	if(!found_first)
		adj[v1].push_back(v2);	

    // Verificando se vertices ja são conectados
	bool found_second = find(adj[v2].begin(), adj[v2].end(), v1) != adj[v2].end();		
	if(!found_second)
    	adj[v2].push_back(v1);		
}

bool Graph::IsSafe(int u, int color){
    // Verificando se um vertice pode ser ligado a outro
    list<int>::iterator it;    
    for(it=adj[u].begin();it!=adj[u].end();++it){
        if(Color[*it] == color) 
			return false;
    }

    return true;
}

bool Graph::Coloring(int u){
    if(u == this->V) 
		return true;

    for(int i = 0; i < this->maxColors; i++){        
        if(IsSafe(u,i)){ 
            Color[u] = i;
            // Chamada recursiva
            if(Coloring(u+1)) 
				return true;

            // Utilizando backtracking
            Color[u] = -1;
        }
    }
    return false;
}

void Graph::Print(){
    for(int i = 0; i < this->V; i++){
        cout << Color[i] +1 << " ";
		if((i+1) % this->maxColors == 0)        
			cout << "\n";	
    }    
}