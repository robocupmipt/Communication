#pragma once
#include "sys/socket.h"
#include "sys/types.h"

typedef int data_t;
typedef int team_info_t;


class Udp
{
	public:
		Udp();
		~Udp();
		int 			getTime();
		const &data_t 		getData() const;
		const &team_info_t 	getTeamInfo() const;
		bool 			isConnected() const;
		int 			getSock();
		void 			Dump();
	private:
		data_t      	    _data;
		team_info_t 	    _team_info;
		bool 	     	    _connected;
		int 	    	    _sock;
		struct* sockaddr_in _target;
};


