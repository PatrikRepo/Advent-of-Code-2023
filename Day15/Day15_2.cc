#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::string &line)
{
	std::ifstream input("input.txt");
  if(input.is_open())
	{
		getline(input, line);
	}
	input.close();
}

uint64_t calculateHashSum(const std::string &line)
{
	uint64_t result = 0;
	size_t pos = 0;
	size_t startPos = 0;
	bool done = false;
	
	while(!done)
	{
		pos=line.find_first_of(",", startPos);
		if(pos == std::string::npos)
		{
			pos = line.length();
			done = true;
		}
		
		uint64_t hash = 0;
		for(int i=startPos; i<pos; i++)
		{
			hash += line[i];
			hash = (hash*17)%256;
		}

		result += hash;
		startPos = pos+1;
	}
	
	return result;
}

unsigned char calculateHash(const std::string &line)
{
	unsigned char hash = 0;
		
	for(int i=0; i<line.length(); i++)
		{
			hash += line[i];
			hash = (hash*17)%256;
		}
	
	return hash;
}

void configure(const std::string &line, std::vector<std::pair<std::string, int>> boxes[])
{
	size_t pos = 0;
	size_t startPos = 0;
	size_t endPos = -1;
	bool done = false;
	
	pos = line.find_first_of("=-");
	
	while(!done)
	{
		std::string label = line.substr(startPos, pos - startPos);
		int focalLength = line[pos+1] - '0';
		unsigned char hash = calculateHash(label);

		if(line[pos] == '=')
		{
			bool found = false;
			for(int i = 0; i<(boxes[hash]).size(); i++)
			{
				if((boxes[hash]).at(i).first == label)
				{
					(boxes[hash]).at(i).second = focalLength;
					found = true;
					break;
				}
			}
			if(!found)
			{
				(boxes[hash]).push_back(std::pair<std::string,int>(label, focalLength));
			}
		}
		if(line[pos] == '-')
		{
			for(auto it = (boxes[hash]).begin(); it!=(boxes[hash]).end(); it++)
			{
				if((*it).first == label)
				{

					(boxes[hash]).erase(it);
					break;
				}
			}
		}
		startPos = line.find_first_of(",", pos);
		if(startPos == std::string::npos)
		{
			done = true;
		}
		else
		{
			pos = line.find_first_of("=-", startPos);
			startPos++;
		}
	}
}

uint64_t calculatePower(const std::vector<std::pair<std::string, int>> boxes[])
{
	uint64_t result = 0;
	for(int i=0; i<256; i++)
	{
		for(int j=0; j<(boxes[i]).size(); j++)
		{
			result += (i+1)*(j+1)*(boxes[i]).at(j).second;
		}
	}
	
	return result;
}

int main()
{	
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string line;
	std::vector<std::pair<std::string, int>> boxes[256];
	
	parseInput(line);
	
	resultA = calculateHashSum(line);
	
	configure(line, boxes);
	resultB = calculatePower(boxes);
	
	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
