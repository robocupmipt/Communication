#ifndef COMMUNICATION_H
# define COMMUNICATION_H

#include <iostream>
#include <alcommon/albroker.h>
#include <alproxies/altexttospeechproxy.h>

/*
#define SPL_STANDARD_MESSAGE_STRUCT_HEADER "SPL"
#define SPL_STANDARD_MESSAGE_STRUCT_VERSION 7
#define PLAYER_NUM 6
#define TEAM_NUM 1
#define SPL_STANDARD_MESSAGE_DATA_SIZE 474

char header[4] = SPL_STANDARD_MESSAGE_STRUCT_HEADER;
uint8_t version = SPL_STANDARD_MESSAGE_STRUCT_VERSION;
uint8_t playerNum = PLAYER_NUM;
uint8_t teamNum = TEAM_NUM;

// number of bytes that is actually used by the data array
  uint16_t numOfDataBytes = SPL_STANDARD_MESSAGE_DATA_SIZE;
  // buffer for arbitrary data, teams do not need to send more than specified in numOfDataBytes
  uint8_t data[SPL_STANDARD_MESSAGE_DATA_SIZE];

typedef struct DataForMessage
{
	// position and orientation of robot
	float pose[3];
	// ball information
	float ballAge;
	// position of ball relative to the robot
	float ball[2];
	// 1 means that the robot is fallen, 0 means that the robot can play
	uint8_t fallen;
} DataForMessage;
*/

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

  //--------- Functions to communicate with Game Controller

  // Transmit data to GameController
  bool transmitToGC();
  // Receive data from GameController
  bool receiveFromGC();

  //--------- Functions to communicate with other modules

  // Send current robot state to Strategy module
  bool sendRobotState();

  // Write robot position (should be called from Localization module)
  void writeRobotPosition();

  // Write ball position (should be called from CV module)
  void writeBallPosition();
  // Function which prints the word given on parameters
  void printWord(const std::string &word);
  // Function which returns true
  bool returnTrue();

  bool sayWord(const std::string &word);

  //--------- Functions to communicate with other robots

  // To be continued

private:
  AL::ALTextToSpeechProxy tts_;
  boost::shared_ptr<AL::ALBroker> broker;
};

#endif // COMMUNICATION_H
