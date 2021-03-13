#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;long t;
long  y ;
long  yr ;
long x;
int ucm;
int ucmr;

#define LF 5
#define LB 6
#define RF 10
#define RB 9
int ule = 7;
int ure = 4;
int ult = 8;
int urt = 3;
int l = A0;
int r = A1;


void setup() {
  pinMode (LF, OUTPUT);
  pinMode (LB, OUTPUT);
  pinMode (RF, OUTPUT);
  pinMode (RB, OUTPUT);
  pinMode (l, INPUT);
  pinMode (r, INPUT);
  pinMode(ult, OUTPUT);
  pinMode(urt, OUTPUT);
  pinMode (ule, INPUT);
  pinMode(ure, INPUT);
  Serial.begin(9600);
   //laser
  //Serial.begin(115200);
    Wire.begin();
    Wire.setClock(400000); // use 400 kHz I2C
  
    sensor.setTimeout(500);
    if (!sensor.init())
    {
      Serial.println("Failed to detect and initialize sensor!");
      while (1);
    }
  
    sensor.setDistanceMode(VL53L1X::Long);
    sensor.setMeasurementTimingBudget(50000);
    sensor.startContinuous(50);

}

void loop()
{




  
  //IR
  int right = digitalRead(r);

  int left  = digitalRead(l);

  

  if (((left == 0) && (right == 0)))
  {
    //laser
int x = sensor.read();
  //Serial.println("x");
  //Serial.println(x);
 // if (sensor.timeoutOccurred()) 
  //{ Serial.print(" TIMEOUT"); 
 // }
    //Ultrasonic1
    digitalWrite(ult, LOW);
    delayMicroseconds(5);
    digitalWrite(ult, HIGH);
    delayMicroseconds(10);
    t = pulseIn(ule, HIGH);
    ucm = ((t / 2) / 29.1);
    y = constrain (ucm, 0, 26);
    // Serial.println("u1");
    //Serial.println(y);
    //
    //Ultrasonic2
    digitalWrite(urt, LOW);
    delayMicroseconds(5);
    digitalWrite(urt, HIGH);
    delayMicroseconds(10);
    t = pulseIn(ure, HIGH);
    ucmr = ((t / 2) / 29.1);
    yr = constrain (ucmr, 0, 26);
     //Serial.println("u2");
    //Serial.println(yr);

     if (x>50)
{

    //Serial.println("white");
    //UR
    if (((y >= 12) && (yr >= 12))&&((y<24)&&(yr<24)))
    {
      f();
      //Serial.println("orw");
    }
    else if  (((y < 12)  && ((yr > 3) && (yr < 22))) ||(y < 12))
    {
      ri();
      //Serial.println("right");
    }
    else if  (((yr < 12) && ((y > 3) && (y < 22)))||(yr < 12))
    {
      le();
      //Serial.println("let");
    }
    
    }
     else if (((x>= 10) && (x<=50)) &&((yr>24) && (y>24)))
    { 
           le();
           //delay(10);
    }
  }
 
  else if  ((((left == 1) && (right == 1))) || ((left == 1) ||  (right == 1)) )
  {
    
    s();
    delay(10);
    //Serial.println("top");
  }
}


//MOTION
void f()
{
  analogWrite(LF, 200);
  analogWrite(LB, 0);
  analogWrite(RF, 200);
  analogWrite(RB, 0); //forward
}
void b()
{
  analogWrite(LF, 0);
  analogWrite(LB, 255);
  analogWrite(RF, 0);
  analogWrite(RB, 255); //backward
}
void le()
{
  analogWrite(LF, 110);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(RB, 110); //left
}
void s()
{
  analogWrite(LF, 0);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(RB, 0); //stop
}

void ri()

{
  analogWrite(LF, 0);
  analogWrite(LB, 110);
  analogWrite(RF, 110);
  analogWrite(RB, 0); //right
}
//
