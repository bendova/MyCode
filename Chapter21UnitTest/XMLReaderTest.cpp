#include "stdafx.h"
#include "CppUnitTest.h"
#include <XMLReader.h>
#include <string>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MyCode;

namespace Chapter21UnitTest
{
	TEST_CLASS(XMLReaderTest)
	{
	public:
		TEST_METHOD(TestNonEmptyReader)
		{
			const char* xml = "<product>purchase0</product>";
			XMLReader reader{ xml };
			Assert::IsFalse(reader.IsEmpty());
		}

		TEST_METHOD(TestEmptyReader)
		{
			const char* xml = "";
			XMLReader reader{ xml };
			Assert::IsTrue(reader.IsEmpty());
		}

		TEST_METHOD(TestGetAsStringWithValue)
		{
			const char* tag = "product";
			const char* expectedValue = "purchase0";
			const char* xml = "<product>purchase0</product>";

			XMLReader reader{ xml };
			std::string value = reader.GetAsString(tag);

			Assert::IsTrue(value.compare(expectedValue) == 0);
		}
		TEST_METHOD(TestGetAsStringWithNoValue)
		{
			const char* tag = "product";
			const char* expectedValue = "";
			const char* xml = "<product></product>";

			XMLReader reader{ xml };
			Assert::IsTrue(reader.GetAsString(tag).compare(expectedValue) == 0);
		}

		TEST_METHOD(TestGetAsStringWithInvalidXML)
		{
			const char* tag = "product";
			const char* expectedValue = "";
			const char* xml = "<product>purchase0<product>";

			XMLReader reader{ xml };
			std::function<std::string(void)> call = [&reader, tag]() { return reader.GetAsString(tag); };
			Assert::ExpectException<std::invalid_argument>(call, L"Expected invalid_argument exception for malformed XML.");
		}

		TEST_METHOD(TestGetAsInt)
		{
			const char* tag = "price";
			const int expectedValue = 2;
			const char* xml = "<price>2</price>";

			XMLReader reader{ xml };
			Assert::IsTrue(reader.GetAsInt(tag) == expectedValue);
		}

		TEST_METHOD(TestGetAsDouble)
		{
			const char* tag = "price";
			const double expectedValue = 2.0;
			const char* xml = "<price>2.0</price>";

			XMLReader reader{ xml };
			Assert::IsTrue(reader.GetAsDouble(tag) == expectedValue);
		}

		TEST_METHOD(TestGetAsUnsigned)
		{
			const char* tag = "price";
			const unsigned expectedValue = 20u;
			const char* xml = "<price>20</price>";

			XMLReader reader{ xml };
			Assert::IsTrue(reader.GetAsUnsigned(tag) == expectedValue);
		}

		TEST_METHOD(TestGetNextElement)
		{
			const char* productTag = "product";
			const char* priceTag = "price";
			const double expectedValue1 = 2.0;
			const double expectedValue2 = 3.0;
			const char* xml = "<products>"
									"<product><price>2.0</price></product>"
									"<product><price>3.0</price></product>"
							"</products>";
		
			XMLReader reader{ xml };
			Assert::AreEqual(expectedValue1, reader.GetNextElement(productTag).GetAsDouble(priceTag));
			Assert::AreEqual(expectedValue2, reader.GetNextElement(productTag).GetAsDouble(priceTag));
		}

		TEST_METHOD(TestReadingArraysOfElements)
		{
			const char* productTag = "product";
			const char* priceTag = "price";
			const char* xml = "<products>"
								"<product><price>0.0</price></product>"
								"<product><price>1.0</price></product>"
								"<product><price>2.0</price></product>"
								"<product><price>3.0</price></product>"
								"<product><price>4.0</price></product>"
							"</products>";
			XMLReader reader{ xml };

			for (int i = 0; i < 5; ++i)
			{
				Assert::IsTrue(reader.HasNextElement(productTag));
				Assert::AreEqual(static_cast<double>(i), reader.GetNextElement(productTag).GetAsDouble(priceTag));
			}

			reader.ResetToFirstElement();

			for (int i = 0; i < 5; ++i)
			{
				Assert::IsTrue(reader.HasNextElement(productTag));
				Assert::AreEqual(static_cast<double>(i), reader.GetNextElement(productTag).GetAsDouble(priceTag));
			}
		}
	};
}