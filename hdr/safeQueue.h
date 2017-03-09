#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__

#include "mutex.h"
#include "semaphore.h"
#include "guard.h"
#include <queue>

template<class T>
class SafeQueue
{
public:
	SafeQueue(size_t _size) : m_sem_occupied(0) {}
	~SafeQueue(){}
	void Push_Back(const T& _value);
	T Pop_Front();
private:	
	std::queue<T> m_queue;
	Mutex m_mutex;	
	Semaphore m_sem_occupied;
};

template<class T>
void SafeQueue<T>::Push_Back(const T& _value)
{
		{
			Guard guard(m_mutex);
			m_queue.push(const_cast<T&>(_value));
		}
		m_sem_occupied.Post();
}

template<class T>
T SafeQueue<T>::Pop_Front()
{
	m_sem_occupied.Wait();
	{
		Guard guard(m_mutex);
		T t = (m_queue.front());
		m_queue.pop();
		return t;
	}
}

#endif /* __SAFE_QUEUE_H__ */

