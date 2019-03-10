#include "Communication.h"

#include <iostream>
#include <qi/log.hpp>
#include <unistd.h>

Communication::Communication(boost::shared_ptr<AL::ALBroker> broker, const std::string& name)
  : AL::ALModule(broker, name), tts_(getParentBroker())
{
  setReturn("boolean", "return true if it was succesfully");
  BIND_METHOD(sendRobotState);
}

Communication::~Communication()
{

}

void Communication::init()
{

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
