/* 
 * File:   CPU.h
 * Author: Emre Behadir 141044021
 *
 * Created on 19 Ekim 2016 Çarşamba, 10:29
 */

#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
using namespace std;
#include "instruction.h"
/*struct instruction {
    string opCode;
    string operandOne;
    string operandTwo;
    int op1;
    int op2;
};*/

class CPU {
public:
    CPU(char* option);
    void setRegisters(int target, int newValue);
    int  getRegisters(int target) const;
    instruction  getInst() const;
    void  setInst(instruction newInst);
    void  setInst();
    int  getSize()const;
    int  getPC() const;
    void setPC();
    void setPC(int jumpline);
    void setSize(int totalLenght);
    void print() const;
    bool halted() const;
    
    void execute(const string instruction);
    void determineStatement(string lineStatement);
    void detectionStatementEror(const string lineStatement);
    void detectionOperandEror(const string lineStatement,instruction& temp);
    bool moveInstruction();
    bool printInstruction();
    bool subtitionInstruction();
    bool addInstruction();
    bool jumpInstruction();
   
    void solveOperand(instruction& variable);


private:
    instruction statement;
    int registers[5];
    static int PC;
    int size;
    char opinion;
};

#endif /* CPU_H */

