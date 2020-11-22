#include <AWS_IOT.h>
#include <WiFi.h>
#include <Arduino_JSON.h>

AWS_IOT hornbill;

const char* ssid = "U+Net9410";
const char* password = "DD6D001259";

char HOST_ADDRESS[] = "a3ov9q9iaitm4a-ats.iot.ap-northeast-2.amazonaws.com";
char CLIENT_ID[] = "SangESP32";
char sTOPIC_NAME[] = "esp32/led";
//char pTOPIC_NAME[] = "esp32/bme280";

int status = WL_IDLE_STATUS;
int msgCount = 0, msgReceived = 0;
char payload[512];
char rcvdPayload[512];
const int buttonPin = 15; // pushbutton pin
unsigned long preMil = 0;
const long intMil = 5000;
const int ledPin = 16;

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
  strncpy(rcvdPayload, payLoad, payloadLen);
  rcvdPayload[payloadLen] = 0;
  msgReceived = 1;
}
void setup() {
  Serial.begin(115200);
  //++choi This is here to force the ESP32 to reset the WiFi and initialise correctly.
  Serial.print("WIFI status = ");
  Serial.println(WiFi.getMode());
  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);
  delay(1000);
  Serial.print("WIFI status = ");
  Serial.println(WiFi.getMode()); //++choi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to wifi");
  if (hornbill.connect(HOST_ADDRESS, CLIENT_ID) == 0) {
    Serial.println("Connected to AWS");
    delay(1000);
    if (0 == hornbill.subscribe(sTOPIC_NAME, mySubCallBackHandler)) {
      Serial.println("Subscribe Successfull");
    }
    else {
      Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
      while (1);
    }
  }
  else {
    Serial.println("AWS connection failed, Check the HOST Address");
    while (1);
  }
  // initialize the pushbutton pin as an input
  pinMode(ledPin, OUTPUT);
  delay(2000);
}

void loop() {
  if (msgReceived == 1)
  {
    msgReceived = 0;
    Serial.print("Received Message:");
    Serial.println(rcvdPayload);
    // Parse JSON
    JSONVar myObj = JSON.parse(rcvdPayload);
    JSONVar state = myObj["state"];
    String led = (const char*) state["led"];
    Serial.print("LED will be ");
    Serial.println(led);
    if (led == "ON")
      digitalWrite(ledPin, HIGH);
    else if (led == "OFF")
      digitalWrite(ledPin, LOW);
  }
}
