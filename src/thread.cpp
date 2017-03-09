#include "thread.h"
#include <iostream>
#include "runnable.h"
#include <stdexcept> 
 
static void* ThreadFunc(void* _arg)
{
	Thread* thread = (Thread*)_arg;
	try
	{
		thread->GetRun()();

	}catch(...)
	{ std::cout << "thread run error" << std::endl;}
	return 0;
}

Thread::Thread(std::tr1::shared_ptr<Runnable> _runnable, const pthread_attr_t* _attr) 							: m_runnable(_runnable),
	 m_Id(0),
	 m_status(true) 
{
	pthread_create(&m_Id, _attr, ThreadFunc, this);
}


Thread::~Thread()
{
	if (m_status)
	{
		Join();
	}
}

int Thread::Join()
{
	int result = -1;
	if(m_status)
	{
		m_status = false;
		if (result = pthread_join(m_Id,0) != 0)
		{
			m_status = true;
			throw std::runtime_error("thread join error");
		}
	}
	return result;
}

int Thread::Cancel()
{
	int result = -1;
	if(m_status)
	{
		m_status = false;
		if(result =  pthread_cancel(m_Id) != 0)
		{
			m_status = true;
			throw std::runtime_error("thread cancel error");
		}
	}
	return result;
}

int Thread::Detach()
{
	int result = -1;
	if(m_status)
	{
		m_status = false;
		if(result =  pthread_detach(m_Id) != 0)
		{
			m_status = true;
			throw std::runtime_error("thread cancel error");
		}
	}
	return result;
}


