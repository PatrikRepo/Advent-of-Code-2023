#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

struct Lines
{
	std::string above;
	std::string line;
	std::string below;
	Lines(std::string a, std::string l, std::string b) : above(a), line(l), below(b) {}
};

struct GearNumbers
{
	bool firstDigitSet = false;
	bool secondDigitSet = false;
	bool isGear = false;
	std::pair<size_t,size_t> pos1;
	std::pair<size_t,size_t> pos2;
	bool setPosition(size_t line, size_t pos)
	{
		bool results = true;
		if(!firstDigitSet)
		{
			pos1.first = line;
			pos1.second = pos;
			firstDigitSet = true;
		}
		else if(!secondDigitSet)
		{
			pos2.first = line;
			pos2.second = pos;
			secondDigitSet = true;
			isGear = true;
		}
		else
		{
			results = false;
			isGear = false;
    }
	return results;
	}
};

void parseInput(std::vector<std::string> &map)
{
	std::string line;

	std::ifstream input("input.txt");
	
	if(input.is_open())
	{
		std::getline(input, line);
		int length = line.length();
		char str[length];
		
		for(int i = 0; i<length; i++)
		{
			str[i] = '.';
		}
		std::string filler(str, length);
		map.push_back(filler);
		map.push_back(line);
		
		while(std::getline(input, line))
		{
			map.push_back(line);
		}
		map.push_back(filler);
	}
	input.close();
}

bool isPart(const std::string &line)
{
	return line.find_first_not_of("0123456789.") != std::string::npos;
}

uint32_t getPartNumber(const Lines &lines)
{
	uint32_t results = 0;
	bool part = false;
	size_t pos = lines.line.find_first_of("0123456789");
	size_t startpos = 0;
	size_t endpos = 0;
  size_t scope = 0;
	size_t numscope = 0;

	while(pos != std::string::npos)
	{
		if(pos == 0)
		{
			startpos = pos;
		}
		else
		{
			startpos = pos - 1;
		}
		endpos = lines.line.find_first_not_of("0123456789", pos);

		if(endpos == std::string::npos)
		{
			scope = endpos - startpos;
			numscope = scope -1;
		}
		else
		{
			scope = endpos - startpos + 1;
			if(pos != 0)
			{
				numscope = scope -2;
			}
			else
			{
				numscope = scope - 1;
			}
		}

		if(pos != 0 && lines.line[startpos] != '.')
		{
			part = true;
		}
		if(endpos != std::string::npos && lines.line[endpos] != '.')
		{
			part = true;
		}
		else
		{
			if(isPart(lines.above.substr(startpos, scope)) || isPart(lines.below.substr(startpos, scope)))
			{
				part = true;
			}
		}
		if(part)
		{
			results += std::stoi(lines.line.substr(pos, numscope));
			part = false;
		}
		if(endpos != std::string::npos)
		{
			pos = lines.line.find_first_of("0123456789", endpos);
		}
		else
		{
			pos = std::string::npos;
		}
	}
	return results;
}

void isGear(const size_t pos, const Lines &lines, GearNumbers &gearNumbers)
{
	bool endpos = false;
	bool gotSet = true;
   
	if(pos == lines.line.length() - 1)
	{
		endpos = true;
	}
	
	if(pos!=0)
	{
		if(isdigit(lines.above[pos-1]))
		{
			gearNumbers.setPosition(1, pos-1);
			
			if(!endpos && !isdigit(lines.above[pos]) && isdigit(lines.above[pos+1]))
			{
				gotSet = gearNumbers.setPosition(1, pos+1);
			}
		}
		else if(isdigit(lines.above[pos]))
		{
			gotSet = gearNumbers.setPosition(1, pos);
		}
		else if(isdigit(lines.above[pos+1]))
		{
			gotSet = gearNumbers.setPosition(1, pos+1);
		}
		
		if(isdigit(lines.line[pos-1]))
		{
			gotSet = gearNumbers.setPosition(2, pos-1);
			
			if(!gotSet)
			{
				goto end;
			}
		}
		
		if(isdigit(lines.line[pos+1]))
		{
			gotSet = gearNumbers.setPosition(2, pos+1);
			
			if(!gotSet)
			{
				goto end;
			}
		}
		
		if(isdigit(lines.below[pos-1]))
		{
			gotSet = gearNumbers.setPosition(3, pos-1);
			
			if(!gotSet)
			{
				goto end;
			}
			
			if(!endpos && !isdigit(lines.below[pos]) && isdigit(lines.below[pos+1]))
			{
				gotSet = gearNumbers.setPosition(3, pos+1);
				
				if(!gotSet)
				{
					goto end;
				}
			}
		}
		else if(isdigit(lines.below[pos]))
		{
			gotSet = gearNumbers.setPosition(3, pos);
			
			if(!gotSet)
			{
				goto end;
			}
		}
		else if(isdigit(lines.below[pos+1]))
		{
			gotSet = gearNumbers.setPosition(3, pos+1);
			
			if(!gotSet)
			{
				goto end;
			}
		}
	}
	else
	{
		if(isdigit(lines.above[pos]))
		{
			gotSet = gearNumbers.setPosition(1, pos);
		}
		else if(isdigit(lines.above[pos+1]))
		{
			gotSet = gearNumbers.setPosition(1, pos+1);
		}
	
		if(isdigit(lines.line[pos+1]))
		{
			gotSet = gearNumbers.setPosition(2, pos+1);
		}
	
		if(isdigit(lines.below[pos]))
		{
			gotSet = gearNumbers.setPosition(3, pos);
		
			if(!gotSet)
			{
				goto end;
			}
		}
		else if(isdigit(lines.below[pos+1]))
		{
			gotSet = gearNumbers.setPosition(3, pos+1);
			if(!gotSet)
			{
				goto end;
			}
		}
	}
	end:;
}

uint32_t getGearNumber(const size_t pos, const Lines &lines)
{
	uint32_t results = 0;
	GearNumbers gearNumbers;
	size_t startNum = 0;
	size_t endNum = 0;
	uint32_t num1 = 0;
	uint32_t num2 = 0;
	
	isGear(pos, lines, gearNumbers);
    
	if(gearNumbers.isGear)
	{
		switch(gearNumbers.pos1.first)
		{
			case 1:
				startNum = lines.above.find_last_not_of("0123456789", gearNumbers.pos1.second) + 1;
				
				if(startNum == std::string::npos)
				{
					startNum = 0;
				}
				endNum = lines.above.find_first_not_of("0123456789", startNum);
				
				if(endNum == std::string::npos)
				{
					endNum = lines.above.length();
				}
				num1 = std::stoi(lines.above.substr(startNum, endNum - startNum));
				break;
			case 2:
				startNum = lines.line.find_last_not_of("0123456789", gearNumbers.pos1.second) + 1;

				if(startNum == std::string::npos)
				{
					startNum = 0;
				}
				endNum = lines.line.find_first_not_of("0123456789", startNum);
				
				if(endNum == std::string::npos)
				{
					endNum = lines.line.length();
				}
				num1 = std::stoi(lines.line.substr(startNum, endNum - startNum));
				break;
			case 3:
				startNum = lines.below.find_last_not_of("0123456789", gearNumbers.pos1.second) + 1;
				
				if(startNum == std::string::npos)
				{
					startNum = 0;
				}
				endNum = lines.below.find_first_not_of("0123456789", startNum);
				
				if(endNum == std::string::npos)
				{
					endNum = lines.below.length();
				}
				num1 = std::stoi(lines.below.substr(startNum, endNum - startNum));
				break;
		}
		
		switch(gearNumbers.pos2.first)
		{
			case 1:
				startNum = lines.above.find_last_not_of("0123456789", gearNumbers.pos2.second) + 1;
				if(startNum == std::string::npos)
				{
					startNum = 0;
				}
				endNum = lines.above.find_first_not_of("0123456789", startNum);
				
				if(endNum == std::string::npos)
				{
					endNum = lines.above.length();
				}
				num2 = std::stoi(lines.above.substr(startNum, endNum - startNum));
				break;
			case 2:
				startNum = lines.line.find_last_not_of("0123456789", gearNumbers.pos2.second) + 1;
				
				if(startNum == std::string::npos)
				{
					startNum = 0;
				}
				endNum = lines.line.find_first_not_of("0123456789", startNum);
				
				if(endNum == std::string::npos)
				{
					endNum = lines.line.length();
				}
				num2 = std::stoi(lines.line.substr(startNum, endNum - startNum));
				break;
			case 3:
				startNum = lines.below.find_last_not_of("0123456789", gearNumbers.pos2.second) + 1;
				
				if(startNum == std::string::npos)
				{
					startNum = 0;
				}
				endNum = lines.below.find_first_not_of("0123456789", startNum);
				
				if(endNum == std::string::npos)
				{
					endNum = lines.above.length();
				}
				num2 = std::stoi(lines.below.substr(startNum, endNum - startNum));
				break;
		}
		results += num1*num2;
	}
	return results;
}

uint32_t addGearNumbers(const Lines &lines)
{
	uint32_t results = 0;
	size_t pos = lines.line.find_first_of("*");

	while(pos != std::string::npos)
	{
		results += getGearNumber(pos, lines);
		pos = lines.line.find_first_of("*", pos+1);
	}
	return results;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> map;
	
	parseInput(map);

	for(auto it=map.begin()+1; it!=map.end()-1; it++)
	{
		Lines lines(*(it-1), *it, *(it+1));
		resultA += getPartNumber(lines);
		resultB += addGearNumbers(lines);
	}

	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	return 0;
}


