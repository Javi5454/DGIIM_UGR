//FP 
//Javier G�mez L�pez
/* Programa para yruncar un n�mero real tantos decimales como pida
   el usuario.
   
   Para ello guardaremos la parte enterea del real en una variable, 
   la parte decimal la multiplicaremos por 10 elevado al n�mero de decimales
   pedido por el usuario y guardaremos su parte entera en otra variable.
   
   Tras esto, dividiremos dicha parte entera entre 10 elevado de nuevo 
   al entero introducido por el usuario y lo sumaremos a la parte entera
   del real guardada anteriormente.
   
   Entradas: un real con los n�meros decimales que desee el usuario
             y un entero.
   Salidas: el n�mero real truncado a los decimales pedidos por el usuario
*/

#include <iostream>  //Inclusi�n de los recursos de entrada y salida
#include <cmath>     //Inclusi�n de los recursos de matem�ticas

using namespace std;

int main()
{
	//Declaraci�n de variables
	double real_entrada;
	int entero_entrada;
	int r_entero;
	double r_decimales;
	double r_truncado;
	
	//Entradas
	cout << "Introduzca un n�mero real a truncar: ";
	cin >> real_entrada;
	cout << "Introduzca el n�mero de decimales a truncar: ";
	cin >> entero_entrada;
	
	//C�lculos
	bool aux = entero_entrada > 0;
	r_entero = int(real_entrada);
	r_decimales = real_entrada - r_entero;
	r_decimales = r_decimales * pow(10, entero_entrada);
	r_decimales = int(r_decimales);
	r_decimales = (r_decimales / (pow(10, entero_entrada))) * aux;
	r_truncado = r_entero + r_decimales;
	
	//Salidas
	cout << "El n�mero truncado es: " << r_truncado;
	
	return (0);
}
