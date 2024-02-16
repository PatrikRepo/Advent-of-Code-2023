#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

struct Tables
{
	std::vector<std::pair<uint64_t, uint64_t>> seeds;
	std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> seedToSoil;
	std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> soilToFert;
	std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> fertToWater;
	std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> waterToLight;
	std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> lightToTemp;
	std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> tempToHum;
	std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> humToLoc;
};

const std::string digits = "0123456789";

void readData(std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> &dataTable, std::string &line)
{
	uint64_t dest = 0;
	uint64_t source = 0;
	uint64_t range = 0;
	size_t pos = 0;
	size_t endpos = 0;
	
	pos = line.find_first_of(digits);
	endpos = line.find_first_not_of(digits, pos);
	dest = std::stoll(line.substr(pos, endpos - pos));
	
	pos = line.find_first_of(digits, endpos);
	endpos = line.find_first_not_of(digits, pos);
	source = std::stoll(line.substr(pos, endpos - pos));
	
	pos = line.find_first_of(digits, endpos);
	range = std::stoll(line.substr(pos));
	
	dataTable.push_back(std::tuple<uint64_t,uint64_t,uint64_t>(source, range, dest));
}

void readInput(Tables &tables)
{
	std::string line;
	size_t pos = 0;
	size_t endpos = 0;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		pos = line.find_first_of(digits);
		while(pos != std::string::npos)
		{
			uint64_t seed = 0;
			uint64_t range = 0;
			
			endpos = line.find_first_not_of(digits, pos);
			
			seed = std::stoll(line.substr(pos, endpos - pos));
			
			pos = line.find_first_of(digits, endpos);
			endpos = line.find_first_not_of(digits, pos);
			
			if(endpos == std::string::npos)
			{
				endpos = line.length();
			}
			
			range = std::stoll(line.substr(pos, endpos - pos));
			
			tables.seeds.push_back(std::pair<uint64_t, uint64_t>(seed, range));
			pos = line.find_first_of(digits, endpos);
		}
	}
	
	getline(input, line);
	getline(input, line);
	
	getline(input, line);
	do
	{
		readData(tables.seedToSoil, line);
		getline(input, line);
	} while(line != "");
	
	getline(input, line);
	
	getline(input, line);
	do
	{
		readData(tables.soilToFert, line);
		getline(input, line);
	} while(line != "");
	
	getline(input, line);
	
	getline(input, line);
	do
	{
		readData(tables.fertToWater, line);
		getline(input, line);
	} while(line != "");
	
	getline(input, line);
	
	getline(input, line);
	do
	{
		readData(tables.waterToLight, line);
		getline(input, line);
	} while(line != "");
	
	getline(input, line);
	
	getline(input, line);
	do
	{
		readData(tables.lightToTemp, line);
		getline(input, line);
	} while(line != "");
	
	getline(input, line);
	
	getline(input, line);
	do
	{
		readData(tables.tempToHum, line);
		getline(input, line);
	} while(line != "");
	
	getline(input, line);
	
	getline(input, line);
	do
	{
		readData(tables.humToLoc, line);
		getline(input, line);
	} while(line != "");
	
	input.close();
}

uint64_t convertData(uint64_t data, const std::vector<std::tuple<uint64_t,uint64_t,uint64_t>> &dataTable)
{
	uint64_t start = 0;
	uint64_t end = 0;
	uint64_t offset = 0;
	
	for(auto it = dataTable.begin(); it != dataTable.end(); it++)
	{
		start = std::get<0>(*it);
		end = start + std::get<1>(*it);
		offset = std::get<2>(*it);
		
		if(data >= start && data <= end)
		{
			data = offset + data - start;
			break;
		}
	}
	
	return data;
}

uint64_t calculateLocation(uint64_t data, const Tables &tables)
{
	data = convertData(data, tables.seedToSoil);
	data = convertData(data, tables.soilToFert);
	data = convertData(data, tables.fertToWater);
	data = convertData(data, tables.waterToLight);
	data = convertData(data, tables.lightToTemp);
	data = convertData(data, tables.tempToHum);
	data = convertData(data, tables.humToLoc);
	
	return data;
}

uint64_t lowestLocation(const Tables &tables)
{
	uint64_t result = UINT64_MAX;
	uint64_t newResult = 0;
	
	for(auto it = tables.seeds.begin(); it != tables.seeds.end(); it++)
	{
		newResult = calculateLocation(it->first, tables);
		if(newResult < result)
		{
			result = newResult;
		}
		newResult = calculateLocation(it->second, tables);
		if(newResult < result)
		{
			result = newResult;
		}
	}
	
	return result;
}

uint64_t firstEstimation(const Tables &tables)
{
	uint64_t result = UINT64_MAX;
	uint64_t newResult = 0;
	uint64_t seedResult = 0;
	uint64_t seed = 0;
	uint64_t range = 0;
	
	for(auto it = tables.seeds.begin(); it != tables.seeds.end(); it++)
	{
		seed = (*it).first;
		range = (*it).second;
		for(uint64_t i=0; i<range; i=i+100000)
		{
			newResult = calculateLocation(seed+i, tables);
			if(newResult < result)
			{
				result = newResult;
				seedResult = seed+i;
			}
		}

	}
	
	return seedResult;
}

uint64_t finalCalculation(const uint64_t seed, const Tables &tables)
{
	uint64_t result = UINT64_MAX;
	uint64_t newResult = 0;
	
	for(int i=-100000; i<100000; i++)
	{
		newResult = calculateLocation(seed + i, tables);
		if(newResult < result)
		{
			result = newResult;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	Tables tables;
	readInput(tables);
	
	resultA = lowestLocation(tables);
	resultB = firstEstimation(tables);
	resultB = finalCalculation(resultB, tables);
	
	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	
	return 0;
}
