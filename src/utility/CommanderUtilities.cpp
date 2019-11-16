#include <list>
#include <algorithm>
#include "../include/GraphUtilities.hpp"
#include <iostream>

using namespace std;

int Order(int v, Graph graph, Graph alterGraph)
{
	bool *visited = new bool[alterGraph.V]; 
    list<int> queue;
    list<int> neighbor;
    for(int i = 0; i < alterGraph.V; i++)
        visited[i] = false;     

    visited[v] = true;
        
    queue.push_back(v); 
    
    list<int>::iterator i; 

    //Enquanto nao percorrer todo o grafo, a busca nao pode finalizar
    while(!queue.empty()) 
    {   
        v = queue.front();        
        queue.remove(v);

        //Percorrer vizinhos do vertice          
        for (i = alterGraph.adj[v].begin(); i != alterGraph.adj[v].end(); ++i) 
        { 
            if (!visited[*i])   
            {				
                visited[*i] = true;   				                                     
				neighbor.push_back(graph.ages[*i]);				
                queue.push_back(*i);                 
            }          
        }              
    }

    //Verificando as idades dos comandantes
	int age;
	if(neighbor.empty())
		age = -1;
	else {
		neighbor.sort();
		age = neighbor.front();
	}

	return age;
}

int GetCommander(Graph graph, list<int> items)
{	
	if(items.empty())
		return -1;	

	int item1 = items.front();

    //Transpor o grafo
	Graph alterGraph = graph.GetTranspose();	

    //Busca em largura a partir do vertice indicado no parametro
	return Order(item1, graph, alterGraph);
}