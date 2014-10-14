#pragma once

#include <iostream>
#include <vector>
#include "Purchase.h"
#include "Customer.h"
#include "XMLWriter.h"
#include "XMLReader.h"

namespace MyCode
{
	class Order
	{
	public:
		explicit Order(const Customer& customer);
		explicit Order(XMLReader& reader);
		Order(Customer&& customer);
		~Order();

		bool operator==(const Order& other);

		void AddPurchase(Purchase& purchase);
		void AddPurchases(std::vector<Purchase>& purchases);
		double GetTotalCost() const;
		const Customer& GetCustomer() const;
		const std::vector<Purchase>& GetPurchases() const;

		void SortPurchases();

		void ToXML(XMLWriter& writer) const;

		static const char* ORDER_TAG;
		static const char* PURCHASES_TAG;
		static const char* CUSTOMER_TAG;
	private:
		Customer mCustomer;
		std::vector<Purchase> mPurchases;
	};

	std::ostream& operator<<(std::ostream& cout, const Order& order);
}