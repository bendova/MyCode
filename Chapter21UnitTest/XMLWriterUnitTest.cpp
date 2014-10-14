#include "stdafx.h"
#include "CppUnitTest.h"
#include "XMLWriter.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MyCode;

namespace Chapter21UnitTest
{
	TEST_CLASS(XMLWriterUnitTest)
	{
	public:
		
		TEST_METHOD(TestEmptyWriter)
		{
			XMLWriter writer;
			std::string empty = writer.FlushAsString();
			Assert::IsTrue(empty.empty());
		}

		template<typename T>
		std::string GetXML(const char* tag, T value)
		{
			std::ostringstream out;
			out << "<" << tag << ">" << value << "</" << tag << ">" << "\n";
			return out.str();
		}

		std::string GetXML(const char* tag, double value)
		{
			std::ostringstream out;
			out << "<" << tag << ">" << std::to_string(value) << "</" << tag << ">" << "\n";
			return out.str();
		}

		std::string GetXML(const char* tag, float value)
		{
			std::ostringstream out;
			out << "<" << tag << ">" << std::to_string(value) << "</" << tag << ">" << "\n";
			return out.str();
		}

		TEST_METHOD(TestWritingEmptyElement)
		{
			const char* value = "";
			const char* tag = "product";

			XMLWriter writer;
			writer.WriteElement(tag, value);

			std::string xml = writer.FlushAsString();
			Assert::AreEqual(0, xml.compare(GetXML(tag, value)));
		}

		TEST_METHOD(TestWritingElementWithIntValue)
		{
			const char* tag = "product";
			const int value = 1;

			XMLWriter writer;
			writer.WriteElement(tag, value);

			std::string xml = writer.FlushAsString();
			Assert::AreEqual(0, xml.compare(GetXML(tag, value)));
		}

		TEST_METHOD(TestWritingElementWithUnsignedValue)
		{
			const char* tag = "product";
			const unsigned value = 1;

			XMLWriter writer;
			writer.WriteElement(tag, value);

			std::string xml = writer.FlushAsString();
			Assert::AreEqual(0, xml.compare(GetXML(tag, value)));
		}

		TEST_METHOD(TestWritingElementWithDoubleValue)
		{
			const char* tag = "product";
			const double value = 1.2;

			XMLWriter writer;
			writer.WriteElement(tag, value);

			std::string xml = writer.FlushAsString();
			Assert::AreEqual(0, xml.compare(GetXML(tag, value)));
		}

		TEST_METHOD(TestWritingElementWithStringValue)
		{
			const char* tag = "product";
			const std::string value = "iron";

			XMLWriter writer;
			writer.WriteElement(tag, value);

			std::string xml = writer.FlushAsString();
			Assert::AreEqual(0, xml.compare(GetXML(tag, value)));
		}
	};
}