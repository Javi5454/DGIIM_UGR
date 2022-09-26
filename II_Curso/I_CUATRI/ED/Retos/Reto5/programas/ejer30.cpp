/**
 * @file ejer24.cpp
 * @author Javier Gómez López
 * @brief Archivo de implementación del ejercicio 24
 * @version 0.1
 */

#include "bintree.h"
#include <iostream>
#include <list>

using namespace std;

/**
 * @brief Funcion, que dado un árbol binario, devuelve en una lista el camino que se obtiene recorriendo el
 * árbol desde la raíz a las hojas, siempre pior el hijo con mayor valor de la etiqueta. Si para un nodo, el valor más
 * grande está repetido, entonces el camino puede seguir por cualquiera de los hijos.
 * @param A
 * @param L
 */
void path_of_largest(bintree<int> &A, list<int> &L){
    bintree<int>::node n = A.root();

    while(n.left().null() == false || n.right().null() == false){
        L.push_back(*n);

        if (n.left().null()){
            n = n.right();
        }
        else if (n.right().null()){
            n = n.left();
        }
        else{
            if (*n.left() >= *n.right()){
                n = n.left();
            }
            else{
                n = n.right();
            }
        }
    }

    L.push_back(*n);
}


/**
 * @brief Funcion main de prueba. Puede modificarse el arbol a placer.
 */
int main(){
    bintree<int> T(1);
    T.insert_left(T.root(),4);
    T.insert_right(T.root(),7);
    T.insert_left(T.root().left(),8);
    T.insert_right(T.root().left(),9);
    T.insert_left(T.root().left().right(), 6);
    T.insert_left(T.root().right(),11);
    T.insert_right(T.root().right(), 10);
    T.insert_right(T.root().right().left(),14);
    T.insert_left(T.root().right().left().right(),8);
    T.insert_right(T.root().right().left().right(),8);

    list<int> result;

    path_of_largest(T, result);

    list<int>::iterator p1;

    for(p1 = result.begin(); p1 != result.end(); p1++){
        cout << *p1 << " ";
    }

    cout << endl;

    return  0;
}