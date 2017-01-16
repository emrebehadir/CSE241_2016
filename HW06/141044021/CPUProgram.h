/* 
 * File:   CPUProgram.h
 * Author: Emre Behadir 141044021
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:34
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CPUProgram {
public:
    CPUProgram(const CPUProgram& test  ,string line);
    CPUProgram(const CPUProgram& ob1  ,const CPUProgram& ob2);
    CPUProgram(int option);
    CPUProgram();
    void ReadFile(const char* filename);
    string getLine(int line)const;
    int size()const;
    void setOption(int option);
    int getOption() const;
    const string& operator[] (const int index) const;
    CPUProgram operator+(const string& line);
    CPUProgram operator+(const CPUProgram& other);
    CPUProgram& operator+=(const string& other);
    bool operator >(const CPUProgram& other);
    bool operator <(const CPUProgram& other);
    bool operator >=(const CPUProgram& other);
    bool operator <=(const CPUProgram& other);
    bool operator ==(const CPUProgram& other);
    bool operator !=(const CPUProgram& other);
    CPUProgram operator ()(int start,int stop);
    CPUProgram operator--();
    CPUProgram operator--(int);
    
    friend ostream& operator <<(ostream& outStream, const CPUProgram& obj);
private:
    vector<string> instruction;
    int totalLine;
    int option;
};

#endif /* CPUPROGRAM_H */

