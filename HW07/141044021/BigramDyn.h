
/* 
 * File:   BigramDyn.h
 * Author:  Emre Behadir 141044021
 *
 * Created on 24 Aralık 2016 Cumartesi, 21:10
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include "Bigram.h"
#include "myexeption.h"
#include<iostream>
using namespace std;

template< class T >
class BigramDyn : public  Bigram <T> {
public:
    BigramDyn();
    BigramDyn(int dataType);
    ~BigramDyn();

    pair<T,T> maxGrams() override;
    int numGrams() override;
    int numOfGrams(T p1, T p2) override;
    void readFile(const char* filename) override;
    ostream& overExtract(ostream& out) override;
    int getUsed() const {
        return used;
    }


private:
    T* bigramDynarry;
    int capacity;
    int used;
};

#endif /* BIGRAMDYN_H */

