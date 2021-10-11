//FP 
//Javier G�mez L�pez
/* Programa para comprobar si tres n�meros enteros son introducidos
   de manera ordenada, ascendente o descendente.
   
   Para ello utilizaremos una doble condici�n que nos verifique la 
   ordenaci�n tanto en un sentido como en otro.
   
   Si no se da ninguno de los dos casos, concluiremos que no est�n
   ordenados.
   
   Entradas: tres n�meros enteros.
   Salidas: si estos est�n o no ordenados
*/

#include <iostream>  //Inclusi�n de los recursos de entrada y salida

using namespace std;

int main()
{
	//Declaraci�n de variables
	int numero_1;
	int numero_2;
	int numero_3;
	
	//Entradas
	cout << "Introduzca el primer numero: ";
	cin >> numero_1;
	cout << "Introduzca el segundo n�mero: ";
	cin >> numero_2;
	cout << "Introduzca el tercer n�mero: ";
	cin >> numero_3;
	
if (numero_1 < numero_2 < numero_3 || numero_1 > numero_2 > numero_3)
{
	cout << "Los valores est�n ordenados";
}
else 
{
	cout << "Los valores no est�n ordenados";
}

	return (0);
}
