import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.net.MalformedURLException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;


public class Servidor implements I_Donaciones
{
    private ArrayList<String> usuarios;
    //El total global será la suma del total local de las dos réplicas
    private double totalLocal;
    //Esta es una referencia a la otra replica del servidor
    private I_Donaciones replicaAUsar;
    //Un vector con todas las réplicas
    private ArrayList<I_Donaciones>  replicas;
    //Aquí mantenemos el registro de las donaciones realizadas
    private ArrayList<Aportacion> Registro;


    public Servidor()
    {
        super();
        totalLocal = 0;
        usuarios = new ArrayList<String>();
        Registro = new ArrayList<Aportacion>();
        replicas = new ArrayList<I_Donaciones>();
    }
    
    @Override
    public void registrar(String usuario) throws RemoteException
    {
        obtenerReplica(0,usuario);
        if(this.replicaAUsar != null)
            this.replicaAUsar.addUsuario(usuario);
    }

    @Override
    public void donar(String usuario,double cantidad) throws RemoteException
    {
        
        if(cantidad > 0)
        {
            Aportacion aux = new Aportacion(usuario,cantidad);
            obtenerReplica(1,usuario);
            if(this.replicaAUsar != null)
            {
                this.replicaAUsar.addToRegistro(aux);
                this.replicaAUsar.incrementar(cantidad);
            }
        }else
        {
            System.out.println("Se ha intentado donar una cantidad no válida");
        }
    }

    @Override
    public double getTotal(String usuario) throws RemoteException
    {
        obtenerReplica(2,usuario);
        if(this.replicaAUsar != null)
        {
            double total = this.totalLocal;
            for(int i = 0; i < this.replicas.size(); i++  )
            {
                total += this.replicas.get(i).getTotalLocal();
            }
            
            return total;
        }
        else{
            System.out.println("Es necesario realizar una donación para poder consultar el total aportado");
            return 0.0;
        }
    }
    
    public void enlazar(String ubicacion, String nombre, int nReplicas)
    {
        try {
            if(nReplicas == 2)
            {
                Registry registry = LocateRegistry.getRegistry(ubicacion);
                I_Donaciones aux = (I_Donaciones) registry.lookup(nombre);
                this.replicas.add(aux);
                this.replicas.get(0).asignarReferencia(this);
                System.out.println("2 Servidores enlazados correctamente");
            }
            if(nReplicas == 3)
            {
                Registry registry = LocateRegistry.getRegistry(ubicacion);
                I_Donaciones aux = (I_Donaciones) registry.lookup(nombre);
                this.replicas.add(aux);
                
                for(int i = 0; i < aux.obtenerReplicas().size(); i++)
                {
                    this.replicas.add(aux.obtenerReplicas().get(i));
                }
                
                for(int i = 0; i < this.replicas.size(); i++ )
                {
                    this.replicas.get(i).asignarReferencia(this);
                }
                
                System.out.println("3 Servidores enlazados correctamente");
            }
        } catch (Exception e){
            System.err.println("Error al enlazar los servidores");
            e.printStackTrace();
        }
    }
    public ArrayList<I_Donaciones> obtenerReplicas()throws RemoteException
    {
        return this.replicas;
    }
    
    public void asignarReferencia(I_Donaciones ref) throws RemoteException
    {
        this.replicas.add(ref);
    }

    
    public ArrayList<String> getUsuarios() throws RemoteException
    {
        return this.usuarios;
    }
    
    public ArrayList<Aportacion> getRegistro() throws RemoteException
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
    
    public void addToRegistro(Aportacion donacion) throws RemoteException
    {
        this.Registro.add(donacion);
    }
    public void asignarReplicaAUsar(I_Donaciones ref)throws RemoteException
    {
        this.replicaAUsar = ref;
    }
    /*
    * Función que actualiza el valor de la variable replicaAUsar dependiendo de la operación que se vaya a realizar
    * En caso de que el usuario pueda realizar la operación deseada se pondrá la variable replicaAUsar con el valor de la réplica encargada de realizar la operación
    * En caso de que el usuario no pueda realizar la operación se pondrá el valor de la variable replicaAUsar a null
    * int opcion puede ser : 0 - Registrar un usuario | 1 - Donar | 2 - Consultar el total
    * String usuario - El usuario que va a realizar la operación
    * En caso de registro se pondrá la referencia replicaAUsar a null cuando el usuario ya este registrado
    * En caso de Donar se pondrá a null cuando el usuario no esté registrado
    * En caso de Consultar se pondrá a null cuando el usuario no haya realizado ninguna aportación
    */
    private void obtenerReplica(int opcion, String usuario )throws RemoteException
    {
        Boolean encontrado = false;
            if(this.replicas.size() > 0)
            {
                switch(opcion)
                {

                    //Registrar
                    case 0:
                        this.replicaAUsar = null;

                        for(int i = 0; i < this.replicas.size() && !encontrado; i++  )
                        {
                            if(this.replicas.get(i).getUsuarios().contains(usuario))
                            {
                                this.replicaAUsar = this.replicas.get(i);
                                encontrado = true;
                            }
                        }

                        if(encontrado)
                        {
                            System.err.println("Error al registrar, el usuario ya se encuentra registrado en alguna réplica");
                            this.replicaAUsar = null;
                        }

                        if(!encontrado)
                        {
                            if(!this.usuarios.contains(usuario))
                            {
                                this.replicaAUsar = this;
                                for(int i = 0; i < this.replicas.size(); i++  )
                                {
                                    if(this.replicaAUsar.getUsuarios().size() >= this.replicas.get(i).getUsuarios().size() )
                                    {
                                        this.replicaAUsar = this.replicas.get(i);
                                    }

                                }

                                for(int i = 0; i < this.replicas.size(); i++  )
                                {
                                    this.replicas.get(i).asignarReplicaAUsar(this.replicaAUsar);
                                }
                            }else
                            {
                                System.err.println("Error al registrar, el usuario ya se encuentra registrado en alguna réplica");
                                this.replicaAUsar = null;
                            }

                        }
                    break;
                    //Donar
                    case 1:
                        encontrado = this.usuarios.contains(usuario);
                        for(int i = 0; i < this.replicas.size() && !encontrado; i++  )
                        {
                            if(this.replicas.get(i).getUsuarios().contains(usuario))
                            {
                                this.replicaAUsar = this.replicas.get(i);
                                encontrado = true;
                            }
                        }
                        if(!encontrado)
                        {
                            System.err.println("Error usuario no registrado");
                            this.replicaAUsar = null;
                        }else
                        {
                            for(int i = 0; i < this.replicas.size(); i++  )
                            {
                                this.replicas.get(i).asignarReplicaAUsar(this.replicaAUsar);
                            }
                        }
                    break;
                    //Consultar
                    case 2:
                        boolean valido = false;

                        for(int j = 0; j < this.getRegistro().size() && !valido; j++)
                        {
                            if( this.getRegistro().get(j).getUser().equals(usuario))
                            {
                                valido = true;
                                this.replicaAUsar = this;
                            }   

                        }

                        for(int i = 0; i < this.replicas.size() && !valido; i++)
                        {
                            for(int j = 0; j < this.replicas.get(i).getRegistro().size() && !valido; j++)
                            {
                                if( this.replicas.get(i).getRegistro().get(j).getUser().equals(usuario))
                                {
                                    valido = true;
                                    this.replicaAUsar = this.replicas.get(i);
                                }   

                            }
                        }
                        if(!valido)
                            this.replicaAUsar = null;

                    break;

                }
            }else
            {
                switch(opcion)
                {
                    case 0:
                        this.replicaAUsar = this;
                    break;
                        
                    case 1:
                        if(this.usuarios.contains(usuario))
                            this.replicaAUsar = this;
                        else
                            System.err.println("Error usuario no registrado");
                    break;
                    
                    case 2:
                        boolean valido = false;
                        this.replicaAUsar = null;
                        for(int j = 0; j < this.getRegistro().size() && !valido; j++)
                        {
                            if( this.getRegistro().get(j).getUser().equals(usuario))
                            {
                                valido = true;
                                this.replicaAUsar = this;
                            }   

                        }
                        
                    break;
                }
            }

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
            String nombre_objeto_remoto = "";
            if(Integer.parseInt(args[1]) == 0)
            {
              nombre_objeto_remoto = "Original";
            }
            if(Integer.parseInt(args[1]) == 1)
            {
              nombre_objeto_remoto = "Replica";
            }
            if(Integer.parseInt(args[1]) == 2)
            {
              nombre_objeto_remoto = "Replica2";
            }
            
            I_Donaciones servidor= new Servidor();
            I_Donaciones  stub =
            (I_Donaciones ) UnicastRemoteObject.exportObject(servidor, 0);
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind(nombre_objeto_remoto, stub);
            
            if(Integer.parseInt(args[1]) == 1)
            {
                ((Servidor) servidor).enlazar(args[0],"Original",2);
            }
            
            if(Integer.parseInt(args[1]) == 2)
            {
                ((Servidor) servidor).enlazar(args[0],"Replica",3);
            }
            
        System.out.println("Ejemplo bound");
        } catch (Exception e) {
            System.err.println("Ejemplo exception:");
            e.printStackTrace();
        }
        

    }
}