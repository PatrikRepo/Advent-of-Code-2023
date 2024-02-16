#include <iostream>
#include <fstream>
#include <vector>
#include <utility>


uint32_t abs(const uint64_t x, const uint64_t y)
{
	uint32_t result = 0;
	uint32_t diff = x-y;
	result = diff >= 0 ? diff : -diff;
	return result;
}

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

void expandVertically(std::vector<std::string> &map)
{
	for(unsigned int i=0; i<map.size(); i++)
	{
		size_t pos = 0;
		pos = map[i].find_first_of("#");
		if(pos == std::string::npos)
		{
			for(unsigned int j=0; j<map[0].length(); j++)
			{
				map[i][j] = 'Y';
			}
		}
	}
}

void expandHorizontally(std::vector<std::string> &map)
{
	for(unsigned int i=0; i<map.at(0).length(); i++)
	{
		bool empty = true;
		for(auto it=map.begin(); it!=map.end(); it++)
		{
			if((*it)[i] == '#')
			{
				empty = false;
			}
		}
		if(empty)
		{
			for(auto it=map.begin(); it!=map.end(); it++)
			{
				if((*it)[i] != 'Y')
				{
					(*it)[i] = 'X';
				}
			}
		}
	}
}

void determineSmallGalaxyCoordinates(const std::vector<std::string> &map, std::vector<std::pair<uint64_t,uint64_t>> &galaxies)
{
	uint64_t j=0;
	uint64_t Y = 0;
	for(auto it=map.begin(); it!=map.end(); it++)
	{
		uint64_t X = 0;
		for(unsigned int i=0; i<map.at(0).length(); i++)
		{
			if((*it)[i] == '#')
			{
				galaxies.push_back(std::pair<int,int>(i+X,j+Y));
			}
			else if((*it)[i] == 'X')
			{
				X++;
			}
			else if((*it)[i] == 'Y')
			{
				Y++;
				break;
			}
		}
		j++;
	}
}

void determineBigGalaxyCoordinates(const std::vector<std::string> &map, std::vector<std::pair<uint64_t,uint64_t>> &galaxies)
{
	uint64_t j=0;
	uint64_t Y = 0;
	for(auto it=map.begin(); it!=map.end(); it++)
	{
		uint64_t X = 0;
		for(unsigned int i=0; i<map.at(0).length(); i++)
		{
			if((*it)[i] == '#')
			{
				galaxies.push_back(std::pair<int,int>(i+X,j+Y));
			}
			else if((*it)[i] == 'X')
			{
				X += 1000000-1;
			}
			else if((*it)[i] == 'Y')
			{
				Y += 1000000-1;
				break;
			}
		}
		j++;
	}
}

uint64_t calculateDistance(const std::vector<std::pair<uint64_t,uint64_t>> &galaxies)
{
	uint64_t result = 0;

	for(unsigned int i=0; i<galaxies.size() - 1; i++)
	{
		for(unsigned int j=i+1; j<galaxies.size(); j++)
		{
			std::pair<uint64_t,uint64_t> galaxy1 = galaxies.at(i);
			std::pair<uint64_t,uint64_t> galaxy2 = galaxies.at(j);

			result += abs(galaxy1.first - galaxy2.first) + abs(galaxy1.second - galaxy2.second);
		}
	}

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> map;
	std::vector<std::pair<uint64_t,uint64_t>> smallGalaxies;
	std::vector<std::pair<uint64_t,uint64_t>> bigGalaxies;

	parseInput(map);

	expandVertically(map);
	expandHorizontally(map);

	determineSmallGalaxyCoordinates(map, smallGalaxies);
	determineBigGalaxyCoordinates(map, bigGalaxies);

	resultA = calculateDistance(smallGalaxies);
	resultB = calculateDistance(bigGalaxies);

	std::cout << "result A: " << resultA << std::endl;
	std::cout << "result B: " << resultB << std::endl;

	return 0;
}
