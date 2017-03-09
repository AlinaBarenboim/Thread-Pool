#include "mutex.h"
#include <time.h>
#include <stdexcept> 
#include <cassert>
#include <cerrno>
#include "exception.h"
#include <string>

Mutex::Mutex(pthread_mutexattr_t* _attr) : m_attr(_attr)
{
	int result = pthread_mutex_init(&m_mutex,_attr);
	if (result)
	{
		assert(result != EBUSY);
		assert(result != EINVAL);
		if (result == EAGAIN) 
		{
			throw MutexInitException("The system lacked the necessary resources (other than memory) to initialize 															another mutex.");
		}
		if (result == ENOMEM) 
		{
			throw MutexInitException("Insufficient memory exists to initialize the mutex. ");
		}
		if (result == EPERM) 
		{
			throw MutexInitException("The caller does not have the privilege to perform the operation.");
		}
	}
}



Mutex::~Mutex()
{
	if (pthread_mutex_destroy(&m_mutex))
	{
		throw std::runtime_error ("mutex destroy error");
	}
	int result = pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock()
{
	int result;
	if (result = pthread_mutex_lock(&m_mutex) != 0)
	{
		throw std::runtime_error ("mutex lock error");
	}
}

bool Mutex::TryLock()
{
	int result;
	if (result = pthread_mutex_trylock(&m_mutex) != 0)
	{
		throw std::runtime_error ("mutex try lock error");
	}
	return true;
}

void Mutex::UnLock()
{
	int result;
	if (result = pthread_mutex_unlock(&m_mutex) != 0)
	{
		throw std::runtime_error ("mutex lock error");
	}
}

void Mutex::TimeLock (unsigned int _miliSec)//(const struct timespec* _deltatime)
{
	struct timespec timeout;
	
	clock_gettime(CLOCK_REALTIME, &timeout);
	
	timeout.tv_sec += _miliSec/1000;
	timeout.tv_nsec += (_miliSec % 1000)*1000000;
	int result = pthread_mutex_timedlock(&m_mutex, &timeout);
	if (result)
	{
		assert (result!=EINVAL);
		assert (result!=EAGAIN);
		assert (result!=EDEADLK);
		assert (!"unknown error code");
		throw std::runtime_error ("ETIMEDOUT: The mutex could not be locked before the specified timeout expired");
	}
}
	
