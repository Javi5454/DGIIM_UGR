//FP 
//Javier G�mez L�pez
/* Programa para calcular el total ganado a partir de un inter�s
   en un banco.
   
   Implementamos la f�rmula que dice el problema para
   el c�lculo del capital final.
   
   Entradas: capital inicial e inter�s
   Salidas: total del capital
                  
           total = capital + capital * (interes / 100);
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	double capital;  //Declaraci�n de variables
	double interes;
	double total;
	
//Entradas

cout << "El capital que usted desea depositar en el banco es: ";
cin >> capital;
cout << endl;
cout << "Y el inter�s al que desea depositarlo es: ";
cin >> interes;
cout << endl;

//Calculos
total = capital + capital * (interes / 100);

//Salidas

cout << "Su capital tras un a�o ser�: " << total << endl;

return (0);

}

/*Si quisieramos cambiar el valor del capital 
  (para un inter�s compuesto por ejemplo) deber�amos
  usar otra expresi�n tal que capital = total tras los c�lculos
  actuales, no es posible directamente en la misma expresi�n
*/
