#ifndef MY_MODULE_H
# define MY_MODULE_H

#include <iostream>
#include <alcommon/albroker.h>
#include <alproxies/altexttospeechproxy.h>
#include "../include/server.h"

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
}

/**
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable within NAOqi
 */


// class Server;

//-----------------------------------------------------------------------------------

class Communication : public AL::ALModule
{
public:
  Communication() = delete;
  Communication(boost::shared_ptr<AL::ALBroker> broker, const std::string &name);

  virtual ~Communication();

  //-----------------------------------------------------------------------------------
  bool sayWord(const std::string &word);
  
  void printGCData();
  //-----------------------------------------------------------------------------------

  // Start transmit.receive
  int startModule();

  // Start loop transmit/wait/transmit
  void startTransmitLoop();

  // Start loop receive/sendState/receive
  void startReceiveLoop();

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
  boost::shared_ptr<AL::ALBroker> broker;
  Server                          server_;
};

#endif // MY_MODULE_H