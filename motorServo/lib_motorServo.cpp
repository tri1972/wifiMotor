#include "./lib_motorServo.h"

volatile unsigned int direction;
volatile unsigned int rotaring;

/**
コンストラクタ
 */
lib_motorServo::lib_motorServo(){
  if(wiringPiSetupGpio() == -1){
      syslog(LOG_NOTICE,"wiringPI setup error!!");
  }
}

/**
デストラクタ
 */
lib_motorServo::~lib_motorServo(){
}

int lib_motorServo::rotationMotor(double set_degree){

  int servo_pin=PWM_PIN;

  // Set GPIO18 pin to output mode
  pinMode(servo_pin, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);          // 0Vに指定
  pwmSetRange(1024);      // レンジを0～1024に指定
  pwmSetClock(400);       // 後述

  double move_degf=((MAXSERVOVALUE-MINSERVOVALUE)/180.0)*set_degree+MINSERVOVALUE;
  int move_deg=move_degf;

  pwmWrite(servo_pin, move_deg);
}

int lib_motorServo::rotationMotorNeg(double speed){
  int output=-1;
  if(speed >= 0){
    output= rotationMotor(90.0-speed);
  }else{
    output=0;
  }

  return output;
}

int lib_motorServo::rotationMotorPos(double speed){
  int output=-1;
  if(speed >= 0){
    output= rotationMotor(90.0+speed);
  }else{
    output=0;
  }
  return output;
}

int lib_motorServo::rotationMotorStop(){
  int output=-1;
  output= rotationMotor(90);
  return output;
}


int lib_motorServo::motorDrive(enum lib_motorServo::DriveMode driveSet,double speed){
  int output=0;

  char tmpStr[255];
  sprintf(tmpStr,"motorDrive mode %d speed %f",driveSet,speed);
  syslog(LOG_NOTICE,tmpStr);
  
  switch(driveSet){
  case lib_motorServo::DriveMode::Stop:
    rotationMotorStop();
    break;
  case lib_motorServo::DriveMode::NegativeDrive:
    rotationMotorNeg(speed);
    break;
  case lib_motorServo::DriveMode::PositiveDrive:
    rotationMotorPos(speed);
    break;
  default :
    syslog(LOG_NOTICE,"Operand Error!!!");
    output=1;
  }
  return output;
}

int lib_motorServo::motorDrive(int driveSet,double speed){
  int output=0;

  char tmpStr[255];
  syslog(LOG_NOTICE,tmpStr);
  
  switch(driveSet){
  case 0:
    rotationMotorStop();
    break;
  case 1:
    rotationMotorPos(speed);
    break;
  case 2:
    rotationMotorNeg(speed);
    break;
  default :
    //printf("Operand Error!!\n");
    output=1;
  }
  return output;
}


int lib_motorServo::rotationMotorSpeedCntr(unsigned int interop){
  int output=-1;
  //printf("rotationMotorSpeedCntr speed:%d\n",interop);
  
  rotaring=1;
  while(rotaring!=0){
    //printf("go\n");
    /*
    if(direction=0){
      output=rotationMotorNeg();
    }else{
      output=rotationMotorPos();
      }*/
    delay(interop);
    rotationMotorPos(5);
    delay(interop);
    rotationMotorStop();
    }
}



