/**
 * @file ejer27.cpp
 * @author Javier Gómez López
 * @brief Archivo de implementación del ejercicio 27
 * @version 0.1
 * 
 */

#include<iostream>
#include<queue>

using namespace std;

/**
 * @brief Elimina los elementos de la cola Q de tal manera que los 
 * elementos que quedan estén ordenados de forma creciente.
 * 
 * @param Q Cola a modificar dichos elementos
 */

void creciente(queue<int> &Q){
    queue<int> aux;

    aux.push(Q.front());
    Q.pop();

    while (Q.size() != 0)
    {
        if(Q.front() >= aux.back()){ //Comparamos con el último elemento que hemos tenido en cuenta
            aux.push(Q.front());
            Q.pop();
        }
        else{
            Q.pop();
        }
    }

    while (aux.size() != 0) //Movemos la cola aux a la cola Q
    {
        Q.push(aux.front());
        aux.pop();
    }
    
    
}

/**
 * @brief Main de prueba de la función \<void> *creciente*.
 * 
 * Modificar Q a antojo mediante Q.push(<valor>).
 * 
 * @return 0 si todo ha ido bien, otro número si ha habido algun error
 * @post La cola Q será modificada de acuerdo a la funcion *creciente*
 */

int main(){
    queue<int> Q;

    Q.push(5);
    Q.push(5);
    Q.push(9);
    Q.push(13);
    Q.push(19);
    Q.push(17);
    Q.push(16);
    Q.push(20);
    Q.push(19);
    Q.push(21);

    creciente(Q);

    while (Q.size() != 0)
    {
        cout << Q.front() << " ";
        Q.pop();
    }
    
    cout << endl;

    return 0;
}