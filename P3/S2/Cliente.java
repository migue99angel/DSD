
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

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
        try {
                String nombre_objeto_remoto = "Original";
                System.out.println("Buscando el objeto servidor...");
                Registry registry = LocateRegistry.getRegistry("localhost");
                I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                System.out.println("Invocando el objeto servidor");
                
                /*System.out.println("Primer usuario");
                instancia_local.registrar("Otro");
                instancia_local.donar("Otro",3000.0);
                System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Julian")+" euros");
                
                System.out.println("Segundo usuario");
                instancia_local.registrar("Otro2");
                instancia_local.donar("Otro2",200.0);
                System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Julian")+" euros");
                
                System.out.println("Tercer usuario");
                instancia_local.registrar("Otro3");
                instancia_local.donar("Otro3",1000.0);
                System.out.println("El total donado por los usuarios es "+instancia_local.getTotal("Julian")+" euros");*/
                
                System.out.println(instancia_local.getUsuarios());
                
        } catch (Exception e) {
                System.err.println("Error al invocar el servidor");
                e.printStackTrace();
            }
    }
}
