const int buttonPin = 15;
const int ledPin = 16;
int buttonState = 0;
const int touchPin = 4;
const int threshold = 20;
int touchValue;


void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  
  if ( (buttonState == HIGH) || (touchValue < threshold) ){
    digitalWrite (ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
  delay(500);
}
