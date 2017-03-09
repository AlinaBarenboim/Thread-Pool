#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <semaphore.h>
#include "uncopyble.h"

class Semaphore: private Uncopyable
{
public:
	Semaphore(int _pshared = 0, unsigned int _value = 1);
	~Semaphore();

	int Post();
	int Wait();
	
	int TryWait();
	int TymedWait(const struct timespec* _abs_timeout);

private:
	sem_t m_semaphore;		
};



#endif /* __SEMAPHORE_H__ */
