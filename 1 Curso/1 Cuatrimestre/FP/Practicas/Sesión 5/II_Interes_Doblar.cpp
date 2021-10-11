/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI�N
//
// (C) FRANCISCO JOS� CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI�N E INTELIGENCIA ARTIFICIAL
//
// RELACI�N DE PROBLEMAS 2
// 
/*	
   Programa que calcula el dinero que se obtiene al realizar una 
   inversi�n un n�mero dado de a�os.

   Entradas: capital a invertir (capital_inicial)
			 inter�s a aplicar (interes)
			 n�mero de a�os de la inversi�n (numero_anios)
   Salidas:  dinero total obtenido por la inversi�n 
			 (capital + ganancia obtenida) calculado -anualmente- por: 
				total = capital + (capital * interes/100)
			  reinvirtiendo cada a�o el nuevo total.
			  
	Se comprueba la validez de los valores le�dos usando filtros	  
*/
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
	const int MIN_CAPITAL = 1000;
	const int MIN_INTERES =  0;
	const int MAX_INTERES = 10;
	
	// Entradas: 
	double interes, capital_inicial;
	int numero_anios;
	   
	// Salidas
	double capital_objetivo;
	
	cout.setf(ios::fixed);		// Notaci�n de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales 

	// Lectura y filtrado de datos

	const string mensaje_capital =  "Introduzca capital inicial (capital >= "
	      + to_string(MIN_CAPITAL) + "): ";
	const string mensaje_interes =  "Introduzca % interes (" 
	      + to_string(MIN_INTERES) + "-" +  to_string(MAX_INTERES) + "): ";
	      	      
	do {	
		cout << mensaje_capital;
		cin >> capital_inicial;
	} while (capital_inicial < MIN_CAPITAL);
		
	do {	
		cout << mensaje_interes;
		cin >> interes;   
   	} while ((interes<= MIN_INTERES) || (interes>MAX_INTERES));

	cout << endl;
	
	// C�lculos y presentaci�n de resultados
	
	capital_objetivo = capital_inicial; // Capital inicial
	
	numero_anios  = 0; // contador de a�os 
   
	while (capital_objetivo <= capital_inicial * 2) {  //Para comprobar si se
                                                       //se ha doblado
		capital_objetivo = capital_objetivo  +  
		                   (capital_objetivo * (interes / 100.0));   

		numero_anios++; // actualizar el a�o de inversi�n 
   }

	cout << endl;
	cout << "Para doblar el capital necesitar� como m�nimo: " <<  numero_anios
	     << " a�os";
   
   return 0;
}
