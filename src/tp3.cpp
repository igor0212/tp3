#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <sstream> 
#include "../include/GraphUtilities.hpp"
#include "../include/SwapUtilities.hpp"
#include "../include/CommanderUtilities.hpp"

using namespace std;

void Swap(Graph graph, list<int> items, string *fileOut)
{	
	bool isSwap = GetSwap(graph, items);	

	//Adicionar resultado a saida
	if(isSwap)	
		*fileOut += "S T\n";
	else	
		*fileOut += "S N\n";
}

void Commander(Graph graph, list<int> items, string *fileOut)
{
	int commander = GetCommander(graph, items);	

	//Adicionar resultado a saida
	if(commander < 0)
		*fileOut += "C * \n";	
	else 
	{
		ostringstream str_age; 
		str_age << commander; 
		*fileOut += "C " + str_age.str() + "\n";		
	}
}

void Meeting(Graph graph, string *fileOut)
{
	string row = "";

	//Realizar a busca em largura
	graph.Bfs(0, &row);

	//Adicionar resultado a saida
	*fileOut += "M " + row + "\n";
}

void Tasks(Graph graph)
{
	string fileOut = "";
	typedef map <string, list<int>> StringFloatMap;
	StringFloatMap :: iterator pos;	

	//Percorrer a lista de dicionarios para tratar cada comando
	for (auto i: graph.commands) 
	{
		for (pos = i.begin(); pos != i.end (); ++ pos) 
		{
			string command = pos->first;
			list<int> items = pos->second;		

			if(command == "S")
				Swap(graph, items, &fileOut);
			else if(command == "C")
				Commander(graph, items, &fileOut);
			else if(command == "M")
				Meeting(graph, &fileOut);
			else
			{
				cout << "Comando " << command << " inválido";
			}
		}
	}
	
	cout << fileOut;	
}

void StartTP1(string equipeFile)
{	
	//Criação do grafo, dicionario de idades e lista de dicionarios dos comandos
	Graph graph = GetGraphFromFile(equipeFile);

	//Realizar comandos (Swap, Commander, Meeting)
	Tasks(graph);
}