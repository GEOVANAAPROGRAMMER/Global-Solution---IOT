#include <OneWire.h>
#include <DallasTemperature.h>

// Variáveis e Pinos
float celsius = 0;                // Temperatura
bool sensorAtivado = true;        // Flag para ativar/desativar o PIR

const int pinoLampada = 2;        // Pino do LED para lâmpada
const int sensorPin = 4;          // Pino do sensor PIR

// Pinos para os LEDs do ar-condicionado
const int pinoArCondicionadoBaixo = 10;
const int pinoArCondicionadoMedio = 9;
const int pinoArCondicionadoAlto = 8;

const int pinoTempSensor = A0;    // Pino do sensor de temperatura DS18B20

OneWire oneWire(pinoTempSensor);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);

  // Configuração dos pinos
  pinMode(sensorPin, OUTPUT);     // Saída para simulação do sensor PIR
  pinMode(pinoLampada, OUTPUT);   // Saída para a lâmpada
  pinMode(pinoArCondicionadoBaixo, OUTPUT); // LED para temperatura baixa
  pinMode(pinoArCondicionadoMedio, OUTPUT); // LED para temperatura média
  pinMode(pinoArCondicionadoAlto, OUTPUT);  // LED para temperatura alta

  // Inicializa todos os LEDs desligados
  desligarArCondicionado();
  digitalWrite(pinoLampada, LOW);

  sensors.begin(); // Inicializa o sensor de temperatura

  Serial.println("Sistema iniciado!");
}

void loop() {
  if (sensorAtivado) {
    // Simular movimento
    digitalWrite(sensorPin, HIGH);
    delay(1000); // Simula movimento por 1 segundo

    // Leitura da temperatura
    sensors.requestTemperatures();
    celsius = sensors.getTempCByIndex(0);

    if (celsius == DEVICE_DISCONNECTED_C) {
      Serial.println("Erro: Sensor de temperatura desconectado!");
    } else {
      digitalWrite(pinoLampada, HIGH); // Liga a lâmpada
      controlarArCondicionadoPorTemperatura(celsius);

      // Feedback no console serial
      Serial.print("Movimento detectado! Temperatura: ");
      Serial.print(celsius);
      Serial.println(" °C");
    }

    // Simular ausência de movimento
    digitalWrite(sensorPin, LOW);
    delay(6000); // Simula ausência de movimento por 6 segundos

    digitalWrite(pinoLampada, LOW); // Desliga a lâmpada
    desligarArCondicionado();
    Serial.println("Nenhum movimento detectado.");
  } else {
    Serial.println("Sensor PIR desativado. Aguardando comando...");
  }

  delay(10000); // Atraso de 10 segundos
}

// Função para controlar os LEDs do ar-condicionado com base na temperatura
void controlarArCondicionadoPorTemperatura(float temp) {
  desligarArCondicionado(); // Desliga todos os LEDs antes de acender o correto

  if (temp <= 20) {
    digitalWrite(pinoArCondicionadoBaixo, HIGH);
    Serial.println("Ar-condicionado: Aumentar temperatura");
  } else if (temp > 20 && temp <= 30) {
    digitalWrite(pinoArCondicionadoMedio, HIGH);
    Serial.println("Ar-condicionado: Temperatura média");
  } else {
    digitalWrite(pinoArCondicionadoAlto, HIGH);
    Serial.println("Ar-condicionado: Abaixar temperatura");
  }
}

// Função para desligar todos os LEDs do ar-condicionado
void desligarArCondicionado() {
  digitalWrite(pinoArCondicionadoBaixo, LOW);
  digitalWrite(pinoArCondicionadoMedio, LOW);
  digitalWrite(pinoArCondicionadoAlto, LOW);
}
