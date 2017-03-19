#include <Servo.h>
unsigned long previousMillis = 0;
const long interval = 5000;
uint8_t sure = 10,sagbutonpin = 33, solbutonpin = 31,servopin=2;
Servo myservo;  // myservo nesnesini oluştur

int pos = 90;    // açı başlangıç değeri 90 derece ortada başla

void setup() {
  pinMode(sagbutonpin,INPUT_PULLUP); // sag döndürme butonu giriş olarak ayarlandı
  pinMode(solbutonpin,INPUT_PULLUP); // sola döndürme butonu giriş olarka ayarlandı
  myservo.attach(servopin);  //motor servopin numaralı pine atandı
  myservo.write(pos); // servo başlangıç değeri 90 derece uygulandı
  
}

void loop() {
  if((digitalRead(sagbutonpin) == LOW)) { // butona basıldı ise sagadöndür
    pos++; // dereceyi arttır saga dönüş
    if(pos > 180) pos = 180; // decere 180 den daha fazla olamaz dereceyi 180 de tut üstüne çıkarma
    myservo.write(pos); // arttırılan dereceyi yaz
    delay(sure); // her adım arası sure kadar geçikme yarat
  }
 if((digitalRead(solbutonpin) == LOW)) { // butona basıldı ise soladöndür
    pos--; // dereceyi azalt sola dönüş
    if(pos < 0) pos = 0; // decere 0 dan daha düşük olamaz dereceyi 0 da tut altına düşürme
    myservo.write(pos); // arttırılan dereceyi yaz
    delay(sure); // her adım arası sure kadar geçikme yarat
       
  }
  
}

