#pragma once

#include <string>

namespace MyCode
{
	class FileHandle
	{
	public:
		FileHandle(std::string filePath);
		~FileHandle();

	private:
		std::string mFilePath;
	};
}

