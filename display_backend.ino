#include <UTFT.h> 
#include <UTouch.h>

UTouch  myTouch( 6, 5, 4, 3, 2);
UTFT    myGLCD(SSD1289,38,39,40,41); //Parameters should be adjusted to your Display/Schield model
int sensorPin = A7;    // select the input pin for the potentiometer
int x, y ;

//data sensor current
int sensorValue;
long CurrentSensor; 

//option text
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

char currentPage;
char buttonCon;

//output relay
int maju =8;
int mundur =9;
int manual =10;

void setup() {
Serial.begin(9600);

 myGLCD.InitLCD();
 myGLCD.clrScr();
 myTouch.InitTouch();
 myTouch.setPrecision(PREC_MEDIUM);

// Defining Pin Modes
  pinMode(maju, OUTPUT); 
  pinMode(mundur, OUTPUT); 
  pinMode(manual, OUTPUT); 
  
 autoScreen() ;
 currentPage = '0'; // Indicates that we are at Home Screen
 buttonCon = '0';

  digitalWrite(maju, LOW); 
  digitalWrite(mundur, LOW); 
  digitalWrite(manual, LOW);
}

void loop() {
CurrentSensor=analogRead (sensorPin);
Serial.println(CurrentSensor);
delay (1000);
sensorData();
if (currentPage =='0') {
 if (myTouch.dataAvailable()){
  myTouch.read();
  x=myTouch.getX(); // X coordinate where the screen has been pressed
  y=myTouch.getY(); // Y coordinates where the screen has been pressed
 //if the manual pressed
 if ((x>=0) && (x<=120) && (y>=0) && (y<=25)) {
        drawFrame(0, 0, 120, 25); // Custom Function -Highlighs the buttons when it's pressed
        currentPage = '1'; // Indicates that we are the first example
        myGLCD.clrScr(); // Clears the screen
        manualScreen();
        }
 //if button start pressed
   if ((x>=111) && (x<=209) && (y>=111) && (y<=209)){
  drawFrameCircle(160, 160, 55);
  currentPage ='2';
  buttonScreen();
   }
  }
  //relay condition
   digitalWrite(maju,HIGH);
   digitalWrite(mundur,HIGH);
   digitalWrite(manual,HIGH);
 }

 if (currentPage =='1'){
  if (myTouch.dataAvailable()){
  myTouch.read();
  x=myTouch.getX(); // X coordinate where the screen has been pressed
  y=myTouch.getY(); // Y coordinates where the screen has been pressed
  if ((x>=220) && (x<=319) && (y>=1) && (y<=25)){
    drawFrame(220, 1, 319, 25);
    myGLCD.clrScr();
    autoScreen();
    currentPage='0';
    }
   }
 //relay condition
   digitalWrite(maju,HIGH);
   digitalWrite(mundur,HIGH);
   digitalWrite(manual,LOW);
 }

 if (currentPage =='2'){ //if button change to STOP 
  if (myTouch.dataAvailable()){
  myTouch.read();
  x=myTouch.getX(); // X coordinate where the screen has been pressed
  y=myTouch.getY(); // Y coordinates where the screen has been pressed
  //if button STOP pressed
  if ((x>=111) && (x<=209) && (y>=111) && (y<=209)){
    drawFrameCircle(160, 160, 55);
    autoScreen();
    currentPage='0';
  }
  //manual bttuon pressed
 if ((x>=0) && (x<=120) && (y>=0) && (y<=25)) {
        drawFrame(0, 0, 120, 25); // Custom Function -Highlighs the buttons when it's pressed
        currentPage = '1'; // Indicates that we are the first example
        myGLCD.clrScr(); // Clears the screen
        manualScreen();
        digitalWrite(maju,HIGH);
        digitalWrite(mundur,HIGH);
        }
 }
  if ((CurrentSensor>=0) && (CurrentSensor<=500)){
     digitalWrite(mundur,HIGH);
     digitalWrite(maju,LOW);
  }
  else if((CurrentSensor>=501) &&(CurrentSensor<=1023)){
    digitalWrite(mundur,LOW);
    digitalWrite(maju,HIGH);
    delay(3000);
  }
 }
}

void autoScreen() {
  // Title
  myGLCD.setBackColor(0,0,0); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("AUTO MODE", CENTER, 45); // Prints the string on the screen
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,75,319,75); // Draws the red line
 // myGLCD.setColor(255, 255, 255); // Sets color to white
 // myGLCD.setFont(SmallFont); // Sets the font to small
  //myGLCD.print("FTMD ITB", 240,4); // Prints the string
  myGLCD.setColor(16, 167, 103); // Sets green color
  myGLCD.fillCircle (160, 160, 55); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawCircle (160, 160, 55); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("START", CENTER, 152); // Prints the string
//software version
  myGLCD.setBackColor(0,0,0);
  myGLCD.setColor(255,255,255);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Vr 1.0", 270,225);
//manual text
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (0, 0, 120, 25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (0, 0, 120, 25);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<Manual", 2,6);
  }

 //start button scree
  void buttonScreen(){
  myGLCD.setColor(255, 0, 0); // Sets green color
  myGLCD.fillCircle (160, 160, 55); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawCircle (160, 160, 55); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(255, 0, 0); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("STOP", CENTER, 152); // Prints the string
  }
 //manualscren
 void manualScreen(){
  myGLCD.setBackColor(0,0,0); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("MANUAL MODE", CENTER, 45); // Prints the string on the screen
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,75,319,75); // Draws the red line
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (220, 1, 319, 25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (220, 1, 319, 25);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("AUTO>", 230,6);
  // inform text
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(SmallFont); // Sets the font to big
  myGLCD.setBackColor(0,0,0); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("You're in manual mode", CENTER, 142); // Prints the string
  myGLCD.print("use manual control to handling ", CENTER, 162); // Prints the string
 }
 void sensorData(){
 
  myGLCD.setBackColor(0,0,0);
  myGLCD.setColor(255,255,255);
  myGLCD.setFont(SmallFont);
  myGLCD.print("crnt(mA):",0,225);
  myGLCD.setBackColor(0,0,0);
  myGLCD.setColor(255,255,255);
  myGLCD.setFont(SmallFont);
  myGLCD.print("     ",75,225);
  delay(100);
  myGLCD.printNumI((CurrentSensor),75,225);
  myGLCD.print("rot:",0,215);
}
 

// Highlights the button when pressed
void drawFrame(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (x1, y1, x2, y2);
}

void drawFrameCircle(int x, int y, int r) {
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawCircle (x, y, r);
  while (myTouch.dataAvailable())
    myTouch.read();
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawCircle (x,y,r);
}
