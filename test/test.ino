#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>
#include <Stepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

Stepper baseStepper = Stepper(2038, 8, 10, 9, 11);

Servo servoBase;
MPU6050 imu(Wire);
int servoPin = 6;
float baseRotate,prevBaseRotate,baseAngle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  imu.begin();
  imu.calcGyroOffsets(true);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  baseStepper.setSpeed(15); //max speed to 15
  
  servoBase.attach(servoPin, 510, 2600);
  servoBase.write(0);
  baseAngle = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  imu.update();
  
//  Serial.println("");
  

  Serial.print("Rotation Angle: X: ");
  Serial.print(imu.getAngleX());
  Serial.print(", Base Angle: ");
  Serial.println(servoBase.read());
  
//  Serial.print("Rotation Angle: Z: ");
//  Serial.print(imu.getAngleZ());
//  Serial.print(", Base Angle: ");
//  Serial.println("stepper");
  

 //Base Servo
 
 baseAngle = 0;
 baseAngle = map(imu.getAngleX(), -40, 40, -1, 1);
// if (imu.getAnglex() < -10){
//  
// }
// else
 if (abs(imu.getAngleX()) > 10){
    baseAngle = baseAngle + servoBase.read();
    servoBase.write(baseAngle = constrain (baseAngle, 0, 89));
 }
 
//  if(servoBase.read() < 89){ //limit to 90
//    if(-45 < imu.getAngleX() < -10){
//      baseAngle += 0.05;
//      servoBase.write(baseAngle);
//    }else if(imu.getAngleX() < -44){
//      baseAngle += 1;
//      servoBase.write(baseAngle);
//    }else if(10 > imu.getAngleX() > 45){
//      baseAngle -= 0.05;
//      servoBase.write(baseAngle);
//    }else if(imu.getAngleX() > 44){
//      baseAngle -= 1;
//      servoBase.write(baseAngle);
//      }

//  }
 

//Base stepper
//
//  if(imu.getAngleZ() > 10){
//    
//    baseStepper.step(bas  
//  }
  

  delay(2);

}
