//FP 
//Javier G�mez L�pez
/* Programa para calcular el espacio de tiempo entre dos instantes distintos
   manteniendo las unidades.
   
   Implementamos algoritmos de conversion de unidades en sistema sexagesimal.
   
   Adem�s nos dir� si los intervalos de tiempo est�n en d�as distintos. Por un 
   lado compararemos los segundos totales y por otro la diferencia entre los
   d�as
   
   Entradas: una cantidad de horas minutos y segundos
   Salidas: la diferencia transformada al sistema de h, min y segundos.
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	int hora_inicio;  //Declaraci�n de variables
	int minuto_inicio;
	int segundo_inicio;
	
	int hora_final;
	int minuto_final;
	int segundo_final;
	
	int hora_salida;
	int minuto_salida;
	int segundo_salida;
	
	int diferencia_total_segundos;
	
	const int DIFERENCIA_SEGUNDOS = 86400; //Numero de segundos que tiene un dia
	const int DIFERENCIA_HORAS = 24;
	const int HORAS_A_SEGUNDOS = 3600;
	const int MINUTOS_A_SEGUNDOS = 60;
	
//Entradas

cout << "El n�mero de segundos de inicio es: ";
cin >> segundo_inicio;
cout << "El n�mero de minutos de inicio es: ";
cin >> minuto_inicio;
cout << "El n�mero de horas de inicio es: ";
cin >> hora_inicio;

cout << "El n�mero de segundos final es: ";
cin >> segundo_final;
cout << "El n�mero de minutos final es: ";
cin >> minuto_final;
cout << "El n�mero de horas final es: ";
cin >> hora_final;

//C�lculos

segundo_salida = (segundo_final - segundo_inicio)%60;
minuto_inicio = minuto_inicio + (segundo_final - segundo_inicio)/60;
minuto_salida = (minuto_final - minuto_inicio)%60;
hora_inicio = hora_inicio + (minuto_final - minuto_inicio)/60;
hora_salida = hora_final - hora_inicio;


//Salidas

//Soluci�n en funci�n solo de los segundos

diferencia_total_segundos = hora_salida * HORAS_A_SEGUNDOS + minuto_salida 
                            * MINUTOS_A_SEGUNDOS + segundo_salida;
                            
if (diferencia_total_segundos >= DIFERENCIA_SEGUNDOS)
{
	cout << "Los instantes se encuentran en d�as distintos" << endl;
}
else 
{
	cout << "Los instantes se encuentran en el mismo d�a" << endl;
} 

//Soluci�n en funci�n de comparar las horas
if (hora_salida >= DIFERENCIA_HORAS)
{
	cout << "Los instantes se encuentran en d�as distintos" << endl;
}
else
{
	cout << "Los instantes se encuentran en el mismo d�a" << endl;
}

cout << "La diferencia son: " << segundo_salida << " segundos" << endl;
cout << "La diferencia son: " << minuto_salida << " minutos" << endl;
cout << "La diferencia son: " << hora_salida << " horas" << endl;

return (0);
}
