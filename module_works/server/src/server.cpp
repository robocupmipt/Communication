#include"server/include/server.h"
#include <iostream>

Server::Server()
{
  createSocket();

  addressesConfig();
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

void Server::addressesConfig()
{
  clilen = sizeof(cliaddr);

  bzero(&cliaddr, clilen);
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
  if((n = recvfrom(sockfd, &buf, sizeof(buf) - 1, FLAGS_RECV_FROM, (struct sockaddr *) &cliaddr, (socklen_t *) &clilen)) < 0)
    perror("recvfrom");
}

void Server::sendReturnData()
{
    if(sendto(sockfd, &returnData, sizeof(returnData), FLAGS_SEND_TO, (struct sockaddr *) &cliaddr, clilen) < 0)
    {
      perror("sendto");
    }
}

void Server::printBuf()
{
  std::cout << "\nPRINT MESSAGE IN BUFFER:\n";

  printf("Header: %s\n", buf.header);
  printf("Pack num: %d\n", buf.packetNumber);
  printf("State: %d\n\n", buf.state);

  printf("Version: %d\n", buf.version);
  printf("Players per team: %d\n", buf.playersPerTeam);
  printf("CompetitionPhase: %d\n", buf.competitionPhase);
  printf("CompetitionType: %d\n", buf.competitionType);
  printf("GamePhase: %d\n", buf.gamePhase);
  printf("Set play: %d\n", buf.setPlay);
  printf("First half: %d\n", buf.firstHalf);
  printf("Kicking team: %d\n", buf.kickingTeam);
  printf("Drop in team: %d\n", buf.dropInTeam);
  printf("Drop in time: %d\n", buf.dropInTime);
  printf("Seconds remaining: %d\n", buf.secsRemaining);
  printf("Secondary time: %d\n", buf.secondaryTime);

  printf("\nTeam 1 info:\n");
  printf("Number: %d\n", buf.teams[0].teamNumber);
  printf("Colour: %d\n", buf.teams[0].teamColour);
  printf("Score: %d\n", buf.teams[0].score);
  printf("Penalty shot: %d\n", buf.teams[0].penaltyShot);
  printf("Signle shots: %d\n", buf.teams[0].singleShots);

  PlayerInfo * s;

  s = buf.teams[0].players;
  printf("Players info: \t\t1\t2\t3\t4\t5\t6\n");
  printf("Penalty: \t\t%d\t%d\t%d\t%d\t%d\t%d\n", s[0].pen, s[1].pen, s[2].pen, s[3].pen, s[4].pen, s[5].pen);
  printf("Secs till unpen: \t%d\t%d\t%d\t%d\t%d\t%d\n", s[0].secs, s[1].secs, s[2].secs, s[3].secs, s[4].secs, s[5].secs);

  printf("\nTeam 2 info:\n");
  printf("Number: %d\n", buf.teams[1].teamNumber);
  printf("Colour: %d\n", buf.teams[1].teamColour);
  printf("Score: %d\n", buf.teams[1].score);
  printf("Penalty shot: %d\n", buf.teams[1].penaltyShot);
  printf("Signle shots: %d\n", buf.teams[1].singleShots);

  s = buf.teams[1].players;
  printf("Players info: \t\t1\t2\t3\t4\t5\t6\n");
  printf("Penalty: \t\t%d\t%d\t%d\t%d\t%d\t%d\n", s[0].pen, s[1].pen, s[2].pen, s[3].pen, s[4].pen, s[5].pen);
  printf("Secs till unpen: \t%d\t%d\t%d\t%d\t%d\t%d\n", s[0].secs, s[1].secs, s[2].secs, s[3].secs, s[4].secs, s[5].secs);

  std::cout << "END OF MESSAGE IN BUFFER\n";
}

