/* 
 * File:   main.cpp
 * Author: Emre Behadir 141044021
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:34
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
#include "CPUProgramDyn.h"



class Computer {
public:
    Computer(CPU myCPU,CPUProgram myCPUProgram,Memory myMemory,int option);
    Computer(int option);
    void execute();
    void setMemory(Memory myMemory);
    Memory getMemory() const;
    void setCPUProgram(CPUProgram myCPUprogram);
    CPUProgram getCPUProgram() const;
    void setCPU(CPU myCPU);
    CPU getCPU() const;
    void setOption(int option);
    int getOption() const;
private:
    CPU myCPU;
    CPUProgram myCPUProgram;
    Memory myMemory;
    int option;
};

#endif /* COMPUTER_H */

