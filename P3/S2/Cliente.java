
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author migue
 */
public class Cliente {
    public static void main(String args[]) {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        
        if(args.length < 2)
        {
            System.out.println("Llamada inválida al programa, uso correcto java Cliente <IP> <0 | 1 | 2 | 3>");
            System.exit(0);
        }
                
        try {
                if(Integer.parseInt(args[1]) == 0)
                {
                    String nombre_objeto_remoto = "Original";
                    System.out.println("Buscando el objeto servidor...");
                    Registry registry = LocateRegistry.getRegistry(args[0]);
                    I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                    System.out.println("Invocando el objeto servidor");

                    System.out.println("Primer usuario");
                    instancia_local.registrar("Miguel");
                    instancia_local.donar("Miguel",3000.0);
                    System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Miguel")+" euros");

                    System.out.println("Segundo usuario");
                    instancia_local.registrar("Juan");
                    instancia_local.donar("Juan",200.0);
                    System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Juan")+" euros");

                    System.out.println("Tercer usuario");
                    instancia_local.registrar("Jesus");
                    instancia_local.donar("Jesus",1000.0);
                    System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Jesus")+" euros");
                }
                
                if(Integer.parseInt(args[1]) == 1)
                {
                    String nombre_objeto_remoto = "Replica";
                    System.out.println("Buscando el objeto servidor...");
                    Registry registry = LocateRegistry.getRegistry(args[0]);
                    I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                    System.out.println("Invocando el objeto servidor");

                    System.out.println("Primer usuario");
                    instancia_local.registrar("Antonio");
                    instancia_local.donar("Antonio",3000.0);
                    System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Antonio")+" euros");

                    System.out.println("Segundo usuario");
                    instancia_local.registrar("Luisa");
                    instancia_local.donar("Luisa",200.0);
                    System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Luisa")+" euros");

                    System.out.println("Tercer usuario");
                    instancia_local.registrar("Maria");
                    instancia_local.donar("Maria",1000.0);
                    System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Maria")+" euros");
                }
                if(Integer.parseInt(args[1]) == 2)
                {
                    String nombre_objeto_remoto = "Original";
                    System.out.println("Buscando el objeto servidor...");
                    Registry registry = LocateRegistry.getRegistry(args[0]);
                    I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                    System.out.println("Invocando el objeto servidor");
                    System.out.println("Comprobando los usuarios que se han registrado en el servidor original");
                    System.out.println(instancia_local.getUsuarios());
                }
                if(Integer.parseInt(args[1]) == 3)
                {
                    String nombre_objeto_remoto = "Replica";
                    System.out.println("Buscando el objeto servidor...");
                    Registry registry = LocateRegistry.getRegistry(args[0]);
                    I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                    System.out.println("Invocando el objeto servidor");
                    System.out.println("Comprobando los usuarios que se han registrado en el servidor replicado");
                    System.out.println(instancia_local.getUsuarios());
                }
                if(Integer.parseInt(args[1]) == 6)
                {
                    String nombre_objeto_remoto = "Original";
                    System.out.println("Buscando el objeto servidor...");
                    Registry registry = LocateRegistry.getRegistry(args[0]);
                    I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                    System.out.println("Invocando el objeto servidor");
                    System.out.println("Comprobando el registro de donaciones del servidor original");
                    for(int i = 0; i < instancia_local.getRegistro().size(); i++)
                    {
                        System.out.println(instancia_local.getRegistro().get(i).getUser());
                        System.out.println(instancia_local.getRegistro().get(i).getAporte());
                    }
                    System.out.println("Comprobando los usuarios del servidor original");
                    System.out.println(instancia_local.getUsuarios().size());
                    System.out.println("Comprobando el total del servidor original");
                    System.out.println(instancia_local.getTotalLocal());
                    System.out.println("Comprobando el tamaño del vector replicas del servidor original");

                }
                if(Integer.parseInt(args[1]) == 7)
                {
                    String nombre_objeto_remoto = "Replica";
                    System.out.println("Buscando el objeto servidor...");
                    Registry registry = LocateRegistry.getRegistry(args[0]);
                    I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                    System.out.println("Invocando el objeto servidor");
                    System.out.println("Comprobando el registro de donaciones del servidor replicado");
                    
                    for(int i = 0; i < instancia_local.getRegistro().size(); i++)
                    {
                        System.out.println(instancia_local.getRegistro().get(i).getUser());
                        System.out.println(instancia_local.getRegistro().get(i).getAporte());
                    }
                    System.out.println("Comprobando los usuarios del servidor replicado");
                    System.out.println(instancia_local.getUsuarios().size());
                    System.out.println("Comprobando el total del servidor replicado");
                    System.out.println(instancia_local.getTotalLocal());
                    System.out.println("Comprobando el tamaño del vector replicas del servidor replicado");

                    System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Miguel")+" euros");
                }
                if(Integer.parseInt(args[1]) == 8)
                {
                    String nombre_objeto_remoto = "Replica2";
                    System.out.println("Buscando el objeto servidor...");
                    Registry registry = LocateRegistry.getRegistry(args[0]);
                    I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                    System.out.println("Invocando el objeto servidor");
                    System.out.println("Comprobando el registro de donaciones del servidor replicado2");
                    
                    for(int i = 0; i < instancia_local.getRegistro().size(); i++)
                    {
                        System.out.println(instancia_local.getRegistro().get(i).getUser());
                        System.out.println(instancia_local.getRegistro().get(i).getAporte());
                    }
                    System.out.println("Comprobando los usuarios del servidor replicado2");
                    System.out.println(instancia_local.getUsuarios().size());
                    System.out.println("Comprobando el total del servidor replicado2");
                    System.out.println(instancia_local.getTotalLocal());
                    System.out.println("Comprobando el tamaño del vector replicas del servidor replicado2");


                }
                
                if(Integer.parseInt(args[1]) == 9)
                {
                    String nombre_objeto_remoto = "Replica2";
                    System.out.println("Buscando el objeto servidor...");
                    Registry registry = LocateRegistry.getRegistry(args[0]);
                    I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                    System.out.println("Invocando el objeto servidor");
                    ArrayList<Aportacion> aux = instancia_local.getRegistroTotal();
                    for(int i= 0; i < aux.size(); i++)
                        System.out.println("Usuario: "+aux.get(i).getUser() +" Cantidad donada: "+aux.get(i).getAporte());
                }
                

        } catch (Exception e) {
                System.err.println("Error al invocar el servidor");
                e.printStackTrace();
            }
    }
}
