//FP 
//Javier G�mez L�pez
/* Programa para calcular la funci�n gaussiana en base a unos par�metros
   variables (media y desviaci�n t�pica).
   
   Para ello usaremos la f�rmula que nos proporciona el enunciado.
   
   Entradas: la desviaci�n t�pica, la media y un valor x.
   Salidas: un valor de la funci�n gaussiana seg�n esos valores
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main ()
{
	double media;
	double desviacion_tipica;
	double valor_x;
	
	double resultado;

//Entradas

cout << "El valor de la media es: ";
cin >> media;
cout << "El valor de la desviaci�n t�pica es: ";
cin >> desviacion_tipica;
cout << "El valor de la x es: ";
cin >> valor_x;

//Calculos

resultado = 1/(desviacion_tipica * sqrt(2 * 3.141592));
resultado = resultado * exp(-0.5 * pow(((valor_x - media)/desviacion_tipica),2));

//Salidas

cout << "El valor es: " << resultado;

return (0);

}
