//
// Created by Vladislav Molodtsov on 2019-03-29.
//

#include <qi/log.hpp>

#include <iostream>
#include <thread>

#include <unistd.h> 
#include<errno.h>
#include<stdio.h>

#define FILE_KEY "../key"

#include "../include/CommunicationModule.hpp"

Communication::Communication(boost::shared_ptr<AL::ALBroker> broker, const std::string& name) : AL::ALModule(broker, name), tts_(getParentBroker()), server_(), message_(FROM_COMMUNICATION_TO_STRATEGY, FROM_STRATEGY_TO_COMMUNICATION)
{
}

Communication::~Communication()
{

}

void Communication::init()
{
  message_.InitMsg();

  StartModule();
}

void Communication::SayGameState()
{
  switch(gameState)
  {
    case INITIAL:
      SayWord("initial");
      break;
    case READY:
      SayWord("ready");
      break;
    case SET:
      SayWord("set");
      break;
    case PLAYING:
      SayWord("playing");
      break;
    case FINISHED:
      SayWord("finished");
      break;
  }
}

void Communication::SendRobotState()
{
  MessageType<Send> buf;

  buf.data.state = currentGameState;
  message_.SendMessage(buf);
}

void Communication::PrintGCData()
{
    server_.PrintGCData();
}

void Communication::StartModule()
{

  std::cout << "Executed succesfully" << std::endl;

  std::thread receive([&](){
      ReceiveLoop();
  });

  std::thread send([&](){
      TransmitLoop();
  });

  //https://en.cppreference.com/w/cpp/thread/thread/detach
  receive.detach();
  send.detach();

  std::cout << "Detach completed" << std::endl;
}

void Communication::TransmitLoop()
{
  std::cout << "Transmit loop start\n";

  while(1)
  {
    // server_.transmit();
    sleep(1);
  }
}

void Communication::ReceiveLoop()
{
  std::cout << "Receive loop start\n";

  while(1)
  {
    server_.ReceiveGCData();
    //server_.PrintGCData();
    CheckState();
  }
}

void Communication::CheckState()
{
    gameState = server_.GetGameState();
    if(gameState != currentGameState)
    {
      currentGameState = gameState;
      SendRobotState();
    }
}

bool Communication::SayWord(const std::string& word)
{
  tts_.say(word);
}


