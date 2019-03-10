#ifndef UDP_CONFIG_H
#define UDP_CONFIG_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/wait.h>

#define BUF_SIZE 1000
#define PORT 3838
#define FLAGS_RECV_FROM 0
#define FLAGS_SEND_TO 0

#define CHECK(nameFunction, retValue)				\
do {								\
	if(retValue < 0)					\
	{							\
		perror(nameFunction);		\
		exit(1);					\
	}							\
} while(0)							\

#endif /* UDP_CONFIG_H */
