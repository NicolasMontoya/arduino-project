int incomingByte = 0;
bool dataArray[600];
bool tmp[8];
int printpos = 0;
int arraylength = 0;
bool state = 0;
int totalCharacters = 0;

int LED1 = 13;
int LED2 = 12;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
  Serial.println("'n' -> Enviar siguiente ");
  Serial.println("'p' -> Enviar anterior ");
  Serial.println("'b' -> Borrar carga ");
  Serial.println("'c' -> Cargar datos ");
  Serial.println("Ingrese opción: \n");
}

void loop() {
  
  while ( Serial.available() ) {
      incomingByte = Serial.read();
      if (incomingByte == 'n') {
        Serial.println("Enviando siguiente caracter ...");
        printByte();
      }
      else if (incomingByte == 'p') {
        Serial.println("Enviando caracter anterior ...");
        printpos -= 8;
        if (printpos < 0) {
          printpos = 0;  
        }
        printByte();
      }
      else if (incomingByte == 'c') {
        Serial.println("Entro a modo cargar - Ingrese caracteres");
        while (1){
            while(Serial.available()) {
              incomingByte = Serial.read();
              if (incomingByte > 0 && incomingByte < 144) {
                  locateData(incomingByte, tmp);
                  arraylength = arraylength + 8;
                  totalCharacters += incomingByte & 0x07;
                  Serial.println("Simbolo cargado  ");   
              }
            }
            if (totalCharacters >= 64) {
              Serial.print(totalCharacters);
              break;  
            }
          }
      } else if (incomingByte == 'b'){
          deleteArray();
      }
    
  }

}

void fromByte(unsigned int c, bool b[8])
{
    int k = 8;
    for (int i=0; i < 8; ++i){
        b[--k] = (c & (1<<i)) != 0;}
}

void locateData(int c, bool source[8]) {
  int k = 8;
  for (int i=0; i < 8; ++i)
      source[--k] = (c & (1<<i)) != 0;
  for (int i = 0; i < 8; ++i){
        Serial.print(source[i]);
        dataArray[arraylength + i] = source[i];}
}

void deleteArray() {
  arraylength = 0;
  totalCharacters = 0;
}

void printByte() {
  digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        delay(2000);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        delay(2000);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        delay(2000);
        int finalData = printpos + 8;
        while ( (printpos < finalData) &&  (printpos < arraylength) ) {
            if (dataArray[printpos] == true) {
              Serial.println("1");
              digitalWrite(LED1, HIGH);
            } else {
              Serial.println("0");
              digitalWrite(LED1, LOW);
              }
            if (dataArray[printpos + 1] == true) {
              Serial.println("1");
              digitalWrite(LED2, HIGH);
            } else {
              Serial.println("0");
              digitalWrite(LED2, LOW);
              }
           printpos+=2;
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
}

void printArray() {
  for (int i = 0; i < arraylength; ++i)
        Serial.println(dataArray[i]);
}
