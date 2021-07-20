/* 
 * File:   Cliente.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 11 de junio de 2020, 19:17
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente {
public:
    /**
     * Constructor por defecto
     */
    Cliente();

    /**
     * Devuelve el identificador de cliente
     * @return el identificador de cliente
     */
    int getIdCliente() const;

    /**
     * Devuelve el descuento que se aplica a este cliente
     * @return el descuento que se aplica a este cliente
     */
    double getDescuento() const;

    /**
     * Devuelve el nombre del cliente
     * @return el nombre del cliente
     */
    std::string getNombre() const;

    /**
     * Devuelve el NIF del cliente
     * @return el NIF del cliente
     */
    std::string getNIF() const;

    /**
     * Devuelve una cadena (string) con los datos de este cliente, separados
     * por espacios en blanco
     * @return una cadena (string) con los datos de este cliente, separados
     * por espacios en blanco
     */
    std::string toString() const;
    friend std::istream& operator>>(std::istream& flujo, Cliente& cliente);

private:
    int idCliente;
    double descuento;
    std::string nombre;
    std::string NIF;
};

/**
 * Operador de salida para Cliente
 * @param flujo el flujo de salida donde enviar los datos de Cliente
 * @param cliente el objeto Cliente
 * @return el flujo de salida usado
 */
std::ostream& operator<<(std::ostream& flujo, const Cliente& cliente);

/**
 * Operador de entrada para Cliente.
 * @param flujo el flujo de entrada donde enviar los datos de Cliente
 * @param cliente el objeto Cliente
 * @return el flujo de entrada usado
 */
std::istream& operator>>(std::istream& flujo, Cliente& cliente);


#endif /* CLIENTE_H */

