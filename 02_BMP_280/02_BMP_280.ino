//SCL porta 22 (clock)
//SDA porta 21 (transmissão)

#include<Adafruit_BMP280.h> // Inclui biblioteca do sensor

// Instância do objeto responsável pela leitura de temperatura e pressão 
Adafruit_BMP280 bmp;

// Declara as variáveis que irão armazenar os valores de temperatura e pressão respectivamente
float temperatura;
float pressao;

void setup() {
  Serial.begin(115200);

  // Inicia as leituras, para tanto é necessário especificar o endereço I2C que o sensor irá empregar
  bmp.begin(0x76);
}

void loop() {
  // Realiza a leitura de temperatura e pressão em intervalos de 2 segundos
  temperatura = bmp.readTemperature(); 
  pressao = bmp.readPressure(); 

  // Exibe os dados coletados a partir da comunicação serial
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Pressao: ");
  Serial.println(pressao);

  delay(2000);
}
