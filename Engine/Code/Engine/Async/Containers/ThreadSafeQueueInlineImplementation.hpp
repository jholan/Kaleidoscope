#include "Engine/Async/Containers/ThreadSafeQueue.hpp"



template <typename T>
void ThreadSafeQueue<T>::Enqueue(const T& v)
{
	m_mutexLock.Lock();

	// Critical Section
	m_data.push( v ); 

	m_mutexLock.Unlock();
}


template <typename T>
bool ThreadSafeQueue<T>::Dequeue(T* out_v) 
{
	m_mutexLock.Lock();

	// Critical Section
	bool isNotEmpty = !m_data.empty();
	if (isNotEmpty) 
	{
		*out_v = m_data.front();
		m_data.pop(); 
	}

	m_mutexLock.Unlock();
	return isNotEmpty; 
}