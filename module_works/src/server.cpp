#include"../include/server.h"
#include"iostream"

Server::Server()
{
  createSocket();

  servAddressConfig();
  bindSocket();
}

Server::~Server()
{

}

void Server::createSocket()
{
  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  CHECK("socket", sockfd);
  std::cout << "sockfd = " << sockfd << '\n';
}

void Server::servAddressConfig()
{
  bzero(&cliaddr, sizeof(cliaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Server::bindSocket()
{
  if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(cliaddr)) < 0)
  {
    perror("bind");
    close(sockfd);
  }
}

void Server::receiveGCData()
{
  int clilen = sizeof(cliaddr);
  int n = recvfrom(sockfd, &receiveBuf, sizeof(receiveBuf) - 1, FLAGS_RECV_FROM, (struct sockaddr *) &cliaddr, (socklen_t *) &clilen);

  if(n < 0)
    perror("recvfrom");

  checkBufAndCopy();
}

void Server::checkBufAndCopy()
{
  if(strcmp(receiveBuf.header, "RGme"))
  {
    std::cout << "Correct message received\n";
    gameControlData = receiveBuf;
  }
  else
    std::cout << "Incorrect message received\n";
}

void Server::sendReturnData()
{
  if(sendto(sockfd, &returnData, sizeof(returnData), FLAGS_SEND_TO, (struct sockaddr *) &cliaddr, sizeof(cliaddr)) < 0)
  {
    perror("sendto");
  }
}

void Server::printGCData()
{
  std::cout << "\nPRINT MESSAGE IN BUFFER:\n";

  printf("Header: %s\n", gameControlData.header);
  printf("Pack num: %d\n", gameControlData.packetNumber);
  printf("State: %d\n\n", gameControlData.state);

  printf("Version: %d\n", gameControlData.version);
  printf("Players per team: %d\n", gameControlData.playersPerTeam);
  printf("CompetitionPhase: %d\n", gameControlData.competitionPhase);
  printf("CompetitionType: %d\n", gameControlData.competitionType);
  printf("GamePhase: %d\n", gameControlData.gamePhase);
  printf("Set play: %d\n", gameControlData.setPlay);
  printf("First half: %d\n", gameControlData.firstHalf);
  printf("Kicking team: %d\n", gameControlData.kickingTeam);
  printf("Drop in team: %d\n", gameControlData.dropInTeam);
  printf("Drop in time: %d\n", gameControlData.dropInTime);
  printf("Seconds remaining: %d\n", gameControlData.secsRemaining);
  printf("Secondary time: %d\n", gameControlData.secondaryTime);

  printf("\nTeam 1 info:\n");
  printf("Number: %d\n", gameControlData.teams[0].teamNumber);
  printf("Colour: %d\n", gameControlData.teams[0].teamColour);
  printf("Score: %d\n", gameControlData.teams[0].score);
  printf("Penalty shot: %d\n", gameControlData.teams[0].penaltyShot);
  printf("Signle shots: %d\n", gameControlData.teams[0].singleShots);

  PlayerInfo * s;

  s = gameControlData.teams[0].players;
  printf("Players info: \t\t1\t2\t3\t4\t5\t6\n");
  printf("Penalty: \t\t%d\t%d\t%d\t%d\t%d\t%d\n", s[0].pen, s[1].pen, s[2].pen, s[3].pen, s[4].pen, s[5].pen);
  printf("Secs till unpen: \t%d\t%d\t%d\t%d\t%d\t%d\n", s[0].secs, s[1].secs, s[2].secs, s[3].secs, s[4].secs, s[5].secs);

  printf("\nTeam 2 info:\n");
  printf("Number: %d\n", gameControlData.teams[1].teamNumber);
  printf("Colour: %d\n", gameControlData.teams[1].teamColour);
  printf("Score: %d\n", gameControlData.teams[1].score);
  printf("Penalty shot: %d\n", gameControlData.teams[1].penaltyShot);
  printf("Signle shots: %d\n", gameControlData.teams[1].singleShots);

  s = gameControlData.teams[1].players;
  printf("Players info: \t\t1\t2\t3\t4\t5\t6\n");
  printf("Penalty: \t\t%d\t%d\t%d\t%d\t%d\t%d\n", s[0].pen, s[1].pen, s[2].pen, s[3].pen, s[4].pen, s[5].pen);
  printf("Secs till unpen: \t%d\t%d\t%d\t%d\t%d\t%d\n", s[0].secs, s[1].secs, s[2].secs, s[3].secs, s[4].secs, s[5].secs);

  std::cout << "END OF MESSAGE IN BUFFER\n";
}

GameState Server::getGameState() const
{
  return (GameState)gameControlData.state;
}
