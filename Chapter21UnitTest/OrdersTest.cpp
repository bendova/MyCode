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

		std::unique_ptr<Order> GetTestOrder()
		{
			Customer myCustomer("Ion", "Humulesti", "Copilarie");
			std::unique_ptr<Order> order{ new Order(myCustomer) };

			std::ostringstream osstream;
			const unsigned purchasesCount = 10;
			for (unsigned i = 0; i < purchasesCount; ++i)
			{
				osstream.str("");
				osstream << "purchase" << i;
				Purchase cartofiPurchase(osstream.str(), i, 5 * i);
				order->AddPurchase(cartofiPurchase);
			}
			
			return order;
		}

		std::string GetOrderAsString()
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

		std::string GetOrderAsXML(std::unique_ptr<Order> order)
		{
			std::ostringstream outputBuffer;
			order->ToXML(outputBuffer);
			return outputBuffer.str();
		}

		void WriteToFile(const std::string& filePath, const std::string& content)
		{
			std::ofstream outputFile;
			outputFile.open(filePath.c_str(), std::ofstream::out);
			if (outputFile.good())
			{
				outputFile << content;
			}
			outputFile.close();
		}

		std::string ReadFromFile(const std::string& filePath)
		{
			std::ifstream inputFile;
			inputFile.open(filePath.c_str(), std::ifstream::in);

			std::string readContent{ std::istreambuf_iterator < char > {inputFile},
				std::istreambuf_iterator < char > {} };

			return readContent;
		}

		TEST_METHOD(TestOrderToXML)
		{
			std::string fileName{ "Orders.xml" };
			std::string contentToWrite = GetOrderAsXML(GetTestOrder());
			WriteToFile(fileName, contentToWrite);

			std::string readContent = ReadFromFile(fileName);

			Assert::AreEqual(0, contentToWrite.compare(readContent));
		}
	};
}