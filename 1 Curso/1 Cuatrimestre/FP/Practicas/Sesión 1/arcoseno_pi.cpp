//FP 
//Javier G�mez L�pez
/* Programa para mostrar el n�mero pi 
   usando el arcoseno.
   
   Salidas: una aproximaci�n bastante fiel de pi.
   
   p/6= arco-seno(0,5)

   
*/

#include <iostream>  //Inclusi�n de los recursos de E/S
#include <cmath>     //Inlcusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	double pi = asin(0.5) * 6;  //Declaraci�n de la variable de pi
	
//Salidas
	
	cout << "El valor aproximado de pi es: " << pi << endl;
	
return (0);

}
