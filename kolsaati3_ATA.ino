#include <Wire.h>           //İletişim kütüphanesi.
#include <DS1307new.h>      //Rtc modülü için kütüphane.
#include <LCD5110_Basic.h>         // LCD kütüphanemizi ekliyoruz

uint16_t startAddr = 0x0000;   // NV-RAM'de saklamak için başlangıç adresi.
uint16_t lastAddr;                      // NV-RAM'de saklamak için yeni adres.
uint16_t TimeIsSet = 0xaa55;   // Saatin tekrar ayarlanmamasına yardımcı olur.

LCD5110 myGLCD(8,9,10,11,12);     //  LCD pinlerimizi tanıtıyoruz
extern uint8_t BigNumbers[];      //Kullanacağımız fontlar için eklemeler yapıyoruz.
extern uint8_t MediumNumbers[]; 
extern uint8_t SmallFont[];


int lcd3v = 6;
int lcd_ledi = 5;

void setup()
{
  
  pinMode(lcd3v, OUTPUT);
  pinMode(lcd_ledi, OUTPUT);
  digitalWrite(lcd_ledi, HIGH);
  digitalWrite(lcd3v, HIGH);

  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));
  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  if (TimeIsSet != 0xaa55)
  {
    RTC.stopClock();
    RTC.fillByYMD(2019,2,15);
    RTC.fillByHMS(22,2,0);
    RTC.setTime();
    TimeIsSet = 0xaa55;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.startClock();
  }
    else
  {
    RTC.getTime();
  }
  
  myGLCD.InitLCD();
  myGLCD.setContrast(60);
  myGLCD.clrScr();
}

void loop()
{
  RTC.getTime();

  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();
//  myGLCD.print("HERYERDE", CENTER, 26);
  myGLCD.print("BILNET - ATA", CENTER, 0);
  myGLCD.print(":", 24, 20);
  myGLCD.print(":", 55, 20);
  myGLCD.print(".", 24, 44);
  myGLCD.print(".", 55, 44);
  myGLCD.print("2019", 60, 40);

  if (RTC.hour < 10)                  
  {
      myGLCD.setFont(MediumNumbers);
      myGLCD.print("0", LEFT, 8);
      myGLCD.printNumI(RTC.hour, 12, 8);
  } 
  else
  {
      myGLCD.setFont(MediumNumbers);
      myGLCD.printNumI(RTC.hour, LEFT, 8);
  }

  if (RTC.minute < 10)
  {
    myGLCD.setFont(MediumNumbers);
    myGLCD.print("0", 30, 8);
    myGLCD.printNumI(RTC.minute, 42, 8);
  }
  else
  {
    myGLCD.printNumI(RTC.minute, CENTER, 8);
  }

  if (RTC.second < 10) 
  {
    myGLCD.setFont(MediumNumbers);
    myGLCD.print("0", 60, 8);
    myGLCD.printNumI(RTC.second, 72, 8);
  }
  else
  {
    myGLCD.setFont(MediumNumbers);
    myGLCD.printNumI(RTC.second, RIGHT, 8);
  }

  if (RTC.day < 10)                  
  {
    myGLCD.setFont(MediumNumbers);
    myGLCD.print("0", LEFT, 32);
    myGLCD.printNumI(RTC.day, 12, 32);
  }
  else
  {
    myGLCD.setFont(MediumNumbers);
    myGLCD.printNumI(RTC.day, LEFT, 32);
  }

  if (RTC.month < 10)              
  {
    myGLCD.setFont(MediumNumbers);
    myGLCD.print("0", 30, 32);
    myGLCD.printNumI(RTC.month, 42, 32);
  }
  else
  {
    myGLCD.setFont(MediumNumbers);
    myGLCD.printNumI(RTC.month, 30, 32);
  }
  
//    myGLCD.setFont(MediumNumbers);
//    myGLCD.printNumI(RTC.year, 30, 8);

  switch (RTC.dow)   // Haftanın günü
  {
    case 1:
      myGLCD.setFont(SmallFont);
      myGLCD.print("PAZARTESI", CENTER, 26);
      break;
    case 2:
      myGLCD.setFont(SmallFont);
      myGLCD.print("SALI", CENTER, 26);
      break;
    case 3:
      myGLCD.setFont(SmallFont);
      myGLCD.print("CARSAMBA", CENTER, 26);
      break;
    case 4:
      myGLCD.setFont(SmallFont);
      myGLCD.print("PERSEMBE", CENTER, 26);
      break;
    case 5:
      myGLCD.setFont(SmallFont);
      myGLCD.print("CUMA", CENTER, 26);
      break;
    case 6:
      myGLCD.setFont(SmallFont);
      myGLCD.print("CUMARTESI", CENTER, 26);
      break;
    case 7:
      myGLCD.setFont(SmallFont);
      myGLCD.print("PAZAR", CENTER, 26);
      break;
  }
  delay(1000);
}
