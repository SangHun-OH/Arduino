const int touchPin = 4;
const int ledPin = 16;
const int threshold = 20;
int touchValue;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode (ledPin, OUTPUT);
}

void loop() {

  touchValue = touchRead(touchPin);
  Serial.print(touchValue);

  if(touchValue < threshold) {
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED off");
  }
  delay(500);
}
