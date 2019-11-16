#include <list>
#include <algorithm>
#include "../include/GraphUtilities.hpp"

using namespace std;

bool GetSwap(Graph graph, list<int> items)
{
	if(items.empty())
		return false;

	int item1 = items.front();
	int item2 = items.back();	

	//Verificar se vertices possuem conexao
	bool hasConnection = find(graph.adj[item1].begin(), graph.adj[item1].end(), item2) != graph.adj[item1].end();

	if(!hasConnection)
		return false;

	graph.adj[item1].remove(item2);
	graph.adj[item2].push_back(item1);

	//Verificar se grafo possui ciclo
	if(graph.HasCycle())
	{
		graph.adj[item2].remove(item1);
		graph.adj[item1].push_back(item2);
		return false;
	}

	return true;
}