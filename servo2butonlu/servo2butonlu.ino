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

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);

uint8_t sure = 15, servopin=22, sagbutonpin = 31, solbutonpin = 33; // her derece arası bekleme sure değeri(ms), Servo pin numarası, sag dödürme butonpin numarası, sola söndürme buton pin murası
uint8_t simdikipos=90,oncekipos=0; 
Servo myservo;  // myservo nesnesini oluştur

int pos = 90;    // açı başlangıç değeri 90 derece ortada başla

void setup() {
  tft.reset(); // tft yi resetle

  uint16_t identifier = tft.readID(); // tft idsini oku

  pinMode(sagbutonpin,INPUT_PULLUP); // sag döndürme butonu dahili pull-up giriş olarak ayarlandı
  pinMode(solbutonpin,INPUT_PULLUP); // sola döndürme butonu dahili pull-up giriş olarka ayarlandı
  myservo.attach(servopin);  //motor servopin numaralı pine atandı
  myservo.write(pos); // servo derece başlangıç pos değeri uygulandı
  tft.begin(identifier); // tft id den başlat
  tft.fillScreen(BLACK); // ekranı temizle
  tft.setTextColor(WHITE); // yazı rengi beyaz olarak seçildi
  tft.setCursor(48,88); // Imleci stringi yazdırmak için ortalanmış kordinata al
  tft.setTextSize(4); // puntoyu ayarla
  tft.print("Derece"); // stringi yaz
  tft.setCursor(66,144); //imleci 66,144 konumuna al
  tft.setTextSize(6);  // punto değerini 6 yap
  tft.print(180-pos); // ekrana dereceyi yazdır motor tutuş yönü ters olduğu için 180-pos
  tft.setCursor(43,168);
  tft.setTextSize(2);
  tft.print("");      
}

void loop() {
 
 while((digitalRead(solbutonpin) == LOW)) { // butona basıldı ise sola döndür
    if(pos >= 180) {pos = 180; break;} // derece 180den büyük ise döngüye girme.
  tft.setCursor(12,216); // imleci 12,216 kordinatına al gerekli punto için ortalanmış değerler   
  tft.setTextSize(2); // puntoyu 2 olarak ayarla
  tft.fillRect(189, 144, 38, 49, BLACK); // önceki dönüş yönünü silmek için arkaplan ile aynı renkte kare oluştur (x baslangıc, y baslangıc, genişlik, yükseklik, renk)
  tft.fillRect(12, 216, 216, 16, BLACK); // Ekranı baştan yenileyip silmek yerine gerekli yeri silmek için arka plan ile aynı renkte kare oluştur sag ok yönünü silmek için
  tft.fillTriangle(51, 192, 51, 144, 15, 168, WHITE); // sol tarafa dönüş yönüne doğru ok(üçgen) oluştur
  tft.print("Motor Sola Donuyor"); //imlecin olduğu yerden itibaren stringi yaz
      for(pos;pos<=180;pos++){ // derece değeri 180den küçük veya eşit ise açıyı arttır
        myservo.write(pos); // derece değerini servoya uygula
        tft.setCursor(66,144); //imleci 66,144 konumuna al
        tft.setTextSize(6); // punto değerini 6 yap
        tft.fillRect(66, 144, 108, 48, BLACK); // Önceki derece değerini silmek için arkaplan ile aynı renkte kare oluştur (x baslangıc, y baslangıc, genişlik, yükseklik, renk)
        tft.print(180-pos); // ekrana dereceyi yazdır motor tutuş yönü ters olduğu için 180-pos
        if (digitalRead(solbutonpin) == HIGH) break; // buton bırakıldı ise döngüden çık
        delay(sure); // servo hızını ayarlamak için gerkli bekleme
    }
    if(pos >= 180) {pos = 180; break;} // derece 180den büyük ise buton döngüsünden çık
  }

  
 while((digitalRead(sagbutonpin) == LOW)) { // butona basıldı ise sagaadöndür
  if(pos <= 0) {pos = 0; break;} // derece 0 dan büyük ise döngüye girme.
  tft.setCursor(12,216); // dönüş yönünü yazdırmak için imleci 12,216 kordinatına al gerekli punto için ortalanmış değerler     
  tft.setTextSize(2); // puntoyu 2 olarak ayarla
  tft.fillRect(12, 216, 216, 16, BLACK); // önceki dönüş yönünü silmek için arkaplan ile aynı renkte kare oluştur (x baslangıc, y baslangıc, genişlik, yükseklik, renk)
  tft.fillRect(15, 144, 38, 49, BLACK); // Ekranı baştan yenileyip silmek yerine gerekli yeri silmek için arka plan ile aynı renkte kare oluştur sol ok yönünü silmek için
  tft.print("Motor Saga Donuyor"); //imlecin olduğu yerden itibaren stringi yaz
  tft.fillTriangle(189, 192, 189, 144, 225, 168, WHITE); // sag tarafa dönüş yönüne doğru ok(üçgen) oluştur
      for(pos;pos>=0;pos--){ // derece değeri 0 dan büyük veya eşit ise açıyı arttır
        myservo.write(pos); // derece değerini servoya uygula
        tft.setCursor(66,144); //imleci 66,144 konumuna al
        tft.setTextSize(6); // punto değerini 6 yap
        tft.fillRect(66, 144, 108, 48, BLACK); // Önceki derece değerini silmek için arkaplan ile aynı renkte kare oluştur (x baslangıc, y baslangıc, genişlik, yükseklik, renk)
        tft.print(180-pos); // ekrana dereceyi yazdır motor tutuş yönü ters olduğu için 180-pos
        if (digitalRead(sagbutonpin) == HIGH) break; // buton bırakıldı ise döngüden çık
        delay(sure); // servo hızını ayarlamak için gerkli bekleme
    }
    if(pos <= 0) {pos = 0; break;} // derece 0 dan küçük ise buton döngüsünden çık 
  }

 simdikipos = pos; // şimdiki derece değerini kaydet
if ((simdikipos != oncekipos)) { // derece değeri değiştiyse
  oncekipos = simdikipos; // önceki değeri şimdiki değer olur
  tft.setCursor(42,216); // dönüş yönünü yazmak imleci 42,216 konumuna al -ortalamak için belirlenmiş değerler-    
  tft.setTextSize(2); // puntoyu 2 olarak ayarla
  tft.fillRect(189, 144, 38, 49, BLACK); // Ekranı baştan yenileyip silmek yerine gerekli yeri silmek için arka plan ile aynı renkte kare oluştur ok yönünü silmek için
  tft.fillRect(15, 144, 38, 49, BLACK);  // Ekranı baştan yenileyip silmek yerine gerekli yeri silmek için arka plan ile aynı renkte kare oluştur ok yönünü silmek için, Durduğu için iki yönüde siliyoruz
  tft.fillRect(12, 216, 216, 16, BLACK); // Önceki dönüş yönünü silmek için arkaplan ile aynı renkte kare oluştur (x baslangıc, y baslangıc, genişlik, yükseklik, renk)
  tft.print("Motor Duruyor"); // Belirlenen ortalanmış kordinata stringi yazdır
  while(1){ // butonların ikisinede basılmamış ise beklemek için
    if (digitalRead(solbutonpin) == LOW) break; //Butonu kontrol et sol butona basıldıysa döngüden çık
    if (digitalRead(sagbutonpin) == LOW) break; //Butonu kontrol et sağ butona basıldıysa döngüden çık
      }
    }
}
