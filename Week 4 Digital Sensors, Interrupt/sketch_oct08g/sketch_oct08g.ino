#define timeSeconds 20
const int motionSensor = 36;
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
const int ledPin[3] = {16, 5, 7};
int ledState[3] = {LOW, LOW, LOW};
unsigned long previousMillis = 0;
int count = 0;
void IRAM_ATTR detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
  count = count + 1;
  digitalWrite(ledPin[count], HIGH);
  startTimer = true;
  lastTrigger = millis();
}
void setup() {
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  pinMode(ledPin[0], OUTPUT);
  pinMode(ledPin[1], OUTPUT);
  pinMode(ledPin[2], OUTPUT);
}
void loop() {
  now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if (startTimer && (now - lastTrigger > (timeSeconds * 1000)))
  {
    Serial.println("Motion stopped...");
    digitalWrite(ledPin[count], LOW);
    startTimer = false;
  }
}
