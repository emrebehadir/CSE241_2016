#include <iostream>
#include <string>
#include <fstream>
using namespace std;

typedef struct  {
    string opCode;
    string operandOne;
    string operandTwo;
}instruction;

int simulateCpuProgram(char* filename,char* option);
//Dosyadan satır satır okuyarak diziye aktaırır
bool readInstructionStatement(instruction* statement,char* filename,int* line);
//Satırı bulur opcode operand larını ayırır
bool determineStatement(string lineStatement,instruction* temp,int line);
//Stament taki hataları bulur
bool detectionStatementEror(string lineStatement,int line);
//operanddaki hataları bulur
bool detectionOperandEror(string lineStatement,int line,instruction* temp);
//Hangi instructionun calısacağına karar verir
bool runInstructionStatement(instruction statement,int* registers,int* jmplne);
//Instruction fonksiyonları
bool moveInstruction(instruction* statement,int* registers);
bool printInstruction(instruction* statement,int* registers);
bool subtitionInstruction(instruction* statement,int* registers);
bool addInstruction(instruction* statement,int* registers);
bool jumpInstruction(instruction* statement,int* registers,int* jmplne);
//Operandın hangi int degere karşılık geldigini bulur
void solveOperand(instruction* statement,int* op1,int*op2);

int main(int argc, char** argv) {
                  
    simulateCpuProgram(argv[1],argv[2]);
    return 0;
}

int simulateCpuProgram(char* filename,char* option){ 

    int         registers[5];
    int         cursorLine=1;
    int         totalLine=1;
    instruction statement[256];// Dosyanın enfazla 256 olacağını varsaydım.
    
    registers[0]=0;registers[1]=0;registers[2]=0;registers[3]=0;registers[4]=0;

    if(!readInstructionStatement(statement,filename,&totalLine))
        {cout <<endl;return false;}

    while (statement[cursorLine].opCode != "HLT" && cursorLine<=totalLine) 
    {  int templine=cursorLine;                                          
       if(runInstructionStatement(statement[cursorLine],registers,&cursorLine)){
            if (*option =='1') {
                cout << statement[templine].opCode <<" "
                            <<statement[templine].operandOne<<","
                            <<statement[templine].operandTwo<<"-";
                for (int i = 0; i < 5; i++)
                    cout <<"R" <<i+1 << "=" << registers[i]<< " ";
                cout << endl;
            }
       }
        if(cursorLine==templine)
            cursorLine++;
    }
    
    if (statement[cursorLine].opCode == "HLT") {
        cout <<endl;
        for (int i = 0; i < 5; i++){
                cout <<"R" <<i+1 << "=" << registers[i];
                if (i<4)
                    cout<<",";
        }        
        cout << endl;
    } else 
        cout <<"!! EROR : Program is not ended with halt insruction." << endl;
    
    cout << endl << endl;
    return 0;
}

bool readInstructionStatement(instruction* statement,char* filename,int* line){ 
    
    fstream instructionFile;
    instructionFile.open(filename);
    string lineStatement;
    instruction tempInst;
    while( getline(instructionFile,lineStatement) )
    {    
        if(determineStatement(lineStatement,&tempInst,(*line))){
           statement[(*line)]=tempInst;
           (*line)++;
        }
        else{
            return false;
        }
    }
    instructionFile.close();
    return true;
}
bool determineStatement(string lineStatement,instruction* temp,int line){
    
    string instructArr[] = {"MOV", "ADD","SUB","JMP","PRN","HLT" };
    int intructArrSize=6;
    
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
    
    if (!detectionStatementEror( lineStatement,line))//statementta hata varmı
        {return false;}                              //yokmu

    for (int i = 0; i <intructArrSize ; i++) {//ınstruction bulur
        int instructFound =lineStatement.find(instructArr[i]);
        if ( instructFound != -1 ){
            if ( instructFound ==0) {
                temp->opCode= instructArr[i];
            } else {
                cout << "!! EROR line("<<line <<")"
                <<" Unexpected symbols before instruction"<<endl;return false;
            }
        } 
    }
    int comIndex=lineStatement.find(',');
    int lenthState=lineStatement.size();
    if (temp->opCode == "ADD"|| temp->opCode == "MOV" || temp->opCode == "SUB"){
         if (comIndex !=-1){
            temp->operandOne =lineStatement.substr(3,comIndex-3);//3char ınsrtuct
            temp->operandTwo =lineStatement.substr(comIndex+1,lenthState-comIndex-1);
         }else{
                cout << "!! EROR line("<<line <<")"
                <<" Unsolved incruction operands."<<endl;return false;             
         }
    } 
    else if (temp->opCode == "JMP") {
        if (comIndex !=-1) {
            temp->operandOne =lineStatement.substr(3,comIndex-3);
            temp->operandTwo =lineStatement.substr(comIndex+1,lenthState-comIndex-1);
        } else {
            temp->operandOne =lineStatement.substr(3,lenthState);
            temp->operandTwo ="";
        }
    }
    else if (temp->opCode == "PRN") {
         if (comIndex !=-1) {
            temp->operandOne =lineStatement.substr(3,comIndex-3);
            temp->operandTwo =lineStatement.substr(comIndex+1,lenthState-comIndex-1);
        } else {
            temp->operandOne =lineStatement.substr(3,lenthState);
            temp->operandTwo ="";
        }
    }
    else if (temp->opCode == "HLT") {
        temp->operandOne ="";
        temp->operandTwo ="";
    } 
    if (!detectionOperandEror( lineStatement, line, temp))
        return false;
        
    return true;
}
bool detectionStatementEror(string lineStatement,int line){
    string instructArr[] = {"MOV", "ADD","SUB","JMP","PRN","HLT" };
    int intructArrSize=6;
    //farklı karkterler olmsı
    for (int i = 0; i < lineStatement.size(); i++) {
        if ( !((lineStatement[i] >= 'A' && lineStatement[i] <='Z') ||
               (lineStatement[i] >= '0' && lineStatement[i] <='9') ||
                lineStatement[i] == ',' || lineStatement[i] == '-')  ) {
            cout << "!!! EROR "<<line <<":" <<i <<"  Unexpected Symbols (" 
                 <<lineStatement[i]<<")" <<endl;
            return false;
        }
    }
    //Virgülün birden cok olması
    int occuranceComma=0;
    for (int i = 0; i < lineStatement.size(); i++) {
        if ( lineStatement[i] == ',')  
            occuranceComma++;
    }
    if (occuranceComma >1) 
       {cout << "!! EROR line("<<line <<")"<<" There are too much comma symbols" 
                  <<endl;return false;}
    //Virgülün yanlış yerde olması
    int improperComma=lineStatement.find(',');
    if (improperComma != -1 && improperComma<5) {//movr1 5 ckarakter
        cout << "!! EROR line("<<line <<")"<<" Unexpected comma place"<<endl;
        return false;
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
        {cout << "!! EROR line("<<line <<") There is no instruction"<<endl;
        return false;}
    else if(occuranceInstruct >1)
        {cout << "!! EROR line("<<line <<") There are more than one instruction"
              <<endl;
        return false;}

    return true;
}
bool detectionOperandEror(string lineStatement,int line,instruction* temp){
    if (temp->opCode == "ADD"|| temp->opCode == "MOV" || temp->opCode == "SUB"){
        if (temp->operandOne=="" ||temp->operandTwo=="") {
           cout << "!! EROR line("<<line <<") There are missing parameters." ;
           cout << endl;return false;
        }
    }
    int op1err=0;
    int op2err=0;
    for (int i = 0; i < temp->operandOne.size(); i++) {
        if ( (temp->operandOne[i] >= 'A' && temp->operandOne[i] <='Z') ) 
                op1err++;     
    }
    for (int i = 0; i < temp->operandTwo.size(); i++) {
        if ( (temp->operandTwo[i] >= 'A' && temp->operandTwo[i] <='Z') ) 
                op2err++;        
    }
    if (temp->operandOne != "" && op1err>1 ) {// RR1,0R0R gibi durmlar
        cout << "!! EROR line("<<line<<") This operand ("<<temp->operandOne<<
                ") is not proper."<<endl;return false;
    }
    if (temp->operandTwo != "" && op2err>1 ) {
        cout << "!! EROR line("<<line<<") This operand ("<<temp->operandTwo<<
                ") is not proper."<<endl;return false;
    }
    
    int dashChracterIndexop1=temp->operandOne.find_first_of('-');
    int dashChracterIndexop2=temp->operandTwo.find_first_of('-');//r-1 gibi
    if ( temp->operandOne != "" && dashChracterIndexop1 != -1 && op1err==1 ) {
        cout << "!! EROR line("<<line<<") This operand ("<<temp->operandOne<<
                ") is not proper."<<endl;return false;
    }
    if (temp->operandTwo != "" && dashChracterIndexop2 != -1 && op2err==1 ) {
        cout << "!! EROR line("<<line<<") This operand ("<<temp->operandTwo<<
                ") is not proper."<<endl;return false;
    }
    op1err=temp->operandOne.find_first_of('R');
    op2err=temp->operandTwo.find_first_of('R');//R nin farklı yerlerde olması
    if ( (op1err==1 && temp->operandOne[0]!='R' ) ||
         (op2err==1 && temp->operandTwo[0]!='R') ) {
        cout << "!! EROR line("<<line<<") This operand ";
        if (op1err==1) 
            cout <<"("<<temp->operandOne<<") ";
        else if (op2err==1) 
            cout <<"("<< temp->operandTwo<<") ";        
        cout <<"is not proper." << endl;
        return false;
    }
    if ( (dashChracterIndexop1 != -1 && dashChracterIndexop1 != 0) ||
         (dashChracterIndexop2 != -1 && dashChracterIndexop2 != 0) ) {
        cout << "!! EROR line("<<line<<") This operand ";
        if (dashChracterIndexop1 != -1) 
            cout <<"("<<temp->operandOne<<") ";
        if (dashChracterIndexop2 != -1) 
            cout <<"("<< temp->operandTwo<<") ";        
        cout << endl;
        return false;
    }

    int operand1=0,operand2=0;
    solveOperand( temp,&operand1,&operand2);
    
    if ( temp->operandOne[0] == 'R' && ( operand1<1 || operand1>5 ) ) 
        {cout << "!! EROR line("<<line <<") You don't have "<<temp->operandOne
                <<" register."<<endl;return false;}
    if ( temp->operandTwo[0] == 'R' && ( operand2<1 || operand2>5 ) ) 
        {cout << "!! EROR line("<<line <<") You don't have "<<temp->operandTwo
                <<" register."<<endl;return false;}
    if ( temp->opCode == "JMP"  && ( operand1<0  ) ) 
        {cout<< "!! EROR line("<<line <<") You don't jump to "<<temp->operandOne
                <<" line."<<endl;return false;}    
    int hltInstruct =lineStatement.find("HLT");
    if (hltInstruct!=-1 && lineStatement.size()>3) {
        cout << "!! EROR line("<<line <<") Improper HLT instruction"<<endl;
        return false;
    }
   
    return true;
}

bool runInstructionStatement(instruction statement,int* registers,int* jmplne){
    if( statement.opCode == "MOV" ) 
        return moveInstruction(&statement,registers);                                                  
    else if( statement.opCode == "ADD" )
        return addInstruction(&statement,registers);                                                   
    else if ( statement.opCode =="SUB" ) 
        return subtitionInstruction(&statement,registers);                                             
    else if( statement.opCode == "JMP")
        return jumpInstruction(&statement,registers,jmplne);                                                  
    else if( statement.opCode == "PRN" ) 
        return printInstruction(&statement,registers);                                                 
    else if( statement.opCode == "HLT" ) 
        return false;
}
bool moveInstruction(instruction* statement,int* registers){
    
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);
    if (statement->operandTwo[0]=='R')//register1 to register2
        {registers[operand2-1]=registers[operand1-1];return true;} 
    else //constant to register
        {registers[operand1-1]=operand2;return true;}
    return false;
}
bool printInstruction(instruction* statement,int* registers){
  
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);
    if (statement->operandOne[0]=='R')//register1 to register2
        {cout << "R" <<operand1 << " = " << registers[operand1-1]<< endl;
         return true;} 
    else //constant to register
        {cout << "Constant "  << " = " << operand1<< endl ;return true;}
    return false;
}
bool subtitionInstruction(instruction* statement,int* registers){
    
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);
    if (statement->operandTwo[0]=='R')//register1 subtition register2
        {registers[operand1-1]= registers[operand1-1] - registers[operand2-1];
         return true;} 
    else // constant subtition register
        {registers[operand1-1]=registers[operand1-1] - operand2;return true;}
    return false;
}
bool addInstruction(instruction* statement,int* registers){

    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);
    if (statement->operandTwo[0]=='R')//register1 subtition register2
        {registers[operand1-1]= registers[operand1-1] + registers[operand2-1];
         return true;}            
    else // constant subtition register
        {registers[operand1-1]=registers[operand1-1] + operand2;return true;}
    return false;
}
bool jumpInstruction(instruction* statement,int* registers,int* jmplne){
    
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);   
    if (statement->operandOne[0]=='R' && registers[operand1-1] == 0 )//register1 to register2
        { *jmplne=operand2;return true;}//-2 maindeki artısı dengelmek için 
    else if (statement->operandOne[0]!='R' )//Constant line
        { *jmplne=operand1;return true;}
    return false;
}

void solveOperand(instruction* statement,int* op1,int*op2){

    if (statement->operandOne[0] == 'R') 
       *op1=statement->operandOne[1]-48;
    else{ 
        int size=statement->operandOne.size();
        int tempnum=0;
        int i=0;
        if (statement->operandOne[0] == '-')
            i++;  
        for (; i<size; i++) 
            tempnum = 10*tempnum + statement->operandOne[i] -48;
        if (statement->operandOne[0] == '-')
            *op1=tempnum*(-1); 
        else
            *op1=tempnum; 
        
    }  
   
    if (statement->operandTwo[0] == 'R') {
       *op2=statement->operandTwo[1]-48;
    }
    else{
        int size=statement->operandTwo.size();
        int tempnum=0;
        int i=0;
        if (statement->operandTwo[0] == '-')
            i++;  
        for (; i<size; i++) 
            tempnum = 10*tempnum + statement->operandTwo[i] -48;
        if (statement->operandTwo[0] == '-')
            *op2=tempnum*(-1); 
        else
            *op2=tempnum; 
    }  
}


