#include <LiquidCrystal.h>
const int rs = 8; // lcd den komut veya data girisi 0 ise komut 1 ise data
const int en = 7; // izin sinyali
const int d4 = 3; // VO ekranın konstrat ayarı pot ile
const int d5 = 4; // rw read or write 0 ise write 1 ise read
const int d6 = 5; // A K anot katot ayarı anota 3.3 volt veya 5 volt ise 220 ohm direnc
const int d7 = 6; // vss toprak vdd artı hatta bagla
const int trig = 9;
const int echo = 10;
const int buton1 = 11;
const int buton2 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //(rs,rw,e,d0...d7)var ise
float  hesapla() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(50);
  float sure = pulseIn(echo, HIGH);
  float mesafe = (sure / 2) / 29.1;
  return mesafe;
}
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  lcd.begin(16, 2);
  lcd.print("Merhaba");
  delay(1000);
  lcd.home();
  lcd.println("Buton1 e basınız");
  Serial.begin(9600);
}


typedef enum
{
  START_STATE = 0x00,
  CALIBRATION_STATE = 0x01,
  MEASUREMENT_STATE = 0x02,

} state_table;

state_table state = START_STATE;
float calibration_val = 0;

void loop() {

  
  switch (state)
  {
    case START_STATE :
      if (digitalRead(buton1))
      {
        state = CALIBRATION_STATE;
        delay(100);
      }
      Serial.println(state);
      while(digitalRead(buton1));
    case CALIBRATION_STATE :
      calibration_val = hesapla();
      
      Serial.println(calibration_val);
      Serial.println(state);
      while(digitalRead(buton1));
      state = MEASUREMENT_STATE;
      delay(100);
    case MEASUREMENT_STATE :
      if (digitalRead(buton1))
      {
        float current_val = hesapla();
        float diff = calibration_val - current_val;
        Serial.println(diff);
        Serial.println(state);
        while(digitalRead(buton1));
        state = START_STATE;
               
      }
      
  }
}
