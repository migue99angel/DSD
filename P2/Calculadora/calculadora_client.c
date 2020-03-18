//Autor: Miguel Ángel Posadas Arráez 
//Comando para compilar : cc calculadora_client.c calculadora_clnt.c calculadora_xdr.c -o cliente -lnsl

#include "calculadora.h"


double* calculadora_1(char *host, double argv1, char operador, double argv2)
{
	CLIENT *clnt;
	double * res;	//Variable que usare para almacenar el resultado

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "tcp");	//Se muestra un error si hay algún error al establecer conexión con el servidor
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	switch(operador)	//Dependiendo del operador que haya introducido el usuario se llamará a una función u otra
	{
		case '+':
			res = suma_1(argv1,argv2,clnt);
		break;
		case '-':
			res = resta_1(argv1,argv2,clnt);
		break;
		case 'x':
			res = multiplicacion_1(argv1,argv2,clnt);
		break;
		case '/':
			res = division_1(argv1,argv2,clnt);
		break;
		default:
			printf("El operando introducido no es válido\n");
			exit(1);
		break;
	}
	return res;

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int main (int argc, char *argv[])
{
	char *host; //Puntero a char que almacena el nombre del servidor
	char operador; // Almaceno en un char el operador
	double arg1, arg2; //Argumentos de las operaciones 
	double* resultado; //Puntero a double donde se almacenarán las operaciones
	int opcion = 0,vectores = 0, op_aux = 0;
	char* entrada;
	host = argv[1];		  //Almaceno el nombre del servidor
	while( 1 == 1)
	{
		switch(opcion)
		{
			case 0:
				printf("¿Qué quieres hacer?\n");
				printf("1 - Operaciones básicas (+ - x /)\n");
				printf("2 - Operaciones con vectores\n");
				printf("3 - Operaciones con matrices\n");
				printf("4 - Acabar ejecución\n");
				int x;
				scanf("%i",&x);
				opcion = (int)x;
			break;
			case 1:
				
				printf("Introduce el operador (+,-,x,/) \n");
				scanf("%s",&operador);
				printf("Introduce el primer argumento de la operación básica a realizar\n");
				scanf("%le",&arg1);
				printf("Introduce el segundo argumento de la operación básica a realizar\n");
				scanf("%le",&arg2);

				resultado = calculadora_1 (host,arg1,operador,arg2);	//Realizo el calculo
				printf("%f %c %f = %f\n",arg1,operador,arg2,*resultado); //Muestro por pantalla el resultado
				opcion = 0;
			break;
			case 2:
				vectores = 1;
				while(vectores == 1)
				{
					switch(op_aux)
					{
						case 0:
							printf("¿Qué operación quieres hacer con vectores?\n");
							printf("1 - Suma de vectores\n");
							printf("2 - Producto de un escalar por un vector\n");
							printf("3 - Producto vectorial\n");
							printf("4 - Volver al menu\n");
							int y;
							scanf("%i",&y);
							op_aux = (int)y;
						break;

						case 1:
							printf("HOLA\n");
							op_aux = 0;
						break;

						case 2:
							printf("HOLA\n");
							op_aux = 0;
						break;

						case 3:
							printf("HOLA\n");
							op_aux = 0;
						break;

						case 4:
							vectores = 0;
							opcion = 0;
						break;
					}
				}
			break;

			case 3:
				vectores = 2;
				while(vectores == 2)
				{
					switch(op_aux)
					{
						case 0:
							printf("¿Qué operación quieres hacer con matrices?\n");
							printf("1 - Suma de matrices\n");
							printf("2 - Producto de un escalar por una matriz\n");
							printf("3 - Matriz traspuesta\n");
							printf("4 - Volver al menu\n");
							int z;
							scanf("%i",&z);
							op_aux = (int)z;
						break;

						case 1:
							printf("HOLA\n");
							op_aux = 0;
						break;
						
						case 2:
							printf("HOLA\n");
							op_aux = 0;
						break;
						
						case 3:
							printf("HOLA\n");
							op_aux = 0;
						break;

						case 4:
							vectores = 0;
							opcion = 0;
						break;
					}
				}
			break;

			case 4:
				exit(0);
			break;
		}
	}

}
