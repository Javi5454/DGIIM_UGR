//FP 
//Javier G�mez L�pez
/* Programa para calcular la variaci�n porcentual 
   a partir de dos valores, inicial y final.
   
   Implementamos la f�rmula de  la variaci�n porcentual.
   
   Entradas: valor inicial y final
   Salidas: la variaci�n porcentual entre esos valores
                  
            VP = abs ((100 x (valor final - valor inicial)) / valor inicial)
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	double valor_inicial; //Declaraci�n de las variables 
	double valor_final;
	double variacion_porcentual;
	
//Entradas
cout << "El valor inicial es: ";
cin >> valor_inicial;
cout << endl;
cout << "El valor final es: ";
cin >> valor_final;
cout << endl;

//Calculos

variacion_porcentual = abs((100 * (valor_final - valor_inicial)) / valor_inicial);

//Salida

cout << "La variaci�n porcentual es: " << variacion_porcentual << endl;

return (0);

}
