#ifndef __UNCOPYABLE_H__
#define __UNCOPYABLE_H__


class Uncopyable
{
	protected:
	Uncopyable(){}
	virtual ~Uncopyable(){}
	
	private:
	Uncopyable(const Uncopyable&);
	const Uncopyable& operator=(const Uncopyable&);
};

#endif /* __UNCOPYABLE_H__ */
