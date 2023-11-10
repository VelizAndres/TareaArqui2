#include <msp430.h>

unsigned long tiempo = millis();

int digital = PUSH2; // Recibir valor de puerto P1.3
int estado = LOW;

int encender = 0;
int contador = 0;
int aux = 0;


void setup() {
  pinMode(digital, INPUT);
  P2DIR = 0xFF;  // Todos los pines como salida = 1111 1111 => Out = 1, In = 0
  P2OUT = 0;    // Limpiar el puerto D
 attachInterrupt(digitalPinToInterrupt(digital),Cambiar, RISING);
}

void Contador()
{
   P2OUT++;
}

void SubeBaja()
{
  if ( P2OUT == 0x80) {
    contador = 1;
  }
  else if ( P2OUT == 0x01) {
    contador = 0;
  }
  if (contador == 0) {
    if ( P2OUT == 0) {
       P2OUT = 1;
    }
    else {
       P2OUT =  P2OUT * 2;
    }
  }
  else {
     P2OUT =  P2OUT / 2;
  }
}

void ParImpar()
{
  if (contador == 0) {
    if ( P2OUT == 0) {
       P2OUT = 1;
    }
    else if ( P2OUT == 0x40) {
       P2OUT =  P2OUT * 2;
      contador = 1;
    }
    else {
       P2OUT =  P2OUT * 4;
    }
  }
  else {
    if ( P2OUT == 0x02) {
       P2OUT =  P2OUT / 2;
      contador = 0;
    }
    else {
       P2OUT =  P2OUT / 4;
    }
  }
}

void Cargador()
{
  contador = contador % 3;
  if (contador == 0) {
     P2OUT =  P2OUT % 255;
    aux =  P2OUT * 2;
     P2OUT = aux + 1;
    contador++;
    aux = 0;
  }
  else {
    if (aux == 0) {
      aux =  P2OUT;
       P2OUT =  P2OUT / 2;
    }
    else {
       P2OUT = aux;
      aux = 0;
      contador++;
    }
  }

}

void CentrOrilla()
{
  if ( P2OUT == 0) {
     P2OUT = 0x18;
    aux =  P2OUT;
  }
  else {

    if (contador == 0) {
      aux = aux / 2;
       P2OUT = ( P2OUT * 2) - aux;
    }
    else {
       P2OUT = ( P2OUT + aux) / 2;
      aux = aux * 2;

    }
    if ( P2OUT == 0x81) {
      contador = 1;
    }
    else if ( P2OUT == 0x18) {
      contador = 0;
    }
  }


}



void loop() {
  //ciclo
  if (millis()- tiempo >= 1000)
  {
    tiempo = millis();
    if (encender == 0x00)
    {
      Contador();
    }
    else if (encender == 0x01)
    {
      SubeBaja();
    }
     else if (encender == 0x02)
    {
      ParImpar();
    }
     else if (encender == 0x03)
    {
      Cargador();
    }
     else if (encender == 0x04)
    {
      CentrOrilla();
    }

  }
}

void Cambiar()
{
  contador=0;
  P2OUT = 0;
  encender++;
  if (encender == 0x05)
    {
      encender = 0;
    }
}
