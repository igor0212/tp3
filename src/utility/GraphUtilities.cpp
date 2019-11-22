#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Graph.hpp>
#include <math.h>
#include <algorithm>

using namespace std;

bool Contains(vector<int> vector, int element)
{    
    std::vector<int>::iterator it;
    it = find (vector.begin(), vector.end(), element); 
    return it != vector.end();
}

void AddColumn(Graph graph, int N)
{
    vector<int> vectorAux;

    vector<int> incorrectRegion;    

    for(int i=0; i < graph.sudokuTable.size(); i++)
    {
        if(Contains(vectorAux, i))                    
            continue;     

        int counterColumn = 1;
        int idxColumn = i;
        while (counterColumn <= N)
        {               
            vectorAux.push_back(idxColumn);               
            incorrectRegion.push_back(idxColumn);
            idxColumn += N;  
            counterColumn++;          
        }        
    }

    vector<vector<int>> regions;
    vector<int> region;
    for(int i=0; i < incorrectRegion.size(); i++)
    {
        int idxAux = i+1;               
        region.push_back(incorrectRegion[i]);        

        if(idxAux % N == 0)
        {
            regions.push_back(region);
            region.clear();
        }
    }

    for(int i=0; i < regions.size(); i++)  
    {
        vector<int> region = regions[i];

        for(int j=0; j < region.size()-1; j++)
            for(int k=0; k < region.size(); k++)            
                if(j != k && k > j)
                    graph.AddEdge(region[j], region[k]);  
    }
}

void AddRow(Graph graph, int N)
{
    vector<vector<int>> regions;
    vector<int> region;
    for(int i=0; i < graph.sudokuTable.size(); i++)
    {
        int idxAux = i+1;               
        region.push_back(i);        

        if(idxAux % N == 0)
        {            
            regions.push_back(region);
            region.clear();
        }
    }

    for(int i=0; i < regions.size(); i++)  
    {
        vector<int> region = regions[i];

        for(int j=0; j < region.size()-1; j++)
            for(int k=0; k < region.size(); k++)            
                if(j != k && k > j)
                    graph.AddEdge(region[j], region[k]);  
    }
}

void AddRegion(Graph graph, int N, int I)
{
    vector<int> vectorAux;

    vector<int> incorrectRegion;    

    for(int i=0; i < graph.sudokuTable.size(); i++)
    {
        if(Contains(vectorAux, i))                    
            continue;     

        int counterColumn = 1;
        int idxColumn = i;
        while (counterColumn <= I)
        {   
            vectorAux.push_back(idxColumn);               
            incorrectRegion.push_back(idxColumn);
            idxColumn += N;  
            counterColumn++;          
        }
    }

    vector<vector<int>> regions;
    vector<int> region;
    for(int i=0; i < incorrectRegion.size(); i++)
    {
        int idxAux = i+1;               
        region.push_back(incorrectRegion[i]);        

        if(idxAux % N == 0)
        {
            regions.push_back(region);
            region.clear();
        }
    }

    for(int i=0; i < regions.size(); i++)  
    {
        vector<int> region = regions[i];

        for(int j=0; j < region.size()-1; j++)
            for(int k=0; k < region.size(); k++)            
                if(j != k && k > j)
                    graph.AddEdge(region[j], region[k]);  
    }
}

Graph AddEdge(Graph graph, int N, int I, int J)
{
    AddRegion(graph, N, I);

    AddRow(graph, N);

    AddColumn(graph, N);    

    return graph;
}

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
        int a = 0;
		istringstream s(line);		
		if (counter == 1)
		{  
			// Armazenando primeira linha: tamanho da tabela do Sudoku, quantidade de colunas
			// e quantidade de linhas
    		if (!(s >> N >> J >> I)) { break; }	
			graph.Create(N*N);
		}
        else
        {
            // Armazenando sudoku no vetor
            int verticeAux;
            vector<int> verticesRow;
            for(int i = 0; i < N; i++)
            {
                if (!(s >> verticeAux)) { break; }
                verticesRow.push_back(verticeAux);
                graph.sudokuTable.push_back(verticeAux);                
            }            
        }

        a++;
		counter++;
	}    

	inFile.close();	

    graph = AddEdge(graph, N, I, J);    

	return graph;
}

void GreedyColoring(Graph graph)
{	 
    int aux = sqrt(graph.V);
    bool available[aux]; 
    for (int cr = 0; cr < aux; cr++) {
        available[cr] = false;
    }  
    
    for (int u = 0; u < graph.V; u++) 
    {         
        list<int>::iterator i; 
        for (i = graph.adj[u].begin(); i != graph.adj[u].end(); ++i) 
            if (graph.sudokuTable[*i] != 0) 
                available[graph.sudokuTable[*i]] = true; 
  
        int cr; 
        for (cr = 1; cr < aux; cr++){
            if (available[cr] == false){
                break;
            }  
        }
  
        graph.sudokuTable[u] = cr;       
        for (i = graph.adj[u].begin(); i != graph.adj[u].end(); ++i) 
            if (graph.sudokuTable[*i] != 0) 
                available[graph.sudokuTable[*i]] = false; 
    }   

    int u = 0;
    for(int i = 0; i < graph.V; i++){
        cout << graph.sudokuTable[i] << " ";
        u++;
        if(u == sqrt(graph.V)){
            cout << endl;
            u = 0;
        }
    }

    // for (int v = 0; v < graph.V; ++v) 
    // { 
    //     cout << "\n Adjacency list of vertex "
    //          << v << "\n head "; 
    //     for (auto x : graph.adj[v]) 
    //        cout << "-> " << x; 
    //     printf("\n"); 
    // }
}