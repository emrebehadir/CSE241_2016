/* 
 * File:   CPU.h
 * Author: Emre Behadir 141044021
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:34
 */

#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
using namespace std;
#include "Memory.h"
#include "instruction.h"
/* instruction { memberlerini iceren bir class
    string opCode;
    string operandOne;
    string operandTwo;
    int op1;
    int op2;
};*/

class CPU {
public:
    CPU();
    CPU(int option);
    void setRegisters(int target, int newValue);
    int  getRegisters(int target) const;
    instruction  getInst() const;
    void setInst(instruction newInst);
    void setInst();
    int  getSize()const;
    int  getPC() const;
    void setPC();
    void setPC(int jumpline);
    void setSize(int totalLenght);
    void print( Memory&  memory) const;
    bool halted() const;
    //Hangi instructionun calısacağına karar verir.
    void execute(const string instruction, Memory& memory);
    //Satırıdaki opcode operandlarıbulur ve  ayırır.
    void determineStatement(string lineStatement);
    //Stament taki hataları bulur
    void detectionStatementEror(const string lineStatement);
    //operanlardaki hataları bulur
    void detectionOperandEror(const string lineStatement,instruction& temp);
    //Instruction fonksiyonları
    bool moveInstruction(Memory& memory);
    bool printInstruction(Memory& memory);
    bool subtitionInstruction(Memory& memory);
    bool addInstruction(Memory& memory);
    bool jumpInstruction(Memory& memory);
    //Operanların hangi int degere karşılık geldigini bulur.
    //Instructiondaki op1 ve op2 değerlerine atar.
    void solveOperand(instruction& variable);

private:
    instruction statement;
    int registers[5];
    static int PC;
    int size;
    int opinion;
};

#endif /* CPU_H */

