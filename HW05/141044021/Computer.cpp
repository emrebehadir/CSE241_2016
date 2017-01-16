/* 
 * File:   Computer.cpp
 * Author: Emre Behadir 141044021
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:34
 */

#include "Computer.h"

Computer::Computer(CPU myCPU,CPUProgram myCPUProgram,Memory myMemory,int option){
    setCPU(myCPU);
    setCPUProgram(myCPUProgram);
    setMemory(myMemory);
    setOption(option);
}
Computer::Computer(int option) {
    setOption(option);
}

void Computer::execute() {
  
    myCPU.setSize(myCPUProgram.size());
    
    while(!myCPU.halted()){
        int tempCounter=myCPU.getPC();
        string instruction = myCPUProgram.getLine(myCPU.getPC());
        myCPU.execute(instruction, myMemory);
        
        if(tempCounter==myCPU.getPC())
            myCPU.setPC();
    }
    if (myCPU.getInst().opCode != "HLT") {
         cout <<"!! EROR : Program is not ended with halt insruction." << endl
              << endl;
    }
}

void Computer::setMemory(Memory myMemory) {
    this->myMemory = myMemory;
}
Memory Computer::getMemory() const {
    return myMemory;
}
void Computer::setCPUProgram(CPUProgram myCPUprogram) {
    this->myCPUProgram = myCPUprogram;
}
CPUProgram Computer::getCPUProgram() const {
    return myCPUProgram;
}
void Computer::setCPU(CPU myCPU) {
    this->myCPU = myCPU;
}
CPU Computer::getCPU() const {
    return myCPU;
}
void Computer::setOption(int option) {
    this->option = option;
}
int Computer::getOption() const {
    return option;
}



