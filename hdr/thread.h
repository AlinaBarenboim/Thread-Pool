#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdexcept>
#include <tr1/memory>
#include <pthread.h>
#include "uncopyble.h"
#include "thread.h"

class iostream;
class Runnable;

class Thread: private Uncopyable
{
public:
	Thread(std::tr1::shared_ptr<Runnable> _runnable , const pthread_attr_t* _attr = 0);
	~Thread();
	int Join();	
	int Cancel();
	int Detach();
	pthread_t GetId() const {return m_Id;}
	//std::tr1::shared_ptr<Runnable>& GetRunnable() { return m_runnable;}
	bool IsRunning() const { return m_status;}
	Runnable& GetRun()const {
	if (!m_runnable)
	{
		throw std::runtime_error ("runnable nox exist");
	}
	return *(m_runnable);}
	
    
private:
	std::tr1::shared_ptr<Runnable> m_runnable;
	pthread_t m_Id;
	bool m_status;
};

#endif /* __THREAD_H__ */

