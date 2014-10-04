#pragma once

#include <vector>
#include "Purchase.h"
#include "Customer.h"
#include <iostream>

namespace MyCode
{
	class Order
	{
	public:
		Order(const Customer& customer);
		Order(Customer&& customer);
		~Order();

		void AddPurchase(Purchase& purchase);
		double GetTotalCost() const;
		const Customer& GetCustomer() const;
		const std::vector<Purchase>& GetPurchases() const;

		std::ostream& ToXML(std::ostream& cout);
	private:
		Customer mCustomer;
		std::vector<Purchase> mPurchases;
	};

	std::ostream& operator<<(std::ostream& cout, const Order& order);
}