#include <iostream>
#include <fstream>
#include <vector>

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

bool markEnergyMap(size_t posX, size_t posY, char direction, std::vector<std::string> &energyMap)
{
	bool done = false;
	char energy = energyMap[posY][posX];
	
	if(energy != '/' && energy != '\\' && energy != 'M')
	{
		switch(direction)
		{
			case 'L':
			case 'R':
				if(energy == '+' || energy == 'H')
				{
					done = true;
				}
				else
				{
					if(energy == 'V')
					{
						energyMap[posY][posX] = '+';
					}
					else
					{
						energyMap[posY][posX] = 'H';
					}
				}
				break;
			case 'U':
			case 'D':
				if(energy == '+' || energy == 'V')
				{
					done = true;
				}
				else
				{
					if(energy == 'H')
					{
						energyMap[posY][posX] = '+';
					}
					else
					{
						energyMap[posY][posX] = 'V';
					}
				}
		}
	}
	
	return done;
}

void forwardRotation(char &direction)
{
	switch(direction)
	{
		case 'U':
			direction = 'R';
			break;
		case 'R':
			direction = 'U';
			break;
		case 'D':
			direction = 'L';
			break;
		case 'L':
			direction = 'D';
	}
}

void backwardRotation(char &direction)
{
	switch(direction)
	{
		case 'U':
			direction = 'L';
			break;
		case 'L':
			direction = 'U';
			break;
		case 'D':
			direction = 'R';
			break;
		case 'R':
			direction = 'D';
	}
}

void walk(size_t posX, size_t posY, char direction, std::vector<std::string> &map, std::vector<std::string> &energyMap)
{
	bool done = false;
	
	done = markEnergyMap(posX, posY, direction, energyMap);
	while(!done)
	{
		char currentPos = map[posY][posX];
		switch(currentPos)
		{
			case '/':
				forwardRotation(direction);
				energyMap[posY][posX] = 'M';
				break;
			case '\\':
				backwardRotation(direction);
				energyMap[posY][posX] = 'M';
				break;
			case '|':
				if(direction == 'R' || direction == 'L')
				{
					energyMap[posY][posX] = '+';
					done = true;
					if(posY+1 < map.size())
					{
						walk(posX, posY+1, 'D', map, energyMap);
					}
					if(posY > 0)
					{
						walk(posX, posY-1, 'U', map, energyMap);
					}
				}
				break;
			case '-':
				if(direction == 'U' || direction == 'D')
				{
					energyMap[posY][posX] = '+';
					done = true;
					if(posX+1 < map[0].length())
					{
						walk(posX+1, posY, 'R', map, energyMap);
					}
					if(posX > 0)
					{
						walk(posX-1, posY, 'L', map, energyMap);
					}
				}
		}
			
		if(!done)
		{
			switch(direction)
			{
				case 'U':
					if(posY > 0)
					{
						posY--;
					}
					else
					{
						done = true;
					}
					break;
				case 'R':
					if(posX + 1 < map[0].length())
					{
						posX++;
					}
					else
					{
						done = true;
					}
					break;
				case 'D':
					if(posY + 1 < map.size())
					{
						posY++;
					}
					else
					{
						done = true;
					}
					break;
				case 'L':
					if(posX > 0)
					{
						posX--;
					}
					else
					{
						done = true;
					}
			}
		}
		if(!done)
		{
			done = markEnergyMap(posX, posY, direction, energyMap);
		}
	}
}

uint64_t calculateEnergy(std::vector<std::string> &energyMap)
{
	uint64_t result = 0;
	
	for(unsigned int posY=0; posY<energyMap.size(); posY++)
	{
		for(unsigned int posX=0; posX<energyMap[0].length(); posX++)
		{
			char token = energyMap[posY][posX];
			if(token == 'H' || token == 'V' || token == '+' || token == 'M')
			{
				result++;
			}
		}
	}
	return result;
}

void emptyEnergyMap(std::vector<std::string> &map, std::vector<std::string> &energyMap)
{
	for(unsigned int i=0; i<map.size(); i++)
	{
		energyMap[i] = map[i];
	}
}

uint64_t calculateMaxEnergy(std::vector<std::string> &map, std::vector<std::string> &energyMap)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		emptyEnergyMap(map, energyMap);
		
		uint64_t newResult = 0;
		
		walk(i, 0, 'D', map, energyMap);
		
		newResult = calculateEnergy(energyMap);

		if(newResult > result)
		{
			result = newResult;
		}
		
		emptyEnergyMap(map, energyMap);
		
		walk(i, map.size()-1, 'U', map, energyMap);
		
		newResult = calculateEnergy(energyMap);

		if(newResult > result)
		{
			result = newResult;
		}
	}
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		uint64_t newResult = 0;
		emptyEnergyMap(map, energyMap);
		

		
		walk(0, i, 'R', map, energyMap);
		
		newResult = calculateEnergy(energyMap);
		
		if(newResult > result)
		{
			result = newResult;
		}
		
		emptyEnergyMap(map, energyMap);

		walk(map[0].length()-1, i, 'L', map, energyMap);
		
		newResult = calculateEnergy(energyMap);

		if(newResult > result)
		{
			result = newResult;
		}
	}
	
	return result;
}

void traverseMap(std::vector<std::string> &map, std::vector<std::string> &energyMap)
{
	size_t posX = 0;
	size_t posY = 0;
	char direction = 'R';
	
	walk(posX, posY, direction, map, energyMap);
}


int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> map;
	std::vector<std::string> energyMap;
	
	parseInput(map);
	energyMap = map;
	
	traverseMap(map, energyMap);
	
	resultA = calculateEnergy(energyMap);
	resultB = calculateMaxEnergy(map, energyMap);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
