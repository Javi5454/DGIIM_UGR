/**
 * @file ejer20.cpp
 * @author Javier Gómez López
 * @brief Archivo de implementación del ejercicio 20
 * @version 0.1
 * 
 */

#include <iostream>
#include <queue>

using namespace std;

/**
 * @brief Función que saca una cierta cantidad de enteros del frente 
 * de la cola C y los vuelve a insertar al final de la cola, de forma
 * que quede en el frente el primer número par que haya en la cola
 * 
 * @param C Cola sobre la que se va a realizar la rotación
 * @post La cola *C* estará modificada de manera que ahora su 
 * primer número par estará al frente de la cola
 */

void rotacion(queue<int> &C){
    queue<int> aux;

    while (C.front() % 2 != 0) //Comprobamos si es par
    {
        aux.push(C.front()); //Lo movemos a la cola auxiliar
        C.pop();
    }

    while (aux.size() != 0)
    {
        C.push(aux.front()); //Insertamos la cola auxiliar al final de la original
        aux.pop();
    }
};

/**
 * @brief Main de prueba para la función \<void> *rotacion*.
 * 
 * Modificar la cola a antojo para probar mediante el método
 * C.push(<valor>)
 * 
 * @return 0 si todo ha ido bien, otro número si ha habido algún error
 * @post La cola C será modificada de acuerdo a la función *rotacion*
 */
int main(){
    queue<int> C;

    C.push(3);
    C.push(4);
    C.push(8);
    C.push(16);
    C.push(32);

    rotacion(C);

    while (!C.empty())
    {
        cout << C.front() << " ";
        C.pop();
    }

    cout << endl;
    

    return 0;
}