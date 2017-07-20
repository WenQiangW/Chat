
#include "pool.h"

pool::pool(int size)
	:data_pool(size)
	,c_step(0)
	,p_step(0)
	,cap(size)
{
	sem_init(&c_sem,0,0);
	sem_init(&p_sem,0,size);
}
int pool::get_data(std::string& out)
{
	sem_wait(&c_sem);
	out = data_pool[c_step++];
	c_step %= cap;
	sem_post(&p_sem);
}
int pool::put_data(const std::string& in)
{
	sem_wait(&p_sem);
	data_pool[p_step++] = in;
	p_step %= cap;
	sem_post(&c_sem);
}
pool::~pool()
{
	sem_destroy(&c_sem);
	sem_destroy(&p_sem);
}
