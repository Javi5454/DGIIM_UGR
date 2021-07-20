/* 
 * File:   Producto.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 13 de junio de 2020, 13:06
 */

#include <iostream>
#include "Producto.h"

using namespace std;

Producto::Producto() {
    idProducto = 0;
    precioBase = 0;
    IVA = 0.0;
    codBarras = "";
}

std::ostream& operator<<(std::ostream& flujo, const Producto& producto) {
    flujo << producto.getIdProducto() << " " << producto.getPrecioBase() <<
            " " << producto.getIVA() << " " << producto.getCodBarras();
    return flujo;
}

std::istream& operator>>(std::istream& flujo, Producto& producto) {
    flujo >> producto.idProducto;
    flujo >> producto.precioBase;
    flujo >> producto.IVA;
    flujo >> producto.codBarras;
    
    return flujo;
}


