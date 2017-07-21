#include "udp_client.h"
#include "data.h"
#include "window.h"

typedef struct net_window
{
	udp_client *cp;
	window *wp;
}net_window_t,*net_window_p;


void usage(const char* arg)
{
	std::cout<<"Usage: "<<arg<<"[client_ip] [client_port]" <<std::endl;
}
void* show_header(void *arg)
{
	net_window_p obj = (net_window_p)arg;

	window *winp = obj->wp;
	udp_client *clientp = obj->cp;
	
	winp->create_header();
	wrefresh(winp->header);
	int x=0,y=0;
	getmaxyx(winp->header,y,x);
	std::string msg = "welcome to chat sysytem";
	int i=1;
	//跑马灯实现，先放置消息，然后清屏重画，
	while(1)
	{
		winp->put_str_to_win(winp->header,y/2,i++,msg);
		wrefresh(winp->header);
		usleep(200000);
		winp->clear_win_line(winp->header,y/2,1);
		
		if(i == x)
			i=1;		  	
		winp->create_header();
		wrefresh(winp->header);
	}
}
void* show_output_fl(void *arg)
{

}
void* show_input(void *arg)
{
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
	window win;
	
	net_window_t nw={&client,&win};

	pthread_t theader,toutput_fl,tinput;
	pthread_create(&theader,NULL,show_header,&nw);
	pthread_create(&toutput_fl,NULL,show_output_fl,&nw);
	pthread_create(&tinput,NULL,show_input,&nw);
	
	pthread_join(theader,NULL);
	pthread_join(toutput_fl,NULL);
	pthread_join(tinput,NULL);
	
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

