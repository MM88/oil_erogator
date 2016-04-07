
#include <elapsedMillis.h>
#include <LiquidCrystal.h>                            

#define butUp    12     
#define butOk    11



char page = 0x01;                                       
char subpage = 0x00;       
boolean t_butUp, t_butOk;         
long previousMills = 0;
unsigned int page_time = 5000;
elapsedMillis timeElapsed = 0;
boolean first_enter = true;


LiquidCrystal_I2C disp(0x27,16,2);  // set the LCD address to 0x27 for a 20 chars and 4 line display


void setup_LCD_menu()
{
  Serial.begin(9600);  
  disp.begin();                                    

  pinMode(31, INPUT_PULLUP);    
  pinMode(37, INPUT_PULLUP); 
  
  t_butUp   = 0x00;                                   
  t_butOk   = 0x00;    

  disp.setCursor(0,0 );                                
  disp.print("NON ABILITATO ");                                            
                                
  
}


void loop_LCD_menu(boolean abilitated)
{
    if (abilitated && distr == false && oil_finished == false ){
       if (timeElapsed >= page_time && page != 0x01 ){  
        timeElapsed=0;      
        disp.clear();                         
        page = 0x01;
        subpage =  0x00;         
      }      
      if (first_enter){
        disp.clear();
        first_enter = false; 
         dispMenu( changeMenu());
      }  dispMenu( changeMenu());
       
           
    }
    else if (abilitated && distr == true && oil_finished == false ){
      disp.clear(); 
      disp.setCursor(0,0 );                                
      disp.print("EROGAZIONE");    
      page = 0x01;  
      subpage =  0x00;  
      }
    else if (!abilitated)
    {
      disp.clear(); 
      disp.setCursor(0,0 );                                
      disp.print("NON ABILITATO");    
    }  
  
  else if (oil_finished == true ) {
      disp.clear(); 
      disp.setCursor(0,0 );                                
      disp.print("OLIO FINITO");   
  }
  
}

int changeMenu()                                      
{
  if (!digitalRead(butUp))   t_butUp   = 0x01;         

  if (digitalRead(butUp) && t_butUp)                  
  { 
    t_butUp = 0x00;  
    disp.clear();                                    
    page++;
    timeElapsed=0;                                           
    if (page > 0x04) page = 0x01;         
  } 
  return page;
} 

void dispMenu(int page){
  
  switch (page)                                       
  {
    case 0x01:                                      
      temperature();
       
      break;                                    
    case 0x02:                                       
      oil_level();
      
      break;                                     
    case 0x03:                                      
      oil_productor();
     
      break;                                    
    case 0x04:                                       
      erogation();
       
      break;                 
  } 
} 

void temperature()                                        
{
  quantity = min_qta;   
  disp.setCursor(0,0 );                                
  disp.print("temperatura:");   
  disp.setCursor(0, 1);  
  disp.print(celsius);
  disp.setCursor(3, 1);
  disp.print((char) 223);  // print °
  disp.print("C");      
  
} 

void oil_level()                                      
{
  //get_oil_level();
  disp.setCursor(0, 0);                               
  disp.print("livello di olio: ");       
  String myString = String((char*)oil_quantity);  
  disp.setCursor(0, 1);  
  disp.print(myString);                             

}

void oil_productor() {            
                             
  //get_oil_productor();
  disp.setCursor(0, 0);                               
  disp.print("produttore olio: ");    
  String myString = String((char*)productor);
  disp.setCursor(0, 1);  
  disp.print(myString);    
    
  //PrintHexChar(productor,16);                            
        
} 
void erogation()                                           
{

     
  disp.setCursor(0, 0);                               
  disp.print("cambia quantita'");                                
  //disp.setCursor(7, 1);

  
  if(!digitalRead(butOk))    t_butOk    = 0x01;

  if(digitalRead(butOk) && t_butOk)                     
   {   
                
      t_butOk = 0x00;                                   
      
      subpage++;                                           
      timeElapsed=0;   
      if(subpage > 2) subpage = 0x01;                        
      
      switch(subpage)                                     
      {
          case 0x01:    
                             
                disp.setCursor(0,1);                    
                disp.print("op 1"); 
                quantity = 5000;                                                         
                      
                break;                                  
          case 0x02:        
                                           
                disp.setCursor(0,1);                   
                disp.print("op 2");   
                quantity = 7000;                
                              
                break;   
                                       
      
      } 
   
   } 

} 

















