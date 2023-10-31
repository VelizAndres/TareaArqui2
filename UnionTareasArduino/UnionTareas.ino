unsigned long tiempo = millis();

int digital = A0; // Recibir valor de puerto
int estado = LOW;

int encender = 0;
int contador = 0;
int aux = 0;


void setup() {
  DDRD = 0xFF;  // Todos los pines como salida = 1111 1111 => Out = 1, In = 0
  PORTD = 0;    // Limpiar el puerto D
   DDRB = 0xFF;
   PORTB =0;
}

void Contador()
{
  PORTD++;
}

void SubeBaja()
{
  if (PORTD == 0x80) {
    contador = 1;
  }
  else if (PORTD == 0x01) {
    contador = 0;
  }
  if (contador == 0) {
    if (PORTD == 0) {
      PORTD = 1;
    }
    else {
      PORTD = PORTD * 2;
    }
  }
  else {
    PORTD = PORTD / 2;
  }
}

void ParImpar()
{
  if (contador == 0) {
    if (PORTD == 0) {
      PORTD = 1;
    }
    else if (PORTD == 0x40) {
      PORTD = PORTD * 2;
      contador = 1;
    }
    else {
      PORTD = PORTD * 4;
    }
  }
  else {
    if (PORTD == 0x02) {
      PORTD = PORTD / 2;
      contador = 0;
    }
    else {
      PORTD = PORTD / 4;
    }
  }
}

void Cargador()
{
  contador = contador % 3;
  if (contador == 0) {
    PORTD = PORTD % 255;
    aux = PORTD * 2;
    PORTD = aux + 1;
    contador++;
    aux = 0;
  }
  else {
    if (aux == 0) {
      aux = PORTD;
      PORTD = PORTD / 2;
    }
    else {
      PORTD = aux;
      aux = 0;
      contador++;
    }
  }

}

void CentrOrilla()
{
  if (PORTD == 0) {
    PORTD = 0x18;
    aux = PORTD;
  }
  else {

    if (contador == 0) {
      aux = aux / 2;
      PORTD = (PORTD * 2) - aux;
    }
    else {
      PORTD = (PORTD + aux) / 2;
      aux = aux * 2;

    }
    if (PORTD == 0x81) {
      contador = 1;
    }
    else if (PORTD == 0x18) {
      contador = 0;
    }
  }


}



void loop() {

  estado = digitalRead(digital); //Capturar la lectura
    if (estado == HIGH)
    {
      delay(300);
    if (estado == HIGH ) {
      contador=0;
      PORTD = 0;
      encender++;
      PORTB = encender; 

    if (encender == 0x06)
        {
          encender = 0;
        }
        }
    }
  //ciclo
  if (millis()- tiempo >= 1000)
  {
    tiempo = millis();
    if (encender == 0x01)
    {
      Contador();
    }
    else if (encender == 0x02)
    {
      SubeBaja();
    }
     else if (encender == 0x03)
    {
      ParImpar();
    }
     else if (encender == 0x04)
    {
      Cargador();
    }
     else if (encender == 0x05)
    {
      CentrOrilla();
    }

  }
}