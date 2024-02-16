#include <iostream>
#include <fstream>
#include <vector>

std::vector<int64_t> getNumbers(std::string &line)
{
	size_t pos = 0;
	size_t endpos = 0;
	int64_t number = 0;
	pos = line.find_first_of("0123456789");
	std::vector<int64_t> numbers;
	
	while(pos != std::string::npos)
	{
		endpos = line.find_first_not_of("0123456789", pos);
		if(endpos == std::string::npos)
		{
			endpos = line.length();
		}
		if(pos > 0 && line[pos-1] == '-')
    {
      pos--;
    }
		number = std::stol(line.substr(pos, endpos - pos));
		numbers.push_back(number);
		
		pos = line.find_first_of("0123456789", endpos);

	}
	
	return numbers;
}

void parseInput(std::vector<std::vector<int64_t>> &numbers)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			numbers.push_back(getNumbers(line));
		}
	}
	input.close();
}

int64_t extrapolate(const std::vector<std::int64_t> &numbers)
{
	int64_t result = 0;
	int64_t difference = 0;
	int64_t newDiff = 0;
	int64_t number = 0;
	std::vector<std::int64_t> newNumbers;
	bool diffSet = false;
	bool diffSame = true;
	int count = 0;
	
	for(auto it=numbers.begin()+1; it!=numbers.end(); it++)
	{
		if(!diffSet)
		{
			difference = *it - *(it-1);
			diffSet = true;
			count++;
		}
		else
		{
			if(diffSame)
			{
				number = *it;
				newDiff = number - *(it-1);
				if(difference != newDiff)
				{
					diffSame = false;
					for(int i=0; i<count; i++)
					{
						newNumbers.push_back(difference);
					}
					newNumbers.push_back(newDiff);
				}
				else
				{
					count++;
				}
			}
			else
			{
				number = *it;
				newDiff = number - *(it-1);
				newNumbers.push_back(newDiff);
			}
		}
	}
	
	if(!diffSame)
	{
		difference = extrapolate(newNumbers);
	}
	
	result = number + difference;
	
	return result;
}

int64_t extrapolateBack(const std::vector<std::int64_t> &numbers)
{
	int64_t result = 0;
	int64_t difference = 0;
	int64_t newDiff = 0;
	int64_t number = 0;
	std::vector<std::int64_t> newNumbers;
	bool diffSet = false;
	bool diffSame = true;
	int count = 0;
	
	for(auto it=numbers.begin()+1; it!=numbers.end(); it++)
	{
		if(!diffSet)
		{
			number = *(it-1);
			difference = *it - *(it-1);
			diffSet = true;
			count++;
		}
		else
		{
			if(diffSame)
			{
				newDiff = *it - *(it-1);
				if(difference != newDiff)
				{
					diffSame = false;
					for(int i=0; i<count; i++)
					{
						newNumbers.push_back(difference);
					}
					newNumbers.push_back(newDiff);
				}
				else
				{
					count++;
				}
			}
			else
			{
				newDiff = *it - *(it-1);
				newNumbers.push_back(newDiff);
			}
		}
	}
	
	if(!diffSame)
	{
		difference = extrapolateBack(newNumbers);
	}
	
	result = number - difference;
	
	return result;
}

int main()
{
	int64_t resultA = 0;
	int64_t resultB = 0;
	std::vector<std::vector<std::int64_t>> numbers;
	
	parseInput(numbers);
	
	for(auto it=numbers.begin(); it!=numbers.end(); it++)
	{
		resultA += extrapolate(*it);
		resultB += extrapolateBack(*it);
	}
	
	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	
	return 0;
}
