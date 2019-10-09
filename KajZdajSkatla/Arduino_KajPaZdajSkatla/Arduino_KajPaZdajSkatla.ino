#include "Keyboard.h"

byte LED_gumb_naprej=9;
byte LED_gumb_nazaj=10;

byte gumb_naprej=7;
byte gumb_nazaj=6;

int dihanje=0;
int korak_dihanja=2;
bool smerdihanja=false;
int dihanjeMax=40;
int dihanjeMin=1;

int hitrostKlikov=10;

void setup() {
  pinMode(LED_gumb_naprej, OUTPUT);
  pinMode(LED_gumb_nazaj, OUTPUT);
  pinMode(gumb_nazaj, INPUT_PULLUP);
  pinMode(gumb_naprej, INPUT_PULLUP);
  Serial1.begin(9600);
  Keyboard.begin();
}

int analogno=0;

int drzal_naprej=0;
int drzal_nazaj=0;
int drzal_oba=0;

int drzi=5;

byte nazaj=false;
byte naprej=false;

byte ekran=true;

long sifra=0;
byte bitek=1;

long KARTICA=0;
long KARTICA_ZDAJ=0;
long KARTICA_PREJ=0;

void NAPREJ(){
  if(drzal_naprej==drzi/2){
    digitalWrite(LED_gumb_naprej, HIGH);   
    digitalWrite(LED_gumb_nazaj, LOW);
    Keyboard.write(' ');
    delay(1000);
    
    drzal_naprej=0;
  }else{
    drzal_naprej++;
    digitalWrite(LED_gumb_naprej, LOW);   
    digitalWrite(LED_gumb_nazaj, LOW);
  }
}

void NAZAJ(){
  if(drzal_nazaj==drzi){
    digitalWrite(LED_gumb_naprej, LOW);   
    digitalWrite(LED_gumb_nazaj, HIGH);
  
    
    Keyboard.press(KEY_RIGHT_SHIFT);
    Keyboard.press(0x20);//space
    Keyboard.releaseAll();
    delay(1000);
    
    
    drzal_nazaj=0;
  }else{
    drzal_nazaj++;
    digitalWrite(LED_gumb_naprej, LOW);   
    digitalWrite(LED_gumb_nazaj, LOW);
  }
}

void OBA(){
  if(drzal_oba==drzi){
    digitalWrite(LED_gumb_naprej, HIGH);   
    digitalWrite(LED_gumb_nazaj, HIGH);

    OdpriURL(KARTICA_PREJ);
    KARTICA=KARTICA_PREJ;
    KARTICA_PREJ=KARTICA_ZDAJ;
    KARTICA_ZDAJ=KARTICA;
    
    
  
   
    drzal_oba=0;
  }else{
    drzal_oba++;
    digitalWrite(LED_gumb_naprej, LOW);   
    digitalWrite(LED_gumb_nazaj, LOW);
  }
}

void NOBEN(){
  if(dihanje>dihanjeMax){
    dihanje=dihanjeMax;
    smerdihanja=false;
  }

  if(dihanje<dihanjeMin){
    dihanje=dihanjeMin;
    smerdihanja=true;
  }

  analogWrite(LED_gumb_nazaj, dihanje);
  analogWrite(LED_gumb_naprej, dihanje);

  if(smerdihanja==true){
    dihanje+=korak_dihanja;
  }else{
    dihanje-=korak_dihanja/2;
  }
  drzal_naprej=0;
  drzal_nazaj=0;
  drzal_oba=0;
  
}


void OdpriURL(long KARTICA){
    Keyboard.write(KEY_F11);
    delay(2000);
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press('l');    
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.print("http>&&m.os/mk.si&iydelek.php_ID)000");
    Keyboard.println(KARTICA,DEC);
    /*delay(2000);
    Keyboard.write(KEY_RETURN);*/
    //delay(2000);
    Keyboard.write(KEY_F11);
    
 
  
}

void Kartica(){
  switch(KARTICA){
    case 8072239:
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F2);
    Keyboard.releaseAll();
    delay(500);
    Keyboard.print("poweroff");
    delay(500);
    Keyboard.write(KEY_RETURN);
     //malina izklop: ALT+F2 "poweroff" ENTER
      break;
    case 3395770:
    //izklop ekrana
    if(ekran){
      ekran=false;
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F2);
    Keyboard.releaseAll();
    delay(500);
    Keyboard.print("vcgencmd displaz?power 0");
    delay(500);
    Keyboard.write(KEY_RETURN);
    }else{
      ekran=true;
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F2);
    Keyboard.releaseAll();
    delay(500);
    Keyboard.print("vcgencmd displaz?power 1");
    delay(500);
    Keyboard.write(KEY_RETURN);
    }
//vcgencmd display_power 0
//vklop ekrana
//vcgencmd display_power 0
      break;
    case 7850344:
      //Keyboard.print("SEF");

      if(drzi<10){
        drzi=100;
      }else{
        drzi=5;
      }

      break;
    default:
    
      KARTICA_PREJ=KARTICA_ZDAJ;
            
      OdpriURL(KARTICA);
      
      KARTICA_ZDAJ=KARTICA;
        
      
  }
  
}

void loop() {
     
//  analogno=analogRead(gumba_pin);
  //DigiKeyboard.println(analogno);
   nazaj=!digitalRead(gumb_nazaj);
   naprej=!digitalRead(gumb_naprej);

//kartica
  if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    sifra=sifra<<8;
    sifra = sifra | Serial1.read();
    if(bitek<6){
    sifra=0;
    }
    //sifra2=sifra2 | sifra;
    if(bitek==8){
      
      KARTICA=sifra;
      Kartica();

      
      
      
       }
          
     if(bitek==10){bitek=0;sifra=0;}
      bitek++;
      // Serial.println(sifra2,HEX);   
  }
  ///karitca konec
   
  if(!nazaj && !naprej){
    NOBEN();
  }else{
    if(nazaj && naprej){
      OBA();
    }else{
      if(naprej){
        NAPREJ();
      }
      if(nazaj){
          NAZAJ();
      }
    }
  }
  delay(100);
}
//http://www.os-mk.si/izdelek.php?ID=0007843962
