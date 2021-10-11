//FP 
//Javier G�mez L�pez
/* Programa que permitir� al usuario elegir entre dos men�s distintos
   para realizar distintas operaciones
   
   Para ello usaremos distintos ciclos anidados
   
   Entradas: distintas opciones que se le ofrecer�n al usuario y n�meros 
             reales.
   Salidas: distintas opciones dependiendo de lo que haya escogido el usuario
   
*/

#include <iostream>  //Inclusi�n de los recursos de entrada y salida
#include <string>    //Inclsui�n de los recursos string

using namespace std;

int main()
{
    //Declaraci�n de variables
    
    const string SALIR = "X";
    const string ADICION = "A";
    const string PRODUCTO = "P";
    
    const string SUMA = "S";
    const string RESTA = "R";
    
    const string MULTIPLICAR = "M";
    const string DIVIDIR = "D";
    
    int num_menu = 1;
    double num1;
    double num2;
    double resultado_operacion;
    string opcion_seleccionada;
    
    do
    {
        while (num_menu == 1)
        {
            
            cout << "Menu 1" << endl;
            cout << "Elija una de las siguientes opciones:" << endl;
            cout << "\t A: Calcular adici�n" << endl;
            cout << "\t P: Calcular producto" << endl;
            cout << "\t X: Salir" << endl;
            cin >> opcion_seleccionada;
            
            if (opcion_seleccionada == ADICION)
            {
                num_menu = 2;
            }
            else if (opcion_seleccionada == PRODUCTO)
            {
                num_menu = 3;
            }
            else if (opcion_seleccionada == SALIR)
            {
                num_menu = 0;
            }

        }
        
        while (num_menu == 2)
        {
            cout << "Menu 2" << endl;
            cout << "Elija una de las siguientes opciones:" << endl;
            cout << "\t S: Calcular suma" << endl;
            cout << "\t R: Calcular resta" << endl;
            cout << "\t X: Salir" << endl;
            cin >> opcion_seleccionada;
            cout << endl;
            
            if (opcion_seleccionada == SUMA)
            {
                cout << "Introduzca el primer t�rmino a sumar: ";
                cin >> num1;
                cout << "Introduzca el segundo t�rmino a sumar: ";
                cin >> num2;
                
                resultado_operacion = num1 + num2;
                
                cout << "El resultado de la suma es: " << resultado_operacion;
                cout << endl;
                cout << endl;
            }
            else if (opcion_seleccionada == RESTA)
            {
                cout << "Introduzca el primer t�rmino de la resta: ";
                cin >> num1;
                cout << "Introduzca el segundo t�rmino de la resta: ";
                cin >> num2;
                
                resultado_operacion = num1 - num2;
                
                cout << "El resultado de la resta es: " << resultado_operacion;
                cout << endl;
                cout << endl;
            }
            else if (opcion_seleccionada == SALIR)
            {
                num_menu = 1;
                cout << endl;
            }
        }
        
        while (num_menu == 3)
        {
            cout << "Menu 2" << endl;
            cout << "Elija una de las siguientes opciones:" << endl;
            cout << "\t M: Calcular multiplicaci�n" << endl;
            cout << "\t D: Calcular divisi�n" << endl;
            cout << "\t X: Salir" << endl;
            cin >> opcion_seleccionada;
            cout << endl;
            
            if (opcion_seleccionada == MULTIPLICAR)
            {
                cout << "Introduzca el primer t�rmino del producto: ";
                cin >> num1;
                cout << "Introduzca el segundo t�rmino del producto: ";
                cin >> num2;
                
                resultado_operacion = num1 * num2;
                
                cout << "El resultado del producto es: " << resultado_operacion;
                cout << endl;
                cout << endl;
            }
            else if (opcion_seleccionada == DIVIDIR)
            {
                cout << "Introduzca el dividendo: ";
                cin >> num1;
                
                do
                {
                    cout << "Introduzca el divisor: ";
                    cin >> num2;
                } while (num2 == 0);
                
                resultado_operacion = num1 / num2;
                
                cout << "El resultado de la divisi�n es: ";
                cout << resultado_operacion;
                cout << endl;
                cout << endl;
            }
            else if (opcion_seleccionada == SALIR)
            {
                num_menu = 1;
                cout << endl;
            }
        }
            
            
            
    } while (num_menu != 0);
    
    return (0);
    
}
