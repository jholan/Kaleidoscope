#include "Engine/FileSystem/FileUtils.hpp"



std::string	GetFileExtension(const std::string& filepath)
{
	std::string extension = "";

	size_t extensionStart = filepath.find_last_of('.');
	if(extensionStart != std::string::npos)
	{
		extension = filepath.substr(extensionStart);
	}

	return extension;
}