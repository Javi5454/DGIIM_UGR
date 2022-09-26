/**
 * @file ejer24.cpp
 * @author Javier Gómez López
 * @brief Archivo de implementación del ejercicio 24
 * @version 0.1
 */

#include "bintree.h"
#include <iostream>

using namespace std;

/**
 * @brief Función que devuelve la suma de las etiquetas de los nodos tales que su etiqueta y la etiqueta de todos
 * los antecesores es par. Si la etiqueta de un nodo es impar, devuelve 0.
 * @param a Arbol original
 * @param n Nodo del que partimos
 * @return La suma de las etiquetas de el nodo dado junto a la de sus ancestros hasta que nos encontramos un ancestro
 * con etiqueta impar o llegamos a la raíz del arbol.
 */
int sumaparantec (bintree<int> &a, bintree<int>::node n){

    if (*n % 2 == 1){
        return 0;
    }

    bool keep = true;
    int result = 0;

    bintree<int>::node next = n;

    while(keep){
        if (next == a.root()){
            if (*next % 2 == 0){
                result += *next;
                keep = false;
            }
            else{
                keep = false;
            }
        }
        else{
            if(*next % 2 == 0){
                result += *next;

                next = next.parent();
            }
            else{
                keep = false;
            }
        }
    }

    return result;
}

/**
 * @brief Funcion main de prueba. Puede modificarse el arbol a placer.
 */
int main(){
    bintree<int> T1(10);
    T1.insert_left(T1.root(), 22);
    T1.insert_right(T1.root(), 11);
    T1.insert_left(T1.root().left(), 16);
    T1.insert_right(T1.root().left(), 6);
    T1.insert_left(T1.root().right(),8);

    int result = sumaparantec(T1, T1.root().left().right());

    cout << result;

    return 0;
}