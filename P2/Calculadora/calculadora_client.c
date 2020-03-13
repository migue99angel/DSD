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
	//Nos aseguramos que se llama correctamente al programa
	if (argc != 5) {
		printf ("Uso: %s [servidor] [argumento] [operador] [argumento]\n", argv[0]);
		exit (1);
	}

	host = argv[1];		  //Almaceno el nombre del servidor
	arg1 = atof(argv[2]); // La función atof transforma el argumento en double
	operador = *argv[3];  // El operador es un char por lo que no es necesario utilizar atof
	arg2 = atof(argv[4]); // La función atof transforma el argumento en double
	resultado = calculadora_1 (host,arg1,operador,arg2);	//Realizo el calculo
	printf("%f %c %f = %f\n",arg1,operador,arg2,*resultado); //Muestro por pantalla el resultado

exit (0);
}
