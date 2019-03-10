#ifndef SERVER_H
#define SERVER_H

#include"udp_config.h"

class Server
{
  public:

  Server();

  ~Server();

  private:

  // To configure socket

  int sockfd = 0;
  bool isAlWorks = true;

  void CreateSocket();
  void BindSocket();

  // To configure addresses

  void addressesConfig();

  struct sockaddr_in servaddr, cliaddr; // struct for addresses
  int clilen;

  // To receive

  struct GameControlData buf; // just buffer to recieve
  int n;  // number of received bytes
  struct GameControlData gameControldata;

  void receiveGCData();

  // To answer

  struct ReturnData returnData;

  void sendReturnData();
};

#endif /* SERVER_H */
