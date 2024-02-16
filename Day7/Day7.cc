#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>

void parseInput(std::pair<std::string,uint64_t> hands[])
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		int i=0;
		while(getline(input, line))
		{
			std::string hand = line.substr(0,5);
			uint64_t value = std::stoi(line.substr(6));
			hands[i] = std::make_pair(hand, value);
			i++;
		}
	}
	input.close();
}

void remapHand(std::string &hand)
{
	for(int i=0; i<5; i++)
	{
		switch(hand[i])
		{
			case 'T':
				hand[i] = 'A';
				break;
			case 'J':
				hand[i] = 'B';
				break;
			case 'Q':
				hand[i] = 'C';
				break;
			case 'K':
				hand[i] = 'D';
				break;
			case 'A':
				hand[i] = 'E';
		}
	}
}

void remapHands(std::pair<std::string,uint64_t> hands[])
{
	for(int i=0; i<1000; i++)
	{
		remapHand((hands[i].first));
	} 
}

int compareHands(const void* A, const void* B, void* data)
{
	int result = 0;
	std::unordered_map<char, int> mapA;
	std::unordered_map<char, int> mapB;
	int rankA = 0;
	int rankB = 0;
	
	std::pair<std::string, uint64_t>* dataArray = (std::pair<std::string, uint64_t>*) data;
	int a = * (int *) A;
	int b = * (int *) B;
	
	std::string handA = dataArray[a].first;
	std::string handB = dataArray[b].first;	
	
	for(int i=0; i<5; i++)
	{
		mapA[handA[i]] += 1;
		mapB[handB[i]] += 1;
	}
	
	for(auto it = mapA.begin(); it != mapA.end(); it++)
	{
		if(it->second < 3)
		{
			rankA += it->second -1;
		}
		else if(it->second == 3)
		{
			rankA += it->second;
		}
		else
		{
			rankA += it->second +1;
		}
	}
	for(auto it = mapB.begin(); it != mapB.end(); it++)
	{
		if(it->second < 3)
		{
			rankB += it->second -1;
		}
		else if(it->second == 3)
		{
			rankB += it->second;
		}
		else
		{
			rankB += it->second +1;
		}
	}

	if(rankA!=rankB)
	{
		result = rankA - rankB;
	}
	else
	{
		for(int i=0; i<5; i++)
		{
			if(handA[i] != handB[i])
			{

				result = handA[i] - handB[i];
				break;
			}
		}
	}
	return result;
}

void remapHandWithJokers(std::string &hand)
{
	for(int i=0; i<5; i++)
	{
		switch(hand[i])
		{
			case 'T':
				hand[i] = 'A';
				break;
			case 'J':
				hand[i] = '0';
				break;
			case 'Q':
				hand[i] = 'C';
				break;
			case 'K':
				hand[i] = 'D';
				break;
			case 'A':
				hand[i] = 'E';
		}
	}
}

void remapHandsWithJokers(std::pair<std::string,uint64_t> hands[])
{
	for(int i=0; i<1000; i++)
	{
		remapHandWithJokers((hands[i].first));
	} 
}

int compareHandsWithJokers(const void* A, const void* B, void* data)
{
	int result = 0;
	std::unordered_map<char, int> mapA;
	std::unordered_map<char, int> mapB;
	int rankA = 0;
	int rankB = 0;
	int jokersA = 0;
	int jokersB = 0;
	
	std::pair<std::string, uint64_t>* dataArray = (std::pair<std::string, uint64_t>*) data;
	int a = * (int *) A;
	int b = * (int *) B;
	
	std::string handA = dataArray[a].first;
	std::string handB = dataArray[b].first;	
	
	for(int i=0; i<5; i++)
	{
		mapA[handA[i]] += 1;
		mapB[handB[i]] += 1;
	}
	
	for(auto it = mapA.begin(); it != mapA.end(); it++)
	{
		if(it->second < 3)
		{
			rankA += it->second -1;
		}
		else if(it->second == 3)
		{
			rankA += it->second;
		}
		else
		{
			rankA += it->second +1;
		}
	}
	for(auto it = mapB.begin(); it != mapB.end(); it++)
	{
		if(it->second < 3)
		{
			rankB += it->second -1;
		}
		else if(it->second == 3)
		{
			rankB += it->second;
		}
		else
		{
			rankB += it->second +1;
		}
	}
	
	for(int i=0; i<5; i++)
	{
		if(handA[i] == '0')
		{
			jokersA++;
		}
		if(handB[i] == '0')
		{
			jokersB++;
		}
	}
	
	if(rankA == 0)
	{
		rankA = jokersA;
	}
	else if(rankA == 1)
	{
		rankA = jokersA != 0 ? 3 : 1;
	}
	else if(rankA == 2)
	{
		if(jokersA == 2)
		{
			rankA = 5;
		}
		else if(jokersA == 1)
		{
			rankA = 4;
		}
	}
	else if(rankA == 3)
	{
		if(jokersA > 0)
		{
			rankA = 5;
		}
	}
	else if(rankA == 4)
	{
		if(jokersA > 0)
		{
			rankA = 6;
		}
	}
	else if(rankA == 5)
	{
		if(jokersA > 0)
		{
			rankA = 6;
		}
	}
	
		if(rankB == 0)
	{
		rankB = jokersB;
	}
	else if(rankB == 1)
	{
		rankB = jokersB != 0 ? 3 : 1;
	}
	else if(rankB == 2)
	{
		if(jokersB == 2)
		{
			rankB = 5;
		}
		else if(jokersB == 1)
		{
			rankB = 4;
		}
	}
	else if(rankB == 3)
	{
		if(jokersB > 0)
		{
			rankB = 5;
		}
	}
	else if(rankB == 4)
	{
		if(jokersB > 0)
		{
			rankB = 6;
		}
	}
	else if(rankB == 5)
	{
		if(jokersB > 0)
		{
			rankB = 6;
		}
	}
	
	if(rankA!=rankB)
	{
		result = rankA - rankB;
	}
	else
	{
		for(int i=0; i<5; i++)
		{
			if(handA[i] != handB[i])
			{

				result = handA[i] - handB[i];
				break;
			}
		}
	}
	return result;
}


void rankHands(std::pair<std::string,uint64_t> hands[], int indices[])
{
	qsort_r(indices, 1000, sizeof(indices[0]), &compareHands, hands);
}

void rankHandsWithJokers(std::pair<std::string,uint64_t> hands[], int indices[])
{
	qsort_r(indices, 1000, sizeof(indices[0]), &compareHandsWithJokers, hands);
}

uint64_t calculateWinnings(const std::pair<std::string,uint64_t> hands[], const int indices[])
{
	uint64_t result = 0;
	
	for(int i=0; i<1000;i++)
	{
		result+=(hands[indices[i]].second)*(i+1);
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::pair<std::string,uint64_t> hands[1000];
	std::pair<std::string,uint64_t> handsWithJokers[1000];
	
	int indices[1000];
	int indicesWithJokers[1000];
	
	for(int i=0; i<1000; i++)
	{
		indices[i] = i;
		indicesWithJokers[i] = i;
	}
	
	parseInput(hands);
	for(int i=0; i<1000; i++)
	{
		handsWithJokers[i] = hands[i];
	}

	remapHands(hands);
	rankHands(hands, indices);
	resultA = calculateWinnings(hands, indices);
	
	remapHandsWithJokers(handsWithJokers);
	rankHandsWithJokers(handsWithJokers, indicesWithJokers);
	resultB = calculateWinnings(handsWithJokers, indicesWithJokers);
	
	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	
	return 0;
}
