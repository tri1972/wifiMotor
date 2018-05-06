#ifndef LIB_DRC8830
#define LIB_DRC8830

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define DRV8830_0 0x60
#define DRV8830_1 0x62
#define CONTROL_REG 0x00
#define FAULT_REG 0x01

#define STANBY 0x00
#define NEG_ROT 0x02
#define POS_ROT 0x01
#define BREAK 0x03

enum DriveMode{
  Stanby=0,
  NegativeDrive=1,
  PositiveDrive=2,
  Break=3
};

class lib_drv8830{
 public:
  lib_drv8830();
  int motorDrive(int,enum DriveMode,float);
  ~lib_drv8830();
};

#endif
