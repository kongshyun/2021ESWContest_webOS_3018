#include <AccelStepper.h>
#include <SoftwareSerial.h>
#define FULLSTEP 8  //Half-step mode (8 step control signal sequence)
#define HALFSTEP 4  //하프와 풀의 차이는 전류또는 속도와관련, 풀이더빠름
//모터 핀 번호 정의(1번모터: 8~11, 2번모터: 3~6)
#define mtrPin1  8     // IN1 on the ULN2003 driver 1
#define mtrPin2  9     // IN2 on the ULN2003 driver 1
#define mtrPin3  10     // IN3 on the ULN2003 driver 1
#define mtrPin4  11     // IN4 on the ULN2003 driver 1
#define mtrPin_1  4     // IN1 on the ULN2003 driver 2
#define mtrPin_2  5     // IN2 on the ULN2003 driver 2
#define mtrPin_3  6     // IN3 on the ULN2003 driver 2
#define mtrPin_4  7     // IN4 on the ULN2003 driver 2

unsigned long steps = 2048;//한바퀴 스텝수
unsigned long rotation_number_1=3*steps;//원하는 모터 회전수
unsigned long rotation_number_2=2*steps;//원하는 모터 회전수


AccelStepper stepper1(HALFSTEP, mtrPin1, mtrPin3, mtrPin2, mtrPin4); //모터1정의
AccelStepper stepper2(HALFSTEP, mtrPin_1, mtrPin_3, mtrPin_2, mtrPin_4); //모터2정의

#define ONE_TURN_PULSE 3600 
u16 motorPosition;

SoftwareSerial espSerial(2, 3);
String str_read;
char str_status[50];
char buff[50]; // srial buffer
String window = "close";
String light1 = "off";
String light2 = "off";
int main_cnt = 0;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  stepper1.setMaxSpeed(2000.0);
  stepper2.setMaxSpeed(2000.0);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}
char state;

void loop(){
  //모터정지상태
  stepper1.stop();
  stepper2.stop();
  stepper1.disableOutputs(); //motor power disconnect, so motor led will turn off
  stepper2.disableOutputs();
  Serial.println("NOOOOOOO");delay(500);//모터정지상태(전원x)일때 STOP보내기
  
  if(Serial.available()){  //데이터가 들어오면
    str_read = espSerial.readStringUntil('\n');  //state에 읽은 데이터 입력
    if (str_read.startsWith("command")) {
      if (str_read.substring(8) == "open") {
        window = "open";
        _Open();  //창문열기
      } else if (str_read.substring(8) == "close") {
        window = "close";
        _Close();  //창문닫기
      } else if (str_read.substring(8) == "light1:on") {
        light1 = "on"
        digitalWrite(13,HIGH);
      } else if (str_read.substring(8) == "light1:off") {
        light1 = "off"
        digitalWrite(13,LOW);
      } else if (str_read.substring(8) == "light2:on") {
        light2 = "on"
        digitalWrite(12,HIGH);
      } else if (str_read.substring(8) == "light2:off") {
        light1 = "off"
        digitalWrite(12,LOW);
      }
    }
  }
  delay(1);
  main_cnt++;
  if (main_cnt >= 3000) {
    sprintf(str_status, "window:%s,light1:%s,light2:%s", window, light1, light2);
    espSerial.println(str_status);
    Serial.println("Send status");
  }
}

void _Open() {  //창문열기(시계방향회전)
  for (;;) {
    stepper1.moveTo(rotation_number_1);
    stepper2.moveTo(rotation_number_2);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    if ((stepper1.distanceToGo()==0) and (stepper2.distanceToGo()==0)){//모터2개 회전수같으면||써도됨
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      Serial.println("'The Window Is Open'");
      return;
    }
  }
}

void _Close(){ //창문닫기(반시계방향회전)
  for(;;){
    stepper1.moveTo(-rotation_number_1);
    stepper2.moveTo(-rotation_number_2);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    if ((stepper1.distanceToGo()==0)and(stepper2.distanceToGo()==0)){
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      Serial.println("'The Window Is Closed'");
      return;
    }
  }
}
