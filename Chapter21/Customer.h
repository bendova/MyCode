#pragma once
#include <string>
#include <iostream>
#include "XMLWriter.h"
#include "XMLReader.h"

namespace MyCode
{
	class Customer
	{
	public:
		Customer(std::string name, std::string address, std::string data);
		Customer(Customer&& other);
		Customer(XMLReader& reader);
		~Customer();

		bool operator==(const Customer& other);

		const std::string& GetName() const { return mName; }
		const std::string& GetAddress() const { return mAddress; }
		const std::string& GetData() const { return mData; }
		
		void ToXML(XMLWriter& writer) const;

		static const char* CUSTOMER_TAG;
		static const char* NAME_TAG;
		static const char* ADDRESS_TAG;
		static const char* DATA_TAG;
	private:
		std::string mName;
		std::string mAddress;
		std::string mData;
	};

	std::ostream& operator<<(std::ostream& cout, const Customer& customer);
}

