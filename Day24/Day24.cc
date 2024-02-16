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

uint64_t calculateIntersections(const std::vector<Hailstone> &stones)
{
	uint64_t result = 0;
	
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
	
	return result;
}

uint64_t calculateCollisions(const std::vector<Hailstone> &stones)
{
	uint64_t result = 0;
	long double matrix[4][5];
	
	for(int i=0; i<4; i++)
	{
		matrix[i][0] = stones[i+1].posX - stones[i].posX;
		matrix[i][1] = stones[i].posY - stones[i+1].posY;
		matrix[i][2] = stones[i].vX - stones[i+1].vX;
		matrix[i][3] = stones[i+1].vY - stones[i].vY;
		matrix[i][4] = (stones[i].posY)*(stones[i].vX) - (stones[i].posX)*(stones[i].vY) + (stones[i+1].posX)*(stones[i+1].vY) - (stones[i+1].posY)*(stones[i+1].vX);
	}

	for(int i=4; i>=0; i--)
	{
		matrix[0][i] = (long double)matrix[0][i]/matrix[0][0];
	}

	for(int i=1; i<4; i++)
	{
		for(int j=4; j>=0; j--)
		{
				matrix[i][j] -= matrix[0][j]*matrix[i][0];
		}
	}
	
	for(int i=4; i>=1; i--)
	{
		matrix[1][i] = (long double)matrix[1][i]/matrix[1][1];
	}
	
	for(int i=2; i<4; i++)
	{
		for(int j=4; j>=1; j--)
		{
				matrix[i][j] -= matrix[1][j]*matrix[i][1];
		}
	}

	for(int i=4; i>=2; i--)
	{
		matrix[2][i] = (long double)matrix[2][i]/matrix[2][2];
	}
		matrix[2][2] = 1;

	for(int i=3; i<4; i++)
	{
		for(int j=4; j>=2; j--)
		{
				matrix[i][j] -= matrix[2][j]*matrix[i][2];
		}
	}


	matrix[3][4] = (long double)matrix[3][4]/matrix[3][3];

	long double x = matrix[3][4];
	long double y = matrix[2][4] - (matrix[2][3]*x);
	
	for(int i=0; i<4; i++)
	{
		matrix[i][0] = stones[i+1].posY - stones[i].posY;
		matrix[i][1] = stones[i].posZ - stones[i+1].posZ;
		matrix[i][2] = stones[i+1].vZ - stones[i].vZ;
		matrix[i][3] = stones[i].vY - stones[i+1].vY;
		matrix[i][4] = (stones[i].posZ)*(stones[i].vY) - (stones[i].posY)*(stones[i].vZ) + (stones[i+1].posY)*(stones[i+1].vZ) - (stones[i+1].posZ)*(stones[i+1].vY);
	}
	
	for(int i=4; i>=0; i--)
	{
		matrix[0][i] = (long double)matrix[0][i]/matrix[0][0];
	}

	for(int i=1; i<4; i++)
	{
		for(int j=4; j>=0; j--)
		{
				matrix[i][j] -= matrix[0][j]*matrix[i][0];
		}
	}
	
	for(int i=4; i>=1; i--)
	{
		matrix[1][i] = (long double)matrix[1][i]/matrix[1][1];
	}
	
	for(int i=2; i<4; i++)
	{
		for(int j=4; j>=1; j--)
		{
				matrix[i][j] -= matrix[1][j]*matrix[i][1];
		}
	}

	for(int i=4; i>=2; i--)
	{
		matrix[2][i] = (long double)matrix[2][i]/matrix[2][2];
	}
		matrix[2][2] = 1;

	for(int i=3; i<4; i++)
	{
		for(int j=4; j>=2; j--)
		{
				matrix[i][j] -= matrix[2][j]*matrix[i][2];
		}
	}


	matrix[3][4] = (long double)matrix[3][4]/matrix[3][3];


	long double z = matrix[3][4];

	result = x + y + z;

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<Hailstone> stones;
	
	parseInput(stones);
	
	resultA = calculateIntersections(stones);
	resultB = calculateCollisions(stones);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
