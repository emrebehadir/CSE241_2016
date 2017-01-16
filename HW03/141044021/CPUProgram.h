/* 
 * File:   CPUProgram.h
 * Author: Emre Behadir 141044021
 *
 * Created on 19 Ekim 2016 Çarşamba, 10:28
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class CPUProgram {
public:
    CPUProgram(char* filename);
    void ReadFile(char* filename);
    string getLine(int line)const;
    int size()const;
private:
    vector<string> instruction;
    int totalLine;
};

#endif /* CPUPROGRAM_H */

