#include <elapsedMillis.h>

int LED = 35;
int BUTTON = 10;
#define out1 5
#define inp1 9

elapsedMillis timePassed = 0;

void setup_erogator()
{
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode( out1,OUTPUT );
    //digitalWrite( out1,LOW );


}


void loop_erogator(int distr_time)
{
  if (distr == false ) {
    timePassed=0;
  }
  //delay(150);
  

  if (digitalRead(BUTTON) == HIGH && distr == false && oil_finished == false){
    
      distr = true;
      digitalWrite(LED,HIGH);    
      digitalWrite( out1,HIGH );

      get_oil_level();
      String myString = String((char*)oil_quantity);
      residue_oil = myString.toInt();
      residue_oil = residue_oil - quantity;
      quantity = min_qta;
      if (residue_oil <= 0 ){
        oil_finished = true;
        set_oil_level(0);      
      } 
      else { set_oil_level(residue_oil); }
    
  }
  // abbiamo detto che non si stoppa l'erogazione per adesso
  //else if (digitalRead(BUTTON) == HIGH && distr == true){    
  //  distr = false;
  //  digitalWrite(LED,LOW);  
  //} 
  
   if (timePassed >= distr_time){
    digitalWrite(LED,LOW);
    digitalWrite( out1,LOW);
    distr = false;
  }

}
