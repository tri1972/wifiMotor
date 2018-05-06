#include "wifiMotor.h"


int main()
{
  jsonReader * json = new jsonReader();
  
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  unsigned int len;
  int sock;
  int yes = 1;
  char recvBuffer[256];
  char sendBuffer[256];

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


  //接続要求待ちループ
  while (1) {
    
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
    printf("recvData = %s\n", recvBuffer);
    
    std::string jsonStr(recvBuffer);

    std::string keyDouble("Voltage");
    double valueDouble = json->readDouble(jsonStr,keyDouble);

    std::string keyInt("Mode");
    int valueInt = json->readDouble(jsonStr,keyInt);

    printf("mode=%d Voltage=%f\n",valueInt,valueDouble);

    
    //送信データをセット
    memcpy(sendBuffer, "Data OK!\n", 256);

    //データ送信送信
    send(sock, sendBuffer, sizeof(char)*strlen(sendBuffer), 0);

  }

  //ソケットクローズ
  close(sock0);

  printf( "Close socket...\n" );
  delete json;
  
  return 0;
}
