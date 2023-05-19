#include<WiFi.h> // Inclui biblioteca que dá acesso aos recursos de rede

char *ssid = "NOME_DA_REDE_WIFI_AQUI"; // Nome da rede WiFi 
char *password = "SENHA_DA_REDE_WIFI_AQUI"; // Senha de autenticação

void setup_wifi(){
  // Inicia a conexão com a rede desejada
  WiFi.begin(ssid, password);

  Serial.print("Conectando.");

  while(WiFi.status() != WL_CONNECTED){
    // Enquanto o MCU não estiver conectado, exiba um ponto a cada meio segundo
    Serial.print(".");
    delay(500);
  }

  //Uma vez concetado, exibe o endereço IP do MCU
  Serial.println("Conectado com sucesso!!!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
}

void loop() {
  
}
