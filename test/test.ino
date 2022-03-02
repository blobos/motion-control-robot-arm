
//servo
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>
#include <Stepper.h>

MPU6050 imu(Wire);

//servo
int handPin = 9, wristPin = 6, elbowPin = 5, shoulderPin = 3;
Servo hand, wrist, elbow, shoulder;

float handAngle, wristAngle, elbowAngle, shoulderAngle;
//joystick

#define joyX A0 // x 0 to button 15 away 
#define joyY A1 // y 0 back, 15 forward

//stepper
#define IN1 10
#define IN2 11
#define IN3 12
#define IN4 13
Stepper baseStepper = Stepper(2038, 10, 12, 11, 13);
int gyroY, stepCount;

 
void setup() {
  Serial.begin(115200);
//gyro
  Wire.begin();
  imu.begin();
  imu.calcGyroOffsets(true);

//servo
  hand.attach(handPin, 510, 2600);
  wrist.attach(wristPin, 510, 2600);
  elbow.attach(elbowPin, 510, 2600);
  shoulder.attach(shoulderPin, 510, 2600);
  handAngle = 0, wristAngle = 0, elbowAngle = 0, shoulderAngle = 0;
  shoulder.write(shoulderAngle);
  elbow.write(elbowAngle);

//Stepper  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  baseStepper.setSpeed(5);
  int stepCount = 0;
}
 
void loop() {
// HAND
int xValue = analogRead(joyX);
if (xValue < 250){
  if (handAngle >1){
  handAngle --;
  hand.write(handAngle);
  delay(10);}}
  else if(xValue > 850){
    if (handAngle <140){
    handAngle++;
    hand.write(handAngle);
    delay(10);}}
    
//   Serial.print("Joystick X: ");
//   Serial.print(xValue);
//   Serial.print("\t");
//   Serial.print("Map: ");
//   Serial.print(handAngle);
//   Serial.print("\t Servoread ");
//   Serial.println(hand.read());

//wrist
int yValue = analogRead(joyY);
if (yValue < 250){
  if (wristAngle >1){
  wristAngle --;
  wrist.write(wristAngle);
  delay(10);}}
  else if(yValue > 850){
    if (wristAngle <180){
    wristAngle++;
    wrist.write(wristAngle);
    delay(10);}}

//   Serial.print("Joystick Y: ");
//   Serial.print(yValue);
//   Serial.print("\t");
//   Serial.print("Map: ");
//   Serial.print(wristAngle);
//   Serial.print("\t Servoread ");
//   Serial.println(wrist.read());

//SHOULDER & ELBOW
  imu.update();
  

//  Serial.print(", elbow Angle: ");
//  Serial.print(elbow.read());
  

//elbow is inverse of shoulder.  
  shoulderAngle = map(imu.getAngleX(), 40, -40, -1, 1);
  elbowAngle = map(imu.getAngleX(), 40,-40 , 1, -1);
  if (abs(imu.getAngleX()) > 10){

  shoulderAngle = shoulderAngle + shoulder.read();
  shoulder.write(shoulderAngle = constrain (shoulderAngle, 0, 150)); 

//  Serial.print("Rotation Angle: X: ");
//  Serial.print(imu.getAngleX());
//  Serial.print(", shoulder increment");
//  Serial.print(shoulderAngle);
//  Serial.print(", Shoulder Servo Position: ");
//  Serial.println(shoulder.read());

  elbowAngle = elbowAngle + elbow.read();
  elbow.write(elbowAngle = constrain (shoulderAngle, 10, 120));
  delay(10);
 }
  


//Base Stepper 
  
  gyroY=imu.getAngleY();
//  Serial.print("Steps: ");
//  Serial.print(stepCount);
//  Serial.print(" Gyro:");
//  Serial.println(gyroY);

  
  if((gyroY) > 15){
      baseStepper.step(-1);  
      stepCount--;
    }
    else if(gyroY < -15){
      baseStepper.step(1);
      stepCount++;
    }
    else {
      baseStepper.step(0);
      }
}
