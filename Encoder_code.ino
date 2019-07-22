int encoderPin1 = 2;
int encoderPin2 = 3;
 
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
 
long lastencoderValue = 0;
 
int lastMSB = 0;
int lastLSB = 0;

int motion=0;

volatile long newposition;
volatile long oldposition = 0;
unsigned long newtime;
unsigned long oldtime = 0;
int vel;

void setup() {
  Serial.begin (9600);
 
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
 
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
 
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
 
}
double angle,ang;
int rot;
void loop(){ 
  //Do stuff here
  angle=encoderValue/4000.0*360;
  rot=(int)(angle/360);
  ang=((int)(angle))%360;
  Serial.print("EncoderValue : ");
  Serial.print(encoderValue);
  Serial.print("\t No. of rotations : ");
  Serial.print(rot);
  Serial.print("\t Angle : ");
  Serial.print(ang);
  

  newposition = encoderValue ;
  newtime = millis();
  vel = 60.0*(newposition-oldposition) /(4.0*(newtime-oldtime));
  Serial.print ("\t speed = ");
  Serial.print (abs(vel));
  Serial.print("rpm");
  oldposition = newposition;
  oldtime = newtime;

  if(motion==-1) Serial.print("\t CLOCKWISE");
  else if(motion==1) Serial.print("\t ANTICLOCKWISE");
  else   Serial.print("\t REST");

  Serial.println();
  
  motion=0;
  delay(1000); //just here to slow down the output, and show it will work  even during a delay
}
 
 
void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  motion=0;
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011){ encoderValue ++;  motion=1;}
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000){ encoderValue --;  motion=-1;}
 
  lastEncoded = encoded; //store this value for next time
}
