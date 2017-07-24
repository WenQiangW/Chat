#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <string>
#include "base_json.h"

class data
{
public:
	data();
	~data();
	//数据的序列化
	void data_to_string(std::string& out);
	//数据的反序列化
	void string_to_data(std::string& in);
public:
	std::string nick_name;
	std::string school;
	std::string msg;
	std::string cmd;
};
#endif
