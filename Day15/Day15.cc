#include <iostream>
#include <fstream>

uint32_t calculateHash(std::string &line)
{
	uint32_t result = 0;
	size_t pos = 0;
	size_t startPos = 0;
	bool done = false;
	

	while(!done)
	{
		pos=line.find_first_of(",", startPos);
		if(pos == std::string::npos)
		{
			pos = line.length();
			done = true;
		}
		
		uint32_t hash = 0;
		for(unsigned int i=startPos; i<pos; i++)
		{
			hash += line[i];
			hash = (hash*17)%256;
		}

		result += hash;
		startPos = pos+1;
	}
	
	return result;
}

int main()
{	
	uint32_t result = 0;
	std::string line;
	
	std::ifstream input("input.txt");
  if(input.is_open())
	{
		getline(input, line);
	}
	input.close();
	
	result = calculateHash(line);
	
	std::cout << "result: " << result << std::endl;
	
	return 0;
}
