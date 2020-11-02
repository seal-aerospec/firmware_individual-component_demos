
#include "awsCredentials.h"
#include "wifiCredential.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

//giving esp32 a static ip address
IPAddress ip(192, 168, 1, 43); //ESP32 IP
IPAddress gateway(192, 168, 1, 1); //Router IP
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);
   
  
void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (!WiFi.config(ip, gateway, subnet, dns)) {  // configure wifi
    Serial.println("STA Failed to configure");
  }

  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  delay(1000);
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());
  delay(100);
  
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler  
  client.onMessage(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(WiFi.status());
    Serial.print(".");
    delay(500);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["time"] = millis();
  doc["sensor_a0"] = analogRead(0);
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

// print incoming messages to serial monitor
void messageHandler(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

//  StaticJsonDocument<200> doc;
//  deserializeJson(doc, payload);
//  const char* message = doc["message"];
}

void setup() {
  Serial.begin(9600);
  connectAWS();
}

void loop() {
  if(client.connected()) {
      publishMessage(); // send a test message
  }
  Serial.println(WiFi.status()); // check if wifi is still connected(3)
  client.loop();
  delay(5000);
}
