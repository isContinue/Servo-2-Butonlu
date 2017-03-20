#include <Servo.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
//void aciyaz(uint8_t);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);

uint8_t sure = 15, servopin=22, sagbutonpin = 31, solbutonpin = 33;
uint8_t simdikipos=90,oncekipos=0;
Servo myservo;  // myservo nesnesini oluştur

int pos = 90;    // açı başlangıç değeri 90 derece ortada başla

void setup() {
  tft.reset();

  uint16_t identifier = tft.readID();

  pinMode(sagbutonpin,INPUT_PULLUP); // sag döndürme butonu giriş olarak ayarlandı
  pinMode(solbutonpin,INPUT_PULLUP); // sola döndürme butonu giriş olarka ayarlandı
  myservo.attach(servopin);  //motor servopin numaralı pine atandı
  myservo.write(pos); // servo başlangıç değeri 90 derece uygulandı
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setCursor(48,88);
  tft.setTextSize(4);
  tft.print("Derece");
  tft.setCursor(66,144);
  tft.setTextSize(6);
  tft.print(180-pos);
  tft.setCursor(43,168);
  tft.setTextSize(2);
  tft.print("");      
}

void loop() {
 while((digitalRead(solbutonpin) == LOW)) { // butona basıldı ise soladöndür
    if(pos >= 180) {pos = 180; break;}
  tft.setCursor(12,216);    
  tft.setTextSize(2);
  tft.fillRect(189, 144, 38, 49, BLACK); // x baslangıc, y baslangıc, genişlik, yükseklik, renk
  tft.fillRect(12, 216, 216, 16, BLACK);
  tft.fillTriangle(51, 192, 51, 144, 15, 168, WHITE);
  tft.print("Motor Sola Donuyor");
      for(pos;pos<=180;pos++){
        myservo.write(pos);
        tft.setCursor(66,144);
        tft.setTextSize(6);
        tft.fillRect(66, 144, 108, 48, BLACK); // x baslangıc, y baslangıcı, genişlik, yükseklik, renk
        tft.print(180-pos);
        if (digitalRead(solbutonpin) == HIGH) break;
        delay(sure);
    }
    if(pos >= 180) {pos = 180; break;} 
  }

  
 while((digitalRead(sagbutonpin) == LOW)) { // butona basıldı ise sagaadöndür
  if(pos <= 0) {pos = 0; break;}
  tft.setCursor(12,216);    
  tft.setTextSize(2);
  tft.fillRect(12, 216, 216, 16, BLACK);
  tft.fillRect(15, 144, 38, 49, BLACK);
  tft.print("Motor Saga Donuyor");
  tft.fillTriangle(189, 192, 189, 144, 225, 168, WHITE);
      for(pos;pos>=0;pos--){
        myservo.write(pos);
        tft.setCursor(66,144);
        tft.setTextSize(6);
        tft.fillRect(66, 144, 108, 48, BLACK); // x baslangıc, y baslangıcı, genişlik, yükseklik, renk
        tft.print(180-pos);
        if (digitalRead(sagbutonpin) == HIGH) break;
        delay(sure);
    }
    if(pos <= 0) {pos = 0; break;} 
  }
 simdikipos = pos;
if ((simdikipos != oncekipos)/*||((digitalRead(sagbutonpin) == HIGH) && (digitalRead(solbutonpin) == HIGH))*/) {
  oncekipos = simdikipos;
  tft.setCursor(42,216);    
  tft.setTextSize(2);
  tft.fillRect(189, 144, 38, 49, BLACK);
  tft.fillRect(15, 144, 38, 49, BLACK);
  tft.fillRect(12, 216, 216, 16, BLACK);
  tft.print("Motor Duruyor");
  while(1){
    if (digitalRead(solbutonpin) == LOW) break;
    if (digitalRead(sagbutonpin) == LOW) break;
    }
}

}
 /* while((digitalRead(solbutonpin) == LOW)) { // butona basıldı ise soladöndür
    pos++; // dereceyi arttır saga dönüş
    if(pos > 180) {pos = 180; break;} // decere 180 den daha fazla olamaz dereceyi 180 de tut üstüne çıkarma
    myservo.write(pos); // arttırılan dereceyi yaz
  //tft.fillScreen(BLACK);
  //tft.setCursor(48,88);
  //tft.setTextSize(4);
  //tft.print("Derece");
  tft.setCursor(66,144);
  tft.setTextSize(6);
  tft.fillRect(66, 144, 144, 48, BLACK);
  tft.print(180-pos);
  tft.setCursor(12,216);
  tft.setTextSize(2);
  tft.fillRect(96, 216, 24, 16, BLACK);
  tft.print("Motor Sola Donuyor"); 
  //delay(sure); // her adım arası sure kadar geçikme yarat
  }

  
 while((digitalRead(sagbutonpin) == LOW)) { // butona basıldı ise sagaadöndür
    if(pos <= 0) {pos = 0; break;}
    pos--; // dereceyi azalt sola dönüş
    if(pos < 0) {pos = 0; break;} // decere 0 dan daha düşük olamaz dereceyi 0 da tut altına düşürme
    myservo.write(pos); // arttırılan dereceyi yaz
  //tft.fillScreen(BLACK);
  //tft.setCursor(48,88);
  //tft.setTextSize(4);
  //tft.print("Derece");
  tft.setCursor(66,144);
  tft.setTextSize(6);
  tft.fillRect(66, 144, 144, 48, BLACK); // x baslangıc, y baslangıcı, genişlik, yükseklik, renk
  tft.print(180-pos);
  tft.setCursor(12,216);
  tft.setTextSize(2);
  tft.fillRect(96, 216, 24, 16, BLACK);
  tft.print("Motor Saga Donuyor");  
  //delay(sure); // her adım arası sure kadar geçikme yarat
 }
  */
  
/*
 * void aciyaz(uint8_t deger){
  tft.fillScreen(BLACK);
  tft.setCursor(50,100);
  tft.print("ACI = ");
  tft.print(180-deger);
}
*/
