//FP 
//Javier G�mez L�pez
/* Programa para calcular el m�nimo numero de bits necesarios
   para representar un numero entero positivo.
   
   Para ello usaremos un algoritmo que nos permita conocer este m�nimo
   n�mero de bits a partir de logaritmos en base 2 y truncamientos.
   
   Declararemos una variable booleana en funci�n de si el n�mero es 0
   (puesto que ningun logaritmo puede tener un argumento 0) y para el 
   resto de casos sumaremos uno y truncaremos el resultado.
   
   Entradas: un entero positivo teniendo en cuenta el 0
   Salidas: el m�nimo n�mero de bits para representar dicho entero
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	//Declaraci�n de variables
	int entero;
	int bits;
	
	//Entradas
	cout << "Introduzca un entero positivo (el 0 tambi�n se permite): ";
	cin >> entero;
	
	//Calculos
	bool aux = entero > 0;
	bits = log2(entero);
	bits = aux * bits + 1;
	
	//Salidas
	cout << "El n�mero m�nimo de bits necesarios para representar ";
	cout << entero << " es " << bits;
	
	return (0);
}
