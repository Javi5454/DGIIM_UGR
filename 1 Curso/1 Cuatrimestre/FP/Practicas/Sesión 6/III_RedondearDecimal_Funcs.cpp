//FP 
//Javier G�mez L�pez
/* Programa que permitir� al usuario redondear un n�mero decimal seg�n
   la precisi�n que �l elija
   
   Para ello crearemos una funci�n que llamaremos potencia y otra que ser�
   redondeo
   
   Entradas: un n�mero decimal y el n�mero de decimales que deseamos redondear
   Salidas: el n�mero decimal redondeado
   
*//

#include <iostream> // Inclusi�n de los recursos de E/S
#include <cmath> // Inclusi�n de los recursos matem�ticos
#include <iomanip>

using namespace std;


double Potencia (double base, int exponente){

	
	double potencia = 1.0;
	
	// Si el exponente es positivo
	
	if (exponente >= 0){
		
		for (int i = 1; i <= exponente; i = i + 1){
			potencia = potencia * base;
		}
	}
	
	// Si el exponente es negativo
	
	else{
		
		for (int i = 1; i <= (exponente - 2*exponente); i = i + 1){
			potencia = (potencia / base);
		}
	}
	
	return (potencia);
}

// 2. Funci�n Redondear

double Redondear (double numero, double cifra_red){
	
	double num_aumentado;
	double num_redondeado;
	
	num_aumentado = numero * Potencia (10, cifra_red);
	
	if ((num_aumentado - floor(num_aumentado)) >= 0.5){
		
		num_redondeado = (floor(num_aumentado) + 1) * Potencia (10, -cifra_red);
	}
	
	else{
		
		num_redondeado = floor(num_aumentado) * Potencia (10, -cifra_red);
	}
	
	return (num_redondeado);
}

int main () // Programa principal
{
	// Declaraci�n de datos
	
	double numero; // N�mero a redondear;
	int cifra_redondeo; // Cifra hasta la que se quiere redondear
	double numero_redondeado; // Es el resultado del programa
	
	// Entrada de datos
	
	cout << "Introduzca el n�mero que desea redondear: ";
	cin >> numero;
	
	// Filtro para la cifra hasta la que se quiere redondear
	
	do{
		cout << "Introduzca la cifra decimal hasta la que desea redondear: ";
		cin >> cifra_redondeo;
	}
	while (cifra_redondeo < 0);
	
	// C�lculos
	
	numero_redondeado = Redondear (numero, cifra_redondeo);
	
	// Salida de datos
	
	cout << "El n�mero redondeado es " << setw(15) << setprecision(15) 
	<< numero_redondeado;
	
	return 0;
}


		
		
	
	

	
