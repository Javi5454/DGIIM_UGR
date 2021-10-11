//FP 
//Javier G�mez L�pez
/* Programa para calcular el precio final de un autom�vil.
   
   Para ello utilizaremos un algoritmo que sume el precio y le aplique
   otros costes en base a porcentajes sobre el valor del vehiculo.
   
   Entradas: el costo del veh�culo
   Salidas: el precio de venta al p�blico
*/

#include <iostream> //Inclusi�n de los recursos de entrada y salida

using namespace std;

int main()
{
	//Declaraci�n de variables y constantes 
	double precio_construccion;
	double precio_final;
	
	const double IVA = 0.16;
	const double VENDEDOR = 0.2;
	
	//Entradas
	cout << "Introduzca el coste de producci�n del veh�culo: ";
	cin >> precio_construccion;
	
	//Calculos
	precio_final = precio_construccion + precio_construccion * VENDEDOR;
	precio_final = precio_final + precio_construccion * IVA;
	
	//Salidas
	cout << "El PVP del veh�culo es: " << precio_final << " euros";
	
	return (0);
}
