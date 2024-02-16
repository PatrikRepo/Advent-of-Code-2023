#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

enum class Direction 
{
	RIGHT,
	DOWN,
	LEFT,
	UP
};

struct Edge
{
	int direction = 0;
	int64_t length = 0;
	int64_t posX = 0;
	int64_t posY = 0;
	Edge(char d, int l) : direction(d), length(l){}
};

int getDirectionFromChar(const char cDirection)
{
	int direction = 0;
	
	switch(cDirection)
	{
		case 'R':
			direction = 0;
			break;
		case 'D':
			direction = 1;
			break;
		case 'L':
			direction = 2;
			break;
		case 'U':
			direction = 3;
	}
	
	return direction;
}

void parseInput(std::vector<Edge> &smallEdges, std::vector<Edge> &bigEdges)
{
	std::string line;
	
	std::ifstream input("input.txt");
  if(input.is_open())
	{
		while(getline(input, line))
		{
			size_t pos = 0;
			size_t endpos = 0;
			uint64_t l = 0;
			int d = getDirectionFromChar(line[0]);
			
			pos = line.find_first_of("0123456789");
			endpos = line.find_first_not_of("0123456789");
			l = std::stoll(line.substr(pos, endpos-pos));
			smallEdges.push_back(Edge(d,l));
			
			pos = line.find_first_of("#", endpos);
			std::string hex = line.substr(pos+1,5);
			d = line[pos+6] - '0';
			std::istringstream(hex) >> std::hex >> l;
			bigEdges.push_back(Edge(d,l));
		}
		
	}
	input.close();
}

uint64_t calculateArea(std::vector<Edge> &edges)
{
	uint64_t result = 0;
	int64_t posX = 0;
	int64_t posY = 0;
	int64_t boundaryNodes = 0;

	for(auto& edge : edges)
	{	
		edge.posX = posX;
		edge.posY = posY;
		boundaryNodes += edge.length;
		if(edge.direction == (int)Direction::UP)
		{
			posY -= edge.length;
		}
		else if(edge.direction == (int)Direction::DOWN)
		{
			posY += edge.length;
		}
		else if(edge.direction == (int)Direction::LEFT)
		{
			posX -= edge.length;
		}
		else if(edge.direction == (int)Direction::RIGHT)
		{
			posX += edge.length;
		}
	}

	uint64_t numberOfEdges = edges.size();
	for(unsigned int i=0; i<numberOfEdges; i++)
	{
		result += edges[i].posX*edges[(i+1)%numberOfEdges].posY - edges[i].posY*edges[(i+1)%numberOfEdges].posX;
	}
	result = (boundaryNodes+result)/2+1;

	return result;

}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<Edge> smallEdges;
	std::vector<Edge> bigEdges;
	
	parseInput(smallEdges, bigEdges);
	
	resultA = calculateArea(smallEdges);
	resultB = calculateArea(bigEdges);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
