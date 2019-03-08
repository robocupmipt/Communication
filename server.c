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

struct RoboCupGameControlData
{
  char header[4];               // header to identify the structure
  uint16_t version;             // version of the data structure
  uint8_t packetNumber;         // number incremented with each packet sent (with wraparound)
  uint8_t playersPerTeam;       // the number of players on a team
  uint8_t competitionPhase;     // phase of the competition (COMPETITION_PHASE_ROUNDROBIN, COMPETITION_PHASE_PLAYOFF)
  uint8_t competitionType;      // type of the competition (COMPETITION_TYPE_NORMAL, COMPETITION_TYPE_MIXEDTEAM, COMPETITION_TYPE_GENERAL_PENALTY_KICK)
  uint8_t gamePhase;            // phase of the game (GAME_PHASE_NORMAL, GAME_PHASE_PENALTYSHOOT, etc)
  uint8_t state;                // state of the game (STATE_READY, STATE_PLAYING, etc)
  uint8_t setPlay;              // active set play (SET_PLAY_NONE, SET_PLAY_GOAL_FREE_KICK, etc)
  uint8_t firstHalf;            // 1 = game in first half, 0 otherwise
  uint8_t kickingTeam;          // the team number of the next team to kick off, free kick, DROPBALL etc.
  uint8_t dropInTeam;           // number of team that caused last drop in
  uint16_t dropInTime;          // number of seconds passed since the last drop in. -1 (0xffff) before first dropin
  uint16_t secsRemaining;       // estimate of number of seconds remaining in the half
};

#define BUF_SIZE 1000
#define PORT 3838

#define CHECK(nameFunction, retValue)				\
do {								\
	if(retValue < 0)					\
	{							\
		perror(nameFunction);		\
		exit(1);					\
	}							\
} while(0)							\

int main()
{
	int n, clilen;
	char line[BUF_SIZE] = {};
	struct RoboCupGameControlData spl;

	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	CHECK("socket", sockfd);
	printf("%d\n", sockfd);

	struct sockaddr_in servaddr, cliaddr;
	bzero(&cliaddr, sizeof(cliaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(cliaddr)) < 0)
	{
		perror("bind");
		close(sockfd);
		exit(1);
	}

	while(1)
	{
		clilen = sizeof(cliaddr);
		if((n = recvfrom(sockfd, &spl, 999, 0, (struct sockaddr *) &cliaddr, &clilen)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}

		printf("%s\n", spl.header);
		printf("packNum:%d\n", spl.packetNumber);
		printf("state:%d\n", spl.state);
		printf("playerPerTeam:%d\n", spl.playersPerTeam);
		/*
		if(sendto(sockfd, line, strlen(line) + 1, 0, (struct sockaddr *) &cliaddr, clilen) < 0)
		{
			perror("sendto");
			close(sockfd);
			exit(1);
		}*/
	}

	return 0;
}
