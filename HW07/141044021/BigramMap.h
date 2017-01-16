/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramMap.h
 * Author: Emre Behadir 141044021
 *
 * Created on 22 Aralık 2016 Perşembe, 20:56
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H

#include "Bigram.h"
#include "myexeption.h"
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <map>
using namespace std;

template< class T >
class BigramMap : public  Bigram <T> {
    
public:
    
    BigramMap();
    BigramMap(int dataType);
    virtual ~BigramMap();

    void readFile(const char* filename) override;
    int numGrams() override;
    std::pair< T, T > maxGrams() override;
    int numOfGrams(T p1, T p2) override;    
    ostream& overExtract(ostream& out) override;

private: 
  
    std::map<int,T> bigramMaparr;

};

#endif /* BIGRAMMAP_H */

