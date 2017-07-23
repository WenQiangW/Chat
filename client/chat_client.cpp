#include "udp_client.h"
#include "data.h"
#include "window.h"
#include <signal.h>

typedef struct net_window
{
	udp_client *cp;
	window *wp;
}net_window_t,*net_window_p;

std::string name;
std::string school;
std::vector<std::string> fl;//朋友列表
udp_client *qclient = NULL;
int flag = 1;//退出标志

void usage(const char* arg)
{
	std::cout<<"Usage: "<<arg<<"[client_ip] [client_port]" <<std::endl;
}
void quit(int n)
{
	std::string out;
	data q;
	q.nick_name = name;
	q.school = q.school;
	q.cmd = "QUIT";
	q.msg = "";
	q.data_to_string(out);
	qclient->send_msg(out);
	endwin();
	exit(1);
	//flag = 0;
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
		
		if(i == x - msg.length())
			i=1;		  	
		winp->create_header();
		wrefresh(winp->header);
	}
}
//添加好友
void add_user(std::string& user)
{
	std::vector<std::string>::iterator iter = fl.begin();
	for(;iter!= fl.end();++iter)
	{	
		if(user == *iter)
			return ;
	}
	fl.push_back(user);
}
void del_user(std::string& user)
{
	std::vector<std::string>::iterator iter = fl.begin();
	for(;iter!= fl.end();)
	{	
		if(user == *iter)
		{
			iter = fl.erase(iter);
			break;
		}
		else
			++iter;
	}

}
void* show_output_fl(void *arg)
{
	net_window_p obj = (net_window_p)arg;
	window *winp = obj->wp;
	udp_client *clientp = obj->cp;
	
	//显示输出窗口:读取数据，反序列化
	data r;
	std::string r_str;
	std::string show_str;
	std::string friends;
	int i = 1,j =1;
	int x =0,y=0;
	int fx=0,fy=0;
	winp->create_output();
	winp->create_friends_list();
	wrefresh(winp->output);
	wrefresh(winp->friends_list);
	while(1)
	{
		//读取数据，反序列化
		clientp->recv_msg(r_str);
		r.string_to_data(r_str);
		//判断是否为退出的客户端
		//构建输出语句和朋友列表信息
		show_str = r.nick_name;
		show_str += "- ";
		show_str += r.school;
		friends = show_str;
		show_str += "# ";
		show_str += r.msg;
		if(r.cmd == "QUIT")
		{
			del_user(friends);
		}
		else
		{
			add_user(friends);
		
			//输出到output窗口
			winp->put_str_to_win(winp->output,i++,1,show_str);
			wrefresh(winp->output);
			//判断是否输满
			getmaxyx(winp->output,y,x);
			if(i == y-1)
			{
				i=1;
				usleep(200000);
				
				winp->clear_win_line(winp->output,1,y-1);
				winp->create_output();
				wrefresh(winp->output);
			}
		}
		//显示好友列表
		std::vector<std::string>::iterator iter = fl.begin();
		for(;iter!= fl.end();++iter)
		{	
			winp->put_str_to_win(winp->friends_list,j++,1,*iter);
			wrefresh(winp->friends_list);
			getmaxyx(winp->output,fy,fx);
			if(j == fy-1)
			{
				j=1;
				winp->clear_win_line(winp->friends_list,1,fy-1);
				winp->create_friends_list();
				wrefresh(winp->friends_list);
			}
		}
		j=1;
		usleep(200000);
	}	
}
void* show_input(void *arg)
{
	net_window_p obj = (net_window_p)arg;

	window *winp = obj->wp;
	udp_client *clientp = obj->cp;
	
	std::string str = "Please Enter# ";
	std::string out;
	data w;
	w.nick_name = name;
	w.school = school;
	w.cmd = "";
	while(1)
	{
		winp->create_input();
		winp->put_str_to_win(winp->input,1,2,str);
		wrefresh(winp->input);
		winp->get_str(winp->input,w.msg);
		//序列化，发送
		w.data_to_string(out);
		clientp->send_msg(out);
		//清屏
		winp->clear_win_line(winp->input,1,1);
		winp->create_input();
		wrefresh(winp->input);
	}
}

int main(int argc,char*argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return -1;
	}

	std::cout<<"please enter nick_name:";
	std::cin>>name;
	std::cout<<"please enter school:";
	std::cin>>school;
	udp_client client(argv[1],atoi(argv[2]));
	client.init_client();
	window win;
	
	net_window_t nw={&client,&win};
	qclient = &client;

	signal(2,quit);
	//if(flag == 0)
	//{
	//	exit(1);
	//}
	pthread_t theader,toutput_fl,tinput;
	pthread_create(&theader,NULL,show_header,&nw);
	pthread_create(&toutput_fl,NULL,show_output_fl,&nw);
	pthread_create(&tinput,NULL,show_input,&nw);
	
	pthread_join(theader,NULL);
	pthread_join(toutput_fl,NULL);
	pthread_join(tinput,NULL);
	
	return 0;
}

