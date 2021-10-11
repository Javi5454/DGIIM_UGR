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
	const int TARIFA_BASE = 150;   //Declaraci�n de las varibales
	const int KM_BASE = 300;      
	const int DESCUENTO_KM = 700;
	const int PUNTOS_3 = 100;
	const int PUNTOS_4 = 200;

	double descuento_km = 0;
	double descuento_puntos;
	double kilometros;
	int puntos;
	double precio_final;     //que definir�n el precio del billete

//Entradas

cout << "Introduzca los km que va a realizar: ";
cin >> kilometros;
cout << "Introduza su n�mero de puntos de fidelizaci�n: ";
cin >> puntos;

if (kilometros < KM_BASE)	
{
//Calculos

precio_final = TARIFA_BASE;

}
else 
{
	precio_final = TARIFA_BASE + (kilometros - KM_BASE) * 0.1;
}

if (kilometros > 700)
{
	descuento_km = precio_final * 0.02;
}

if (puntos >= 100 && puntos < 200)
{
	descuento_puntos = precio_final * 0.03;
}
else if (puntos >= 200)
{
	descuento_puntos = precio_final * 0.04;
}

precio_final = precio_final - descuento_puntos - descuento_km;

//Salidas

cout << "El precio de su billete es: " << precio_final << endl;

return (0);

}
