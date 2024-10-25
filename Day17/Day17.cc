#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

struct Node
{
	int x = 0;
	int y = 0;
	unsigned cost = 0;
	bool vertical = false;
};

struct SortNodes
{
	bool operator()(const Node &node1, const Node &node2) const { return node1.cost < node2.cost; }
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
	std::deque<Node> openList;
	std::vector<Node> closedList;
	
	Node node; 
	node.vertical = false;
	openList.push_back(node);
	
	node.vertical = true;
	openList.push_back(node);
	
	while(!openList.empty())
	{
		node = openList.front();
		openList.pop_front();
		if(node.x == goalX && node.y == goalY)
		{
			result = node.cost;
			break;
		}
		closedList.push_back(node);
		
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
			auto it = std::find_if(openList.begin(),openList.end(),[newNode](Node &oNode) { return newNode.x == oNode.x && newNode.y == oNode.y && newNode.vertical == oNode.vertical; });
			if(it != std::end(openList))
			{
				it->cost = (newNode.cost < it->cost) ? newNode.cost : it->cost;
			}
			else
			{
				if(std::find_if(closedList.begin(),closedList.end(),[newNode](Node &cNode) { return newNode.x == cNode.x && newNode.y == cNode.y && newNode.vertical == cNode.vertical; }) == std::end(closedList))
				{
					openList.push_back(newNode);
				}
			}
		}
		
		std::sort(openList.begin(), openList.end(), SortNodes());
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
