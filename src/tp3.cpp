#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <sstream> 
#include "../include/GraphUtilities.hpp"

using namespace std;

void Tasks(Graph graph)
{
	string fileOut = "";
	typedef map <string, list<int>> StringFloatMap;
	StringFloatMap :: iterator pos;		
}

void StartTP3(string sudokuFile)
{	
	//Criação do grafo, dicionario de idades e lista de dicionarios dos comandos
	Graph graph = GetGraphFromFile(sudokuFile);

	//Realizar comandos (Swap, Commander, Meeting)
	Tasks(graph);
}