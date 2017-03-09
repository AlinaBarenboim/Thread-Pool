#include "runnable.h"
#include <string>
#include <iostream>
#include <unistd.h>

class Tester :public Runnable
{
public:
	Tester (std::string _str, size_t _counter) : m_str(_str), m_counter(_counter) {}
	void operator()()
	{
		while (m_counter--)
		{
			std::cout << m_str << std::endl;
		}		
	}

private:
	std::string m_str;
	size_t m_counter;
};
