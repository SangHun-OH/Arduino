const int buttonPin = 15; // the number of the pushbutton pin
const int ledPin = 16; 
int buttonState = 0;

const int touchPin = 4;
const int threshold = 20;
int touchValue;
bool button = true;

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
  if(button){
    Serial.println(touchValue);
    Serial.println(" - LED on");
  }
}
else {
  digitalWrite(ledPin, LOW);
  if(button){
    Serial.println(touchValue);
    Serial.println(" - LED off");
  }
}

if (buttonState == HIGH) {
  if(button == true){
    button = false;
   // Serial.println("Button Value : false");
  }else{
    button = true;
   // Serial.println("Button Value : true");
  }
}

delay(500);
}
