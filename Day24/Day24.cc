#include <iostream>
#include <fstream>
#include <vector>

struct Hailstone
{
	int64_t posX = 0;
	int64_t posY = 0;
	int64_t posZ = 0;
	int vX = 0;
	int vY = 0;
	int vZ = 0;
	Hailstone(int64_t px, int64_t py, int64_t pz, int vx, int vy, int vz) : posX(px), posY(py), posZ(pz), vX(vx), vY(vy), vZ(vz) {}
};

void parseInput(std::vector<Hailstone> &stones)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			size_t pos = 0;
			size_t numPos = 0;
			pos = line.find_first_of(",");
			int64_t px = std::stoll(line.substr(numPos, pos));
			numPos = line.find_first_of("0123456789", pos);
			pos = line.find_first_of(",", numPos);
			int64_t py = std::stoll(line.substr(numPos, pos - numPos));
			numPos = line.find_first_of("0123456789", pos);
			pos = line.find_first_of("@", numPos);
			pos--;
			int64_t pz = std::stoll(line.substr(numPos, pos - numPos));
			numPos = line.find_first_of("-0123456789", pos);
			pos = line.find_first_of(",", numPos);
			int64_t vx = std::stoi(line.substr(numPos, pos - numPos));
			numPos = line.find_first_of("-0123456789", pos);
			pos = line.find_first_of(",", numPos);
			int64_t vy = std::stoi(line.substr(numPos, pos - numPos));
			numPos = line.find_first_of("-0123456789", pos);
			int64_t vz = std::stoi(line.substr(numPos));
			stones.push_back(Hailstone(px,py,pz,vx,vy,vz));
		}
	}
	input.close();
}

int main()
{
	uint64_t result = 0;
	std::vector<Hailstone> stones;
	
	for(auto stone1 = stones.begin(); stone1 != stones.end()-1; stone1++)
	{
		for(auto stone2 = stone1+1; stone2 != stones.end(); stone2++)
		{
			float det = (stone1->vX*stone2->vY) - (stone2->vX*stone1->vY);
			if(det != 0)
			{
				float time = 0;
				float time2 = 0;
				time = (stone2->vX*(stone1->posY - stone2->posY) - stone2->vY*(stone1->posX - stone2->posX))/det;
				int64_t x = stone1->posX + stone1->vX*time;
				int64_t y = stone1->posY + stone1->vY*time;
				time2 = (y - stone2->posY)/stone2->vY;
				if(time > 0 && time2 > 0 && x >= 200000000000000 && x <= 400000000000000 && y >= 200000000000000 && y <= 400000000000000)
				{
					result++;
				}
			}
		}
	}
	
	std::cout << "result: " << result << std::endl;
	return 0;
}
