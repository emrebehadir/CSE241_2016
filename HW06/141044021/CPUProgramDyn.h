/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgramDyn.h
 * Author: testbhdr
 *
 * Created on 27 Kasım 2016 Pazar, 20:48
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H

#include "instruction.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

namespace CPUProgramDynSpace
{
        
    class CPUProgramDyn {
    public:
        CPUProgramDyn();
        CPUProgramDyn(const CPUProgramDyn& orig);
        CPUProgramDyn& operator =(const CPUProgramDyn& rightSide);

        CPUProgramDyn(const CPUProgramDyn& test  ,string line);
        CPUProgramDyn(const CPUProgramDyn& ob1  ,const CPUProgramDyn& ob2);

        CPUProgramDyn(int option);

        void   ReadFile(const char* filename);
        string getLine(int line)const;
        void addElement(string newElement);
        void rescaleCapacity(int newCapaciy);
        int  size()const;
        int  instructSize()const { return used-1;}
        void setOption(int option);
        int  getOption() const;
        int GetUsed() const { return used; }
        int GetCapacity() const { return capacity; }
        const string operator[] (const int index) const;
        CPUProgramDyn operator+(const string& line);
        CPUProgramDyn operator+(const CPUProgramDyn& other);
        CPUProgramDyn& operator+=(const string& other);
        bool operator >(const CPUProgramDyn& other);
        bool operator <(const CPUProgramDyn& other);
        bool operator >=(const CPUProgramDyn& other);
        bool operator <=(const CPUProgramDyn& other);
        bool operator ==(const CPUProgramDyn& other);
        bool operator !=(const CPUProgramDyn& other);
        CPUProgramDyn operator ()(int start,int stop);
        CPUProgramDyn operator--();
        CPUProgramDyn operator--(int); // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Incle


        friend ostream& operator <<(ostream& outStream, const CPUProgramDyn& obj);

        ~CPUProgramDyn();

    private:
        string* instruction;
        int totalLine;
        int option;
        int capacity;
        int used;    
    };
    
}

#endif /* CPUPROGRAMDYN_H */

