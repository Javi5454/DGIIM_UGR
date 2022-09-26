/**
 * @file ejer17.cpp
 * @author Javier Gómez López
 * @brief Archivo de implementación del ejercicio 17
 * @version 0.1
 */

#include<iostream>
#include<list>
#include<iterator>

using namespace std;

/**
 * @brief Función que retorna en indx los índices de los elemtnos de
 * L2 que forman L1, en el caso que L2 fue una sublista de L1, si no 
 * indx retorna vacía, independientemente de lo que contenía
 * @param L1 Lista principal de elementos
 * @param L2 Lista a comprobar que es una sublista de L1
 * @param indx Almacén de los índices de donde se encuentran los elementos
 * de L2 que forman L1
 * @return true Si L2 es una sublista de L1
 * @return false Si L2 no es una sublista de L1
 * @post indx almacenerá en el caso de ser sublista L2 de L1, los índices
 * de las elementos de L2 en L1
 */

bool encuentra(list<int> &L1, list<int> &L2, list<int> &indx){
    list<int>::iterator p1,p2;

    p2 = L2.begin();

    int pos = 0; //Serán los índices de los valores encontrados

    bool success = false;

    for (p1 = L1.begin(); p1 != L1.end(); p1++)
    {

        if(p2 != L2.end() && *p2 == *p1){ //Elemento que coincide en ambas listas
                indx.push_back(pos);
                success = true;
                p2++;
        }
        pos++;
        
    }

    if (p2 != L2.end()){ //Comprobación de que L2 es una sublista de L1
        indx.clear();
        success = false;
    }

    return success;
};

/**
 * @brief Main de prueba para la función \<bool> **encuentra**.
 * 
 * Modificar L1 y L2 a antojo para probar.
 * 
 * @return 0 si el correcto ha ido correctamente, otro número si hay algun error
 * @post En indx almacenamos la índices que representan los elementos de 
 * L2 en L1 en caso de que L2 sea sublista de L1.
 */
int main(){

    list<int> L1 = {13,9,8,12,9,6,12,2,9,14,18,10};
    list<int> L2 = {13,12,9};
    list<int> indx;

    if(encuentra(L1,L2,indx)){
        for(list<int>::iterator p = indx.begin(); p != indx.end(); p++){
            cout << *p << " ";
        }
    }
    else{
        cout << "failed" << endl;
    }
    
    return 0;
}