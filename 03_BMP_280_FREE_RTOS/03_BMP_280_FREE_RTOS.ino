#include<Adafruit_BMP280.h> // Inclui biblioteca do sensor

// Instância do objeto responsável pela leitura de temperatura e pressão 
Adafruit_BMP280 bmp;

// Declara as variáveis que irão armazenar os valores de temperatura e pressão respectivamente
float temperatura;
float pressao;


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
  // Função responsável pela leitura de temperatura e pressão

  for(;;){
      // Loop infinito

      // Realiza a leitura de temperatura e pressão em intervalos de 2 segundos
      temperatura = bmp.readTemperature(); 
      pressao = bmp.readPressure(); 

      // Exibe os dados coletados a partir da comunicação serial
      Serial.print("Temperatura: ");
      Serial.println(temperatura);
      Serial.print("Pressao: ");
      Serial.println(pressao);

      // Adiciona delay de 2 segundos 
      // Esse delay não bloqueia a CPU
      vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void setup_task(){
  xTaskCreate(
    read_sensor, // Nome da função que será executada em paralelo 
    "read_sensor", 
    1024, // define o tamanho da pilha reservada para a tarefa
    NULL, // parâmetros repassados para a função, no caso não será repassado 
    1, // prioridade da tarefa
    NULL // Se haverá um handler para a tarefa 
  );

  xTaskCreate(
    blink_led, // Nome da função que será executada em paralelo 
    "blink_led", // define o tamanho da pilha reservada para a tarefa
    1024, // parâmetros repassados para a função, no caso não será repassado 
    NULL, 
    1, // prioridade da tarefa
    NULL // Se haverá um handler para a tarefa 
  );

}

void setup() {
  Serial.begin(115200);

  // Inicia as leituras, para tanto é necessário especificar o endereço I2C que o sensor irá empregar
  bmp.begin(0x76);
  setup_task();
}

void loop() {

}


