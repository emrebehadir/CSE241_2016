/* 
 * File:   main.cpp
 * Author: Emre Behadir 141044021
 *
 * Created on 17 Ekim 2016 Pazartesi, 14:34
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

int main(int argc, char** argv) {
    
    CPU myCPU(argv[2]);
    CPUProgram myProg(argv[1]);
    
    myCPU.setSize(myProg.size());
    
    while(!myCPU.halted()){
        int tempCounter=myCPU.getPC();
        string instruction = myProg.getLine(myCPU.getPC());
        myCPU.execute(instruction);
        myCPU.print();
        if(tempCounter==myCPU.getPC())
            myCPU.setPC();
    }

    return 0;
}

