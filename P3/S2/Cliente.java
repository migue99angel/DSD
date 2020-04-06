
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
                String nombre_objeto_remoto = "Orginal";
                System.out.println("Buscando el objeto servidor...");
                Registry registry = LocateRegistry.getRegistry(args[0]);
                I_Donaciones instancia_local = (I_Donaciones) registry.lookup(nombre_objeto_remoto);
                System.out.println("Invocando el objeto servidor");
                instancia_local.registrar("Manolo");
                instancia_local.donar("Manolo",3000.0);
                instancia_local.getTotal("Manolo");
        } catch (Exception e) {
                System.err.println("Error al invocar el servidor");
                e.printStackTrace();
            }
    }
}
