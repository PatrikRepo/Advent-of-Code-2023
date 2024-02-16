#include <iostream>
#include <fstream>
#include <vector>

std::string words[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
std::uint32_t numbers[] = {1,2,3,4,5,6,7,8,9};

void parseInput(std::vector<std::string> &lines)
{
	std::string line;
	std::ifstream input("input.txt");
  if(input.is_open())
  {
  	while(getline(input, line))
  	{
  		lines.push_back(line);
    }
  }
  input.close();
}

uint64_t getFirstNumWithoutWords(const std::string &line)
{
	uint64_t num = 0;
	size_t pos = line.find_first_of("0123456789");
	num = line[pos] - '0';

	num *= 10;
	return num;
}

uint64_t getFirstNumWithWords(const std::string &line)
{
	uint64_t num = 0;
	size_t pos = line.find_first_of("0123456789");
	num = line[pos] - '0';
	for(int i = 0; i < 9; i++)
	{
		size_t newPos = line.find(words[i]);
		if(newPos < pos)
		{
			pos = newPos;
			num = numbers[i];
		}
	}
	num *= 10;
	return num;
}

uint64_t getLastNumWithoutWords(const std::string &line)
{
	uint64_t num = 0;
	size_t pos = line.find_last_of("0123456789");
	num = line[pos] - '0';

	return num;
}

uint64_t getLastNumWithWords(const std::string &line)
{
	uint64_t num = 0;
	size_t pos = line.find_last_of("0123456789");
	num = line[pos] - '0';
	for(int i = 0; i < 9; i++)
	{
		size_t newPos = line.rfind(words[i]);
		if(newPos > pos && newPos != std::string::npos)
		{
			pos = newPos;
			num = numbers[i];
		}
	}
	return num;
}

void getSum(const std::vector<std::string> &lines, uint64_t &resultA, uint64_t &resultB)
{
	for(auto it=lines.begin(); it!=lines.end(); it++)
	{
		resultA += getFirstNumWithoutWords(*it);
		resultA += getLastNumWithoutWords(*it);
		resultB += getFirstNumWithWords(*it);
		resultB += getLastNumWithWords(*it);
	}
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> lines;
	
	parseInput(lines);

	getSum(lines, resultA, resultB);

  std::cout << "Result A: " << resultA << '\n';
  std::cout << "Result B: " << resultB << std::endl;
  
  return 0;
}
