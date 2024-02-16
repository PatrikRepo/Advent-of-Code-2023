#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

struct Block
{
	int id = 0;
	int xStart = 0;
	int xEnd = 0;
	int yStart = 0;
	int yEnd = 0;
	int zStart = 0;
	int zEnd = 0;
	std::vector<int> supporting;
	std::vector<int> supported;
	void setSupporting(const int id)
	{
		bool found = false;
		for(auto it=supporting.begin(); it!=supporting.end(); it++)
		{
			if(*it == id)
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			supporting.push_back(id);
		}
	}
	void setSupported(const int id)
	{
		bool found = false;
		for(auto it=supported.begin(); it!=supported.end(); it++)
		{
			if(*it == id)
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			supported.push_back(id);
		}
	}
	void fall(std::vector<int> &falling, std::queue<int> &fallQueue)
	{
		bool fallen = false;
		for(unsigned int i=0; i<falling.size(); i++)
		{
			if(id == falling[i])
			{
				fallen = true;
				break;
			}
		}
		if(!fallen)
		{
			unsigned int fallenSupport = 0;
			for(unsigned int i=0; i<supported.size(); i++)
			{
				for(unsigned int j=0; j<falling.size(); j++)
				{
					if(supported[i] == falling[j])
					{
						fallenSupport++;
						break;
					}
				}
			}
			if(fallenSupport == supported.size())
			{
				falling.push_back(id);
				for(unsigned int i=0; i<supporting.size(); i++)
				{
					fallQueue.push(supporting[i]);
				}
			}
		}
	}
};

struct orderBlocks
{
	bool operator()(const Block* block1, const Block* block2) const { return block1->zStart > block2->zStart;}
};

void parseInput(std::vector<Block> &blocks)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		int idCounter = 1;
		size_t pos = 0;
		while(getline(input, line))
		{
			Block block;
			block.id = idCounter;
			block.xStart = line[0] - '0';
			block.yStart = line[2] - '0';
			pos = line.find_first_of("~");
			block.zStart = std::stoi(line.substr(4,pos-4));
			block.xEnd = line[pos+1] - '0';
			block.yEnd = line[pos+3] - '0';
			block.zEnd = std::stoi(line.substr(pos+5,line.length()-pos-5));
			blocks.push_back(block);
			idCounter++;
		}
	}
	input.close();
}

void brickFall(std::vector<Block> &blocks, std::priority_queue<Block*, std::vector<Block*>, orderBlocks> &queue, std::pair<int,int> map[10][10])
{
	while(!queue.empty())
	{
		Block* block = queue.top();
		int xStart = block->xStart;
		int xDiff = block->xEnd - xStart;
		int yStart = block->yStart;
		int yDiff = block->yEnd - yStart;
		int zStart = block->zStart;
		int zDiff = block->zEnd - zStart;
		int height = 0;
		
		if(xDiff != 0)
		{
			for(int i=xStart; i<=xStart+xDiff; i++)
			{
				if(height < map[yStart][i].first +1)
				{
					height = map[yStart][i].first +1;
				}
			}
			if(height != 1)
			{
				for(int i=xStart; i<=xStart+xDiff; i++)
				{
					if(map[yStart][i].first == height-1)
					{
						blocks.at(map[yStart][i].second - 1).setSupporting(block->id);
						block->setSupported(map[yStart][i].second);
					}
				}
			}
			for(int i=xStart; i<=xStart+xDiff; i++)
			{
				map[yStart][i].first = height;
				map[yStart][i].second = block->id;
			}
		}
		else if(yDiff != 0)
		{
			for(int i=yStart; i<=yStart+yDiff; i++)
			{
				if(height < map[i][xStart].first +1)
				{
					height = map[i][xStart].first +1;
				}
			}
			if(height != 1)
			{
				for(int i=yStart; i<=yStart+yDiff; i++)
				{
					if(map[i][xStart].first == height-1)
					{
						blocks.at(map[i][xStart].second - 1).setSupporting(block->id);
						block->setSupported(map[i][xStart].second);
					}
				}
			}
			for(int i=yStart; i<=yStart+yDiff; i++)
			{
				map[i][xStart].first = height;
				map[i][xStart].second = block->id;
			}
		}
		else
		{
			height = map[yStart][xStart].first +1;
			if(height!=1 && map[yStart][xStart].first == height-1)
			{
				blocks.at(map[yStart][xStart].second - 1).setSupporting(block->id);
				block->setSupported(map[yStart][xStart].second);
			}
				map[yStart][xStart].first = height + zDiff;
				map[yStart][xStart].second = block->id;
		}
		
		queue.pop();
	}
}

uint64_t removableBlocks(const std::vector<Block> &blocks)
{
	uint64_t result = 0;
	
	for(auto it=blocks.begin(); it!=blocks.end(); it++)
	{
		bool removeable = true;
		for(auto jt = (it->supporting).begin(); jt != (it->supporting).end(); jt++)
		{
			if((blocks[(*jt)-1].supported).size() == 1)
			{
				removeable = false;
				break;
			}
		}
		if(removeable)
		{
			result++;
		}
	}
	
	return result;
}

uint64_t maximizeDestruction(std::vector<Block> &blocks)
{
	uint64_t result = 0;
	
	for(auto it=blocks.begin(); it!=blocks.end(); it++)
	{
		std::queue<int> fallQueue;
		std::vector<int> falling;
		falling.push_back(it->id);
		for(auto jt = (it->supporting).begin(); jt != (it->supporting).end(); jt++)
		{
			fallQueue.push((*jt));
		}
		while(!fallQueue.empty())
		{
			int blockId = fallQueue.front();
			blocks[blockId-1].fall(falling, fallQueue);
			fallQueue.pop();
		}
		result += falling.size()-1;
	}
	
	return result;
}
int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::pair<int,int> map[10][10];
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			map[i][j].first = 0;
			map[i][j].second = 0;
		}
	}
	std::vector<Block> blocks;
	std::priority_queue<Block*, std::vector<Block*>, orderBlocks> queue;

	parseInput(blocks);
	
	for(auto it=blocks.begin(); it!=blocks.end(); it++)
	{
			queue.push(&(*it));
	}

	brickFall(blocks, queue, map);
	
	resultA = removableBlocks(blocks);
	resultB = maximizeDestruction(blocks);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
}
