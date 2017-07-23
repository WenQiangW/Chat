#include "udp_server.h"

void usage(const char* arg)
{
	std::cout<<"Usage: "<<arg<<"[server_ip] [server_port]" <<std::endl;
}
void* brocast(void *arg)
{
	udp_server* serverp = (udp_server*)arg;
	while(1)
	{
		serverp->brocast_msg();
	}
}
int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	udp_server server(argv[1],atoi(argv[2]));
	server.init_server();
	//精灵化
	//daemon(0,0);
	
	//创建线程，新线程给客户端发数据，主线程将从客户端读取的数据写入pool
	pthread_t id;
	pthread_create(&id,NULL,brocast,(void*)&server);

	std::string msg;
	while(1)
	{
		server.recv_msg(msg);
	//	std::cout<<"client echo#: "<<msg<<std::endl;
	}

	return 0;
}
