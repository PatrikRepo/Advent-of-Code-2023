#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::vector<std::string>> &maps)
{
	std::string line;
	
	std::ifstream input("input.txt");
  if(input.is_open())
	{
		while(getline(input,line))
		{
			std::vector<std::string> map;
			map.push_back(line);
			while(getline(input,line) && line != "")
			{
				map.push_back(line);
			}
			maps.push_back(map);
		}
	}
	
	input.close();
}

bool checkIfOneError(const std::string &line1, const std::string &line2)
{
	bool oneError = false;
	for(unsigned int i=0; i<line1.length(); i++)
	{
		if(line1[i] != line2[i])
		{
			if(!oneError)
			{
				oneError = true;
			}
			else
			{
				oneError = false;
				break;
			}
		}
	}
	
	return oneError;
}

uint64_t summarizeFaultyMirrors(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	std::string previousLine = "";
	int mapSize = map.size();
	bool foundMirror = false;
	bool oneError = false;
	
	for(int i=0; i<mapSize; i++)
	{
		oneError = checkIfOneError(map.at(i), previousLine);
		if(map.at(i) == previousLine || oneError)
		{
			oneError = false;
			foundMirror = true;
			for(int j=i; (2*i)-j-1>=0 && j<mapSize; j++)
			{
				if(map.at(j) != map.at((2*i)-j-1))
				{
					if(!oneError)
					{
						oneError = checkIfOneError(map.at(j), map.at((2*i)-j-1));
						if(oneError)
						{
							continue;
						}
					}
					else
					{
						oneError = false;
						foundMirror = false;
						break;
					}
				}
			}
			if(foundMirror && oneError)
			{
				result += 100*i;
				break;
			}
			else
			{
				foundMirror=false;
			}
		}
		previousLine = map.at(i);
	}
	
	if(!foundMirror)
	{
		int stringLength = previousLine.length();
		previousLine = "";
		
		for(int i=0; i<stringLength; i++)
		{
			std::string currentLine = "";
			for(auto it=map.begin(); it!=map.end(); it++)
			{
				currentLine += (*it)[i];
			}
			oneError = checkIfOneError(currentLine, previousLine);
			if(currentLine == previousLine || oneError)
			{
				oneError = false;
				foundMirror = true;
				for(int j=i; (2*i)-j-1>=0 && j<stringLength; j++)
				{
					std::string line1 = "";
					std::string line2 = "";
					
					for(auto it=map.begin(); it!=map.end(); it++)
					{
						line1 += (*it)[(2*i)-j-1];
					}
					for(auto it=map.begin(); it!=map.end(); it++)
					{
						line2 += (*it)[j];
					}
					if(line1 != line2)
					{
						if(!oneError)
						{
							oneError = checkIfOneError(line1, line2);
							if(oneError)
							{
								continue;
							}
						}
						else
						{
							oneError = false;
							foundMirror = false;
							break;
						}
					}
				}
				if(foundMirror && oneError)
				{
					result += i;
					break;
				}
				else
				{
					foundMirror = false;
				}
			}
			previousLine = currentLine;
		}
	}
	return result;
}

uint64_t summarizeMirrors(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	std::string previousLine = "";
	int mapSize = map.size();
	bool foundMirror = false;
	
	for(int i=0; i<mapSize; i++)
	{
		if(map.at(i) == previousLine)
		{
			foundMirror = true;
			for(int j=i; (2*i)-j-1>=0 && j<mapSize; j++)
			{
				if(map.at(j) != map.at((2*i)-j-1))
				{
					foundMirror = false;
					break;
				}
			}
			if(foundMirror)
			{
				result += 100*i;
				break;
			}
		}
		previousLine = map.at(i);
	}
	
	if(!foundMirror)
	{
		int stringLength = previousLine.length();
		previousLine = "";
		
		for(int i=0; i<stringLength; i++)
		{
			std::string currentLine = "";
			for(auto it=map.begin(); it!=map.end(); it++)
			{
				currentLine += (*it)[i];
			}

			if(currentLine == previousLine)
			{
				foundMirror = true;
				for(int j=i; (2*i)-j-1>=0 && j<stringLength; j++)
				{
					std::string line1 = "";
					std::string line2 = "";
					
					for(auto it=map.begin(); it!=map.end(); it++)
					{
						line1 += (*it)[(2*i)-j-1];
					}
					for(auto it=map.begin(); it!=map.end(); it++)
					{
						line2 += (*it)[j];
					}
					if(line1 != line2)
					{
						foundMirror = false;
						break;
					}
				}
				if(foundMirror)
				{
					result += i;
					break;
				}
			}
			previousLine = currentLine;
		}
	}
	return result;
}


int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::vector<std::string>> maps;
	
	parseInput(maps);
	
	for(unsigned int i=0; i<maps.size(); i++)
	{
		resultA += summarizeMirrors(maps[i]);
		resultB += summarizeFaultyMirrors(maps[i]);
	}
	
	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
	return 0;
}
