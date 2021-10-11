//FP 
//Javier G�mez L�pez
/* Programa para convertir un ritmo (min/km) a velocidad (km/h).
   
   Implementamos algoritmos de conversion de unidades de ritmo a velocidad.
   
   Entradas: una cantidad de minutos y segundos por km
   Salidas: ese ritmo transformado a velocidad.
   
                       1min          1km
                    ---------- = -----------
                        1km          60min
                        
                        
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	int minutos_entrada; //Declaraci�n de variables
	int segundos_entrada;
	double tiempo_minutos;
	
	double velocidad_salida;
	
//Entrada

cout << "Los minutos en lo que usted se hace un kil�metro son: ";
cin >> minutos_entrada;
cout << "Y los segundos exactos que tarda tras esos minutos son: ";
cin >> segundos_entrada;

//C�lculos

tiempo_minutos = minutos_entrada + (double(segundos_entrada)/60);
velocidad_salida = 60 / tiempo_minutos;

//Salidas
cout << "Su ritmo es: " << velocidad_salida << " km/h";

return (0);

}
