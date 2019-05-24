#include "wifiMotor.h"

static volatile int sigterm = 0;
static void handle_sigterm(int sig) { sigterm = 1; }

int main()
{
  jsonReader * json = new jsonReader();
  lib_drv8830 * motor=new lib_drv8830();
  lib_motorServo * servoMotor=new lib_motorServo();
  
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  unsigned int len;
  int sock;
  int yes = 1;
  char recvBuffer[256];
  char sendBuffer[256];
  char strBuffer[256];

  /* syslog オープン*/
  openlog("wifiMotor", LOG_PID, LOG_DAEMON);
  syslog(LOG_NOTICE,"start wifiMotor.");
  
  //daemon化初期化
  char* const pathpid="/var/run/wifiMotor.pid";
  char* const id="wifiMotor";
  if(!daemonize::daemonizing(pathpid,id, (int)LOG_PID, (int)LOG_DAEMON))
    {
      syslog(LOG_ERR,"failed to daemonize.");
      //fprintf(stderr, "failed to daemonize.\n");
      return 2; // fail to start daemon
    }
    
  //ソケット作成
  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  //ソケット作成エラーチェック
  if(sock0 < 0) {
    perror("socket");
    return -1;
  }
  //接続先情報設定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SOCKET_PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  //ソケットのオプション設定
  setsockopt(sock0, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes,  sizeof(yes));

  //アドレスとソケットディスクリプタを関連付け
  if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
    perror("bind");
    return -1;
  }

  //接続待ちに設定（acceptにて接続要求を受ける）
  if(listen(sock0, 5) != 0) {
    perror("listen");
    return -1;
  }

  //daemonループの開始
  syslog(LOG_NOTICE, "wifiMotorLoop  started.");
  signal(SIGTERM, handle_sigterm); 
  //接続要求待ちループ
  while (!sigterm) {
    
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);

    //接続エラー判定
    if (sock < 0) {
      //エラー時はループを抜けて処理を終了
      perror("accept");
      break;
    }
    //受信用バッファ用意
    memset(recvBuffer, 0, sizeof(char)*256);

    //データ受信
    recv(sock, (void *)recvBuffer, sizeof(char)*256, 0);

    //受信したデータを表示
    sprintf(strBuffer, "recvData = %s\n", recvBuffer);
    syslog(LOG_NOTICE,strBuffer);
    
    std::string jsonStr(recvBuffer);

    std::string keyDouble("Voltage");
    double valueDouble = json->readDouble(jsonStr,keyDouble);

    std::string keyInt("Mode");
    int valueInt = json->readDouble(jsonStr,keyInt);

    std::string keyIntMotor("MotorNumber");
    int valueMotor = json->readDouble(jsonStr,keyIntMotor);
    sprintf(strBuffer,"motorNumber=%d mode=%d Voltag=%f\n",valueMotor,valueInt,valueDouble);
    syslog(LOG_NOTICE,strBuffer);
     
    if(valueInt==4){
      char sendJson[256];
      sprintf(sendJson,"{ \"echoTankID\":%s }\n",TANK_ID);      
      syslog(LOG_NOTICE,sendJson);
      //データ送信送信
      memcpy(sendBuffer, sendJson, 256);
      send(sock, sendBuffer, sizeof(char)*strlen(sendBuffer), 0);
    }else{
      //データ送信送信
      memcpy(sendBuffer, "sendOK!!\n", 256);
      send(sock, sendBuffer, sizeof(char)*strlen(sendBuffer), 0);

      if(valueMotor<2){
	enum DriveMode modeDrive;

	switch(valueInt){
	  case 0:
	   modeDrive=Stanby;
	   break;
	  case 1:
	    modeDrive=PositiveDrive;
	    break;
	  case 3:
	    modeDrive=NegativeDrive;
	    break;
	  case 2:
	    modeDrive=Break;
	    break;
	}
	//モータードライブ実行
	motor->motorDrive(valueMotor,modeDrive,valueDouble);
      }else{
	enum lib_motorServo::DriveMode modeDrive;

	switch(valueInt){
	  case 1:
	    modeDrive=lib_motorServo::PositiveDrive;
	    break;
	  case 3:
	    modeDrive=lib_motorServo::NegativeDrive;
	    break;
	  case 2:
	    modeDrive=lib_motorServo::Stop;
	    break;
	}
	//モーターナンバーが３の時はサーボモータの動作実行
	//servoMotor->motorDrive(valueInt,valueDouble);
	servoMotor->motorDrive(modeDrive,valueDouble);
      }
    }
  }

  //ソケットクローズ
  close(sock0);

  //printf( "Close socket...\n" );
  syslog(LOG_NOTICE,"Close socket...\n");
    
  delete json;
  
  return 0;
}
