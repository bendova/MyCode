#include "stdafx.h"
#include "Order.h"
#include <numeric>
#include <algorithm>
#include <utility>

namespace MyCode
{
	Order::Order(const Customer& customer)
		: mCustomer(customer)
		, mPurchases()
	{}

	Order::Order(Customer&& customer)
		: mCustomer(std::forward<Customer>(customer))
		, mPurchases()
	{}
	
	Order::~Order()
	{}

	void Order::AddPurchase(Purchase& purchase)
	{
		mPurchases.push_back(purchase);
	}

	double Order::GetTotalCost() const
	{
		return std::accumulate(mPurchases.begin(), mPurchases.end(), 0.0, 
			[](double initialValue, const Purchase& purchase) { return initialValue + purchase.GetCount() * purchase.GetUnitPrice(); });
	}

	const Customer& Order::GetCustomer() const
	{
		return mCustomer;
	}

	const std::vector<Purchase>& Order::GetPurchases() const
	{
		return mPurchases;
	}

	std::ostream& Order::ToXML(std::ostream& cout)
	{
		cout << "<order>" << std::endl;
		{
			mCustomer.ToXML(cout);

			cout << "<purchases>" << std::endl;
			for (const Purchase& purchase : mPurchases)
			{
				purchase.ToXML(cout);
			}
			cout << "</purchases>" << std::endl;
		}
		cout << "</order>" << std::endl;

		return cout;
	}

	std::ostream& operator<<(std::ostream& cout, const Order& order)
	{
		cout << order.GetCustomer();
		cout << "The order contains: " << std::endl;
		std::for_each(order.GetPurchases().begin(), order.GetPurchases().end(), [&cout](const Purchase& purchase)
		{
			cout << purchase;
		});
		cout << "Total cost: " << order.GetTotalCost();
		return cout;
	}
}