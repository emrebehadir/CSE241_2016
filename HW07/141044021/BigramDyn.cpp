/* 
 * File:   BigramDyn.cpp
 * Author: Emre Behadir 141044021
 * 
 * Created on 24 Aralık 2016 Cumartesi, 21:10
 */

#include "BigramDyn.h"
#include <fstream>

template<class T>
BigramDyn<T>::BigramDyn() 
{ }

template<class T>
BigramDyn<T>::BigramDyn(int dataType) {

    capacity=100;
    used=0;
    bigramDynarry = new T[capacity];
}

template<class T>
pair<T, T> BigramDyn<T>::maxGrams() {
    
    pair<T,T> returnPairvalue;

    int occurance= numOfGrams(bigramDynarry[0],bigramDynarry[1]) ;
    
    for (int i = 0; i < used; i++) {
        int tempOccurance= numOfGrams(bigramDynarry[i],bigramDynarry[i+1]);
        if (tempOccurance>=occurance) {
            occurance=tempOccurance;
            returnPairvalue.first=bigramDynarry[i];
            returnPairvalue.second=bigramDynarry[i+1];
        }
    }
    
    if (occurance==1) {
        returnPairvalue.first=bigramDynarry[0];
        returnPairvalue.second=bigramDynarry[1];
    }

    return returnPairvalue;
}

template<class T>
int BigramDyn<T>::numGrams() {
    return used-1;
}

template<class T>
int BigramDyn<T>::numOfGrams(T p1, T p2) {
  int numOfsize=0;
    
    for (int i = 0; i < used-1; i++) {
        if(bigramDynarry[i]==p1 && bigramDynarry[i+1]== p2)
            ++numOfsize;
    }
    return numOfsize;
}

template<class T>
void BigramDyn<T>::readFile(const char* filename) {
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

    bool stop=false;
    while (!stop) {
        
        if(bigramFile >> tempBigram){
            if(used>=capacity){
                capacity *= 2;
                T* newData = new T[capacity];
                for (int i = 0; i <= used; i++)
                    newData[i] = bigramDynarry[i];
                delete[] bigramDynarry;

                bigramDynarry=newData;
            }
            bigramDynarry[used]=tempBigram;
            ++used;
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
BigramDyn<T>::~BigramDyn() {
    delete [] bigramDynarry;
}

template<class T>
ostream& BigramDyn<T>::overExtract(ostream& out) {
    int numOfsize=0;
    
    T**  tempGrams;int tempGramsSize=0; 
    int* tempGramsOccur;int tempGramsOccurSize=0; 
    
    tempGrams = new T*[capacity];
    for(int i = 0; i < capacity; ++i) {
        tempGrams[i] = new T[2];
    }
    tempGramsOccur = new int[capacity];
                        //bigramDynarry.size()-1
    for (int i = 0; i < getUsed() -1 ; i++) {
        tempGrams[tempGramsSize][0]=bigramDynarry[i];
        tempGrams[tempGramsSize][1]=bigramDynarry[i+1];
        ++tempGramsSize;
                            //tempGrams.size()
        for (int j = 0; j < tempGramsOccurSize+1 ; j++) {
            if(tempGrams[j][0]==bigramDynarry[i] && tempGrams[j][1]== bigramDynarry[i+1])
            {++numOfsize;}
        }
        
        int a=numOfGrams(bigramDynarry[i],bigramDynarry[i+1]);
        tempGramsOccur[tempGramsOccurSize]=a;
        ++tempGramsOccurSize;
        
        if (numOfsize>1) {
            --tempGramsSize;
            --tempGramsOccurSize;
        }
        
        numOfsize=0;
    
    }
  
    T temp;
    int intTemp;
                    //tempGramsOccur.size()
    for(int i=0; i<tempGramsOccurSize; i++)
    {               //tempGramsOccur.size()-1
        for(int j=tempGramsOccurSize-1; j>i; j--)
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
                        //tempGrams.size()
    for (int i = 0; i < tempGramsSize; i++) {
        out <<">> "<<"{ " << tempGrams[i][0]<<" "<<tempGrams[i][1] 
                    <<" } - occurance >> "<< tempGramsOccur[i]<<endl;

    }
    
    delete [] tempGramsOccur;
    delete [] tempGrams;
    return out;  
}


