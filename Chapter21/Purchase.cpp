#include "stdafx.h"
#include "Purchase.h"
#include <utility>

namespace MyCode
{
	Purchase::Purchase(std::string produceName, double unitPrice, unsigned count)
		: mProductName(produceName)
		, mUnitPrice(unitPrice)
		, mCount(count)
	{}

	Purchase::Purchase(Purchase&& other)
		: mProductName(std::forward<std::string>(other.mProductName))
		, mUnitPrice(other.mUnitPrice)
		, mCount(other.mCount)
	{}

	Purchase::~Purchase()
	{}

	std::ostream& Purchase::ToXML(std::ostream& cout) const
	{
		cout << "<purchase>" << std::endl;
		{
			cout << "<product>" << mProductName << "</product>" << std::endl;
			cout << "<unitprice>" << mUnitPrice << "</unitprice>" << std::endl;
			cout << "<count>" << mCount << "</count>" << std::endl;
		}
		cout << "</purchase>" << std::endl;

		return cout;
	}

	std::ostream& operator<<(std::ostream& cout, const Purchase& purchase)
	{
		cout << "Product: " << purchase.GetProductName() << ", ";
		cout << "Unit price: " << purchase.GetUnitPrice() << ", ";
		cout << "Count: " << purchase.GetCount() << std::endl;

		return cout;
	}
}
