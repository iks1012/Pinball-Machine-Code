#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

//Pin hole tests
const int hole1 = 3;
const int hole2 = 5;
const int hole3 = 6;

const int startGameSwitch = 9;
const int endGameSwitch = 10;
const int slaveSignalPin = 11; //will be used to output a signal to a slave board controlling the lights

int stateOfPin1 = 0;
int prevState1  = 0;

int stateOfPin2 = 0;
int prevState2  = 0;

int stateOfPin3 = 0;
int prevState3  = 0;

boolean isRunning = false; 


const int LED1 = 7;

int score = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(hole1,INPUT);
  pinMode(hole2,INPUT);
  pinMode(hole3,INPUT);
  pinMode(startGameSwitch,INPUT_PULLUP);
  pinMode(endGameSwitch,INPUT_PULLUP);
  pinMode(slaveSignalPin,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
}

void print(String str){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Start Game Limit Switch
  if (digitalRead(startGameSwitch) == LOW) {
    isRunning = true;
    digitalWrite(slaveSignalPin, 1); //sends a signal to the slave board to start the lights
    lcd.clear();
    lcd.setCursor(0,0);
    print("Game Started");
  }

  //End Game Limit switch
  if (digitalRead(endGameSwitch) == LOW) {
    isRunning = false;
    digitalWrite(slaveSignalPin, 0);
    print("Game Over");
  }
  
  if (isRunning) {
    stateOfPin1 = digitalRead(hole1);
    stateOfPin2 = digitalRead(hole2);
    stateOfPin3 = digitalRead(hole3);
    if(stateOfPin1 != prevState1 || stateOfPin2 != prevState2 || stateOfPin3 != prevState3){
      if(stateOfPin1 == HIGH || stateOfPin2 == HIGH || stateOfPin3 == HIGH){
        score++;
        print("Score: "+score);
        Serial.println(score);
      }
      else{
        Serial.println("OFF");
      }
      //delay(500);
      prevState1 = stateOfPin1;
      prevState2 = stateOfPin2;
      prevState3 = stateOfPin3;
    }
  }
}

void startLED(){

}

void startGame(){

}

void endGame(){

}




