#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Graph.hpp>

using namespace std;

vector<vector<int>> GetRegions(vector<vector<int>> vertices, int N, int I, int J)
{
    vector<vector<int>> regions;
    vector<vector<int>> incorrect_regions;
    int minColumn = 0;
    int maxColumn = J;

    // Separando regiões pela coluna
    while(minColumn <= N)
    {
        vector<int> incorrect_region;

        for(int i=0; i < N; i++)
            for(int j=0; j < N; j++)            
            {                
                int column = j+1;
                if(column > minColumn && column <= maxColumn)                
                    incorrect_region.push_back(vertices[i][j]);
            }        

        minColumn += J;
        maxColumn += J;    

        if(incorrect_region.size() > 0)
            incorrect_regions.push_back(incorrect_region);        
    }

    // Separando regiões pela linha      
    for(int i=0; i < incorrect_regions.size(); i++)
    {
        vector<int> incorrect_region = incorrect_regions[i];
        
        int minRow = 0;
        int maxRow = N;

        while(maxRow <= incorrect_region.size())
        {
            vector<int> region;

            for(int j=0; j < incorrect_region.size(); j++)   
            {
                int row = j+1;
                if(row > minRow && row <= maxRow)                
                    region.push_back(incorrect_region[j]);                             
            }            

            minRow += N;
            maxRow += N;

            if(region.size() > 0)
                regions.push_back(region);        
        }        
    }

    return regions;
}


Graph AddEdge(Graph graph, vector<vector<int>> vertices, int N, int I, int J)
{
    // Adicionando linhas ao sudoku
    for(int i=0; i < N; i++)    
        for(int j=0; j < N-1; j++)            
            graph.AddEdge(vertices[i][j], vertices[i][j+1]);

    // Adicionando colunas ao sudoku
    for(int i=0; i < N-1; i++)
        for(int j=0; j < N; j++)            
            graph.AddEdge(vertices[i][j], vertices[i+1][j]);

    // Adicionando quadrantes ao sudoku 
    vector<vector<int>> regions = GetRegions(vertices, N, I, J);    
    for(int i=0; i < regions.size(); i++)    
    {
        vector<int> region = regions[i];

        for(int j=0; j < region.size()-1; j++)
            graph.AddEdge(region[j], region[j+1]);        
    }        

    return graph;
}

Graph GetGraphFromFile(string sudokuFile)
{	
	string line;	
	ifstream inFile;
	int N, I, J, counter=1;	
	Graph graph;
    vector<vector<int>> vertices;
	
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
            }

            vertices.push_back(verticesRow);
        }

		counter++;
	}

	inFile.close();	

    graph = AddEdge(graph, vertices, N, I, J);    

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

    // Mostrar resultado do sudoku finalizado
    for (int u = 0; u < graph.V; u++)     
    {    
        //cout << result[u] << " ";

        if ((u+1) % 4 == 0)
            cout << "\n";
    }
}