void setup() {
  
  // configura a porta 12 na qua o led está conectado como sendo de saída
  // desa forma, o MCU poderá enviar o sinal para ligar e desligar o LED através dela 
  pinMode(12, OUTPUT);

  // configura a interface serial
  Serial.begin(115200);

}

void loop() {
  // o led ficará ligado por meio segundo 
  digitalWrite(12, HIGH);
  delay(500);

  // o led ficará desligado por meio segundo
  digitalWrite(12, HIGH);  
  delay(500);
}
