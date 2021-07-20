#include <iostream> 

#include <math.h> //esta librería sirve para utilizar funciones matemáticas

using namespace std; 

 int main ()

{

    int total = 0, elevado = 0, n;

    cout<<"Ingrese el numero de elementos a sumar: "; cin>>n;

    for (int i = 1; i <= n; i++){

        elevado = pow (2,i); //pow es una función matemática

        total += elevado;

    }

    cout<<"La suma total es: "<<total;

    return 0;

}