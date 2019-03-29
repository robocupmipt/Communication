#include <boost/shared_ptr.hpp>
#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/altoolsmain.h>

#include "../include/CommunicationModule.hpp"

extern "C"
{
  int _createModule(boost::shared_ptr<AL::ALBroker> broker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker);
    // create module instances
    AL::ALModule::createModule<Communication>(broker, "Communication");
    return 0;
  }

  int _closeModule(  )
  {
    return 0;
  }
} // extern "C"

#ifdef COMMUNICATION_IS_REMOTE
int main(int argc, char* argv[])
{
  // pointer to createModule
  TMainType sig = &_createModule;

  // call main
  return ALTools::mainFunction("Communication", argc, argv, sig);
}
#endif
