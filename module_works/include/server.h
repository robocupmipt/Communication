#ifndef SERVER_H
#define SERVER_H

#include"udp_config.h"
#include"message.h"

class Server
{
  public:

  Server();

  ~Server();

  //-------- To receive ----------//

  struct GameControlData receiveBuf; // just buffer to recieve

  void receiveGCData();
  void printGCData();

  struct GameControlData gameControlData;
  void checkBufAndCopy();

  //--------- To answer ----------//

  struct ReturnData returnData;

  void sendReturnData();

  private:

  //------- To configure socket --------//

  int sockfd = 0;

  void createSocket();
  void bindSocket();

  //---------- To configure address ------------//

  struct sockaddr_in servaddr, cliaddr; // struct for addresses

  // Config serv address
  void servAddressConfig();
};

#endif /* SERVER_H */
