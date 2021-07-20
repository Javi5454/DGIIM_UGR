/* 
 * File:   Venta.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 11 de junio de 2020, 20:57
 */

#ifndef VENTA_H
#define VENTA_H

#include <string>

class Venta {
public:
    /**
     * Constructor por defecto
     */
    Venta();

    /**
     * Constructor que crea un objeto Venta leyendo los datos de la cadana (string=
     * proporcionada. Se supone que la cadena contiene los datos de la siguiente
     * forma: idCliente idProducto total
     * @param linea cadena de caracteres (string) que contiene los datos a 
     * partir de los que se va a construir el objeto Venta
     */
    Venta(const std::string &linea);

    /**
     * Devuelve el identificador del cliente de esta venta
     * @return el identificador del cliente de esta venta
     */
    int getIdCliente() const {
        return idCliente;
    }

    /**
     * Devuelve el identificador del producto de esta venta
     * @return el identificador del producto de esta venta
     */
    int getIdProducto() const {
        return idProducto;
    }

    /**
     * Devuelve el número de unidades vendidas del producto en esta venta
     * @return el número de unidades vendidas del producto en esta venta
     */
    int getUnidades() const {
        return unidades;
    }

    /**
     * Devuelve el total del importe de esta venta
     * @return el total del importe de esta venta
     */
    double getTotal() const {
        return total;
    }

    friend std::ostream& operator<<(std::ostream& flujo, const Venta& venta);
    friend std::istream& operator>>(std::istream& flujo, Venta& venta);

private:
    int idCliente;
    int idProducto;
    int unidades;
    double total;
};

/**
 * Operador de salida para Venta
 * @param flujo el flujo de salida donde enviar los datos de Venta
 * @param venta el objeto Venta
 * @return el flujo de salida usado
 */
std::ostream& operator<<(std::ostream& flujo, const Venta& venta);

/**
 * Operador de entrada para Venta.
 * @param flujo el flujo de entrada donde enviar los datos de Venta
 * @param cliente el objeto Venta
 * @return el flujo de entrada usado
 */
std::istream& operator>>(std::istream& flujo, Venta& venta);

#endif /* VENTA_H */

