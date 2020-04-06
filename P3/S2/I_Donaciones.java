import java.rmi.Remote;
import java.rmi.RemoteException;

public interface I_Donaciones extends Remote
{
    void registrar(String usuario) throws RemoteException;
    void donar(String usuario,double cantidad) throws RemoteException;
    double getTotal(String usuario) throws RemoteException; 
}