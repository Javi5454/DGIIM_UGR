/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Model;

/**
 * Clas to represent milk
 *
 * @author javi5454
 */
public class Leche extends ProductoAnimal{
    public static final int PRECIO_VENTA = 3;
    public static final int EXPERIENCIA = 2;
    public static final int DURACION = 5;
    public static final int CALIDAD = 10;
    
    //Constructor
    public Leche(){
        super("/img/leche40.png", DURACION, EXPERIENCIA, PRECIO_VENTA, CALIDAD, TipoProductoAnimal.LECHE);
    }
    
    //Getters and setters
    
    //Functionalty
    @Override 
    public void enProduccion(){
        System.out.println("Produciendo Leche...");
    }
    
}
