
#ifndef HOJAS_H_
#define HOJAS_H_

using namespace std;
#include "include/BasicCDS.h"

class Inode{
    public:
    double probability = 0.0;
        Inode(){}
        Inode(double prob){
            probability = prob;
        }
        double getProb() const {return probability;}
        virtual ~Inode(){};
};

class Hoja : public Inode{
    public:
        char character;
        Hoja(char letra, double prob): Inode(prob){
            character = letra;
        }
        virtual ~Hoja(){}
        char getChar() const {return character;}
};

class NodoInterno : public Inode{
    public:
        Inode* HijoI;
        Inode* HijoD;
        NodoInterno(Inode* a, Inode* b,double prob) : Inode(prob){
            HijoI = a;
            HijoD = b;
        }
        virtual ~NodoInterno(){
            delete HijoI;
            delete HijoD;
        }
};
#endif