#include <SoftwareSerial.h>
//#include <TimerOne.h> // timer interrupt
#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//SoftwareSerial serialName(RX, TX);
SoftwareSerial espSerial(2, 3);

String str_read;
char str_status[50];
char buff[50]; // srial buffer
int temp_home = 32; // 실내 온도 값
int humi = 28;
String aircon_onoff = "off";
int main_cnt = 0;
int cnt = 0;
 
void setup() {
  Serial.begin(9600);
  delay(100);
  
  espSerial.begin(9600);
  delay(100);
  
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_crox5hb_tf);  
  u8g2.setFontDirection(0);
}
 
void loop() {
  str_read = espSerial.readStringUntil('\n');
  Serial.println(str_read);
  if (str_read.startsWith("command")) {
    if (str_read.substring(8) == "on") {
      aircon_onoff = "on";
      Serial.println(aircon_onoff);
    } else {
      aircon_onoff = "off";
      Serial.println(aircon_onoff);
    }
  }
  u8g2.firstPage();
  do {
    u8g2.setCursor(70, 23);
    u8g2.print(String(temp_home));
    u8g2.setCursor(70, 60);
    u8g2.print(String(humi));
  } while ( u8g2.nextPage() );
  delay(1);
  main_cnt++;
  if (main_cnt >= 3000) {
    if (aircon_onoff == "on") {
      temp_home--;
      humi--;
    } else {
      temp_home++;
      humi++;
    }
    sprintf(str_status, "temp:%d,humi:%d", temp_home, humi);
    espSerial.println(str_status);
    Serial.println("Send status");
  }
}
