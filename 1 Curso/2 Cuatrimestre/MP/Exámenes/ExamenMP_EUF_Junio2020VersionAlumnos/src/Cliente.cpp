/* 
 * File:   Cliente.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 11 de junio de 2020, 19:17
 */
#include <string>
#include <iostream>
#include <sstream>

#include "Cliente.h"

using namespace std;

Cliente::Cliente() : idCliente(0), descuento(0), nombre("sinNombre"), NIF("NIFnoVálido") {
}

int Cliente::getIdCliente() const {
    return idCliente;
}

double Cliente::getDescuento() const {
    return descuento;
}

std::string Cliente::getNombre() const {
    return nombre;
}

string Cliente::getNIF() const {
    return NIF;
}

std::string Cliente::toString() const {
    string cadena = to_string(idCliente) + " " + to_string(descuento) + " " +
            nombre + " " + NIF;
    return cadena;
}

std::ostream& operator<<(std::ostream& flujo, const Cliente& cliente) {
    flujo << cliente.getIdCliente() << " " << cliente.getDescuento() <<
            " " << cliente.getNombre() << " " << cliente.getNIF() << endl;
    return flujo;
}

std::istream& operator>>(std::istream& flujo, Cliente &cliente) {
    string linea;
    string parteNombre;
    getline(flujo, linea);
    
    istringstream flujosString;
    flujosString.str(linea);

    flujosString >> cliente.idCliente;
    flujosString >> cliente.descuento;
    flujosString >> cliente.nombre;

    while (flujosString >> parteNombre) {
        if (!flujosString.eof())
            cliente.nombre = cliente.nombre + " " + parteNombre;
    }
    cliente.NIF = parteNombre;

    return flujo;
}
