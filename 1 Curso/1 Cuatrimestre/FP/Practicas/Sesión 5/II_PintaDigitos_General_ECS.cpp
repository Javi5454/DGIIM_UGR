//FP 
//Javier G�mez L�pez
/* Programa para leer un n�mero de tres d�gitos y separar
   sus n�meros con barras.
   
   Para ello trabajaremos con filtros en forma de ciclos do-while y 
   los posteriores c�lculos.
   
   Entradas: una cadena string de 3 d�gitos.
   
   Salidas: otra cadena string que con los n�meros de la original 
            separados
   
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <string>   //Inclusi�n de los recursos string

using namespace std;

int main()
{

    //Declaraci�n de variables
    string cad_entrada;
    int entero_entrada, numero;

    int cuenta_digitos = 0;
    string SEPARADOR = " | ";
    
    string resultado = " | ";
    int resto;

	//Entradas
	do 
	{
		cout << "Introduzca un entero positivo: ";
		cin >> cad_entrada;
		entero_entrada = stoi(cad_entrada);
		numero = entero_entrada;
	} while (entero_entrada <= 0);
	
	
    //C�clulos

    while (numero >= 10)
    {
    	resto = numero % 10;
    	
    	resultado = SEPARADOR + to_string(resto) + resultado;
    	
    	cuenta_digitos = cuenta_digitos + 1;
    	
    	numero = numero / 10;
    	
    }
    
    //Falta a�adir a�n el �ltimo d�gito
    resultado = SEPARADOR + to_string(numero) + resultado;
    
    cuenta_digitos = cuenta_digitos + 1;
		                       
	//Salida
	
	cout << endl;
	cout << "El n�mero tiene " << cuenta_digitos << " digitos" << endl;
	cout << "El n�mero es: " << resultado << endl;
    
	return (0);
}
