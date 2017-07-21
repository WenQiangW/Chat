#include "window.h"

window::window()
{
	initscr();
	curs_set(0);
}

window::~window()
{
	delwin(header);
	delwin(input);
	delwin(friends_list);
	delwin(output);
	endwin();

}
//获取窗口内的消息
void window::get_str(WINDOW* win,std::string& out)
{
	char msg[1024];
	wgetnstr(win,msg,sizeof(msg));
	out = msg;
}

void window::put_str_to_win(WINDOW* w,int y,int x,std::string& msg)
{
	mvwaddstr(w,y,x,msg.c_str());
}
void window::clear_win_line(WINDOW* w,int begin,int lines)
{
	while(lines-- >0)
	{
		//移动光标
		wmove(w,begin++,0);
		wclrtoeol(w);
	}
}
WINDOW* window::create_newwin(int _h,int _w,int _y,int _x)
{
	WINDOW *win = newwin(_h,_w,_y,_x);
	box(win,0,0);
	return win;
}
void window::create_header()
{
	int _y = 0;
	int _x = 0;
	int _h = LINES/5;
	int _w = COLS;
	header = create_newwin(_h,_w,_y,_x);
}
void window::create_output()
{
	int _y = LINES/5;
	int _x = 0;
	int _h = (LINES*3)/5;
	int _w = (COLS*3)/4;
	output = create_newwin(_h,_w,_y,_x);
}
void window::create_friends_list()
{
	int _y = LINES/5;
	int _x = (COLS*3)/4;
	int _h = (LINES*3)/5;
	int _w = COLS/4;
	friends_list = create_newwin(_h,_w,_y,_x);
}
void window::create_input()
{
	int _y =(LINES*4)/5;
	int _x = 0;
	int _h = LINES/5;
	int _w = COLS;
	input = create_newwin(_h,_w,_y,_x);
}


//int main()
//{
//	window win;
//	win.create_header();
//	sleep(1);
//	wrefresh(win.header);
//	win.create_output();
//	sleep(1);
//	wrefresh(win.output);
//	win.create_friends_list();
//	sleep(1);
//	wrefresh(win.friends_list);
//	win.create_input();
//	sleep(1);
//	wrefresh(win.input);
//		
//	//放置消息
//	std::string msg = "please Enter#";
//	mvwaddstr(win.input,1,2,msg.c_str());
//	wrefresh(win.input);
//	sleep(2);
//	int x=0,y=0;
//	getmaxyx(win.output,y,x);
//
//	int hx = 0,hy=0;
//	getmaxyx(win.header,hy,hx);
//	int i=1;
//	int j=1;
//	std::string running = "welcome to chat system";
//	while(1)
//	{
//		//header跑马灯实现
//		
//		mvwaddstr(win.header,hy/2,j++,running.c_str());
//		wrefresh(win.header);
//		usleep(200000);
//		win.clear_win_line(win.header,hy/2,1);
//		win.create_header();
//		wrefresh(win.header);
//		if(j == hx)
//		{
//			j=1;
//		}
//
//
//		//output 循环放出消息
//		//mvwaddstr(win.output,i,2,msg.c_str());
//		//wrefresh(win.output);
//		//usleep(200000);
//		//i++;
//		//i %=(y-1);
//		//if(i==0)
//		//{
//		//	i=1;
//		//	win.clear_win_line(win.output,1,y-1);
//		//	win.create_output();
//		//	wrefresh(win.output);
//		//}
//	}
//	return 0;
//}
