/**
 * @file Intervalo.h
 * @author jgl
 * @date 5 de marzo de 2020
 */

#ifndef INTERVALO_H
#define INTERVALO_H

/**
 * @class Intervalo
 * @brief Para representar un intervalo en la recta real
 */

class Intervalo{
private:
    bool cerradoInf;  //< indica si toma el valor limite inferior
    bool cerradoSup;  //< indica si toma el valor limite superior
    double cotaInf;   //< indica la cota inferior
    double cotaSup;   //< indica la cota superior
    
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
    bool validar(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);
    
public:
    /** 
     *  @brief Crea un intervalo vacio 
     */
    Intervalo();
    /** 
     * @brief Devuelve la cota inferior del intervalo
     * @return El valor de la cota
     */
    /** 
     * @brief Crea un Intervalo cerrado 
     * @param cotaInferior
     * @param cotaSuperior
     * @pre El intervalo es válido
     */
    Intervalo(double cotaInferior, double cotaSuperior);
    /** 
     * @brief Crea un intervalo cualquiera 
     * @param cotaInferior
     * @param cotaSuperior
     * @param cerradoInferior
     * @param cerradoSuperior
     * @pre El intervalo es válido
     */
    Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);
    /** 
     * @brief Devuelve la cota inferior del intervalo
     * @return El valor de la cota
     */
    double getCotaInf()const ;
    /** 
     * @brief Devuelve la cota superior del intervalo
     * @return El valor de la cota
     */
    double getCotaSup()const ;
    /** 
     * @brief Modifica el valor de cotaSup
     * @param el valor nuevo
     */
    void setCotaSup(double n);
    /** 
     * @brief Modifica el valor de cotaInf
     * @param el valor nuevo
     */
    void setCotaInf(double n);
    /** 
     * @brief Modifica el valor de cerradoInf
     * @param el valor nuevo
     */
    void setCerradoInf(bool i);
    /** 
     * @brief Modifica el valor de cerradoSup
     * @param el valor nuevo
     */
    void setCerradoSup(bool i);
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota inferior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool esCerradoInf()const ;
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota superior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool esCerradoSup()const ;
    /** 
     * @brief Consulta si el intervalo almacenado es vacío o no
     * @return @retval true si es un intervalo vacío, @retval false en otro caso 
     */
    bool esVacio()const ;
    /** 
     * @brief Consulta si un determinado valor está dentro del intervalo
     * @param n El valor consultado
     * @return @retval true si el valor @p n pertenece al intervalo, @retval false en otro caso 
     */
    bool estaDentro(double n)const ;


};
    
/** 
* @brief Imprime los valores de un intervalo de forma visual según lo indicado en el guión
* @param i El intervalo
*/
void escribir(const Intervalo &i);

/** 
* @brief Lee los valores del intervalo según el formato indicado en el guión
* @param i El intervalo
*/
void leer(Intervalo &i);

#endif /* INTERVALO_H */