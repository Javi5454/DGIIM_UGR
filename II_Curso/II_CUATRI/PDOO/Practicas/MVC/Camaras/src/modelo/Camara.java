package modelo;

/**
 * Class to represent a camera
 *
 * @author javi5454
 */
public abstract class Camara {
    //Attributes
    private String marca;
    private int resolucion;
    
    //Constructor
    public Camara(String marca, int resolucion){
        this.marca = marca;
        this.resolucion = resolucion;  //TODO: Maybe Max resolution is 1024?
    }
    
    //Deep copy necesary methods
    public abstract Camara copy();
    
    public abstract String getType();
    
    public String getMarca(){
        return marca;
    }
    
    public int getResolucion(){
        return resolucion;
    }
    
    //Getter and setters
    public void setResolucion(int res){
        resolucion = res;
    }
    
    //Functionality
    public abstract void calibrar();
}
