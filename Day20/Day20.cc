#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <numeric>

class EModule
{
	public: 
		std::string name;
		int state = 0;
		std::queue<std::pair<std::string,std::pair<int,std::string>>> *messageQueue;
		std::vector<std::string> recipients;
		bool calibrated = false;
		
		virtual void receiveSignal(const std::pair<int,std::string> &signal){}
		virtual ~EModule(){}
	protected:
		
		void sendMessage(const int pulse)
		{
			auto signal = std::make_pair(pulse, name);
			for(auto it=recipients.begin(); it!=recipients.end(); it++)
			{
				auto message = std::make_pair(*it,signal);
				messageQueue->push(message);
			}
		}
};

class FlipFlop : public EModule
{
	public:

		void receiveSignal(const std::pair<int, std::string> &signal) override
		{
			if(signal.first == -1)
			{
				if(!calibrated)
				{
					calibrated = true;
					sendMessage(-1);
				}
			}
			else if(signal.first == 1 || signal.first == 0)
			{
				if(signal.first == 0)
				{
					state = (state+1)%2;
					sendMessage(state);
				}
			}
		}
};

class Broadcaster : public EModule
{
		public:

		void receiveSignal(const std::pair<int, std::string> &signal) override
		{
			if(signal.first == -1)
			{
				sendMessage(-1);
			}
			else
			{
				sendMessage(0);
			}
		}
};

class Conjunction : public EModule
{
	public:
	
	std::vector<std::pair<std::string,int>> sources;
	bool state = 1;
	
		void receiveSignal(const std::pair<int, std::string> &signal) override
		{
			if(signal.first == -1)
			{	
				bool found = false;
				for(auto it=sources.begin(); it!=sources.end(); it++)
				{
					if(it->first == signal.second)
					{
						found = true;
						break;
					}
				}
				if(!found)
				{
					auto source = std::make_pair(signal.second, 0);
					sources.push_back(source);				
				}

				if(!calibrated)
				{
					calibrated = true;
					sendMessage(-1);
				}
			}
			else if(signal.first == 1 || signal.first == 0)
			{
				changeState(signal);
				sendMessage(state);
			}
		}
		
	private:
	
		void changeState(const std::pair<int, std::string> &signal)
		{
			for(auto it=sources.begin(); it!=sources.end(); it++)
			{
				if(it->first == signal.second)
				{
					it->second = signal.first;
					break;
				}
			}
			state = 0;
			for(auto it=sources.begin(); it!=sources.end(); it++)
			{
				if(it->second == 0)
				{
					state = 1;
					break;
				}
			}
		}
};

void parseInput(std::unordered_map<std::string,EModule*> &modules, std::queue<std::pair<std::string,std::pair<int,std::string>>> &messageQueue)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			switch(line[0])
			{
				case '%':
					{
						EModule* flipFlop = new FlipFlop();
						std::string name = line.substr(1,2);
						flipFlop->name = name;
						flipFlop->messageQueue = &messageQueue;
						size_t pos = line.find_first_of(",");
						std::string moduleName;
						while(pos != std::string::npos)
						{

							moduleName = line.substr(pos-2,2);
							flipFlop->recipients.push_back(moduleName);
							pos = line.find_first_of(",",pos+1);
						}
						pos = line.length();
						moduleName = line.substr(pos-2,2);
						flipFlop->recipients.push_back(moduleName);
						modules[name] = flipFlop;
						break;
					}
				case '&':
					{
						EModule* conjunction = new Conjunction();
						std::string name = line.substr(1,2);
						conjunction->name = name;
						conjunction->messageQueue = &messageQueue;
						size_t pos = line.find_first_of(",");
						std::string moduleName;
						while(pos != std::string::npos)
						{
							moduleName = line.substr(pos-2,2);
							conjunction->recipients.push_back(moduleName);
							pos = line.find_first_of(",",pos+1);
						}
						pos = line.length();
						moduleName = line.substr(pos-2,2);
						conjunction->recipients.push_back(moduleName);
						modules[name] = conjunction;
						break;
					}
				case 'b':
					{
						EModule* broadcaster = new Broadcaster();
						broadcaster->name = "broadcaster";
						broadcaster->messageQueue = &messageQueue;
						size_t pos = line.find_first_of(",");
						std::string moduleName;
						while(pos != std::string::npos)
						{
							moduleName = line.substr(pos-2,2);
							broadcaster->recipients.push_back(moduleName);
							pos = line.find_first_of(",",pos+1);
						}
						pos = line.length();
						moduleName = line.substr(pos-2,2);
						broadcaster->recipients.push_back(moduleName);
						modules["broadcaster"] = broadcaster;
					}
			}
		}
	}
	input.close();
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	uint64_t high = 0;
	uint64_t low = 0;

	std::queue<std::pair<std::string,std::pair<int,std::string>>> messageQueue;	
	std::unordered_map<std::string,EModule*> modules;
	
	parseInput(modules, messageQueue);
	
	auto signal = std::make_pair(-1, "button");
	auto message = std::make_pair("broadcaster", signal);
	messageQueue.push(message);
	while(!messageQueue.empty())
	{
		auto message = messageQueue.front();
		EModule * modulePtr = (modules[message.first]);
		if(modulePtr)
		{
			modulePtr->receiveSignal(message.second);
		}
		messageQueue.pop();
	}

	for(int i=0; i<1000; i++)
	{
		auto signal = std::make_pair(0, "button");
		auto message = std::make_pair("broadcaster", signal);
		messageQueue.push(message);
		while(!messageQueue.empty())
		{
			auto message = messageQueue.front();
			EModule * modulePtr = (modules[message.first]);
			if(modulePtr)
			{
				modulePtr->receiveSignal(message.second);
			}
			if((message.second).first == 1)
			{
				high++;
			}
			else if((message.second).first == 0)
			{
				low++;
			}
			messageQueue.pop();
		}
	}
	
	resultA = high*low;

	bool rkFound = false;
	uint32_t rkCount = 0;
	bool cdFound = false;
	uint32_t cdCount = 0;
	bool zfFound = false;
	uint32_t zfCount = 0;
	bool qxFound = false;
	uint32_t qxCount = 0;
	for(int i=1000; i<10000000; i++)
	{
		auto signal = std::make_pair(0, "button");
		auto message = std::make_pair("broadcaster", signal);
		messageQueue.push(message);
		while(!messageQueue.empty())
		{
			auto message = messageQueue.front();
			EModule * modulePtr = (modules[message.first]);
			if(modulePtr)
			{
				modulePtr->receiveSignal(message.second);
			}
			if((message.second).second == "rk" && (message.second).first == 1 && !rkFound)
			{
				rkCount = i+1;
				rkFound = true;
			}
			if((message.second).second == "cd" && (message.second).first == 1 && !cdFound)
			{
				cdCount = i+1;
				cdFound = true;
			}
			if((message.second).second == "zf" && (message.second).first == 1 && !zfFound)
			{
				zfCount = i+1;
				zfFound = true;
			}
			if((message.second).second == "qx" && (message.second).first == 1 && !qxFound)
			{
				qxCount = i+1;
				qxFound = true;
			}
			messageQueue.pop();
		}
		
		if(rkFound && cdFound && zfFound && qxFound)
		{
			resultB = std::lcm(rkCount, cdCount);
			resultB = std::lcm(resultB, zfCount);
			resultB = std::lcm(resultB, qxCount);
			break;
		}
	}
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	for(auto it=modules.begin(); it!=modules.end(); it++)
	{
		delete it->second;
	}
	return 0;
}
