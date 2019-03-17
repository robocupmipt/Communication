#ifndef SERVER_H
#define SERVER_H

#include"udp_config.h"
#include"message.h"

enum GameState
{
  initial = 0,
  ready,
  set,
  playing,
  finished
};

class Server
{
  public:

  Server(); 
  ~Server();

  void receiveGCData();
  void printGCData();

  GameState getGameState() const;

  void sendReturnData();

  private:

  //-------- To receive ----------//

  struct GameControlData receiveBuf; // just buffer to recieve

  struct GameControlData gameControlData;

  void checkBufAndCopy();

  //--------- To answer ----------//

  struct ReturnData returnData;

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
