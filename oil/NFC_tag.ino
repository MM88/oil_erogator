
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>


#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield


#define ID_TARGA 116046784 
// #define ID_TARGA 1365872655 


Adafruit_NFCShield_I2C nfc(IRQ, RESET);

void setup_NFC() {
  
  Serial.begin(9600);
  Serial.println("Initialization....");
  nfc.begin();
  nfc.SAMConfig();
  Serial.println("Ready to read tag!");

}


boolean isAbilitated() {
 
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
 
  boolean success = false;
  uint8_t keya[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,1000);
    
  if (success) {
     
      uint32_t  cid = 0;
    	for( uint8_t i=0 ; i< uidLength ; i++ )
    	{
    	// cid <<= 8;
        cid <<= 4;
    		cid |= uid[i];
    	}
      Serial.print("  cid : ");Serial.println(cid, DEC);

      if(cid== ID_TARGA) {
        if (abilitated == true) first_access = false; 
        abilitated = true;       
      }
      else abilitated = false;      
  } else {
     abilitated = false;    
     first_access = true; 
  } 
  
  return abilitated; 
}


void get_oil_level(){
  
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  boolean success = false;
  uint8_t keya[4] = { 0xFF, 0xFF, 0xFF, 0xFF};
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,1000);
    
  if (success) {

    if (uidLength == 7)
    {           
    
      //autentico blocco 5 e in caso positivo lo leggo e salvo il contenuto in oil_quantity
      success = nfc.mifareclassic_AuthenticateBlock(uid,uidLength,5,0,keya);     
      if (success)
      {     
        success = nfc.mifareclassic_ReadDataBlock(5, oil_quantity);        
       //** PrintHexChar(oil_quantity,16);
       PrintHexChar(oil_quantity,4);
      }
    
    }
    else
    {
      Serial.println("This doesn't seem to be a Mifare Classic card!");
     
    }
     
  }
  
}

void set_oil_level(int new_level){
  
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  boolean success = false;
  //** uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF };
  uint8_t keya[4] = { 0xFF, 0xFF, 0xFF, 0xFF};
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,1000);
    
  if (success) {

    //** if (uidLength == 4)
    if (uidLength == 7)
    {      
       
    
      //autentico blocco 5 e in caso positivo lo leggo e salvo il contenuto in oil_quantity
      success = nfc.mifareclassic_AuthenticateBlock(uid,uidLength,5,0,keya);     
      if (success)
      {  
         String s_new_level = String(new_level);
         //** uint8_t charBuf[16];
         uint8_t charBuf[8];
         //** s_new_level.getBytes(charBuf, 16);
         s_new_level.getBytes(charBuf, 8) ;
        // memcpy(data, (const uint8_t[]){ 0,0,0,0,0,0,0,0,0,0,0,'1','0','0','0','0' }, sizeof data);
         success = nfc.mifareclassic_WriteDataBlock (5, charBuf);
           
        success = nfc.mifareclassic_ReadDataBlock(5, oil_quantity);   
        //PrintHexChar(oil_quantity,16);
      }    
    }
    else
    {
      Serial.println("This doesn't seem to be a Mifare Classic card!");
    }
       
  }
}


void get_oil_productor(){
  
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  boolean success = false;
    //** uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF };
  uint8_t keya[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
  uint8_t tmp_productor[16];

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,1000);
    
  if (success) {
    //** if (uidLength == 4)
    if (uidLength == 7)
    {      
      //autentico blocco 4 e in caso positivo lo leggo e salvo il contenuto in productor
      success = nfc.mifareclassic_AuthenticateBlock(uid,uidLength,4,0,keya);     
      if (success)
      {      
        success = nfc.mifareclassic_ReadDataBlock(4, tmp_productor);   
        memcpy (productor, tmp_productor, 4);
        //PrintHexChar(productor,16);
      }
    }
    else
    {
      Serial.println("This doesn't seem to be a Mifare Classic card!");
    }
     
  }

  
}

