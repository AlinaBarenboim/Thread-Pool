#ifndef __MUTEX_H__
#define __MUTEX_H__
	
#include "pthread.h"
#include "uncopyble.h"

class Mutex : private Uncopyable
{
public:
	Mutex(pthread_mutexattr_t* _attr = 0);// : m_attr(_attr) {	pthread_mutex_init(&m_mutex,m_attr);}
	~Mutex();
	
	void Lock();
	void UnLock();
	bool TryLock();
	//void TimeLock(const struct timespec* _deltatime);
	void TimeLock (unsigned int _miliSec);	
		
private:
	pthread_mutex_t m_mutex;
	pthread_mutexattr_t* m_attr;
};


#endif /* __MUTEX_H__ */

