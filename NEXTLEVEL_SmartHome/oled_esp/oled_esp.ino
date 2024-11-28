#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <string.h>

const char* ssid = "KSH";
const char* password = "01030189958";
const char* websockets_server_host = "192.168.1.11"; //Enter server adress
const uint16_t websockets_server_port = 3001; // Enter server port
String jsondata;
StaticJsonDocument<200> send_doc;
StaticJsonDocument<200> get_doc;
int temp = 32;
int humi = 28;
int temp_index;
String str_read;

using namespace websockets;
WebsocketsClient client;

void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  delay(1000);

  bool connected = client.connect(websockets_server_host, websockets_server_port, "/");

  client.onMessage([&](WebsocketsMessage message) { //서버로부터 값을 받으면 호출
    deserializeJson(get_doc, message.data());
    if (get_doc["msg_type"] == "command" && get_doc["device_id"] == "aircon") {
      if (get_doc["command"] == "on") { //esp->아두이노 보드 serial print
        Serial.println("command:on");
      } else if (get_doc["command"] == "off") {
        Serial.println("command:off");
      }
    }
  });
}

void loop() {
  while (client.available()) {
    client.poll();
    delay(500);
    str_read = Serial.readStringUntil('\n'); //아두이노 보드 -> esp serial read
    if (str_read.startsWith("temp")) {
      temp_index = str_read.indexOf(",");
      temp = str_read.substring(5, temp_index).toInt(); serial에서 값 추출
      humi = str_read.substring(temp_index + 6).toInt();
      send_doc["msg_type"] = "status"; //json 만들기
      send_doc["devide_id"] = "aircon";
      send_doc["temp"] = String(temp);
      send_doc["humi"] = String(humi);
      serializeJson(send_doc, jsondata);
      client.send(jsondata);//send json
      jsondata = "";
    }
  }
}
