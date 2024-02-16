#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::vector<std::string> &map)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			map.push_back(line);
		}
	}
	input.close();
}

void findStartCoordinates(size_t &posX, size_t &posY, const std::vector<std::string> &map)
{
	size_t pos = 0;
	for(unsigned int i=0; i<map.size(); i++)
	{
		pos = map[i].find_first_of("S");
		if(pos != std::string::npos)
		{
			posX = pos;
			posY = i;
			break;
		}
	}
}

void removeJunkFromMap(std::vector<std::string> &map, const std::vector<std::string> &loopMap)
{
	for(unsigned int i=0; i<loopMap.size(); i++)
	{
		for(unsigned int j=0; j<loopMap[0].length(); j++)
		{
			if(loopMap[i][j] != 'X')
			{
				map[i][j] = '.';
			}
		}
	}
}

void findNorthwesternF(size_t &posX, size_t &posY, const std::vector<std::string> &map)
{
	size_t pos = 0;
	for(unsigned int i=0; i<map.size(); i++)
	{
		pos = map[i].find_first_of("F");
		if(pos != std::string::npos)
		{
			posX = pos;
			posY = i;
			break;
		}
	}
}

void setNewInnerSide(const char &from, size_t &innerX, size_t &innerY)
{
	switch(from)
	{
		case 'D':
			innerX++;
			break;
		case 'L':
			innerY++;
			break;
		case 'U':
			innerX--;
			break;
		case 'R':
			innerY--;
	}
}

void newPos(size_t &posX, size_t &posY, char &currentPos, char &from, std::vector<std::string> &map)
{
	switch(currentPos)
	{
		case '|':
			if(from == 'D')
			{
				posY--;
				from = 'D';
			} 
			else
			{
				posY++;
				from = 'U';
			}
			break;
		case '-':
			if(from == 'L')
			{
				posX++;
				from = 'L';
			}
			else
			{
				posX--;
				from = 'R';
			}
			break;
		case '7':
			if(from == 'D')
			{
				posX--;
				from = 'R';
			}
			else
			{
				posY++;
				from = 'U';
			}
			break;
		case 'F':
			if(from == 'D')
			{
				posX++;
				from = 'L';
			}
			else
			{
				posY++;
				from = 'U';
			}
			break;
		case 'J':
			if(from == 'U')
			{
				posX--;
				from = 'R';
			}
			else
			{
				posY--;
				from = 'D';
			}
			break;
		case 'L':
			if(from == 'U')
			{
				posX++;
				from = 'L';
			}
			else
			{
				posY--;
				from = 'D';
			}
			break;
	}
	currentPos = map[posY][posX];
}


void markAndCount(const size_t innerX, const size_t innerY, uint64_t &area, std::vector<std::string> &map)
{
	if(map[innerY][innerX] == '.')
	{
		map[innerY][innerX] = 'I';
		area++;
		if(innerX < 139)
		{
				markAndCount(innerX+1,innerY, area, map);
		}
		if(innerX > 0)
		{
				markAndCount(innerX-1,innerY, area, map);
		}
		if(innerY < 139)
		{
				markAndCount(innerX,innerY+1, area, map);
		}
		if(innerY > 0)
		{
				markAndCount(innerX,innerY-1, area, map);
		}
	}
}

std::pair<uint64_t,uint64_t> countArea(std::vector<std::string> &map, std::vector<std::string> &loopMap)
{
	std::pair<uint64_t,uint64_t> result;
	uint64_t steps = 0;
	uint64_t val = 0;
	size_t posX = 0;
	size_t posY = 0;
	size_t innerX = 0;
	size_t innerY = 0;
	char currentPos = 0;
	char from = 0;
	
	findStartCoordinates(posX, posY, map);
	
	posX++;
	steps++;
	currentPos = map[posY][posX];
	loopMap[posY][posX] = 'X';
	from = 'L';
	
	while(currentPos != 'S')
	{
		steps++;
		newPos(posX, posY, currentPos, from, map);
		loopMap[posY][posX] = 'X';
	}
	result.first = steps/2;
	
	map[posY][posX] = 'L';

	removeJunkFromMap(map, loopMap);

	findNorthwesternF(posX, posY, map);

	currentPos = 'F';
	from = 'D';
	
	while(currentPos != 'X')
	{
		newPos(posX, posY, currentPos, from, map);
		innerX = posX;
		innerY = posY;
		setNewInnerSide(from, innerX, innerY);
		markAndCount(innerX, innerY, val, map);
		if(currentPos == '7' && from == 'D')
		{
			markAndCount(posX, posY-1, val, map);
		}
		if(currentPos == 'J' && from == 'L')
		{
			markAndCount(posX+1, posY, val, map);
		}
		if(currentPos == 'L' && from == 'U')
		{
			markAndCount(posX, posY+1, val, map);
		}
		if(currentPos == 'F' && from == 'R')
		{
			markAndCount(posX-1, posY, val, map);
		}
		map[posY][posX] = 'X';
	}
	result.second = val;
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;

	std::vector<std::string> map;
	std::vector<std::string> loopMap;
	
	parseInput(map);
	loopMap = map;
	
	result = countArea(map, loopMap);

	std::cout << "result A: " << result.first << '\n';
	std::cout << "result B: " << result.second << std::endl;
	
	return 0;
}
