/* 
 * File:   Producto.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 13 de junio de 2020, 13:06
 */

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto {
public:
    /**
     * Constructor por defecto
     */
    Producto();
    
    /**
     * Devuelve el IVA de este producto
     * @return el IVA de este producto
     */
    double getIVA() const {
        return IVA;
    }

    /**
     * Devuelve el código de barras de este producto
     * @return el código de barras de este producto
     */
    std::string getCodBarras() const {
        return codBarras;
    }

    /**
     * Devuelve el identificador de este producto
     * @return el identificador de este producto
     */
    int getIdProducto() const {
        return idProducto;
    }

    /**
     * Devuelve el precio base de este producto
     * @return el precio base de este producto
     */
    double getPrecioBase() const {
        return precioBase;
    }
    
    friend std::istream& operator>>(std::istream& flujo, Producto& producto);

private:
    int idProducto;
    double precioBase;
    double IVA;
    std::string codBarras;      
};

/**
 * Operador de salida para Producto
 * @param flujo el flujo de salida donde enviar los datos de Producto
 * @param producto el objeto Producto
 * @return el flujo de salida usado
 */
std::ostream& operator<<(std::ostream& flujo, const Producto& producto);

/**
 * Operador de entrada para Producto.
 * @param flujo el flujo de entrada donde enviar los datos de Producto
 * @param producto el objeto Producto
 * @return el flujo de entrada usado
 */
std::istream& operator>>(std::istream& flujo, Producto& producto);

#endif /* PRODUCTO_H */

