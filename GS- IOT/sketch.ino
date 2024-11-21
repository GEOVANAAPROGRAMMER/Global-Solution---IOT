#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Wokwi-GUEST";
const char *password = "";
const char *mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
const char *mqtt_topic = "esp32/projetoIOT";

WiFiClient espClient;
PubSubClient client(espClient);

// Pinos e variáveis
const int sensorPin = 4;
const int pinoLampada = 2;
const int pinoTemp = 34; // Sensor de temperatura (analógico)
const int pinoArCondicionadoBaixo = 27;
const int pinoArCondicionadoMedio = 26;
const int pinoArCondicionadoAlto = 25;

bool sensorAtivado = false;

// Constantes do termistor
const float R0 = 10000;      // Resistência de referência
const float T0_ref = 298.15; // 25ºC em Kelvin
const float B = 3950;        // Constante beta do termistor

// Limite para tentativas de reconexão
int maxReconnectAttempts = 5;
int reconnectAttempts = 0;

// Prototipagem das funções
void callback(char *topic, byte *payload, unsigned int length);
void setup();
void loop();
void reconnectMQTT();
float calcularTemperatura();
void controlarArCondicionadoPorTemperatura(float temp);
void desligarArCondicionado();

void callback(char *topic, byte *payload, unsigned int length)
{
  String message = "";
  for (int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }

  if (String(topic) == "iot/ativar_sensor")
  {
    sensorAtivado = (message == "ON");
    if (sensorAtivado)
    {
      Serial.println("Sensor PIR ativado!");
    }
    else
    {
      digitalWrite(pinoLampada, LOW);
      desligarArCondicionado();
      Serial.println("Sensor PIR desativado!");
    }
  }

  if (String(topic) == "iot/configurar_temperatura")
  {
    int celsius = message.toInt();
    controlarArCondicionadoPorTemperatura(celsius);
    Serial.printf("Temperatura configurada: %d°C\n", celsius);
  }
}

void setup()
{
  Serial.begin(115200);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");

  // Configuração MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // Configuração de pinos
  pinMode(pinoTemp, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(pinoLampada, OUTPUT);
  pinMode(pinoArCondicionadoBaixo, OUTPUT);
  pinMode(pinoArCondicionadoMedio, OUTPUT);
  pinMode(pinoArCondicionadoAlto, OUTPUT);

  desligarArCondicionado();
}

void loop()
{
  if (!client.connected())
  {
    reconnectMQTT();
  }
  client.loop();

  if (sensorAtivado)
  {
    int pirState = digitalRead(sensorPin);
    float temperatura = calcularTemperatura();

    if (pirState == HIGH)
    {
      digitalWrite(pinoLampada, HIGH);
      controlarArCondicionadoPorTemperatura(temperatura);
      client.publish("iot/temperatura", String(temperatura, 2).c_str());
      client.publish("iot/movimento", "1");
      Serial.println("Movimento detectado!");
    }
    else
    {
      digitalWrite(pinoLampada, LOW);
      desligarArCondicionado();
      client.publish("iot/movimento", "0");
      Serial.println("Nenhum movimento.");
    }
  }
  delay(500);
}

void reconnectMQTT()
{
  while (!client.connected())
  {
    if (client.connect("ESP32Client"))
    {
      client.subscribe("iot/ativar_sensor");
      client.subscribe("iot/configurar_temperatura");
      reconnectAttempts = 0; // Reinicia contagem em caso de sucesso
      Serial.println("Conexão MQTT estabelecida com sucesso!"); // Mensagem de sucesso
    }
    else
    {
      reconnectAttempts++;
      if (reconnectAttempts > maxReconnectAttempts)
      {
        ESP.restart(); // Reinicia após muitas tentativas
      }
      delay(2000);
    }
  }
}

float calcularTemperatura()
{
  int leituraAnalogica = analogRead(pinoTemp);
  float Vout = leituraAnalogica * (3.3 / 4095.0);
  if (Vout < 0.01 || leituraAnalogica < 0 || leituraAnalogica > 4095)
    return -273.15; // Prevenir erros
  float Rt = (R0 * (3.3 - Vout)) / Vout;
  float temperaturaKelvin = B / (log(Rt / R0) + (B / T0_ref));
  return temperaturaKelvin - 273.15;
}

void controlarArCondicionadoPorTemperatura(float temp)
{
  desligarArCondicionado();
  if (temp <= 20)
  {
    digitalWrite(pinoArCondicionadoBaixo, HIGH);
  }
  else if (temp <= 30)
  {
    digitalWrite(pinoArCondicionadoMedio, HIGH);
  }
  else
  {
    digitalWrite(pinoArCondicionadoAlto, HIGH);
  }
}

void desligarArCondicionado()
{
  digitalWrite(pinoArCondicionadoBaixo, LOW);
  digitalWrite(pinoArCondicionadoMedio, LOW);
  digitalWrite(pinoArCondicionadoAlto, LOW);
}
