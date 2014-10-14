#include "stdafx.h"
#include "CppUnitTest.h"
#include "Customer.h"
#include "Purchase.h"
#include "Order.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MyCode;

namespace UnitTest
{
	TEST_CLASS(OrdersTest)
	{
	public:
		TEST_METHOD(TestCustomerConstructor)
		{
			Customer myCustomer("Ion", "Humulesti", "Copilarie");
		}

		TEST_METHOD(TestPurchase)
		{
			std::string productName = "cartofi";
			double cost = 1.0;
			unsigned unitsCount = 5;
			Purchase myPurchase(productName, cost, unitsCount);

			Assert::IsTrue((myPurchase.GetProductName() == productName));
			Assert::IsTrue((myPurchase.GetUnitPrice() == cost));
			Assert::IsTrue((myPurchase.GetCount() == unitsCount));
		}

		TEST_METHOD(TestOrderConstructor)
		{
			Customer myCustomer("Ion", "Humulesti", "Copilarie");
			Order myOrder(myCustomer);

			std::string productName = "cartofi";
			double cost = 1.0;
			unsigned unitsCount = 5;
			Purchase myPurchase(productName, cost, unitsCount);
		}

		TEST_METHOD(TestAddingPurchases)
		{
			Customer myCustomer("Ion", "Humulesti", "Copilarie");
			Order myOrder(myCustomer);

			Purchase cartofiPurchase("cartofi", 1.0, 5);
			myOrder.AddPurchase(cartofiPurchase);

			Purchase painePurchase("paine", 2.5, 4);
			myOrder.AddPurchase(painePurchase);

			double totalCost = (cartofiPurchase.GetCount() * cartofiPurchase.GetUnitPrice()) + 
								(painePurchase.GetCount() * painePurchase.GetUnitPrice());
			Assert::AreEqual(totalCost, myOrder.GetTotalCost());
		}

		Customer OrdersTest::getTestCustomer()
		{
			return Customer("Ion", "Humulesti", "Copilarie");
		}

		std::vector<Purchase> OrdersTest::GetTestPurchases(const unsigned purchasesCount)
		{
			std::vector<Purchase> purchases;
			std::ostringstream osstream;
			for (unsigned i = 0; i < purchasesCount; ++i)
			{
				osstream.str("");
				osstream << "purchase" << i;
				purchases.push_back(Purchase(osstream.str(), i, 5 * i));
			}
			return purchases;
		}

		std::unique_ptr<Order> OrdersTest::GetTestOrder()
		{
			std::unique_ptr<Order> order{ new Order(getTestCustomer()) };
			order->AddPurchases(GetTestPurchases(8));
			return order;
		}

		std::string OrdersTest::GetOrderAsString()
		{
			std::unique_ptr<Order> myOrder = GetTestOrder();

			std::ostringstream outputBuffer;
			outputBuffer << *myOrder << std::endl;

			return outputBuffer.str();
		}

		TEST_METHOD(TestWritingOrderToFile)
		{
			std::ofstream outputFile;
			outputFile.open("Orders.txt", std::ofstream::out);
			if (outputFile.good())
			{
				outputFile << GetOrderAsString();
			}
			outputFile.close();
		}

		void OrdersTest::WriteToFile(const std::string& filePath, const std::string& content)
		{
			std::ofstream outputFile;
			outputFile.open(filePath.c_str(), std::ofstream::out);
			if (outputFile.good())
			{
				outputFile << content;
			}
			outputFile.close();
		}

		std::string OrdersTest::ReadFromFile(const std::string& filePath)
		{
			std::ifstream inputFile;
			inputFile.open(filePath.c_str(), std::ifstream::in);

			std::string readContent{ std::istreambuf_iterator < char > {inputFile},
				std::istreambuf_iterator < char > {} };

			return readContent;
		}

		TEST_METHOD(TestWritingOrderToXML)
		{
			std::string fileName{ "Order.xml" };
			XMLWriter writer;
			GetTestOrder()->ToXML(writer);
			std::string contentToWrite = writer.FlushAsString();
			WriteToFile(fileName, contentToWrite);

			std::string readContent = ReadFromFile(fileName);

			Assert::AreEqual(0, contentToWrite.compare(readContent));
		}

		TEST_METHOD(TestReadingPurchaseFromXML)
		{
			Purchase purchase("purchase1", 1.0, 5);
			XMLWriter writer;
			purchase.ToXML(writer);
			XMLReader reader{ writer.FlushAsString() };
			Purchase purchaseRead{ reader };

			Assert::IsTrue(purchase == purchaseRead);
		}

		TEST_METHOD(TestReadingCustomerFromXML)
		{
			Customer customer("Jon", "Romania", "Data");
			XMLWriter writer;
			customer.ToXML(writer);
			XMLReader reader{ writer.FlushAsString() };
			Customer customerRead{ reader };

			Assert::IsTrue(customer == customerRead);
		}

		TEST_METHOD(TestReadingOrderFromXML)
		{
			XMLWriter writer;
			std::unique_ptr<Order> order = GetTestOrder();
			order->ToXML(writer);
			XMLReader reader{ writer.FlushAsString() };
			Order orderRead{ reader };

			Assert::IsTrue(*order == orderRead);
		}

		TEST_METHOD(TestSortingPurchases)
		{
			std::vector<Purchase> purchases;
			purchases.push_back(Purchase("Purchase1", 2.0, 5));
			purchases.push_back(Purchase("Purchase0", 4.0, 1));
			purchases.push_back(Purchase("Purchase3", 7.0, 4));
			purchases.push_back(Purchase("Purchase2", 6.0, 3));

			std::vector<Purchase> stdSortedPurchases{ purchases };
			std::sort(stdSortedPurchases.begin(), stdSortedPurchases.end());

			std::unique_ptr<Order> order{ new Order(getTestCustomer()) };
			order->AddPurchases(purchases);
			order->SortPurchases();

			Assert::IsTrue(std::equal(stdSortedPurchases.begin(), stdSortedPurchases.end(), order->GetPurchases().begin()));
		}
	};
}