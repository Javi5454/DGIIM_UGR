//FP 
//Javier G�mez L�pez
/* Programa para calcular la funci�n gaussiana en base a unos par�metros
   variables (media y desviaci�n t�pica). Adem�s comprobaremos si los datos
   introducidos son correctos (si la desviaci�n t�pica es distinta de 0)
   
   Para ello usaremos la f�rmula que nos proporciona el enunciado.
   
   Entradas: la desviaci�n t�pica, la media y un valor x.
   Salidas: un valor de la funci�n gaussiana seg�n esos valores
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main ()
{
	const double PI = 3.14159265;
	
	double media;
	double desviacion_tipica;

//Entradas

cout << "Introduzca el valor de la media: ";
cin >> media;
cout << "Introduzca el valor de la desviaci�n t�pica: ";
cin >> desviacion_tipica;

if (desviacion_tipica >= 0)
{
    double resultado, valor_x;
    cout << "Introduzca el valor de la x: ";
    cin >> valor_x;
	resultado = 1/(desviacion_tipica * sqrt(2 * PI));
	resultado = resultado * exp(-0.5 * pow(((valor_x - media)
	            /desviacion_tipica),2));
	
	cout << "El valor de la y para los valores introducidos es: " << resultado;
	
} 
else
{
	cout << "El valor de la desviaci�n t�pica debe de ser mayor o igual que 0";
}
	


return (0);

}
