/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bigram.h
 * Author:  Emre Behadir 141044021
 *
 * Created on 22 Aralık 2016 Perşembe, 20:55
 */

#ifndef BIGRAM_H
#define BIGRAM_H

#include <iostream>
#include <ostream>
using namespace std;

template< class T >
class Bigram {
public:

    virtual void readFile( const char* filename)= 0;
    virtual int numGrams()= 0;
    virtual int numOfGrams(T p1,T p2) = 0;
    virtual std::pair< T, T > maxGrams()= 0;
    virtual std::ostream&  overExtract(std::ostream& out) = 0;  
    inline friend  std::ostream& operator<<(std::ostream& os, Bigram<T>& obj){
        return obj.overExtract(os);
    }
    
};


#endif /* BIGRAM_H */

