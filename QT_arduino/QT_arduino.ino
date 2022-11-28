#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
  String a;
 int i;
Servo myservo;
//int potpin = 9;  // analog pin used to connect the potentiometer
int val;  
///////////
LiquidCrystal_I2C lcd(0x27, 20, 4);
void setup() {
    /// BUZZER
    pinMode(4, OUTPUT);
    // MOTOR
    myservo.attach(7);


     
  ////////// RFID
  Serial.begin(9600); 
   SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522


  //////// LCD
lcd.init();
lcd.backlight();
lcd.setCursor(1, 0);
lcd.print("Smart Radio!");
}
void loop() {

    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  String content= "";
  byte letter;
  int read;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
  
     Serial.print(mfrc522.uid.uidByte[i], HEX);
   
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
 Serial.println();
  content.toUpperCase();

  if (content.substring(1) == "C3 0C 77 A7") //change here the UID of the card/cards that you want to give access
  {
  a="";i=0;
  while ((a=="")&& (i<30))
   {a=Serial.readString();i++;}
         lcd.clear();
    lcd.setCursor(0, 0);
lcd.print("Bonjour ");
lcd.print(a);
lcd.setCursor(0, 1);
lcd.print("Bienvenue!");
   
    //Serial.println("Authorized access");
    
      // scale it to use it with the servo (value between 0 and 180)
  myservo.write(0); 
  tone(4,1000);
  // sets the servo position 
  delay(3000);  
   noTone(4);

  }
 
 else if (content.substring(1) == "73 E4 8E 92") 
 {
   // Serial.println("Second access");
   // Serial.println();
     // scale it to use it with the servo (value between 0 and 180)
     a="";i=0;
  while ((a=="")&& (i<30))
   {a=Serial.readString();i++;}
         lcd.clear();
    lcd.setCursor(0, 0);
lcd.print("Bonjour ");
lcd.print(a);
lcd.setCursor(0, 1);
lcd.print("Bienvenue!");
  myservo.write(90);  
    tone(4,1000);   // sets the servo position according to the scaled value
  delay(3000);
noTone(4);


  
  }
 
else if (content.substring(1) == "7C BD EB 31") 
 {
  // scale it to use it with the servo (value between 0 and 180)
   a="";i=0;
  while ((a=="")&& (i<30))
   {a=Serial.readString();i++;}
         lcd.clear();
    lcd.setCursor(0, 0);
lcd.print("Bonjour ");
lcd.print(a);
lcd.setCursor(0, 1);
lcd.print("Bienvenue!");
  myservo.write(90);                  // sets the servo position according to the scaled value
  delay(500);
  myservo.write(180);                  // sets the servo position according to the scaled value
    tone(4,1000);

  delay(3000);
noTone(4);


  
  }
 
 
 else   {
   lcd.clear();
    lcd.setCursor(0, 0);
lcd.print(" Access denied ");
    //Serial.println(" Access denied");
    delay(3000);
  
  }

        

  
}

////////

 
