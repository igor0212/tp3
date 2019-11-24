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
    vector<vector<int>> regions;
    vector<int> region;

    for(int i=0; i < graph.vertices.size(); i++)
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

    for(int i=0; i < graph.vertices.size(); i++)
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
    vector<vector<int>> regions;
    vector<int> region;

    for(int i=0; i < graph.vertices.size(); i++)
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
    // Adicionando arestas para os vertices da mesma regiao
    AddRegion(graph, N, I);

    // Adicionando arestas para os vertices da mesma linha
    AddRow(graph, N);

    // Adicionando arestas para os vertices da mesma coluna
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
		istringstream s(line);		
		if (counter == 1)
		{  
			// Armazenando primeira linha: tamanho da tabela do Sudoku, quantidade de colunas
			// e quantidade de linhas
    		if (!(s >> N >> J >> I)) { break; }	
			graph.Create(N*N, N);
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
                graph.vertices.push_back(verticeAux);                
            }            
        }
        
		counter++;
	}    

	inFile.close();	

    // Adicionando arestas aos vertices
    graph = AddEdge(graph, N, I, J);    

	return graph;
}