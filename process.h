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
		
		char get_name(){
			return PROC_ID;
		}

		int get_memframes(){
			return MEM_FRAMES;
		}

		std::vector<std::pair<int,int> > get_times(){
			return TIMES;
		}

		void remove_time(){
			TIMES.erase(TIMES.begin());
		}	
		
	private:
		char PROC_ID;
		int MEM_FRAMES;
		std::vector<std::pair<int,int> > TIMES;
};
