//Autor: Miguel Ángel Posadas Arráez 
//Comando para compilar : cc calculadora_server.c calculadora_svc.c calculadora_xdr.c -o servidor -lnsl

#include "calculadora.h"

double * suma_1_svc(double a, double b,  struct svc_req *rqstp)
{
	static double  result;

	result = a + b;

	return &result;
}

double * resta_1_svc(double a, double b,  struct svc_req *rqstp)
{
	static double  result;

	result = a - b;

	return &result;
}

double * multiplicacion_1_svc(double a, double b,  struct svc_req *rqstp)
{
	static double  result;

	result = a * b;

	return &result;
}

double * division_1_svc(double a, double b,  struct svc_req *rqstp)
{
	static double  result;
	//Evitamos divitir por 0
	if(b != 0)		
		result = a/b;

	return &result;
}
