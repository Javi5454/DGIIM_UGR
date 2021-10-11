//FP 
//Javier G�mez L�pez
/* Programa para calcular el valor del voltaje dado intensidad y resistencia
   
   Entradas: el valor de la intensidad de la resistencia
   Salidas: el voltaje
                  
                       V = I x R
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()  //Programa principal
{

double resistencia;  //Declara variables para guardar
double intensidad;   //la resistencia y la intensidad y el voltaje
double voltaje;

//Entrada de datos

cout << "Introduzca la resistencia: "  ;
cin >> resistencia;
cout << "Introduzca la intensidad: ";
cin >> intensidad;

//C�lculos

voltaje = intensidad * resistencia;    

//Salida

cout << endl;
cout << "El voltaje vale: " << voltaje << endl;

return (0);
}
