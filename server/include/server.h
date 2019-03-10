#ifndef SERVER_H
#define SERVER_H

#include"udp_config.h"
#include"message.h"

class Server
{
  public:

  Server();

  ~Server();

  // To receive

  struct GameControlData buf; // just buffer to recieve
  int n;                      // number of received bytes

  struct GameControlData gameControldata;

  void receiveGCData();
  void printBuf();

  // To answer

  struct ReturnData returnData;

  void sendReturnData();

  private:

  // To configure socket

  int sockfd = 0;
  bool isAlWorks = true;

  void createSocket();
  void bindSocket();

  // To configure addresses

  void addressesConfig();

  struct sockaddr_in servaddr, cliaddr; // struct for addresses
  int clilen;
};

#endif /* SERVER_H */
