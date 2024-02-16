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
	
	for(int i=1; i<130; i++)
	{
		for(int j=1; j<130; j++)
		{
			if(map[i+1][j] == '#' && map[i-1][j] == '#' && map[i][j+1] == '#' && map[i][j-1] == '#')
			{
				map[i][j] = '#';
			}
		}
	}
}

uint64_t calculateFewSteps(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	size_t posX = 0;
	size_t posY = 0;
	size_t startX = 0;
	size_t endX = 0;
	size_t startY = 0;
	size_t endY = 0;
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		posX = map[i].find_first_of("S");
		if(posX != std::string::npos)
		{
			posY = i;
			break;
		}
	}
	
	startX = posX - 64 >= 0 ? posX - 64 : 0;
	startY = posY - 64 >= 0 ? posY - 64 : 0;
	endX = posX + 64 < map[0].length() ? posX + 64 : map[0].length() - 1;
	endY = posY + 64 < map.size() ? posY + 64 : map.size() - 1;
	
	for(unsigned int i=startY; i<=endY; i++)
	{
		for(unsigned int j=startX; j<=endX; j++)
		{
			if(abs(j-posX) + abs(i-posY) <= 64 && (i + j)%2 == 0 && map[i][j] != '#')
			{
				result++;
			}
		}
	}
	return result;
}

uint64_t calculateManySteps(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	uint64_t even = 0;
	uint64_t odd = 0;
	uint64_t west = 0;
	uint64_t east = 0;
	uint64_t north = 0;
	uint64_t south = 0;
	uint64_t bigNW = 0;
	uint64_t smallNW = 0;
	uint64_t bigNE = 0;
	uint64_t smallNE = 0;
	uint64_t bigSE = 0;
	uint64_t smallSE = 0;
	uint64_t bigSW = 0;
	uint64_t smallSW = 0;
	
	for(int i=0; i<131; i++)
	{
		for(int j=0; j<131; j++)
		{
			if(map[i][j] != '#')
			{
				if((i + j)%2 == 0)
				{
					even++;
				}
				else
				{
					odd++;
				}
			}
		}
	}
	
	for(int i=0; i<131; i++)
	{
		for(int j=0; j<131; j++)
		{
			if(map[i][j] != '#')
			{
				if(j+i < 65 && (i+j)%2 == 0)
				{
					smallNW++;
				}
				else if(j+i<196 && (i+j)%2 == 1)
				{
					bigSE++;
				}
			}
		}
	}
	
	for(int i=130; i>=0; i--)
	{
		for(int j=0; j<131; j++)
		{
			if(map[i][j] != '#')
			{
				if(j+abs(i-130) < 65 && (i+j)%2 == 0)
				{
					smallSW++;
				}
				else if(j+abs(i-130)<196 && (i+j)%2 == 1)
				{
					bigNE++;
				}
			}
		}
	}
	
	for(int i=130; i>=0; i--)
	{
		for(int j=130; j>=0; j--)
		{
			if(map[i][j] != '#')
			{
				if(abs(j-130) + abs(i-130) < 65 && (i+j)%2 == 0)
				{
					smallSE++;
				}
				else if(abs(j-130) + abs(i-130)<196 && (i+j)%2 == 1)
				{
					bigNW++;
				}
			}
		}
	}
	
	for(int i=0; i<131; i++)
	{
		for(int j=130; j>=0; j--)
		{
			if(map[i][j] != '#')
			{
				if(abs(j-130) + i < 65 && (i+j)%2 == 0)
				{
					smallNE++;
				}
				else if(abs(j-130) + i <196 && (i+j)%2 == 1)
				{
					bigSW++;
				}
			}
		}
	}
	
	west = bigNW + bigSW - odd;
	north = bigNW + bigNE - odd;
	east = bigNE + bigSE - odd;
	south = bigSE + bigSW - odd;
	
	uint32_t n = 26501300/131;
	
	result += odd;
	
	for(unsigned int i=1; i<n; i++)
	{
		if(i%2 == 0)
		{
			uint32_t temp = 4*i;
			result += temp*odd;
		}
		else
		{
			uint32_t temp = 4*i;
			result += temp*even;
		}
	}
	
	result += west + north + east + south;
	result += (n-1)*bigSW;
	result += (n-1)*bigSE;
	result += (n-1)*bigNW;
	result += (n-1)*bigNE;
	result += (n)*smallSW;
	result += (n)*smallSE;
	result += (n)*smallNW;
	result += (n)*smallNE;

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> map;
	
	parseInput(map);
	
	resultA = calculateFewSteps(map);
	resultB = calculateManySteps(map);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
