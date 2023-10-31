int encender = 0;
int contador = 0;
int aux = 0;

void configurar()  //Configuracion del TIMER
{
  T0CON = 0x03;
  TMR0L = 0xEE;
  TMR0H = 0x85;
  ADCON1 = 0x0F;
  TRISB = 0x01;
  PORTB = 0;
  TRISD = 0;
  PORTD = 0;
  INTCON = 0xc0;
  INTCON2 = 0xF4;
  INT0IE_bit = 1;
}


//Bloque de acciones
// Opcion 0
void Contar()
{
  PORTD = PORTD + 1;
}
 // Opcion 1
void SubeBaja()
{
  if (PORTD == 0x80) {
    contador = 1;
  }
  else if (PORTD == 1) {
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

// Opcion 2
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
// Opcion 3
void Vumetro()
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
// Opcion 4
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

//Fin Bloque acciones

void interrupt()
{
  if (T0IF_bit == 1) {
    TMR0ON_bit = 0;
    T0IE_bit = 0;
    T0IF_bit = 0;
    TMR0L = 0xEE;
    TMR0H = 0x85;

    if(encender == 0)
    {
      Contar();
    }
    else if(encender == 0x01)
    {
      SubeBaja();
    }
    else if(encender == 0x02)
    {
      ParImpar();
    }
    else if(encender == 0x03)
    {
      Vumetro();
    }
    else if(encender == 0x04)
    {
      CentrOrilla();
    }
    T0IE_bit = 1;
    T0CON = 0x83;
  }
  else {
    if (INT0IF_bit == 1) {
      INT0IE_bit = 0;
      INT0IF_bit = 0;
      if (encender < 0x05) {
        PORTD = 0;
        contador = 0;
        encender++;
      }
      else if(encender == 0x05) {
        encender = 0;
      }
      INT0IE_bit = 1;
    }
  }
}


void main()
{
  configurar();
  while (1) {
    if (encender == 0) {
      T0IE_bit = 1;
      TMR0ON_bit = 1;
    }
    else if(encender == 0x05) {
      T0IE_bit = 0;
      TMR0ON_bit = 0;
    }
  };
}