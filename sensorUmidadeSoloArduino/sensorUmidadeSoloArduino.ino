#include <Wire.h> // Biblioteca utilizada para comunicação I2C
#include <LiquidCrystal_I2C.h>

#define umidadeAnalogica A0     // Pino de leitura analógica do sensor
#define umidadeDigital 7        // Pino de leitura digital do sensor
#define buzz 6                  // Pino do buzzer

#define addr 0x3F
#define colunas 16
#define linhas 2

int valorumidade;               // Valor da umidade analógica
int valorumidadeDigital;        // Valor da umidade digital

LiquidCrystal_I2C lcd(addr, colunas, linhas);  // Endereço 0x3F, display 16x2

void setup() {
  Serial.begin(9600);               // Inicia comunicação serial

  pinMode(umidadeAnalogica, INPUT);
  pinMode(umidadeDigital, INPUT);
  pinMode(buzz, OUTPUT);

  lcd.init();                       // Inicializa LCD
  lcd.backlight();                  // Liga o backlight
  lcd.clear();                      // Limpa o display
}

void loop() {
  valorumidadeDigital = digitalRead(umidadeDigital); 
  valorumidade = analogRead(umidadeAnalogica); 

  // Mapeia a leitura para uma escala percentual (ajuste os valores conforme necessário)
  valorumidade = (int)((map(valorumidade, 1023, 315, 0, 100)));

  // Exibe no Serial Monitor
  Serial.print("Umidade encontrada: ");
  Serial.print(valorumidade);
  Serial.println(" %");


  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);

  // digitalWrite(buzz, HIGH);
  if (valorumidade < 50) { // caso umidade seja abaixo de 50%
    Serial.println("Solo seco");
    lcd.print("Status: Solo seco");
    digitalWrite(buzz, HIGH);
  } else {
    Serial.println("Solo úmido");
    lcd.print("Status: Solo úmido");
    digitalWrite(buzz, LOW);
  }

  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");
  lcd.print(valorumidade);
  lcd.print(" %   ");
  delay(500);
  // lcd.setBacklight(LOW);
  // delay(500);
}
