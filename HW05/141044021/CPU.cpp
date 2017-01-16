/* 
 * File:   CPU.cpp
 * Author: Emre Behadir 141044021
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:34
 */
#include <string>
#include "CPU.h"
#include "Memory.h"
#include <iomanip>// register yazdırırken  padding amacıyla ekledim setw(4)
#include <cstdlib>
int CPU::PC=0;

CPU::CPU(){
    
}

CPU::CPU(int option) {
   
    for (int i = 0; i < 5; i++) {
        registers[i]=0;
    } 
    PC=1;
    size=1;
    opinion=option;
}

void CPU::setSize(int totalLenght) {
    size=totalLenght;
}
int CPU::getSize() const{
    return size;
}
void CPU::setRegisters(int target, int newValue) {
    registers[target-1]=newValue;
}
int CPU::getRegisters(int target) const {
    return registers[target-1];
}
int CPU::getPC() const {
    return PC-1;
}
void CPU::setPC() {
    PC++;
}
void CPU::setPC(int jumpline) {
    PC=jumpline;
}
instruction CPU::getInst() const{
    return statement;
}
void CPU::setInst(instruction newInst){
    statement.opCode=newInst.opCode;
    statement.operandOne=newInst.operandOne;
    statement.operandTwo=newInst.operandTwo;
    statement.op1=newInst.op1;
    statement.op2=newInst.op2;
}
void CPU::setInst() {
    statement.opCode="";
    statement.operandOne="";
    statement.operandTwo="";
    statement.op1=0;
    statement.op2=0;
}

void CPU::print( Memory&  memory) const {
    if (opinion==1 || opinion==2) {
        cout <<statement.opCode <<" " <<setw(3)
             <<statement.operandOne<<","<<setw(3)
             <<statement.operandTwo<<endl;
        cout<<"CPU Register Values:"<<endl;
        for (int i = 0; i < 5; i++)
            cout <<"["<<i+1<<"] -> "<< getRegisters(i+1) << " "<<endl;
        cout<<"PC= "<<PC << endl;
        if(opinion==2){
            memory.printAll();
        }
        cout<< endl;
    }
    if(opinion==0 && statement.opCode=="HLT" ||
       opinion==1 && statement.opCode=="HLT"){
        cout << endl;
        cout<<"CPU Register Values:"<<endl;
        for (int i = 0; i < 5; i++)
           cout <<"["<<i+1<<"] -> "<< getRegisters(i+1)<< " "<<endl;
        cout<<"PC= "<<PC << endl << endl;
        memory.printAll();
    }
    
}
bool CPU::halted() const{
    return (PC >size) || (statement.opCode=="HLT");
}

void CPU::execute(const string instruction, Memory& memory) {
    setInst();
    determineStatement(instruction);
    
    if( statement.opCode == "MOV" ) 
        moveInstruction(memory);                                                  
    else if( statement.opCode == "ADD" )
        addInstruction(memory);                                                   
    else if ( statement.opCode =="SUB" ) 
        subtitionInstruction(memory);                                             
    else if( statement.opCode == "JMP" || statement.opCode == "JPN"   )
        jumpInstruction(memory);                                                  
    else if( statement.opCode == "PRN" ) 
        printInstruction(memory);
    
    print(memory);
}

void CPU::determineStatement(string lineStatement) {
    string instructArr[] = {"MOV", "ADD","SUB","JMP","PRN","HLT","JPN"};
    int intructArrSize=7;
    instruction temp;

    int commaSymbolindex=lineStatement.find_first_of(';');//yorum silindi
    if (commaSymbolindex != -1)
        lineStatement.erase(commaSymbolindex);

    for (int i = 0; i < lineStatement.size(); i++) {//Büyük harf dönüşümü
        if (lineStatement[i] >= 'a' && lineStatement[i] <='z'  ) {
            lineStatement[i] -= 'a' - 'A';
        }
    }
   
    int statementSize =lineStatement.size();//bosluklar gitti
    for (int i = 0; i < statementSize; i++) {
        int spaceChracterIndex=lineStatement.find_first_of(' ');
        if (spaceChracterIndex != -1)
            lineStatement.erase(spaceChracterIndex,1);
    }
    
    detectionStatementEror( lineStatement);//statementta hata varmı
                             
    for (int i = 0; i <intructArrSize ; i++) {//ınstruction bulur
        int instructFound =lineStatement.find(instructArr[i]);
        if ( instructFound != -1 ){
            if ( instructFound ==0) {
                temp.opCode= instructArr[i];
            } else {
                cout << "!! EROR line("<<getPC()<<")"
                <<" Unexpected symbols before instruction"<<endl;exit(-1);
            }
        } 
    }
    int comIndex=lineStatement.find(',');
    int lenthState=lineStatement.size();
    if (temp.opCode == "ADD"|| temp.opCode == "MOV" || temp.opCode == "SUB"){
         if (comIndex !=-1){
            temp.operandOne =lineStatement.substr(3,comIndex-3);//3char ınsrtuct
            temp.operandTwo =lineStatement.substr(comIndex+1,lenthState-comIndex-1);
         }else{
                cout << "!! EROR line("<<getPC()<<")"
                <<" Unsolved incruction operands."<<endl;exit(-1);             
         }
    } 
    else if (temp.opCode == "JMP" || temp.opCode == "JPN" ) {
        if (comIndex !=-1) {
            temp.operandOne =lineStatement.substr(3,comIndex-3);
            temp.operandTwo =lineStatement.substr(comIndex+1,lenthState-comIndex-1);
        } else {
            temp.operandOne =lineStatement.substr(3,lenthState);
            temp.operandTwo ="";
        }
    }
    else if (temp.opCode == "PRN") {
         if (comIndex !=-1) {
            temp.operandOne =lineStatement.substr(3,comIndex-3);
            temp.operandTwo =lineStatement.substr(comIndex+1,lenthState-comIndex-1);
        } else {
            temp.operandOne =lineStatement.substr(3,lenthState);
            temp.operandTwo ="";
        }
    }
    else if (temp.opCode == "HLT") {
        temp.operandOne ="";
        temp.operandTwo ="";
    } 
    detectionOperandEror( lineStatement,temp);

    setInst(temp);   
}
void CPU::detectionStatementEror(const string lineStatement) {
    string instructArr[] = {"MOV", "ADD","SUB","JMP","PRN","HLT","JPN"};
    int intructArrSize=7;
    //farklı karkterler olmsı
    for (int i = 0; i < lineStatement.size(); i++) {
        if ( !((lineStatement[i] >= 'A' && lineStatement[i] <='Z') ||
               (lineStatement[i] >= '0' && lineStatement[i] <='9') ||
                lineStatement[i] == ',' || lineStatement[i] == '-' ||
                lineStatement[i] == '#') ) {
            cout << "!!! EROR "<<PC <<":" <<i <<"  Unexpected Symbols (" 
                 <<lineStatement[i]<<")" <<endl;
            exit(-1);
        }
    }
    //Virgülün birden cok olması
    int occuranceComma=0;
    for (int i = 0; i < lineStatement.size(); i++) {
        if ( lineStatement[i] == ',')  
            occuranceComma++;
    }
    if (occuranceComma >1) 
       {cout << "!! EROR line("<<PC <<")"<<" There are too much comma symbols" 
                  <<endl;exit(-1);}
    //Virgülün yanlış yerde olması
    int improperComma=lineStatement.find(',');
    if (improperComma != -1 && improperComma<5) {//movr1 5 ckarakter
        cout << "!! EROR line("<<PC <<")"<<" Unexpected comma place"<<endl;
        exit(-1);
    }
    //Aynı yada farklı birden fazla instruction
    int occuranceInstruct=0;
    for (int i = 0; i <intructArrSize ; i++) {
        int instructFound =lineStatement.find(instructArr[i]);
        if ( instructFound != -1 ) //Dzinin içinde varsa
        {    
            occuranceInstruct++;
            int repeatInst=lineStatement.find(instructArr[i],instructFound+1);
            if (repeatInst != -1) // aynı addan ikitane olma durumu
                occuranceInstruct++;
        }
    }
    if ( occuranceInstruct == 0 ) 
        {cout << "!! EROR line("<<PC <<") There is no instruction"<<endl;
        exit(-1);}
    else if(occuranceInstruct >1)
        {cout << "!! EROR line("<<PC <<") There are more than one instruction"
              <<endl;
        exit(-1);}

}
void CPU::detectionOperandEror(const string lineStatement,instruction& temp) {
    solveOperand(temp);
    
    if (temp.opCode == "ADD"|| temp.opCode == "MOV" || temp.opCode == "SUB"){
        if (temp.operandOne=="" ||temp.operandTwo=="") {
           cout << "!! EROR line("<<PC <<") There are missing parameters." ;
           cout << endl;exit(-1);
        }
    }
    int op1err=0;int op1err1=0;
    int op2err=0;int op2err2=0;
    for (int i = 0; i < temp.operandOne.size(); i++) {
        if ( (temp.operandOne[i] >= 'A' && temp.operandOne[i] <='Z') ) 
                op1err++;
        if ( (temp.operandOne[i] >= 'A' && temp.operandOne[i] <='Z') && 
              temp.operandOne[i] !='R' ) 
                op1err1++;
    }
    for (int i = 0; i < temp.operandTwo.size(); i++) {
        if ( (temp.operandTwo[i] >= 'A' && temp.operandTwo[i] <='Z') ) 
                op2err++;
        if ( (temp.operandTwo[i] >= 'A' && temp.operandTwo[i] <='Z') && 
              temp.operandTwo[i] !='R' ) 
                op2err2++;        
    }
    if (temp.operandOne != "" && ( op1err>1 || op1err1>0 ) ) {// RR1,0R0R gibi durmlar
        cout << "!! EROR line("<<PC<<") This operand ("<<temp.operandOne<<
                ") is not proper."<<endl;exit(-1);
    }
    if (temp.operandTwo != "" && (op2err>1 || op2err2>0 ) ) {
        cout << "!! EROR line("<<PC<<") This operand ("<<temp.operandTwo<<
                ") is not proper."<<endl;exit(-1);
    }
    
    int dashChracterIndexop1=temp.operandOne.find_first_of('-');
    int dashChracterIndexop2=temp.operandTwo.find_first_of('-');//r-1 gibi
    if ( temp.operandOne != "" && dashChracterIndexop1 != -1 && op1err==1 ) {
        cout << "!! EROR line("<<PC<<") This operand ("<<temp.operandOne<<
                ") is not proper."<<endl;exit(-1);
    }
    if (temp.operandTwo != "" && dashChracterIndexop2 != -1 && op2err==1 ) {
        cout << "!! EROR line("<<PC<<") This operand ("<<temp.operandTwo<<
                ") is not proper."<<endl;exit(-1);
    }
    op1err=temp.operandOne.find_first_of('R');
    op2err=temp.operandTwo.find_first_of('R');//R nin farklı yerlerde olması
    if ( (op1err!=-1 && temp.operandOne[0]!='R' ) ||
         (op2err!=-1 && temp.operandTwo[0]!='R') ) {
        cout << "!! EROR line("<<PC<<") This operand ";
        if (op1err>0) 
            cout <<"("<<temp.operandOne<<") ";
        else if (op2err>0) 
            cout <<"("<< temp.operandTwo<<") ";        
        cout <<"is not proper." << endl;
        exit(-1);
    }
    if ( (dashChracterIndexop1 != -1 && dashChracterIndexop1 != 0) ||
         (dashChracterIndexop2 != -1 && dashChracterIndexop2 != 0) ) {
        cout << "!! EROR line("<<PC<<") This operand ";
        if (dashChracterIndexop1 != -1) 
            cout <<"("<<temp.operandOne<<") ";
        if (dashChracterIndexop2 != -1) 
            cout <<"("<< temp.operandTwo<<") ";        
        cout <<"is not proper."  << endl;
        exit(-1);
    }
    int sharpCharIndexop1=temp.operandOne.find_first_of('#');//1#
    int sharpCharIndexop2=temp.operandTwo.find_first_of('#');
        if ( (sharpCharIndexop1 != -1 && sharpCharIndexop1 != 0) ||
             (sharpCharIndexop2 != -1 && sharpCharIndexop2 != 0) ) {
        cout << "!! EROR line("<<PC<<") This operand ";
        if (sharpCharIndexop1 != -1) 
            cout <<"("<<temp.operandOne<<") ";
        if (sharpCharIndexop2 != -1) 
            cout <<"("<< temp.operandTwo<<") ";        
        cout <<"is not proper."  << endl;
        exit(-1);
    }
    sharpCharIndexop1=0;sharpCharIndexop2=0;
    for (int i = 0; i < temp.operandOne.size(); i++) {
        if ( (temp.operandOne[i] == '#' ) ) 
                sharpCharIndexop1++;     
    }
    for (int i = 0; i < temp.operandTwo.size(); i++) {
        if ( (temp.operandTwo[i] == '#') ) 
                sharpCharIndexop2++;        
    }
    if (temp.operandOne != "" && sharpCharIndexop1>1 ) {// ##1,0#0# gibi durmlar
        cout << "!! EROR line("<<PC<<") This operand ("<<temp.operandOne<<
                ") is not proper."<<endl;exit(-1);
    }
    if (temp.operandTwo != "" && sharpCharIndexop2>1 ) {
        cout << "!! EROR line("<<PC<<") This operand ("<<temp.operandTwo<<
                ") is not proper."<<endl;exit(-1);
    }
    
    if ( temp.operandOne[0] == 'R' && ( temp.op1<1 || temp.op1>5 ) ) 
        {cout << "!! EROR line("<<PC <<") You don't have "<<temp.operandOne
                <<" register."<<endl;exit(-1);}
    if ( temp.operandTwo[0] == 'R' && ( temp.op2<1 || temp.op2>5 ) ) 
        {cout << "!! EROR line("<<PC <<") You don't have "<<temp.operandTwo
                <<" register."<<endl;exit(-1);}
    if ( temp.operandOne[0] == '#' && ( temp.op1<0 || temp.op1>49 ) ) 
        {cout << "!! EROR line("<<PC <<") You don't have "<<temp.operandOne
                <<" memory."<<endl;exit(-1);}
    if ( temp.operandTwo[0] == '#' && ( temp.op2<0 || temp.op2>49 ) ) 
        {cout << "!! EROR line("<<PC <<") You don't have "<<temp.operandTwo
                <<" memory."<<endl;exit(-1);}
    if ( temp.opCode == "JMP"  && ( temp.op1<=0  ) ) 
        {cout<< "!! EROR line("<<PC <<") You don't jump to "<<temp.operandOne
                <<" line."<<endl;exit(-1);}    
    int hltInstruct =lineStatement.find("HLT");
    if (hltInstruct!=-1 && lineStatement.size()>3) {
        cout << "!! EROR line("<<PC <<") Improper HLT instruction"<<endl;
        exit(-1);
    }

}

bool CPU::addInstruction(Memory& memory) {
    if (statement.operandOne[0]=='R'){
        if(statement.operandTwo[0]=='R')//register1 add register2(RR)
            {setRegisters(getInst().op1,getRegisters(getInst().op1) +getRegisters(getInst().op2));return true;}
        else if(statement.operandTwo[0]=='#')////register1 add adress(R#)
            {setRegisters(getInst().op1,getRegisters(getInst().op1) +memory.getMem(getInst().op2));return true;}
        else//register1 add constant(RC)
            {setRegisters(getInst().op1,getRegisters(getInst().op1) + getInst().op2);return true;}
    }
    return false;
}
bool CPU::jumpInstruction(Memory& memory) {
    if ( (statement.operandOne[0]=='R' && getRegisters(getInst().op1) == 0) ||
         (statement.opCode=="JPN" && getRegisters(getInst().op1) <= 0)  )
        { setPC(getInst().op2);return true;}
    else if(statement.operandTwo=="")//constant line
        { setPC(getInst().op1);return true;}
    return false;
}
bool CPU::moveInstruction(Memory& memory) {
    //RR R# RC -  #R #C
    if (statement.operandOne[0]=='R'){
        if (statement.operandTwo[0]=='R')//register1 to register2(RR) 
            {setRegisters(getInst().op2,getRegisters(getInst().op1) );return true;}
        else if (statement.operandTwo[0]=='#')//register1 to adress(R#)
            {memory.setMem(getInst().op2,getRegisters(getInst().op1) );return true;}
        else//constant to register (RC)
            {setRegisters(getInst().op1,getInst().op2 );return true;}
    }
    else if (statement.operandOne[0]=='#'){
        if (statement.operandTwo[0]=='R')//adress to register2(#R)
            {setRegisters(getInst().op2 ,memory.getMem(getInst().op1));}
        else//constant to adress (#C)
            {memory.setMem(getInst().op1,getInst().op2);return true;}
    }

    return false;
}
bool CPU::printInstruction(Memory& memory) {
    if (statement.operandOne[0]=='R')//register
        {cout << "R" << getInst().op1<< " = " << getRegisters(getInst().op1) << endl;
         return true;}
    else if(statement.operandOne[0]=='#')
        {cout <<"["<<getInst().op1<<"]"<<"-> "<<memory.getMem(getInst().op1) 
              << endl; return true;}
    else //constant 
        {cout << "Constant"<< " = " <<  getInst().op1<< endl ;return true;}
    return false;
}
bool CPU::subtitionInstruction(Memory& memory) {
    if (statement.operandOne[0]=='R'){
        if(statement.operandTwo[0]=='R')//register1 sub register2(RR)
            {setRegisters(getInst().op1,getRegisters(getInst().op1) - 
                                        getRegisters(getInst().op2));
            return true;}
        else if(statement.operandTwo[0]=='#')//register1 sub adress(R#)
            {setRegisters(getInst().op1,getRegisters(getInst().op1) - 
                                        memory.getMem(getInst().op2));
            return true;}
        else//register1 sub register2(RC)
            {setRegisters(getInst().op1,getRegisters(getInst().op1)-getInst().op2);return true;}
    }
    return false;
}
void CPU::solveOperand(instruction& variable) {
    int size=variable.operandOne.size();
        int tempnum=0;
        int i=0;
        if (variable.operandOne[0] == '-' || variable.operandOne[0] == 'R' ||
            variable.operandOne[0] == '#' )
            i++;  
        for (; i<size; i++) 
            tempnum = 10*tempnum + variable.operandOne[i] -48;
        if (variable.operandOne[0] == '-')
            variable.op1=tempnum*(-1); 
        else
            variable.op1=tempnum;         

        size=variable.operandTwo.size();
        tempnum=0;
        i=0;
        if (variable.operandTwo[0] == '-' || variable.operandTwo[0] == 'R' ||
            variable.operandTwo[0] == '#')
            i++;  
        for (; i<size; i++) 
            tempnum = 10*tempnum + variable.operandTwo[i] -48;
        if (variable.operandTwo[0] == '-')
            variable.op2=tempnum*(-1); 
        else
            variable.op2=tempnum; 
}


