#include<WiFi.h> // Inclui biblioteca que dá acesso aos recursos de rede
#include<WebServer.h> // Inclui a biblioteca do servidor Web

char *ssid = "NOME_DA_REDE_WIFI_AQUI"; // Nome da rede WiFi 
char *password = "SENHA_DA_REDE_WIFI_AQUI"; // Senha de autenticação

// Instância do servidor Web. Deve ser fornecido a porta na qual ele vai operar.
WebServer server(80);

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

void setup_routes(){
  //Configura a rota hello_world do servidor Web
  server.on("/hello_world", send_hello_world);

  // Incializa o servidor
  server.begin();
}

void send_hello_world(){
  // Define uma string contendo o HTML da página a ser exibida
  String html = "<html><body>";
  html += "<h1> Hello World </h1>";
  html += "<p> Isso eh um teste de rota! </p>";
  html += "</body></html>";

  // Envia o HTML. Deve ser fornecido também o código de status HTTP (200 para sucesso), bem como o tipo de conteúdo.
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  setup_routes();
}

void loop() {
  // Lida com as requisições dos clientes. 
  server.handleClient();
}
