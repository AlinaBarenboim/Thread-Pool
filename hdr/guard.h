#ifndef __GUARD_H__
#define __GUARD_H__

#include <stdexcept> 
#include "pthread.h"
#include "mutex.h"

class Guard : public Uncopyable
{
public:
	Guard(Mutex& _mutex) :m_mutex(_mutex)
	{
		try
		{
			m_mutex.Lock();
		}catch(std::runtime_error)
		{
			throw std::runtime_error("mutex lock failed");
		}
//		{
//			throw std::runtime_error("mutex lock failed");
//		}
	}
	~Guard()
	{
//		if(m_mutex.UnLock() !=0)
//		{
//			throw std::runtime_error("mutex unlock failed");
//		}
		try
		{
			m_mutex.UnLock();
		}catch(std::runtime_error)
		{
			throw std::runtime_error("mutex unlock failed");
		}
	}
	
private:
	Mutex& m_mutex;
};

#endif /* __GUARD_H__ */
