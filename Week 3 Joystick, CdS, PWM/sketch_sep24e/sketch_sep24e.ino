const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 23;
const int duty = 128;

int tVal, dVal;

int nFrq[] = {262, 294, 330, 349, 392, 440, 494, 523};

int dfrq[] = {187, 125, 250, 375, 500, 750, 1000};

void playNote(int note, int dur) {

  
  ledcSetup(ledChannel, nFrq[note], resolution);
  ledcWrite(ledChannel, duty);
  Serial.println(note);
  Serial.println(dur);
  delay(dfrq[dur]);
}
void setup() {
  Serial.begin(115200);
  ledcAttachPin(buzPin, ledChannel);
}
void loop() {
  if (Serial.available() > 0) {
    tVal = Serial.read();
    dVal = Serial.read();
    if(tVal == 11){
      delay (250);
    }
    else
      playNote(tVal - 0x30, dVal - 0x30);
  }
}
