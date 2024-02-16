#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Xmas
{
	int x = 0;
	int xMin = 1;
	int xMax = 4000;
	int m = 0;
	int mMin = 1;
	int mMax = 4000;
	int a = 0;
	int aMin = 1;
	int aMax = 4000;
	int s = 0;
	int sMin = 1;
	int sMax = 4000;
	char accepted = 0;
	std::string process = "in";
	Xmas(int newx, int newm, int newa, int news): x(newx), m(newm), a(newa), s(news){}
	Xmas(){}
};

void parseInput(std::unordered_map<std::string,std::string> &map,	std::vector<Xmas> &xmasVector)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		while(line != "")
		{
			size_t pos = 0;
			pos = line.find_first_of("{");
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos+1);
			map[key] = value;
			getline(input, line);
		}

		while(getline(input, line))
		{
			size_t pos = 0;
			size_t endpos = 0;
			
			pos = line.find_first_of("0123456789");
			endpos = line.find_first_not_of("0123456789", pos);
			int x = std::stoi(line.substr(pos, endpos - pos));
			pos = line.find_first_of("0123456789",endpos);
			endpos = line.find_first_not_of("0123456789", pos);
			int m = std::stoi(line.substr(pos, endpos - pos));
			pos = line.find_first_of("0123456789",endpos);
			endpos = line.find_first_not_of("0123456789", pos);
			int a = std::stoi(line.substr(pos, endpos - pos));
			pos = line.find_first_of("0123456789",endpos);
			endpos = line.find_first_not_of("0123456789", pos);
			int s = std::stoi(line.substr(pos, endpos - pos));
			xmasVector.push_back(Xmas(x,m,a,s));
		}
	}
	input.close();
}

bool sort(Xmas &xmas, const std::string &process)
{

	bool sorted = false;
	bool done = false;
	size_t endPos = 0;
	size_t pos = 0;
	while(!done)
	{
		pos = process.find_first_of("<>",endPos);
		if(pos == std::string::npos)
		{
			done = true;
			if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
			{
				sorted = true;
				xmas.accepted = process[endPos+1];
			}
			else
			{
				pos = process.find_first_of("}", endPos);
				xmas.process = process.substr(endPos+1, pos-endPos-1);
			}
		}
		else
		{
			endPos = process.find_first_of(":",pos);
			if(process[pos] == '>')
			{
				switch(process[pos-1])
				{
					case 'x':
						if(xmas.x > std::stoi(process.substr(pos+1, endPos-pos-1)))
						{
							done = true;
							if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
							{
								sorted = true;
								xmas.accepted = process[endPos+1];
							}
							else
							{
								pos = endPos;
								endPos = process.find_first_of(",",pos);
								xmas.process = process.substr(pos+1, endPos-pos-1);
							}
						}
						else
						{
							endPos = process.find_first_of(",",endPos);
						}
						break;
					case 'm':
						if(xmas.m > std::stoi(process.substr(pos+1, endPos-pos-1)))
						{
							done = true;
							if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
							{
								sorted = true;
								xmas.accepted = process[endPos+1];
							}
							else
							{
								pos = endPos;
								endPos = process.find_first_of(",",pos);
								xmas.process = process.substr(pos+1, endPos-pos-1);
							}
						}
						else
						{
							endPos = process.find_first_of(",",endPos);
						}
						break;
					case 'a':
						if(xmas.a > std::stoi(process.substr(pos+1, endPos-pos-1)))
						{
							done = true;
							if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
							{
								sorted = true;
								xmas.accepted = process[endPos+1];
							}
							else
							{
								pos = endPos;
								endPos = process.find_first_of(",",pos);
								xmas.process = process.substr(pos+1, endPos-pos-1);
							}
						}
						else
						{
							endPos = process.find_first_of(",",endPos);
						}
						break;
					case 's':
						if(xmas.s > std::stoi(process.substr(pos+1, endPos-pos-1)))
						{
							done = true;
							if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
							{
								sorted = true;
								xmas.accepted = process[endPos+1];
							}
							else
							{
								pos = endPos;
								endPos = process.find_first_of(",",pos);
								xmas.process = process.substr(pos+1, endPos-pos-1);
							}
						}
						else
						{
							endPos = process.find_first_of(",",endPos);
						}
				}
			}
			else if(process[pos] == '<')
			{
				switch(process[pos-1])
				{
					case 'x':
						if(xmas.x < std::stoi(process.substr(pos+1, endPos-pos-1)))
						{
							done = true;
							if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
							{
								sorted = true;
								xmas.accepted = process[endPos+1];
							}
							else
							{
								pos = endPos;
								endPos = process.find_first_of(",",pos);
								xmas.process = process.substr(pos+1, endPos-pos-1);
							}
						}
						else
						{
							endPos = process.find_first_of(",",endPos);
						}
						break;
					case 'm':
						if(xmas.m < std::stoi(process.substr(pos+1, endPos-pos-1)))
						{
							done = true;
							if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
							{
								sorted = true;
								xmas.accepted = process[endPos+1];
							}
							else
							{
								pos = endPos;
								endPos = process.find_first_of(",",pos);
								xmas.process = process.substr(pos+1, endPos-pos-1);
							}
						}
						else
						{
							endPos = process.find_first_of(",",endPos);
						}
						break;
					case 'a':
						if(xmas.a < std::stoi(process.substr(pos+1, endPos-pos-1)))
						{
							done = true;
							if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
							{
								sorted = true;
								xmas.accepted = process[endPos+1];
							}
							else
							{
								pos = endPos;
								endPos = process.find_first_of(",",pos);
								xmas.process = process.substr(pos+1, endPos-pos-1);
							}
						}
						else
						{
							endPos = process.find_first_of(",",endPos);
						}
						break;
					case 's':
						if(xmas.s < std::stoi(process.substr(pos+1, endPos-pos-1)))
						{
							done = true;
							if(process[endPos+1] == 'A' || process[endPos+1] == 'R')
							{
								sorted = true;
								xmas.accepted = process[endPos+1];
							}
							else
							{
								pos = endPos;
								endPos = process.find_first_of(",",pos);
								xmas.process = process.substr(pos+1, endPos-pos-1);
							}
						}
						else
						{
							endPos = process.find_first_of(",",endPos);
						}
				}
			}
		}
	}
	return sorted;
}


uint64_t calculateXmas(std::vector<Xmas> &xmasVector, std::unordered_map<std::string,std::string> &map)
{
	uint64_t result = 0;
	
	for(auto it=xmasVector.begin(); it!=xmasVector.end(); it++)
	{		
		while(!sort(*it, map[it->process]))
		{
			;
		}
		if(it->accepted == 'A')
		{
			result += it->x + it->m + it->a + it->s;
		}
	}
	
	return result;
}

uint64_t calculateXmasRange(Xmas &xmas, std::unordered_map<std::string,std::string> &map)
{
	uint64_t result = 0;
	std::vector<std::string> branches;	
	std::string process = map[xmas.process];
	size_t pos = 0;
	size_t endpos = 0;

	while(pos != std::string::npos)
	{
		endpos = process.find_first_of(",}",pos);
		std::string line = process.substr(pos, endpos-pos);
		branches.push_back(line);
		pos = process.find_first_not_of(",}",endpos);
	}

	for(auto it=branches.begin(); it!=branches.end(); it++)
	{		
		pos = 0;
		endpos = 0;
		
		pos = it->find_first_of("<>");
		if(pos == std::string::npos)
		{
			if((*it) == "A")
			{
				uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
				temp = temp*(xmas.aMax-xmas.aMin +1);
				temp = temp*(xmas.sMax-xmas.sMin +1);
				result+=temp;
			}
			else if((*it) != "R")
			{
				xmas.process = (*it);
				result += calculateXmasRange(xmas, map);
			}
		}
		else
		{
			endpos = it->find_first_of(":",pos);
			int compValue = std::stoi(it->substr(pos+1, endpos-pos-1));
			if((*it)[pos] == '>')
			{
				switch((*it)[pos-1])
				{
					case 'x':
						if(xmas.xMin <= compValue && xmas.xMax > compValue)
						{
							Xmas newXmas = xmas;
							newXmas.xMin = compValue+1;
							xmas.xMax = compValue;
							newXmas.process = it->substr(endpos+1);
							if(newXmas.process == "A")
							{
								uint64_t temp = (newXmas.xMax-newXmas.xMin +1)*(newXmas.mMax-newXmas.mMin +1);
								temp = temp*(newXmas.aMax-newXmas.aMin +1);
								temp = temp*(newXmas.sMax-newXmas.sMin +1);
								result+=temp;
							}
							else if(newXmas.process != "R")
							{
								result += calculateXmasRange(newXmas, map);
							}
						}
						else if(xmas.xMin > compValue)
						{
							xmas.process = it->substr(endpos+1);
							if(xmas.process == "A")
							{
								uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
								temp = temp*(xmas.aMax-xmas.aMin +1);
								temp = temp*(xmas.sMax-xmas.sMin +1);
								result+=temp;
							}
							else if(xmas.process != "R")
							{
								result += calculateXmasRange(xmas, map);
							}
							it=branches.end()-1;
						}
						break;
					case 'm':
						if(xmas.mMin <= compValue && xmas.mMax > compValue)
						{
							Xmas newXmas = xmas;
							newXmas.mMin = compValue+1;
							xmas.mMax = compValue;

							newXmas.process = it->substr(endpos+1);
							if(newXmas.process == "A")
							{
								uint64_t temp = (newXmas.xMax-newXmas.xMin +1)*(newXmas.mMax-newXmas.mMin +1);
								temp = temp*(newXmas.aMax-newXmas.aMin +1);
								temp = temp*(newXmas.sMax-newXmas.sMin +1);
								result+=temp;
							}
							else if(newXmas.process != "R")
							{
								result += calculateXmasRange(newXmas, map);
							}
						}
						else if(xmas.mMin > compValue)
						{
							xmas.process = it->substr(endpos+1);
							if(xmas.process == "A")
							{
								uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
								temp = temp*(xmas.aMax-xmas.aMin +1);
								temp = temp*(xmas.sMax-xmas.sMin +1);
								result+=temp;
							}
							else if(xmas.process != "R")
							{
								result += calculateXmasRange(xmas, map);
							}
							it=branches.end()-1;
						}
						break;
					case 'a':
						if(xmas.aMin <= compValue && xmas.aMax > compValue)
						{
							Xmas newXmas = xmas;
							newXmas.aMin = compValue+1;
							xmas.aMax = compValue;
							newXmas.process = it->substr(endpos+1);
							if(newXmas.process == "A")
							{
								uint64_t temp = (newXmas.xMax-newXmas.xMin +1)*(newXmas.mMax-newXmas.mMin +1);
								temp = temp*(newXmas.aMax-newXmas.aMin +1);
								temp = temp*(newXmas.sMax-newXmas.sMin +1);
								result+=temp;
							}
							else if(newXmas.process != "R")
							{
								result += calculateXmasRange(newXmas, map);
							}
						}
						else if(xmas.aMin > compValue)
						{
							xmas.process = it->substr(endpos+1);
							if(xmas.process == "A")
							{
								uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
								temp = temp*(xmas.aMax-xmas.aMin +1);
								temp = temp*(xmas.sMax-xmas.sMin +1);
								result+=temp;
							}
							else if(xmas.process != "R")
							{
								result += calculateXmasRange(xmas, map);
							}
							it=branches.end()-1;
						}
						break;
					case 's':
						if(xmas.sMin <= compValue && xmas.sMax > compValue)
						{
							Xmas newXmas = xmas;
							newXmas.sMin = compValue+1;
							xmas.sMax = compValue;
							newXmas.process = it->substr(endpos+1);
							if(newXmas.process == "A")
							{
								uint64_t temp = (newXmas.xMax-newXmas.xMin +1)*(newXmas.mMax-newXmas.mMin +1);
								temp = temp*(newXmas.aMax-newXmas.aMin +1);
								temp = temp*(newXmas.sMax-newXmas.sMin +1);
								result+=temp;
							}
							else if(newXmas.process != "R")
							{
								result += calculateXmasRange(newXmas, map);
							}
						}
						else if(xmas.sMin > compValue)
						{
							xmas.process = it->substr(endpos+1);
							if(xmas.process == "A")
							{
								uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
								temp = temp*(xmas.aMax-xmas.aMin +1);
								temp = temp*(xmas.sMax-xmas.sMin +1);
								result+=temp;
							}
							else if(xmas.process != "R")
							{
								result += calculateXmasRange(xmas, map);
							}
							it=branches.end()-1;
						}
				}
			}
			else if((*it)[pos] == '<')
			{
				switch((*it)[pos-1])
				{
					case 'x':
						if(xmas.xMin < compValue && xmas.xMax >= compValue)
						{
							Xmas newXmas = xmas;
							newXmas.xMax = compValue-1;
							xmas.xMin = compValue;
							newXmas.process = it->substr(endpos+1);
							if(newXmas.process == "A")
							{
								uint64_t temp = (newXmas.xMax-newXmas.xMin +1)*(newXmas.mMax-newXmas.mMin +1);
								temp = temp*(newXmas.aMax-newXmas.aMin +1);
								temp = temp*(newXmas.sMax-newXmas.sMin +1);
								result+=temp;
							}
							else if(newXmas.process != "R")
							{
								result += calculateXmasRange(newXmas, map);
							}
						}
						else if(xmas.xMax < compValue)
						{
							xmas.process = it->substr(endpos+1);
							if(xmas.process == "A")
							{
								uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
								temp = temp*(xmas.aMax-xmas.aMin +1);
								temp = temp*(xmas.sMax-xmas.sMin +1);
								result+=temp;
							}
							else if(xmas.process != "R")
							{
								result += calculateXmasRange(xmas, map);
							}
							it=branches.end()-1;
						}
						break;
					case 'm':
						if(xmas.mMin < compValue && xmas.mMax >= compValue)
						{
							Xmas newXmas = xmas;
							newXmas.mMax = compValue-1;
							xmas.mMin = compValue;
							newXmas.process = it->substr(endpos+1);
							if(newXmas.process == "A")
							{
								uint64_t temp = (newXmas.xMax-newXmas.xMin +1)*(newXmas.mMax-newXmas.mMin +1);
								temp = temp*(newXmas.aMax-newXmas.aMin +1);
								temp = temp*(newXmas.sMax-newXmas.sMin +1);
								result+=temp;
							}
							else if(newXmas.process != "R")
							{
								result += calculateXmasRange(newXmas, map);
							}
						}
						else if(xmas.mMax < compValue)
						{
							xmas.process = it->substr(endpos+1);
							if(xmas.process == "A")
							{
								uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
								temp = temp*(xmas.aMax-xmas.aMin +1);
								temp = temp*(xmas.sMax-xmas.sMin +1);
								result+=temp;
							}
							else if(xmas.process != "R")
							{
								result += calculateXmasRange(xmas, map);
							}
							it=branches.end()-1;
						}
						break;
					case 'a':
						if(xmas.aMin < compValue && xmas.aMax >= compValue)
						{
							Xmas newXmas = xmas;
							newXmas.aMax = compValue-1;
							xmas.aMin = compValue;
							newXmas.process = it->substr(endpos+1);
							if(newXmas.process == "A")
							{
								uint64_t temp = (newXmas.xMax-newXmas.xMin +1)*(newXmas.mMax-newXmas.mMin +1);
								temp = temp*(newXmas.aMax-newXmas.aMin +1);
								temp = temp*(newXmas.sMax-newXmas.sMin +1);
								result+=temp;
							}
							else if(newXmas.process != "R")
							{
								result += calculateXmasRange(newXmas, map);
							}
						}
						else if(xmas.aMax < compValue)
						{
							xmas.process = it->substr(endpos+1);
							if(xmas.process == "A")
							{
								uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
								temp = temp*(xmas.aMax-xmas.aMin +1);
								temp = temp*(xmas.sMax-xmas.sMin +1);
								result+=temp;
							}
							else if(xmas.process != "R")
							{
								result += calculateXmasRange(xmas, map);
							}
							it=branches.end()-1;
						}
						break;
					case 's':
						if(xmas.sMin < compValue && xmas.sMax >= compValue)
						{
							Xmas newXmas = xmas;
							newXmas.sMax = compValue-1;
							xmas.sMin = compValue;
							newXmas.process = it->substr(endpos+1);
							if(newXmas.process == "A")
							{
								uint64_t temp = (newXmas.xMax-newXmas.xMin +1)*(newXmas.mMax-newXmas.mMin +1);
								temp = temp*(newXmas.aMax-newXmas.aMin +1);
								temp = temp*(newXmas.sMax-newXmas.sMin +1);
								result+=temp;
							}
							else if(newXmas.process != "R")
							{
								result += calculateXmasRange(newXmas, map);
							}
						}
						else if(xmas.sMax < compValue)
						{
							xmas.process = it->substr(endpos+1);
							if(xmas.process == "A")
							{
								uint64_t temp = (xmas.xMax-xmas.xMin +1)*(xmas.mMax-xmas.mMin +1);
								temp = temp*(xmas.aMax-xmas.aMin +1);
								temp = temp*(xmas.sMax-xmas.sMin +1);
								result+=temp;
							}
							else if(xmas.process != "R")
							{
								result += calculateXmasRange(xmas, map);
							}
							it=branches.end()-1;
						}
						
				}
			}			
					
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::unordered_map<std::string,std::string> map;
	std::vector<Xmas> xmasVector;
		
	parseInput(map, xmasVector);
	
	Xmas xmas;

	resultA = calculateXmas(xmasVector, map);
	resultB = calculateXmasRange(xmas, map);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
