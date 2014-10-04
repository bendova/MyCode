#pragma once
#include <string>
#include <iostream>

namespace MyCode
{
	class Customer
	{
	public:
		Customer(std::string name, std::string address, std::string data);
		Customer(Customer&& other);
		~Customer();
		const std::string& GetName() const { return mName; }
		const std::string& GetAddress() const { return mAddress; }
		const std::string& GetData() const { return mData; }
		
		std::ostream& ToXML(std::ostream& cout) const;
	private:
		std::string mName;
		std::string mAddress;
		std::string mData;
	};

	std::ostream& operator<<(std::ostream& cout, const Customer& customer);
}

