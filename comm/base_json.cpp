
#include "base_json.h"
//序列化
void serialize(Json::Value& val,std::string &out)
{
	Json::FastWriter w;
	out = w.write(val);
}
//反序列化
void un_serialize(Json::Value& val,std::string &in)
{
	Json::Reader read;
	read.parse(in,val,false);
}
