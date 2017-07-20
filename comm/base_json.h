#ifndef _BASE_JSON_H__
#define _BASE_JSON_H__


#include <iostream>
#include <string>
#include "json/json.h"

//序列化
void serialize(Json::Value& val,std::string &out);
//反序列化
void un_serialize(Json::Value& val,std::string &in);

#endif
