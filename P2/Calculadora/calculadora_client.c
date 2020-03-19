//Autor: Miguel Ángel Posadas Arráez grupo DSD1
//Para compilar este archivo: 
#include "calculadora.h"
//Esta calculadora la utilizo para el apartado de operaciones básicas que no necesitan estructuras de datos complejas
float* calculadora_1(char *host, float argv1, char operador, float argv2)
{
	CLIENT *clnt;
	float * res;


#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "tcp");
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
		case '^':
			res = potencia_1(argv1,argv2,clnt);
		break;
		case 'l':
			res = logaritmobase_n_1(argv1,argv2,clnt);
		break;
		default:
			printf("El operando introducido no es válido\n");
		break;
	}
	return res;

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}
//Esta calculadora la utilizo para operaciones que necesitan dos vectores
t_vector* calculadora_2(char *host, t_vector v_1, t_vector v_2,int operacion)
{
	CLIENT *clnt;
	t_vector * res;


#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
	#endif	/* DEBUG */

switch(operacion)
{
	case 1:
		res = sumavectores_1(v_1,v_2,clnt);
	break;
	case 2:
		res = productovectorial_1(v_1,v_2,clnt);
	break;
}
	return res;

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}
//Esta calculadora la uso unicamente para el productoescalar
t_vector* calculadora_3(char *host, t_vector v_1, float escalar)
{
	CLIENT *clnt;
	t_vector * res;


#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
	#endif	/* DEBUG */

	res = productoescalarvectores_1(v_1,escalar,clnt);

	return res;

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}
//Esta calculadora solo la utilizo para el factorial
int* calculadora_4(char *host, float n)
{
	CLIENT *clnt;
	int * res;


#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "tcp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

	res = factorial_1(n,clnt);

	return res;

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}

float* calculadora_5(char *host, t_vector v)
{
	CLIENT *clnt;
	float * res;


#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
	#endif	/* DEBUG */

	res = mediaaritmetica_1(v,clnt);

	return res;

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}

t_vector* calculadora_6(char *host,int n)
{
	CLIENT *clnt;
	t_vector * res;


#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
	#endif	/* DEBUG */

	res = fibonacci_1(n,clnt);

	return res;

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}

int main (int argc, char *argv[])
{
	char *host; //Puntero a char que almacena el nombre del servidor
	char operador; // Almaceno en un char el operador
	float arg1, arg2; //Argumentos de las operaciones 
	float* resultado; //Puntero a double donde se almacenarán las operaciones
	int opcion = 0,vectores = 0, op_aux = 0, n;
	char* entrada;
	float ej1 = 17, ej2 = 24.5;
	int fac_ej = 5;
	host = argv[1];		  //Almaceno el nombre del servidor
	if (argc != 2)
	{
		printf("Error en la llamada al programa\n");
		exit(0);
	}
	while( 1 == 1)
	{
		switch(opcion)
		{
			case 0:
				printf("¿Qué quieres hacer?\n");
				printf("1 - Operaciones básicas (+ - x / ^ l(para el logaritmo) f (Para factorial) )\n");
				printf("2 - Operaciones con vectores\n");
				printf("3 - Calcular la sucesión de Fibonacci hasta un n\n");
				printf("4 - Calcular la media aritmética de n números\n");
				printf("5 - Batería de ejemplos probando todas las funciones \n");
				printf("6 - Acabar ejecución\n");
				int x;
				scanf("%i",&x);
				opcion = (int)x;
			break;
			case 1:
				
				printf("Introduce el operador (+,-,x,/ ^ l(para el logaritmo) f (Para factorial) \n");
				scanf("%s",&operador);
				if(operador == '+' || operador == '-' || operador == 'x' || operador == '/')
				{
					printf("Introduce el primer argumento de la operación básica a realizar\n");
					scanf("%f",&arg1);
					printf("Introduce el segundo argumento de la operación básica a realizar\n");
					scanf("%f",&arg2);
				}
				else
				{
					if(operador == '^')
					{
						printf("Introduce la base\n");
						scanf("%f",&arg1);
						printf("Introduce elexponente\n");
						scanf("%f",&arg2);
					}
					else
					{
						if(operador == 'l')
						{
							printf("Introduce el argumento\n");
							scanf("%f",&arg1);
							printf("Introduce la base\n");
							scanf("%f",&arg2);
						}
						else
						{
							if(operador == 'f')
							printf("Introduce el numero del que quieres calcular su factorial\n");
							scanf("%f",&arg1);
						}
						
					}
					
				}
				
				if(operador != 'f')
				{
					resultado = calculadora_1 (host,arg1,operador,arg2);	//Realizo el calculo
					printf("%f %c %f = %f\n",arg1,operador,arg2,*resultado); //Muestro por pantalla el resultado
				}
				if(operador == 'f')
				{
					int* re = calculadora_4(host,arg1);
					printf("!%f = %d \n",arg1,*re);
				}


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
							
							printf("Introduce el tamaño de los vectores, ambos deben tener la misma longitud y ser superior a 0\n");
							int w;
							do{
								scanf("%d",&w);
							}while(w <= 0);
							printf("Rellena el primer vector\n");
							t_vector v_1;
							v_1.t_vector_len = w;
							v_1.t_vector_val = malloc(w*sizeof(float));
							printf("Empieza a rellenar el vector\n");
							for(int i = 0; i < v_1.t_vector_len; i++)
							{
								scanf("%f",&v_1.t_vector_val[i]);
							}		
							
							printf("Rellena el segundo vector\n");
							t_vector v_2;
							v_2.t_vector_len = w;
							v_2.t_vector_val = malloc(w*sizeof(float));
							for(int i = 0; i < v_2.t_vector_len; i++)
							{
								scanf("%f",&v_2.t_vector_val[i]);
							}
							


							t_vector r;

							r.t_vector_val = malloc(w*sizeof(float));
							r.t_vector_len = w;

							r = *calculadora_2(host,v_1,v_2,1);

							printf("El vector suma es: \n");
							for(int i = 0; i < r.t_vector_len; i++)
							{
								printf("%f  ",r.t_vector_val[i]);
							}

							printf("\n");
							free(v_1.t_vector_val);
							free(v_2.t_vector_val);
							free(r.t_vector_val);
							op_aux = 0;
						break;

						case 2:
							printf("Introduce el tamaño del vector, recuerda que tiene que ser mayor que 0\n");
						
							do{
								scanf("%d",&w);
							}while(w <= 0);
							printf("Rellena el vector\n");

							v_1.t_vector_len = w;
							v_1.t_vector_val = malloc(w*sizeof(float));
							for(int i = 0; i < v_1.t_vector_len; i++)
							{
								scanf("%f",&v_1.t_vector_val[i]);
							}

							printf("Introduce el escalar\n");
							float esc;
							scanf("%e",&esc);


							r = *calculadora_3(host,v_1,esc);

							printf("El vector resultado es: \n");
							for(int i = 0; i < r.t_vector_len; i++)
							{
								printf("%f  ",r.t_vector_val[i]);
							}

							printf("\n");
							free(v_1.t_vector_val);
							free(r.t_vector_val);
							op_aux = 0;
						break;

						case 3:
							printf("El producto vectorial se hará de vectores de tamaño 3\n");
							printf("Rellena el primer vector\n");

							v_1.t_vector_len = 3;
							v_1.t_vector_val = malloc(3*sizeof(float));
							for(int i = 0; i < v_1.t_vector_len; i++)
							{
								scanf("%f",&v_1.t_vector_val[i]);
							}

							printf("Rellena el segundo vector\n");

							v_2.t_vector_len = 3;
							v_2.t_vector_val = malloc(3*sizeof(float));
							for(int i = 0; i < v_2.t_vector_len; i++)
							{
								scanf("%f",&v_2.t_vector_val[i]);
							}


							r = *calculadora_2(host,v_1,v_2,2);

							printf("El vector resultado es: \n");
							for(int i = 0; i < r.t_vector_len; i++)
							{
								printf("%f  ",r.t_vector_val[i]);
							}

							printf("\n");
							free(v_1.t_vector_val);
							free(v_2.t_vector_val);
							free(r.t_vector_val);

							op_aux = 0;
						break;

						case 4:
							vectores = 0;
							opcion = 0;
						break;
						default:
							printf("Parece que has introducido un operando no válido\n");
							op_aux = 0;
						break;
					}
				}
			break;

			case 3:
				printf("Introduce el n hasta el cual quieres calcular la sucesión de fibonacci, recuerda que tiene que ser mayor o igual que 0\n");
				do{
					scanf("%d",&arg1);
				}while(arg1 < 0);

				t_vector r_fib;

				r_fib = *calculadora_6(host,arg1);

				printf("El resultado es de tamaño %d \n",r_fib.t_vector_len);
				for(int i = 0; i < r_fib.t_vector_len; i++)
				{
					printf("%d  ",(int)r_fib.t_vector_val[i]);
				}

				printf("\n");

				free(r_fib.t_vector_val);
				opcion = 0;
			break;

			case 4:
				printf("Introduce la cantidad de números que vas a introducir, recuerda que el número tiene que ser mayor que 0\n");
				int cantidad;
				do{
					scanf("%d",&cantidad);
				}while(cantidad <= 0);
				printf("Rellena el vector\n");
				t_vector v_media;
				v_media.t_vector_len = cantidad;
				v_media.t_vector_val = malloc(cantidad*sizeof(float));
				for(int i = 0; i < v_media.t_vector_len; i++)
				{
					scanf("%e",&v_media.t_vector_val[i]);
				}
				float * media = 0;		
				media = calculadora_5(host,v_media); 
				printf("La media de los números introducidos es: %f\n",*media);
				v_media.t_vector_len = 0;
				free(v_media.t_vector_val);
				opcion = 0;
				break;

			case 5:
				printf("Numero de ejemplo 1 %f \n",ej1);
				printf("Numero de ejemplo 2 %f \n",ej2);
				operador = '+';
				resultado = calculadora_1 (host,ej1,operador,ej2);
				printf("%f %c %f = %f\n",ej1,operador,ej2,*resultado);
				resultado = calculadora_1 (host,ej1,'-',ej2);
				printf("%f %c %f = %f\n",ej1,'-',ej2,*resultado);
				resultado = calculadora_1 (host,ej1,'x',ej2);
				printf("%f %c %f = %f\n",ej1,'x',ej2,*resultado);
				resultado = calculadora_1 (host,ej1,'/',ej2);
				printf("%f %c %f = %f\n",ej1,'/',ej2,*resultado);
				resultado = calculadora_1 (host,ej1,'l',ej2);
				printf("%f %c %f = %f\n",ej1,'l',ej2,*resultado);
				int* re_ej = calculadora_4(host,5);
				printf("!%d = %d \n",5,*re_ej);
				t_vector v_ej, v_ej2;
				v_ej.t_vector_len = 3;
				v_ej.t_vector_val = malloc(3*sizeof(float));
				v_ej.t_vector_val[0] = 15.2;
				v_ej.t_vector_val[1] = 36;
				v_ej.t_vector_val[2] = 78.21;
				v_ej2.t_vector_len = 3;
				v_ej2.t_vector_val = malloc(3*sizeof(float));
				v_ej2.t_vector_val[0] = 1.2;
				v_ej2.t_vector_val[1] = 0;
				v_ej2.t_vector_val[2] = 17;
				printf("El vector ejemplo 1 es : \n");
				for(int i = 0; i < v_ej.t_vector_len; i++)
				{
					printf("%f  ",v_ej.t_vector_val[i]);
				}
				printf("\n");
				printf("El vector ejemplo 2 es : \n");
				for(int i = 0; i < v_ej2.t_vector_len; i++)
				{
					printf("%f  ",v_ej2.t_vector_val[i]);
				}
				printf("\n");
				t_vector r;

				r.t_vector_val = malloc(3*sizeof(float));
				r.t_vector_len = 3;

				r = *calculadora_2(host,v_ej,v_ej2,1);

				printf("El vector suma es: \n");
				for(int i = 0; i < r.t_vector_len; i++)
				{
					printf("%f  ",r.t_vector_val[i]);
				}
				printf("\n");
				printf("El vector resultado de la suma multiplicado por 5 tiene de resultado el siguiente vector: \n");
				r = *calculadora_3(host,r,5);
				for(int i = 0; i < r.t_vector_len; i++)
				{
					printf("%f  ",r.t_vector_val[i]);
				}
				printf("\n");
				printf("El siguiente vector es el resultado del producto vectorial entre los dos vectores de ejemplo\n");
				r = *calculadora_2(host,v_ej,v_ej2,2);

				for(int i = 0; i < r.t_vector_len; i++)
				{
					printf("%f  ",r.t_vector_val[i]);
				}

				printf("\n");
				opcion = 0;
			break;
			case 6:
				exit(0);
			break;
			default:
				printf("Parece que has introducido una opción no válida\n");
				opcion = 0;
			break;
		}
	}
}