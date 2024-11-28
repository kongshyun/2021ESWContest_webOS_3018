#include <SoftwareSerial.h>

const int analogIn = A0; //아날로그 입력 PIN  
int mVperAmp = 185; // 아날로그 입력 mV당 전류 값  
                   // 5A 짜리는 185  
                   // 20A 짜리는 100  
                   // 30A 짜리는 66  
int RawValue= 0;   // 아날로그 값 저장 변수  
int ACSoffset = 2500; // 기준 값 0A일때 아날로그 값은 2500mV 이다.  
double Voltage = 0;   // 계산된 아날로그 값  
double Amps = 0;      // 실제 측정된 전류 값  
int cnt = 0;  
int main_cnt = 0;
double smoothAmps = 0;  

SoftwareSerial espSerial(2, 3);
String str_read;
String aircon_onoff = "off";
char str_status[50];
char buff[50]; // srial buffer

  
void setup(){   
  Serial.begin(9600);  
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
 
  espSerial.begin(9600);
}  
void loop(){  
  RawValue = analogRead(analogIn);  
  Voltage = (RawValue / 1024.0) * 5000;    
  Amps = ((Voltage - ACSoffset) / mVperAmp) * 1000;  
  smoothAmps = Amps * 0.01 + smoothAmps * 0.99;
  if ( cnt++ > 100 ) {
     Serial.print("Current= ");    
     Serial.println(smoothAmps);   
     cnt = 0;  
  } 
  if(Serial.available()){
    str_read = espSerial.readStringUntil('\n');
    if (str_read.startsWith("command")) {
      if (str_read.substring(8) == "on") {
        aircon_onoff = "on";
        digitalWrite(5,HIGH);
        digitalWrite(6,LOW);
      } else {
        aircon_onoff = "off";
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
      }
    }
  }
  main_cnt++;
  if (main_cnt >= 3000) {
    sprintf(str_status, "aircon_onoff:%s", aircon_onoff);
    espSerial.println(str_status);
    Serial.println("Send status");
  }
  delay(1); 
}
