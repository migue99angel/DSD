service Calculadora {
    void ping () ,
    i32 suma (1: i32 num1 , 2: i32 num2 ) ,
    i32 resta (1: i32 num1 , 2: i32 num2 ) ,
    double multiplicacion (1: double num1,2: double num2),
    double division (1: double num1,2: double num2),
    i32 factorial(1: i32 n),
    double potencia(1: double base, 2: double exponente),
    list<double> sumavectores(1: list<double> arr1, 2:list<double> arr2), 
    list<double> productoescalar(1: list<double> arr, 2: double escalar),
    list<double> productovectorial(1: list<double> arr1, 2:list<double> arr2),
    list<list<double>> sumamatrices(1: list<list<double>> m1 ,2: list<list<double>> m2),
    list<list<double>> productoescalarmatrices(1: list<list<double>> m1 ,2:  double escalar),
}