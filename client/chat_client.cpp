

#include "udp_client.h"
#include "data.h"
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
		data w;
		std::cout<<"please enter nick_name:";
		std::cin>>w.nick_name;
		std::cout<<"please enter school:";
		std::cin>> w.school;
		std::cout<<"Please Enter# ";
		std::cin >> w.msg;
		//fflush(stdout);
		//char buf[1024];
		//ssize_t s = read(0,buf,sizeof(buf)-1);
		//if(s >0)
		//{
		//	buf[s] = 0;
		//	
		//	int ret = client.send_msg(buf);
		//}
		std::string msg;
		w.data_to_string(msg);
		client.send_msg(msg);
		std::string out;
		client.recv_msg(out);
		std::cout <<"server echo# "<<msg<<std::endl;
		data r;
		r.string_to_data(out);
		std::cout<<r.nick_name<<"-"<<r.school<<"-"<<r.msg<<std::endl;
		
	}

	return 0;
}

