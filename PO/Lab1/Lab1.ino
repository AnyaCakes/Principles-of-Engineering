const int ledPin1 =  9;
const int ledPin2 = 11;
const int ledPin3 = 10;
const int buttPin = 8;
const int potPin = A1;
float volt = 0;
float pot = 0;

int ledState = LOW;   
int i = 0; 
int j = 0;
int k = 0; 
unsigned long previousMillis = 0;       
const long interval = 1000;
const long interval_rand = 500;
const long interval_fast = 100;
bool change = false;   



//we have 5 functions to define
void (*myFunction[5])();


void setup() {
  myFunction[0] = delay_flash;
  myFunction[1] = flash;
  myFunction[2] = all_on;
  myFunction[3] = strobe;
  myFunction[4] = rand_flash;
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // switches between different modes. Reads values from button. 1 means button not pressed, 0 means it is. Every time pressed switches to new mode
  volt = digitalRead(buttPin);
  pot = analogRead(potPin)/4;
  Serial.println(pot);
  
  digitalWrite(buttPin, HIGH);



  while(volt == 1){
    volt = digitalRead(buttPin);
    pot = analogRead(potPin)/4;
    Serial.println(pot);
    myFunction[i]();
    
    
  }

  while(volt == 0){
    volt = digitalRead(buttPin);
    pot = analogRead(potPin)/4;
    Serial.println(pot);
    change = true;
  }
  
  if (change == true){
    if (i<4) {
      i = i+1;
      j = 0;
      analogWrite(ledPin1, LOW);
      analogWrite(ledPin2, LOW);
      analogWrite(ledPin3, LOW);  
      change = false;
    }
    else {
        i = 0;
        j = 0;
        analogWrite(ledPin1, LOW);
        analogWrite(ledPin2, LOW);
        analogWrite(ledPin3, LOW);  
        change = false;
    }
  }
  
};

// turns all LEDs on and off at the same time
void flash () {
   
  unsigned long currentMillis = millis();


  
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

   
    if (ledState == LOW) {
      pot = analogRead(potPin)/4;
      ledState = pot;
    } else {
      ledState = LOW;
    }
  
    analogWrite(ledPin1, ledState);
    analogWrite(ledPin2, ledState);
    analogWrite(ledPin3, ledState);  
  }

}

//turns LEDs on in series, and then off
void delay_flash () {
  int ledPin[] = {ledPin1, ledPin2, ledPin3};     
   
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (analogRead(ledPin[j]) == 0) {
      pot = analogRead(potPin)/4;
      ledState = pot;
    } else {
      ledState = LOW;
    }
    
    analogWrite(ledPin[j], ledState);
     
    if(j<2){
      j = j+1;
    } else {
      j = 0;
    }
  }

}

//turns all LEDs on
void all_on () {
    pot = analogRead(potPin)/4;
    ledState = pot;
    
  
    analogWrite(ledPin1, ledState);
    analogWrite(ledPin2, ledState);
    analogWrite(ledPin3, ledState);  
    
}

//turns all LEDs off
void strobe () {
    
    unsigned long currentMillis = millis();


  
  if (currentMillis - previousMillis >= interval_fast) {
    
    previousMillis = currentMillis;

    if (ledState == LOW) {
      pot = analogRead(potPin)/4;
      ledState = pot;
    } else {
      ledState = LOW;
    }
  
    analogWrite(ledPin1, ledState);
    analogWrite(ledPin2, ledState);
    analogWrite(ledPin3, ledState);  
  }  
}

//turns on and off randomly
void rand_flash () {
  int ledPin[] = {ledPin1, ledPin2, ledPin3};     
  k = int(random(0,3));
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval_rand) {
    
    previousMillis = currentMillis;

    
    if (analogRead(ledPin[k]) == 0) {
      pot = analogRead(potPin)/4;
      ledState = pot;
    } else {
      ledState = LOW;
    }
  
    analogWrite(ledPin[k], ledState);

  }

}

