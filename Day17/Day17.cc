#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct Node
{
	int x = 0;
	int y = 0;
	unsigned cost = 0;
	bool vertical = false;
};

void parseInput(std::vector<std::string> &map)
{
	std::string line;
	
	std::ifstream input("input.txt");
  if(input.is_open())
	{
		while(getline(input, line))
		{
			map.push_back(line);
		}
	}
	input.close();
}

uint64_t findPath(const std::vector<std::string> &map, int minLength, int maxLength)
{
	uint64_t result = 0;

	int goalX = map[0].size()-1;
	int goalY = map.size()-1;
	std::vector<Node> openList;
	std::unordered_set<unsigned> closedList;
	
	Node node; 
	node.vertical = false;
	openList.push_back(node);
	
	node.vertical = true;
	openList.push_back(node);
	
	while(!openList.empty())
	{
		node = openList.back();
		openList.pop_back();

		if(node.x == goalX && node.y == goalY)
		{
			result = node.cost;
			break;
		}
		closedList.emplace(((node.x+1)*10000) + ((node.y+1)*10) + node.vertical);
		
		std::vector<Node> newNodes;
				
		if(node.vertical)
		{
			for(int i=minLength; i<=maxLength && node.y-i >= 0; i++)
			{
				Node newNode = node;
				newNode.vertical = false;
				newNode.y -= i;
				for(int j=1; j<=i; j++)
				{	
					newNode.cost += map[node.y-j][node.x] - '0';
				}
				
				newNodes.push_back(newNode);
			}
			for(int i=minLength; i<=maxLength && (unsigned)node.y+i < map.size(); i++)
			{
				Node newNode = node;
				newNode.vertical = false;
				newNode.y += i;
				for(int j=1; j<=i; j++)
				{	
					newNode.cost += map[node.y+j][node.x] - '0';
				}

				newNodes.push_back(newNode);
			}
		}
		else
		{
			for(int i=minLength; i<=maxLength && node.x-i >= 0; i++)
			{
				Node newNode = node;
				newNode.vertical = true;
				newNode.x -= i;
				for(int j=1; j<=i; j++)
				{	
					newNode.cost += map[node.y][node.x-j] - '0';
				}
				
				newNodes.push_back(newNode);
			}
			for(int i=minLength; i<=maxLength && (unsigned)node.x+i < map[0].size(); i++)
			{
				Node newNode = node;
				newNode.vertical = true;
				newNode.x += i;
				for(int j=1; j<=i; j++)
				{	
					newNode.cost += map[node.y][node.x+j] - '0';
				}
				
				newNodes.push_back(newNode);
			}
		}
		
		for(auto &newNode:newNodes)
		{
			auto it = std::find_if(openList.begin(),openList.end(),[&newNode](const Node &oNode) { return newNode.x == oNode.x && newNode.y == oNode.y && newNode.vertical == oNode.vertical; });
			if(it != std::end(openList))
			{
				it->cost = (newNode.cost < it->cost) ? newNode.cost : it->cost;
			}
			else
			{
				if(closedList.count(((newNode.x+1)*10000) + ((newNode.y+1)*10) + newNode.vertical) == 0)
				{
					openList.insert(openList.begin(), newNode);
				}
			}
		}
		
		std::sort(openList.begin(), openList.end(), [](const Node &aNode, const Node &bNode) { return aNode.cost > bNode.cost;});
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::string> map;

	parseInput(map);
	
	resultA = findPath(map, 1, 3);
	resultB = findPath(map, 4, 10);
	
	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
