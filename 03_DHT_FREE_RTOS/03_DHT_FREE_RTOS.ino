#include<DHT.h> // Inclui a biblioteca do sensor
#include<FreeRTOS.h> // Inclui biblioteca por meio da qual é possível criar tarefas em paralelo

// Instância o objeto responsável por realizar a leitura da temperatura e da umidade
DHT dht(14, DHT22);

// Define as variáveis ponto flutuantes que armazenarão a temperatura e a umidade respectivamente
float temperatura;
float umidade;

void blink_led(void *parameter){
  // Função responsável por ligar e desliar o LED a cada meio segundo
  for(;;){
    digitalWrite(12, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(12, LOW);
    vTaskDealy(500 / portTICK_PERIOD_MS);
  }
}

void read_sensor(void * parameters){
  // Função responsável pela leitura de temperatura e umidade

  for(;;){
      // Loop infinito

      //Realiza a leitura da temperatura e da umidade respectivamente em intervalos de 2 segundos
      temperatura = dht.readTemperature();
      umidade = dht.readHumidity();

      // Exibe os dados coletados através da comunicação serial
      Serial.print("Temperatura: ");
      Serial.println(temperatura);
      Serial.print("Umidade: ");
      Serial.println(umidade);

      // Adiciona delay de 2 segundos 
      // Esse delay não bloqueia a CPU
      // The actual time that the task remains blocked depends on the tick rate. 
      // The constant portTICK_PERIOD_MS can be used to calculate real time from the tick rate - with the resolution of one tick period.
      vTaskDelay(2000 / portTICK_PERIOD_MS);
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

void setup() {
  Serial.begin(115200);
  
  pinMode(12, OUTPUT);
  // Inicia a leitura 
  dht.begin(); 
  setup_task();
}

void loop() {

}
