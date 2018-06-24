/*
* Huffman.cpp
* Super codigo para crear arbol de Huffman de un input
*   Author: Arturo Reyes
*/

#include "Hojas.h"
#include <bits/stdc++.h>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream> 
#include <ctime>

using namespace std;
typedef string Code;
typedef map<char,Code> Diccionario;
typedef map<string,char> Decoder;

class comparacion{//Estructura de datos para comparar.
    public:
    string letra;
    string valor;
    comparacion(string letra,string valor):letra(letra),valor(valor){}
};
class Comparator{//Defino funcion de comparacion para minheap 1
    public:
        bool operator() (const Inode* p1, const Inode* p2){
            return p1->probability > p2->probability;
        }
};
class Comparador{//Defino funcion de comparacion para minheap 2
    public:
        bool operator() (const comparacion* p1, const comparacion* p2){
            if(p1->valor.length()!=p2->valor.length()){
                return (p1->valor.length() > p2->valor.length());
            }
            if(p1->valor.length()==p2->valor.length()){
                return stoi(p1->valor) > stoi(p2->valor);
            }
        }
};
void converter(int numero){
    if(numero/2!=0){
        converter(numero/2);
    }
    cout<< numero%2<<" binario"<<endl;
};

string toBinary(int numero){
    string Binary = bitset<6>(numero).to_string();
    return Binary;
};

void recorreArbol(Inode* nodo,const Code& codigo, Diccionario& salida){
    if(Hoja* Q = dynamic_cast<Hoja*>(nodo)){
        cout<<"hoja: " << Q->getChar()<<" "<< codigo<<endl;
        salida[Q->getChar()]=codigo;
    }
    if(NodoInterno* Q = dynamic_cast<NodoInterno*>(nodo)){
        Code Dsalida = codigo;
        Dsalida.push_back(*"0");
        Code Isalida = codigo;
        Isalida.push_back(*"1");

        recorreArbol(Q->HijoD,Dsalida,salida);
        recorreArbol(Q->HijoI,Isalida,salida);
    }
}

int main(int argc, char** argv){
    unsigned t0,t1,t2,t3,t4,t5;
    char A = 'a';
    int pointer = 0;
    int contador = 0;
    int size = 0;
    double List [58][2] = {};
    int contadorCodigo = 0;
    t0 = clock();
    /*What is Lorem Ipsum?Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industrys standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.Why do we use it?It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).Where does it come from?Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of  (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, , comes from a line in section 1.10.32.The standard chunk of Lorem Ipsum used since the 1500s is reproduced below for those interested. Sections 1.10.32 and 1.10.33 from  by Cicero are also reproduced in their exact original form, accompanied by English versions from the 1914 translation by H. Rackham.Where can I get some?There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which  look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isnt anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators on the Internet tend to repeat predefined chunks as necessary, making this the first true generator on the Internet. It uses a dictionary of over 200 Latin words, combined with a handful of model sentence structures, to generate Lorem Ipsum which looks reasonable. The generated Lorem Ipsum is therefore always free from repetition, injected humour, or non-characteristic words etc.
    */
    string cadena = "supercalifragilistico espiralidoso";
    for (int i = 0; i < cadena.length(); i++){
        pointer = 0;
        while (pointer < 58){
            if (List[pointer][0] == NULL){
                List[pointer][0] = int(cadena[i]);
                List[pointer][1]++;
                break;
            }
            if (List[pointer][0] == int(cadena[i])){
                List[pointer][1]++;
                break;
            }
            pointer++;
        }
    }
    while(contador< 100){
        if(List[contador][0]==NULL){
            break;
        }
        contador++;
    }

    priority_queue <Inode*, vector<Inode*>, Comparator> pq; //Creo un min heap
    priority_queue <comparacion*, vector<comparacion*>,Comparador> listaOrdenada;//Creo otro minHeap

    double ListaA [contador][3];
    for (int i = 0; i < contador; i++){//creo la lista e inserto los elementos en el minheap
        ListaA[i][0] = List[i][0];
        ListaA[i][1] = List[i][1];
        ListaA[i][2] = List[i][1]/cadena.length();
        pq.push(new Hoja(ListaA[i][0],ListaA[i][2]));
    }

    cout << "Empieza lista" << endl;//Lista no ordenada por orden de aparicion de los caracteres
    for (int i=0; i < sizeof(ListaA)/sizeof(*ListaA); i++){
        cout << char(ListaA[i][0])<<" ";
        cout << ListaA[i][1]<<" "<<ListaA[i][2]<<endl;

    }

    while(pq.size() > 1){
        Inode* HijoR = pq.top();
        pq.pop();
        Inode* HijoL = pq.top();
        pq.pop();
        double freq_padre = HijoR->probability+HijoL->probability;
        Inode* Padre = new NodoInterno(HijoL,HijoR,freq_padre);
        pq.push(Padre);
    }
    Inode* WTF = pq.top();
    NodoInterno* Raiz = dynamic_cast< NodoInterno*>(WTF);
    Diccionario diccionario;
    recorreArbol(Raiz,"",diccionario);

    string ListaB [diccionario.size()][2];
    int numero = 0;
    cout<<"Empieza diccionario de letras:"<<endl;
    for(Diccionario::const_iterator recorre = diccionario.begin();recorre!=diccionario.end();++recorre){
        ListaB[numero][0]=recorre->first;
        ListaB[numero][1]=recorre->second;
        cout<<recorre->first << " "<<recorre->second;
        cout<<endl;
        numero++;
    }
    string output = "";
    for(int i=0; i<cadena.length();i++){
        output = output + diccionario[cadena[i]];
    }
    t1 = clock();
    cout << "Tiempo de codificacion: " << (double(t1-t0)/CLOCKS_PER_SEC)<< "s" << endl;
    cout << "Texto codificado: " << endl;
    cout<< output <<endl;
    Decoder decoder;
    string decoding;
    t2 = clock();
    for(Diccionario::const_iterator recorre = diccionario.begin();recorre!=diccionario.end();++recorre){
        decoder[recorre->second] = recorre->first;
    }
    for(int i=0;i < output.length();i++){
        decoding = decoding + output[i];
        if (decoder[decoding]){
            cout << decoder[decoding];
            decoding = "";
        }
    }
    cout << endl;
    t3 = clock();
    cout << "Tiempo de decodificacion: " << (double(t3-t2)/CLOCKS_PER_SEC) << "s" << endl;
}