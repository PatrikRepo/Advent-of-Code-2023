#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>

enum class Direction 
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};
	

struct Node
{
	unsigned int direction = 0;
	unsigned int posX = 0;
	unsigned int posY = 0;
	uint32_t cost = 0;
	unsigned int directionCount = 0;
	void setDirection(Direction newDirection)
	{
		direction = (unsigned int)newDirection;
	}
	int turnRight()
	{
		return (direction+1)%4;
	}
	int turnLeft()
	{
		return (direction+3)%4;
	}
};

struct orderNodes
{
	bool operator()(const Node node1, const Node node2) const { return node1.cost > node2.cost;}
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

void updatePos(Node &node, const int steps)
	{
		switch(node.direction)
		{
			case (int)Direction::UP:
				node.posY = node.posY-steps;
				break;
			case (int)Direction::RIGHT:
				node.posX = node.posX+steps;
				break;
			case (int)Direction::DOWN:
				node.posY = node.posY+steps;
				break;
			case (int)Direction::LEFT:
				node.posX = node.posX-steps;
		}
	}

bool checkIfNodeIsAllowed(const Node &node, const std::vector<std::string> &map)
{
	bool result = false;
	if(node.posX >= 0 && node.posX < map[0].length() && node.posY >= 0 && node.posY < map.size())
	{
		result = true;
	}
	return result;
}

void findNeighbors(Node &node, std::vector<Node> &neighbors, const std::vector<std::string> &map, const unsigned int minLength, const unsigned int maxLength)
{
	Node newNode;
	if(node.directionCount < maxLength)
	{
		newNode = node;
		updatePos(newNode, 1);
		if(checkIfNodeIsAllowed(newNode, map))
		{
			newNode.directionCount = node.directionCount+1;
			newNode.cost = node.cost + map[newNode.posY][newNode.posX] - '0';
			neighbors.push_back(newNode);
		}
	}
	
	newNode = node;
	newNode.direction = node.turnRight();
	updatePos(newNode, minLength);
	if(checkIfNodeIsAllowed(newNode, map))
	{
		newNode.directionCount = minLength;
		
		newNode.cost = node.cost;
		for(unsigned int i=1; i<=newNode.posX-node.posX; i++)
		{
			newNode.cost += map[node.posY][node.posX + i] - '0';
		} 
		for(unsigned int i=0; i<node.posX-newNode.posX; i++)
		{
			newNode.cost += map[newNode.posY][newNode.posX+i] - '0';
		} 
		for(unsigned int i=1; i<=newNode.posY-node.posY; i++)
		{
			newNode.cost += map[node.posY+i][node.posX] - '0';
		} 
		for(unsigned int i=0; i<node.posY-newNode.posY; i++)
		{
			newNode.cost += map[newNode.posY+i][newNode.posX] - '0';
		} 
		neighbors.push_back(newNode);
	}

	newNode = node;
	newNode.direction = node.turnLeft();
	updatePos(newNode, minLength);
	if(checkIfNodeIsAllowed(newNode, map))
	{
		newNode.directionCount = minLength;
		
		newNode.cost = node.cost;
		for(unsigned int i=1; i<=newNode.posX-node.posX; i++)
		{
			newNode.cost += map[node.posY][node.posX + i] - '0';
		} 
		for(unsigned int i=0; i<node.posX-newNode.posX; i++)
		{
			newNode.cost += map[newNode.posY][newNode.posX+i] - '0';
		} 
		for(unsigned int i=1; i<=newNode.posY-node.posY; i++)
		{
			newNode.cost += map[node.posY+i][node.posX] - '0';
		} 
		for(unsigned int i=0; i<node.posY-newNode.posY; i++)
		{
			newNode.cost += map[newNode.posY+i][newNode.posX] - '0';
		} 
		neighbors.push_back(newNode);
	}
}

int walk(std::priority_queue<Node, std::vector<Node>, orderNodes> &queue, const std::vector<std::string> &map, const unsigned int minLength, const unsigned int maxLength)
{
	bool done = false;
	unsigned int result = 0;
	std::vector<Node> calculatedNodes;
	while(!done)
	{

		std::vector<Node> neighbors;
		
		Node node = queue.top();
		queue.pop();

		if(node.posY == map.size()-1 && node.posX == map[0].length()-1)
		{
			done = true;
			result = node.cost;
			break;
		}

		bool calculated = false;
		for(auto it=calculatedNodes.begin(); it!=calculatedNodes.end(); it++)
		{
			if(node.posX == it->posX && node.posY == it->posY && node.direction == it->direction && node.directionCount >= it->directionCount)
			{
				calculated = true;
				break;
			}
		}
		if(!calculated)
		{
			calculatedNodes.push_back(node);
			findNeighbors(node, neighbors, map, minLength, maxLength);

			for(auto it=neighbors.begin(); it!=neighbors.end(); it++)
			{
				queue.push(*it);
			}
		}
		if(queue.empty())
		{
			done=true;
		}
	}
	return result;
}

uint64_t findPath(const std::vector<std::string> &map, const unsigned int minLength, const unsigned int maxLength)
{
	uint64_t result = 0;

	std::priority_queue<Node, std::vector<Node>, orderNodes> queue;
	
	Node node; 
	
	node.setDirection(Direction::RIGHT);
	node.directionCount = minLength;
	for(unsigned int i=1; i<=minLength; i++)
	{
		node.cost += map[0][i] - '0';
	}
	node.posX = minLength;
	queue.push(node);

	node.setDirection(Direction::DOWN);
	node.posX = 0;
	node.posY = minLength;
	node.cost = 0;
	for(unsigned int i=1; i<=minLength; i++)
	{
		node.cost += map[i][0] - '0';
	}
	queue.push(node);
	
	result = walk(queue, map, minLength, maxLength);
	
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
