#include <AWS_IOT.h>
#include <WiFi.h>
#include <Arduino_JSON.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
int delayTime;
AWS_IOT hornbill;

const char* ssid = "U+Net9410";
const char* password = "DD6D001259";

char HOST_ADDRESS[] = "a3ov9q9iaitm4a-ats.iot.ap-northeast-2.amazonaws.com";
char CLIENT_ID[] = "SangESP32";
char sTOPIC_NAME[] = "$aws/things/ESP32_BME280_LED/shadow/update";
char pTOPIC_NAME[] = "$aws/things/ESP32_BME280_LED/shadow/update";

int status = WL_IDLE_STATUS;
int msgCount = 0, msgReceived = 0;
char payload[512];
char rcvdPayload[512];
const int buttonPin = 15; // pushbutton pin
unsigned long preMil = 0;
const long intMil = 5000;
const int ledPin = 16;

String ledV;
void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" `%");
  Serial.println();
}
void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
  strncpy(rcvdPayload, payLoad, payloadLen);
  rcvdPayload[payloadLen] = 0;
  msgReceived = 1;
}
void setup() {
  bool status;
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
  Serial.println(F("BME280 test"));
  // default settings
  status = bme.begin(0x76); // bme280 I2C address = 0x76
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print(" ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print(" ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print(" ID of 0x60 represents a BME 280.\n");
    Serial.print(" ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  Serial.println("-- Default Test --");
  delayTime = 1000;
  Serial.println();
}
void loop() {
  if (msgReceived == 1)
  {
    msgReceived = 0;
    Serial.print("Received Message:");
    Serial.println(rcvdPayload);
  }
  if ((millis() - preMil) > intMil) {
    // read the state of the pushbutton value
    preMil = millis();
    // sprintf(payload,"Hello from hornbill ESP32 : % d",msgCount++);
    if(bme.readTemperature() > 30 && bme.readHumidity() > 40){
      ledV = "OFF";
    }else{
      ledV = "ON";
    }
    sprintf(payload, "{\"state\":{\"reported\":{\"temp\":%f,\"humid\":%f,\"led\":\"%s\"}}}", bme.readTemperature(), bme.readHumidity(),ledV);
    if (hornbill.publish(pTOPIC_NAME, payload) == 0) {
      Serial.print("Publish Message: ");
      Serial.println(payload);
    }
    else
      Serial.println("Publish failed");
  }

  // Parse JSON
  JSONVar myObj = JSON.parse(rcvdPayload);
  JSONVar state = myObj["state"];
  JSONVar reported = state["reported"];
  String led = (const char*) reported["led"];
  if (led == "ON")
    digitalWrite(ledPin, HIGH);
  else if (led == "OFF")
    digitalWrite(ledPin, LOW);

  // printValues();
  // delay(delayTime);
}
