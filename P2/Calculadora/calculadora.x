/*Archivo calculadora.x*/
/*rpcgen -NCa calculadora.x*/

typedef float t_vector<>;
program CALCULADORA{
    
    version CALCULADORA_VER{
        float SUMA(float a,float b) = 1;
        float RESTA(float a,float b) = 2;
        float MULTIPLICACION(float a,float b) = 3;
        float DIVISION(float a,float b) = 4;
        t_vector SUMAVECTORES(t_vector v_1,t_vector v_2) = 5;
        t_vector PRODUCTOESCALARVECTORES(t_vector v, float escalar) = 6;
        t_vector PRODUCTOVECTORIAL(t_vector v_1, t_vector v_2) = 7;
        float MEDIAARITMETICA(t_vector v) = 8;
        t_vector FIBONACCI(int n) = 9;
        int FACTORIAL(int n) = 10;
        float LOGARITMOBASE_N(float numero, float base) = 11;
        float POTENCIA(float base, float exponente) = 12;
    } = 1;
} = 0x20000001;

