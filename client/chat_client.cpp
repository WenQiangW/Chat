

#include "udp_client.h"

void usage(const char* arg)
{
	std::cout<<"Usage: "<<arg<<"[client_ip] [client_port]" <<std::endl;
}
int main(int argc,char*argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return -1;
	}
	udp_client client(argv[1],atoi(argv[2]));
	client.init_client();
	while(1)
	{
		std::cout<<"Please Enter# ";
		fflush(stdout);
		char buf[1024];
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s >0)
		{
			buf[s] = 0;
			int ret = client.send_msg(buf);
		}
		std::string msg;
		client.recv_msg(msg);
		std::cout <<"server echo# "<<msg<<std::endl;
	}
	return 0;
}

