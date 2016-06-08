#include <Aldi_NeoPixel.h>
#include <PressurePlate.h>
#include <TimerOne.h>

//*********************************
//** Pin number definitions: ******
//*********************************
#define pressurePlate1 9
#define pressurePlate2 10
#define ledStripPin 6
#define numPixelsPerPlate 16
#define numPixelsSide 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Aldi_NeoPixel strip = Aldi_NeoPixel(32, ledStripPin, NEO_BRG + NEO_KHZ800);
PressurePlate pressurePlateObj1 = PressurePlate(30); //30 seconds;
PressurePlate pressurePlateObj2 = PressurePlate(60); //60 seconds;
String state; //Initialize current state.
int animationCounter, animationId, plate1PixelsOn, plate2PixelsOn, plate1Counter, plate2Counter, plate1Id, plate2Id;
bool lock;

void setup() {
  //Setting pinModes:
  pinMode(pressurePlate1, INPUT);
  pinMode(pressurePlate2, INPUT);
  pinMode(ledStripPin, OUTPUT);
  //Initializing ledstip:
  strip.begin();
  strip.show();
  resetLedStrip();
  //Setting timer:
  Timer1.initialize(); //Updates every second.
  Timer1.attachInterrupt(timerEvent);
  //Enabling serial:
  Serial.begin(9600);
  //Intitialize variables:
  state = "Start";
}

void loop() {
  // yes polling beacause interrupts need bigger schematic with a pull up switch.
  pollPressurePlates();
  if(state == "Start") 
    startUpEffect();
  if(pressurePlateObj1.IsReady()) {
    if(plate1Counter < 255) {
        if(plate1Id%2 == 0)
          setPixels(0,numPixelsPerPlate,0,255-plate1Counter,0);
        else
          setPixels(0,numPixelsPerPlate,0,plate1Counter,0);
        plate1Counter+=2;
      } 
      else {
        plate1Counter = 0;
        plate1Id++;
      }
  }  
  if(pressurePlateObj2.IsReady()) {
    if(plate2Counter < 255) {
        if(plate2Id%2 == 0)
          setPixels(numPixelsPerPlate,numPixelsPerPlate*2,0,255-plate2Counter,255-plate2Counter);
        else
          setPixels(numPixelsPerPlate,numPixelsPerPlate*2,0,plate2Counter,plate2Counter);
         plate2Counter+=2;
      } 
      else {
        plate2Counter = 0;
        plate2Id++;
      }
  }
    
 
  
  animationCounter+=2;
  delay(10);
  //resetLedStrip();
}

//Triggered when serial communication is present.
void serialEvent() {
  while (Serial.available()) {
     String word = "";
     while(Serial.available() > 0) {
       char letter = Serial.read();
        word += letter;
        delay(3); 
     }
     handleSerialEvent(word);
  }
}

void handleSerialEvent(String word) {
  String command = word.substring(0,3);
  if(command.equals("EGM")) { //Enable game modus:
    state = "Game";
    pressurePlateObj1.Reset();
    pressurePlateObj2.Reset();
    plate1PixelsOn = 0;
    plate2PixelsOn = 0;
    plate1Counter = 0;
    plate2Counter = 0;
    plate1Id = 0;
    plate2Id = 0;
    lock = false;
  }
  else if(command.equals("ESM")) { //Enable start modus:
    animationCounter = 0;
    animationId = 0;
    state = "Start";
  }
}

void pollPressurePlates() {
  if(digitalRead(pressurePlate1) && pressurePlateObj1.IsReady()) {
    Serial.println("PP1");
    for(int value = 0; value <= 255; value+=2) {
      for(int pixel = 0; pixel < numPixelsPerPlate; pixel++)
        strip.setPixelColor(pixel, strip.Color(value,value,value));
      strip.show();
      delay(1);
    }
    for(int value = 255; value > 0; value-=2) {
      for(int pixel = 0; pixel < numPixelsPerPlate; pixel++)
        strip.setPixelColor(pixel, strip.Color(value,value,value));
      strip.show();
      delay(1);
    }
    for(int pixel = 0; pixel < numPixelsPerPlate; pixel++)
      strip.setPixelColor(pixel,strip.Color(0,0,0)); 
    pressurePlateObj1.Reset();
    plate1PixelsOn = 0;  
  }
  if(digitalRead(pressurePlate2) && pressurePlateObj2.IsReady()) {
    Serial.println("PP2");
    for(int value = 0; value <= 255; value+=2) {
      for(int pixel = numPixelsPerPlate; pixel < numPixelsPerPlate*2; pixel++)
        strip.setPixelColor(pixel, strip.Color(value,value,value));
      strip.show();
      delay(1);
    }
    for(int value = 255; value > 0; value-=2) {
      for(int pixel = numPixelsPerPlate; pixel < numPixelsPerPlate*2; pixel++)
        strip.setPixelColor(pixel, strip.Color(value,value,value));
      strip.show();
      delay(1);
    }
    for(int pixel = numPixelsPerPlate; pixel < numPixelsPerPlate*2; pixel++)
      strip.setPixelColor(pixel,strip.Color(0,0,0));  
    pressurePlateObj2.Reset();
    plate2PixelsOn = 0;
  }
}

void timerEvent() {
  if(state.equals("Game")) {
    //Updating pressureplate counters:
    pressurePlateObj1.Update();
    pressurePlateObj2.Update();
    updateLoading();
  }
}

void resetLedStrip() {
  for(int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.show();
  }
}

void resetLedStrip(int startPixel, int endPixel) {
  for(int pixel = startPixel; pixel < endPixel; pixel++)
    strip.setPixelColor(pixel, strip.Color(0,0,0)); 
  //strip.show();
}

void startUpEffect() {
    if(animationCounter < 255) {
      if(animationId%2 == 0)
        executeStartEffect(animationCounter);
      else
        executeStartEffect(255-animationCounter);
    }
    else {
      animationCounter = 0;
      animationId++;
    }
}

void executeStartEffect(int x) {
  for(int i = 0; i < numPixelsSide; i++) 
    strip.setPixelColor(i, strip.Color(0,0,x));
  for(int i = numPixelsSide; i < numPixelsSide*2; i++) 
    strip.setPixelColor(i, strip.Color(0,x,x));
  for(int i = numPixelsSide*2; i < numPixelsSide*3; i++) 
    strip.setPixelColor(i, strip.Color(x,x,0));
  for(int i = numPixelsSide*3; i < numPixelsSide*4; i++) 
    strip.setPixelColor(i, strip.Color(x,0,0));
  for(int i = numPixelsSide*4; i < numPixelsSide*5; i++) 
    strip.setPixelColor(i, strip.Color(0,0,x));
  for(int i = numPixelsSide*5; i < numPixelsSide*6; i++) 
    strip.setPixelColor(i, strip.Color(0,x,x));
  for(int i = numPixelsSide*6; i < numPixelsSide*7; i++) 
    strip.setPixelColor(i, strip.Color(x,x,0));
  for(int i = numPixelsSide*7; i < numPixelsSide*8; i++) 
    strip.setPixelColor(i, strip.Color(x,0,0));
  strip.show();
}

void updateLoading() {
  if(!lock) {
    lock = true;
    //PressurePlate 1:
    if(!pressurePlateObj1.IsReady()) {
      int offset =  ((float)pressurePlateObj1.GetThreshold()/(float)numPixelsPerPlate)+0.5;
      int numOfPixelsOn = pressurePlateObj1.GetCount()/offset;
      if(plate1PixelsOn <= numOfPixelsOn) {
        resetLedStrip(0,numPixelsPerPlate);
        setPixels(0, numOfPixelsOn,0,255,0);
        for(int x = 0; x <= 255; x++) {
          strip.setPixelColor(numOfPixelsOn,strip.Color(0,x,0));
          strip.show();
          delay(1);
       }
          plate1PixelsOn++;
      }
    }
    //PressurePlate2: 
    if(!pressurePlateObj2.IsReady()) {
      int offset =  ((float)pressurePlateObj2.GetThreshold()/(float)numPixelsPerPlate)+0.5;
      int numOfPixelsOn = pressurePlateObj2.GetCount()/offset;
      if(plate2PixelsOn <= numOfPixelsOn) {
        resetLedStrip(numPixelsPerPlate,numPixelsPerPlate*2);
        setPixels(numPixelsPerPlate, numPixelsPerPlate+numOfPixelsOn,0,255,255);
        for(int x = 0; x <= 255; x++) {
          strip.setPixelColor(numPixelsPerPlate+numOfPixelsOn,strip.Color(0,x,x));
          strip.show();
          delay(1);
        }
        plate2PixelsOn++;
      }
    }
    lock = false;
  }
}

void setPixels(int startPixel, int endPixel, int r, int g, int b) {
  for(int pixel = startPixel; pixel < endPixel; pixel++)
    strip.setPixelColor(pixel,strip.Color(r,g,b));
  strip.show();
}



