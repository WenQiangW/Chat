
#include "udp_client.h"

udp_client::udp_client(const std::string& _ip,int _port):ip(_ip),port(_port),sock(-1)
{}

int udp_client::init_client()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		write_log("socket error",FATAL);
		return -1;
	}

}

//从server端接受数据
int udp_client::recv_msg( std::string& out)
{
	char buf[1024];
	//输入输出参数，从远端(client)读取
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);
	int ret = recvfrom(sock,buf,sizeof(buf)-1,0,\
			(struct sockaddr*)&peer,&len);
	if(ret > 0)
	{
		buf[ret] = 0;
		out = buf;
		//add_online_user(&peer);	
		return 0;
	}
	return -1;
}
//从标准输入读取数据，发送数据
int udp_client::send_msg(const std::string & in)
{
	struct sockaddr_in server;
	server.sin_family =AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ip.c_str());

	int ret = sendto(sock,in.c_str(),in.size(),0,\
			(struct sockaddr*)&server,sizeof(server));
	if(ret < 0 )
	{
		write_log("client send_msg errror",WARNING);
		return -1;
	}
	return 0;
}

udp_client::~udp_client()
{
	if(sock >0)
		close(sock);
}


