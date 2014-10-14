#include "stdafx.h"
#include "Customer.h"
#include <utility>
#include <sstream>

namespace MyCode
{
	const char* Customer::CUSTOMER_TAG = "customer";
	const char* Customer::NAME_TAG  = "name";
	const char* Customer::ADDRESS_TAG = "address";
	const char* Customer::DATA_TAG = "data";

	Customer::Customer(std::string name, std::string address, std::string data)
		: mName(name)
		, mAddress(address)
		, mData(data)
	{}

	Customer::Customer(Customer&& other)
		: mName(std::forward<std::string>(other.mName))
		, mAddress(std::forward<std::string>(other.mAddress))
		, mData(std::forward<std::string>(other.mData))
	{}

	Customer::Customer(XMLReader& reader)
	{
		XMLReader customerReader = reader.GetNextElement(CUSTOMER_TAG);
		mName = customerReader.GetAsString(NAME_TAG);
		mAddress = customerReader.GetAsString(ADDRESS_TAG);
		mData = customerReader.GetAsString(DATA_TAG);
	}

	Customer::~Customer()
	{}

	bool Customer::operator==(const Customer& other)
	{
		return ((mName == other.mName) && (mAddress == other.mAddress)
			&& (mData == other.mData));
	}

	void Customer::ToXML(XMLWriter& writer) const
	{
		writer.BeginElement(CUSTOMER_TAG);
		{
			writer.WriteElement(NAME_TAG, mName);
			writer.WriteElement(ADDRESS_TAG, mAddress);
			writer.WriteElement(DATA_TAG, mData);
		}
		writer.EndElement(CUSTOMER_TAG);
	}

	std::ostream& operator<<(std::ostream& cout, const Customer& customer)
	{
		cout << "Customer: " << customer.GetName() << ", Address: " << customer.GetAddress() << std::endl;
		return cout;
	}
}
