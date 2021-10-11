//FP 
//Javier G�mez L�pez
/* Programa para calcular el �rea de un c�rculo 
   y la longitud de la circunferencia correspondiente.
   
   Implementamos las f�rmulas de la longitud y el �rea de una 
   circunferencia.
   
   Entradas: el radio de dicha circunferencia
   Salidas: el �rea y la longitud de la circunferencia
                  
            Longitud = 2 x pi x r
            �rea: pi x r^2
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main() //Programa principal
{
	double radio;       //Declara las variables para 
	double longitud;    //guardar tanto el radio como
	double area;        //como los resultados de las operaciones
	
//Entrada de datos

cout << "Introduzca el valor del radio del c�rculo: ";
cin >> radio;

//C�lculos 

longitud = 2 *3.1415927 * radio;
area = 3.1415927 * radio * radio;

//Salida de datos

cout << endl;
cout << "El valor de la longitud del c�rculo es: " << longitud << endl;
cout << "El valor del �rea del c�ruclo es: " << area << endl;


return (0);
}
