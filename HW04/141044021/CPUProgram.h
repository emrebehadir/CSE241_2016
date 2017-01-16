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
    CPUProgram(const char* filename);
    CPUProgram(int option);
    CPUProgram();
    void ReadFile(const char* filename);
    string getLine(int line)const;
    int size()const;
    void setOption(int option);
    int getOption() const;
private:
    vector<string> instruction;
    int totalLine;
    int option;
};

#endif /* CPUPROGRAM_H */

