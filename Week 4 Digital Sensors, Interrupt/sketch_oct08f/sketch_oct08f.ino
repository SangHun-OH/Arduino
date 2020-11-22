#define timeSeconds 20
// Set GPIOs for LED and PIR Motion Sensor
const int led1 = 5;
const int led2 = 17;
const int led3 = 16;
const int motionSensor = 36;
int count = 0;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger1 = 0;
unsigned long lastTrigger2 = 0;
unsigned long lastTrigger3 = 0;

boolean startTimer1 = false;
boolean startTimer2 = false;
boolean startTimer3 = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR detectsMovement() {
  if (count%3 == 0) {
    Serial.println("MOTION (0) DETECTED!!!");
    digitalWrite(led1, HIGH);
    startTimer1 = true;
    lastTrigger1 = millis();
    count += 1;
  }
  else if (count %3 == 1) {
    Serial.println("MOTION (1) DETECTED!!!");
    digitalWrite(led2, HIGH);
    startTimer2 = true;
    lastTrigger2 = millis();
    count += 1;
  }
  else if (count %3 == 2) {
    Serial.println("MOTION (2) DETECTED!!!");
    digitalWrite(led3, HIGH);
    startTimer3 = true;
    lastTrigger3 = millis();
    count += 1;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  // Current time
  now = millis();

  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if (startTimer1 && (now - lastTrigger1 > (timeSeconds * 1000))) {
    Serial.println("Motion (0) stopped...");
    digitalWrite(led1, LOW);
    startTimer1 = false;
  }
  if (startTimer2 && (now - lastTrigger2 > (timeSeconds * 1000))) {
    Serial.println("Motion (1) stopped...");
    digitalWrite(led2, LOW);
    startTimer2 = false;
  }
  if (startTimer3 && (now - lastTrigger3 > (timeSeconds * 1000))) {
    Serial.println("Motion (2) stopped...");
    digitalWrite(led3, LOW);
    startTimer3 = false;
  }
}
