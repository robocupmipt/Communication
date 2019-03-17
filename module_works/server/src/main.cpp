#include"server.h"

int main()
{
  Server server;

  while(1)
  {
    server.receiveGCData();
    server.printBuf();
  }

  return 0;
}
