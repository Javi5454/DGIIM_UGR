package main;

import modelo.*;
import controlador.Controller;
import vista.Vista;
import java.util.ArrayList;

/**
 * Main class of the model
 *
 * @author javi5454
 */
public class main {
    public static void main (String[] args){
        
        //Apartado A
        Camara c1 = new CamaraFotos("Canon", 512, "SLR");
        Camara c2 = new CamaraVideo("Sony", 2048, 1000);
        
        ArrayList<Camara> arrCamaras = new ArrayList<>();
        arrCamaras.add(c1);
        arrCamaras.add(c2);
        
        //Apartado B
        ((CamaraFotos) arrCamaras.get(0)).cambiarObjetivo();
        
        //Apartado C
        Encargo boda = new Encargo("Pareja", arrCamaras);
        Encargo bautizo = new Encargo(boda);
        
        //Apartado d
        bautizo.calibrar();
        
        //Apartado e
        Controller c = new Controller();
        
        Vista vista = new Vista(c);
        
        c.setModelView(bautizo, vista);
        c.start();
    }
}
