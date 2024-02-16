#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

void parseInput(std::vector<std::string> &map)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			map.push_back(line);
		}
	}
	input.close();
}

bool allFlagsRaised(const std::string &flaggedMap)
{
	bool allFlagsRaised = false;
	size_t pos = flaggedMap.find_first_of("#");
	if(pos == std::string::npos)
	{
		allFlagsRaised = true;
	}
	
	return allFlagsRaised;
}

uint32_t countFlagsLeft(const std::string &map)
{
	uint32_t result = 0;
	
	for(int i=0; i<map.length(); i++)
	{
		if(map[i] == '#')
		{
			result++;
		}
	}
	
	return result;
}

uint64_t fitFlagsInMap(const std::string &map, size_t pos, const std::vector<int> &flags, int flagNumber, std::unordered_map<uint32_t, uint64_t> &cashe)
{
	uint64_t result = 0;
	size_t startpos = 0;
	size_t endpos = 0;

	int flagSize = 0;

	flagSize = flags.at(flagNumber);

	while(pos != map.length())
	{
		bool foundRange = false;
		while(!foundRange)
		{
			startpos = map.find_first_not_of(".", pos);
			endpos = map.find_first_of(".", startpos);
			
			if(endpos == std::string::npos)
			{
				endpos = map.length();
			}
			
			if(endpos - startpos >= flagSize)
			{
				foundRange = true;
			}
			
			pos = endpos;
		}
		
		for(int i=startpos; i<= endpos-flagSize; i++)
		{
			std::string flaggedMap = map;
			
			for(int j=i; j<i+flagSize; j++)
			{
				flaggedMap[j] = 'F';
			}

			int newFlagNumber = flagNumber + 1;
			size_t newPos = i+flagSize;
			
			if(newFlagNumber == flags.size() || newPos == std::string::npos)
			{
				if(newFlagNumber == flags.size() && allFlagsRaised(flaggedMap))
				{
					result += 1;
				}
			}
			else
			{
				uint32_t flagsLeft = countFlagsLeft(flaggedMap);
				uint32_t casheNumber = (newPos+1)*100000 + newFlagNumber*1000 + flagsLeft;
				if(cashe.count(casheNumber) == 0)
				{
					uint64_t newresult = fitFlagsInMap(flaggedMap, newPos+1, flags, newFlagNumber, cashe);
					cashe[casheNumber] = newresult;
					result += newresult;
				}
				else
				{
					result+= cashe[casheNumber];
				}
			}
		}
	}

	return result;
}

uint64_t getCombinationsBigMap(const std::string &line)
{
	uint64_t result = 0;
	size_t pos = 0;
	size_t endpos = 0;
	std::string map;
	std::string fullMap;
	std::vector<int> flags;
	int flagNumber = 0;
	std::unordered_map<uint32_t, uint64_t> cashe;

	pos = line.find_first_of(" ");
	map = line.substr(0, pos);
	fullMap = map;
	for(int i = 0; i<4; i++)
	{
		fullMap += "?" + map;
	}

	pos = line.find_first_of("0123456789", pos);
	for(int i=0; i<5; i++)
	{
		size_t newpos = pos;
		while(newpos != std::string::npos)
		{
			endpos = line.find_first_not_of("0123456789", newpos);
			if(endpos == std::string::npos)
			{
				endpos = line.length();
			}
			flags.push_back(std::stoi(line.substr(newpos, endpos-pos)));
			newpos = line.find_first_of("0123456789", endpos);
		}
	}

	result = fitFlagsInMap(fullMap, 0, flags, flagNumber, cashe);  
 
	return result;
}

uint64_t getCombinationsSmallMap(const std::string &line)
{
	uint64_t result = 0;
	size_t pos = 0;
	size_t endpos = 0;
	std::string map;
	std::vector<int> flags;
	int flagNumber = 0;
  std::unordered_map<uint32_t, uint64_t> cashe;
	pos = line.find_first_of(" ");
	map = line.substr(0, pos);
 
	pos = line.find_first_of("0123456789", pos);
	while(pos != std::string::npos)
	{
		endpos = line.find_first_not_of("0123456789", pos);
		if(endpos == std::string::npos)
		{
				endpos = line.length();
		}
		flags.push_back(std::stoi(line.substr(pos, endpos-pos)));
		pos = line.find_first_of("0123456789", endpos);
	}

	result = fitFlagsInMap(map, 0, flags, flagNumber, cashe);
   
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> map;
  
	parseInput(map);
	
	for(int i=0; i<map.size(); i++)
	{
		resultA += getCombinationsSmallMap(map[i]);
		resultB += getCombinationsBigMap(map[i]);
	}

	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
 
  return 0;
}
