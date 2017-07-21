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
	void clear_win_line(WINDOW* w,int begin,int lines);
	void get_str(WINDOW* win,std::string& out);
	void put_str_to_win(WINDOW* w,int y,int x,std::string& msg);
	WINDOW* create_newwin(int _h,int _w,int _y,int _x); 
	void create_header();
	void create_output();
	void create_friends_list();
	void create_input();

public:
	WINDOW* header;
	WINDOW* output;
	WINDOW* friends_list;
	WINDOW* input;
};
#endif
