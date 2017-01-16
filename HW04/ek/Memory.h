/* 
 * File:   Memory.h
 * Author: Emre Behadir 141044021
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:34
 */

#ifndef MEMORY_H
#define MEMORY_H

class Memory {
public:
    Memory();
    Memory(int option);
    void setMem(int target ,unsigned int newValue);
    unsigned int getMem(int target) const;
    void printAll();
    void setOption(int option);
    int getOption() const;
private:
    unsigned int memory[50];
    int option;
};

#endif /* MEMORY_H */

