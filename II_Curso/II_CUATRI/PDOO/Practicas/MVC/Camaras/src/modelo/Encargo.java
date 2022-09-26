package modelo;

import java.util.ArrayList;

/**
 * Class to represent a work
 *
 * @author javi5454
 */
public class Encargo {
    //Attributes
    private String cliente;
    private ArrayList<Camara> realizadoCon;
    
    //Constructor
    public Encargo(String cliente, ArrayList<Camara> realizadoCon){
        this.cliente = cliente;
        this.realizadoCon = new ArrayList<>(realizadoCon);
    }
    
    //Copy constructor
    public Encargo(Encargo e){
        this.cliente = e.cliente;
        this.realizadoCon = new ArrayList<>();
        
        for(Camara c : e.realizadoCon){
            this.realizadoCon.add(c.copy());
        }
    }
    
    //Getters and setters
    public String getCliente(){
        return cliente;
    }
    
    public ArrayList<Camara> getRealizacoCon(){
        return realizadoCon;
    }
    
    public int getNumCameras(){
        return realizadoCon.size();
    }
    
    //Functionality
    public void addCamara(Camara c){
        if(c != null){
            realizadoCon.add(c);
        }
    }
    
    public void calibrar(){
        for(Camara c : realizadoCon){
            c.calibrar();
        }
    }
    
}
