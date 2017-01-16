/* 
 * File:   Memory.cpp
 * Author: Emre Behadir 141044021
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:34
 */

#include "Memory.h"
#include <iostream>
#include <iomanip>// memory yazdırırken  padding amacıyla ekledim setw(4)
using namespace std;

Memory::Memory() {
    for (int i = 0; i < 50; i++)
        memory[i]=0;
}
Memory::Memory(int option){
    for (int i = 0; i < 50; i++)
        memory[i]=0;
    setOption(option);
}

void Memory::setMem(int target , unsigned int newValue) {
    memory[target] = newValue;
}

unsigned int Memory::getMem(int target) const {
    return memory[target];
}

void Memory::printAll(){
    if(option==2 || option==0 ||option==1){
    cout<<"Memory values:"<<endl;
    for (int i = 0; i < 50; i++){ 
            cout <<"[";
            if(i<10)
                cout<< '0';
            cout<< i<<"]"<< "-> "<< this->getMem(i)<< " ";
        cout<< endl;
    }
    cout<< endl;
    }
 }

void Memory::setOption(int option) {
     this->option = option;
 }
int Memory::getOption() const {
     return option;
 }


