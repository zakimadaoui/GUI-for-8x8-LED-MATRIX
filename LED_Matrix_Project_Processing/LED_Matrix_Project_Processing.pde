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


import processing.serial.*;

Serial mySerial;

Matrix m ;
String a  = "Clear";



void setup() {

  size(500, 700);
  m = new Matrix();
  
  String portName = Serial.list()[0];
  mySerial = new Serial(this,portName,9600);
}



void draw() {

  background(150);

  m.Draw();
  

}



void mouseDragged(){
 
m.lightON(new PVector(mouseX,mouseY));

}

void mouseClicked(){

  
m.lightOFF(new PVector(mouseX,mouseY));

m.buttonClicked(mouseX,mouseY);

}

void keyPressed() {
  m.sendText(key);
}
