/*
 * Copyright 2019 Zakaria Madaoui. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 

#define DEVICES_NUMBER 1

int RCLK1 = 2 ;
int SRCLK1 = 3 ;
int DATA1 = 4 ;


int RCLK2 = 5 ;
int SRCLK2 = 6 ;
int DATA2 = 7 ;
int lngth = 1 ;

bool charComplete = false ;
char coordinate[3] ;
int index = 0 ;

bool string = false ;
bool gesture = true ;
String inString = "" ;
char inChar;
bool stringComplete = false ;
bool shiftON = false ;
byte chr[8];


byte inWord[80] = {0, 0, 0, 0, 0, 0, 0, 0};
byte Display[8] = {B11111110,
                   B11111101,
                   B11111011,
                   B11110111,
                   B11101111,
                   B11011111,
                   B10111111,
                   B01111111
                  };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Setting up timers
  TCCR1A = 0 ;
  TCCR1B = 0 ;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);


  pinMode(SRCLK1, OUTPUT);
  pinMode(RCLK1, OUTPUT);
  pinMode(DATA1, OUTPUT);

  pinMode(SRCLK2, OUTPUT);
  pinMode(RCLK2, OUTPUT);
  pinMode(DATA2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (charComplete) {
    updateChar();
    //inByte = 0; // may be not neccesary
    charComplete = false ;
  }

 if (stringComplete) {
    updateWord(inString);
    inString = "";
    stringComplete = false ;
  }
  
//---------------- Updating the display ------------------------
  Update();
}

//Timer for shifting
ISR(TIMER1_OVF_vect) {
  if (shiftON) {
    byte temp = inWord[0];

    for (int i = 0 ; i < lngth * 8 - 1; i++ ) {
      inWord[i] = inWord[i + 1];
    }
    inWord[lngth * 8 - 1] = temp;
  }
}

void Update() {

  for (int i = 0; i < DEVICES_NUMBER * 8; i++ ) {
    digitalWrite(RCLK1, LOW);
    digitalWrite(RCLK2, LOW);

    shiftOut(DATA1, SRCLK1, MSBFIRST, inWord[i]); // if devices number is > 1 you need to use shiftOutX library
    shiftOut(DATA2, SRCLK2, MSBFIRST, Display[i]);

    digitalWrite(RCLK1, HIGH);
    digitalWrite(RCLK2, HIGH);
  }

}


// this function makes the array of bytes of a given string
void updateWord(String s) {

  int index = 0 ;
  int n = s.length();

  for (int i = 0 ; i < n ; i++) {
    updateChar(s.charAt(i));
    for (int i = 0 ; i < 8 ; i++) {
      inWord[index] = chr[i] ;
      index++;

    }
  }
}


void updateChar() {

  byte temp = B00000001;

  if (coordinate[0] == '1') {
    temp = temp;
  }
  if (coordinate[0] == '0') {
    temp = -temp;
  }
//-------------------------------------
  if      (coordinate[2] == '0') {
    temp = temp;
  }
  else if (coordinate[2] == '1') {
    temp = temp << 1;
  }
  else if (coordinate[2] == '2') {
    temp = temp << 2;
  }
  else if (coordinate[2] == '3') {
    temp = temp << 3;
  }
  else if (coordinate[2] == '4') {
    temp = temp << 4;
  }
  else if (coordinate[2] == '5') {
    temp = temp << 5;
  }
  else if (coordinate[2] == '6') {
    temp = temp << 6;
  }
  else if (coordinate[2] == '7') {
    temp = temp << 7;
  }
//-----------------------------------------------------
  
  if      (coordinate[1] == '0') {
    inWord[0] = inWord[0]+ temp;
  }
  else if (coordinate[1] == '1') {
    inWord[1] += temp;
  }
  else if (coordinate[1] == '2') {
    inWord[2] += temp;
  }
  else if (coordinate[1] == '3') {
    inWord[3] += temp;
  }
  else if (coordinate[1] == '4') {
    inWord[4] += temp;
  }
  else if (coordinate[1] == '5') {
    inWord[5] += temp;
  }
  else if (coordinate[1] == '6') {
    inWord[6] += temp;
  }
  else if (coordinate[1] == '7') {
    inWord[7] += temp;
  }

}



void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    if (inChar == 'W') { string = true ; gesture = false;
                         shiftON = true;}
   
    else if (inChar == 'C') {
      shiftON = false; Clear();
      string = false ; gesture = true;
    }

   else if (inChar == 'S') {shiftON = true;}
    
   else  if(string){
      
      inString += inChar;
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
     if (inChar == '\n') {
      stringComplete = true;
    }
    
    lngth = inString.length()-1 ;/*if you dont use serial monitor
                                  you have to ommit "-2"*/
  }
  
      
 
 
  else  if(gesture) {

      coordinate[index] = inChar;
      index++;

      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
      if (index == 3) {
        charComplete = true;
        index = 0;
      }
    }
  }
}


void updateChar(char c) {

  //Note that the characters are rotated clockwize
  switch (c) {
    case 'a': 
      chr[0] = B00000000;
      chr[1] = B11111110;
      chr[2] = B00010010;
      chr[3] = B00010010;
      chr[4] = B00010010;
      chr[5] = B00010010;
      chr[6] = B11111110;
      chr[7] = B00000000;
      break;

    case 'b': 
      chr[0] = B00000000;
      chr[1] = B11111110;
      chr[2] = B10010010;
      chr[3] = B10010010;
      chr[4] = B10010010;
      chr[5] = B10010010;
      chr[6] = B01101100;
      chr[7] = B00000000;
      break;

    case 'c': 
      chr[0] = B00000000;
      chr[1] = B11111110;
      chr[2] = B10000010;
      chr[3] = B10000010;
      chr[4] = B10000010;
      chr[5] = B10000010;
      chr[6] = B10000010;
      chr[7] = B00000000;
      break;
    case 'd': 
      chr[0] = B00000000;
      chr[1] = B11111110;
      chr[2] = B10000010;
      chr[3] = B10000010;
      chr[4] = B10000010;
      chr[5] = B10000010;
      chr[6] = B01111100;
      chr[7] = B00000000;
      break;
      
    case 'e': 
      chr[0] = B00000000;
      chr[1] = B11111110;
      chr[2] = B10010010;
      chr[3] = B10010010;
      chr[4] = B10010010;
      chr[5] = B10010010;
      chr[6] = B10010010;
      chr[7] = B00000000;
      break;
    case 'f': 
      chr[0] = B00000000;
      chr[1] = B11111110;
      chr[2] = B00010010;
      chr[3] = B00010010;
      chr[4] = B00010010;
      chr[5] = B00010010;
      chr[6] = B00010010;
      chr[7] = B00000000;
      break;

    case 'g': 
      chr[0] = B00000000;
      chr[1] = B11111110;
      chr[2] = B10000010;
      chr[3] = B10110010;
      chr[4] = B10010010;
      chr[5] = B10010010;
      chr[6] = B11110010;
      chr[7] = B00000000;
      break;

    case 'h': 
      chr[0] = B00000000;
      chr[1] = B11111110;
      chr[2] = B00010000;
      chr[3] = B00010000;
      chr[4] = B00010000;
      chr[5] = B00010000;
      chr[6] = B11111110;
      chr[7] = B00000000;
      break;

    case 'i': 
      chr[0] = B00000000;
      chr[1] = B10000010;
      chr[2] = B10000010;
      chr[3] = B11111110;
      chr[4] = B10000010;
      chr[5] = B10000010;
      chr[6] = B00000000;
      chr[7] = B00000000;
      break;

    default : 
      chr[0] = B00000000;
      chr[1] = B00000000;
      chr[2] = B00000000;
      chr[3] = B00000000;
      chr[4] = B00000000;
      chr[5] = B00000000;
      chr[6] = B00000000;
      chr[7] = B00000000;
      break;


    //you can add more charachters here

  }


}

void Clear(){
  
  for(int i = 0;i<80;i++){
  inWord[i] = B00000000 ; 
  
  
    }
  }
