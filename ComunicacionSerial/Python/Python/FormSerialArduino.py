from tkinter import *
import serial
#Crear variable de tipo objeto serial
#baudrate -> Velocidad de 
arduino = serial.Serial(port = 'COM3', baudrate = 9600, timeout= 0.1)


def ledStatus():
    if estado.get == 'Encender': x = 0 
    else: x =1
    arduino.write(bytes(x,'utf-8'))

    if x == 0:
        estado.set('Encender')
    else:
        estado.set('Apagar')


## Formulario
frmRoot = Tk()

frmRoot.geometry('400x300')
estado = StringVar()
estado.set('Encender')
lblTitulo = Label(frmRoot, text = 'Encendido/Apagado')
lblTitulo.pack()
btnStatus = Button(frmRoot, textvariable= estado, command=ledStatus)
btnStatus.pack()


frmRoot.mainloop()