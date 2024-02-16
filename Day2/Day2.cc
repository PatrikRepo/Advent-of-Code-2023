#include <iostream>
#include <fstream>
#include <vector>

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

bool isGamePossible(const std::string &line)
{
	bool result = true;
	const int red = 12;
	const int green = 13;
	const int blue = 14;
	char color;
	int amount = 0;
	size_t pos = line.find_first_of(":");
	size_t numberPos = 0;
	bool done = false;
	std::string readLine = line.substr(pos+2);;
	
	while(!done)
	{
		pos = readLine.find_first_of(",;");
		if(pos == std::string::npos)
		{
			done = true;
			pos = readLine.length();
		}
		color = readLine[pos-1];
		numberPos = readLine.find_first_of("0123456789");
		switch(color)
		{
			case 'd':
				amount = std::stoi(readLine.substr(numberPos,pos-numberPos-4));
				if(red<amount)
				{
					result=false;
				}
				break;
			case 'n':
				amount = std::stoi(readLine.substr(numberPos,pos-numberPos-6));
				if(green<amount)
				{
					result=false;
				}
				break;
			case 'e':
				amount = std::stoi(readLine.substr(numberPos,pos-numberPos-5));
				if(blue<amount)
				{
					result=false;
				}
				break;
		}
		if(!result || done)
		{
			break;
		}
		readLine = readLine.substr(pos+1);
	}
	
	return result;
}

uint64_t gamePossiblePower(const std::string &line)
{
	uint64_t result = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	char color;
	int amount = 0;
	std::string readLine;
	
	size_t pos = line.find_first_of(":");
	readLine = line.substr(pos+2);
	size_t numberPos;
	bool done = false;
	while(!done)
	{
		pos = readLine.find_first_of(",;");
		if(pos == std::string::npos)
		{
			done = true;
			pos = readLine.length();
		}
		color = readLine[pos-1];
		numberPos = readLine.find_first_of("0123456789");
		switch(color)
		{
			case 'd':
				amount = std::stoi(readLine.substr(numberPos,pos-numberPos-4));
				if(red<amount)
				{
					red=amount;
				}
				break;
			case 'n':
				amount = std::stoi(readLine.substr(numberPos,pos-numberPos-6));
				if(green<amount)
				{
					green=amount;
				}
				break;
			case 'e':
				amount = std::stoi(readLine.substr(numberPos,pos-numberPos-5));
				if(blue<amount)
				{
					blue=amount;
				}
				break;
		}
		if(done)
		{
			break;
		}
		readLine = readLine.substr(pos+1);
		
	}
	result = red*green*blue;
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	int id = 1;
	std::vector<std::string> lines;
	
	parseInput(lines);

	for(auto it=lines.begin(); it!=lines.end(); it++)
	{
		if(isGamePossible(*it))
		{
			resultA += id;
		}
		resultB += gamePossiblePower(*it);
		
		id++;
	}
  
	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << '\n';
	return 0;
}
