/* 
 * File:   Clientes.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 11 de junio de 2020, 19:20
 */

#ifndef CLIENTES_H
#define CLIENTES_H

#include "Cliente.h"

class Clientes {
public:
    /**
     * Constructor por defecto
     */
    Clientes();

    /**
     * Constructor de copia
     * @param orig el objeto original a ser copiado
     */
    Clientes(const Clientes& orig);

    /**
     * Constructor que rellena el contenido del objeto a partir del fichero
     * en formato Clientes cuyo nombre se proporciona
     * @param nombre nombre del fichero a leer
     */
    Clientes(const std::string &nombre);

    /**
     * Destructor
     */
    ~Clientes();

    /**
     * Devuelve el número de clientes en la colección
     * @return el número de clientes en la colección
     */
    int getNumeroClientes() const {
        return numClientes;
    };

    /**
     * Operador de asignación
     * @param orig objeto original Clientes usado para hacer la asignación
     * @return una referencia al objeto actual
     */
    Clientes &operator=(const Clientes& orig);

    /**
     * Versión de devolución por referencia del operador de acceso a un elemento 
     * de la colección de clientes
     * @param n el número de elemento al que se quiere acceder
     * @return el elemento que hay en la posición n (comienza desde la posición 0)
     */
    Cliente& operator[](int n);

    /**
     * Versión de devolución por referencia constante del operador de acceso 
     * a un elemento de la colección de clientes
     * @param n el número de elemento al que se quiere acceder
     * @return el elemento que hay en la posición n (comienza desde la posición 0)
     */
    const Cliente& operator[](int n) const;


    Clientes& operator+=(const Cliente& cliente);

    /**
     * Devuelve la posición en el array de clientes donde se encuentra el
     * cliente cuyo NIF es el proporcionado como parámetro
     * @param nif El NIF a buscar en el array de clientes
     * @return la posición en el array de clientes donde se encuentra el
     * cliente cuyo NIF es el proporcionado como parámetro (-1) si no se encuentra
     */
    int posicionCliente(std::string nif) const;

    /**
     * Lee un fichero que contiene la cadena FICHEROCLIENTES y la información
     * sobre clientes, colocándolos en el objeto actual, cuya información es 
     * eliminada previamente
     * @param nombre el nombre del fichero de entrada a leer
     */
    void leerClientes(const std::string &nombre);

    /**
     * Guarda la cadena FICHEROCLIENTES y el array de clientes de este objeto 
     * en el fichero cuyo nombre se proporciona como parámetro
     * @param nombre el nombre del fichero donde se guarda la información
     */
    void escribirClientes(const std::string &nombre) const;


    friend std::ostream& operator<<(std::ostream& flujo, const Clientes& clientes);
    friend std::istream& operator>>(std::istream& flujo, Clientes& clientes);
private:
    int numClientes;
    Cliente *losClientes;

    void liberarMemoria();
    void copiar(const Clientes& orig);
    void reservarMemoria(int n);
};

/**
 * Operador de concatenación para dos objetos Clientes que devuelve un nuevo
 * objeto Clientes con los clientes de las dos colecciones, que no están repetidos
 * (respecto al NIF)
 * @param clientes1 objeto Clientes con la primera colección de objetos Cliente
 * @param clientes2 objeto Clientes con la segunda colección de objetos Cliente
 * @return un nuevo objeto Clientes con los clientes no repetidos de las dos
 * colecciones de entrada.
 */
Clientes operator+(const Clientes &clientes1, const Clientes &clientes2);

/**
 * Operador de salida para objetos de la clase Clientes
 * @param flujo el flujo de salida donde enviar los datos del objeto Clientes
 * @param cliente el objeto Clientes
 * @return el flujo de salida usado
 */
std::ostream& operator<<(std::ostream& flujo, const Clientes& clientes);


/**
 * Operador de entrada para objetos de la clase Clientes.
 * @param flujo el flujo de entrada donde enviar los datos del objeto Clientes
 * @param cliente el objeto Clientes
 * @return el flujo de entrada usado
 */
std::istream& operator>>(std::istream& flujo, Clientes& clientes);

#endif /* CLIENTES_H */

