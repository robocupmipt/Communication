#ifndef MY_MODULE_H
# define MY_MODULE_H

#include <iostream>
#include <alcommon/albroker.h>
#include <alproxies/altexttospeechproxy.h>

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
class MyModule : public AL::ALModule
{
public:
  MyModule(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);

  virtual ~MyModule();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();

  // After that you may add all your bind method.

  // Function which prints "Hello!" on standard output
  void printHello();
  // Function which prints the word given on parameters
  void printWord(const std::string &word);
  // Function which returns true
  bool returnTrue();

  bool sayWord(const std::string &word);

private:
  AL::ALTextToSpeechProxy tts_;
};

//-----------------------------------------------------------------------------------

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

#endif // MY_MODULE_H