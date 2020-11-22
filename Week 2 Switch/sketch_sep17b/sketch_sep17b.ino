const int ledPin = 16;
const int buttonPin = 15;
int buttonState = 0;


char serState = NULL;
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}
void loop() {
  if (Serial.available() > 0)
    serState = Serial.read();
  if (serState == 'h') {
    digitalWrite(ledPin, HIGH);
  }else if (serState == 'l') {
    digitalWrite(ledPin, LOW);
  }
  delay(250);
}
