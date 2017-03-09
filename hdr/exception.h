#include <stdexcept> 
#include <string>

struct MutexInitException : public std::exception
{
	MutexInitException(const std::string& _str) : m_desc(_str) {}
	virtual ~MutexInitException()throw() {}
	std::string m_desc;
};

struct MutexDestroyException : public std::exception
{
	MutexDestroyException(const std::string& _str): m_desc(_str) {}
	virtual ~MutexDestroyException()throw() {}
	std::string m_desc;
};

struct MutexTryLockException : public std::exception
{
	MutexTryLockException(const std::string& _str) : m_desc(_str) {}
	virtual ~MutexTryLockException()throw() {}
	std::string m_desc;
};

struct MutexLockException : public std::exception
{
	MutexLockException(const std::string& _str): m_desc(_str) {}
	virtual ~MutexLockException()throw() {}
	std::string m_desc;
};

struct MutexUnlockException : public std::exception
{
	MutexUnlockException(const std::string& _str) : m_desc(_str) {}
	virtual ~MutexUnlockException()throw() {}
	std::string m_desc;
};

struct MutexTimedlockException : public std::exception
{
	MutexTimedlockException(const std::string& _str) : m_desc(_str) {}
	virtual ~MutexTimedlockException()throw() {}
	std::string m_desc;
};
