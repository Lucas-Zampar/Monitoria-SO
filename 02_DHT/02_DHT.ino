#include "DHT.h" // Inclui a biblioteca do sensor

// Instância o objeto responsável por realizar a leitura da temperatura e da umidade
DHT dht(14, DHT22);

// Define as variáveis ponto flutuantes que armazenarão a temperatura e a umidade respectivamente
float temperatura;
float umidade;

void setup() {
  Serial.begin(115200);
  
  // Inicia a leitura 
  dht.begin(); 
}

void loop() {
  //Realiza a leitura da temperatura e da umidade respectivamente em intervalos de 2 segundos
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  
  // Exibe os dados coletados através da comunicação serial
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Umidade: ");
  Serial.println(umidade);

  delay(2000);
}
