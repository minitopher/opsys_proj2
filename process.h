#include <iostream>
#include <vector>
#include <string> 
#include <utility>

class Process{
	public:
		Process();
		void create_process(char PROC, int MEM);

		void time_pushback(std::pair<int,int> newtime){
			TIMES.push_back(newtime);
		}
		
	private:
		char PROC_ID;
		int MEM_FRAMES;
		std::vector<std::pair<int,int> > TIMES;
};
