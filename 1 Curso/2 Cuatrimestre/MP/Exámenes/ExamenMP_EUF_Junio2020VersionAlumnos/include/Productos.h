/* 
 * File:   Productos.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 13 de junio de 2020, 13:10
 */

#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <string>
#include <iostream>

#include "Producto.h"

class Productos {
public:
    /**
     * Constructor por defecto
     */
    Productos();

    /**
     * Constructor de copia
     * @param orig el objeto original a ser copiado
     */
    Productos(const Productos& orig);

    /**
     * Destructor
     */
    ~Productos();

    /**
     * Devuelve el número de productos que hay almacenados en este objeto
     * @return el número de productos que hay almacenados en este objeto
     */
    int getNumProductos() const {
        return numProductos;
    }

    /** 
     * Operador de asignación
     * @param orig objeto original Productos usado para hacer la asignación
     * @return una referencia al objeto actual
     */
    Productos& operator=(const Productos& orig);

    /**
     * Operador compuesto de asignación y suma que permite añadir una copia
     * del producto proporcionado al final del array dinámico de productos de
     * este objeto
     * @param producto el producto que será añadido 
     * @return una referencia al objeto actual
     */
    Productos& operator+=(const Producto& producto);

    /**
     * Lee un fichero que contiene la cadena FICHEROPRODUCTOS y la información
     * sobre productos, colocándolos en el objeto actual, cuya información es 
     * eliminada previamente
     * @param nombre el nombre del fichero de entrada a leer
     */
    void leerProductos(const std::string &nombre);

    /**
     * Guarda la cadena FICHEROPRODUCTOS y el array de productos de este objeto 
     * en el fichero cuyo nombre se proporciona como parámetro
     * @param nombre el nombre del fichero donde se guarda la información
     */
    void escribirProductos(const std::string &nombre) const;

    friend std::ostream& operator<<(std::ostream& flujo, const Productos& productos);
    friend std::istream& operator>>(std::istream& flujo, Productos& productos);
private:
    int numProductos;
    Producto *losProductos;

    void liberarMemoria();
    void copiar(const Productos& orig);
    void reservarMemoria(int n);
};

/**
 * Operador de salida para objetos de la clase Productos
 * @param flujo el flujo de salida donde enviar los datos del objeto Productos
 * @param productos el objeto Productos
 * @return el flujo de salida usado
 */
std::istream& operator>>(std::istream& flujo, Productos& productos);

/**
 * Operador de entrada para objetos de la clase Productos.
 * @param flujo el flujo de entrada donde enviar los datos del objeto Productos
 * @param cliente el objeto Productos
 * @return el flujo de entrada usado
 */
std::ostream& operator<<(std::ostream& flujo, const Productos& productos);

#endif /* PRODUCTOS_H */

