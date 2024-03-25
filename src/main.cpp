#include <Arduino.h>
int RPWM1 = 7;
int LPWM1 = 6;
int RPWM = 8;
int LPWM = 9;
int IRT = 2;
int IRS = 3;
int trig1 = 10;
int echo1 = 11;
int trig2 = 12;
int echo2 = 13;
int valIRT;
int valIRS;
unsigned long duration1, duration2;
int scan = 0;
int distance1;
int distance2;

void FORWARD()
{
  Serial.println("Tien");
  analogWrite(LPWM, 30);
  analogWrite(LPWM1, 30);
  analogWrite(RPWM, 0);
  analogWrite(RPWM1, 0);
}

void BACKWARD()
{
  Serial.println("Lui");
  analogWrite(LPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM, 30);
  analogWrite(RPWM1, 30);
}

void Stop()
{
  Serial.println("Dung");
  analogWrite(LPWM, 0);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 0);
}

void Spin120()
{
  Serial.println("120 do");
  analogWrite(LPWM, 80);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 60);
}
void proval()
{
  valIRT = digitalRead(IRT);
  valIRS = digitalRead(IRS);

  if (valIRT == 0)
  {
    Stop();
    delay(100);
    BACKWARD();
    delay(1500);
    Spin120();
    BACKWARD();
    delay(500);
    search();
  }
  else if (valIRS == 0)
  {
    Stop();
    delay(100);
    FORWARD();
    delay(1500);
    Spin120();
    delay(500);
    search();
  }
}
void search()
{

  if (distance1 <= 25)
  {
    Serial.println("hulk1");
    analogWrite(LPWM, 80);
    analogWrite(RPWM, 0);
    analogWrite(LPWM1, 80);
    analogWrite(RPWM1, 0);
    delay(10000);
  }
  else if (distance2 <= 25)
  {
    Serial.println("hulk2");
    analogWrite(LPWM, 80);
    analogWrite(RPWM, 0);
    analogWrite(LPWM1, 80);
    analogWrite(RPWM1, 0);
    delay(10000);
  }
  else
  {
    if (scan < 3)
    {
      analogWrite(RPWM, 50);
      analogWrite(LPWM, 0);
      analogWrite(RPWM1, 0);
      analogWrite(LPWM1, 30);
    }
    else if (scan <= 7)
    {
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 50);
      analogWrite(RPWM1, 30);
      analogWrite(LPWM1, 0);
    }
    if (scan < 7)
    {
      scan += 1;
    }
    else if (scan == 7)
    {
      scan = 0;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  delay(1000);
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(IRT, INPUT);
  pinMode(IRS, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  attachInterrupt(0, proval, CHANGE);
  attachInterrupt(1, proval, CHANGE);
}

void loop()
{
  // IR
  valIRT = digitalRead(IRT);
  Serial.print("IR truoc: ");
  Serial.println(valIRT);
  valIRS = digitalRead(IRS);
  Serial.print("IR sau: ");
  Serial.println(valIRS);
  // SR04
  digitalWrite(trig1, 0);
  delayMicroseconds(2);
  digitalWrite(trig1, 1);
  delayMicroseconds(5);
  digitalWrite(trig1, 0);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = int(duration1 / 2 / 29.412);
  digitalWrite(trig2, 0);
  delayMicroseconds(2);
  digitalWrite(trig2, 1);
  delayMicroseconds(5);
  digitalWrite(trig2, 0);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = int(duration2 / 2 / 29.412);

  Serial.print(distance1);
  Serial.println("cm");
  Serial.print(distance2);
  Serial.println("cm");
  search();
  delay(1000);
}
