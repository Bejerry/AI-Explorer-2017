#pragma once

#include <string>
using namespace std;

template <typename T>
class AlgProceedItf
{
public:
	static T& GetProcessor(void)
	{
		if (NULL == m_proceed)
		{
			m_proceed = new T();
		}
		return *m_proceed;
	}

	static T* m_proceed;
public:
	virtual void SetAlgPara(CString filePath, CString targetFile, UINT thresh) = 0;
	virtual void Start(void) = 0;
};
template <typename T>
T* AlgProceedItf<T>::m_proceed = NULL;