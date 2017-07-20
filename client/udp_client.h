
#ifndef _udp_client_H_
#define _udp_client_H_


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "log.h"


class udp_client
{
public:
	udp_client(const std::string& _ip,int port);
	int init_client();
	int recv_msg(std::string& out);
	int send_msg(const std::string& in);
	//int add_online_user(struct sockaddr_in *client);
	~udp_client();
private:
	udp_client(const udp_client&);
private:
	std::string ip;
	int port;
	int sock;
	//std::map<int,struct sockaddr_in> online_user;
};
#endif
