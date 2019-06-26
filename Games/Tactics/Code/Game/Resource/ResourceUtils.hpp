#pragma once

#include <string>



enum eResourceLoadState
{
	RESOURCE_LOAD_STATE_UNLOADED,
	RESOURCE_LOAD_STATE_REQUESTING_LOAD,
	RESOURCE_LOAD_STATE_LOADING,
	RESOURCE_LOAD_STATE_LOADED,
};

eResourceLoadState SetResourceLoadState(eResourceLoadState currVal, eResourceLoadState newVal);

std::string GetFullResourcePath(const std::string relativePath);