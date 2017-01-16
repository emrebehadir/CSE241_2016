/* 
 * File:   CPUProgram.cpp
 * Author: Emre Behadir 141044021
 *
 * Created on 14 Kasım 2016 Pazartesi, 14:34
 */

#include "CPUProgram.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

CPUProgram::CPUProgram(){
    
}

CPUProgram::CPUProgram(int option){
    totalLine=0;
    setOption(option);
}

CPUProgram::CPUProgram(const CPUProgram& test, string line) {
    for (int i = 0; i < test.size(); i++) 
        instruction.push_back(test.instruction[i]);

    instruction.push_back(line); 
    totalLine = test.size() ;
}
CPUProgram::CPUProgram(const CPUProgram& ob1,const CPUProgram& ob2){
    for (int i = 0; i < ob1.size(); i++) 
        instruction.push_back(ob1.instruction[i]);
    for (int i = 0; i < ob2.size(); i++) 
        instruction.push_back(ob2.instruction[i]);
    totalLine=ob1.size()+ob2.size();
    option=ob1.option;
}


void CPUProgram::ReadFile(const char* filename) {
    fstream instructionFile;
    instructionFile.open(filename);
    string lineStatement;
    totalLine=0;
    if (!instructionFile){
        cout << "File is not opened."<<endl;exit(-1);
    }
    
    while( getline(instructionFile,lineStatement) ){    
        instruction.push_back(lineStatement);   
    }
    totalLine=instruction.size();
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

const string& CPUProgram::operator[](const int index) const {
    if(index<0 || index>instruction.size()){
        cout << "Invail index!!"<< endl;
        exit(-1);
    }
    if(index ==0 )
        return instruction[index];
        
    return instruction[index-1];
}

CPUProgram CPUProgram::operator +(const string& line) { 
    return CPUProgram(*this,line);
}

CPUProgram CPUProgram::operator +(const CPUProgram& other){
    return CPUProgram(*this,other);
}

CPUProgram& CPUProgram::operator+=(const string& other) {
    instruction.push_back(other); 
    totalLine++;
    return *this;
}


bool CPUProgram::operator>(const CPUProgram& other) {
    return totalLine>other.totalLine ;
}

bool CPUProgram::operator<(const CPUProgram& other) {
    return totalLine<other.totalLine ;
}

bool CPUProgram::operator<=(const CPUProgram& other) {
    return  (*this<other || *this==other);
}

bool CPUProgram::operator>=(const CPUProgram& other) {
    return  (*this>other || *this==other);
}

bool CPUProgram::operator!=(const CPUProgram& other) {
    return !(*this==other);
}

bool CPUProgram::operator==(const CPUProgram& other) {
    return totalLine==other.totalLine;
}

CPUProgram CPUProgram::operator()(int start, int stop) {
    CPUProgram temp;
    for (int i = start; i <= stop; i++) 
        temp.instruction.push_back(instruction[i]);
    temp.totalLine=stop-start;
    return temp;
}

CPUProgram CPUProgram::operator--() {
    instruction.pop_back();
    return *this;
}

CPUProgram CPUProgram::operator--(int) {
    instruction.pop_back();
    return *this;
}

ostream& operator <<(ostream& outStream, const CPUProgram& obj){
    for (int i = 0; i < obj.size(); i++) {
        outStream<<obj.instruction[i]<<endl;
    }
    return outStream;
}