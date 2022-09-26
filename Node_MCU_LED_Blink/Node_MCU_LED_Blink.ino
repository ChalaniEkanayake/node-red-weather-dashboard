#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "add_your_ssid";
const char* password = "add_your_password";

unsigned long previousMillis = 0;

boolean stateLow = false;
boolean stateMid1 = false;
boolean stateMid2 = false;
boolean stateHigh = false;

int ledState = HIGH;

const char* mqtt_server = "test.mosquitto.org";

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient espClient22;
PubSubClient client(espClient22);

//Connect NodeMCU to router
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - NodeMCU IP address: ");
  Serial.println(WiFi.localIP());
}

void blinkLoop(int del) {
  digitalWrite(LED_BUILTIN, ledState);   

  if (millis() >= del + previousMillis) {
    previousMillis = millis();

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(LED_BUILTIN, ledState);
  }
}

// This functions is executed when some device publishes a message to a topic that your NodeMCU is subscribed to
void callback(String topic, byte * message, unsigned int length) {
  Serial.print("\nMessage arrived on topic: ");
  Serial.print(topic);
  Serial.print(" with value of : ");
  String messageInfo;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageInfo += (char)message[i];
  }
  Serial.println();
  int warningVal = messageInfo.toInt();

  if (topic == "warning") {
    Serial.print("Warning received ");

    if (warningVal > 20) {
      Serial.println("Warning limit exceeded by more than 20 units, blink at 500ms");
      stateLow = false;
      stateMid1 = false;
      stateMid2 = false;
      stateHigh = true;
    }
    else if (warningVal > 15) {
      Serial.println("Warning limit exceeded by more than 15 units but less than 20 units, blink at 1s");
      stateLow = false;
      stateMid1 = false;
      stateMid2 = true;
      stateHigh = false;
    }
    else if (warningVal > 10) {
      Serial.println("Warning limit exceeded by more than 10 units but less than 15 units, blink at 2s");
      stateLow = false;
      stateMid1 = true;
      stateMid2 = false;
      stateHigh = false;
    }
    else if (warningVal < 10) {
      Serial.println("Warning limit exceeded by less than 10 units, blink at 5s");
      stateLow = true;
      stateMid1 = false;
      stateMid2 = false;
      stateHigh = false;
    }
  }
  Serial.println();
}

// reconnects your ESP8266 to your MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266Client22")) {
      Serial.println("connected");
      client.subscribe("warning");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// sets ESP GPIOs to Outputs, starts the serial communication at a baud rate of 9600
// Set  mqtt broker and set the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

//  ensures that the NodeMCU is connected to MQTT broker
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP8266Client22");

  if (stateLow == true) {
    blinkLoop(5000);
  }
  else if (stateMid1 == true) {
    blinkLoop(2000);
  }
  else if (stateMid2 == true) {
    blinkLoop(1000);
  }
  else if (stateHigh == true) {
    blinkLoop(500);
  }
}
