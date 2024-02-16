#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <numeric>

void parseInput(std::string &path, std::unordered_map<std::string,std::pair<std::string,std::string>> &map)
{
	std::string line;
	std::string key;
	std::string val1;
	std::string val2;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		path = line;
		
		getline(input, line);
		
		while(getline(input, line))
		{
			key = line.substr(0,3);
			val1 = line.substr(7,3);
			val2 = line.substr(12,3);
			map[key] = std::pair<std::string,std::string>(val1, val2);
		}
	}
	input.close();
}

uint64_t walk(const std::string &path, std::unordered_map<std::string,std::pair<std::string,std::string>> &map)
{
	int result = 0;
	int step = 0;
	int maxStep = path.length();
	std::string here = "AAA";
	while(true)
	{
		here = path[step] == 'L' ? map[here].first : map[here].second;
		step = (step+1)%maxStep;
		result++;
		if(here == "ZZZ")
		{
			break;
		}
	}
	
	return result;
} 

uint64_t ghostWalk(const std::string &path, std::unordered_map<std::string,std::pair<std::string,std::string>> &map)
{
	uint64_t result = 0;
	int step = 0;
	int maxStep = path.length();
	std::string here[] = {"AAA", "XCA", "GPA", "LFA", "PQA", "HMA"};
	uint64_t results[6];
	int found = 0;

	while(true)
	{
		for(int i=0; i<6; i++)
		{
			here[i] = path[step] == 'L' ? map[here[i]].first : map[here[i]].second;
		}

		step = (step+1)%maxStep;
		result++;

		for(int i=0; i<6; i++)
		{
			if((here[i])[2] == 'Z')
			{
				found++;
				results[i] = result;
			}
		}

		if(found==6)
		{
			break;
		}
	}
	
	result = results[0];
	for(int i=1;i<6;i++)
	{
		result = std::lcm(result,results[i]);
	}	
	return result;
} 

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string path;
	std::unordered_map<std::string,std::pair<std::string,std::string>> map;
	
	parseInput(path, map);
	
	resultA = walk(path, map);
	resultB = ghostWalk(path, map);
	
	std::cout << "result A: " << resultA << std::endl;
	std::cout << "result B: " << resultB << std::endl;
	
	return 0;
}
