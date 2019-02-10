#include "udp.hpp"


Udp::Udp():
	_data(0),
	_team_info(0),
	_connected(0),
	_sock(0),
	_target(new struct sockaddr_in)
{
	std::cout << "Udp constructor" << std::endl;
	_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // pretty constants
	if(_sock == -1)
	{
		std::cout << "Error in Socket constructor!" << std::endl;
		perror("socket");
	}
};

~Udp()
{
	std::cout << "Udp destructor" << std::endl;
}


// rewrite this kind of example

const int Udp::getTime() const
{
	return 0;
}

const & data_t Udp::getData() const
{
	return _data;
}


const & team_info_t Udp::getTeamInfo() const
{
	return _team_info;
}

const bool Udp::isConnected() const
{
	return _connected;
}


const int Udp::getSock()
{
	return _sock;
}

// add data Dump


void Udp::Dump()
{
	std::cout << "Soket: " << sock << std::endl;
	std::cout << "isConnected: " << _connected << std::endl;
}

