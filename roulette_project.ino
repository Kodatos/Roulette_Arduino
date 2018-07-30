int inPin1 = 4;
int inPin2 = 5;
int inPin3 = 6;
int potPin = A0;
int swPin = A1;
int digitPin = 3;
int ledPin = 2;
int interruptPin = 2;
int currentPin = 1;
int chosenPin = 1;
int isChoosing = 10000;
int del = 50;
int stopDelay = 200;
int score = 0;

int num_array[10][7] = {  { 1, 1, 1, 1, 1, 1, 0 }, // 0
  { 0, 1, 1, 0, 0, 0, 0 }, // 1
  { 1, 1, 0, 1, 1, 0, 1 }, // 2
  { 1, 1, 1, 1, 0, 0, 1 }, // 3
  { 0, 1, 1, 0, 0, 1, 1 }, // 4
  { 1, 0, 1, 1, 0, 1, 1 }, // 5
  { 1, 0, 1, 1, 1, 1, 1 }, // 6
  { 1, 1, 1, 0, 0, 0, 0 }, // 7
  { 1, 1, 1, 1, 1, 1, 1 }, // 8
  { 1, 1, 1, 0, 0, 1, 1 }
};   // 9

/*
 * LED 1 : Low, HIgh, Z
 * LED 5 : Z, High, Low
 * LED 4 : Z, Low, HIgh
 * LED 2 : High, Low, Z
 * LED 3 : High, Z, Low
 * LED 6 : Low, Z, High
 */
 


void setup() {
  // put your setup code here, to run once:
    //attachInterrupt(digitalPinToInterrupt(interruptPin), changeState, CHANGE);
    pinMode(digitPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    for(int i=7; i<=13; i++)
      pinMode(i,OUTPUT);
    digitalWrite(3, HIGH);
    randomSeed(analogRead(0));
    stopDelay = random(200, 250);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sw = analogRead(swPin);
  if((sw>=650 && sw<=720) && isChoosing>0){
    isChoosing--;
  }
  if(isChoosing==10000){
    int pot = analogRead(potPin);
    currentPin = map(pot, 0, 1000, 1, 6);
    lightCharlie(currentPin);
  }
  else if(isChoosing==0){
    if(del>=stopDelay){
      if(currentPin == chosenPin)
        score++;
      else
        score--;
      if(score>9)
        score=9;
      if(score<0)
        score=0;
      del = 50;
      isChoosing = 10000;
      lightCharlie(currentPin);
      stopDelay = random(200,250);
      delay(5000); 
    }
    else {
    lightCharlie(currentPin);
    currentPin++;
    if(currentPin==7)
      currentPin=1;
    delay(del);
    del+=5;
    }
  }
    else{
      chosenPin = currentPin;    
    /*for(int i=6;i>=1;i--){
     lightCharlie(i);
     delay(100);
    }*/
  }
  if(isChoosing==10000)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
  ssd(score);
}

void ssd(int score){
  for(int j=7; j<=13; j++){
    digitalWrite(j, num_array[score][j-7]);
  }
}

void lightCharlie(int pin){
  switch(pin){
  case 3:
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, INPUT);
  pinMode(inPin3, OUTPUT);
  digitalWrite(inPin1, HIGH);
  digitalWrite(inPin3, LOW);
  break; 
  case 4:
  pinMode(inPin1, INPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, OUTPUT);
  digitalWrite(inPin2, LOW);
  digitalWrite(inPin3, HIGH);
  break; 
  case 5:
  pinMode(inPin1, INPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, OUTPUT);
  digitalWrite(inPin2, HIGH);
  digitalWrite(inPin3, LOW);
  break; 
  case 1:
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, INPUT);
  digitalWrite(inPin1, LOW);
  digitalWrite(inPin2, HIGH); 
  break;
  case 2:
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, INPUT);
  digitalWrite(inPin1, HIGH);
  digitalWrite(inPin2, LOW);
  break;
  case 6:
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, INPUT);
  pinMode(inPin3, OUTPUT);
  digitalWrite(inPin1, LOW);
  digitalWrite(inPin3, HIGH);
  break;
  default:
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, OUTPUT);
  digitalWrite(inPin1, LOW);
  digitalWrite(inPin2, LOW);
  digitalWrite(inPin3, LOW);
  break;
  }
}

