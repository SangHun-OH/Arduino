const int buttonPin = 15;
const int ledPin = 16; 
int buttonState = 0;

const int touchPin = 4;
const int threshold = 20;
int touchValue;

bool button = true;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  delay(1000);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  touchValue = touchRead(touchPin);
  
  if (buttonState == HIGH) {
    if(button = true){
      button = false;
    }
    else{
      button = true;
    }
  }

  if(touchValue < threshold) {
    digitalWrite(ledPin, HIGH);
    if(button = true){
      Serial.println(touchValue);
      Serial.println(" - LED on");
    }
  }
  else {
    digitalWrite(ledPin, LOW);
    if(button = true){
     Serial.println(touchValue);
     Serial.println(" - LED off");
    }
  }
  delay(500);
}
