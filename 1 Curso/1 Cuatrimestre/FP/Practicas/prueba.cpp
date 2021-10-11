/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// PRUEBA 02 - TIPO B
//
/***************************************************************************/

#include<iostream>
#include <iomanip>
#include <string>
#include<ctime>
#include<cstdlib>
#include<cctype>
using namespace std;
	
/***************************************************************************/
/***************************************************************************/

int main()
{		
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	
    //.......................................................................
	// Para generar números aleatorios

	const int NUM_FILAS = 10;  // Núm. filas de la matriz
	const int NUM_COLS  = 10;  // Núm. filas de la matriz
	
	const int NUM_DATOS_LINEA = 10; // Para la presentación de datos
	
	int matriz_principal [NUM_FILAS][NUM_COLS];  //Inicializamos la matriz
	const int VALOR_MAX = 8; //Valor maximo aleatorio - 1
	
	int contador[VALOR_MAX]{0}; //El array de contadores 
	
	// Inicializa el generador de números aleatorios con el reloj del 
	// sistema  (hora actual)
	time_t t;
	srand ((int) time(&t)); 
	
	// RELLENAR MATRIZ
	int valor; //Valor que tomará cada casilla de la matriz
	
	for (int i = 0; i < NUM_FILAS; i++)
	{
		for(int j = 0; j < NUM_COLS; j++)
		{
			valor = rand() % 8; //Nums entre 0 - 7
			matriz_principal[i][j] = valor;
		}
	}
			
	// MOSTRAR MATRIZ
	
	cout << endl; 
	cout << "Matriz de valores: " << endl; 
	cout << endl; 
	
	for (int k = 0; k < NUM_FILAS; k++)
	{
		for(int m = 0; m < NUM_COLS; m++)
		{
			cout << setw(5) << matriz_principal[k][m];
		}
		cout << endl;
	}



	// CALCULAR CUÁNTAS VECES APARECE CADA VALOR  
	int valor_contador;
	
	for(int fil = 0; fil < NUM_FILAS; fil++)
	{
		for(int col = 0; col < NUM_COLS; col++)
		{
			valor_contador = matriz_principal[fil][col];
			
			switch(valor_contador)
			{
				case 0: contador[0]++;
				break;
				case 1: contador[1]++;
				break;
				case 2: contador[2]++;
				break;
				case 3: contador[3]++;
				break;
				case 4: contador[4]++;
				break;
				case 5: contador[5]++;
				break;
				case 6: contador[6]++;
				break;
				case 7: contador[7]++;
				break;
			}
		}
	}
	
	
	
	// INTEGRIDAD
	int valores_totales = 0;
	for (int pos = 0; pos < VALOR_MAX; pos++) //Sumamos todas las aparaciones
	{
		valores_totales = valores_totales + contador[pos];
	}
	
	cout << endl;
	
	if (valores_totales == NUM_FILAS * NUM_COLS)
	{
		cout << "Integridad veificada" << endl << endl;
	}
	else
	{
		cout << "Integridad erronea" << endl << endl;
	}


	// RESUMEN FINAL

	cout << endl << "Repeticiones: " << endl << endl;
	for (int mostrar = 0; mostrar < VALOR_MAX; mostrar++)
	{
		cout << "\t" << mostrar << ": " << contador[mostrar] << endl;
	}


	return 0;	
}

/***************************************************************************/
/***************************************************************************/
