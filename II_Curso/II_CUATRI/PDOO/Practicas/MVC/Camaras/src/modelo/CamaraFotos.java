package modelo;

/**
 * Class to represent a photo camera
 *
 * @author javi5454
 */
public class CamaraFotos extends Camara{
    //Atributos
    private String formatoSensor;
    
    //Constructor
    public CamaraFotos(String marca, int resolucion, String formatoSensor){
        super(marca,resolucion);
        this.formatoSensor = formatoSensor;
    }
    
    //Copy camera
    @Override
    public CamaraFotos copy(){
        return new CamaraFotos(this.getMarca(), this.getResolucion(), this.formatoSensor);
    }
    
    @Override
    public String getType(){
        return "Fotos";
    }
    
    //Functionality
    @Override
    public void setResolucion(int res){
        if(res <= 1024){
            super.setResolucion(res);
        }
    }
    
    @Override
    public void calibrar(){
        System.out.println("Calibrando CamaraFotos");
    }
    
    public void cambiarObjetivo(){
        System.out.println("Objetivo cambiado");
    }    
}
