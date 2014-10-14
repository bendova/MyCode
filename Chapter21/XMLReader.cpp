#include "stdafx.h"
#include "XMLReader.h"
#include <sstream>
#include <stdexcept>
#include <utility>

namespace MyCode
{
	XMLReader::XMLReader(const std::string& xml)
		: mXML(xml)
		, mCurrentElementPosition(0)
	{}

	XMLReader::XMLReader(std::string&& xml)
		: mXML(std::forward<std::string>(xml))
		, mCurrentElementPosition(0)
	{}

	XMLReader::~XMLReader()
	{}

	bool XMLReader::IsEmpty() const
	{
		return mXML.empty();
	}

	void XMLReader::ResetToFirstElement()
	{
		mCurrentElementPosition = 0;
	}

	XMLReader XMLReader::GetNextElement(const char* tag)
	{
		std::pair<std::size_t, std::size_t> bounds = GetElementBounds(tag);
		std::pair<std::string, std::string> xmlTags = GetXMLTagsFor(tag);
		std::size_t offset = bounds.first + xmlTags.first.length();
		std::size_t count = bounds.second - offset;
		std::string nextElementXML = mXML.substr(offset, count);
		
		mCurrentElementPosition = bounds.second + xmlTags.second.length();
		return XMLReader{ std::forward<std::string>(nextElementXML) };
	}
	
	bool XMLReader::HasNextElement(const char* tag) const
	{
		try
		{
			std::pair<std::size_t, std::size_t> bounds = GetElementBounds(tag);
			return (bounds.first != std::string::npos);
		}
		catch (std::invalid_argument e)
		{
			return false;
		}
	}

	std::string XMLReader::GetAsString(const char* tag) const
	{
		std::pair<std::size_t, std::size_t> bounds = GetElementBounds(tag);
		std::pair<std::string, std::string> xmlTags = GetXMLTagsFor(tag);
		std::size_t offset = bounds.first + xmlTags.first.length();
		std::size_t count = bounds.second - offset;
		return mXML.substr(offset, count);
	}

	std::pair<std::size_t, std::size_t> XMLReader::GetElementBounds(const char* tag) const
	{
		bool isContentValid = false;
		std::pair<std::size_t, std::size_t> bounds;
		std::pair<std::string, std::string> xmlTags = GetXMLTagsFor(tag);
		std::size_t startAt = mXML.find(xmlTags.first, mCurrentElementPosition);
		if (startAt != std::string::npos)
		{
			std::size_t endAt = mXML.find(xmlTags.second, startAt);
			if (endAt != std::string::npos)
			{
				std::size_t offset = startAt + xmlTags.first.length();
				std::size_t count = endAt - offset;
				bounds = std::make_pair(startAt, endAt);

				isContentValid = true;
			}
		}
		if (isContentValid == false)
		{
			std::string error{ "Invalid XML syntax: " };
			error.append(mXML);
			throw std::invalid_argument{ error };
		}
		return bounds;
	}

	double XMLReader::GetAsDouble(const char* tag) const
	{
		return std::stod(GetAsString(tag));
	}
	int XMLReader::GetAsInt(const char* tag) const
	{
		return std::stoi(GetAsString(tag));
	}
	unsigned XMLReader::GetAsUnsigned(const char* tag) const
	{
		return static_cast<unsigned>(std::stoi(GetAsString(tag)));
	}

	std::pair<std::string, std::string> XMLReader::GetXMLTagsFor(const char* tag) const
	{
		std::ostringstream ostream;
		ostream << "<" << tag << ">";
		std::string startTag = ostream.str();
		ostream.str("");
		ostream << "</" << tag << ">";
		std::string endTag = ostream.str();
		return std::make_pair(startTag, endTag);
	}
}
