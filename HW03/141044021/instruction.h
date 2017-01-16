/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

