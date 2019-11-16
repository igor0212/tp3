#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <Graph.hpp>

using namespace std;

map<int, int> ages;

Graph GetGraphFromFile(string teamFile)
{	
	string line;	
	ifstream inFile;
	int N, M, I, counter=1;	
	list<map<string, list<int>>> commands;
	Graph graph;
	
	inFile.open("datasets/" + teamFile);	

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
			//Armazenando primeira linha: numero de pessoas no time, numero de relações
			// diretas entre os membros e numero de instrucoes e criando o grafo
    		if (!(s >> N >> M >> I)) { break; }	
			graph.Create(N);
		} else if (counter == 2)
		{	
			//Criar dicionario (de/para) com as idades das pessoas
			int age, index=0;			
			while (s >> age) 
			{
				ages[index] = age;
				index++;
			}	
		}
		else if (counter >= 3 && counter < (3 + M))
		{
			//Adicionar arestas no grafo
			int commander, commanded;			
			if (!(s >> commander >> commanded)) { break; }
			graph.AddEdge(commander-1, commanded-1);
		}
		else if (counter >= (3 + M) && counter < ((3 + M) + I))
		{
			//Criar lista de dicionarios para os comandos
			string command = ""; 
			int commander = 0, commanded = 0;
			list<int> listCommanderCommanded;
			map<string, list<int>> cmdDic;			
			s >> command >> commander >> commanded;			
			if(commander != 0) listCommanderCommanded.push_back(commander-1);
			if(commanded != 0) listCommanderCommanded.push_back(commanded-1);
			cmdDic[command] = listCommanderCommanded;
			commands.push_back(cmdDic);
		}

		counter++;
	}

	inFile.close();	

	//Adicionar dicionario de idades e lista de comandos no grafo	
	graph.Alter(commands, ages);

	return graph;
}