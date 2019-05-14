#pragma once
#include "Engine/Events/EventSystem.hpp"



// -----------------------------------------------------------------
// Internal Classes
// -----------------------------------------------------------------
class SubscriberListingBase
{
public:
	SubscriberListingBase() {};
	~SubscriberListingBase() {};

	virtual bool Call(TypedProperties& args) = 0;
};


class SubscriberListingStaticFunction : public SubscriberListingBase
{
public:
	SubscriberListingStaticFunction(EventCallback callback) : m_callback(callback) {};

	virtual bool Call(TypedProperties& args) override;


private:
	EventCallback m_callback;
};


template<typename t, typename dummy> 
class SubscriberListingMemberFunction : public SubscriberListingBase
{
	typedef bool(t::*EventCallback)(TypedProperties& args);

public:
	SubscriberListingMemberFunction(t* user, dummy callback);

	virtual bool Call(TypedProperties& args) override;



private:
	t*				m_user;
	EventCallback	m_callback;
};



// -----------------------------------------------------------------
// SubscriberListingStaticFunction Implementation
// -----------------------------------------------------------------
bool SubscriberListingStaticFunction::Call(TypedProperties& args)
{
	bool result = m_callback(args);
	return result;
}



// -----------------------------------------------------------------
// SubscriberListingMemberFunction Implementation
// -----------------------------------------------------------------
template<typename t, typename dummy>
SubscriberListingMemberFunction<typename t, typename dummy>::SubscriberListingMemberFunction(t* user, dummy callback)
{
	// GOD user != nullptr;

	m_user = user;
	m_callback = (EventCallback)callback;
}


template <typename t, typename dummy>
bool SubscriberListingMemberFunction<typename t, typename dummy>::Call(TypedProperties& args)
{
	bool result = (m_user->*m_callback)(args);
	return result;
}



// -----------------------------------------------------------------
// EventSystem Implementation
// -----------------------------------------------------------------
void EventSystem::FireEvent(const std::string& name, TypedProperties& args)
{
	auto searchIter = m_callbacks.find(name);
	if (searchIter != m_callbacks.end())
	{
		bool shouldContinue = true;
		std::vector<SubscriberListingBase*>& listings = searchIter->second;
		for (int i = 0; i < (int)listings.size() && shouldContinue; ++i)
		{
			shouldContinue = !listings[i]->Call(args);
		}
	}
}


void EventSystem::SubscribeEventCallbackFunction(const std::string& eventName, EventCallback callback)
{
	SubscriberListingStaticFunction* listing = new SubscriberListingStaticFunction(callback);
	m_callbacks[eventName].push_back((SubscriberListingBase*)listing);
}


template<typename t, typename dummy>
void EventSystem::SubscribeEventCallbackMemberFunction(const std::string& eventName, t* user, dummy memberCallback)
{
	SubscriberListingMemberFunction<t, dummy>* listing = new SubscriberListingMemberFunction<t, dummy>(user, memberCallback);
	m_callbacks[eventName].push_back((SubscriberListingBase*)listing);
}