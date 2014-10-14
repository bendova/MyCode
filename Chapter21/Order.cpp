#include "stdafx.h"
#include <numeric>
#include <algorithm>
#include <utility>
#include <sstream>
#include "Order.h"
#include "Algorithm.h"

namespace MyCode
{
	const char* Order::ORDER_TAG = "order";
	const char* Order::PURCHASES_TAG = "purchases";
	const char* Order::CUSTOMER_TAG = "customer";

	Order::Order(const Customer& customer)
		: mCustomer(customer)
		, mPurchases()
	{}

	Order::Order(Customer&& customer)
		: mCustomer(std::forward<Customer>(customer))
		, mPurchases()
	{}
	
	Order::Order(XMLReader& reader)
		: mCustomer{reader}
	{
		// TODO and now start reading the purchases from XML

		XMLReader purchasesXML = reader.GetNextElement(PURCHASES_TAG);
		while (purchasesXML.HasNextElement(Purchase::PURCHASE_TAG))
		{
			Purchase purchase{ purchasesXML };
			mPurchases.push_back(purchase);
		}
	}

	Order::~Order()
	{}

	bool Order::operator==(const Order& other)
	{
		bool isSameOrder = false;
		if (mCustomer == other.mCustomer)
		{
			auto begin = mPurchases.begin();
			auto end = mPurchases.end();

			auto otherBegin = other.mPurchases.begin();
			auto otherEnd = other.mPurchases.end();
			for (; (begin != end) && (otherBegin != otherEnd); ++begin, ++otherBegin)
			{
				if ((*begin == *otherBegin) == false)
				{
					break;
				}
			}
			isSameOrder = ((begin == end) && (otherBegin == otherEnd));
		}
		return isSameOrder;
	}

	void Order::AddPurchase(Purchase& purchase)
	{
		mPurchases.push_back(purchase);
	}

	void Order::AddPurchases(std::vector<Purchase>& purchases)
	{
		mPurchases.insert(mPurchases.end(), purchases.begin(), purchases.end());
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

	void Order::SortPurchases()
	{
		Sort(mPurchases.begin(), mPurchases.end());
	}

	void Order::ToXML(XMLWriter& writer) const
	{
		writer.BeginElement(ORDER_TAG);
		{
			mCustomer.ToXML(writer);
			writer.BeginElement(PURCHASES_TAG);
			{
				for (const Purchase& purchase : mPurchases)
				{
					purchase.ToXML(writer);
				}
			}
			writer.EndElement(PURCHASES_TAG);
		}
		writer.EndElement(ORDER_TAG);
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