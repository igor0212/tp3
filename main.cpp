#include <iostream>
#include <stdio.h>
#include "include/tp3.hpp"

using namespace std;

int main(int argc, char* argv[])
{		
	if (argc != 2) {
		cout <<  "Argumento invalido";		
		return 0;
	}
	else {					
		string sudokuFile = argv[argc-1];			
		StartTP3(sudokuFile);
		return 1;
	}		
}