//FP 
//Javier G�mez L�pez
/* Programa para la distribuci�n acumulada en el punto x de una funci�n
   normal (Gaussiana). 
   
   Para ello usaremos un filtro para obtener los datos correctos del usuario
   y tras ello calcularemos una integral usando un ciclo for (muchas sumas).
   
   Entradas: la desviaci�n t�pica, la media y un valor x.
   Salidas: CFD de la gaussiana en ese valor de x
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main ()
{
	const double PI = 3.14159265;
	const float dx = 0.00005;
	
	double media, gaussiana, valor_x, inicio_intervalo, i;
	double desviacion_tipica = 0;
	double integral = 0;
	double resultado;

	//Entradas

	cout << "Introduzca el valor de la media: ";
	cin >> media;
	
	while (desviacion_tipica <= 0)
	{
		cout << "Introduzca el valor de la desviaci�n t�pica (>0): ";
		cin >> desviacion_tipica;
	}
	
	
	cout << "Introduzca el valor de la x: ";
    cin >> valor_x;
    
    //Calculos
    inicio_intervalo = media - 3 * desviacion_tipica;
	            
	for (i = inicio_intervalo; i <= valor_x; i = i + dx)
	{
		gaussiana = 1/(desviacion_tipica * sqrt(2 * PI));
		gaussiana = gaussiana * exp(-0.5 * pow(((i - media)
	            /desviacion_tipica),2));
	    resultado = gaussiana * dx;  //Calculamos el area del rect�ngulo 
	    integral = integral + resultado;
	}
	
	//Salidas
	
	cout << "El valor CDF en " << valor_x << " es: " << integral << endl;

return (0);

}
