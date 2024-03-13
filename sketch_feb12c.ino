#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LEDG 7
#define LEDR 6

MFRC522 mfrc522(SS_PIN, RST_PIN);  

void setup() 
{
 Serial.begin(9600);   
 SPI.begin();   
 mfrc522.PCD_Init();
 Serial.println("Approximate your card to the reader...");
 Serial.println();

 pinMode(LEDG, OUTPUT);
 pinMode(LEDR, OUTPUT);
}

void loop() 
{
 if ( ! mfrc522.PICC_IsNewCardPresent()) 
 {
    return;
 }
 if ( ! mfrc522.PICC_ReadCardSerial()) 
 {
    return;
 }
 String content= "";
 byte letter;
 for (byte i = 0; i < mfrc522.uid.size; i++) 
 {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
 }
 Serial.println();
 Serial.print("Message : ");
 content.toUpperCase();
 if (content.substring(1) == "E3 60 DE 24" || content.substring(1) == "26 F9 31 D4")
 {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(LEDG, HIGH); 
    delay(300);
    digitalWrite(LEDG, LOW);
 }
 else   {
    Serial.println(" Access denied");
    digitalWrite(LEDR, HIGH);
    delay(300);
    digitalWrite(LEDR, LOW);
 }
}
