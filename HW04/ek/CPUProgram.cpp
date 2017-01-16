/* 
 * File:   CPUProgram.cpp
 * Author: Emre Behadir 141044021
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:34
 */

#include "CPUProgram.h"
#include <fstream>
#include <cstdlib>
using namespace std;

CPUProgram::CPUProgram(){
    
}
CPUProgram::CPUProgram(const char* filename) {
    totalLine=1;    
    ReadFile(filename);
}
CPUProgram::CPUProgram(int option){
    totalLine=1;
    setOption(option);
}

void CPUProgram::ReadFile(const char* filename) {
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
void CPUProgram::setOption(int option) {
    this->option = option;
}
int CPUProgram::getOption() const {
    return option;
}



