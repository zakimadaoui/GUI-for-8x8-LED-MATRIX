
class Dots {

  color Color = color(#DEDBDB); // Grey color
  PVector p ;
  boolean state = true;

  void Draw() {
    noStroke();
    fill(Color);
    ellipse(p.x, p.y, 20, 20);
  }
}

//---------------------------------------------------------------------------

class Button {

  //TODO: Clear all / Text / Custom + Shift : buttons
  String a;
  PVector b;
  PVector c;
  PFont font = createFont("Cantarell Light", 48);

  Button(String d, PVector e, PVector f) {
    a=d;
    b=e;
    c=f;
  }

  void Draw() {

    stroke(#403F3F);  
    fill(#676767);  
    rectMode(CORNER);
    rect(b.x, b.y, (width-60)/2-10, 50);

    fill(255);
    textFont(font);
    textSize(35);
    textAlign(CENTER);
    //text(a,30+((width-60)/2)/2,(height/3)+(width-60)/2+45);
    text(a, c.x, c.y);
  }
}
//---------------------------------------------------------------------------
class Layout {

  void Draw() {

    fill(0);
    strokeWeight(3);
    stroke(255);
    rectMode(CENTER);
    rect(width/2, height/3, width-60, width-60);
  }
}

//---------------------------------------------------------------------------

class textBox {

  PVector p ;

  textBox(PVector p)
  {
    this.p = p ;
  }

  void Draw() {
    stroke(0);  
    fill(#F7F5F5);  
    rectMode(CENTER);
    rect(p.x, p.y, (width-60), 50);
  }
}
