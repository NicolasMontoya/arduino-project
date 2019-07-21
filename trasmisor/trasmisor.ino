int incomingByte = 0;
bool dataArray[600];
bool tmp[4];
int actualpos = 0;
bool state = 0;

int LED1 = 13;
int LED2 = 12;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
  Serial.println("'q' -> Borrar datos ");
  Serial.println("Ingrese opción: \n");
}

void loop() {
  
  while ( Serial.available() ) {
      incomingByte = Serial.read();
      if (incomingByte == 'q') {
        Serial.println("Arreglo borrado");
        deleteArray();
      } else if (incomingByte == 'e') {
        Serial.println("INICIO ENVIO DE INFORMACIÓN");
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        delay(2000);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        delay(2000);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        delay(2000);
        for (int i = 0 ; i < actualpos ; i = i + 2 ){
            if (dataArray[i] == true) {
              digitalWrite(LED1, HIGH);
            } else {
              digitalWrite(LED1, LOW);
              }
            if (dataArray[i + 1] == true) {
              digitalWrite(LED2, HIGH);
            } else {
              digitalWrite(LED2, LOW);
              }
           delay(2000);
          }
          digitalWrite(LED1, LOW);
          digitalWrite(LED2, LOW);
          delay(500);
          digitalWrite(LED1, HIGH);
          digitalWrite(LED2, HIGH);
          delay(500);
          digitalWrite(LED1, LOW);
          digitalWrite(LED2, LOW);
          delay(500);
      } else if (incomingByte > 47 && incomingByte < 58) {
          fromByte(incomingByte - 48, tmp);
          locateData(tmp);
          actualpos = actualpos + 4;
          Serial.println("Cargado");   
      } else {
        Serial.println("No es un caracter válido");
        }
  }

}

void fromByte(unsigned int c, bool b[4])
{
    int k = 4;
    for (int i=0; i < 4; ++i)
        b[--k] = (c & (1<<i)) != 0;
}

void locateData(bool source[4]) {
  for (int i = 0; i < 4; ++i)
        dataArray[actualpos + i] = source[i];
}

void deleteArray() {
  actualpos = 0;
}

void printArray() {
  for (int i = 0; i < actualpos; ++i)
        Serial.println(dataArray[i]);
}
