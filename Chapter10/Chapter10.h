#include <string>
#include <vector>

namespace MyCode
{
	int GetSumOfIntegersFromFile(const std::string& filePath);
	bool WriteIntegersToFile(const std::string& filePath, const std::vector<int>& values, const std::string& valueSeparator);
	std::vector<int> ReadIntegersFromFile(const std::string& filePath);
}