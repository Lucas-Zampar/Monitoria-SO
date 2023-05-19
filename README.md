# Monitoria: Sistemas Operacionais

Durante a monitoria, conduzi um projeto prático com os alunos de modo a explorar o conceito de concorrência através do sistema operacional FreeRTOS presente no microcontrolador ESP-32. Em tal projeto, duas tarefas deveriam ser criadas e executradas de forma concorrente, sendo elas:

- um led deveria ser ligado e desligado continumente a cada meio segundo;
- dados físicos de temperatura, umidade e pressão atmosférica deveriam ser lidos pelos sensores DHT-22 e BMP-280; 

Dessa forma, foi possível abordar também como sensores de baixo custo, como o DHT-22 e BMP-280, podem ser empregados para a leitura de dados físicos do ambiente em um contexto de IoT. Por fim, foi possível realizar uma demonstração de como esses dados podem ser acessados através de um webserver disponível em uma rede local. 
