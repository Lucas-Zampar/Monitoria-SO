#include<WiFi.h> // Inclui biblioteca que dá acesso aos recursos da rede WiFi
#include<WebServer.h> // Inclui a biblioteca do servidor Web
#include<FreeRTOS.h> // Inclui biblioteca por meio da qual podemos configurar tarefas do SO 
#include<DHT.h>

char *ssid = "NOME_DA_REDE_WIFI_AQUI"; // Nome da rede WiFi 
char *password = "SENHA_DA_REDE_WIFI_AQUI"; // Senha de autenticação

// Instância do servidor Web. Deve ser fornecido a porta na qual ele vai operar.
WebServer server(80);

// Instância o objeto responsável por realizar a leitura da temperatura e da umidade
DHT dht(14, DHT22);

// Declara variáveis responsáveis por armazenar os valores de temperatura e umidad 
float temperatura;
float umidade;

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

void read_sensor(void * parameters){
  // Essa função precisa ter um argumento especificado 

  for(;;){
    // Inicia um laço infinito 
    // Atualiza as variáveis globais a cada 2 segundos

    temperatura = dht.readTemperature(); 
    umidade = dht.readHumidity();

    Serial.print("Temperatura: ");
    Serial.println(temperatura);
    Serial.print("Umidade: ");
    Serial.println(umidade);

    vTaskDelay(2000 / portTICK_PERIOD_MS );  
  }
}

void blink_led(void *parameters){
  for(;;){
    digitalWrite(12, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(12, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup_task(){
  xTaskCreate(
    read_sensor, // Nome da função que será executada em paralelo 
    "read_sensor", 
    1024, // define o tamanho da pilha reservada para a tarefa
    NULL, // parâmetros repassados para a função, no caso não será repassado 
    2, // prioridade da tarefa
    NULL // Se haverá um handler para a tarefa 
  );

  xTaskCreate(
    blink_led, // Nome da função que será executada em paralelo 
    "blink_led", 
    1024, // define o tamanho da pilha reservada para a tarefa
    NULL, // parâmetros repassados para a função, no caso não será repassado 
    1, // prioridade da tarefa
    NULL // Se haverá um handler para a tarefa 
  );
}


void setup_routes(){
  //Configura a rota hello_world do servidor Web
  server.on("/hello_world", send_hello_world);

  // Configura a rota que dá acesso aos dados do ambiente
  server.on("/data", send_data);

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

void send_data(){
  // Define uma string referente ao HTML da página que exibirá os dados do sensor
  String html = "<html><body>";
  html += "<h1> Dados do Ambiente </h1>";
  html += "<p> Temperatura : ";
  html += temperatura; 
  html += "</p>";
  html += "<p> Umidade: ";
  html += umidade;
  html += "</p></body></html>";

  // Envia o HTML. Deve ser fornecido também o código de status HTTP (200 para sucesso), bem como o tipo de conteúdo.
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  pinMode(12, OUTPUT);

  dht.begin();
  
  setup_wifi();
  setup_task();
  setup_routes();
}

void loop() {
  // Lida com as requisições dos clientes. 
  server.handleClient();
}
