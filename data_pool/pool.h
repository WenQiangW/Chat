
#ifndef _POOL_H_
#define _POOL_H_

#include <iostream>
#include <string>
#include <vector>
#include <semaphore.h>

//数据池的实现，是一个环形队列
class pool
{
public:
	pool(int);
	//从数据池取出数据
	int get_data(std::string& out);
	//向数据池中放数据
	int put_data(const std::string& in);
	~pool();

private:
	pool(const pool&);
private:
	sem_t c_sem;//consumer
	sem_t p_sem;//productor 
	std::vector<std::string> data_pool;
	int c_step;//consumer 的步数
	int p_step;//productor 的步数
	int cap;//环形队列的容量
};


#endif
