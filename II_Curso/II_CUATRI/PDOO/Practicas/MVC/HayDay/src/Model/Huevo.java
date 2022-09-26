package Model;

/**
 * Class to represent an egg
 *
 * @author javi5454
 */
public class Huevo extends ProductoAnimal{
    //Atributes
    public static final int PRECIO_VENTA = 2;
    public static final int EXPERIENCIA = 1;
    public static final int DURACION = 2;
    public static final int CALIDAD = 30;
    
    //Constructor
    public Huevo(){
        super("/img/huevo40.png", DURACION, EXPERIENCIA, PRECIO_VENTA, CALIDAD, TipoProductoAnimal.HUEVO);
    }
    
    //Getter and setters
    
    //Functionaltiy
    @Override
    public void enProduccion(){
        System.out.println("Produciendo huevo...");
    }
}
