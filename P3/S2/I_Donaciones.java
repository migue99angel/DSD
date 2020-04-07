import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import javafx.util.Pair;

public interface I_Donaciones extends Remote
{
    void registrar(String usuario) throws RemoteException;
    void donar(String usuario,double cantidad) throws RemoteException;
    double getTotal(String usuario) throws RemoteException; 
    ArrayList<String> getUsuarios() throws RemoteException;
    ArrayList<Pair<String, Double>> getRegistro() throws RemoteException;
    void addUsuario(String usuario) throws RemoteException;
    double getTotalLocal() throws RemoteException;
    void incrementar(double cantidad) throws RemoteException;
    void addToRegistro(Pair<String, Double> donacion) throws RemoteException;
    void asignarReferencia(I_Donaciones ref)throws RemoteException;
}