/*
  ==         MONITOR DE UMIDADE DO SOLO        ==
  ===============================================
  == BLOG DA ROBOTICA - www.blogdarobotica.com ==
  ===============================================
  Autor: Carol Correia
  E-mail: contato@blogdarobotica.com
  Facebook: facebook.com/blogdarobotica
  Instagram:@blogdarobotica
  YouTube: youtube.com/user/blogdarobotica
  ===============================================
  == CASA DA ROBOTICA - www.casadarobotica.com ==
  ===============================================
  Facebook: facebook.com/casadaroboticaoficial
  Instagram:@casadarobotica
  ===============================================
*/

#define umidadeAnalogica A0 //Atribui o pino A0 a variável umidade - leitura analógica do sensor
#define umidadeDigital 7 //Atribui o pino 7 a variável umidadeDigital - leitura digital do sensor
#define LedVermelho 5 //Atribui o pino 7 a variável LedVermelho
#define LedVerde 6 //Atribui o pino 6 a variável LedVerde

int valorumidade; //Declaração da variável que armazenará o valor da umidade lida - saída analogica
int valorumidadeDigital; //Declaração da variável que armazenara a saída digital do sensor de umidade do solo

void setup() {
  Serial.begin(9600); //Incia a comunicação serial
  pinMode(umidadeAnalogica, INPUT); //Define umidadeAnalogica como entrada
  pinMode(umidadeDigital, INPUT); //Define umidadeDigital como entrada
  pinMode(LedVermelho, OUTPUT); //Define LedVermelho como saída
  pinMode(LedVerde, OUTPUT); //Define LedVerde como saída
}

void loop() {
  valorumidade = analogRead(umidadeAnalogica); //Realiza a leitura analógica do sensor e armazena em valorumidade
  valorumidade = map(valorumidade, 1023, 315, 0, 100); //Transforma os valores analógicos em uma escala de 0 a 100
  Serial.print("Umidade encontrada: "); //Imprime mensagem
  Serial.print(valorumidade); //Imprime no monitor serial o valor de umidade em porcentagem
  Serial.println(" % " );

  valorumidadeDigital = digitalRead(umidadeDigital); //Realiza a leitura digital do sensor e armazena em valorumidadeDigital
  if (valorumidade < 50) { //Se esse valor for igual a 0, será mostrado no monitor serial que o solo está úmido e o led verde se acende
    Serial.println("Status: Solo seco");
    digitalWrite(LedVermelho, HIGH);
    digitalWrite(LedVerde, LOW);
  }
  else { // se esse valor for igual a 1, será mostrado no monitor serial que o solo está seco e o led vermelho se acende
    Serial.println("Status: Solo úmido");
    digitalWrite(LedVermelho, LOW);
    digitalWrite(LedVerde, HIGH);
  }
  delay(500); //Atraso de 500ms
}