
class Matrix {
  
  String typing = "";

  float x;
  float y ;
  float center ;
  PVector mouseP = new PVector();
  // button 1 position   
  PVector b1Pos = new PVector(30,(height/3)+(width-60)/2+10);
  PVector t1Pos = new PVector(30+(width-60)/4,b1Pos.copy().y+35);
  // button 2 poition
  PVector b2Pos = new PVector(40+(width-60)/2,b1Pos.y);
  PVector t2Pos = new PVector(t1Pos.copy().x+(width-60)/2+10,t1Pos.y);
  // textBox position
  PVector tbPos = new PVector(width/2,(height/3)+(width-60)/2+100);
  PVector txtPos = new PVector(60,tbPos.copy().y+10);

  Layout layout ;
  Dots[][] dot = new Dots[8][8];
  Button b1 = new Button("Clear",b1Pos,t1Pos);
  Button b2 = new Button("Shift",b2Pos,t2Pos);
  textBox tb = new textBox(tbPos);
  
//========================== Some inetializations ===========================
  Matrix() {

    layout = new Layout(); // Layout instance

    x = 30+(width-60)/16 ; // calculated ;)
    y = (height/3)-9*(width-60)/16 ; // calculated ;)


    // Inetializing the LEDs and assigning thier positions
    for (int col=0; col<8; col++) {
      for (int row=0; row<8; row++) {

        y += (width-60)/8;

        dot[col][row] = new Dots();
        dot[col][row].p = new PVector(x, y); // positions for leds

        if (row==7) y = (height/3)-9*(width-60)/16 ;
      }
      x+= (width-60)/8;
    }
  }

//========================= Drawing the LED Matrix ==========================


  void Draw() {

    //Drawing the layout 
    layout.Draw();  
    b1.Draw();
    b2.Draw();
    tb.Draw();
    viewText();
    // Drawing the led dots 
    for (int col=0; col<8; col++) {
      for (int row=0; row<8; row++) {
        dot[col][row].Draw();
      }
    }

  
  }
//---------------------------------------------------------------------------

// ==================== Clear function for Clear Button =====================
  void Clear() {

    for (int col=0; col<8; col++) {
      for (int row=0; row<8; row++) {
        dot[col][row].Color = color(#DEDBDB);
        dot[col][row].state = true;
      }
    }
  }
//---------------------------------------------------------------------------

  void lightON(PVector v) {

    for (int col=0; col<8; col++) {
      for (int row=0; row<8; row++) {


        if (dist(v.x, v.y, dot[col][row].p.x, dot[col][row].p.y)<22) {

          dot[col][row].Color = color(#FF2B00);
          
        if(dot[col][row].state){  char a = intToChar(col);
          char b = intToChar(row); ;
          
          // Send the coordinates from here
           mySerial.write('1');    //"1" for ledON
           mySerial.write(a) ;
           mySerial.write(b) ;
           dot[col][row].state = false ;
         }
          
          
        }
      }
    }
  }
  
  void lightOFF(PVector v) {

    for (int col=0; col<8; col++) {
      for (int row=0; row<8; row++) {


        if (dist(v.x, v.y, dot[col][row].p.x, dot[col][row].p.y)<22) {

          dot[col][row].Color = color(#DEDBDB);
          
          char a = intToChar(col);
          char b = intToChar(row); ;
          
          // Send the coordinates from here
        if(!dot[col][row].state){   mySerial.write('0');    //"1" for ledON
           mySerial.write(a) ;
           mySerial.write(b) ;
           dot[col][row].state =true ;
         }
        }
      }
    }
  }
  
  
  //--------------------------------------------------------------------------
  
 void sendText(char c){
   
 typing = typing + c;
   
 if(c == '\n'){ mySerial.write(typing);
                typing = "" ;}

 
 }
 
 
 void viewText(){
 
 // draw the text
 fill(0);
 textSize(35);
 textAlign(CORNER);
 text("Input: "+typing,txtPos.x,txtPos.y);
 
 }
 
 void buttonClicked(float x,float y){
 
//if(dist(t1Pos.x,t1Pos.y,x,y)<50){
//  Clear();
//  mySerial.write('C');
  
if(abs(t1Pos.x-x)<(width-80)/4 && abs(t1Pos.y-y)<22){
  Clear();
  mySerial.write('C');


}


if(abs(t2Pos.x-x)<(width-80)/4 && abs(t2Pos.y-y)<22){
  mySerial.write('S');}   
   
 
if((x>30&& x< width-30)&& abs(tbPos.y-y)<25 ){
  
  mySerial.write('W'); 
}
 
 }
  
 

char intToChar(int n){
if(n==0){return '0';}
else if(n==1){return '1';}
else if(n==2){return '2';}
else if(n==3){return '3';}
else if(n==4){return '4';}
else if(n==5){return '5';}
else if(n==6){return '6';}
else {return '7';}

}


}
