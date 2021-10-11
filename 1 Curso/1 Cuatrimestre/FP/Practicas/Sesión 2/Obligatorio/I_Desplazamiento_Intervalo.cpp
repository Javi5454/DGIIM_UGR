//FP 
//Javier G�mez L�pez
/* Programa para posicionar un n�mero tras desplazarlo un n�mero de posiciones
   dentro de un intervalo.
   
   Para ello usaremos un algoritmo que nos permita determinar la posicion 
   nueva del numero en el intervalo y situarlo en este.
   
   Primero calcularemos el espacio del intervalo, luego el numero tras el 
   desplazamiento y finalmente la posici�n de este en el intervalo
   
   Entradas: un m�nimo, un m�ximo, un n�mero y un desplazamiento
   Salidas: la posici�n de dicho n�mero en el intervalo tras el 
            desplazamiento
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	/nt minimo;  //Declaraci�n de variables
	int maximo;
	int a_desplazar;
	int desplazamiento;
	
	int intervalo;
	int movimiento;
	int numero_movido;
	
//Entradas

cout << "El m�nimo de su intervalo es: ";
cin >> minimo;
cout << "El m�ximo de su intervalo es: ";
cin >> maximo;
cout << "El desplazamiento que desea realizar es: ";
cin >> desplazamiento;
cout << "Y el n�mero a desplazar es: ";
cin >> a_desplazar;

//Calculos

intervalo = maximo - minimo + 1; //Sumamos el 1 para tomar todos los 
movimiento = a_desplazar + desplazamiento;  //valores del intervalo
numero_movido = minimo + ((movimiento - minimo) % intervalo);

//Salidas
cout << "El n�mero desplazado es: " << numero_movido;

return (0);
}
