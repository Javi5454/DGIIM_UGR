//FP 
//Javier G�mez L�pez
/* Programa para devolver la mayor tabla rectangular que se encuentre dentro 
   de una dentada
*/

#include <iostream>
#include <string> 
#include <iomanip>
#include<ctime>
#include<cstdlib>
#include<cctype>
#include <cmath>

using namespace std;

//Definimos la clase SecuenciaReales

class SecuenciaReales
{

private:
	
	static const int TAMANIO = 50; //Numeros de casillas disponibles
	double vector_privado[TAMANIO];
	
	//PRE: 0 <= total_utilizados < TAMANIO
	int total_utilizados;  //Numero de casillas ocupadas
	
public:
	
	//Constructor sin argumentos
	SecuenciaReales (void): total_utilizados(0) {}
	
	
	//Metodos Get 
	
	//Devuelve el numero total de casillas utilizadas
	int TotalUtilizados (void)
	{
		return total_utilizados;
	}
	
	//Devuelve el numero de casillas disponibles
	int Capacidad (void)
	{
		return TAMANIO;
	}
	
	
	// A�ade un elemento al vector.
	// Recibe: nuevo, el elemento que se va a a�adir.
	//
	// PRE: total_utilizados < TAMANIO
	// 		La adici�n se realiza si hay espacio para el nuevo elemento.
	// 		El nuevo elemento se coloca al final del vector.
	// 		Si no hay espacio, no se hace nada.

	void Aniade (double nuevo)
	{
		if (total_utilizados < TAMANIO) {
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}
	
	/***********************************************************************/
	// Eliminar el dato de la posici�n dada por "indice".
	// Realiza un borrado f�sico (con desplazamiento y sustituci�n).
	//
	// PRE: 0 <= indice < total_utilizados

	void Elimina (int indice)
	{
		// Recorremos de izquierda a derecha toda las componentes
		// que hay a la derecha de la posici�n a eliminar
		//		Le asignamos a cada componente la que hay a su derecha

		if ((indice >= 0) && (indice < total_utilizados)) {

			int tope = total_utilizados-1; // posici�n del �ltimo

			for (int i = indice ; i < tope ; i++)
				vector_privado[i] = vector_privado[i+1];

			total_utilizados--;
		}
	}
	
	/***********************************************************************/
	// Devuelve el elemento de la casilla "indice"
	//
	// PRE: 0 <= indice < total_utilizados

	double Elemento (int indice)
	{
		return vector_privado[indice];
	}
	
	/***********************************************************************/
	// Devuelve true si la secuencia est� vac�a

	bool EstaVacia (void)
	{
		return (total_utilizados == 0);
	}
	
	/***********************************************************************/
	// "Vac�a" una secuencia

	void EliminaTodos (void)
	{
		total_utilizados = 0;
	}
		
	/***********************************************************************/
	// Devuelve la posici�n del m�nimo valor de la secuencia
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	int PosicionMinimo (int izda, int dcha)
	{
		int posicion_minimo;
		double minimo;

		minimo = vector_privado[izda];
		posicion_minimo = izda;

		for (int i = izda; i <= dcha ; i++) {

			if (vector_privado[i] < minimo){
				minimo = vector_privado[i];
				posicion_minimo = i;
			}
		}

		return (posicion_minimo);
	}
	
	/***********************************************************************/
	// Devuelve la posici�n del m�ximo valor de la secuencia
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	int PosicionMaximo (int izda, int dcha)
	{
		int posicion_maximo;
		double maximo;

		maximo = vector_privado[izda];
		posicion_maximo = izda;

		for (int i = izda; i <= dcha ; i++) {

			if (vector_privado[i] > maximo){
				maximo = vector_privado[i];
				posicion_maximo = i;
			}
		}

		return (posicion_maximo);
	}
	
	/***********************************************************************/
	// Devuelve el m�nimo de la secuencia.
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	double Minimo (int izda, int dcha)
	{
		return (vector_privado[PosicionMinimo(izda, dcha)]);
	}
	
	/***********************************************************************/
	// Devuelve el m�ximo de la secuencia.
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	double Maximo (int izda, int dcha)
	{
		return (vector_privado[PosicionMaximo(izda, dcha)]);
	}
	
	//Metodo ToString
	string ToString (void)
	{
		string cadena;

		cadena = "|";
		for (int i=0; i<total_utilizados; i++)
			cadena = cadena + to_string(vector_privado[i]) + "|";

		return (cadena);
	}
};


//Definamos la clase TablaRectangularReales

class TablaRectangularReales
{

private:

    static const int NUM_FILS = 50; // Filas disponibles
    static const int NUM_COLS = 50; // Columnas disponibles
    
    double matriz_privada[NUM_FILS][NUM_COLS];

    // PRE: 0 <= filas_utilizadas <= NUM_FILS
    // PRE: 0 <= col_utilizadas < NUM_COLS
    
    int filas_utilizadas;
    int cols_utilizadas;

public:

	/***********************************************************************/
	// Constructor sin argumentos--> Crea matriz nula

	TablaRectangularReales(void): filas_utilizadas(0), cols_utilizadas(0) {}
	
	/***********************************************************************/
	// Constructor--> Recibe "numero_de_columnas" que indica el n�mero de 
	// columnas que deben tener TODAS las filas. 
	// PRE: numero_de_columnas <= MAX_COL

	TablaRectangularReales (int numero_de_columnas) : filas_utilizadas(0), 
		  cols_utilizadas(numero_de_columnas)
	{ }

	/***********************************************************************/
	// Constructor--> Recibe una secuencia de enteros.  El n�mero de 
	// elementos de la secuencia es el valor que se usa como "col_utilizadas"
	// PRE: primera_fila.TotalUtilizados() <= MAX_COL

	TablaRectangularReales (SecuenciaReales primera_fila)
		: filas_utilizadas(0), cols_utilizadas (primera_fila.TotalUtilizados())
	{
		Aniade(primera_fila); // Actualiza "filas_utilizadas"
	}

	/***********************************************************************/
	// M�todo de lectura: n�mero m�ximo de filas

	int CapacidadFilas (void)
	{
		return (NUM_FILS);
	}

	/***********************************************************************/
	// M�todo de lectura: n�mero m�ximo de columnas

	int CapacidadColumnas (void)
	{
		return (NUM_COLS);
	}

	/***********************************************************************/
	// M�todo de lectura: n�mero real de filas usadas

	int FilasUtilizadas (void)
	{
		return (filas_utilizadas);
	}

	/***********************************************************************/
	// M�todo de lectura: n�mero real de columnas usadas

	int ColumnasUtilizadas (void)
	{
		return (cols_utilizadas);
	}

	/***********************************************************************/
	// M�todo de lectura: devuelve el dato que ocupa la casilla 
	// de coordenadas (fila, columna)
	// PRE: 0 <= fila < filas_utilizadas
	// PRE: 0 <= columna < cols_utilizadas	
	
	double Elemento (int fila, int columna)
	{
		return (matriz_privada[fila][columna]);
	}

	/***********************************************************************/
	// Devuelve true si la tabla est� vac�a

	bool EstaVacia (void)
	{
		return (filas_utilizadas == 0);
	}
	
	/*****************************************************************/
	// Devuelve una fila completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_fila < filas_utilizadas
	
	SecuenciaReales Fila (int indice_fila)
	{
		SecuenciaReales fila;

		for (int col=0; col<cols_utilizadas; col++)
			fila.Aniade(matriz_privada[indice_fila][col]);

		return (fila);
	}

	/***********************************************************************/
	// Devuelve una columna completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_columna < cols_utilizadas
	
	SecuenciaReales Columna (int indice_columna)
	{
		SecuenciaReales columna;

		for (int fil=0; fil<filas_utilizadas; fil++)
			columna.Aniade (matriz_privada[fil][indice_columna]);

		return (columna);
	}

	/***********************************************************************/
	// A�ade una fila completa (un objeto "SecuenciaEnteros")
	// PRE:  fila_nueva.TotalUtilizados() = cols_utilizadas
	// PRE:  filas_utilizadas < MAX_FIL
	
	void Aniade (SecuenciaReales fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		if ((filas_utilizadas < NUM_FILS) &&
			(cols_utilizadas < NUM_COLS)) {

			for (int col = 0; col < numero_columnas_fila_nueva; col++)
				matriz_privada[filas_utilizadas][col]=fila_nueva.Elemento(col);
		}
		
		cols_utilizadas = fila_nueva.TotalUtilizados();
		filas_utilizadas++;
	}

	/***********************************************************************/
	// "Vac�a" una tabla

	void EliminaTodos (void)
	{
		filas_utilizadas = 0;
	}
	
	/***********************************************************************/
	// Calcula si dos matrices rectangulares son iguales
	// Compara la tabla impl�cita con "otra" (tabla expl�cita) 

	bool EsIgual (TablaRectangularReales otra_tabla)
	{
		bool son_iguales = true; 
		
		if ((filas_utilizadas != otra_tabla.FilasUtilizadas()) ||  
			 (cols_utilizadas != otra_tabla.ColumnasUtilizadas()))		
			
			son_iguales = false;
		
		else {
			
			int f=0; 
			
			while (f<filas_utilizadas && son_iguales) {
				
				int c=0; 
				
				while (c<cols_utilizadas && son_iguales) {
			
					if (matriz_privada[f][c] != otra_tabla.Elemento(f,c)) 
						son_iguales = false;
						
					c++;
					
				} // while c
	
				f++;
					
			} // while f
					
		} // else 
	
		return (son_iguales);
	}
	
	

	/***********************************************************************/
	// Calcula si una matriz es sim�trica.
	// CONDICI�N NECESARIA: debe ser cuadrada. 
	// Este m�todo comprueba directamente si cada componente es igual a
	// su sim�trica, parando el recorrido cuando encuentre una componente
	// que no lo verifique.
	//
	// Evita el c�lculo de la traspuesta, y el problema que puede surgir
	// si no se puede calcular la traspuesta de la matriz por problemas de
	// capacidad.

	bool EsSimetrica (void)
	{
		bool es_simetrica = true;

		// Si el n�mero de filas y columnas no coinciden, no hay que seguir
		// porque la matriz no es sim�trica.

		es_simetrica = (filas_utilizadas == cols_utilizadas);

		if (es_simetrica) {

			int f=0;

			while (f<filas_utilizadas && es_simetrica) {

				int c=0;

				while (c<cols_utilizadas && es_simetrica) {

					if (matriz_privada[f][c] != matriz_privada[c][f])
						es_simetrica = false;

					c++;

				} // while c

				f++;

			} // while f

		} // if (es_simetrica)

		return (es_simetrica);
	}
					
	/***********************************************************************/
	// Inserta una fila completa en una posici�n dada. 
	// La fila se porporciona en un objeto "SecuenciaEnteros".
	// 
	// Recibe: num_fila, la posici�n que ocupar� "fila_nueva" cuando se 
	//		 		inserte en la tabla.
	//		   fila_nueva, la secuencia que se va a insertar. Se trata 
	//				de un objeto de la clase "SecuenciaEnteros". 
	//
	// PRE:  fila_nueva.TotalUtilizados() = cols_utilizadas
	// PRE:  filas_utilizadas < MAX_FIL
	// PRE:  0 <= num_fila <= TotalUtilizados()
	//		 Si num_fila = 0, "nueva_fila" ser� la nueva primera fila. 
	//		 Si num_fila = TotalUtilizados(), "nueva_fila" ser� la nueva 
	//		 �ltima fila (el resultado ser� equivalente al de "Aniade()" 
	
	void Inserta (int num_fila, SecuenciaReales fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		// Comprobar precondiciones
		
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva == cols_utilizadas) && 
			(0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones altas. 
			// La �ltima fila se copia en una NUEVA FILA que ocupa la 
			// posici�n "filas_utilizadas", la pen�ltima se copia en 
			// "filas_utilizadas"-1, ... y se queda un "hueco" en 
			// la fila "num_fila ".
			// NOTA: no se modifica (todav�a) "filas_utilizadas" 
			
			for (int fil=filas_utilizadas; fil>num_fila; fil--) {
				
				for (int col = 0; col < numero_columnas_fila_nueva; col++)
					matriz_privada[fil][col]=matriz_privada[fil-1][col];
			}
			
			// Copiar en el "hueco" (fila "num_fila") el contenido de 
			// la secuencia "fila_nueva"
			
			for (int col = 0; col < numero_columnas_fila_nueva; col++)
				matriz_privada[num_fila][col]=fila_nueva.Elemento(col);	
			
			filas_utilizadas++; // Actualizaci�n del tama�o de la tabla.
		}
	}

	/***********************************************************************/
	// Elimina una fila completa, dada una posici�n. 
	// 
	// Recibe: num_fila, la posici�n de la fila a eliminar.
	// PRE:  0 <= num_fila < TotalUtilizados()
	
	void Elimina (int num_fila)
	{		
		// Comprobar precondiciones
		
		if ((0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones bajas. 
			// En la posici�n "num_fila" se copia la que est� en la posici�n
			// siguiente ("num_fila"+1), en su lugar se copia que est� en 
			// "num_fila"+2, ... y en la posici�n "total_utilizados"-2 se 
			// copia la de "total_utilizados"-1. 
			
			for (int fil=num_fila; fil<filas_utilizadas-1; fil++) {
			
				int num_columnas = cols_utilizadas;
					
				for (int c=0; c<num_columnas; c++) 
					matriz_privada[fil][c]=matriz_privada[fil+1][c];
			}
			
			filas_utilizadas--; // Actualizaci�n del tama�o de la tabla.
		}
	}	
	
	/***********************************************************************/
	// Devuelve TRUE si la matriz contiene el valor "buscado"
	
	bool Contiene (int buscado)
	{
		bool encontrado = false;

		// Recorrido por columnas 

		int col = 0;

		while (col < cols_utilizadas && !encontrado) {

			int fil=0;

			while (fil < filas_utilizadas && !encontrado) {

				if (matriz_privada[fil][col] == buscado)
					encontrado = true;
				
				fil++;

			} // while fil

			col++; 

		} // while col

		return (encontrado);
	}
	
	
	//Metodo para encontrar la fila mas parecia a un elemento
	
	int MasParecida (SecuenciaReales referencia, SecuenciaReales filas_a_comparar)
	{
	    double distancias[filas_a_comparar.TotalUtilizados()];
	    
	    for(int i = 0; i < filas_a_comparar.TotalUtilizados(); i++)
	    {
	        double distancia = 0;
	        
	        for (int k = 0; k < referencia.TotalUtilizados(); k++)
	        {
	            distancia = distancia + 
                pow((referencia.Elemento(k) - 
                matriz_privada[int(filas_a_comparar.Elemento(i))][k]), 2);
                
                distancia = sqrt(distancia);
            }
            
            distancias[i] = distancia;
        }
        
        double distancia_min = distancias[0];  //El primer valor
        double resultado = filas_a_comparar.Elemento(0);
        
        for(int m = 1; m < filas_a_comparar.TotalUtilizados(); m++)
        {
            if(distancia_min > distancias[m])
            {
                distancia_min = distancias[m];
                resultado = filas_a_comparar.Elemento(m);
            }
        }
        
        return resultado;
    }
	        	

	/***********************************************************************/
};

//Definimos la clase TablaDentadaREales


class TablaDentadaReales
{
	
private:

    static const int NUM_FILS = 50;  // Filas disponibles
    static const int NUM_COLS = 40;  // Columnas disponibles

    double matriz_privada[NUM_FILS][NUM_COLS];

    // PRE: 0 <= filas_utilizadas <= NUM_FILS

    int filas_utilizadas;

    // PRE: 0 <= num_cols_utilizadas[i] <= NUM_COLS
    //      para i=0,1,...,filas_utilizadas-1
    // N�mero de columnas ocupadas en cada fila

    int num_cols_utilizadas[NUM_FILS] = {0};

public:

	/***********************************************************************/
	// Constructor sin argumentos--> Crea matriz nula

	TablaDentadaReales (void) : filas_utilizadas(0) { }
	
	/***********************************************************************/
	// Constructor--> Recibe una secuencia de caracteres que ser� la primera 
	// fila de la tabla. 

	TablaDentadaReales (SecuenciaReales primera_fila)
		: filas_utilizadas(0)
	{
		Aniade(primera_fila); // Actualiza "filas_utilizadas"
	}
	
	/***********************************************************************/
	// M�todo de lectura: n�mero m�ximo de filas

	int CapacidadFilas (void)
	{
		return (NUM_FILS);
	}

	/*****************************************************************/
	// M�todo de lectura: n�mero m�ximo de columnas

	int CapacidadColumnas (void)
	{
		return (NUM_COLS);
	}

	/*****************************************************************/
	// M�todo de lectura: n�mero real de filas usadas

	int FilasUtilizadas (void)
	{
		return (filas_utilizadas);
	}

	/*****************************************************************/
	// M�todo de lectura: n�mero real de columnas usadas en la fila "fila"
	// PRE: 0 <= fila < filas_utilizadas
	
	int ColumnasUtilizadas (int fila)
	{
		return (num_cols_utilizadas[fila]);
	}

	/*****************************************************************/
	// M�todo de lectura: devuelve el dato que ocupa la casilla 
	// de coordenadas (fila, columna)
	// PRE: 0 <= fila < filas_utilizadas
	// PRE: 0 <= columna < num_cols_utilizadas[fila]	
	
	double Elemento (int fila, int columna)
	{
		return (matriz_privada[fila][columna]);
	}

	/***********************************************************************/
	// Devuelve true si la tabla est� vac�a

	bool EstaVacia (void) 
	{
		return (filas_utilizadas == 0);
	}
	
	/***********************************************************************/
	// "Vac�a" una tabla
	
	void EliminaTodos (void)
	{
		filas_utilizadas = 0;
	}
	
	/*****************************************************************/
	// Devuelve una fila completa (un objeto "SecuenciaCaracteres")
	// PRE: 0 <= indice_fila < filas_utilizadas
	
	SecuenciaReales Fila (int indice_fila)
	{
		SecuenciaReales la_fila;
				
		int num_columnas = num_cols_utilizadas[indice_fila];
			
		for (int c=0; c<num_columnas; c++) 
			la_fila.Aniade (matriz_privada[indice_fila][c]);
		
		return (la_fila);
	}

	/*****************************************************************/
	// A�ade una fila completa. La fila se porporciona en un objeto de 
	// la clase "SecuenciaCaracteres".
	// PRE:  fila_nueva.TotalUtilizados() <= NUM_COLS
	// PRE:  filas_utilizadas < NUM_FILS
	
	void Aniade (SecuenciaReales fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva <= NUM_COLS)) {

			for (int c=0; c<numero_columnas_fila_nueva; c++) 
				matriz_privada[filas_utilizadas][c] = fila_nueva.Elemento(c);

			num_cols_utilizadas[filas_utilizadas]=numero_columnas_fila_nueva;
			
			filas_utilizadas++;
		}
	}

	/*****************************************************************/
	// Calcula si dos matrices dentadas son iguales

	bool EsIgual (TablaDentadaReales otra_tabla)
	{
		bool son_iguales = true; 
		
		if (filas_utilizadas != otra_tabla.FilasUtilizadas())
			
			son_iguales = false;
		
		else {
			
			int f=0; 
			
			while (f<filas_utilizadas && son_iguales) {
				
				if (num_cols_utilizadas[f] != otra_tabla.ColumnasUtilizadas(f)) 
				
					son_iguales = false;	
				
				else {
					
					int c=0; 
					
					while (c<num_cols_utilizadas[f] && son_iguales) {
				
						if (matriz_privada[f][c] != otra_tabla.Elemento(f,c)) 
							son_iguales = false;
							
						c++;
						
					} // while c
		
					f++;
					
				} // else 
					
			} // while f
					
		} // else 
	
		return (son_iguales);
	}
	
	/*****************************************************************/
	// Inserta una fila completa en una posici�n dada. 
	// La fila se porporciona en un objeto "SecuenciaReales".
	// 
	// Recibe: num_fila, la posici�n que ocupar� "fila_nueva" cuando se 
	//		 		inserte en la tabla.
	//		   fila_nueva, la secuencia que se va a insertar. Se trata 
	//				de un objeto de la clase SecuenciaCaracteres. 
	//
	// PRE:  fila_nueva.TotalUtilizados() <= NUM_COLS
	// PRE:  filas_utilizadas <= NUM_FILS
	// PRE:  0 <= num_fila <= TotalUtilizados()
	//		 Si num_fila = 0, "nueva_fila" ser� la nueva primera fila. 
	//		 Si num_fila = TotalUtilizados(), "nueva_fila" ser� la nueva 
	//		 �ltima fila (el resultado ser� equivalente al de "Aniade()" 
	
	void Inserta (int num_fila, SecuenciaReales fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		// Comprobar precondiciones
		
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva <= NUM_COLS) &&
			(0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones altas. 
			// La �ltima fila se copia en una NUEVA FILA que ocupa la 
			// posici�n "filas_utilizadas", la pen�ltima se copia en 
			// "filas_utilizadas"-1, ... y se queda un "hueco" en 
			// la fila "num_fila ".
			// NOTA: no se modifica (todav�a) "filas_utilizadas" 
			
			for (int fil=filas_utilizadas; fil>num_fila; fil--) {	
			
				int num_columnas = num_cols_utilizadas[fil-1];
					
				for (int c=0; c<num_columnas; c++) 
					matriz_privada[fil][c] = matriz_privada[fil-1][c]; 
					
				num_cols_utilizadas[fil] = num_cols_utilizadas[fil-1];
			}
					
			// Copiar en el "hueco" (fila "num_fila") el contenido de 
			// la secuencia "fila_nueva"
			
			for (int c=0; c<numero_columnas_fila_nueva; c++) 
				matriz_privada[num_fila][c] = fila_nueva.Elemento(c);
			
			num_cols_utilizadas[num_fila] = numero_columnas_fila_nueva;
			
			filas_utilizadas++; // Actualizaci�n del tama�o de la tabla.
		}
	}

	/*****************************************************************/
	// Elimina una fila completa, dada una posici�n. 
	// 
	// Recibe: num_fila, la posici�n de la fila a eliminar.
	// PRE:  0 <= num_fila < TotalUtilizados()
	
	void Elimina (int num_fila)
	{		
		// Comprobar precondiciones
		
		if ((0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones bajas. 
			// En la posici�n "num_fila" se copia la que est� en la posici�n
			// siguiente ("num_fila"+1), en su lugar se copia que est� en 
			// "num_fila"+2, ... y en la posici�n "total_utilizados"-2 se 
			// copia la de "total_utilizados"-1. 
			
			for (int fil=num_fila; fil<filas_utilizadas-1; fil++) {
			
				int num_columnas = num_cols_utilizadas[fil+1];
					
				for (int c=0; c<num_columnas; c++) 
					matriz_privada[fil][c]=matriz_privada[fil+1][c];
					
				num_cols_utilizadas[fil] = num_cols_utilizadas[fil+1];
			}
			
			filas_utilizadas--; // Actualizaci�n del tama�o de la tabla.
		}
	}
	
	
	//Metodo para calcular la suma de cada fila
	
	SecuenciaReales SumaFilas (void)
	{
	    SecuenciaReales resultado;
	    
	    for(int i = 0; i < filas_utilizadas; i++)
	    {
	        double suma = 0;
	        
	        for(int k = 0; k < num_cols_utilizadas[i]; k++)
	        {
	            
	            suma = suma + matriz_privada[i][k];
	        }
	        
	        resultado.Aniade(suma);
	    }
	    
	    return resultado;
	}
	
	
	//Metodo para encontar la tabla rectangular inscrita
	
	TablaRectangularReales MinimaRectangular (void)
	{
	    
	    int min_cols = num_cols_utilizadas[0]; //Buscamos el n� min de cols
	    
	    for(int i = 1; i < filas_utilizadas; i++)
	    {
	        if (num_cols_utilizadas[i] < min_cols)
	        {
	            min_cols = num_cols_utilizadas[i];
	        }
	    }
	    
	    //Ahora creamos la tabla rectangular
	    TablaRectangularReales resultado(min_cols);
	    
	    for(int k = 0; k < filas_utilizadas; k++)
	    {
	        SecuenciaReales fila;  //Creamos las filas que a�adimos
	        
	        for (int l = 0; l < min_cols; l++)
	        {
	            double elemento;
	            elemento = matriz_privada[k][l];
	            
	            fila.Aniade(elemento);
	        }
	        
	        resultado.Aniade(fila);
	    }
	    
	    return resultado;
	}
	    
		
	/*********************************************************************/
	// Forma un string con el contenido de la tabla.  
	// La primera l�nea es el encabezamiento indicado en "titulo".
	
	string ToString (string titulo)
	{
		string cad; 
		
		cad = "\n" + titulo + "\n"; 	
		cad = cad + "\n--------------------------------------\n"; 
		
		for (int fila=0; fila<filas_utilizadas; fila++) {
	
			SecuenciaReales la_secuencia = Fila(fila);
			
			int num_datos = la_secuencia.TotalUtilizados();
	
			cad = cad + "Fila " + to_string(fila); 
			cad = cad + " (" + to_string(num_datos) + " datos): "; 
			cad = cad + la_secuencia.ToString() + "\n";
		}
		
		cad = cad + "--------------------------------------\n"; 
		cad = cad + "\n\n";
		
		return (cad); 
	}
	
	/*****************************************************************/

};


//Funcion principal

int main()
{
    
    // Para generar n�meros aleatorios

	const int NUM_FILAS = 7;  // N�m. filas de la matriz
	
	TablaDentadaReales tabla;  //Inicializamos la tabla
	SecuenciaReales rellenar; //Secuencia para rellenar la tabla
	
	// Inicializa el generador de n�meros aleatorios con el reloj del 
	// sistema  (hora actual)
	time_t t;
	srand ((double) time(&t)); 
	
	// RELLENAR MATRIZ
	
	for (int i = 0; i < NUM_FILAS; i++)
	{
	    int cols = rand() % 10 + 1;
	    
		for(int j = 0; j < cols; j++)
		{
			double valor = (rand() % 10001);
            valor = valor/1000; //Nums entre 0 - 10 decimales
			rellenar.Aniade(valor);
		}
		
		tabla.Aniade(rellenar);
		rellenar.EliminaTodos();
	}
	
	cout << endl; 
	cout << "Matriz Dentada:" << endl; 
	cout << endl; 
	
	for (int k = 0; k < NUM_FILAS; k++)
	{
		SecuenciaReales mostrar;
		mostrar = tabla.Fila(k);
		
		for (int l = 0; l < mostrar.TotalUtilizados(); l++)
		{
		    cout << setw(7) << mostrar.Elemento(l);
		}
		
		cout << endl;
	}
	
	//Mostramos resultados
	cout << endl << endl;
	cout << "-------------------------------" << endl;
	
	TablaRectangularReales final;
	final = tabla.MinimaRectangular();
	cout << endl; 
	
	cout << "Matriz Rectangular:" << endl; 
	cout << endl; 
	
	for (int k = 0; k < NUM_FILAS; k++)
	{
		SecuenciaReales mostrar;
		mostrar = final.Fila(k);
		
		for (int l = 0; l < mostrar.TotalUtilizados(); l++)
		{
		    cout << setw(7) << mostrar.Elemento(l);
		}
		
		cout << endl;
	}
	
	return 0;
}
