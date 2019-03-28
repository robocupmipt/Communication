#include "../include/communication.hpp"
#include <iostream>
#include <thread>
#include <qi/log.hpp>
#include <unistd.h> 

Communication::Communication(boost::shared_ptr<AL::ALBroker> broker, const std::string& name) : AL::ALModule(broker, name), tts_(getParentBroker()), server_(), fMemoryProxy(getParentBroker()), message_(FROM_COMMUNICATION_TO_STRATEGY, FROM_STRATEGY_TO_COMMUNICATION)
{
}

Communication::~Communication()
{

}

void Communication::init()
{
  message_.InitMsg();

  startModule();
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

void Communication::sendRobotState()
{
  MessageOutputBuf buf;

  buf.data.state = currentGameState;
  message_.SendMessage(buf);
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
    //server_.printGCData();
    checkState();
  }
}

void Communication::checkState()
{
    gameState = server_.getGameState();
    if(gameState != currentGameState)
    {
      currentGameState = gameState;
      sendRobotState();
    }
}

bool Communication::sayWord(const std::string& word)
{
  tts_.say(word);
}


