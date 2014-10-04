#include "stdafx.h"
#include "Customer.h"
#include <utility>

namespace MyCode
{
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

	Customer::~Customer()
	{}

	std::ostream& Customer::ToXML(std::ostream& cout) const
	{
		cout << "<customer>" << std::endl;
		{
			cout << "<name>" << mName << "</name>" << std::endl;
			cout << "<address>" << mAddress << "</address>" << std::endl;
			cout << "<data>" << mData << "</data>" << std::endl;
		}
		cout << "</customer>" << std::endl;

		return cout;
	}

	std::ostream& operator<<(std::ostream& cout, const Customer& customer)
	{
		cout << "Customer: " << customer.GetName() << ", Address: " << customer.GetAddress() << std::endl;
		return cout;
	}
}
