#include <Wire.h> // Biblioteca utilizada para comunicação I2C
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2                // pino que estamos conectado
#define DHTTYPE DHT22           // DHT 22  (AM2303)
#define umidadeAnalogica A0     // Pino de leitura analógica do sensor
#define umidadeDigital 3        // Pino de leitura digital do sensor
#define buzz 7                 // Pino do buzzer

#define addr 0x3F
#define colunas 16
#define linhas 2

#define MAX_TEMP 40
#define MIN_TEMP 15

#define MAX_UMID 60
#define MIN_UMID 10

#define BUZZ_ON false

//Variables
int valorUmidade;               // Valor da umidade analógica
int valorUmidadeDigital;        // Valor da umidade digital
float valorTempDigital;         // Valor da temperatura digital
bool flagTemp = false;          // Flag de ativação do buzzer
bool flagUmid = false;          // Flag de ativação do buzzer

LiquidCrystal_I2C lcd(addr, colunas, linhas);  // Endereço 0x3F, display 16x2
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);               // Inicia comunicação serial

  pinMode(umidadeAnalogica, INPUT);
  pinMode(umidadeDigital, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(buzz, OUTPUT);

  lcd.init();                       // Inicializa LCD
  lcd.backlight();                  // Liga o backlight
  lcd.clear();                      // Limpa o display

  dht.begin();
}

void loop() {
  valorUmidadeDigital = digitalRead(umidadeDigital); 
  valorUmidade = analogRead(umidadeAnalogica); 
  valorTempDigital = dht.readTemperature();

  // Mapeia a leitura para uma escala percentual (ajuste os valores conforme necessário)
  valorUmidade = (int)((map(valorUmidade, 1023, 315, 0, 100)));

  // Exibe no Serial Monitor
  Serial.print("Umidade do solo: ");
  Serial.print(valorUmidade);
  Serial.println(" %");
  Serial.print("\nTemperatura: ");
  Serial.print(valorTempDigital);
  Serial.println(" Celsius");

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);

  // Confere valor de umidade
  if (valorUmidade < MAX_UMID && valorUmidade > MIN_UMID) {
    Serial.println("Solo ideal");
    lcd.print("Solo ideal");
    flagUmid = false;
  } else {
    if (valorUmidade > MAX_UMID) {
      Serial.println("Solo molhado");
      lcd.print("Solo molhado");
    }else {
      Serial.println("Solo seco");
      lcd.print("Solo seco");  
    }
    flagUmid = true;
  }
  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(valorUmidade);
  lcd.print(" %");

  delay(5000);
  lcd.clear();                                    // Limpa o displa
  lcd.setCursor(0, 0);                     

  // Confere valor de temp
  if (valorTempDigital < MAX_TEMP && valorTempDigital > MIN_TEMP) {
    Serial.println("Temp ideal");
    lcd.print("Temp ideal");
    flagTemp = false;
  } else {
    if (valorTempDigital > MAX_TEMP) {
      Serial.println("Temp alta");
      lcd.print("Temp alta");
    }else {
      Serial.println("Temp baixa");
      lcd.print("temp baixa");  
    }
    flagTemp = true;
  }

  lcd.setCursor(0, 1);
  lcd.print(valorTempDigital);
  lcd.print(" Cels");
  Serial.println(valorTempDigital);  
  
  delay(5000);
  lcd.clear();                      // Limpa o display

  // ativa buzzer caso alguma flag esteja ativa
  if (BUZZ_ON){
    if (flagTemp || flagUmid){
      digitalWrite(buzz, HIGH);  
      Serial.println("Buzz on");  
    }else {
      digitalWrite(buzz, LOW); 
      Serial.println("Buzz off");
    }
  }
  

}
