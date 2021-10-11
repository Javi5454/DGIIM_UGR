//FP 
//Javier G�mez L�pez
/* Programa para pasar de mayusuclas a minusculas sin utilizar toupper y 
   tolower.
   
   Para ello utilizaremos la equivalencia entre tipos enteros 
   y de car�cter
   
   Entradas: una cadena de texto en mayusculas
   
   Salidas: la cadena transformada a minusuculas
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <string>  //Inclusi�n de los recursos string

using namespace std;

int main()
{
	//Declaracion de variables
	
	char letra_mayus;
		
	//Entradas
	cout << "Introduzca una letra en may�scula: ";
	cin >> letra_mayus;
	
if (letra_mayus >= 'A' && letra_mayus <= 'Z')
{
	char letra_minus;
	
	const int DIFERENCIA_MAYUS_MINUS = 'a' - 'A';
	
	//Calculos
	letra_minus = char(letra_mayus + DIFERENCIA_MAYUS_MINUS);
	
	//Salidas
	cout << "La letra en min�scula es: " << letra_minus;
}
else
{
	cout << "Debe introducir una letra may�scula";
}
	return (0);
}
