#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// ----------- WiFi ------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ----------- ThingSpeak MQTT ------------
const char* mqtt_server = "mqtt3.thingspeak.com";
const int mqtt_port = 1883;

// Credenciais do ThingSpeak 
const char* channel_id = "2982369";
const char* client_id = "CRAALDYfCxUIOi8gOAAiMDI";
const char* mqtt_username = "CRAALDYfCxUIOi8gOAAiMDI";
const char* mqtt_password = "bYu5jiSzzwqQjpIYCKcEkjkr";

String topic = "channels/" + String(channel_id) + "/publish";

WiFiClient espClient;
PubSubClient MQTT(espClient);

// ----------- Sensor DHT22 ------------
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ----------- LEDs ------------
const int ledVerde = 2;
const int ledVermelho = 4;

// ----------- Conexão MQTT ------------
void conectaMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Conectando ao MQTT... ");
    if (MQTT.connect(client_id, mqtt_username, mqtt_password)) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha. Código: ");
      Serial.println(MQTT.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  dht.begin();

  Serial.print("Conectando ao WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  
  MQTT.setServer(mqtt_server, mqtt_port);
  conectaMQTT();
}

void loop() {
 
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }

  if (!MQTT.connected()) {
    conectaMQTT();
  }

  MQTT.loop();

  
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Falha na leitura do DHT!");
    delay(5000);
    return;
  }

  if (temp >= 35.0) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, HIGH);
    Serial.println("Temperatura PERIGOSA");
  } else {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
    Serial.println("Temperatura OK");
  }

  // Montar e enviar payload MQTT
  String payload = "field1=" + String(temp);
  Serial.print("Enviando para o tópico: ");
  Serial.println(topic);
  Serial.print("Payload: ");
  Serial.println(payload);

  boolean enviado = MQTT.publish(topic.c_str(), payload.c_str());

  if (enviado) {
    Serial.println("Temperatura enviada ao ThingSpeak via MQTT!");
  } else {
    Serial.println("Falha ao enviar via MQTT.");
  }

  delay(20000); 
}
