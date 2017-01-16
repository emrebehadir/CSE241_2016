/* 
 * File:   instruction.h
 * Author: Emre Behadir 141044021
 *
 * Created on 23 Ekim 2016 Pazar, 11:10
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
using namespace std;

//Bu class getline ile gelen satır pars edildikten sonra opcode operand gibi 
//verileri daha verimli kullanmak amacıyla yazılmıştır.
class instruction {
public:
    instruction();
    string opCode;
    string operandOne;
    string operandTwo;
    int op1;
    int op2;
private:

};

#endif /* INSTRUCTION_H */

