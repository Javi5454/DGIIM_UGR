package Model;

/**
 * Class to implement a product
 *
 * @author javi5454
 */
public abstract class Producto {
    //Atributes
    private String icono;
    private int duracionProduccion;
    private int experienciaProduccion;
    private int precioVenta;
    
    //Constructors
    public Producto(String icono, int dP, int eP, int pV){
        this.icono = icono;
        this.duracionProduccion = dP;
        this.experienciaProduccion = eP;
        this.precioVenta = pV;
    }
    
    public Producto(){
        this.icono = "";
        this.duracionProduccion = 1;
        this.experienciaProduccion = 1;
        this.precioVenta = 1;
    }
    
    //Getters and setters

    public String getIcono() {
        return icono;
    }

    public int getDuracionProduccion() {
        return duracionProduccion;
    }

    public int getExperienciaProduccion() {
        return experienciaProduccion;
    }

    public int getPrecioVenta() {
        return precioVenta;
    }

    public void setIcono(String icono) {
        this.icono = icono;
    }

    public void setDuracionProduccion(int duracionProduccion) {
        this.duracionProduccion = duracionProduccion;
    }

    public void setExperienciaProduccion(int experienciaProduccion) {
        this.experienciaProduccion = experienciaProduccion;
    }

    public void setPrecioVenta(int precioVenta) {
        this.precioVenta = precioVenta;
    }
    
    
    //Functionality
    public abstract void enProduccion();
}
