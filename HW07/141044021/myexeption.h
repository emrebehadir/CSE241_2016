/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myexeption.h
 * Author: testbhdr
 *
 * Created on 25 Aralık 2016 Pazar, 11:44
 */

#ifndef MYEXEPTION_H
#define MYEXEPTION_H
#include <iostream>
#include <exception>
#include <string>
using namespace std;

class myexeption : public std::exception {
public:
    myexeption();
    
    myexeption(const char* exeption):exeptionType(exeption)
    { }
    
    virtual const char* what() const throw ()
    {   return exeptionType.c_str(); }
    
    virtual ~myexeption() throw (){}

private:
    string exeptionType;
};

#endif /* MYEXEPTION_H */

