#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
SoftwareSerial mySerial(6,7);//rx tx
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  mySerial.begin(115200);
}

void loop() 
{
  // Look for new cards
     if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }
    
  // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }
    
    //Show UID on serial monitor
    Serial.print("UID tag :");
    String content= "";
    
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    { if(mfrc522.uid.uidByte[i] < 0x0A){
      Serial.print(" 00"); //Add two zeroes for id value less than 10 
    }else if(mfrc522.uid.uidByte[i] < 0x64 ){
      Serial.print(" 0");
    }else{
      Serial.print(" ");
    }
    Serial.print(mfrc522.uid.uidByte[i]);
    if(mfrc522.uid.uidByte[i] < 0x0A){
     content.concat(String("00")); 
    }else if(mfrc522.uid.uidByte[i] < 0x64 ){
      content.concat(String("0"));
    }
       content.concat(String(mfrc522.uid.uidByte[i])); 
    }
    
      content.replace(" ", ""); //To remove spaces in the string
      Serial.println();
      Serial.println(content);
      mySerial.println(content);
      delay(3000);
} 

