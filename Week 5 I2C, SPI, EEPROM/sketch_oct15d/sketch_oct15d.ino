
#include <EEPROM.h> // define the number of bytes you want to access 
#include <vector>
#include <algorithm>
#define EEPROM_SIZE 100
// music play station by using pwm
// choi++20200924 
//   freq -> pitch 
//   duty -> volume (?)
// setting PWM properties 
const int ledChannel = 0; 
const int resolution = 8; 
const int buzPin = 2; 
const int duty = 128;
// variables 
int vNote=0, vDur=0; 
const int dDur = 250; // default duration
// notes 
//enum Notes {C3=0, CS3, D3, DS3, E3, F3}; 
int nFrq[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523}; 
int nDur[] = { 2000, 1500, 1000, 750, 500, 375, 250, 5000 };
int count =0;
int count2=0;
int arr[150]={-1,};
void playNote(int note, int dur) { 
  if (note == -1) { 
    ledcSetup(ledChannel, 0, resolution);
    ledcWrite(ledChannel, 0); 
    }else { 
     ledcSetup(ledChannel, nFrq[note], resolution); 
     ledcWrite(ledChannel, duty); 
    } 
      Serial.println(String(note)+","+String(dur));
      delay(nDur[dur]);
}

void setup() { 
  Serial.begin(115200); 
  EEPROM.begin(EEPROM_SIZE); 
  // attach the channel to the GPIOs 
  ledcAttachPin(buzPin, ledChannel);
  EEPROM.write(0, 0xAA);
  EEPROM.write(1, 0x55);
 // EEPROM.write(2, 0);
  EEPROM.commit();
   
  if(EEPROM.read(2)<150){
    for(int i=0;i<EEPROM.read(2);i++){
      arr[i]=EEPROM.read(i+3);
    }
    for(int i=0;arr[i]!=-1;i+=2){
      playNote(arr[i],arr[i+1]);
    }
  }
 }
void loop(){ 
  if (Serial.available() > 0) { 
    vNote = Serial.read();
      if(vNote =='<'){
        if (Serial.available() > 0) { 
          vNote = Serial.read();
          vDur = Serial.read(); 
          if (vDur <= '6' && vDur >= '0') 
            vDur -= '0'; 
          else vDur = dDur; 
          if (vNote <= '9' && vNote >= '0') 
            vNote -= '0'; 
          else if (vNote <= 'c' && vNote >= 'a') 
            vNote = vNote - 'a' + 10; 
          else 
            vNote = -1;              
          // rest 
          playNote(vNote, vDur);
          EEPROM.write(2,count);
          EEPROM.write(count+3,vNote);
          EEPROM.write(count+4,vDur);
          EEPROM.commit();
          count+=2;
          count2=1;
        }
      }else if(vNote == '>'){
        if (Serial.available() > 0) { 
          vNote = Serial.read();
          vDur = Serial.read(); 
          if (vDur <= '6' && vDur >= '0') 
            vDur -= '0'; 
          else vDur = dDur; 
          if (vNote <= '9' && vNote >= '0') 
            vNote -= '0'; 
          else if (vNote <= 'c' && vNote >= 'a') 
            vNote = vNote - 'a' + 10; 
          else 
            vNote = -1;              
          // rest 
          playNote(vNote, vDur);
          count2=0;
        }
      }else if(count2==1){
        if (Serial.available() > 0) { 
          vDur = Serial.read(); 
          if (vDur <= '6' && vDur >= '0') 
            vDur -= '0'; 
          else vDur = dDur; 
          if (vNote <= '9' && vNote >= '0') 
            vNote -= '0'; 
          else if (vNote <= 'c' && vNote >= 'a') 
            vNote = vNote - 'a' + 10; 
          else 
            vNote = -1;              
          // rest 
          playNote(vNote, vDur);
          EEPROM.write(2,count);
          EEPROM.write(count+3,vNote);
          EEPROM.write(count+4,vDur);
          EEPROM.commit();
          count+=2;
        }    
  }else if(count2==0){
        if (Serial.available() > 0) { 
          vDur = Serial.read(); 
          if (vDur <= '6' && vDur >= '0') 
            vDur -= '0'; 
          else vDur = dDur; 
          if (vNote <= '9' && vNote >= '0') 
            vNote -= '0'; 
          else if (vNote <= 'c' && vNote >= 'a') 
            vNote = vNote - 'a' + 10; 
          else  
            vNote = -1;              
          // rest 
          playNote(vNote, vDur);
        }
    }
  }
}
