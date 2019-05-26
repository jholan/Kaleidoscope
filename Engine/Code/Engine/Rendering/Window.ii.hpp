#pragma once
#include "Engine/Rendering/Window.hpp"



// -----------------------------------------------------------------
// WindowMessageCallbackBase 
// -----------------------------------------------------------------
class WindowMessageCallback_Base
{
public:
	WindowMessageCallback_Base() {};
	virtual ~WindowMessageCallback_Base() {};

	virtual void Call(uint messageCode, ulonglong wparam, longlong lparam) = 0;
};



// -----------------------------------------------------------------
// WindowMessageCallback_CFunction
// -----------------------------------------------------------------
class WindowMessageCallback_CFuncton : public WindowMessageCallback_Base
{
public:
	inline WindowMessageCallback_CFuncton(WindowMessage_Callback callback);
	~WindowMessageCallback_CFuncton() {};

	inline virtual void Call(uint messageCode, ulonglong wparam, longlong lparam) override;



public:
	WindowMessage_Callback m_callback;
};


WindowMessageCallback_CFuncton::WindowMessageCallback_CFuncton(WindowMessage_Callback callback)
{
	m_callback = callback;
}


void WindowMessageCallback_CFuncton::Call(uint messageCode, ulonglong wparam, longlong lparam)
{
	m_callback(messageCode, wparam, lparam);
}



// -----------------------------------------------------------------
// WindowMessageCallback_MemberFuction
// -----------------------------------------------------------------
template<typename T, typename DummyCallback>
class WindowMessageCallback_MemberFunction : public WindowMessageCallback_Base
{
public:
	typedef void (T::*WindowMessage_Callback)(uint messageCode, ulonglong wparam, longlong lparam);



public:
	inline WindowMessageCallback_MemberFunction(T* user, DummyCallback callback);
	~WindowMessageCallback_MemberFunction() {};

	inline virtual void Call(uint messageCode, ulonglong wparam, longlong lparam) override;



public:
	T*						m_user;
	WindowMessage_Callback	m_callback;
};


template<typename T, typename DummyCallback>
WindowMessageCallback_MemberFunction<typename T, typename DummyCallback>::WindowMessageCallback_MemberFunction(T* user, DummyCallback callback)
{
	m_user = user;
	m_callback = callback;
}


template<typename T, typename DummyCallback>
void WindowMessageCallback_MemberFunction<typename T, typename DummyCallback>::Call(uint messageCode, ulonglong wparam, longlong lparam)
{
	(m_user->*m_callback)(messageCode, wparam, lparam);
}



// -----------------------------------------------------------------
// Window
// Callbacks
// C Functions
// -----------------------------------------------------------------
void Window::RegisterCallback(WindowMessage_Callback callback)
{
	// Check to see the callback has already been registered
	bool alreadyAdded = false;
	for (int i = 0; i < (int)m_callbacks.size(); ++i)
	{
		WindowMessageCallback_CFuncton* testCallback = dynamic_cast<WindowMessageCallback_CFuncton*>(m_callbacks[i]);

		if (testCallback != nullptr &&
			testCallback->m_callback == callback)
		{
			alreadyAdded = true;
		}
	}


	// SHORT CIRCUIT
	if (alreadyAdded)
	{
		// If it has already been added don't add a second copy
		return;
	}


	// Add the callback if it is unique
	WindowMessageCallback_CFuncton* callbackContainer = new WindowMessageCallback_CFuncton(callback);
	m_callbacks.push_back((WindowMessageCallback_Base*)callbackContainer);
}


void Window::UnregisterCallback(WindowMessage_Callback callback)
{
	for (int i = 0; i < (int)m_callbacks.size(); ++i)
	{
		WindowMessageCallback_CFuncton* testCallback = dynamic_cast<WindowMessageCallback_CFuncton*>(m_callbacks[i]);

		if (testCallback != nullptr &&
			testCallback->m_callback == callback)
		{
			delete m_callbacks[i];
			m_callbacks.erase(m_callbacks.begin() + i);
			break;
		}
	}
}



// -----------------------------------------------------------------
// Callbacks
// Member Functions
// -----------------------------------------------------------------
template<typename T, typename DummyCallback>
void Window::RegisterMemberCallback(T* user, DummyCallback callback)
{
	// Check to see if the callback has already been registered
	bool alreadyAdded = false;
	for (int i = 0; i < (int)m_callbacks.size(); ++i)
	{
		WindowMessageCallback_MemberFunction<T, DummyCallback>* testCallback = dynamic_cast<WindowMessageCallback_MemberFunction<T, DummyCallback>* >(m_callbacks[i]);

		if (testCallback != nullptr				&&
			testCallback->m_user == user		&&
			testCallback->m_callback == callback)
		{
			alreadyAdded = true;
			break;
		}
	}


	// SHORT CIRCUIT
	if (alreadyAdded)
	{
		// If the callback is already registered, don't add it again
		return;
	}


	// Add the callback
	WindowMessageCallback_MemberFunction<T, DummyCallback>* callbackContainer = new WindowMessageCallback_MemberFunction<T, DummyCallback>(user, callback);
	m_callbacks.push_back((WindowMessageCallback_Base*)callbackContainer);
}


template<typename T, typename DummyCallback>
void Window::UnregisterMemberCallback(T* user, DummyCallback callback)
{
	for (int i = 0; i < (int)m_callbacks.size(); ++i)
	{
		WindowMessageCallback_MemberFunction<T, DummyCallback>* testCallback = dynamic_cast<WindowMessageCallback_MemberFunction<T, DummyCallback>* >(m_callbacks[i]);

		if (testCallback != nullptr				&&
			testCallback->m_user == user		&&
			testCallback->m_callback == callback)
		{
			delete m_callbacks[i];
			m_callbacks.erase(m_callbacks.begin() + i);
			break;
		}
	}
}