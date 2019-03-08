#pragma once
#include "sys/socket.h"
#include "sys/types.h"
#include "unistd.h"
#include <netinet/in.h>
#include <iostream>
#include <string>

typedef int data_t;
typedef int team_info_t;

/*
 * There is a question about data transfer size
 * the safe size is 508 bytes from 576 byte available
 *
*/


/*
 * write data types and team info data class
 */

class Udp
{
	public:
		Udp();
		~Udp();
		const int 		getTime() const;
		const data_t & 		getData() const;
		const team_info_t & 	getTeamInfo() const;
		const bool 		isConnected() const;
		const int 		getSock() const;
		void 			Dump();
		inline void 		writeLog(const char* error);
	private:
		data_t      	    _data;
		team_info_t 	    _team_info;
		bool 	     	    _connected;
		int 	    	    _sock;
		struct sockaddr_in* _target;
};
