#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <Graph.hpp>

using namespace std;

Graph GetGraphFromFile(string sudokuFile)
{	
	string line;	
	ifstream inFile;
	int N, I, J, counter=1;	
	Graph graph;
	
	inFile.open("datasets/" + sudokuFile);	

	if (!inFile) {
        cout << "Não foi possível abrir o arquivo";
        return graph;
    }	

	//Percorrer todo o arquivo
	while (getline(inFile, line))
	{	
		istringstream s(line);		
		if (counter == 1)
		{  
			//Armazenando primeira linha: tamanho da tabela do Sudoku, quantidade de colunas
			// e quantidade de linhas
    		if (!(s >> N >> I >> J)) { break; }	
			graph.Create(N);
		}

		counter++;
	}

	inFile.close();	

	return graph;
}

void GreedyColoring(Graph graph)
{
	int result[graph.V]; 

	for (int u = 1; u < graph.V; u++) 
        result[u] = -1; 

	bool available[graph.V]; 
    for (int cr = 0; cr < graph.V; cr++) 
        available[cr] = false; 

    for (int u = 1; u < graph.V; u++) 
    {
        list<int>::iterator i; 
        for (i = graph.adj[u].begin(); i != graph.adj[u].end(); ++i) 
            if (result[*i] != -1) 
                available[result[*i]] = true; 
  
        int cr; 
        for (cr = 0; cr < graph.V; cr++) 
            if (available[cr] == false) 
                break; 
  
        result[u] = cr; 
  
        for (i = graph.adj[u].begin(); i != graph.adj[u].end(); ++i) 
            if (result[*i] != -1) 
                available[result[*i]] = false; 
    } 

    for (int u = 0; u < graph.V; u++) 
        cout << "Vertex " << u << " --->  Color "
             << result[u] << endl;	
}