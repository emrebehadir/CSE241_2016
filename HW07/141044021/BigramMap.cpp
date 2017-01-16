/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramMap.cpp
 * Author:  Emre Behadir 141044021
 * 
 * Created on 22 Aralık 2016 Perşembe, 20:56
 */

#include "BigramMap.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <exception>
#include <map>


template<class T>
BigramMap<T>::BigramMap() {

}

template<class T>
BigramMap<T>::BigramMap(int dataType)   {
/*    if (dataType == 1) // for int
        bigramArray(20,T());
    if (dataType == 2) // for double
        bigramArray(20.0,T());
    if (dataType == 3) // for string
        bigramArray("initilaze",T());
*/
}

template<class T>
void BigramMap<T>::readFile(const char* filename) {
    fstream bigramFile;
    bigramFile.open(filename);
    
    T tempBigram;
    if (!bigramFile){
        myexeption a("File is not opened.");
        throw a;
    }
    
    if(bigramFile >> tempBigram){
        bigramFile.close();   
    }
    else{
        myexeption a(" Empty file !!");
        throw a;
    }
    
    bigramFile.open(filename);
    int i=0;
    bool stop=false;
    while (!stop) {
        
        if(bigramFile >> tempBigram){
            bigramMaparr.insert( std::pair<int,T>(i,tempBigram) );
            ++i;
        }
        else if(bigramFile.eof()){
            stop=true;
        }
        else{
            myexeption a("Unexpected bad data.");
            throw a;
        }
            
    }
       
    bigramFile.close();
}

template<class T>
int BigramMap<T>::numGrams() {
    return bigramMaparr.size()-1;
}

template<class T>
std::pair<T, T> BigramMap<T>::maxGrams() {
    pair<T,T> returnPairvalue;
    vector< vector<T> > tempGrams;
                        //bigramarr
    for (int i = 0; i < bigramMaparr.size()-1; i++) {
        vector<T> tempRow;

        tempRow.push_back(bigramMaparr[i]);
        tempRow.push_back(bigramMaparr[i+1]);
        
        tempGrams.push_back(tempRow);
    }
    
    int occurance= numOfGrams(tempGrams[0][0],tempGrams [0][1]) ;
    for (int i = 0; i < tempGrams.size(); i++) {
        int tempOccurance= numOfGrams(tempGrams[i][0],tempGrams[i][1]);
        if (tempOccurance>=occurance) {
            occurance=tempOccurance;
            returnPairvalue.first=tempGrams[i][0];
            returnPairvalue.second=tempGrams[i][1];
        }
    }
    if (occurance==1) {
        returnPairvalue.first=tempGrams[0][0];
        returnPairvalue.second=tempGrams[0][1];
    }

    return returnPairvalue;
}

template<class T>
int BigramMap<T>::numOfGrams(T p1, T p2) {
    int numOfsize=0;

    for (int i = 0; i < bigramMaparr.size()-1; i++) {
        if(bigramMaparr[i]==p1 && bigramMaparr[i+1]== p2)
            ++numOfsize;
    }
    
    return numOfsize;
}

template<class T>
BigramMap<T>::~BigramMap() {

}

template<class T>
ostream& BigramMap<T>::overExtract(ostream& out) {
    int numOfsize=0;
    vector< vector<T> > tempGrams;
    vector<int>         tempGramsOccur;
    
    for (int i = 0; i < bigramMaparr.size()-1; i++) {
        vector<T> tempRow;    
        tempRow.push_back(bigramMaparr[i]);
        tempRow.push_back(bigramMaparr[i+1]);
        tempGrams.push_back(tempRow);
        
        for (int j = 0; j < tempGrams.size(); j++) {
            if(tempGrams[j][0]==bigramMaparr[i] && tempGrams[j][1]== bigramMaparr[i+1])
            {++numOfsize;}
        }
        int a=numOfGrams(bigramMaparr[i],bigramMaparr[i+1]);
        tempGramsOccur.push_back(a);
        if (numOfsize>1) {
            tempGrams.pop_back();
            tempGramsOccur.pop_back();
        }
        
        numOfsize=0;
    
    }

    T temp;
    int intTemp;
    for(int i=0; i<tempGramsOccur.size(); i++)
    {
        for(int j=tempGramsOccur.size()-1; j>i; j--)
        {
            if(tempGramsOccur[j]>tempGramsOccur[j-1])
            {
                intTemp=tempGramsOccur[j-1];
                tempGramsOccur[j-1]=tempGramsOccur[j];
                tempGramsOccur[j]=intTemp;
                
                temp=tempGrams[j-1][0];
                tempGrams[j-1][0]=tempGrams[j][0];
                tempGrams[j][0]=temp;
                
                temp=tempGrams[j-1][1];
                tempGrams[j-1][1]=tempGrams[j][1];
                tempGrams[j][1]=temp;
                
            }
        }
    }
    
    for (int i = 0; i < tempGrams.size(); i++) {
        out <<">> "<<"{ " << tempGrams[i][0]<<" "<<tempGrams[i][1] 
                    <<" } - occurance >> "<< tempGramsOccur[i]<<endl;

    }
   
    return out;
}




