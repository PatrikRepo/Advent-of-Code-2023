#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Node
{
	std::string name;
	std::string parent;
	int size = 1;
};

struct Edge
{
	std::string from;
	std::string to;
	Edge(std::string fromNode, std::string toNode) : from(fromNode), to(toNode) {}
};

void parseInput(std::unordered_map<std::string, Node> &nodes, std::vector<Edge> &edges)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			size_t pos = 0;
			pos = line.find_first_of(":");
			std::string name = line.substr(0, pos);
			if(nodes.count(name) == 0)
			{
				Node node;
				node.name = name;
				node.parent = name;
				nodes.insert({name, node});
			}
			pos++;
			while(pos != std::string::npos)
			{
				std::string otherNodeName = line.substr(pos+1,3);
				if(nodes.count(otherNodeName) == 0)
				{
					Node otherNode;
					otherNode.name = otherNodeName;
					otherNode.parent = otherNodeName;
					nodes.insert({otherNodeName, otherNode});
				}
				edges.push_back(Edge(name, otherNodeName));
				pos = line.find_first_of(" ", pos+1);
			}
		}
	}
	input.close();
}

std::string findRoot(const std::string &name, std::unordered_map<std::string, Node> &nodes)
{
	std::string result;
	
	Node* nodePtr = &nodes[name];
	if(nodePtr->parent == name)
	{
		result = name;
	}
	else
	{
		result = findRoot(nodePtr->parent, nodes);
	}
	return result;
}

void join(const std::string &nodeName1, const std::string &nodeName2, std::unordered_map<std::string, Node> &nodes)
{
	Node* node1 = &nodes[nodeName1];
	Node* node2 = &nodes[nodeName2];
	
	if(node1->size > node2->size)
	{
		node1->size += node2->size;
		node2->size = 1;
		node2->parent = nodeName1;
	}
	else
	{
		node2->size += node1->size;
		node1->size = 1;
		node1->parent = nodeName2;
	}
}

uint64_t multiplyRank(const std::unordered_map<std::string, Node> &nodes)
{
	uint64_t result = 1;
	
	for(auto it=nodes.begin(); it!=nodes.end(); it++)
	{
		result *= it->second.size;
	}
	
	return result;
}

uint64_t splitGraph(const std::unordered_map<std::string, Node> &nodes, std::vector<Edge> &edges)
{
	uint64_t result = 0;
	bool done = false;
	int numberOfEdges = edges.size();
	while(!done)
	{
		int numberOfNodes = nodes.size();
		std::unordered_map<std::string, Node> newNodes = nodes;
		while(numberOfNodes > 2)
		{
			int edgeNumber = rand()%numberOfEdges;
			Edge* edge = &edges[edgeNumber];
			std::string node1 = findRoot(edge->from, newNodes);
			std::string node2 = findRoot(edge->to, newNodes);
			
			if(node1 != node2)
			{
				numberOfNodes--;
				join(node1, node2, newNodes);
			}
		}
		int edgesToCut = 0;
		for(auto it=edges.begin(); it!=edges.end(); it++)
		{
			std::string node1 = findRoot(it->from, newNodes);
			std::string node2 = findRoot(it->to, newNodes);
			if(node1 != node2)
			{
				edgesToCut++;
			}
		}
		if(edgesToCut == 3)
		{
			done = true;
			result = multiplyRank(newNodes);
		}
	}

	return result;
}

int main()
{
	uint64_t result = 0;
	std::unordered_map<std::string, Node> nodes;
	std::vector<Edge> edges;
	
	parseInput(nodes, edges);
	
	result = splitGraph(nodes, edges);
	
	std::cout << "result: " << result << std::endl;
	
	return 0;
}
