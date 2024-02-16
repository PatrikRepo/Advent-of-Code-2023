#include <iostream>
#include <fstream>
#include <unordered_map>
#include <math.h>
#include <utility>
#include <vector>

std::pair<std::string,std::string> split(const std::string &line)
{
	size_t pos = line.find_first_of(":");
	return std::make_pair(line.substr(0,pos), line.substr(pos+1));
}

void parseInput(std::vector<std::pair<std::string,std::string>> &cards)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
  {
  	while(getline(input, line))
  	{
  		cards.push_back(split(line));
    }
  }
	
	input.close();
}

void addToHashmap(const std::string &winningNumbers, std::unordered_map<std::string, int> &winMap)
{
	size_t startPos = 0;
	size_t endPos = 0;
	std::string number;
	
	startPos = winningNumbers.find_first_of("0123456789");
	
	while(startPos != std::string::npos)
	{
		endPos = winningNumbers.find_first_not_of("0123456789", startPos);
		if(endPos == std::string::npos)
		{
			endPos = winningNumbers.length();
		}
		
		number = winningNumbers.substr(startPos, endPos - startPos);
		winMap.insert(std::make_pair<std::string, int>(std::string(number), 1));
		startPos = winningNumbers.find_first_of("0123456789", endPos);
	}
}

int checkWin(const std::string &myNumbers, const std::unordered_map<std::string, int> &winMap)
{
	int count = 0;
	size_t startPos = 0;
	size_t endPos = 0;
	std::string number;
	
	startPos = myNumbers.find_first_of("0123456789");
	
	while(startPos != std::string::npos)
	{
		endPos = myNumbers.find_first_not_of("0123456789", startPos);
		if(endPos == std::string::npos)
		{
			endPos = myNumbers.length();
		}
		
		number = myNumbers.substr(startPos, endPos - startPos);
		count += winMap.count(number);
		
		startPos = myNumbers.find_first_of("0123456789", endPos);
	}
	
	return count;
}

uint32_t calculatePoints(const int count)
{
	uint32_t result = 0;
	
	if(count != 0)
	{
		result = pow(2, count-1);
	}
	
	return result;
}

uint64_t addPoints(const std::string &line)
{
	uint64_t result = 0;
	size_t pos = 0;
	std::string winningNumbers;
	std::string myNumbers;
	int count = 0;
	std::unordered_map<std::string, int> winMap;
	
	pos = line.find_first_of("|");
	winningNumbers = line.substr(0,pos);
	myNumbers = line.substr(pos);
	
	addToHashmap(winningNumbers, winMap);
	
	count = checkWin(myNumbers, winMap); 
	
	result = calculatePoints(count);
	
	return result;
}

uint64_t calculateCardsWon(std::unordered_map<int,uint64_t> &cardsWon, const int maxCard)
{
	uint64_t result = 0;
	
	for(int i=1; i<=maxCard; i++)
	{
		result += cardsWon[i];
	}
	
	return result;
}

void processCard(const std::pair<std::string,std::string> &card, std::unordered_map<int,uint64_t> &cardsWon)
{
	size_t pos = 0;
	std::string winningNumbers;
	std::string myNumbers;
	int count = 0;
	std::unordered_map<std::string, int> winMap;
	int cardNumber = 0;
	
	pos = (card.first).find_first_of("0123456789");
	cardNumber = std::stoi((card.first).substr(pos));
	cardsWon[cardNumber] = cardsWon[cardNumber] + 1;
	
	pos = (card.second).find_first_of("|");
	winningNumbers = (card.second).substr(0,pos);
	myNumbers = (card.second).substr(pos);
	
	addToHashmap(winningNumbers, winMap);
	
	count = checkWin(myNumbers, winMap); 
	for(int i=1; i<=count; i++)
	{
		cardsWon[cardNumber+i] += cardsWon[cardNumber];
	}

}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::pair<std::string,std::string>> cards;
	std::unordered_map<int, uint64_t> cardsWon;
	
	parseInput(cards);
	

	for(auto it=cards.begin(); it!=cards.end(); it++)
  {
  	resultA += addPoints(it->second);
  	processCard(*it, cardsWon);
  }
	
	resultB = calculateCardsWon(cardsWon,cards.size());
	
	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << '\n';
	return 0;
}
