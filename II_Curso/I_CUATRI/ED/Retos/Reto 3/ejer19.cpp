/**
 * @file ejer19.cpp
 * @author Javier Gómez López
 * @brief Archivo de implementación del ejercicio 19
 * @version 0.1
 * 
 */

#include<iostream>
#include<stack>

using namespace std;

/**
 * @brief Transforma una pila p en otra en la que los elementos aparecen
 * en el mismo orden original y habiendo eliminado los elementos que 
 * siendo consecutivos aparezcan repetidos.
 * 
 * @param p Pila sobre la que se va a realizar la transformación
 * @post p contendrá los mismos elementos ordenados pero sin repeticiones
 * consecutivas.
 */

void transformarpila(stack<int> &p){
    stack<int> aux;

    int size = p.size();

    aux.push(p.top()); //Minimo el primer elemento tiene que estar de no ser p vacía
    p.pop();

    for (size_t i = 1; i < size; i++)
    {
        if(p.top() != aux.top()){ //Vemos si el elemetno es repetido consecutivamente
            aux.push(p.top());
            p.pop();
        }
        else{
            p.pop();
        }
    }

    size = aux.size();

    for (size_t i = 0; i < size; i++) //Devolvemos en orden los elementos a la cola original
    {
        p.push(aux.top()); 
        aux.pop();
    }
    
    
};

/**
 * @brief Main de prueba para la función \<void> *transformarpila*.
 * 
 * Insertar los valores a probar en la pila p mediante p.push(<valor>)
 * 
 * @return 0 si todo ha ido correcto, otro número si ha habido un error
 * @post La pila p será modificada según la función *transformarpila*
 */

int main(){
    stack<int> p;
    p.push(1);
    p.push(1);
    p.push(2);
    p.push(3);
    p.push(3);
    p.push(4);
    p.push(5);
    p.push(5);
    p.push(1);
    p.push(1);
    p.push(9);
    p.push(8);
    p.push(7);
    p.push(7);
    p.push(3);

    transformarpila(p);

    int size = p.size();

    for (size_t i = 0; i < size; i++) //Los elementos aparaceran inversos a como estan en la pila por la propia naturalesa de esta
    {
        cout << p.top() << " ";
        p.pop();

    }

    cout << endl;
    

    return 0;
} 
