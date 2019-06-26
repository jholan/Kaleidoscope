#include "Game/Resource/ResourceUtils.hpp"

#include "Engine/Core/Blackboard.hpp"

#include "Game/App/AppCommon.hpp"



eResourceLoadState SetResourceLoadState(eResourceLoadState currVal, eResourceLoadState newVal)
{
	eResourceLoadState finalVal = currVal;


	if (currVal == RESOURCE_LOAD_STATE_LOADED && newVal == RESOURCE_LOAD_STATE_UNLOADED)
	{
		// It is ok to unload a resource
		finalVal = newVal;
	}
	else if (newVal > currVal)
	{
		// It is ok to progress the resource state upward
		finalVal = newVal;
	}


	return finalVal;
}


std::string GetFullResourcePath(const std::string relativePath)
{
	std::string fullPath = g_theBlackboard->GetValue("Resources.BasePath", "") + relativePath;
	return fullPath;
}