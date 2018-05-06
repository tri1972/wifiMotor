#include "lib_drv8830.h"


//コンストラクタ
lib_drv8830::lib_drv8830(){
}

//デストラクタ
lib_drv8830::~lib_drv8830(){
}

//モータードライバ
int lib_drv8830::motorDrive(int motorNo, enum DriveMode driveSet,float vSetF){

  int fd,ret;
  unsigned char setValue[3];
  unsigned char vSet,drive,motorHex;

  if(motorNo==0){
    motorHex=DRV8830_0;
  }else if(motorNo==1){
    motorHex=DRV8830_1;
  }else{
    motorHex=DRV8830_0;
  }

  switch(driveSet){
  case Stanby:
    drive=STANBY;
    break;
  case NegativeDrive:
    drive=NEG_ROT;
    break;
  case PositiveDrive:
    drive=POS_ROT;
    break;
  case Break:
    drive=BREAK;
    break;
  default :
    printf("Operand Error!!\n");
    return 1;
  }
  
  if(vSetF < 0.48 || vSetF > 5.06){
    printf("vSet=%lf Error!!\n",vSetF);
    return 1;
  }
  //printf("vSetF= %lf\n",vSetF);
  vSet=((int)(vSetF * 100)) / 8;  
  //printf("vSet= %x\n",vSet);
  
  setValue[0]=CONTROL_REG;
  setValue[1] = ( vSet << 2 )  | drive;  
  fd = wiringPiI2CSetup(motorHex);  
  ret = write(fd, setValue, 2);
  
  if (ret < 0) {
    printf("error: set configuration value\n");
    return 1;
  }
  
  printf("OK!\n");
  return 0;

}



/*
int main(int argc,char *argv[]) {

  int i;
  int motorNo;
  float vSetF;
  enum DriveMode drive;
  char *controlOperand;

  for(i=0;i<argc;i++){
    if( strcmp(argv[i],"-c")==0){
      controlOperand=argv[i+1];
    }else if( strcmp(argv[i],"-v")==0){
      vSetF = atof(argv[i+1]);
    }else if( strcmp(argv[i],"-n")==0){
      motorNo = atoi(argv[i+1]);
    }else if( strcmp(argv[i],"-h")==0){
      printf("-c pos:正転\n neg:逆転\n stop:停止\n stanby:惰走\n");
      printf("-n モータ番号(0～1) \n");
      printf("-v 電圧(0.48～5.06) \n");
    }
  }
  
  if( strcmp(controlOperand,"pos")==0){
    if(vSetF!=0){
      drive=PositiveDrive;
    }else{
      printf("Voletage dont input!!");
      return 1;
    }
  }else if(strcmp(controlOperand,"neg")==0){
    if(vSetF!=0){
      drive=NegativeDrive;
    }else{
      printf("Voletage dont input!!");
      return 1;
    }
  }else if(strcmp(controlOperand,"stop")==0){
    drive=Break;
    vSetF=1;
  }else if(strcmp(controlOperand,"stanby")==0){
    drive=Stanby;
    vSetF=1;
  }else{
    printf("Operand Error!!\n");
    return 1;
  }
  return motorDrive(motorNo, drive,vSetF);
}
*/
