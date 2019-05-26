#pragma once
#include "Engine/Events/EventSystem.hpp"

#include "Engine/Strings/HashedString.hpp"
#include "Engine/Core/TypedProperties.hpp"



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

	inline virtual bool Call(TypedProperties& args) override;
	inline EventCallback GetCallback() const; 

private:
	EventCallback m_callback;
};


template<typename t, typename dummy> 
class SubscriberListingMemberFunction : public SubscriberListingBase
{
	typedef bool(t::*EventCallback)(TypedProperties& args);

public:
	SubscriberListingMemberFunction(t* user, dummy callback);

	inline virtual bool		Call(TypedProperties& args) override;
	//inline t*				GetUser() const;
	//inline EventCallback	GetCallback() const;


	t*				m_user;
	EventCallback	m_callback;
private:
};



// -----------------------------------------------------------------
// SubscriberListingStaticFunction Implementation
// -----------------------------------------------------------------
bool SubscriberListingStaticFunction::Call(TypedProperties& args)
{
	bool result = m_callback(args);
	return result;
}


EventCallback SubscriberListingStaticFunction::GetCallback() const
{
	return m_callback;
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
// Composition
// -----------------------------------------------------------------
EventSystem::EventSystem()
{

}


inline void ClearEventListings(std::vector<SubscriberListingBase*>& listings)
{
	for (int i = 0; i < (int)listings.size(); ++i)
	{
		delete listings[i];
	}
	listings.clear();
}


EventSystem::~EventSystem()
{
	for (auto iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter)
	{
		ClearEventListings(iter->second);
	}
	m_callbacks.clear();
}



// -----------------------------------------------------------------
// Fire Event
// -----------------------------------------------------------------
void EventSystem::FireEvent(const HashedString& name, TypedProperties& args)
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


void EventSystem::FireEvent(const HashedString& name)
{
	TypedProperties args;
	FireEvent(name, args);
}



// -----------------------------------------------------------------
// C Functions
// -----------------------------------------------------------------
void EventSystem::SubscribeEventCallbackFunction(const HashedString& eventName, EventCallback callback)
{
	SubscriberListingStaticFunction* listing = new SubscriberListingStaticFunction(callback);
	m_callbacks[eventName].push_back((SubscriberListingBase*)listing);
}


void EventSystem::UnsubscribeEventCallbackFunction(const HashedString& eventName, EventCallback callback)
{
	auto searchIter = m_callbacks.find(eventName);
	if (searchIter != m_callbacks.end())
	{
		std::vector<SubscriberListingBase*>& subscribers = searchIter->second;

		for (int i = 0; i < (int)subscribers.size(); ++i)
		{
			SubscriberListingStaticFunction* listing = dynamic_cast<SubscriberListingStaticFunction*>(subscribers[i]);
			if (listing != nullptr)
			{
				EventCallback listingCallback = listing->GetCallback();
				if (listingCallback == callback)
				{
					delete subscribers[i];
					subscribers.erase(subscribers.begin() + i);
					break;
				}
			}
		}
	}
}



// -----------------------------------------------------------------
// Member Functions
// -----------------------------------------------------------------
template<typename t, typename dummy>
void EventSystem::SubscribeEventCallbackMemberFunction(const HashedString& eventName, t* user, dummy memberCallback)
{
	SubscriberListingMemberFunction<t, dummy>* listing = new SubscriberListingMemberFunction<t, dummy>(user, memberCallback);
	m_callbacks[eventName].push_back((SubscriberListingBase*)listing);
}


template<typename t, typename dummy>
void EventSystem::UnsubscribeEventCallbackFunction(const HashedString& eventName, t* user, dummy memberCallback)
{
	auto searchIter = m_callbacks.find(eventName);
	if (searchIter != m_callbacks.end())
	{
		std::vector<SubscriberListingBase*>& subscribers = searchIter->second;

		for (int i = 0; i < (int)subscribers.size(); ++i)
		{
			SubscriberListingMemberFunction<t, dummy>* listing = dynamic_cast<SubscriberListingMemberFunction<t, dummy>*>(subscribers[i]);
			if (listing != nullptr)
			{
				if (listing->m_callback == memberCallback &&
					listing->m_user == user)
				{
					delete subscribers[i];
					subscribers.erase(subscribers.begin() + i);
					break;
				}
			}
		}
	}
}
