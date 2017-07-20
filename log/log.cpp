#include "log.h"


std::string err_list[]={
	"SUCCESS",
	"NOTICE",
	"WARING",
	"ERROR",
	"FATAL",
};
void write_log(const std::string& msg,int level)
{
#ifdef _STDOUT
	std::cerr<<"[ "<<msg<< " ] ["<<err_list[level]<<" ]"<<std::endl;

#endif	
}
