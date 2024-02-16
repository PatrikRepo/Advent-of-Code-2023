#include <iostream>
#include <fstream>
#include <vector>

void getNumbers(std::string &line, std::vector<uint64_t> &vector)
{
	size_t pos = 0;
	size_t endpos = 0;
	uint64_t number = 0;
	pos = line.find_first_of("0123456789");
	
	while(pos != std::string::npos)
	{
		endpos = line.find_first_not_of("0123456789", pos);
		if(endpos == std::string::npos)
		{
			endpos = line.length();
		}
		
		number = std::stol(line.substr(pos, endpos - pos));
		vector.push_back(number);
		
		pos = line.find_first_of("0123456789", endpos);

	}
}

void removeWhiteSpace(std::string &line)
{
	size_t pos = 0;
	size_t endpos = 0;
	pos = line.find_first_of(" ");
	
	while(pos != std::string::npos)
	{
		endpos = line.find_first_not_of(" ", pos);
		if(endpos == std::string::npos)
		{
			endpos = line.length();
		}
		
		line.erase(pos, endpos - pos);
		
		pos = line.find_first_of(" ");

	}
}

void parseInput(std::vector<uint64_t> &shortTimes, std::vector<uint64_t> &shortDists, std::pair<uint64_t,uint64_t> &realRecord)
{

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		std::string times;
		std::string distances;
		size_t pos = 0;
		
		getline(input, times);
		getline(input, distances);
		
		getNumbers(times, shortTimes);
		getNumbers(distances, shortDists);
		
		pos = times.find_first_of("0123456789");
		times = times.substr(pos);
		removeWhiteSpace(times);
		realRecord.first = std::stoll(times);
		
		pos = distances.find_first_of("0123456789");
		distances = distances.substr(pos);
		removeWhiteSpace(distances);
		realRecord.second = std::stoll(distances);
		
	}
	input.close();
}

uint64_t calculateMoE(std::vector<uint64_t> &vtime, std::vector<uint64_t> &vdistance)
{
	uint64_t result = 1;
	uint64_t time = 0;
	uint64_t distance = 0;
	
	for(unsigned int i=0; i<vtime.size(); i++)
	{
		time = vtime.at(i);
		distance = vdistance.at(i);

		for(unsigned int i=1; i<time; i++)
		{
			if(i*(time-i)>distance)
			{
				result = result*(((time-1)/2-i+1)*2 + (time-1)%2);

				break;
			}
		}
	}
	
	return result;
}

uint64_t calculateMoE(std::pair<uint64_t,uint64_t> &realRecord)
{
	uint64_t count = 0;
	uint64_t breakpoint = 0;
	
	for(uint64_t i=1; i<realRecord.first; i=i+10000)
	{
		if(i*(realRecord.first-i)>realRecord.second)
			{
				breakpoint = i;

				break;
			}
	}
	
	for(uint64_t i=breakpoint-10000; i<=breakpoint; i++)
	{
		if(i*(realRecord.first-i)>realRecord.second)
			{
				count = (((realRecord.first-1)/2-i+1)*2 + (realRecord.first-1)%2);

				break;
			}
	}
	
	return count;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string line;
	std::vector<uint64_t> shortTimes;
	std::vector<uint64_t> shortDists;
	std::pair<uint64_t,uint64_t> realRecord;

	parseInput(shortTimes, shortDists, realRecord);
	
	resultA = calculateMoE(shortTimes, shortDists);
	resultB = calculateMoE(realRecord);
	
	std::cout << "result A: " << resultA << std::endl;
	std::cout << "result B: " << resultB << std::endl;
	
	return 0;
}
