#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <iostream>
#include <tr1/memory>
#include <queue>
#include "runnable.h"
#include "uncopyble.h"
#include "thread.h"
#include "mutex.h"
#include "semaphore.h" 
#include "guard.h"
#include <vector>
#include "safeQueue.h"

namespace advcpp
{

namespace details
{
class Worker;
}

class ThreadPool: private Uncopyable
{
public:
	static const size_t DEFAULT_SIZE = 10;
	ThreadPool( size_t _poolSize = DEFAULT_SIZE);
	~ThreadPool();
	void RunTask(std::tr1::shared_ptr<Runnable>  _task);
	void StopPool(); //can be in destructor
	
private:
	std::tr1::shared_ptr<details::Worker> m_worker;
	std::vector<Thread*> m_threads;
	SafeQueue<std::tr1::shared_ptr<Runnable> > m_tasks;
};

}//end of advcpp namespace

#endif /* __THREAD_POOL__H__ */
