#pragma once

#include <queue>

#include "Engine/Async/Mutex.hpp"



template <typename T>
class ThreadSafeQueue
{
public:
	ThreadSafeQueue() {};
	~ThreadSafeQueue() {};

	void Enqueue(const T& v);
	bool Dequeue(T* out_v); // return if it succeeds



private:
	std::queue<T> m_data; 
	Mutex		  m_mutexLock; 
};




#include "Engine/Async/Containers/ThreadSafeQueueInlineImplementation.hpp"