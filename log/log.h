#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <string>

#define SUCCESS 0
#define NOTICDE 1
#define WARNING  2
#define ERROR 3
#define FATAL 4

extern std::string err_list[];
void write_log(const std::string &msg,int level);

#endif
