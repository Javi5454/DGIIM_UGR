/**
 * @file ejer15.cpp
 * @author Javier Gómez López
 * @brief Archivo de implementación del ejercicio 15
 * @version 0.1
 * 
 */

#include<iostream>
#include<list>

using namespace std;

/**
 * @brief Función que devuele el máximo de dos enteros dados
 * @param a Primer entero a comparar
 * @param b Segundo entero a comparar
 * @return int máx(a,b)
 */

int max(int &a, int &b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

/**
 * @brief Función que devuelve el minimo de dos enteros dados
 * 
 * @param a Primer entero a comparar
 * @param b Segundo entero a comparar
 * @return int min(a,b)
 */

int min(int &a, int &b){
    if (a < b){
        return a;
    }
    else{
        return b;
    }
}

/**
 * @brief Modifica las listas L1 L2 de tal manera que si a1j, a2j son
 * los elementos de L1 y L2 antes de aplicar la función y a'1j, a'2j
 * los elementos después de aplicar la función, entonces a'1j = max(a1j, a2j),
 * a'2j = min(a1j,a2j). Si las listas no tienen la misma longitud, entonces 
 * los elementos restantes quedan inalterados.
 * 
 * @param L1 Primera lista donde iran los elementos mayorados
 * @param L2 Segunda lista donde iran los elementos minorados
 * @post L1 tendra los elementos a'1j y L2 los elementos a'2j
 */

void mayorar(list<int> &L1, list<int> &L2){
    int size= min(L1.size(), L2.size()); //Vemos que valores tener en cuenta de ambas listas

    list<int>::iterator p1, p2;

    p1 = L1.begin();
    p2 = L2.begin();

    int insert_L1, insert_L2;

    for (size_t i = 0; i < size; i++)
    {

        insert_L1 = max(*p1,*p2); //Vemos el valor a insertar en L1
        insert_L2 = min(*p1,*p2); //Vemos el valor a insertar en L2

        L1.insert(p1,insert_L1);
        L1.erase(p1++);

        L2.insert(p2,insert_L2);
        L2.erase(p2++);
    }
}

/**
 * @brief Main de prueba para la función \<void> *mayorar*.
 * 
 * Modificar L1 y L2 a antojo.
 * 
 * @return 0 si todo ha ido bien, otro número en caso de error.
 * @post L1 y L2 serán modificadas de acuerdo al funcionamiento de la 
 * función *mayorar*
 */
int main(){
    list<int> L1 = {2,65,43,12,3,47,25,8,99,65};
    list<int> L2 = {5,8,98,75,45,37,21,12,6};

    mayorar(L1,L2);

    list<int>::iterator p1,p2;

    for (p1 = L1.begin(); p1 != L1.end(); p1++)
    {
        cout << *p1 << " ";
    }

    cout << endl;

    for (p2 = L2.begin(); p2 != L2.end(); p2++)
    {
        cout << *p2 << " ";
    }

    cout << endl;
    

    return 0;
}