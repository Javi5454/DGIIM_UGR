/* 
 * File:   Productos.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 13 de junio de 2020, 13:10
 */

#include <fstream>
#include <iostream>

#include "Productos.h"

using namespace std;

Productos::Productos() {
    losProductos = nullptr;
    numProductos = 0;
}

Productos::Productos(const Productos& orig) {
    copiar(orig);
}

Productos::~Productos() {
    liberarMemoria();
}

Productos& Productos::operator=(const Productos& orig) {
    if (this != &orig) {
        liberarMemoria();
        reservarMemoria(orig.numProductos);
        copiar(orig);
    }
    return *this;
}

void Productos::liberarMemoria() {
    delete[] losProductos;
    numProductos = 0;
}

void Productos::copiar(const Productos& orig) {
    reservarMemoria(orig.numProductos);
    for (int i = 0; i < numProductos; i++) {
        losProductos[i] = orig.losProductos[i];
    }
}

void Productos::reservarMemoria(int n) {
    losProductos = new Producto[n];
    numProductos = n;
}

Productos& Productos::operator+=(const Producto& producto) {
    Producto *arrayAuxiliar = new Producto[this->numProductos + 1];
    for (int i = 0; i < numProductos; i++) {
        arrayAuxiliar[i] = losProductos[i];
    }
    arrayAuxiliar[numProductos] = producto;
    delete[] losProductos;
    losProductos = arrayAuxiliar;
    numProductos++;

    return *this;
}

void Productos::leerProductos(const std::string &nombre) {
    ifstream flujo;

    flujo.open(nombre);
    if (flujo) {
        string cadena;
        getline(flujo, cadena);
        if (cadena == "FICHEROPRODUCTOS") {
            flujo >> *this;
        }
        flujo.close();
    }
}

void Productos::escribirProductos(const string &nombre) const {
    ofstream flujo;
    flujo.open(nombre);
    if (flujo) {
        flujo << "FICHEROPRODUCTOS" << endl;
        flujo << *this;
        flujo.close();
    }
}


std::istream& operator>>(std::istream& flujo, Productos& productos) {
    Producto producto;
    productos.liberarMemoria();
    while (flujo>>producto) {
        productos += producto;
    }

    return flujo;
}

std::ostream& operator<<(std::ostream& flujo, const Productos& productos) {
    for (int i = 0; i < productos.getNumProductos(); i++) {
        flujo << productos.losProductos[i] << endl;
    }
    return flujo;
}