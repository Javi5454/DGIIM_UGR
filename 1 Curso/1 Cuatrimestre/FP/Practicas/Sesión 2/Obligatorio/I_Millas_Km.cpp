//FP 
//Javier G�mez L�pez
/* Programa para covnertir millas a kil�metros y viceversa.
   
   Implementamos las covnersiones que se muestran en el enunciado
   del ejercicio.
   
   Entradas: una cantidad de kil�metros para convertir en millas
             y viceversa.
   Salidas: los kil�metros de entrada convertidos en millas y las millas
            de entrada convertidas en kil�metros.

*/

#include <iostream>  //Inclusi�n de los recursos E/S
#include <cmath>     //Inclusui�n de los recursos matem�ticos

using namespace std;

int main()
{
	double millas_entrada;  //Declaramos las variables de entrada y salida
	double millas_salida;
	double km_entrada;
	double km_salida;
	
	const double KM_A_MILLAS = 1/1.609; //Declaramos los factores de conversi�n
	const double MILLAS_A_KM = 1.609;
	
//Entradas millas a km
cout << "La cantidad de millas que desea convertir en km es: ";
cin >> millas_entrada;

//C�lculos millas a km

km_salida = millas_entrada * MILLAS_A_KM;

//Salidas millas a km
cout << millas_entrada << " millas son " << km_salida << " km" << endl;

//Entradas km a millas 
cout << "La cantidad de km que desea convertir en millas es: ";
cin >> km_entrada;

//C�lculos km a millas
millas_salida = km_entrada * KM_A_MILLAS;

//Salidas km a millas
cout << km_entrada << " km son " << millas_salida << " millas" << endl;

return (0);
}
