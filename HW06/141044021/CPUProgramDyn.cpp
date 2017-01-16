/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgramDyn.cpp
 * Author: testbhdr
 * 
 * Created on 27 Kasım 2016 Pazar, 20:48
 */

#include "CPUProgramDyn.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

namespace CPUProgramDynSpace 
{
    
CPUProgramDyn::CPUProgramDyn() : capacity(30), used(0), totalLine(1) ,option(0) {
	string* instruction = new string[capacity];
}

CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& orig)
: capacity(orig.GetCapacity()), used(orig.GetUsed())  {
	instruction = new string[capacity];
	for (int i = 0; i < used; ++i)
		instruction[i] = orig.instruction[i];
}

CPUProgramDyn& CPUProgramDyn::operator=(const CPUProgramDyn& rightSide) {
    if (capacity != rightSide.capacity) {
        delete [] instruction;
        instruction = new string[rightSide.capacity];
    }

    capacity = rightSide.capacity;
    used = rightSide.used;
    for (int i = 0; i < used; i++)
        instruction[i] = rightSide.instruction[i];

    return *this;
}

CPUProgramDyn::CPUProgramDyn(int option): 
 capacity(30), used(0), totalLine(1) ,option(0){
    instruction = new string[capacity];
    setOption(option);
}

void CPUProgramDyn::rescaleCapacity(int newCapaciy) {

    capacity = newCapaciy; // dikkat
    string* newArr = new string[capacity];

    for (int i = 0; i < used; i++)
        newArr[i] = instruction[i];

    delete [] instruction;

    instruction = newArr;
   

}

void CPUProgramDyn::addElement(string newElement) {
    if (used >= capacity) {
        rescaleCapacity(capacity*2+1);
    }
   
    instruction[used] = newElement;
    used++;
}

CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& test, string line) {
    capacity=test.capacity;
    instruction = new string[capacity];
    for (int i = 0; i < test.size(); i++) 
        addElement(test.instruction[i]);//instruction.push_back(test.instruction[i]);
    

    addElement(line);//instruction.push_back(line); 
    option= test.option;
    totalLine = test.size()  ;   
}
CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& ob1  ,const CPUProgramDyn& ob2){
    totalLine=1;
    capacity=ob1.capacity + ob2.capacity;
    instruction = new string[capacity];
    used=0;
    for (int i = 0; i < ob1.size(); i++) 
        addElement(ob1.instruction[i]);//instruction.push_back(ob1.instruction[i]);
    for (int i = 0; i < ob2.size(); i++) 
        addElement(ob2.instruction[i]);//instruction.push_back(ob2.instruction[i]);
    totalLine=ob1.size()+ob2.size()  ;
    option=ob1.option;  
}

void CPUProgramDyn::ReadFile(const char* filename) {
    fstream instructionFile;
    instructionFile.open(filename);
    string lineStatement;
    capacity = 30;
    totalLine=1;
    used=0;
    if (!instructionFile){
        cout << "File is not opened."<<endl;exit(-1);
    }
    
    while( getline(instructionFile,lineStatement) ){    
        addElement(lineStatement);//instruction.push_back(lineStatement);   
    }
    totalLine=instructSize() +1 ;
    instructionFile.close();
}

string CPUProgramDyn::getLine(int line) const {
    return instruction[line];
}

int CPUProgramDyn::getOption() const {
    return option;
}

bool CPUProgramDyn::operator!=(const CPUProgramDyn& other) {
    return !(*this==other);
}

CPUProgramDyn CPUProgramDyn::operator()(int start, int stop) {
    CPUProgramDyn temp;
    if (start>stop) {
        cout << "Invaild index range !!!"<<endl;
        return temp;
    }
    temp.instruction = new string[capacity];
    for (int i = start; i <= stop; i++) 
        temp.addElement(instruction[i]);//temp.instruction.push_back(instruction[i]);
    
    temp.totalLine=stop-start;
    temp.option=this->option;
    return temp;
}

CPUProgramDyn CPUProgramDyn::operator+(const string& line) {

    return CPUProgramDyn(*this,line);
}

CPUProgramDyn CPUProgramDyn::operator+(const CPUProgramDyn& other){
    if (other.instructSize()<=0) {
        cout << "You dont append empty cpu program !!"<<endl;
        return *this;
    }
    return CPUProgramDyn(*this,other);
}

CPUProgramDyn& CPUProgramDyn::operator+=(const string& other) {
    if (other.size()<=0) {
        cout << "You dont append empy instructon !!"<<endl;
        return *this;
    }

    addElement(other);//instruction.push_back(other); 
    totalLine++;
    return *this;
}

bool CPUProgramDyn::operator<(const CPUProgramDyn& other) {
    return totalLine<other.totalLine ;
}

CPUProgramDyn CPUProgramDyn::operator--(int) {
    used--;
    return *this;
}

CPUProgramDyn CPUProgramDyn::operator--() {
    used--;
    return *this;
}

bool CPUProgramDyn::operator<=(const CPUProgramDyn& other) {
    return  (*this<other || *this==other);
}

bool CPUProgramDyn::operator==(const CPUProgramDyn& other) {
    return totalLine==other.totalLine;
}

bool CPUProgramDyn::operator>(const CPUProgramDyn& other) {
    return totalLine>other.totalLine ;
}

bool CPUProgramDyn::operator>=(const CPUProgramDyn& other) {
    return  (*this>other || *this==other);
}

const string CPUProgramDyn::operator[](const int index) const {
    if(index < 0 || index > instructSize()){
        cout << "Invaild index!!"<< endl;
        return "";
    }
    if(index ==0 )
        return instruction[index];
        
    return instruction[index];
}

void CPUProgramDyn::setOption(int option) {
    this->option = option;
}

int CPUProgramDyn::size() const {
    return totalLine;
}

ostream& operator <<(ostream& outStream, const CPUProgramDyn& obj){
    for (int i = 0; i < obj.size(); i++) {
        outStream<<obj.instruction[i]<<endl;
    }
    return outStream;
}

CPUProgramDyn::~CPUProgramDyn() {
    delete [] instruction;
}

}