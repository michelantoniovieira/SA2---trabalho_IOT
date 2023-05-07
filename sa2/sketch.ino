#include <DHT.h>
#include <ThingSpeak.h>
#include <WiFi.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

int buzzerPin = 23;//ok
int ledVerde = 18;
int ledAzul = 5;
int relayPin = 2;
int ledAmarelo = 22;

// Definir suas credenciais Wi-Fi e informações do ThingSpeak
char* ssid = "Wokwi-GUEST";
char* password = "";
char* apiKey = "TP65HJZ6EYDKFIL2";
unsigned long channelNumber = 2;

// Inicializar o objeto WiFiClient
WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  dht.begin();

  
    // Conectar-se à rede Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Conectando à rede Wi-Fi...");
    }
  

  // Inicializar o ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("C - Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  // Enviar os dados de temperatura e umidade para o ThingSpeak
  ThingSpeak.writeField(channelNumber, 1, temperatura, apiKey);
  ThingSpeak.writeField(channelNumber, 2, umidade, apiKey);


  if (temperatura > 35) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledAmarelo, HIGH);
  } else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(relayPin, LOW);
    digitalWrite(ledAmarelo, LOW);
  }

  if (umidade > 70) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledAzul, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledAzul, LOW);
  }

  delay(5000);
}
