#include "Communication.h"

#include <iostream>
#include <qi/log.hpp>
#include <unistd.h>

Communication::Communication(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name), tts_(getParentBroker())
{
  setReturn("boolean", "return true if it was succesfully");
  BIND_METHOD(Communication::sendRobotState);
}

Communication::~Communication()
{

}

void Communication::init()
{

}

/*
std::string retState(RobotStates robotState);

typedef enum RobotStates
{
	NotDefined,
	Initial,
	Ready,
	Set,
	Playing,
	Penalized,
	Finished
} RobotStates;

RobotStates curRobotState = NotDefined;
std::string retState(RobotStates robotState)
{
	std::string ret;
	switch(robotState)
	{
		case Initial:
			ret = "Initial";
			break;
		case Ready:
			ret = "Ready";
			break;
		case Set:
			ret = "Set";
			break;
		case Playing:
			ret = "Playing";
			break;
		case Penalized:
			ret = "Penalized";
			break;
		case Finished:
			ret = "Finished";
			break;
		case NotDefined:
		default:
			ret = "NotDefined";
			break;
	}

	return ret;
}
*/

bool Communication::sendRobotState()
{
	bool error = false;

	/*
	if(curRobotState == NotDefined)
	{
		std::cout << "Current state = NotDefined. Can't transmit state.\n";
		return error;
	}

	std::string stringState = retState(ComState::curRobotState);
	// here should be call for transmit state
	std::cout << "Current state = " << stringState << " transmit succesfully.\n";
	*/
}

void Communication::startModule()
{
	int pid = fork();
	if(pid == 0)
		startReceiveLoop();
	else
		startTransmitLoop();
}

void Communication::startTransmitLoop()
{
	while(1)
	{
		transmitToGC();
		sleep(1);
	}
}

void Communication::startReceiveLoop()
{
	while(1)
	{
		receiveFromGC();
		sleep(1);
	}
}

bool Communication::transmitToGC()
{
  std::cout << "transmit succesfully.\n";
}

bool Communication::receiveFromGC()
{
  std::cout << "receive succesfully.\n";
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
