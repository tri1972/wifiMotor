#ifndef WIFIMOTOR
#define WIFIMOTOR

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include "jsonReader.h"
#include "lib_drv8830.h"
#include "daemonize.h"
#include "lib_motorServo.h"

#define SOCKET_PORT 2001//受信ポート番号の指定
#define TANK_ID "0" //戦車ごとに割り当てる数値
#endif
