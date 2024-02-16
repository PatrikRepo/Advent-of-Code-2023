#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

struct Node
{
	unsigned int id = 0;
	size_t posX = 0;
	size_t posY = 0;
	std::vector<std::pair<int,int>> edges;
	Node(unsigned int i, size_t x, size_t y) : id(i), posX(x), posY(y) {}
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

uint64_t walk(const size_t posX, const size_t posY, std::vector<std::string> map, uint64_t steps)
{
	uint64_t result = 0;
	
	if(posX == map[0].length() - 2 && posY == map.size() - 1)
	{
		result = steps;
	}
	else
	{
		std::vector<char> directions;
		
		if(map[posY][posX] == '>')
		{
			directions.push_back('R');
		}
		else if(map[posY][posX] == 'v')
		{
			directions.push_back('D');
		}
		else if(map[posY][posX] == '<')
		{
			directions.push_back('L');
		}
		else if(map[posY][posX] == '^')
		{
			directions.push_back('U');
		}
		else
		{
			if(posX+1 < map[0].length() && (map[posY][posX+1] != '#' && map[posY][posX+1] != '<' && map[posY][posX+1] != 'X'))
			{
				directions.push_back('R');
			}
			if(posX > 0 && (map[posY][posX-1] != '#' && map[posY][posX-1] != '>' && map[posY][posX-1] != 'X'))
			{
				directions.push_back('L');
			}
			if(posY+1 < map.size() && (map[posY+1][posX] != '#' && map[posY+1][posX] != '^' && map[posY+1][posX] != 'X'))
			{
				directions.push_back('D');
			}
			if(posY > 0 && (map[posY-1][posX] != '#' && map[posY-1][posX] != 'v' && map[posY-1][posX] != 'X'))
			{
				directions.push_back('U');
			}
		}
		
		map[posY][posX] = 'X';
		
		uint64_t walkResult = 0;
		for(auto direction : directions)
		{
			if(direction == 'R')
			{
				walkResult = walk(posX+1, posY, map, steps+1);

			}
			else if(direction == 'D')
			{
				walkResult = walk(posX, posY+1, map, steps+1);
			}
			else if(direction == 'L')
			{
				walkResult = walk(posX-1, posY, map, steps+1);
			}
			else if(direction == 'U')
			{
				walkResult = walk(posX, posY-1, map, steps+1);
			}
			
			if(walkResult > result)
			{
				result = walkResult;
			}
		}	
	}
	
	return result;
}


bool isNode(const size_t posX, const size_t posY, const std::vector<std::string> &map)
{
	bool result = false;
	int count = 0;
	if(posX+1 < map[0].length() && (map[posY][posX+1] != '#'))
	{
		count++;
	}
	if(posX > 0 && (map[posY][posX-1] != '#'))
	{
		count++;
	}
	if(posY+1 < map.size() && (map[posY+1][posX] != '#'))
	{
		count++;
	}
	if(posY > 0 && (map[posY-1][posX] != '#'))
	{
		count++;
	}
	if(count!=2)
	{
		result = true;
	}
	return result;
}

void findNodes(std::vector<std::string> &map, std::vector<Node> &nodes)
{
	unsigned int count = 1;
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			if(map[i][j] != '#' && isNode(j, i, map))
			{
				map[i][j] = 'N';
				nodes.push_back(Node(count, j, i));
				count++;
			}
		}
	}
}

Node * getNode(const size_t posX, const size_t posY, std::vector<Node> &nodes)
{
	for(auto it=nodes.begin(); it!=nodes.end(); it++)
	{
		if(it->posX == posX && it->posY == posY)
		{
			return &(*it);
		}
	}
	return nullptr;
}

void findEdges(const size_t posX, const size_t posY, std::vector<std::string> &map, std::vector<Node> &nodes)
{
	for(auto it=nodes.begin(); it!=nodes.end(); it++)
	{
		size_t posX = it->posX;
		size_t posY = it->posY;

		if(posX+1 < map[0].length() && (map[posY][posX+1] != '#'))
		{
			int steps = 1;
			size_t newX = posX+1;
			size_t newY = posY;
			Node* otherNode;

			while(map[newY][newX] != 'N')
			{
				map[newY][newX] = '#';
				if(map[newY-1][newX] != '#')
				{
					newY--;
				}
				else if(map[newY][newX+1] != '#')
				{
					newX++;
				}
				else if(map[newY+1][newX] != '#')
				{
					newY++;
				}
				else if(map[newY][newX-1] != '#')
				{
					newX--;
				}
				steps++;
			}
			otherNode = getNode(newX, newY, nodes);
			if(otherNode)
			{
				it->edges.push_back(std::make_pair(otherNode->id,steps));
				otherNode->edges.push_back(std::make_pair(it->id,steps));
			}
		}
		
		if(posX > 0 && (map[posY][posX-1] != '#'))
		{
			int steps = 1;
			size_t newX = posX-1;
			size_t newY = posY;
			Node* otherNode;

			while(map[newY][newX] != 'N')
			{
				map[newY][newX] = '#';
				if(map[newY+1][newX] != '#')
				{
					newY++;
				}
				else if(map[newY][newX-1] != '#')
				{
					newX--;
				}
				else if(map[newY-1][newX] != '#')
				{
					newY--;
				}
				else if(map[newY][newX+1] != '#')
				{
					newX++;
				}
				steps++;
			}
			otherNode = getNode(newX, newY, nodes);
			if(otherNode)
			{
				it->edges.push_back(std::make_pair(otherNode->id,steps));
				otherNode->edges.push_back(std::make_pair(it->id,steps));
			}
		}
		if(posY+1 < map.size() && (map[posY+1][posX] != '#'))
		{
			int steps = 1;
			size_t newX = posX;
			size_t newY = posY+1;
			Node* otherNode;

			while(map[newY][newX] != 'N')
			{
				map[newY][newX] = '#';
				
				if(map[newY][newX-1] != '#')
				{
					newX--;
				}
				else if(map[newY][newX+1] != '#')
				{
					newX++;
				}
				else if(map[newY+1][newX] != '#')
				{
					newY++;
				}
				else if(map[newY-1][newX] != '#')
				{
					newY--;
				}
				steps++;
			}
			otherNode = getNode(newX, newY, nodes);
			if(otherNode)
			{
				it->edges.push_back(std::make_pair(otherNode->id,steps));
				otherNode->edges.push_back(std::make_pair(it->id,steps));
			}
		}
		if(posY > 0 && (map[posY-1][posX] != '#'))
		{
			int steps = 1;
			size_t newX = posX;
			size_t newY = posY-1;
			Node* otherNode;

			while(map[newY][newX] != 'N')
			{
				map[newY][newX] = '#';
				if(map[newY][newX+1] != '#')
				{
					newX++;
				}
				else if(map[newY][newX-1] != '#')
				{
					newX--;
				}
				else if(map[newY-1][newX] != '#')
				{
					newY--;
				}
				else if(map[newY+1][newX] != '#')
				{
					newY++;
				}
				steps++;
			}
			otherNode = getNode(newX, newY, nodes);
			if(otherNode)
			{
				it->edges.push_back(std::make_pair(otherNode->id,steps));
				otherNode->edges.push_back(std::make_pair(it->id,steps));
			}
		}
			
	}
}

uint64_t longestPath(std::vector<Node> &nodes, std::vector<bool> traversedNodes, const int nodeId, int takenPath)
{
	uint64_t result = 0;
	uint64_t pathResult = 0;
	
	Node* nodePtr = &nodes[nodeId-1];
	traversedNodes[nodeId-1] = true;
	
	if(nodePtr->id == nodes.size())
	{
		result = takenPath;
	}
	else
	{
		for(auto it=nodePtr->edges.begin(); it!=nodePtr->edges.end(); it++)
		{
			if(!traversedNodes[it->first -1])
			{
				pathResult = longestPath(nodes, traversedNodes, it->first, it->second+takenPath);
				if(pathResult > result)
				{
					result = pathResult;
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
	std::vector<std::string> map;
	std::vector<Node> nodes;
	std::vector<bool> traversedNodes;
	
	parseInput(map);

	size_t posX = 1;
	size_t posY = 0;
	resultA = walk(posX, posY, map, 0);
	
	findNodes(map, nodes);
	findEdges(posX, posY, map, nodes);
	
	for(unsigned int i=0; i<nodes.size(); i++)
	{
		traversedNodes.push_back(false);
	}

	resultB = longestPath(nodes, traversedNodes, 1, 0);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
		
	return 0;
}
