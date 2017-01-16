/* 
 * File:   CPUProgram.cpp
 * Author: Emre Behadir 141044021
 * 
 * Created on 19 Ekim 2016 Çarşamba, 10:28
 */

#include "CPUProgram.h"
#include <fstream>
#include <cstdlib>
using namespace std;
CPUProgram::CPUProgram(char* filename) {

    totalLine=1;    
    ReadFile(filename);
}

void CPUProgram::ReadFile(char* filename) {
    fstream instructionFile;
    instructionFile.open(filename);
    string lineStatement;
    if (!instructionFile){
        cout << "File is not opened."<<endl;exit(-1);
    }
    instruction.push_back("");
    while( getline(instructionFile,lineStatement) ){    
        instruction.push_back(lineStatement);   
        totalLine++;
    }
    totalLine--;//Döngü fazlalıgı
    instructionFile.close();
}

string CPUProgram::getLine(int line) const {   
    return instruction[line];
}
int CPUProgram::size() const {
    return totalLine;
}



