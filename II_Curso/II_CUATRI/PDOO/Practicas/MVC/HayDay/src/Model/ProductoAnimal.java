package Model;

/**
 * Class to represent an animal product
 *
 * @author javi5454
 */
public abstract class ProductoAnimal extends Producto {
    private int calidad;
    private TipoProductoAnimal tipo;
    
    //Constructor
    public ProductoAnimal(String icono, int dP, int eP, int pV, int calidad, TipoProductoAnimal tipo){
        super(icono, dP, eP,pV);
        this.calidad = calidad;
        this.tipo = tipo;
    }
    
    //Getters and setters 

    public int getCalidad() {
        return calidad;
    }

    public TipoProductoAnimal getTipo() {
        return tipo;
    }

    public void setCalidad(int calidad) {
        this.calidad = calidad;
    }

    public void setTipo(TipoProductoAnimal tipo) {
        this.tipo = tipo;
    }
    
}
