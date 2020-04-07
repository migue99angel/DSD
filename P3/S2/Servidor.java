import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.net.MalformedURLException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import javafx.util.Pair;

public class Servidor implements I_Donaciones
{
    private ArrayList<String> usuarios;
    //El total global será la suma del total local de las dos réplicas
    private double totalLocal;
    //Esta es una referencia a la otra replica del servidor
    //private Servidor replica;
    private I_Donaciones replica;
    //Aquí mantenemos el registro de las donaciones realizadas
    private ArrayList<Pair<String, Double>> Registro;

    public Servidor()
    {
        super();
        totalLocal = 0;
        usuarios = new ArrayList<String>();
        Registro = new ArrayList<Pair<String, Double>>();
    }
    
    @Override
    public void registrar(String usuario) throws RemoteException
    {
        if(!this.usuarios.contains(usuario))
        {
            if(! this.replica.getUsuarios().contains(usuario))
            {
                if(this.usuarios.size() <= this.replica.getUsuarios().size())
                {
                    this.usuarios.add(usuario);
                }
                else
                   this.replica.addUsuario(usuario); 
            }
            else
                System.out.println("El usuario "+usuario+" ya se encuentra registrado en otro servidor");
        }else
        {
            System.out.println("El usuario "+usuario+" ya se encuentra registrado en este servidor");
        }

    }

    @Override
    public void donar(String usuario,double cantidad) throws RemoteException
    {
        Pair<String, Double> aux = new Pair<>(usuario,cantidad);
        if(cantidad > 0)
        {
            if(this.usuarios.contains(usuario))
            {
                this.Registro.add(aux);
                totalLocal += cantidad;
            }else
            {
                 if(this.replica.getUsuarios().contains(usuario))
                 {
                     this.replica.addToRegistro(aux);
                     this.replica.incrementar(cantidad);
                 }else
                     System.out.println("El usuario introducido no se encuentra registrado en ninguna replica del servidor");
            }
        }else
        {
            System.out.println("Se ha intentado donar una cantidad no válida");
        }
    }

    @Override
    public double getTotal(String usuario) throws RemoteException
    {
        boolean valido = false;
        for(int i = 0; i < this.Registro.size() && !valido; i++)
        {
            if(Registro.get(i).getKey().equals(usuario))
                valido = true;
        }
        
        for(int i = 0; i <  this.replica.getRegistro().size() && !valido; i++)
        {
            if( this.replica.getRegistro().get(i).getKey().equals(usuario))
                valido = true;
        }
        
        if(valido)    
            return this.totalLocal +  this.replica.getTotalLocal();
        else{
            System.out.println("Es necesario realizar una donación para poder consultar el total aportado");
            return 0.0;
        }
    }
    
    public void enlazar(String ubicacion, String nombre)
    {
        try {
        Registry registry = LocateRegistry.getRegistry(ubicacion);
        I_Donaciones aux = (I_Donaciones) registry.lookup(nombre);
        this.replica =  aux;
        this.replica.asignarReferencia(this);
        System.out.println("Servidores enlazados correctamente");
        } catch (Exception e){
            System.err.println("Error al enlazar los servidores");
            e.printStackTrace();
        }
    }
    
    public void asignarReferencia(I_Donaciones ref) throws RemoteException
    {
        this.replica = ref;
    }

    
    public ArrayList<String> getUsuarios() throws RemoteException
    {
        return this.usuarios;
    }
    
    public ArrayList<Pair<String, Double>> getRegistro() throws RemoteException
    {
        return this.Registro;
    }
    
    public void addUsuario(String usuario) throws RemoteException
    {
        this.usuarios.add(usuario);
    }
    
    public double getTotalLocal()
    {
        return this.totalLocal;
    }
    
    public void incrementar(double cantidad) throws RemoteException
    {
        this.totalLocal += cantidad;
    }
    
    public void addToRegistro(Pair<String, Double> donacion) throws RemoteException
    {
        this.Registro.add(donacion);
    }
    
    public static void main(String[] args) {
        if(args.length < 2)
        {
            System.out.println("Llamada inválida al programa, uso correcto java Servidor <IP> <0 si es el primer servidor | 1 si ya existe hay servidor corriendo>");
            System.exit(0);
        }
        
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        
        try {
             String nombre_objeto_remoto;
            if(Integer.parseInt(args[1]) == 0)
            {
              nombre_objeto_remoto = "Original";
            }
            else
            {
              nombre_objeto_remoto = "Replica";
            }
            
            I_Donaciones servidor= new Servidor();
            I_Donaciones  stub =
            (I_Donaciones ) UnicastRemoteObject.exportObject(servidor, 0);
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind(nombre_objeto_remoto, stub);
            
            if(Integer.parseInt(args[1]) == 1)
            {
                ((Servidor) servidor).enlazar(args[0],"Original");
            }
            
        System.out.println("Ejemplo bound");
        } catch (Exception e) {
            System.err.println("Ejemplo exception:");
            e.printStackTrace();
        }
        

    }
}