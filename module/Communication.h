#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>
#include <alcommon/almodulecore.h>
#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>
#include <alproxies/altexttospeechproxy.h>
//#include <boost/config/warning_disable.hpp>
#include <qi/log.hpp>

namespace AL
{
  class ALBroker;
}

class Communication : public AL::ALModule
{
public:
  Communication(boost::shared_ptr<AL::ALBroker> broker, const std::string &name);

  virtual ~Communication();

  virtual void init();

  // Start transmit.receive
  void startModule();

  // Start loop transmit/wait/transmit
  void startTransmitLoop();
  // Start loop receive/sendState/receive
  void startReceiveLoop();

  // Functions to communicate with Game Controller

  // Transmit data to GameController
  bool transmitToGC();
  // Receive data from GameController
  bool receiveFromGC();

  // Functions to communicate with other modules

  // Send current robot state to Strategy module
  bool sendRobotState();

  // Write robot position (should be called from Localization module)
  void writeRobotPosition();

  // Write ball position (should be called from CV module)
  void writeBallPosition();

  bool sayWord(const std::string &word);

  // Functions to communicate with other robots

  // To be continued

private:
  AL::ALTextToSpeechProxy tts_;
  boost::shared_ptr<AL::ALBroker> broker;
};

#endif // COMMUNICATION_H
