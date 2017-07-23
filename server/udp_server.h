
#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "log.h"
#include "pool.h"
#include "data.h"
class udp_server
{
public:
	udp_server(const std::string& _ip,int port);
	int init_server();
	int recv_msg(std::string& out);
	int send_msg(const std::string& in,struct sockaddr_in& peer,\
			const socklen_t& len);
	int add_online_user(struct sockaddr_in *client);
	int del_online_user(struct sockaddr_in *client);
	int brocast_msg();
	~udp_server();
private:
	udp_server(const udp_server&);
private:
	std::string ip;
	int port;
	int sock;
	std::map<int,struct sockaddr_in> online_user;
	pool data_pool;//数据池是一个vector<string>
};
#endif
