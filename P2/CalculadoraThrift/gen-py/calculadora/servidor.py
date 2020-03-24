import glob
import sys


from Calculadora import *

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

import logging
logging.basicConfig(level=logging.DEBUG)


class CalculadoraHandler:
    def __init__(self):
        self.log = {}
    
    def ping(self):
        print('Me han hecho ping')
    
    def suma(self, n1, n2):
        print('sumando '+str(n1)+ " con "+str(n2))
        return n1+n2
    
    def resta(self, n1, n2):
        print('restando '+str(n1)+ " con "+str(n2))
        return n1-n2
    
    def multiplicacion(self,n1,n2):
        print('Multiplicando '+str(n1)+ 'con '+str(n2))
        return n1 * n2

    def division(self,n1,n2):
        print('Dividiendo '+str(n1)+ 'con  '+str(n2))
        return n1 / n2

    def potencia(self,n1,n2):
        print(str(n1)+'^'+str(n2))
        return n1 ** n2
    
    def factorial(self,n):
        print('Calculando el factorial  de: '+str(n))
        if n < 0:
            resultado = 0
        else:
            if n == 0:
                resultado = 1
            else:
                resultado = 1
                for x in range(1,n+1):
                    resultado *= x
        
        return resultado
    # Para sumar vectores ambos deben tener el mismo tamanio
    def sumavectores(self,arr1,arr2):
        print('Sumando vectores')
        res = []
        for i in range (len(arr1)):
            res.append(arr1[i]+arr2[i])
        return res
    
    def productoescalar(self,arr,escalar):
        print('Producto escalar')
        res = []
        for i in range (len(arr)):
            res.append(arr[i]*escalar)
        return res
    # Para producto vectorial ambps vectores deben tener tamanio 3  
    def productovectorial(self,arr1,arr2):
        print('Producto vectorial')
        res = []

        res.append(arr1[1]*arr2[2] - arr1[2]*arr2[1])
        res.append(arr1[2]*arr2[0] - arr1[0]*arr2[2]) 
        res.append(arr1[0]*arr2[1] - arr1[1]*arr2[0])

        return res
    # Para suma matrices ambas matrices deben tener el mismo tamanio    
    def sumamatrices(self,m1,m2):
        mResultado = []
        #Declaramos en la matriz resultado tantas filas como tengan las matrices de entrada
        for i in range(len(m1)):
            mResultado.append([])
        
        for a in range(len(m1)):
            for b in range(len(m2)):
                mResultado[a].append(m1[a][b] + m2[a][b])
    
        return mResultado

    def productoescalarmatrices(self,m1,escalar):
        mResultado = []
        #Declaramos en la matriz resultado tantas filas como tengan las matrices de entrada
        for i in range(len(m1)):
            mResultado.append([])
        
        for a in range(len(m1)):
            for b in range(len(m1)):
                mResultado[a].append(m1[a][b]*escalar)
    
        return mResultado

if __name__ == '__main__':
    handler = CalculadoraHandler()
    processor = Processor(handler)
    transport = TSocket.TServerSocket(host='127.0.0.1', port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print('Iniciando servidor')
    server.serve()
    print('Done')
