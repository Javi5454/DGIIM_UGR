/**
 * @file ejer24.cpp
 * @author Javier Gómez López
 * @brief Archivo de implementación del ejercicio 24
 * @version 0.1
 */

#include <iostream>
#include "bintree.h"
#include <string>

using namespace std;

/**
 * @brief Dados dos árboles binarios de enteros (teniendo la misma estructura de ramificación), se dice que
 * el primero es inferior al segundo si, los elementos del primero, en los nodos coincidentes en posición, son menores
 * que los del segundo.
 * @param ab1 Arbol a comprobar si es menor
 * @param ab2 Arbol a comprobar si es mayor
 * @return True si ab1 es inferior (según la definición anterior) a ab2, y False si no es así.
 */

bool es_inferior(bintree<int> &ab1, bintree<int> &ab2){
    bintree<int>::preorder_iterator p1;
    string preorder_A, preorder_B;

    for(p1 = ab1.begin_preorder(); p1 != ab1.end_preorder(); p1.operator++()){
        preorder_A += to_string(*p1);
    }

    for(p1 = ab2.begin_preorder(); p1 != ab2.end_preorder(); p1.operator++()){
        preorder_B += to_string(*p1);
    }

    for (int i = 0; i < preorder_A.length(); ++i) {
        if(preorder_A[i] > preorder_B[i]){
            return false;
        }
    }

    return true;
}

/**
 * @brief Funcion main de prueba. Puede modificarse el arbol a placer.
 */
int main(){
    bintree<int> T1(1);
    T1.insert_left(T1.root(), 14);
    T1.insert_right(T1.root(),3);
    T1.insert_left(T1.root().left(), 2);
    T1.insert_right(T1.root().left(), 8);

    bintree<int> T2(2);
    T2.insert_left(T2.root(), 8);
    T2.insert_right(T2.root(),4);
    T2.insert_left(T2.root().left(), 3);
    T2.insert_right(T2.root().left(), 9);

    bool result = es_inferior(T1, T2);

    if (result){
        cout << "T1 es inferior a T2";
    }
    else{
        cout << "T1 no es inferior a T2";
    }

    return 0;
}