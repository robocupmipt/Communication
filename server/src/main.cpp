#include"server.h"

int main()
{
  Server server;

  while(1)
  {
    server.receiveGCData();
    server.printGCData();
  }

  return 0;
}
