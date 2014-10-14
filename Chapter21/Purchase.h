#pragma once

#include <string>
#include <iostream>
#include <utility>
#include "XMLReader.h"
#include "XMLWriter.h"

namespace MyCode
{
	class Purchase
	{
	public:
		Purchase(std::string produceName, double unitPrice, unsigned count);
		Purchase(Purchase&& other);
		Purchase(XMLReader& reader);
		~Purchase();

		bool operator==(const Purchase& other);
		bool operator<(const Purchase& other);

		std::string GetProductName() const { return mProductName;  }
		double GetUnitPrice() const { return mUnitPrice; }
		unsigned GetCount() const { return mCount; }

		void ToXML(XMLWriter& writer) const;

		static const char* PURCHASE_TAG;
		static const char* PRODUCT_NAME_TAG;
		static const char* UNIT_PRICE_TAG;
		static const char* UNIT_COUNT_TAG;
	private:
		std::string mProductName;
		double mUnitPrice;
		int mCount;
	};

	std::ostream& operator<<(std::ostream& cout, const Purchase& purchase);
}

