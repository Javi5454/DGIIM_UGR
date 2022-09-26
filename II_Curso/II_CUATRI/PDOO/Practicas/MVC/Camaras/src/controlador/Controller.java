/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package controlador;

import modelo.Encargo;
import vista.Vista;

/**
 *
 * @author javi5454
 */
public class Controller {
    private int camaraActual;
    
    private Encargo modelo;
    private Vista vista;
    
    public Controller(){}
    
    public void setModelView(Encargo modelo, Vista vista){
        this.modelo = modelo;
        this.vista = vista;
    }
    
    public void finish(int i){
        System.exit(i);
    }
    
    public int getCamaraActual(){
        return camaraActual;
    }
    
    public Encargo getModelo(){
        return modelo;
    }
    
    public String getCliente(){
        return modelo.getCliente();
    }
    
    public void start(){
        vista.updateView();
        vista.showView();
    }
    
    public void next(){
        camaraActual++;
        if(camaraActual == this.modelo.getNumCameras()){
            finish(0);
        }
    }
}
