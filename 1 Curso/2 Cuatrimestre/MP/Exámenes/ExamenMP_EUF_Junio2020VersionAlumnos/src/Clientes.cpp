/* 
 * File:   Clientes.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 11 de junio de 2020, 19:20
 */

#include "Clientes.h"
#include "Cliente.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Clientes::Clientes() {
    losClientes = nullptr;
    numClientes = 0;
}

Clientes::Clientes(const Clientes& orig) {
    copiar(orig);
}

Clientes::Clientes(const string &nombre) {
    ifstream flujo;
    string cadena;

    losClientes = nullptr;
    numClientes = 0;
    flujo.open(nombre);
    if (flujo) {
        getline(flujo, cadena);
        if (cadena == "FICHEROCLIENTES") {
            flujo >> *this;
        }
        flujo.close();
    }
}

Clientes::~Clientes() {
    liberarMemoria();
}

Clientes& Clientes::operator=(const Clientes& orig) {
    if (this != &orig) {
        liberarMemoria();
        reservarMemoria(orig.numClientes);
        copiar(orig);
    }
    return *this;
}

void Clientes::liberarMemoria() {
    delete[] losClientes;
    numClientes = 0;
}

void Clientes::copiar(const Clientes& orig) {
    reservarMemoria(orig.numClientes);
    for (int i = 0; i < numClientes; i++) {
        losClientes[i] = orig.losClientes[i];
    }
}

void Clientes::reservarMemoria(int n) {
    losClientes = new Cliente[n];
    numClientes = n;
}

int Clientes::posicionCliente(std::string nif) const {
    for (int i = 0; i < numClientes; i++) {
        if (losClientes[i].getNIF() == nif) {
            return i;
        }
    }
    return -1;
}

Clientes& Clientes::operator+=(const Cliente& cliente) {
    if (posicionCliente(cliente.getNIF()) < 0) {
        Cliente *arrayAuxiliar = new Cliente[numClientes + 1];
        for (int i = 0; i < numClientes; i++) {
            arrayAuxiliar[i] = losClientes[i];
        }
        arrayAuxiliar[numClientes] = cliente;
        delete[] losClientes;
        losClientes = arrayAuxiliar;
        numClientes++;
    }
    return *this;
}

Clientes operator+(const Clientes &clientes1, const Clientes &clientes2) {
    Clientes clientes = clientes1;

    for (int i = 0; i < clientes2.getNumeroClientes(); i++) {
        if (clientes1.posicionCliente(clientes2[i].getNIF()) < 0) { // Si clientes2[i] no está en clientes1
            clientes += clientes2[i];
        }
    }
    return clientes;
}

Cliente& Clientes::operator[](int n) {
    return losClientes[n];

}

const Cliente& Clientes::operator[](int n) const {
    return losClientes[n];
}

std::ostream& operator<<(std::ostream& flujo, const Clientes& clientes) {
    for (int i = 0; i < clientes.getNumeroClientes(); i++) {
        flujo << clientes.losClientes[i].toString() << endl;
    }
    return flujo;
}

std::istream& operator>>(std::istream& flujo, Clientes& clientes) {
    Cliente cliente;
    clientes.liberarMemoria();
    while (flujo >> cliente) {
        clientes += cliente;
    }

    return flujo;
}

void Clientes::leerClientes(const std::string &nombre) {
    Clientes clientes(nombre);
    *this = clientes;
}

void Clientes::escribirClientes(const string &nombre) const {
    ofstream flujo;
    flujo.open(nombre);
    if (flujo) {
        flujo << "FICHEROCLIENTES" << endl;
        flujo << *this;
        flujo.close();
    }
}

