/*Archivo calculadora.x*/
/*rpcgen -NCa calculadora.x*/

typedef float t_vector<>;
program CALCULADORA{
    
    version CALCULADORA_VER{
        float SUMA(float a,float b) = 1;
        float RESTA(float a,float b) = 2;
        float MULTIPLICACION(float a,float b) = 3;
        float DIVISION(float a,float b) = 4;
        t_vector SUMAVECTORES(t_vector v_1,t_vector v_2,int n) = 5;
        t_vector PRODUCTOESCALARVECTORES(t_vector v, float escalar, int n) = 6;
        t_vector PRODUCTOVECTORIAL(t_vector v_1, t_vector v_2,int n) = 7;
    } = 1;
} = 0x20000001;

