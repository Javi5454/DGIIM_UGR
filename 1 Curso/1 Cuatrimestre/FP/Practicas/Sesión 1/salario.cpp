//FP 
//Javier G�mez L�pez
/* Programa para comprobar la asignaci�n de una variable a lo
   largo de un programa.
*/

#include <iostream> //Inclusi�n de los recursos E/S
#include <cmath>    //Inclusi�n de los recursos matem�ticos

using namespace std;

int main()
{
	int salario_bas
int salario_final;
int incremento;
salario_base = 1000;
salario_final = salario_base;
incremento = 200;
salario_final = salario_final + incremento;
salario_base = 3500;
cout << "\nSalario base: " << salario_base;
cout << "\nSalario final: " << salario_final;

return(0);
}

/*
  Como podemos observar, las variables salario_final y salario_base
  no se encuentrna ligadas durante todo el programa
*/
