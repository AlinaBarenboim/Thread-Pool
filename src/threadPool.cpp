#include <queue>
#include "threadPool.h"
#include <tr1/memory>
#include "runnable.h"
#include "testClass.h"
#include "thread.h"
#include <vector>
#include "safeQueue.h"


namespace advcpp
{

static bool m_isActive = true;

namespace details
{
class Worker : public Runnable
{
public:	
	Worker(SafeQueue<std::tr1::shared_ptr<Runnable> >& _tasksQueue) : m_tasks(_tasksQueue) {}
	~Worker(){}
	void operator()()
	{
		while(m_isActive)
		{
			std::tr1::shared_ptr<Runnable> r = m_tasks.Pop_Front(); //get next task from queue
			if (r)
			{
				(*r)();//run task
			}
		}

	}		
	
private:
	SafeQueue<std::tr1::shared_ptr<Runnable> >& m_tasks;
};
} //end of details namespace

ThreadPool::ThreadPool( size_t _poolSize ) :  m_tasks(_poolSize)
{
	std::tr1::shared_ptr<Runnable>  m_worker (new details::Worker(m_tasks ));
	for (int i = 0; i < _poolSize; ++i)
	{
		Thread* t = new Thread(m_worker);
		m_threads.push_back(t);
	}
}

ThreadPool::~ThreadPool()
{
	m_isActive = false;
	for(size_t counter = 0; counter < m_threads.size(); ++counter)
	{
		m_threads[counter]->Join();
	}

}

void ThreadPool::RunTask(std::tr1::shared_ptr<Runnable> _task)
{
	m_tasks.Push_Back(_task);
}


void ThreadPool::StopPool() //FIXME
{
	//m_isActive = false;
}
}//end of namespace advcpp
