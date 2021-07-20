/* 
 * File:   Venta.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 11 de junio de 2020, 20:57
 */

#include <sstream>
#include <string>

#include "Venta.h"

using namespace std;

Venta::Venta() {
    idCliente = 0;
    idProducto = 0;
    unidades = 0;
    total = 0;
}

Venta::Venta(const std::string &linea) {
    istringstream flujodeString;
    if (linea.size() > 0) {
        flujodeString.str(linea);
        flujodeString >> idCliente;
        flujodeString >> idProducto;
        flujodeString >> unidades;       
        flujodeString >> total;
    } else {
        idCliente = 0;
        idProducto = 0;
        total = 0;
    }
}

std::ostream& operator<<(std::ostream& flujo, const Venta& venta) {
    flujo << venta.idCliente << " " << venta.idProducto << 
            " " << venta.unidades << " " << venta.total;
    return flujo;
}

std::istream& operator>>(std::istream& flujo, Venta& venta){ 
    flujo >> venta.idCliente;
    flujo >> venta.idProducto;
    flujo >> venta.unidades;
    flujo >> venta.total;
    return flujo;
}