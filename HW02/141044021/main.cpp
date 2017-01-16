#include <iostream>
#include <iomanip>// memory yazdırırken  padding amacıyla ekledim setw(4)
#include <string>
#include <fstream>
using namespace std;

struct instruction {
    string opCode;
    string operandOne;
    string operandTwo;
};

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
bool runInstructionStatement(instruction statement,int* registers,unsigned int* memory,int* jmplne);
//Instruction fonksiyonları
bool moveInstruction(instruction* statement,int* registers,unsigned int* memory);
bool printInstruction(instruction* statement,int* registers,unsigned int* memory);
bool subtitionInstruction(instruction* statement,int* registers,unsigned int* memory);
bool addInstruction(instruction* statement,int* registers,unsigned int* memory);
bool jumpInstruction(instruction* statement,int* registers,int* jmplne);
//Operandın hangi int degere karşılık geldigini bulur
void solveOperand(instruction* statement,int* op1,int*op2);

int main(int argc, char** argv) {               
    simulateCpuProgram(argv[1],argv[2]);
    return 0;
}

int simulateCpuProgram(char* filename,char* option){ 

    int         registers[5];
    unsigned int         memory[50];//  unsigned int olacak
    int         cursorLine=1;
    int         totalLine=1;
    instruction statement[256];// Dosyanın enfazla 256 olacağını varsaydım.
    
    registers[0]=0;registers[1]=0;registers[2]=0;registers[3]=0;registers[4]=0;
    for (int i = 0; i < 50; i++) 
        memory[i]=0;

    if(!readInstructionStatement(statement,filename,&totalLine))
        {cout <<endl;return false;}

    while (statement[cursorLine].opCode != "HLT" && cursorLine<=totalLine) 
    {  int templine=cursorLine;                                          
       if(runInstructionStatement(statement[cursorLine],registers,memory,&cursorLine)){
            if (*option =='1' || *option =='2') {
                cout << statement[templine].opCode <<" "
                            <<statement[templine].operandOne<<","
                            <<statement[templine].operandTwo<<"-";
                if (*option =='1') 
                    for (int i = 0; i < 5; i++)
                        cout <<"R" <<i+1 << "=" << registers[i]<< " ";
                else if (*option =='2'){
                    for (int i = 0; i < 5; i++)
                        cout <<"R" <<i+1 << "=" << registers[i]<< " ";
                    cout<< endl;
                    for (int i = 0; i < 50; i++){
                        for (int j = 0; j < 10; j++,i++){
                            cout <<"M";
                            if(i<10)
                                cout<< '0';
                            cout<< i << "="<< setw(3) << memory[i]<< " ";
                        }
                        cout<< endl;
                        i--;
                    }
                }
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
        cout << endl;
        for (int i = 0; i < 50; i++){
            for (int j = 0; j < 10; j++,i++){
                cout <<"M";
                if(i<10)
                    cout<< '0';
                cout<< i << "=" << setw(3) << memory[i]<< " ";
            }
            cout<< endl;
            i--;
        }
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
    
    string instructArr[] = {"MOV", "ADD","SUB","JMP","PRN","HLT","JPN" };
    int intructArrSize=7;

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
    else if (temp->opCode == "JMP" || temp->opCode == "JPN") {
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
    string instructArr[] = {"MOV", "ADD","SUB","JMP","PRN","HLT","JPN" };
    int intructArrSize=7;
    //farklı karkterler olmsı
    for (int i = 0; i < lineStatement.size(); i++) {
        if ( !((lineStatement[i] >= 'A' && lineStatement[i] <='Z') ||
               (lineStatement[i] >= '0' && lineStatement[i] <='9') ||
                lineStatement[i] == ',' || lineStatement[i] == '-' ||
                lineStatement[i] == '#')  ) {
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
        cout <<"is not proper."  << endl;
        return false;
    }
    int sharpCharIndexop1=temp->operandOne.find_first_of('#');//1#
    int sharpCharIndexop2=temp->operandTwo.find_first_of('#');
        if ( (sharpCharIndexop1 != -1 && sharpCharIndexop1 != 0) ||
             (sharpCharIndexop2 != -1 && sharpCharIndexop2 != 0) ) {
        cout << "!! EROR line("<<line<<") This operand ";
        if (sharpCharIndexop1 != -1) 
            cout <<"("<<temp->operandOne<<") ";
        if (sharpCharIndexop2 != -1) 
            cout <<"("<< temp->operandTwo<<") ";        
        cout <<"is not proper."  << endl;
        return false;
    }
    sharpCharIndexop1=0;sharpCharIndexop2=0;
    for (int i = 0; i < temp->operandOne.size(); i++) {
        if ( (temp->operandOne[i] == '#' ) ) 
                sharpCharIndexop1++;     
    }
    for (int i = 0; i < temp->operandTwo.size(); i++) {
        if ( (temp->operandTwo[i] == '#') ) 
                sharpCharIndexop2++;        
    }
    if (temp->operandOne != "" && sharpCharIndexop1>1 ) {// ##1,0#0# gibi durmlar
        cout << "!! EROR line("<<line<<") This operand ("<<temp->operandOne<<
                ") is not proper."<<endl;return false;
    }
    if (temp->operandTwo != "" && sharpCharIndexop2>1 ) {
        cout << "!! EROR line("<<line<<") This operand ("<<temp->operandTwo<<
                ") is not proper."<<endl;return false;
    }
    
    int operand1=0,operand2=0;
    solveOperand( temp,&operand1,&operand2);   
    if ( temp->operandOne[0] == 'R' && ( operand1<1 || operand1>5 ) ) 
        {cout << "!! EROR line("<<line <<") You don't have "<<temp->operandOne
                <<" register."<<endl;return false;}
    if ( temp->operandTwo[0] == 'R' && ( operand2<1 || operand2>5 ) ) 
        {cout << "!! EROR line("<<line <<") You don't have "<<temp->operandTwo
                <<" register."<<endl;return false;}
    if ( temp->operandOne[0] == '#' && ( operand1<0 || operand1>49 ) ) 
        {cout << "!! EROR line("<<line <<") You don't have "<<temp->operandOne
                <<" memory."<<endl;return false;}
    if ( temp->operandTwo[0] == '#' && ( operand2<0 || operand2>49 ) ) 
        {cout << "!! EROR line("<<line <<") You don't have "<<temp->operandTwo
                <<" memory."<<endl;return false;}
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

bool runInstructionStatement(instruction statement,int* registers,unsigned int* memory,int* jmplne){
    if( statement.opCode == "MOV" ) 
        return moveInstruction(&statement,registers,memory);                                                  
    else if( statement.opCode == "ADD" )
        return addInstruction(&statement,registers,memory);                                                   
    else if ( statement.opCode =="SUB" ) 
        return subtitionInstruction(&statement,registers,memory);                                             
    else if( statement.opCode == "JMP" || statement.opCode == "JPN"  )
        return jumpInstruction(&statement,registers,jmplne);                                                  
    else if( statement.opCode == "PRN" ) 
        return printInstruction(&statement,registers,memory);                                                 
    else if( statement.opCode == "HLT" ) 
        return false;
}
bool moveInstruction(instruction* statement,int* registers,unsigned int* memory){ 
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);//RR R# RC -  #R #C
    if (statement->operandOne[0]=='R'){
        if (statement->operandTwo[0]=='R')//register1 to register2(RR) 
            {registers[operand2-1]=registers[operand1-1];return true;}
        else if (statement->operandTwo[0]=='#')//register1 to adress(R#)
            {memory[operand2]=registers[operand1-1];return true;}
        else//constant to register (RC)
            {registers[operand1-1]=operand2;return true;}
    }
    else if (statement->operandOne[0]=='#'){
        if (statement->operandTwo[0]=='R')//register2 to adress(#R)
            {registers[operand2-1]=memory[operand1];return true;}
        else//constant to adress (#C)
            {memory[operand1]=operand2;return true;}
    }
    return false;
}
bool printInstruction(instruction* statement,int* registers,unsigned int*memory){ 
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);
    if (statement->operandOne[0]=='R')//register
        {cout << "R" <<operand1 << " = " << registers[operand1-1]<< endl;
         return true;}
    else if(statement->operandOne[0]=='#')
        {cout << "M" <<operand1 << " = " << memory[operand1-1]<< endl;
         return true;}        
    else //constant to register
        {cout << "Constant "  << " = " << operand1<< endl ;return true;}
    return false;
}
bool subtitionInstruction(instruction* statement,int* registers,unsigned int* memory){   
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);//RR R# RC
    if (statement->operandOne[0]=='R'){
        if(statement->operandTwo[0]=='R')//register1 sub register2(RR)
            {registers[operand1-1] -=  registers[operand2-1];return true;}
        else if(statement->operandTwo[0]=='#')//register1 sub adress(R#)
            {registers[operand1-1] -= memory[operand2];return true;}
        else//register1 sub register2(RC)
            {registers[operand1-1] -=  operand2;return true;}
    }
    return false;
}
bool addInstruction(instruction* statement,int* registers,unsigned int* memory){
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);
    if (statement->operandOne[0]=='R'){
        if(statement->operandTwo[0]=='R')//register1 add register2(RR)
            {registers[operand1-1] +=  registers[operand2-1];return true;}
        else if(statement->operandTwo[0]=='#')//register1 add adress(R#)
            {registers[operand1-1] += memory[operand2];return true;}
        else//register1 sub register2(RC)
            {registers[operand1-1] +=  operand2;return true;}        
    }
    return false;
}
bool jumpInstruction(instruction* statement,int* registers,int* jmplne){    
    int operand1=0,operand2=0;
    solveOperand( statement,&operand1,&operand2);   
    if ((statement->operandOne[0]=='R' && registers[operand1-1] == 0) ||
        (statement->opCode=="JPN" && registers[operand1-1] <= 0 )  )
        { *jmplne=operand2;return true;}
    else if(statement->operandTwo=="")//constant line
        { *jmplne=operand1;return true;}
    return false;
}

void solveOperand(instruction* statement,int* op1,int*op2){
        int size=statement->operandOne.size();
        int tempnum=0;
        int i=0;
        if (statement->operandOne[0] == '-' || statement->operandOne[0] == 'R'||
            statement->operandOne[0] == '#')
            i++;  
        for (; i<size; i++) 
            tempnum = 10*tempnum + statement->operandOne[i] -48;
        if (statement->operandOne[0] == '-')
            *op1=tempnum*(-1); 
        else
            *op1=tempnum;         

        size=statement->operandTwo.size();
        tempnum=0;
        i=0;
        if (statement->operandTwo[0] == '-' || statement->operandTwo[0] == 'R'||
            statement->operandTwo[0] == '#')
            i++;  
        for (; i<size; i++) 
            tempnum = 10*tempnum + statement->operandTwo[i] -48;
        if (statement->operandTwo[0] == '-')
            *op2=tempnum*(-1); 
        else
            *op2=tempnum; 
}
