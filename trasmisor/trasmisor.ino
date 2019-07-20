int incomingByte = 0;
bool dataArray[600];
bool tmp[8];
int actualpos;

void setup() {
  Serial.begin(9600);
  Serial.println("'q' -> Borrar datos ");
  Serial.println("Ingrese opción: \n");
}

void loop() {
  
  while ( Serial.available() ) {
      incomingByte = Serial.read();
      if (incomingByte == 113) {
        deleteArray();
      } else if (incomingByte > 47 && incomingByte < 58) {
          fromByte(incomingByte - 48, tmp);
          for (int i = 0; i < 8; ++i)
              Serial.println(tmp[i]);          
      } else {
        Serial.println("No es un caracter válido");
        }
  }

}

void fromByte(unsigned int c, bool b[8])
{
    for (int i=0; i < 8; ++i)
        b[i] = (c & (1<<i)) != 0;
}

void locateData(bool source[8]) {
  for (int i = 0; i < 8; ++i)
        dataArray[actualpos + i] = source[i];
}

void deleteArray() {
  actualpos = 0;
}

void printArray() {
  for (int i = 0; i < 20; ++i)
        Serial.println(dataArray[i]);
}
