
#include "udp_server.h"

udp_server::udp_server(const std::string& _ip,int _port):ip(_ip),port(_port),sock(-1),data_pool(256)
{}

int udp_server::init_server()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		write_log("socket error",FATAL);
		return -1;
	}
	struct sockaddr_in local;
	local.sin_family =AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());

	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		write_log("bind sock error",FATAL);
		return -2;	
	}
	return 0;
}
//添加用户，ip标记用户(有问题NAT技术)
int udp_server::add_online_user(struct sockaddr_in *client)
{
	online_user.insert(std::pair<int,struct sockaddr_in>(client->sin_addr.s_addr,*client));
}
//删除用户
int udp_server::del_online_user(struct sockaddr_in *client)
{	
	std::map<int,struct sockaddr_in>::iterator iter = online_user.find(client->sin_addr.s_addr);
	if(iter != online_user.end())
		online_user.erase(iter);
}

//从客户端读取数据，然后写到data_pool里面
//out指从客户端输出的数据
int udp_server::recv_msg(std::string& out)
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
		data_pool.put_data(out);		
		data d;
		d.string_to_data(out);
		if(d.cmd == "QUIT")
		{
			del_online_user(&peer);
		}
		else
		{
			add_online_user(&peer);	
		}
		return 0;
	}
	return -1;
}
//将消息发送出去,in指从pool得到的数据
int udp_server::send_msg(const std::string& in,\
		struct sockaddr_in& peer,const socklen_t& len)
{
	int ret = sendto(sock,in.c_str(),in.size(),0,\
			(struct sockaddr*)&peer,len);
	if(ret < 0 )
	{
		write_log("server send_msg errror",WARNING);
		return -1;
	}
	return 0;
}
//从数据池里面取出消息，广播发送给每个用户。
int udp_server::brocast_msg()
{
	std::string msg ;
	data_pool.get_data(msg);
	std::map <int, struct sockaddr_in >::iterator iter = online_user.begin();
	for(;iter != online_user.end();++iter)
	{
		send_msg(msg,iter->second,sizeof(iter->second));
	}
	return 0;
}

udp_server::~udp_server()
{
	if(sock >0)
		close(sock);
}


