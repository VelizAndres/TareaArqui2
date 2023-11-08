#Cargar modulo de control de puerto serial

import serial
import time

#Crear variable de tipo objeto serial
#baudrate -> Velocidad de 
arduino = serial.Serial(port = 'COM3', baudrate = 9600, timeout= 0.1)

#Funcion de lectura escritura de puerto serial
def wrSerial(x):
    arduino.write(bytes(x,'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

# Bloque principal
while True:
    num = input('Ingrese un numero:')
    valor = wrSerial(num)
    if (valor == b'0\r\n'):
        print('Apagado')
    else:
        print('Encendido')
        