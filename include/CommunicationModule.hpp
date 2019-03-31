//
// Created by Vladislav Molodtsov on 2019-03-29.
//
#ifndef MY_MODULE_H
# define MY_MODULE_H

#include<iostream>
#include<alcommon/albroker.h>
#include<alproxies/altexttospeechproxy.h>
#include<boost/shared_ptr.hpp>
#include<alcommon/almodule.h>
#include<alproxies/almemoryproxy.h>

#define FILE_KEY "../key"

#include"Check.h"
#include"GCStates.h"
#include"Server.h"
#include"Message.h"

using namespace gamecontroller;
using namespace message;

namespace AL
{
  class ALBroker;
}

//-----------------------------------------------------------------------------------

class Communication : public AL::ALModule
{
public:
  Communication() = delete;
  Communication(boost::shared_ptr<AL::ALBroker> broker, const std::string &name);

  virtual void init();

  virtual ~Communication();

  GameState currentGameState = FINISHED, gameState;

  void CheckState();
  void SayGameState();

  bool SayWord(const std::string &word);
  void PrintGCData();

/*
* Start transmit.receive
* Attention! This function uses std::thread!
*/
  void StartModule();

  // Start loop transmit/wait/transmit
  void TransmitLoop();

  // Start loop receive/sendState/receive
  void ReceiveLoop();

  // Functions to communicate with other modules

  // Send current robot state to Strategy module
  void SendRobotState();

  // Write robot position (should be called from Localization module)
  void WriteRobotPosition();

  // Write ball position (should be called from CV module)
  void WriteBallPosition();

  // Functions to communicate with other robots

  // To be continued

private:
  AL::ALTextToSpeechProxy         tts_;
  Server                          server_;
  Message<MessageType<Send>, MessageType<Receive>> message_;
};

#endif // MY_MODULE_H
