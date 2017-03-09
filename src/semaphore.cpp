#include "semaphore.h"
 #include <stdexcept> 
#include <iostream>
Semaphore::Semaphore(int _pshared, unsigned int _value)
{
	sem_init(&m_semaphore, _pshared, _value);
}

Semaphore::~Semaphore()
{
	if (sem_destroy(&m_semaphore))
	{
		throw std::runtime_error ("semaphore destroy failed");
	}
}

int Semaphore::Post()
{
	int result;
	if (result = sem_post(&m_semaphore) != 0)
	{
		throw std::runtime_error ("semaphore post failed");
	}
	return result;
}

int Semaphore::Wait()
{
	int result;
	if (result = sem_wait(&m_semaphore) != 0)
	{
		throw std::runtime_error ("semaphore wait failed");
	}
	return result;
}

int Semaphore::TryWait()
{
	int result;
	if (result = sem_trywait(&m_semaphore) != 0)
	{
		throw std::runtime_error ("semaphore try  wait failed");
	}
	return result;
}

int Semaphore::TymedWait(const struct timespec* _abs_timeout)
{
	int result;
	if (result = sem_timedwait(&m_semaphore, _abs_timeout) != 0)
	{
		throw std::runtime_error ("semaphore timed  wait failed");
	}
	return result;
}
	
