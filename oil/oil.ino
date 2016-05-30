#include <LiquidCrystal_I2C.h>

#include <elapsedMillis.h>

#define out2 6
#define inp2 10



boolean debug = true;
boolean abilitated = false;
unsigned int  min_qta = 20;           
unsigned int quantity;
boolean distr = false;
uint8_t productor[8];
uint8_t data[16];
uint8_t oil_quantity[16];
int residue_oil;
boolean oil_finished = false;
boolean first_access = true; 
int celsius;



void PrintHexChar(const byte * data, const uint32_t numBytes)
{
  uint32_t szPos;

  for (szPos=0; szPos < numBytes; szPos++) 
  {
    if (data[szPos] <= 0x1F)
      Serial.print(F("."));
    else
      Serial.print((char)data[szPos]);
  }
  Serial.println();
}


void setup() {
  
   if(debug == true){
    Serial.begin(9600);
  }

   pinMode( out2,OUTPUT );
   digitalWrite( out2,LOW );
   setup_NFC();  
   setup_LCD_menu();
   setup_erogator();
   setup_thermocouple();
   quantity = min_qta;
   
}
 
void loop() {

  //set_oil_level(10000);
  
  
  abilitated =  isAbilitated();   
  if (abilitated) {
    
         //leggo le info solo se è il primo accesso così va molto piu veloceS
        if (first_access){
           digitalWrite( out2,HIGH ); 
           get_oil_productor();
           get_oil_level();
            String myString = String((char*)oil_quantity);
            residue_oil = myString.toInt();
            if (residue_oil > 0){
               oil_finished = false;
            }
            else{
              oil_finished = true;         
            }    
           
        }
      loop_thermocouple();
       loop_LCD_menu(abilitated);
       loop_erogator(quantity);
      //Serial.println("TARGA ABILITATA");    
  }
  else {    
     loop_LCD_menu(abilitated);
     digitalWrite( out2,LOW );
     //Serial.println("TARGA NON ABILITATA");
         
  } 
  
}
