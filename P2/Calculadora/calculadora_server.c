
//Autor: Miguel Ángel Posadas Arráez grupo DSD1
//cc calculadora_server.c calculadora_svc.c calculadora_xdr.c -o servidor -lnsl -lm

#include "calculadora.h"
#include <math.h>

float * suma_1_svc(float a, float b,  struct svc_req *rqstp)
{
	static float  result;

	result = a + b;

	return &result;
}

float * resta_1_svc(float a, float b,  struct svc_req *rqstp)
{
	static float  result;

	result = a - b;

	return &result;
}

float * multiplicacion_1_svc(float a, float b,  struct svc_req *rqstp)
{
	static float  result;

	result = a * b;

	return &result;
}

float * division_1_svc(float a, float b,  struct svc_req *rqstp)
{
	static float  result;
	//Evitamos divitir por 0
	if(b != 0)		
		result = a/b;

	return &result;
}

t_vector * sumavectores_1_svc(t_vector v_1, t_vector v_2,  struct svc_req *rqstp)
{
	static t_vector  result;
	result.t_vector_len =v_1.t_vector_len;
	result.t_vector_val = malloc(v_1.t_vector_len*sizeof(float));
	for(int i = 0; i < v_1.t_vector_len;i++)
		result.t_vector_val[i] = v_1.t_vector_val[i] + v_2.t_vector_val[i];

	return &result;
}

t_vector * productoescalarvectores_1_svc(t_vector v, float escalar, struct svc_req *rqstp)
{
	static t_vector  result;

	result.t_vector_len =v.t_vector_len;
	result.t_vector_val = malloc(v.t_vector_len*sizeof(float));

	for(int i = 0; i < v.t_vector_len;i++)
		result.t_vector_val[i] = v.t_vector_val[i] * escalar;

	return &result;
}

t_vector * productovectorial_1_svc(t_vector v_1, t_vector v_2,  struct svc_req *rqstp)
{
	static t_vector  result;

	result.t_vector_len =v_1.t_vector_len;
	result.t_vector_val = malloc(v_1.t_vector_len*sizeof(float));

	result.t_vector_val[0] = v_1.t_vector_val[1]*v_2.t_vector_val[2] - v_1.t_vector_val[2]*v_2.t_vector_val[1];
	result.t_vector_val[1] = v_1.t_vector_val[2]*v_2.t_vector_val[0] - v_1.t_vector_val[0]*v_2.t_vector_val[2];
	result.t_vector_val[2] = v_1.t_vector_val[0]*v_2.t_vector_val[1] - v_1.t_vector_val[1]*v_2.t_vector_val[0];
	

	return &result;
}
float * mediaaritmetica_1_svc(t_vector v,  struct svc_req *rqstp)
{
	static float  result = 0;
	
	result =  v.t_vector_val[0];
	if(v.t_vector_len > 1)
	{
		for(int i = 1; i < v.t_vector_len; i++)
			result += v.t_vector_val[i]; 

		result = result/v.t_vector_len;
	}
	return &result;
}

t_vector * fibonacci_1_svc(int n,  struct svc_req *rqstp)
{
	static t_vector  result;

	result.t_vector_len = n;
	result.t_vector_val = malloc(n*sizeof(int));

	int x = 0, y = 1, z = 0;
	if( n == 1 )
		result.t_vector_val[0] = x;
	if( n == 2)
	{
		result.t_vector_val[0] = x;
		result.t_vector_val[1] = y;
	}

	if( n == 3)
	{
		result.t_vector_val[0] = x;
		result.t_vector_val[1] = y;
		result.t_vector_val[2] = y;
	}

	if(n > 3)
	{
		result.t_vector_val[0] = x;
		result.t_vector_val[1] = y;
		for(int i = 1; i <= n - 2; i++)
		{
			z = x + y;
			result.t_vector_val[1 + i] = z;
			x = y;
			y = z;
		}

	}	

	return &result;
}

int * factorial_1_svc(int n,  struct svc_req *rqstp)
{
	static int  result;

	if(n < 0)
		result = 0;
	else
	{
		if(n == 0)
			result = 1;
		else
		{
			result = 1;
			for(int i = 1; i < n + 1 ; i++)
			{
				result = result * i;
			}
				
		}
			
	}
		

	return &result;
}

float * logaritmobase_n_1_svc(float numero, float base,  struct svc_req *rqstp)
{
	static float  result;

	result = log(numero)/log(base);

	return &result;
}

float * potencia_1_svc(float base, float exponente,  struct svc_req *rqstp)
{
	static float  result;

	result = pow(base,exponente);

	return &result;
}