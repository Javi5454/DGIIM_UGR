//FP 
//Javier G�mez L�pez
/* Programa para calcular distintos datos de interes de la funci�n gaussiana
   en base a los valores introducidos por el usuario
   
   Para ello usaremos distintas funciones que nos dar�n distintos resultados
   
   Entradas: la desviaci�n t�pica, la media y un valor x.
   Salidas: un valor de la funci�n gaussiana seg�n esos valores y el CFD.
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

double ValorGaussiana (double valor_x, double media, double desviacion)
{
	const double PI = 3.1415926535;
	
	double resultado;
	
	resultado = 1/(desviacion_tipica * sqrt(2 * PI));
	resultado = resultado * exp(-0.5 * pow(((valor_x - media) /
	            desviacion_tipica),2));
	            
	return resultado;


int main ()
{
	double media;
	double desviacion_tipica;
	
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
