package modelo;

/**
 *  Class to represent a video camera
 * 
 * @author javi5454
 */
public class CamaraVideo extends Camara{
    //Attributes
    private int maximoMinutos;
    
    //Constructor
    public CamaraVideo(String marca, int resolucion, int maximoMinutos){
        super(marca, resolucion);
        this.maximoMinutos = maximoMinutos;
    }
    
    @Override
    public String getType(){
        return "Video";
    }
    
    //Copy method
    @Override
    public CamaraVideo copy(){
        return new CamaraVideo(this.getMarca(), this.getResolucion(), this.maximoMinutos);
    }
    
    //Functionality
    @Override
    public void calibrar(){
        System.out.println("Calibrando CamaraVideo...");
    }
}
