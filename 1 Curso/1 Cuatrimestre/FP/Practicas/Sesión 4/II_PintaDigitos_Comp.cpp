//FP 
//Javier G�mez L�pez
/* Programa para leer un n�mero de tres d�gitos y separar
   sus n�meros por espacios.
   
   Para ello trabajaremos con condicionales (para comprobar si realmente
   se han introducido tres d�gitos) y con cadenas string
   
   Entradas: una cadena string de 3 d�gitos.
   
   Salidas: otra cadena string que con los n�meros de la original 
            separados
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <string>   //Inclusi�n de los recursos string

using namespace std;

int main()
{
	//Declaracion de variables
	string cad_3digitos;
	
	cout << "Introduce un n�mero entero de tres d�gitos: ";
	getline (cin, cad_3digitos);
	
	
	if (cad_3digitos.length() != 3)
	{
		cout << "Usted ha introducido un n�mero no valido";
	}
	else
	{
		int num_3digitos;
		int num_2digitos;
		
		int centenas;
		int decenas;
		int unidades;
		
		num_3digitos = stoi(cad_3digitos);
		
		centenas = num_3digitos / 100;
		num_2digitos = num_3digitos % 100;
		
		decenas = num_2digitos / 10;
		unidades = num_2digitos % 10;
		
		const string ESPACIO = "    ";
		string cad_resultado = to_string(centenas) + 
		                       ESPACIO + to_string(decenas) +
		                       ESPACIO + to_string (unidades);
	
		                       
	//Salida
	
	cout << endl;
	cout << cad_resultado << endl;
    }
	
	return (0);
}
