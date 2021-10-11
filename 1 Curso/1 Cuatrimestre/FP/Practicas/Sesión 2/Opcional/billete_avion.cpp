//FP 
//Javier G�mez L�pez
/* Programa para calcular el precio de un billete
   de avi�n en funci�n de los kil�metros a realizar.
   
   Implementamos la f�rmula que dice el problema para
   el c�lculo del precio del billete.
   
   Entradas: kil�metros que se van a realizar en el viaje
   Salidas: precio del billete final
                  
            Billete final = tarifa base + km * 0.1 (10 c�ntimos)
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	int tarifa_base = 150;  //Declaraci�n de las varibales
	double kilometros;
	double precio_final;     //que definir�n el precio del billete
	
//Entradas

cout << "Los kil�metros que usted va a realizar en su viaje son: ";
cin >> kilometros;

//Calculos

precio_final = tarifa_base + kilometros * 0.1;

//Salidas

cout << "El precio de su billete es: " << precio_final << endl;

return (0);

}
