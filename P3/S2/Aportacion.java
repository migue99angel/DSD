
import java.io.Serializable;

/*
*
* Clase Aportación, con tiene un usuario y la cantidad donada
* la finalidad es la de mantener un registro de los usuarios que realizan aportaciones
*
*/
public class Aportacion implements Serializable{
    public String usuario;
    public double aporte;
    
    Aportacion(String user, double cant)
    {
        this.usuario = user;
        this.aporte = cant;
    }
    
    public String getUser()
    {
        return this.usuario;
    }
    
    public void setUser(String user)
    {
        this.usuario = user;
    }
    
    public double getAporte()
    {
        return this.aporte;
    }
    
    public void setAporte(double apor)
    {
        this.aporte = apor;
    }
}
