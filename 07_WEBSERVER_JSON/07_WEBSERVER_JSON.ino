#include <WiFi.h>
#include <WebServer.h>
#include <FreeRTOS.h>
#include <ArduinoJson.h>
#include "DHT.h"

char *ssid = "NOME_DA_REDE_WIFI_AQUI"; // Nome da rede WiFi 
char *password = "SENHA_DA_REDE_WIFI_AQUI"; // Senha de autenticação

float temperatura;
float umidade;

StaticJsonDocument<300> doc;
char buffer[300];

//char float_buffer[25];

DHT dht(14, DHT22);
WebServer server(80);

void create_json(char * type, float value,  char * unit ){
  doc.clear();
  doc["type"] = type;
  doc["value"] = value;
  doc["unit"] = unit;
  serializeJson(doc, buffer);
}

void setup_wifi(){
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); 
}

void setup_routes(){
  server.on("/hello_world", get_hello_world);
  server.on("/temperatura", get_temperatura);
  server.on("/umidade", get_umidade);

  server.begin();
} 

void get_hello_world(){
   server.send(200, "text/plain", "Hello World");
}

void get_temperatura(){
  create_json("temperatura", temperatura, "ºC");
  //create_json("temperatura", dtostrf(temperatura, 10, 2, float_buffer), "ºC");
  server.send(200, "application/json", buffer);
  //server.send(200,"text/plain", String(temperatura)); 
}

void get_umidade(){
  create_json("umidade", umidade, "%");
  //create_json("umidade", dtostrf(umidade, 10, 2, float_buffer), "%");
  server.send(200, "application/json", buffer);
  //server.send(200, "text/plain", String(umidade));  
}

void read_sensor(void * parameters){
  for(;;){
    temperatura = dht.readTemperature();
    umidade = dht.readHumidity();

    // 30 segundos 
    vTaskDelay(5000 /  portTICK_PERIOD_MS );
  }
}

void setup_task(){
  xTaskCreate(
    read_sensor, 
    "read_sensor",
    1000, 
    NULL, 
    1,
    NULL
  );
}

void setup(){
  Serial.begin(115200);
  setup_wifi();
  setup_routes();
  setup_task();
  dht.begin();
}

void loop(){
  server.handleClient();
  
  //temperatura = dht.readTemperature();
  //umidade = dht.readHumidity();

  //Serial.print("Temperatura: ");
  //Serial.println(temperatura);
  //Serial.print("Umidade: ");
  //Serial.println(umidade);
  //delay(2000);
}