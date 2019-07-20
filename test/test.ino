char incomingByte = 0;

int LED1 = 13;
int LED2 = 12;


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  while ( Serial.available() ) {
      incomingByte = Serial.read();
      Serial.println(incomingByte);
      if ( incomingByte == 49 ) {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
      } else if ( incomingByte == 48 ) {
        digitalWrite(LED2, HIGH);
        digitalWrite(LED1, LOW);
        
        }
  }

}
