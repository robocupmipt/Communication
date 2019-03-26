#ifndef MY_MODULE_H
# define MY_MODULE_H

#include <iostream>
#include <alcommon/albroker.h>
#include <alproxies/altexttospeechproxy.h>
#include "../include/server.h"

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

  GameState currentGameState = finished, gameState;

  void checkState();
  void sayGameState();

  bool sayWord(const std::string &word);
  void printGCData();

/*
* Start transmit.receive
* Attention! This function uses std::thread!
*/
  void startModule();

  // Start loop transmit/wait/transmit
  void transmitLoop();

  // Start loop receive/sendState/receive
  void receiveLoop();

  // Functions to communicate with other modules

  // Send current robot state to Strategy module
  bool sendRobotState();

  // Write robot position (should be called from Localization module)
  void writeRobotPosition();

  // Write ball position (should be called from CV module)
  void writeBallPosition();

  // Functions to communicate with other robots

  // To be continued

private:
  AL::ALTextToSpeechProxy         tts_;
  Server                          server_;
};

#endif // MY_MODULE_H
