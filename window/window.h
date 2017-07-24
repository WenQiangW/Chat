#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <string>
#include <unistd.h>
class window
{
public:
	window();
	~window();
	//清除窗口内消息
	void clear_win_line(WINDOW* w,int begin,int lines);
	//从窗口获取消息
	void get_str(WINDOW* win,std::string& out);
	//向窗口放置消息
	void put_str_to_win(WINDOW* w,int y,int x,std::string& msg);
	WINDOW* create_newwin(int _h,int _w,int _y,int _x); 
	void create_header();
	void create_output();
	void create_friends_list();
	void create_input();

public:
	WINDOW* header;//标题窗口句柄
	WINDOW* output;//输出窗口句柄
	WINDOW* friends_list;//好友列表窗口句柄
	WINDOW* input;//输入窗口句柄
};
#endif
