#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "freq_table_builder.h"

using namespace std;


void build_freq_table(char* filename, unordered_map<int, int>& freqTable) 
{

	ifstream inFile;
	inFile.open(filename);
	string temp;
	int t;

	while (getline(inFile,temp))
	{
		t = std::stoi(temp);
		if (freqTable.find(t) == freqTable.end()) 
		{
			freqTable[t] = 1;
		}
		else 
		{
			freqTable[t]++;
		}

	}
	inFile.close();

}
