/* 
 * File:   Ventas.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 11 de junio de 2020, 20:58
 */

#include <string>
#include <fstream>

#include "Ventas.h"

using namespace std;

Ventas::Ventas() {
    lasVentas = nullptr;
    numVentas = 0;
}

Ventas::Ventas(const string &nombre) {
    ifstream flujo;
    string cadena;

    lasVentas = nullptr;
    numVentas = 0;

    flujo.open(nombre);
    if (flujo) {
        getline(flujo, cadena);
        if (cadena == "FICHEROVENTAS") {
            flujo >> *this;
        }
        flujo.close();
    }
}

Ventas::Ventas(const Ventas& orig) {
    copiar(orig);
}

Ventas::~Ventas() {
    liberarMemoria();
}

void Ventas::liberarMemoria() {
    delete[] lasVentas;
    numVentas = 0;
}

void Ventas::copiar(const Ventas& orig) {
    reservarMemoria(orig.numVentas);
    for (int i = 0; i < numVentas; i++) {
        lasVentas[i] = orig.lasVentas[i];
    }

}

void Ventas::reservarMemoria(int n) {
    lasVentas = new Venta[n];
    numVentas = n;
}

Ventas& Ventas::operator=(const Ventas& orig) {
    if (this != &orig) {
        liberarMemoria();
        reservarMemoria(orig.numVentas);
        copiar(orig);
    }
    return *this;
}

Ventas& Ventas::operator+=(const Venta& venta) {
    Venta *arrayAuxiliar = new Venta[this->numVentas + 1];
    for (int i = 0; i < numVentas; i++) {
        arrayAuxiliar[i] = lasVentas[i];
    }
    arrayAuxiliar[numVentas] = venta;
    delete[] lasVentas;
    lasVentas = arrayAuxiliar;
    numVentas++;

    return *this;
}

double Ventas::ventaMedia() const {
    double suma = 0.0;
    for (int i = 0; i < numVentas; i++) {
        suma += this->lasVentas[i].getTotal();
    }
    return suma / numVentas;

}

bool operator>(const Ventas &ventas1, const Ventas &ventas2) {
    if (ventas1.ventaMedia() > ventas2.ventaMedia())
        return true;
    else
        return true;
}

bool operator==(const Ventas &ventas1, const Ventas &ventas2) {
    if (ventas1.ventaMedia() == ventas2.ventaMedia())
        return true;
    else
        return true;
}

std::istream& operator>>(std::istream& flujo, Ventas& ventas) {
    string linea;
    ventas.liberarMemoria();
    while (flujo) {
        getline(flujo, linea);
        if (flujo) {
            Venta venta(linea);
            ventas += venta;
        }
    }
    return flujo;
}

std::ostream& operator<<(std::ostream& flujo, const Ventas& ventas) {
    for (int i = 0; i < ventas.numVentas; i++) {
        flujo << ventas.lasVentas[i] << endl;
    }
    return flujo;
}

void Ventas::leerVentas(const std::string &nombre) {
    ifstream flujo;

    flujo.open(nombre);
    if (flujo) {
        string cadena;
        getline(flujo, cadena);
        if (cadena == "FICHEROVENTAS") {
            flujo >> *this;
        }
        flujo.close();
    }
}

void Ventas::escribirVentas(const std::string &nombre) const {
    ofstream flujo;
    flujo.open(nombre);
    if (flujo) {
        flujo << "FICHEROVENTAS" << endl;
        flujo << *this;
        flujo.close();
    }
}
