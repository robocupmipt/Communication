//
// Created by Vladislav Molodtsov on 2019-03-29.
//

#ifndef SERVER_H
#define SERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/wait.h>

#include"Check.h"
#include"GCData.h"
#include"GCStates.h"
using namespace gamecontroller;

#define BUF_SIZE 1000
#define PORT 3838
#define FLAGS_RECV_FROM 0
#define FLAGS_SEND_TO 0

class Server
{
  public:

  Server(); 
  ~Server();

  bool ReceiveGCData();
  bool PrintGCData();

  GameState GetGameState() const;

  bool SendReturnData();

  private:

  //-------- To receive ----------//

  GameControlData receiveBuf; // just buffer to recieve

  GameControlData gameControlData;

  bool CheckBufAndCopy();

  //--------- To answer ----------//

  ReturnData returnData;

  //------- To configure socket --------//

  int sockfd = 0;

  bool CreateSocket();
  bool BindSocket();

  //---------- To configure address ------------//

  struct sockaddr_in servaddr, cliaddr; // struct for addresses

  // Config serv address
  bool ServAddressConfig();
};

#endif /* SERVER_H */
