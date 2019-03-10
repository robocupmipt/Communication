#include"server.h"

Server::Server()
{
  CreateSocket();

  BindSocket();
}

~Server::Server()
{

}

void Server::CreateSocket()
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

void Server::BindSocket()
{
  if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(cliaddr)) < 0)
  {
    perror("bind");
    close(sockfd);
  }
}

void Server::receiveGCData()
{
  if((n = recvfrom(sockfd, &buf, sizeof(buf) - 1, FLAGS_RECV_FROM, (struct sockaddr *) &cliaddr, &clilen)) < 0)
    perror("recvfrom");
}

void Server::sendReturnData()
{
    if(sendto(sockfd, &returnData, strlen(returnData) + 1, FLAGS_SEND_TO, (struct sockaddr *) &cliaddr, clilen) < 0)
    {
      perror("sendto");
    }
}
