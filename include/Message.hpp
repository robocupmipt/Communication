//
// Created by Vladislav Molodtsov on 2019-03-29.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<fcntl.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>

#include<iostream>
#include<string>

#include"Check.h"
#include"GCStates.h"

#define FILE_KEY "../key"
#define PERMISSION 0777
#define FROM_COMMUNICATION_TO_STRATEGY 1
#define FROM_STRATEGY_TO_COMMUNICATION 2

struct InputData
{ 
  gamecontroller::GameState state;
};

struct OutputData
{
  gamecontroller::GameState state;
};

struct MessageOutputBuf
{
	long type;  // It's necessary

  /* Next you can write your own data */

  OutputData data;
};

class Message
{
  public:

  Message();
  Message(int outType, int inputType);

  ~Message();

  bool InitMsg();

  bool SendMessage(MessageOutputBuf &buf);

  bool SetMessageTypes(int output, int input);

  private:

  int msgid_;

  int outputType_ = 1;
  int inputType_ = 2;
};

#endif // MESSAGE_H
