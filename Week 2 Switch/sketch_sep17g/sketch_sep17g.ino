const int buttonPin = 15; // the number of the pushbutton pin
const int ledPin = 16; 
int buttonState = 0;

const int touchPin = 4;
const int threshold = 20;
int touchValue;
bool button = true;
int value = 1;

void setup() {
Serial.begin(115200);
pinMode(buttonPin, INPUT);
delay(1000);
pinMode(ledPin, OUTPUT);
}

void loop() {
  
touchValue = touchRead(touchPin);
buttonState = digitalRead(buttonPin);

if(touchValue < threshold) {
  digitalWrite(ledPin, HIGH);
  if(value = 1){
    Serial.println(touchValue);
    Serial.println(" - LED on");
  }
}
else {
  digitalWrite(ledPin, LOW);
  if(value = 1){
    Serial.println(touchValue);
    Serial.println(" - LED off");
  }
}

if (buttonState == HIGH) {
  if(value = 1){
    value = 0;
   // Serial.println("Button Value : false");
  }else{
    value = 1;
   // Serial.println("Button Value : true");
  }
}

delay(500);
}
