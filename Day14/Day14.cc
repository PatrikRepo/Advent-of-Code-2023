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

void moveBouldersNorth(std::vector<std::string> &map)
{
	int stringSize = map.at(0).length();
	int vectorSize = map.size();
	
	for(int i=0; i<stringSize; i++)
	{
		int emptyPos = 0;
		for(int j=0; j<vectorSize; j++)
		{

			switch((map.at(j))[i])
			{
				case 'O':
					(map.at(j))[i] = '.';
					(map.at(emptyPos))[i] = 'O';
					emptyPos++;
					break;
				case '#':
					emptyPos = j+1;
			}
		}
	}
}

void moveBouldersWest(std::vector<std::string> &map)
{
	int stringSize = map.at(0).length();
	int vectorSize = map.size();
	
	for(int i=0; i<vectorSize; i++)
	{
		int emptyPos = 0;
		for(int j=0; j<stringSize; j++)
		{

			switch((map.at(i))[j])
			{
				case 'O':
					(map.at(i))[j] = '.';
					(map.at(i))[emptyPos] = 'O';
					emptyPos++;
					break;
				case '#':
					emptyPos = j+1;
			}
		}
	}
}

void moveBouldersSouth(std::vector<std::string> &map)
{
	int stringSize = map.at(0).length();
	int vectorSize = map.size();
	
	for(int i=0; i<stringSize; i++)
	{
		int emptyPos = vectorSize-1;
		for(int j=vectorSize-1; j>=0; j--)
		{

			switch((map.at(j))[i])
			{
				case 'O':
					(map.at(j))[i] = '.';
					(map.at(emptyPos))[i] = 'O';
					emptyPos--;
					break;
				case '#':
					emptyPos = j-1;
			}
		}
	}
}

void moveBouldersEast(std::vector<std::string> &map)
{
	int stringSize = map.at(0).length();
	int vectorSize = map.size();

	for(int i=0; i<vectorSize; i++)
	{
		int emptyPos = stringSize-1;
		for(int j=stringSize-1; j>=0; j--)
		{

			switch((map.at(i))[j])
			{
				case 'O':
					(map.at(i))[j] = '.';
					(map.at(i))[emptyPos] = 'O';
					emptyPos--;
					break;
				case '#':
					emptyPos = j-1;
			}
		}
	}
}

std::string getMapString(const std::vector<std::string> &map)
{
	std::string mapString;
	
	for(auto it=map.begin(); it!=map.end(); it++)
	{
		mapString += *it;
	}
	
	return mapString;
}

void moveBoulders(std::vector<std::string> &map, const uint32_t period, const uint32_t cycles)
{
	std::unordered_map<std::string, std::vector<std::string>> cashe;
	std::string mapString = "";
	std::string oldMapString = "old";

	uint32_t newCycles = (1000/period)*period + cycles%period; 
	for(uint32_t i=0; i<newCycles; i++)
	{	
		mapString = getMapString(map);
		if(cashe.count(mapString) == 0)
		{
			moveBouldersNorth(map);
			moveBouldersWest(map);
			moveBouldersSouth(map);
			moveBouldersEast(map);
			cashe[mapString] = map;
		}
		else
		{
			map = cashe[mapString];
		}
	}

}

uint32_t calculatePeriod(std::vector<std::string> map)
{
	std::unordered_map<std::string, std::vector<std::string>> cashe;
	std::string mapString = "";
	std::string oldMapString = "old";
	uint32_t period = 1;
	
	for(uint64_t i=0; i<1000; i++)
	{	
		mapString = getMapString(map);


		if(cashe.count(mapString) == 0)
		{
			moveBouldersNorth(map);
			moveBouldersWest(map);
			moveBouldersSouth(map);
			moveBouldersEast(map);
			cashe[mapString] = map;
		}
		else
		{
			map = cashe[mapString];
		}
	}
	oldMapString = mapString;
	
	mapString = getMapString(map);
	while(oldMapString != mapString)
	{
		period++;
		
		if(cashe.count(mapString) == 0)
		{
			moveBouldersNorth(map);
			moveBouldersWest(map);
			moveBouldersSouth(map);
			moveBouldersEast(map);
			cashe[mapString] = map;
		}
		else
		{
			map = cashe[mapString];
		}
		mapString = getMapString(map);
	}
	
	return period;
}

uint64_t calculateWeight(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	int stringSize = map.at(0).length();
	int vectorSize = map.size();
	
	for(int i=0; i<vectorSize; i++)
	{
		for(int j=0; j<stringSize; j++)
		{
			if((map.at(i))[j] == 'O')
			{
				result += vectorSize - i;
			}
			
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	uint32_t period = 0;
	std::vector<std::string> mapA;
	std::vector<std::string> mapB;
	parseInput(mapA);
	mapB = mapA;
	
	moveBouldersNorth(mapA);
	resultA = calculateWeight(mapA);
	
	period = calculatePeriod(mapB);
	
	moveBoulders(mapB, period, 1000000000);
	resultB = calculateWeight(mapB);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;	
}
