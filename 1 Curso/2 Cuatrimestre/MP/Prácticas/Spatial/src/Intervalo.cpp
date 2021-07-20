/** 
 * @file   intervalo.cpp
 * @author decsai.ugr.es
 *
 */

#include "Intervalo.h"
#include <assert.h>
#include <iostream>
#include <string>

using namespace std;


    /**
     * @brief comprueba que los argumentos definen un intervalo correcto
     * @param cotaInferior
     * @param cotaSuperior
     * @param cerradoInferior
     * @param cerradoSuperior
     * @pre cotaInferior < cotaSuperior 
     * @pre cotaInferior == cotaSuperior && cerradoInferior == cerradoSuperior 
     * @return @retval true si correcto @retval false en otro caso
     */
    bool Intervalo::validar(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior)
    {
        bool resultado;
        
        resultado = ((cotaInf < cotaSup) || ((cotaInf == cotaSup) && (cerradoInf == cerradoSup)));
        
        return resultado;
    }
    
    /** 
     *  @brief Crea un intervalo vacio 
     */
    Intervalo::Intervalo()
    {
        cerradoInf = false;
        cerradoSup = false;
        cotaInf = 0;
        cotaSup = 0;
    }
    /** 
     * @brief Crea un Intervalo cerrado 
     * @param cotaInferior
     * @param cotaSuperior
     * @pre El intervalo es válido
     */
    Intervalo::Intervalo(double cotaInferior, double cotaSuperior)
    {
        assert(validar(cotaInferior, cotaSuperior, true, true));
	cotaInf = cotaInferior;
	cotaSup = cotaSuperior;
	cerradoInf = true;
	cerradoSup = true;
    }
    /** 
     * @brief Crea un intervalo cualquiera 
     * @param cotaInferior
     * @param cotaSuperior
     * @param cerradoInferior
     * @param cerradoSuperior
     * @pre El intervalo es válido
     */
    Intervalo::Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior)
    {
        assert(validar(cotaInferior, cotaSuperior, cerradoInferior, cerradoSuperior));
        cotaInf = cotaInferior;
        cotaSup = cotaSuperior;
        cerradoInf = cerradoInferior;
        cerradoSup = cerradoSuperior;
    }
    /** 
     * @brief Devuelve la cota inferior del intervalo
     * @return El valor de la cota
     */
    double Intervalo::getCotaInf()const 
    {
        return cotaInf;
    }
    /** 
     * @brief Devuelve la cota superior del intervalo
     * @return El valor de la cota
     */
    double Intervalo::getCotaSup()const 
    {
        return cotaSup;
    }
    /** 
     * @brief Modifica el valor de cotaSup
     * @param el valor nuevo
     */
    void Intervalo::setCotaSup(double n)
    {
        cotaSup = n;
    }
    /** 
     * @brief Modifica el valor de cotaInf
     * @param el valor nuevo
     */
    void Intervalo::setCotaInf(double n)
    {
        cotaInf = n;
    }
    /** 
     * @brief Modifica el valor de cerradoInf
     * @param el valor nuevo
     */
    void Intervalo::setCerradoInf(bool i)
    {
        cerradoInf = i;
    }
    /** 
     * @brief Modifica el valor de cerradoSup
     * @param el valor nuevo
     */
    void Intervalo::setCerradoSup(bool i)
    {
        cerradoSup = i;
    }
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota inferior
     * @return @retval true si es cerrado @retval false si no es cerrado
     */
    bool Intervalo::esCerradoInf()const 
    {
        return cerradoInf;
    }
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota superior
     * @return @retval true si es cerrado @retval false si eno s cerrado
     */
    bool Intervalo::esCerradoSup()const 
    {
        return cerradoSup;
    }
    /** 
     * @brief Consulta si el intervalo almacenado es vacío o no
     * @return @retval true si es un intervalo vacío, @retval false en otro caso 
     */
    bool Intervalo::esVacio()const 
    {
        bool resultado = (cotaInf == 0) && (cotaSup == 0) && (cerradoInf == false) && (cerradoSup == false);
        
        return resultado;
    }
    /** 
     * @brief Consulta si un determinado valor está dentro del intervalo
     * @param n El valor consultado
     * @return @retval true si el valor @p n pertenece al intervalo, @retval false en otro caso 
     */
    bool Intervalo::estaDentro(double n)const
    {
        bool resultado;
        
        if (esCerradoInf())
        {
            resultado = (n >= cotaInf && n < cotaSup); 
        }
        else if (esCerradoSup())
        {
            resultado = (n > cotaInf && n <= cotaSup);
        }
        else if (esCerradoInf() && esCerradoSup())
        {
            resultado = (n >= cotaInf && n <= cotaSup);
        }
        else
        {
            resultado = (n < cotaSup && n > cotaInf);
        }
        
        return resultado;
    
};

/** 
* @brief Imprime los valores de un intervalo de forma visual según lo indicado en el guión
* @param i El intervalo
*/
void escribir(const Intervalo &i)
{
    if (i.esCerradoInf())
    {
        cout << "[";
    }
    else
    {
        cout << "(";
    }
    
    cout << i.getCotaInf() << "," << i.getCotaSup();
    
    if (i.esCerradoSup())
    {
        cout << "]";
    }
    else
    {
        cout << ")";
    }
};

/** 
* @brief Lee los valores del intervalo según el formato indicado en el guión
* @param i El intervalo
*/
void leer(Intervalo &i)
{
    string cadena;
    cin >> cadena;
    int contador = 1;
    
    if (cadena[0] == '(')
    {
        i.setCerradoInf(false);
    }
    else
    {
        i.setCerradoInf(true);
    }
    
    if (cadena[(cadena.length() - 1)] == ')')
    {
        i.setCerradoSup(false);
    }
    else
    {
        i.setCerradoSup(true);
    }
    
    string inf;
    
    for (int j = 1; cadena[j] != ','; j++)
    {
        inf += cadena[j];
        contador++;
    }
    
    i.setCotaInf(stod(inf));
    
    string sup;
    
    for (int m = contador + 1; cadena[m] != ')' && cadena[m] != ']'; m++)
    {
        sup += cadena[m];    
    }
    
    i.setCotaSup(stod(sup));
}