#include "Engine/FileSystem/FileUtils.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <sys/stat.h>



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


bool DoesFileExist(const std::string filepath)
{
	bool exists = true;

	struct _stat buff;
	int result = _stat(filepath.c_str(), &buff);

	if (result != 0)
	{
		int errorCode = errno;
		switch(errorCode)
		{
		case ENOENT:
		{
			break;
		}

		case EINVAL:
		{
			break;
		}

		default:
			break;
		}

		exists = false;
	}

	return exists;
}