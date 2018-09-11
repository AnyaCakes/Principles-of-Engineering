//Initialize what pins we will be using
const int ledPin1 =  9;
const int ledPin2 = 11;
const int ledPin3 = 10;
//pin for button
const int buttPin = 8;
//pin for potentiometer
const int potPin = A1;

//Initialize empty variables that hold our changing factors (the voltage passing through the button and the potentiometer)
float volt = 0;
float pot = 0;

//Initialize LEDs as off
int ledState = LOW;
int ledState_array[] = {0,0,0};

//i --> what mode is on
//j --> which LED is being changed from on or off
//k --> used for random changing of LEDs
int i = 0; 
int j = 0;
int k = 0; 

//previousMillis --> intializes start time
//interval --> time elapsed before next behavior in each mode
//interval_rand --> time elapsed before next behavior in random (we wanted it to go faster)
//interval_rand --> time elapsed before next behavior in the fast flashing mode
unsigned long previousMillis = 0;       
const long interval = 1000;
const long interval_rand = 500;
const long interval_fast = 100;

//tells the arduino whether or not to change modes
bool change = false;   

//we have 5 functions (modes) to define and choose from
//this allows us to call the different functions by calling myFunction
void (*myFunction[5])();

//sets up all the pins. Defines all functions in the array
void setup() {
  myFunction[0] = delay_flash;
  myFunction[1] = flash;
  myFunction[2] = all_on;
  myFunction[3] = strobe;
  myFunction[4] = rand_flash;
  //ledPins are outputting voltage
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  //buttPin is reading voltage
  pinMode(buttPin, INPUT);
  //begin serial monitor for debugging
  Serial.begin(9600);
}

//looks for cues to switch between modes
void loop() {
  //read values from button and potentiometer
  volt = digitalRead(buttPin);
  pot = analogRead(potPin)/4;
  digitalWrite(buttPin, HIGH);

  // switches between different modes. Reads values from button. 1 means button not pressed, 0 means it is. Every time pressed switches to new mode
  while(volt == 1){
    volt = digitalRead(buttPin);
    pot = analogRead(potPin)/4;
    //Serial.println(i);
    myFunction[i]();
  }

  while(volt == 0){
    volt = digitalRead(buttPin);
    pot = analogRead(potPin)/4;
    //Serial.println(pot);
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

  //if the interval has passed, turn all LEDs on/off (loops until button is pressed)
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
  //turn each LED on and then each LED off (time between on/off is interval)
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (ledState_array[j] == 0) {
      pot = analogRead(potPin)/4;
      analogWrite(ledPin[j], pot); 
      ledState_array[j] = 1;
    } 
    else {
      ledState_array[j] = 0;
      analogWrite(ledPin[j], 0);
    }
         
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

// turns all LEDs on and off at the same time... but faster
void strobe () {    
    unsigned long currentMillis = millis();
  
  //if the interval has passed, turn all LEDs on/off. Uses faster interval
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
  
  //picks random LED, if it is on, turns it off, and vice versa
  if (currentMillis - previousMillis >= interval_rand) {   
    previousMillis = currentMillis;
    if (ledState_array[k] == 0) {
      pot = analogRead(potPin)/4;
      analogWrite(ledPin[k], pot); 
      ledState_array[k] = 1;
    } 
    else {
      ledState_array[k] = 0;
      analogWrite(ledPin[k], 0);
    }
  }
}

