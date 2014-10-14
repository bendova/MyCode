#include "stdafx.h"
#include "Purchase.h"
#include <sstream>

namespace MyCode
{
	const char* Purchase::PURCHASE_TAG = "purchase";
	const char* Purchase::PRODUCT_NAME_TAG = "product";
	const char* Purchase::UNIT_PRICE_TAG = "unitprice";
	const char* Purchase::UNIT_COUNT_TAG = "count";

	Purchase::Purchase(std::string productName, double unitPrice, unsigned count)
		: mProductName(productName)
		, mUnitPrice(unitPrice)
		, mCount(count)
	{}

	Purchase::Purchase(Purchase&& other)
		: mProductName(std::forward<std::string>(other.mProductName))
		, mUnitPrice(other.mUnitPrice)
		, mCount(other.mCount)
	{}

	Purchase::Purchase(XMLReader& reader)
	{
		XMLReader purchaseReader = reader.GetNextElement(Purchase::PURCHASE_TAG);
		mProductName = purchaseReader.GetAsString(Purchase::PRODUCT_NAME_TAG);
		mUnitPrice = purchaseReader.GetAsDouble(Purchase::UNIT_PRICE_TAG);
		mCount = purchaseReader.GetAsUnsigned(Purchase::UNIT_COUNT_TAG);
	}

	Purchase::~Purchase()
	{}

	bool Purchase::operator==(const Purchase& other)
	{
		return (mProductName == other.mProductName) && (mUnitPrice == other.mUnitPrice)
			&& (mCount == other.mCount);
	}

	bool Purchase::operator<(const Purchase& other)
	{
		return (mCount * mUnitPrice) < (other.mCount * other.mUnitPrice);
	}

	void Purchase::ToXML(XMLWriter& writer) const
	{
		writer.BeginElement(PURCHASE_TAG);
		{
			writer.WriteElement(PRODUCT_NAME_TAG, mProductName);
			writer.WriteElement(UNIT_PRICE_TAG, mUnitPrice);
			writer.WriteElement(UNIT_COUNT_TAG, mCount);
		}
		writer.EndElement(PURCHASE_TAG);
	}

	std::ostream& operator<<(std::ostream& cout, const Purchase& purchase)
	{
		cout << "Product: " << purchase.GetProductName() << ", ";
		cout << "Unit price: " << purchase.GetUnitPrice() << ", ";
		cout << "Count: " << purchase.GetCount() << std::endl;

		return cout;
	}
}
