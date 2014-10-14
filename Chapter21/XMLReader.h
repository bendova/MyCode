#pragma once
#include <string>
#include <utility>

namespace MyCode
{
	class XMLReader
	{
	public:
		XMLReader(const std::string& xml);
		XMLReader(std::string&& xml);
		~XMLReader();

		bool IsEmpty() const;
		
		void ResetToFirstElement();
		XMLReader GetNextElement(const char* tag);
		bool HasNextElement(const char* tag) const;
		std::string GetAsString(const char* tag) const;
		double GetAsDouble(const char* tag) const;
		int GetAsInt(const char* tag) const;
		unsigned GetAsUnsigned(const char* tag) const;

		std::pair<std::string, std::string> GetXMLTagsFor(const char* tag) const;
	private:
		std::pair<std::size_t, std::size_t> GetElementBounds(const char* tag) const;

		std::string mXML;
		std::size_t mCurrentElementPosition;
	};
}

