#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
#include <stdio.h>
//#include <conio.h>
#include "include/tp3.hpp"

using namespace std;

int main(int argc, char* argv[])
{		
	if (argc != 2) {
		cout <<  "Argumento invalido";		
		return 0;
	}
	else {					
		string equipeFile = argv[argc-1];			
		StartTP1(equipeFile);
		return 1;
	}		
}