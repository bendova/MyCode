#pragma once

#include <string>
#include <iostream>

namespace MyCode
{
	class Purchase
	{
	public:
		Purchase(std::string produceName, double unitPrice, unsigned count);
		Purchase(Purchase&& other);
		~Purchase();

		std::string GetProductName() const { return mProductName;  }
		double GetUnitPrice() const { return mUnitPrice; }
		unsigned GetCount() const { return mCount; }

		std::ostream& ToXML(std::ostream& cout) const;
	private:
		std::string mProductName;
		double mUnitPrice;
		int mCount;
	};

	std::ostream& operator<<(std::ostream& cout, const Purchase& purchase);
}

