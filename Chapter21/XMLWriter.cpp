#include "stdafx.h"
#include "XMLWriter.h"

namespace MyCode
{
	XMLWriter::XMLWriter()
		: mBuffer{}
		, mIndentation{}
	{}


	XMLWriter::~XMLWriter()
	{}

	void XMLWriter::BeginElement(const char* tag, bool addNewLine, bool increaseIndent)
	{
		mBuffer.append(mIndentation).append("<").append(tag).append(">");
		if (addNewLine)
		{
			mBuffer.append("\n");
		}
		if (increaseIndent)
		{
			mIndentation.append("\t");
		}
	}

	void XMLWriter::WriteValue(const std::string& value)
	{
		mBuffer.append(value);
	}

	void XMLWriter::WriteValue(const char* value)
	{
		mBuffer.append(value);
	}

	void XMLWriter::EndElement(const char* tag, bool addNewLine, bool decreaseIndent)
	{
		if (decreaseIndent)
		{
			mIndentation.pop_back();
			mBuffer.append(mIndentation).append("</").append(tag).append(">");
		}
		else
		{
			mBuffer.append("</").append(tag).append(">");
		}
		if (addNewLine)
		{
			mBuffer.append("\n");
		}
	}

	std::string XMLWriter::FlushAsString()
	{
		return std::forward<std::string>(mBuffer);
	}
}
