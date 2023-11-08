const int LED = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//Configurar velocidad de serial
  pinMode(LED, OUTPUT); //Configurar pin como salida
  digitalWrite(LED, LOW);  //Se inicializa el pin con valor 0
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    char dato = Serial.read(); //Lee el valor mandado por la comunicacion serial
    if(dato == '1') //Compara con el caracter 41 => 1
    {
      digitalWrite(LED, HIGH);
      Serial.println("Encendido");
    }
    else if(dato == '0') //Compara con caracter 48 =>0
    {
      digitalWrite(LED, LOW);
      Serial.println("Apagado");
    }
  }
}
