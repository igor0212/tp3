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

	// Realizar o sudoku
	GreedyColoring(graph);
}