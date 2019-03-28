#include"include/queue_config.h"

#include<iostream>

#define PERMISSION 0777

#define MESSAGE_TYPE 1

#define CHECK(nameFunction, retValue)				\
do {								\
	if(retValue == -1)					\
	{							\
    perror(nameFunction);\
    return 1;   \
	}							\
	else							\
		printf("%s succeeded\n", nameFunction);		\
} while(0)							\

enum GameState
{
  initial = 0,
  ready,
  set,
  playing,
  finished
};

struct msgBuf
{
	long type;
	int state;
};

struct OutputData
{
  enum GameState state;
};

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Arg error\n");
		return 1;
	}

	const char file[] = "key";

	if(atoi(argv[1]) == 1)	//transmitter
	{
		printf("Transmitter\n");

		key_t key = ftok(file, 0);
		CHECK("ftok", key);
		printf("Key = %d\n", key);

		int msgid = msgget(key, PERMISSION | IPC_CREAT | IPC_EXCL);
		if(msgid < 0)
		{
			if(errno == EEXIST)
			{
				printf("Already exist. Need to remove\n");

				msgid = msgget(key, PERMISSION);
				CHECK("msgget", msgid);

        /*
				CHECK("msgctl", msgctl(msgid, IPC_RMID, (struct msqid_ds *)NULL));

				msgid = msgget(key, PERMISSION | IPC_CREAT | IPC_EXCL);
				CHECK("msgid", msgid);
        */
			}
			else
			{
        perror("msgget");
				return 4;
			}
		}
		else
			printf("Message queue get succesfully\n");

		printf("Let's get transmitted\n");
    struct msgBuf buf;

		buf.type = MESSAGE_TYPE;
		do {
      std::cout << "enter state " << std::endl;
      std::cin >> buf.state;

		  int result = msgsnd(msgid, (struct msgbuf *)&buf, sizeof(int), 0);
		  CHECK("msgsnd", result);
		} while(1);
	}
	else if(atoi(argv[1]) == 0)	//reciever
	{
		printf("Receiver\n");

		key_t key = ftok(file, 0);
		CHECK("ftok", key);

		printf("Key = %d\n", key);

		int msgid;
		do msgid = msgget(key, PERMISSION);
		while((msgid == -1) && (errno ==ENOENT));

		if(msgid == -1)
		{
			printf("Some error");
			return 4;
		}

		printf("msgget succeed\n");
		printf("Let's get received\n");

    struct msgBuf buf;

		int length;
		do {
			length = msgrcv(msgid, (struct msg_buf *)&buf, sizeof(int), 0, 0);
      std::cout << "received" << std::endl;
			CHECK("msgrcv", length);

      std::cout << "type " << buf.type << std::endl;
      std::cout << "state " << buf.state << std::endl;
			}
		while(1);
	}
	else
	{
		printf("Arg error\n");
		return 1;
	}

	return 0;
}




