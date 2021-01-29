#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <time.h>
#include <bitset>
#include "freq_table_builder.h"
#include "huffman_tree_by_binary_heap.h"
#include "huffman_tree_by_4way_heap.h"
#include "huffman_tree_by_pairing_heap.h"
//(Some part of the code is modified based on https ://github.com/rushi13/Huffman-Coding)

using namespace std;

char INPUT_FILE[] = "C:\\Users\\Jonathan\\source\\repos\\adsProject\\sample_input_small.txt";

int main()
{
    
    unordered_map<int, int> freqTable;
    unordered_map<int, string> codeTable;
    build_freq_table(INPUT_FILE, freqTable);
    cout << "freq table built" <<endl;
    //cout << freqTable.size();
    /*
    clock_t startTime;
    
    startTime = clock();
    for (int i = 0; i < 1; i++) 
    {

        build_tree_using_binary_heap(freqTable,codeTable);
    }
    cout << "Time using binary heap (microsecond):  " << (clock() - startTime) /1<< endl;
    

    startTime = clock();
    for (int i = 0; i < 1; i++) 
    {
        build_tree_using_4way_heap(freqTable,codeTable);
    }

    cout << "Time using four way cache heap (microsecond):  " << (clock() - startTime) /1<< endl;
    
    
    startTime = clock();
    for (int i = 0; i < 1; i++) {
        build_tree_using_pairing_heap(freqTable,codeTable);
    }
    cout << "Time using pairing heap (microsecond):  " << (clock() - startTime) /1<< endl;
    //*/
    build_tree_using_pairing_heap(freqTable, codeTable);
    cout << "code table built"<< endl;
    ofstream outFile;
    outFile.open("code_table.txt", ios::out | ios::trunc);
    for (auto i = codeTable.begin(); i != codeTable.end(); i++) {
        //cout << i->first << " " << i->second << endl;
        outFile << i->first << " " << i->second << endl;
    }
    outFile.close();
    cout << "code table written" << endl;
    outFile.open("encode.bin", ios::out | ios::trunc | ios::binary);
    
    ifstream inFile;
    inFile.open(INPUT_FILE);
    string fileLine,temp;
    int t;
    temp = "";
    while (getline(inFile, fileLine))
    {
        t = std::stoi(fileLine);
        temp = temp+codeTable[t];
    }
    for (unsigned int j = 0; j < temp.length(); j=j + 8)
    {
        bitset<8> b(temp, j, 8);
        outFile << static_cast<uint_fast8_t>(b.to_ulong());
    }
    inFile.close();
    outFile.close();
    cout << "encoded binary file written" << endl;
    cout << "finish" << endl;
}