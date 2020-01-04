byte pin_zvonec=3;
byte pin_detektor=4;

bool DB=false;
byte DB_MAX_stevec=3;
byte DB_stevec=0;
byte cas_vzorcenja=100;
byte cas_padanja=1000;

unsigned long zadnjeProzenje=0;
unsigned long zadnjePadanje=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_zvonec, OUTPUT);
  digitalWrite(pin_zvonec, LOW); 
  pinMode(pin_detektor, INPUT);

  Serial.begin(9600);
}

void loop() {
  unsigned long trenutniCas = millis();
  
  DB=digitalRead(pin_detektor);
  if(DB){
    if (trenutniCas - zadnjeProzenje >= cas_vzorcenja) {
      zadnjeProzenje=trenutniCas;
      DB_stevec++;
       
      Serial.println(DB_stevec);
    }
  }else{
    if (trenutniCas - zadnjePadanje >= cas_padanja) {
      zadnjePadanje=trenutniCas;
      
      if(DB_stevec>0){
        DB_stevec--;
      }else{
        DB_stevec=0;
      }
      
      Serial.println(DB_stevec);

    }
  }

  if(DB_stevec>=DB_MAX_stevec){
    for(int k=0; k<=50; k++){ 
      digitalWrite(pin_zvonec, HIGH);   
      delay(random(50,100));
      digitalWrite(pin_zvonec, LOW); 
      delay(random(50,100));
    }
    DB_stevec=0;
    delay(2000);
  }
  
}
