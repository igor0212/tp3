#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream> 
#include "../include/GraphUtilities.hpp"

using namespace std;

void StartTP3(string sudokuFile)
{	
	// Criação do grafo
	Graph graph = GetGraphFromFile(sudokuFile);

	//Resolvendo sudoku
	int index = 0;
    if(graph.Coloring(index))
        cout << "solucao" << "\n";    
    else
		cout << "sem solucao" << "\n";

	graph.Print();	
}