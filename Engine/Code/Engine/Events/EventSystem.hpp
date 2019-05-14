#pragma once

#include <string>
#include <vector>
#include <map>

class TypedProperties;
class SubscriberListingBase;

typedef bool(*EventCallback)(TypedProperties& args);




class EventSystem
{
public:
	void FireEvent(const std::string& name, TypedProperties& args);
	void SubscribeEventCallbackFunction(const std::string& eventName, EventCallback callback);
	
	template<typename t, typename dummy>
	void SubscribeEventCallbackMemberFunction(const std::string& eventName, t* user, dummy memberCallback);



private:
	std::map<std::string, std::vector<SubscriberListingBase*> > m_callbacks;
};




#include "Engine/Events/EventSystemInlineImplementation.hpp"
