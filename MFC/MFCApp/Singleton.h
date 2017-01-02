
#ifndef _SINGLETON_H
#define _SINGLETON_H

#pragma once

template <class T, class Interface = T>
class Singleton
{
public:
	static Interface* GetInstance()
	{
		if (NULL == m_ptSingleton) m_ptSingleton = new T();
		return m_ptSingleton;
	}
	virtual ~Singleton() { m_ptSingleton = NULL; }
private:
	static T *m_ptSingleton;
};
template <typename T, class Interface> T* Singleton<T, Interface>::m_ptSingleton = NULL;

#endif
