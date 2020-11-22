const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 23;
const int duty = 128;
const int trigPin = 22;
const int echoPin = 18;

int sVal;

int nFrq[] = {233, 294, 330, 349, 392, 440, 494, 523};

void playNote(int note, int dur) {
  ledcSetup(ledChannel, nFrq[note], resolution);
  ledcWrite(ledChannel, duty);
  Serial.println(note);
  delay(dur);
}

void setup() {
  Serial.begin(115200);
  ledcAttachPin(buzPin, ledChannel);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW); // trig low for 2us
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // trig high for 10us
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 17 / 1000;

  Serial.print(distance);
  Serial.print("cm");
  Serial.println();

  delay(100);
  if (distance > 0 && distance <= 10)
    playNote(7 , 250);
  if (distance > 10 && distance <= 15)
    playNote(6 , 250);
  if (distance > 15 && distance <= 20)
    playNote(5 , 250);
  if (distance > 20 && distance <= 25)
    playNote(4 , 250);
  if (distance > 25 && distance <= 30)
    playNote(3 , 250);
  if (distance > 30 && distance <= 35)
    playNote(2 , 250);
  if (distance > 35 && distance <= 40)
    playNote(1 , 250);
  if (distance > 40 )
    playNote(0 , 250);
}
