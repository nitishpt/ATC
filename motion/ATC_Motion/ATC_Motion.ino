int pwm_M2_mf=0; //speed of front motor
int pwm_M2_mb=150; //speed of back motor

int en_M2_mb = 11; //pin of front motor
int in1_M2_mb = 45;
int in2_M2_mb = 43;

int en_M2_mf = 10; //pin of back motor
int in1_M2_mf = 41;
int in2_M2_mf = 39;

int pwm_M3_ml=50; //speed of left motor
int pwm_M3_mr=50; //speed of right motor

int en_M3_ml = 13; //pin of left motor
int in1_M3_ml = 53;
int in2_M3_ml = 51;

int en_M3_mr = 12; //pin of right motor
int in1_M3_mr = 47;
int in2_M3_mr = 49;

int pwm_M4_m1 = 255; //speed of drum
int pwm_M4_m2 = 255; //speed of rack

int en_M4_m1 = 7; //pin of drum
int in1_M4_m1 = 27;
int in2_M4_m1 = 29;

int en_M4_m2 = 6; //pin of rack
int in1_M4_m2 = 23;
int in2_M4_m2 = 25;

int pwm_M1_pf = 0; //front pump
int pwm_M1_pb = 0; //back pump

int en_M1_pb = 9; //pin of front pump
int in1_M1_pb = 35;
int in2_M1_pb = 37;

int en_M1_pf = 8; //pin of back pump
int in1_M1_pf = 31;
int in2_M1_pf = 33;

const int trigPin_fl = 42;
const int echoPin_fl = 40;

const int trigPin_fr = 34;
const int echoPin_fr = 32;

const int trigPin_l = 42;
const int echoPin_l = 40;

const int trigPin_r = 44;
const int echoPin_r = 46;

const int trigPin_b = 50;
const int echoPin_b = 52;

#include <Encoder.h>

Encoder enc_X(5, 4);
Encoder enc_Y(3, 2);


void forward()
{
  Serial.println("forward");
  
  digitalWrite(in1_M3_ml, HIGH);
  digitalWrite(in2_M3_ml, LOW);
  
  analogWrite(en_M3_ml, pwm_M3_ml);
  
  digitalWrite(in1_M3_mr, HIGH);
  digitalWrite(in2_M3_mr, LOW);
  
  analogWrite(en_M3_mr, pwm_M3_mr);
}

void backward()
{
  Serial.println("backward");
  digitalWrite(in1_M3_ml, LOW);
  digitalWrite(in2_M3_ml, HIGH);
  
  analogWrite(en_M3_ml, pwm_M3_ml);
  
  digitalWrite(in1_M3_mr, LOW);
  digitalWrite(in2_M3_mr, HIGH);
  
  analogWrite(en_M3_mr, pwm_M3_mr);
}

void clockwise()
{
  Serial.println("clockwise");
  digitalWrite(in1_M3_ml, HIGH);
  digitalWrite(in2_M3_ml, LOW);
  
  analogWrite(en_M3_ml, 0);
  
  digitalWrite(in1_M3_mr, LOW);
  digitalWrite(in2_M3_mr, HIGH);
  
  analogWrite(en_M3_mr, 0);
}

void anticlockwise()
{
  Serial.println("anticlockwise");
  digitalWrite(in1_M3_ml, LOW);
  digitalWrite(in2_M3_ml, HIGH);
  
  analogWrite(en_M3_ml, 0);
  
  digitalWrite(in1_M3_mr, HIGH);
  digitalWrite(in2_M3_mr, LOW);
  
  analogWrite(en_M3_mr, 0);
}

void left()
{
  Serial.println("left");
  
  digitalWrite(in1_M2_mf, HIGH);
  digitalWrite(in2_M2_mf, LOW);
  
  analogWrite(en_M2_mf, pwm_M2_mf);
  
  digitalWrite(in1_M2_mb, HIGH);
  digitalWrite(in2_M2_mb, LOW);
  
  analogWrite(en_M2_mb, pwm_M2_mb);
}

void right()
{
  Serial.println("right");
  digitalWrite(in1_M2_mf, LOW);
  digitalWrite(in2_M2_mf, HIGH);
  
  analogWrite(en_M2_mf, pwm_M2_mf);
  
  digitalWrite(in1_M2_mb, LOW);
  digitalWrite(in2_M2_mb, HIGH);
  
  analogWrite(en_M2_mb, pwm_M2_mb);
}

void drum()
{
  Serial.println("drum");
  
  digitalWrite(in1_M4_m1, HIGH);
  digitalWrite(in2_M4_m1, LOW);
  
  analogWrite(en_M4_m1, pwm_M4_m1);
}

void front_pump()
{
  Serial.println("front_pump");
  
  digitalWrite(in1_M1_pf, HIGH);
  digitalWrite(in2_M1_pf, LOW);
  
  analogWrite(en_M1_pf, pwm_M1_pb);
}

void back_pump()
{
  Serial.println("back_pump");
  
  digitalWrite(in1_M1_pb, HIGH);
  digitalWrite(in2_M1_pb, LOW);
  
  analogWrite(en_M1_pb, pwm_M1_pb);
}

void stop_front_pump()
{
  Serial.println("stop_front");
  
  digitalWrite(in1_M1_pf, LOW);
  digitalWrite(in2_M1_pf, LOW);
}

void stop_back_pump()
{
  Serial.println("stop_back");
  
  digitalWrite(in1_M1_pb, LOW);
  digitalWrite(in2_M1_pb, LOW);
}

void rack()
{
  Serial.println("rack");
  analogWrite(en_M4_m2, pwm_M4_m2);
  
  digitalWrite(in1_M4_m2, HIGH);
  digitalWrite(in2_M4_m2, LOW);

  delay(3000);//////////////////////////////////////////////////////////NEED TOO BE CHECKED\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  
  digitalWrite(in1_M4_m2, LOW);
  digitalWrite(in2_M4_m2, LOW);

  front_pump();

  delay(15000);

  stop_front_pump();

  digitalWrite(in1_M4_m2, LOW);
  digitalWrite(in2_M4_m2, HIGH);

  delay(3000);
  
  digitalWrite(in1_M4_m2, LOW);
  digitalWrite(in2_M4_m2, LOW);
}

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

float imu()
{
  timer = millis();
  
  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  Serial.print(" Pitch = ");
  //Serial.print(pitch);
  
  Serial.print(" Roll = ");
  //Serial.println(roll);  
  
  Serial.print(" Yaw = ");
  //Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));

  return roll;
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

int ultrasonic(int trigPin, int echoPin)
{
  long duration, inches, cm;
  
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

   return cm;
}


long old_f  = -999;
long old_b = -999;

long encoder_f()
{
  long dist;
  long newPosition = enc_X.read();
  
  if (newPosition != old_f) 
  {
    old_f = newPosition;
    dist = (newPosition*3.142*6.8)/360;//6.8 cm = diameter of wheels.
  }
  return dist;
}

long encoder_b()
{
  long dist;
  long newPosition = enc_Y.read();
  
  if (newPosition != old_b) 
  {
    old_b = newPosition;
    dist = (newPosition*3.142*6.8)/360;//6.8 cm = diameter of wheels.
  }
  return dist;
}


void STOP()
{
  Serial.println("STOP");
  digitalWrite(in1_M3_ml, LOW);
  digitalWrite(in2_M3_ml, LOW);
    
  digitalWrite(in1_M3_mr, LOW);
  digitalWrite(in2_M3_mr, LOW);

  digitalWrite(in1_M2_mf, LOW);
  digitalWrite(in2_M2_mf, LOW);

  digitalWrite(in1_M2_mb, LOW);
  digitalWrite(in2_M2_mb, LOW);
  
}

void setup()
{
 Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  
  pinMode(in1_M1_pf, OUTPUT);
  pinMode(in2_M1_pf, OUTPUT);
  pinMode(en_M1_pf, OUTPUT);
  pinMode(in1_M1_pb, OUTPUT);
  pinMode(in2_M1_pb, OUTPUT);
  pinMode(en_M1_pb, OUTPUT);

  pinMode(in1_M2_mf, OUTPUT);
  pinMode(in2_M2_mf, OUTPUT);
  pinMode(en_M2_mf, OUTPUT);
  pinMode(in1_M2_mb, OUTPUT);
  pinMode(in2_M2_mb, OUTPUT);
  pinMode(en_M2_mb, OUTPUT);

  pinMode(in1_M3_ml, OUTPUT);
  pinMode(in2_M3_ml, OUTPUT);
  pinMode(en_M3_ml, OUTPUT);
  pinMode(in1_M3_mr, OUTPUT);
  pinMode(in2_M3_mr, OUTPUT);
  pinMode(en_M3_mr, OUTPUT);

  pinMode(in1_M4_m1, OUTPUT);
  pinMode(in2_M4_m1, OUTPUT);
  pinMode(en_M4_m1, OUTPUT);
  pinMode(in1_M4_m2, OUTPUT);
  pinMode(in2_M4_m2, OUTPUT);
  pinMode(en_M4_m2, OUTPUT);

  Serial.println("start");

  digitalWrite(8, HIGH);
  delay(1000);
}

int cases=-1;
long x0;
long y0;
char ch = 's';
int flag=0;


int wall_tol = 15;
int enc_tol = 20;
int roll_tol = 90;

void loop()
{
  drum();
  if(cases==-1)
  { 
    int val = ultrasonic(trigPin_l, echoPin_l);
    if(val>wall_tol)   //change value for left ultrasonic while calibrating
    {
      float roll_original = imu();
      anticlockwise();
      float roll_instantaneous = imu();
      while(roll_instantaneous-roll_original<roll_tol)
      {
        roll_instantaneous = imu();
      }
      STOP();
      long dist = encoder_f();
      backward();
      long dist2 = encoder_f();
      while(dist-dist2<10)          //distanc to move back in first case
      {
        dist2=encoder_f();
      }
      STOP();
      cases=1;
      x0 = encoder_f();
      y0 = encoder_b();
    }
    else
    {
      int tmp = ultrasonic(trigPin_fr, echoPin_fr);
      long dist = encoder_f();
      forward();
      while(tmp>wall_tol)
      {
        tmp = ultrasonic(trigPin_fr, echoPin_fr);
      }
      STOP();
      long dist2 = encoder_f();

      int temp = ultrasonic(trigPin_l, echoPin_l);
      if(temp<wall_tol)
      {
        backward();
        long dist3 = encoder_f();
        while(dist-dist3<enc_tol)
        {
          dist3 = encoder_f();
        }
        STOP();
        cases=2;
        x0 = encoder_f();
        y0 = encoder_b();
      }
      else
      {
        int roll_original = imu();
        clockwise();
        int roll_instantaneous = imu();
        while(roll_instantaneous-roll_original<roll_tol)
        {
          roll_instantaneous = imu();
        }
        STOP();
        cases=3;
        x0 = encoder_f();
        y0 = encoder_b();      
      }
    }
  }

  int ip = Serial.read();

  if(ip=='1')
  {
    STOP();
    ch='s';
    back_pump();
    delay(5000);
    stop_back_pump();
  }
  if(ip=='5')
  {
    flag=1;
  }

  //main code
  if(case!=-1)
    {
    int val_ultra = ultrasonic(trigPin_fr, echoPin_fr);
    /*int val_ultra_l = ultrasonic(trigPin_fl, echoPin_fl);
    int val_ultra;
    if(val_ultra_l<val_ultra_r)
    {
      val_ultra = val_ultra_l;
    }
    else
    {
      val_ultra = val_ultra_r;
    }*/
    if(ch=='s')
    {
      forward();
      ch='f';
    }
    if(val_ultra<wall_tol)
    {
      STOP();
      if(flag==1)
      {
        rack();
        flag=0;
      }
      ch='s';
    }
  
    int val_encoder_f = encoder_f();
    if(ch=='s')
    {
      backward();
      ch='b';
    }
    int val_ultra_b = ultrasonic(trigPin_b, echoPin_b);
    if(val_encoder_f-x0<enc_tol&&ch=='b'&&val_ultra_b<wall_tol)
    {
      STOP();
      ch='s';
    }
  
    int val_encoder_b = encoder_b();
    right();
    int val_enc_b_new = encoder_b();
    int ultra_r = ultrasonic(trigPin_r, echoPin_r);
    while(val_enc_b_new-val_encoder_b<enc_tol&&ultra_r>wall_tol&&val_enc_b_new-y0<100&&flag==0)
    {
      val_enc_b_new=encoder_b();
      ultra_r = ultrasonic(trigPin_r, echoPin_r);
    }
    STOP();
    ch='s';  
  }
}
