/*
 Example sketch for the PS4 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS4BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the PS4BT class in two ways */
// This will start an inquiry and then pair with the PS4 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS4 controller will then start to blink rapidly indicating that it is in pairing mode
//PS4BT PS4(&Btd, PAIR);

// After that you can simply create the instance like so and then press the PS button on the device
PS4BT PS4(&Btd);
int in1 = 30;
int in2 = 31;
int eA = 6;
int flag = 2;
int blag = 3;
int frag = 4;
int brag = 5;
int fl1 = 22;
int fl2 = 23;
int bl1 = 24;
int bl2 = 25;
int fr1 = 26;
int fr2 = 27;
int br1 = 28;
int br2 = 29;
void forward(){
  digitalWrite(fl1,HIGH);
  digitalWrite(fl2,LOW);
  digitalWrite(bl1,HIGH);
  digitalWrite(bl2,LOW);
  digitalWrite(fr1,HIGH);
  digitalWrite(fr2,LOW);
  digitalWrite(br1,HIGH);
  digitalWrite(br2,LOW);

//  analogWrite(flag,255);
//  analogWrite(blag,255);
//  analogWrite(frag,255);
//  analogWrite(brag,255);
  
  
}
void backward(){
  digitalWrite(fl2,HIGH);
  digitalWrite(fl1,LOW);
  digitalWrite(bl2,HIGH);
  digitalWrite(bl1,LOW);
  digitalWrite(fr2,HIGH);
  digitalWrite(fr1,LOW);
  digitalWrite(br2,HIGH);
  digitalWrite(br1,LOW);

//  analogWrite(flag,255);
//  analogWrite(blag,255);
//  analogWrite(frag,255);
//  analogWrite(brag,255);
  
  
}
void right(){
  digitalWrite(fl1,HIGH);
  digitalWrite(fl2,LOW);
  digitalWrite(bl2,HIGH);
  digitalWrite(bl1,LOW);
  digitalWrite(fr2,HIGH);
  digitalWrite(fr1,LOW);
  digitalWrite(br1,HIGH);
  digitalWrite(br2,LOW);

//  analogWrite(flag,255);
//  analogWrite(blag,255);
//  analogWrite(frag,255);
//  analogWrite(brag,255);
  
  
}
void left(){
  digitalWrite(fl2,HIGH);
  digitalWrite(fl1,LOW);
  digitalWrite(bl1,HIGH);
  digitalWrite(bl2,LOW);
  digitalWrite(fr1,HIGH);
  digitalWrite(fr2,LOW);
  digitalWrite(br2,HIGH);
  digitalWrite(br1,LOW);

//  analogWrite(flag,255);
//  analogWrite(blag,255);
//  analogWrite(frag,255);
//  analogWrite(brag,255);
  
  
}
void stop1(){
  analogWrite(flag,0);
  analogWrite(blag,0);
  analogWrite(frag,0);
  analogWrite(brag,0);
}
void grip(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(eA,255);
  //delay(2000);
  // now turn off motors
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);
}
void release1(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(eA,255);
  //delay(2000);
  // now turn off motors
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);
}
void stop2(){
  analogWrite(eA,0);
  analogWrite(eA,0);
}
bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void setup() {
  Serial.begin(115200);
  pinMode(flag,OUTPUT);
  pinMode(frag,OUTPUT);
  pinMode(brag,OUTPUT);
  pinMode(blag,OUTPUT);
  pinMode(fl1,OUTPUT);
  pinMode(fl2,OUTPUT);
  pinMode(bl1,OUTPUT);
  pinMode(bl2,OUTPUT);
  pinMode(fr1,OUTPUT);
  pinMode(fr2,OUTPUT);
  pinMode(br1,OUTPUT);
  pinMode(br2,OUTPUT);
  
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();

  if (PS4.connected()) {
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS4.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS4.getAnalogHat(LeftHatY));
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS4.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS4.getAnalogHat(RightHatY));
    }

    if(PS4.getAnalogHat(LeftHatY)<120){
      forward();
      analogWrite(flag,255-PS4.getAnalogHat(LeftHatY));
      analogWrite(blag,255-PS4.getAnalogHat(LeftHatY));
      analogWrite(frag,255-PS4.getAnalogHat(LeftHatY));
      analogWrite(brag,255-PS4.getAnalogHat(LeftHatY));
      
    }
    else if(PS4.getAnalogHat(LeftHatY)>140){
      backward();
      analogWrite(flag,PS4.getAnalogHat(LeftHatY));
      analogWrite(blag,PS4.getAnalogHat(LeftHatY));
      analogWrite(frag,PS4.getAnalogHat(LeftHatY));
      analogWrite(brag,PS4.getAnalogHat(LeftHatY));
    }
    else if(PS4.getAnalogHat(RightHatX)<120){
      left();
      analogWrite(flag,255-PS4.getAnalogHat(RightHatX));
      analogWrite(blag,255-PS4.getAnalogHat(RightHatX));
      analogWrite(frag,255-PS4.getAnalogHat(RightHatX));
      analogWrite(brag,255-PS4.getAnalogHat(RightHatX));
      
    }
    else if(PS4.getAnalogHat(RightHatX)>140){
      right();
      analogWrite(flag,PS4.getAnalogHat(RightHatX));
      analogWrite(blag,PS4.getAnalogHat(RightHatX));
      analogWrite(frag,PS4.getAnalogHat(RightHatX));
      analogWrite(brag,PS4.getAnalogHat(RightHatX));
    }
    
    else{
      stop1();
    }

    if (PS4.getAnalogButton(L2) || PS4.getAnalogButton(R2)) { // These are the only analog buttons on the PS4 controller
      Serial.print(F("\r\nL2: "));
      Serial.print(PS4.getAnalogButton(L2));
      Serial.print(F("\tR2: "));
      Serial.print(PS4.getAnalogButton(R2));
    }
    if (PS4.getAnalogButton(L2) != oldL2Value || PS4.getAnalogButton(R2) != oldR2Value) // Only write value if it's different
      PS4.setRumbleOn(PS4.getAnalogButton(L2), PS4.getAnalogButton(R2));
    oldL2Value = PS4.getAnalogButton(L2);
    oldR2Value = PS4.getAnalogButton(R2);

    if (PS4.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS4.disconnect();
    }
    else {
      if (PS4.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTraingle"));
        PS4.setRumbleOn(RumbleLow);
      }
      if (PS4.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS4.setRumbleOn(RumbleHigh);
      }
      if (PS4.getButtonClick(CROSS)) {
        stop1();
        //stop2();
        Serial.print(F("\r\nCross"));

        PS4.setLedFlash(10, 10); // Set it to blink rapidly
      }
      if (PS4.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS4.setLedFlash(0, 0); // Turn off blinking
      }

      if (PS4.getButtonClick(UP)) {
        forward();
        Serial.print(F("\r\nUp"));
        PS4.setLed(Red);
      } if (PS4.getButtonClick(RIGHT)) {
        right();
        Serial.print(F("\r\nRight"));
        PS4.setLed(Blue);
      } if (PS4.getButtonClick(DOWN)) {
        backward();
        Serial.print(F("\r\nDown"));
        PS4.setLed(Yellow);
      } if (PS4.getButtonClick(LEFT)) {
        left();
        Serial.print(F("\r\nLeft"));
        PS4.setLed(Green);
      }

      if (PS4.getButtonClick(L1)){
        grip();
        Serial.print(F("\r\nL1"));
       }
      if (PS4.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (PS4.getButtonClick(R1)){
        release1();
        Serial.print(F("\r\nR1"));
      }
      if (PS4.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS4.getButtonClick(SHARE))
        Serial.print(F("\r\nShare"));
      if (PS4.getButtonClick(OPTIONS)) {
        Serial.print(F("\r\nOptions"));
        printAngle = !printAngle;
      }
      if (PS4.getButtonClick(TOUCHPAD)) {
        Serial.print(F("\r\nTouchpad"));
        printTouch = !printTouch;
      }

      if (printAngle) { // Print angle calculated using the accelerometer only
        Serial.print(F("\r\nPitch: "));
        Serial.print(PS4.getAngle(Pitch));
        Serial.print(F("\tRoll: "));
        Serial.print(PS4.getAngle(Roll));
      }

      if (printTouch) { // Print the x, y coordinates of the touchpad
        if (PS4.isTouching(0) || PS4.isTouching(1)) // Print newline and carriage return if any of the fingers are touching the touchpad
          Serial.print(F("\r\n"));
        for (uint8_t i = 0; i < 2; i++) { // The touchpad track two fingers
          if (PS4.isTouching(i)) { // Print the position of the finger if it is touching the touchpad
            Serial.print(F("X")); Serial.print(i + 1); Serial.print(F(": "));
            Serial.print(PS4.getX(i));
            Serial.print(F("\tY")); Serial.print(i + 1); Serial.print(F(": "));
            Serial.print(PS4.getY(i));
            Serial.print(F("\t"));
          }
        }
      }
    }
  }
}
