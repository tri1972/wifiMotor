#ifndef LIB_MOTOR_SERVO
#define LIB_MOTOR_SERVO

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define MAXSERVOVALUE 115
#define MINSERVOVALUE 24

#define PWM_PIN 18 //サーボモータ動作用PWMピン番号(PWMが使えるGPIOピンのみ可)



class lib_motorServo{
 public:
  enum DriveMode{
  Stop=0,
  NegativeDrive=1,
  PositiveDrive=2,
  };

  lib_motorServo();
  int motorDrive(enum DriveMode driveSet,double speed);
  ~lib_motorServo();
 private:
  int rotationMotor(double);
  int rotationMotorNeg(double);
  int rotationMotorPos(double);
  int rotationMotorStop();
  int rotationMotorSpeedCntr(unsigned int interop);
};

#endif