void setup() {
  // Configura a comunicação serial (bit a bit) entre o MCU e o computador, que é realizada através da conexão USB neste exemplo 
  // Para tanto, é necessário especificar a baud rate, isto é, a taxa na qual os bits serão transferidos por segundo 
  // Neste exemplo, iremos escolher uma baud rate intermediária de 115.200 bit/s 
  
  Serial.begin(115200);
}

void loop() {
  // O MCU irá enviar a mensagem "hello world" em intervalos de 2 segundos (2000 milisegundos)
  
  Serial.println("Hello World");
  delay(2000);
}
