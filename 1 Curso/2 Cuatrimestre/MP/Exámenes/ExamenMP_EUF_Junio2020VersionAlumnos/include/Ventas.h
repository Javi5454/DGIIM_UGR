/* 
 * File:   Ventas.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 11 de junio de 2020, 20:58
 */

#ifndef VENTAS_H
#define VENTAS_H

#include <iostream>
#include <string>

#include "Venta.h"

class Ventas {
public:
    /**
     * Constructor por defecto
     */
    Ventas();

    /**
     * Constructor de copia
     * @param orig el objeto original a ser copiado
     */
    Ventas(const Ventas& orig);


    /**
     * Constructor que rellena el contenido del objeto a partir del fichero
     * en formato Ventas cuyo nombre se proporciona
     * @param nombre nombre del fichero a leer
     */
    Ventas(const std::string &nombre);

    /**
     * Destructor
     */
    ~Ventas();

    /**
     * Devuelve el número de ventas que hay almacenados en este objeto
     * @return el número de ventas que hay almacenados en este objeto
     */
    int getNumVentas() const {
        return numVentas;
    }

    /**
     * Operador de asignación
     * @param orig objeto original Clientes usado para hacer la asignación
     * @return una referencia al objeto actual
     */
    Ventas &operator=(const Ventas& orig);

    /**
     * Operador compuesto de asignación y suma que permite añadir una copia
     * del objeto Venta proporcionado al final del array dinámico de ventas de
     * este objeto
     * @param venta la venta será añadida 
     * @return una referencia al objeto actual
     */
    Ventas& operator+=(const Venta& venta);

    /**
     * Calcula y devuelve la venta media entre todos los objetos Venta 
     * almacenados en este objeto
     * 
     * @return la venta media entre todos los objetos Venta almacenados en este 
     * objeto
     */
    double ventaMedia() const;

    /**
     * Guarda la cadena FICHEROVENTAS y el array de ventas de este objeto 
     * en el fichero cuyo nombre se proporciona como parámetro
     * @param nombre el nombre del fichero donde se guarda la información
     */
    void escribirVentas(const std::string &nombre) const;

    /**
     * Lee un fichero que contiene la cadena FICHEROVENTAS y la información
     * sobre ventas, colocándolos en el objeto actual, cuya información es 
     * eliminada previamente
     * @param nombre el nombre del fichero de entrada a leer
     */
    void leerVentas(const std::string &nombre);

    friend std::istream& operator>>(std::istream& flujo, Ventas& ventas);
    friend std::ostream& operator<<(std::ostream& flujo, const Ventas& ventas);


private:
    int numVentas;
    Venta *lasVentas;
    void liberarMemoria();
    void copiar(const Ventas& orig);
    void reservarMemoria(int n);
};

/**
 * Operador relacional > para comparar dos objetos Venta en base a su venta media
 * @param ventas1 un objeto Venta
 * @param ventas2 un objeto Venta
 * @return true si ventas1 es mayor a ventas2. false en otro caso
 */
bool operator>(const Ventas &ventas1, const Ventas &ventas2);

/**
 * Operador relacional == para comparar dos objetos Venta en base a su venta media
 * @param ventas1 un objeto Venta
 * @param ventas2 un objeto Venta
 * @return true si ventas1 es igual a ventas2. false en otro caso
 */
bool operator==(const Ventas &ventas1, const Ventas &ventas2);

/**
 * Operador de salida para objetos de la clase Ventas
 * @param flujo el flujo de salida donde enviar los datos del objeto Ventas
 * @param ventas el objeto Ventas
 * @return el flujo de salida usado
 */
std::ostream& operator<<(std::ostream& flujo, const Ventas& ventas);

/**
 * Operador de entrada para objetos de la clase Ventas.
 * @param flujo el flujo de entrada donde enviar los datos del objeto Ventas
 * @param cliente el objeto Ventas
 * @return el flujo de entrada usado
 */
std::istream& operator>>(std::istream& flujo, Ventas& ventas);

#endif /* VENTAS_H */

