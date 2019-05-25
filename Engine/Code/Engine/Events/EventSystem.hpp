#pragma once

#include <string>
#include <vector>
#include <map>

class HashedString;
class TypedProperties;
class SubscriberListingBase;

typedef bool(*EventCallback)(TypedProperties& args);




class EventSystem
{
public:
	// Composition
	EventSystem();
	~EventSystem();


	// Fire Event
	inline void FireEvent(const HashedString& name, TypedProperties& args);
	inline void FireEvent(const HashedString& name);


	// C Functions
	inline void SubscribeEventCallbackFunction(const HashedString& eventName, EventCallback callback);
	inline void UnsubscribeEventCallbackFunction(const HashedString& eventName, EventCallback callback);


	// Member Functions
	template<typename t, typename dummy>
	inline void SubscribeEventCallbackMemberFunction(const HashedString& eventName, t* user, dummy memberCallback);

	template<typename t, typename dummy>
	inline void UnsubscribeEventCallbackFunction(const HashedString& eventName, t* user, dummy memberCallback);



private:
	std::map<HashedString, std::vector<SubscriberListingBase*> > m_callbacks;
};




#include "Engine/Events/EventSystemInlineImplementation.hpp"
