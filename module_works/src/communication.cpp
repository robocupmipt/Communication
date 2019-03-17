#include "../include/communication.hpp"


#include <iostream>
#include <qi/log.hpp>
#include <unistd.h>


//--------------------------------------------------------------------------------------------------------

Communication::Communication(boost::shared_ptr<AL::ALBroker> broker, const std::string& name)
  : AL::ALModule(broker, name), tts_(getParentBroker()), server_()
{
  //setReturn("boolean", "return true if it was succesfully");
  BIND_METHOD(Communication::sendRobotState);
}

Communication::~Communication()
{
  std::cout << "destructor called" << std::endl;
  /*
  delete[] tts_;
  delete broker;
  */
}

void Communication::init()
{

}


bool Communication::sendRobotState()
{

}

void Communication::printGCData()
{
    server_.printGCData();
}


int Communication::startModule()
{

  pid_t pid = fork();

  if(pid == -1)
  {
    std::cout << "error occured while fork" << std::endl;
    return -1; /// ?????????????????
  }

  if(pid == 0) // isChild
    startReceiveLoop();
  else
    startTransmitLoop();
  return 0;

}

void Communication::startTransmitLoop()
{
  while(1)
  {
   
    // server_.transmit();
    // sleep(1);
  }
}

void Communication::startReceiveLoop()
{
  while(1)
  {
    server_.receiveGCData();
    //sleep(1);
  }
}

/*
bool Communication::transmitToGC()
{
  std::cout << "transmit succesfully.\n";
}
*/

/*
bool Communication::receiveFromGC()
{
  std::cout << "receive succesfully.\n";
}
*/

bool Communication::sayWord(const std::string& word){
  std::cout << "Saying the phrase in the console..." << std::endl;
  std::cout << word << std::endl;
  try
  {

    /** Call the say method. */
    tts_.say(word);
    /** Note: on the desktop you won't hear anything, but you should see
    * some logs on the naoqi you are connected to. */
  }
  catch(const AL::ALError&)
  {
    qiLogError("module.example") << "Could not get proxy to ALTextToSpeech" << std::endl;
  }
}
