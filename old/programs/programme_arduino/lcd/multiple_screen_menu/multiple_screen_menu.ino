//////////// Bibliothèques + déclaration écran

#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 2);


//////////// Counter to change positions of pages
int page_counter=1 ;       //To move beetwen pages

//-------Pins-----//
int up = 24;               //Up button
int down = 28;           //Down button
const int led = 26;

//////////// Texts
// On note que l'utilisation des string en Arduino est complexe.
// L'utilisation de tableau char ne l'est pas non plus car char => 1 caractère
// PROGMEM => propre a l'arduino pour occuper moins de place : http://www.locoduino.org/spip.php?article131
const char text1[] PROGMEM = "Pulp Fiction";
char message1[50];
const char text2[] PROGMEM = "Sodomiee";
char message2[50];


//---------Storage debounce function-----//
boolean current_up = LOW;          
boolean last_up=LOW;            
boolean last_down = LOW;
boolean current_down = LOW;


void setup() {
pinMode(up, INPUT);
pinMode(down, INPUT);
pinMode(led, OUTPUT);
lcd.init();  // initialisation de l'afficheur

}


   //---- De-bouncing function for all buttons----//
boolean debounce(boolean last, int pin)
{
boolean current = digitalRead(pin);
if (last != current)
{
delay(5);
current = digitalRead(pin);
}
return current;
}


void loop() {

//Recuperation variable text
strcpy_P(message1, text1);
strcpy_P(message2, text2);


current_up = debounce(last_up, up);         //Debounce for Up button
current_down = debounce(last_down, down);   //Debounce for Down button

//----Page counter function to move pages----//

//Page Up
    if (last_up== LOW && current_up == HIGH){  //When up button is pressed
      lcd.clear();                     //When page is changed, lcd clear to print new page  
      if(page_counter <3){              //Page counter never higher than 3(total of pages)
      page_counter= page_counter +1;   //Page up
      
      }
      else{
      page_counter= 3;  
      }
  }
  
    last_up = current_up;

//Page Down
    if (last_down== LOW && current_down == HIGH){ //When down button is pressed
      lcd.clear();                     //When page is changed, lcd clear to print new page    
      if(page_counter >1){              //Page counter never lower than 1 (total of pages)
      page_counter= page_counter -1;   //Page down
      
      }
      else{
      page_counter= 1;  
      }
  }
    
    last_down = current_down;

//------- Switch function to write and show what you want---// 
  switch (page_counter) {
   
    case 1:{     //Design of home page 1
      lcd.setCursor(0,0);
      lcd.print("Bonjour,");
      lcd.setCursor(0,1);
      lcd.print(message1);
    }
    break;

    case 2: { //Design of page 2 
     lcd.setCursor(5,0);
     lcd.print("This is");
     lcd.setCursor(5,1);
     lcd.print(message2);
    }
    break;

    case 3: {   //Design of page 3 
     lcd.setCursor(1,0);
     lcd.print("You are now on");
     lcd.setCursor(4,1);
     lcd.print("Page 3");
    }
    break;
    
  }//switch end
  
}//loop end
