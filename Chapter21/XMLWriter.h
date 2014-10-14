#pragma once
#include <string>

namespace MyCode
{
	class XMLWriter
	{
	public:
		XMLWriter();
		~XMLWriter();

		void BeginElement(const char* tag, bool addNewLine = true, bool increaseIndent = true);
		void WriteValue(const std::string& value);
		void WriteValue(const char* value);
		template<typename T>
		void WriteValue(const T& value)
		{
			mBuffer.append(std::to_string(value));
		}
		void EndElement(const char* tag, bool addNewLine = true, bool decreaseIndent = true);

		template<typename T>
		void WriteElement(const char* tag, T value)
		{
			BeginElement(tag, false, false);
			WriteValue(value);
			EndElement(tag, true, false);
		}

		std::string FlushAsString();
	private:
		std::string mBuffer;
		std::string mIndentation;
	};
}
