/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "calculadora.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

float *
suma_1(float a, float b,  CLIENT *clnt)
{
	suma_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.a = a;
	arg.b = b;
	if (clnt_call (clnt, SUMA, (xdrproc_t) xdr_suma_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
resta_1(float a, float b,  CLIENT *clnt)
{
	resta_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.a = a;
	arg.b = b;
	if (clnt_call (clnt, RESTA, (xdrproc_t) xdr_resta_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
multiplicacion_1(float a, float b,  CLIENT *clnt)
{
	multiplicacion_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.a = a;
	arg.b = b;
	if (clnt_call (clnt, MULTIPLICACION, (xdrproc_t) xdr_multiplicacion_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
division_1(float a, float b,  CLIENT *clnt)
{
	division_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.a = a;
	arg.b = b;
	if (clnt_call (clnt, DIVISION, (xdrproc_t) xdr_division_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

t_vector *
sumavectores_1(t_vector v_1, t_vector v_2,  CLIENT *clnt)
{
	sumavectores_1_argument arg;
	static t_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.v_1 = v_1;
	arg.v_2 = v_2;
	if (clnt_call (clnt, SUMAVECTORES, (xdrproc_t) xdr_sumavectores_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_t_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

t_vector *
productoescalarvectores_1(t_vector v, float escalar,  CLIENT *clnt)
{
	productoescalarvectores_1_argument arg;
	static t_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.v = v;
	arg.escalar = escalar;
	if (clnt_call (clnt, PRODUCTOESCALARVECTORES, (xdrproc_t) xdr_productoescalarvectores_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_t_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

t_vector *
productovectorial_1(t_vector v_1, t_vector v_2,  CLIENT *clnt)
{
	productovectorial_1_argument arg;
	static t_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.v_1 = v_1;
	arg.v_2 = v_2;
	if (clnt_call (clnt, PRODUCTOVECTORIAL, (xdrproc_t) xdr_productovectorial_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_t_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
mediaaritmetica_1(t_vector v,  CLIENT *clnt)
{
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MEDIAARITMETICA,
		(xdrproc_t) xdr_t_vector, (caddr_t) &v,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

t_vector *
fibonacci_1(int n,  CLIENT *clnt)
{
	static t_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, FIBONACCI,
		(xdrproc_t) xdr_int, (caddr_t) &n,
		(xdrproc_t) xdr_t_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
factorial_1(int n,  CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, FACTORIAL,
		(xdrproc_t) xdr_int, (caddr_t) &n,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
logaritmobase_n_1(float numero, float base,  CLIENT *clnt)
{
	logaritmobase_n_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.numero = numero;
	arg.base = base;
	if (clnt_call (clnt, LOGARITMOBASE_N, (xdrproc_t) xdr_logaritmobase_n_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
potencia_1(float base, float exponente,  CLIENT *clnt)
{
	potencia_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.base = base;
	arg.exponente = exponente;
	if (clnt_call (clnt, POTENCIA, (xdrproc_t) xdr_potencia_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
