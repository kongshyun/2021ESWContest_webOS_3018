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
String window = "close";
String light1 = "off";
String light2 = "on";
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

  client.onMessage([&](WebsocketsMessage message) {
    deserializeJson(get_doc, message.data());
    if (get_doc["msg_type"] == "command" && get_doc["device_id"] == "lightwindow") {
      if (get_doc["command"] == "open") {
        Serial.println("command:open");
      } else if (get_doc["command"] == "close") {
        Serial.println("command:close");
      } else if (get_doc["command"] == "light1:on") {
        Serial.println("command:light1:on");
      } else if (get_doc["command"] == "light1:off") {
        Serial.println("command:light1:off");
      } else if (get_doc["command"] == "light2:on") {
        Serial.println("command:light2:on");
      } else if (get_doc["command"] == "light2:off") {
        Serial.println("command:light2:off");
      } 
    }
  });
}

void loop() {
  while (client.available()) {
    client.poll();
    delay(500);
    str_read = Serial.readStringUntil('\n');
    if (str_read.startsWith("temp")) {
      temp_index = str_read.indexOf(",");
      temp = str_read.substring(5, temp_index).toInt();
      humi = str_read.substring(temp_index + 6).toInt();
      send_doc["msg_type"] = "status";
      send_doc["devide_id"] = "lightwindow";
      send_doc["temp"] = String(window);
      send_doc["humi"] = String(light1);
      send_doc["humi"] = String(light2);
      serializeJson(send_doc, jsondata);
      //Serial.println(jsondata);
      client.send(jsondata);
      jsondata = "";
    }
  }

}
