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

		std::pair<int,int> get_times(){
			
			std::pair <int, int> fail (-1, -1);
			if (TIMES.size() == 0){
				return fail;
			}
			return TIMES[0];
		}

		void remove_time(){
			TIMES.erase(TIMES.begin());
		}

		//This adds to the time of all the starting times when defragmentation happens and everything needs to get pushed back
		void add_arrtime(int delay){
			for (unsigned int i = 0; i < TIMES.size(); i++){
				TIMES[i].first += delay;
			}
		}

		int num_proc(){
			return (int)TIMES.size();
		}
		
	private:
		char PROC_ID;
		int MEM_FRAMES;
		std::vector<std::pair<int,int> > TIMES;
};
