#include "../include/communication.hpp"

#include <iostream>
#include <thread>
#include <qi/log.hpp>
#include <unistd.h>


//--------------------------------------------------------------------------------------------------------
Communication::Communication(boost::shared_ptr<AL::ALBroker> broker, const std::string& name) : AL::ALModule(broker, name), tts_(getParentBroker()), server_()
{
  //setReturn("boolean", "return true if it was succesfully");
  // BIND_METHOD(Communication::sendRobotState);
  functionName("startModule", getName(), "Start Module");
  BIND_METHOD(Communication::startModule);
}

Communication::~Communication()
{
  std::cout << "destructor called" << std::endl;
}

void Communication::sayGameState()
{
  switch(gameState)
  {
    case initial:
      sayWord("initial");
      break;
    case ready:
      sayWord("ready");
      break;
    case set:
      sayWord("set");
      break;
    case playing:
      sayWord("playing");
      break;
    case finished:
      sayWord("finished");
      break;
  }
}

bool Communication::sendRobotState()
{
  std::cout << "sendRobotState\n";
  AL::ALProxy proxyStrategy_(broker, "StrategyModule");
  proxyStrategy_.callVoid("UpdateGameState", 1);
}

void Communication::printGCData()
{
    server_.printGCData();
}

void Communication::startModule()
{
  std::thread receive (&Communication::receiveLoop, this);
  std::thread send    (&Communication::transmitLoop, this);

  std::cout << "executed succesfully" << std::endl;

  send.join();
  receive.join();

  std::cout << "completed" << std::endl;
}

void Communication::transmitLoop()
{
  while(1)
  {
    // server_.transmit();
    // sleep(1);
  }
}

void Communication::receiveLoop()
{
  while(1)
  {
    server_.receiveGCData();
    server_.printGCData();
    checkState();
  }
}

void Communication::checkState()
{
    gameState = server_.getGameState();
    if(gameState != currentGameState)
    {
      sendRobotState();
      currentGameState = gameState;
    }
}

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


