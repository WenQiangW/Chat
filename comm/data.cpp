#include "data.h"

data::data(){}
data::~data(){}

//将data 序列化
void data::data_to_string(std::string& out)
{
	Json::Value val;
	val["nick_name"] = nick_name;
	val["school"] = school;
	val["msg"] = msg;
	val["cmd"] = cmd;
	serialize(val,out);

}
//将序列化in 转化为string
void data::string_to_data(std::string& in)
{
	Json::Value val;
	un_serialize(val,in);
	nick_name = val["nick_name"].asString();
	school = val["school"].asString();
	msg = val["msg"].asString();
	cmd = val["cmd"].asString();
}

//int main()
//{
//	data d;
//	d.nick_name = "boy";
//	d.school = "bit";
//	d.msg = "hello";
//    d.cmd = "";
//	std::string out;
//	d.data_to_string(out);
//	std::cout <<"out:"<<out<<std::endl;
//
//	data r;
//	r.string_to_data(out);
//	std::cout <<r.nick_name<<"-"<<r.school<<"-"<<r.msg<<std::endl;
//	return 0;
//}
