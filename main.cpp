#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <utility>
#include <iterator>
#include <sstream>
#include <algorithm>

#include "process.h"

//From https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string
template<typename Out>	
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

//Also from https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

//Prints the memory, make sure you tell it how large the rows are, then how many rows
void print_mem(std::vector<char> mem, int frames, int lines){
	std::string memory_block = "";
	for (int i = 0; i < frames; i++){
		memory_block += '=';
	}
	memory_block += '\n';
	for (int i = 0; i < lines; i++){
		for (int j = 0; j < frames; j++){
			memory_block += mem[i*frames + j];
		}
		memory_block += '\n';
	}
	for (int i = 0; i < frames; i++){
		memory_block += '=';
	}
	
	std::cout << memory_block << std::endl;
}

//Give it the vector, will defragment it and return how many frames were moved (how much time it takes to move it)
int defrag_mem(std::vector<char> &mem, int time){
	
	int total = 256;
	int bytes_moved = 0;
	std::vector<char> moved;

	
	int notmoved = 0;
	std::cout << notmoved << std::endl;
	
	while (mem[notmoved] != '.'){
		notmoved++;
	}

	for (int i = notmoved; i < total; i++){
		if (mem[i] != '.'){
			if(std::find(moved.begin(), moved.end(), mem[i]) != moved.end()) {
				
			}
			else{
				moved.push_back(mem[i]);
			}
			bytes_moved++;
		}
	}
	std::cout << "time " << time + bytes_moved << "ms: Defragmentation complete (moved " << bytes_moved << " frames: ";
	for (unsigned int i = 0; i < moved.size() - 1; i ++){
		std::cout << moved[i] << ", ";
	}
	std::cout << moved[moved.size()-1] << ")" << std::endl; 
	
	mem.erase(std::remove(mem.begin(), mem.end(), '.'), mem.end());
	
	for (int i = 0; i < 256 - (notmoved + bytes_moved); i++){
		mem.push_back('.');
	}

	
	//Returns the number of frames it took to do defragmentation, should do a print statement also here.
	return bytes_moved;
}

//Returns the total amount of freetime
int remaining_free(std::vector<char> mem){
	int count = 0;
	for (unsigned int i = 0; i < mem.size(); i++){
		if (mem[i] == '.'){
			count++;
		}
	}

	return count;
}

void remove_proc(std::vector<char> &mem, char proc){
	for (unsigned int i = 0; i < mem.size(); i++){
		if (mem[i] == proc){
			mem[i] = '.';
		}
	}
}

bool check_location(std::vector<char> mem, int start, int len){
	int space = 0;
	//std::cout << start << "	" << len << std::endl;
	if (start+len > (int)mem.size()){
		return false;
		
	}
	else{
		space = start+len;
	}
	for (int i = start; i < space; i++){
		if (mem[i] != '.'){
				return false;
		} 
	}
	return true;
}

//THIS FINDS SMALLEST PARTITION IN THE MEMORY THAT CAN FIT SIZE, IF TIE, THE ONE CLOSER TO THE TOP
int smallest_partition(std::vector<char> mem, int size){
	std::vector<std::pair<int, int> > empty_partitions;
	std::pair<int,int> smallest(-1,-1);

	
	for (unsigned int i = 0; i < mem.size(); i++){
		int start = 0;
		int len = 0;
		std::pair<int,int> temp;
		if (mem[i] == '.'){
			start = i;
		}
		while (mem[i] == '.'){
			len++;
			i++;
		}
		
		temp.first = start;
		temp.second = len;
		empty_partitions.push_back(temp);
		
	}

	for (unsigned int i = 0; i < empty_partitions.size(); i++){
		if (empty_partitions[i].second){
			if (empty_partitions[i].second > size){
				if (smallest.first == -1){
					smallest = empty_partitions[i];
				}
				else if (empty_partitions[i].second < smallest.second){
					smallest = empty_partitions[i];
				}
			}
			else if(empty_partitions[i].second == size){
				return empty_partitions[i].first;
			}
		}
	}
	
	return 5;
}


void next_fit(std::vector<char> mem, std::vector<Process> processes){
	bool done = false;
	int time = 0;
	while(done == false){
		for(unsigned int i = 0; i < processes.size(); i++){
			//std::cout << processes[i].get_name() << std::endl;
		}
		time += 1;
		//if(processes[0] ){
			done = true;
		//}
	}
	
}

void best_fit(std::vector<char > mem, std::vector<Process> processes){
	//TODO: Make a function that makes this easy to do, should just make a list of all available spaces
	
}

void first_fit(std::vector<char> mem, std::vector<Process> processes){
	//I'll do this one -Casey
	
	int time = 0;
	//int space = mem.size();
	std::vector<Process> queue;


	std::cout << "time " << time << "ms: Simulator started (Contiguous -- Next-Fit)" << std::endl;
	while (processes.size() != 0){
		
		//THIS FUNCTION CHECKS TO SEE IF ANYTHING NEEDS TO BE REMOVED
		for (unsigned int i = 0; i < processes.size(); i++){
			std::pair<int, int> proc_hold = processes[i].get_times();
			//std::cout << proc_hold.first << "	" << proc_hold.second << std::endl;
			if (proc_hold.first != -1 && time == proc_hold.first + proc_hold.second){
				//std::cout << proc_hold.first+proc_hold.second << std::endl;
				remove_proc(mem, processes[i].get_name());
				std::cout << "time " << time << "ms: Process " << processes[i].get_name() << " removed:" << std::endl;
				print_mem(mem, 32, 8);
				processes[i].remove_time();

			} 
			else if (proc_hold.first == -1){
				//no more processes to do, remove this
				processes.erase(processes.begin() + i);
			}
		}

		//THIS CHECKS TO SEE IF ANYTHING NEEDS TO BE ADDED / DEFRAGMENTATION
		for (unsigned int i = 0; i < processes.size(); i++){
			std::pair<int, int> proc_hold = processes[i].get_times();
			//THIS MEANS THAT SOMETHING IS TO BE ADDED AT THIS TIME
			if (proc_hold.first == time && proc_hold.first != -1){
				std::cout << "time " << time << "ms: Process " << processes[i].get_name() << " arrived (requires " << processes[i].get_memframes() << " frames)" << std::endl;
				//Something is being added	
				int space_remaining = remaining_free(mem);

				//NOT ENOUGH SPACE, EVEN WITH DEFRAGMENTATION
				if (processes[i].get_memframes() > space_remaining){
					//TODO: Skip this process and remove it, its a useless cunt
					std::cout << "time " << time << "ms: Cannot place process " << processes[i].get_name() << " -- skipped!" << std::endl;
					print_mem(mem, 32, 8);
					processes[i].remove_time();
					//Check if that was the last process to be removed
					if (processes[i].num_proc() == 0){
						processes.erase(processes.begin() + i);
					}


				
					
				}

				//THERE IS ENOUGH SPACE
				else{
					int place_here = 0;
					bool placed = false;
					for (unsigned int j = 0; j < mem.size(); j++){
						if (mem[j] == '.'){	
							//FINDS THE FIRST PARTITION THAT IT CAN FIT IN						
							if (check_location(mem, j, processes[i].get_memframes())){
								//found a spot where it fits, since this is first fit, use this
								place_here = (int)j;
								placed = true;
								break;
							}
							else{
								while(mem[j] == '.'){
									j++;
								}
								
							}
						}
					}
					//IT WAS NOT PLACED, DEFRAG PLS
					if (!placed){
						//defragged
						int offset = 0;
						offset = defrag_mem(mem, time);
						time += offset;

						//ADDS ALL THE TIMES FOR THE ARRIVAL TIMES FOR ALL THE PROCESSES
						for (unsigned int m = 0; m < processes.size(); m++){
							processes[m].add_arrtime(offset);
						}

						int defrag_place = 0;
						while (mem[defrag_place] != '.'){
							defrag_place++;
						}
						for (int n = defrag_place; n < defrag_place + processes[i].get_memframes(); n++){
							mem[n] = processes[i].get_name();
						}
						
						print_mem(mem, 32, 8);

											
					}
					//PLACE THAT SHIT LIKE ITS HOT
					else{
						//it placed, move along
						//TODO: add the actual function you dumb fuck
						for (int k = place_here; k < place_here+processes[i].get_memframes(); k++){
							mem[k] = processes[i].get_name();
						}
						std::cout << "time " << time << " ms: Placed process " << processes[i].get_name() << ":" <<std::endl;
						print_mem(mem, 32, 8);
						
					}
				}
			}
		}
		time++;
	}
	
	std::cout << "time " << time-2 << "ms: Simulator ended (Contiguous -- First-Fit)" << std::endl;
	return;
}



int main(int argc, char* argv[]){

	std::ifstream input( argv[1] );

	//Creates the data structure to hold the bytes of memory
	std::vector<char> memory;
	for (unsigned int i = 0; i < 8; i++){
		for (unsigned int j = 0; j < 32; j++){
			memory.push_back ('.');
		}
	}

	//Test Structure

	std::vector<char> testmem;

	for (unsigned int i = 0; i < 8; i++){
		for (unsigned int j = 0; j < 32; j++){
			if (i == 5){
				testmem.push_back('A');
			}else{
				testmem.push_back('.');
			}
		}
	}
	
	//Parses the file and stores the values in a Process structure
	std::vector<Process> processes;

	std::string line;
	while ( std::getline(input, line) ){
		if (line[0] == '#' || line[0] == '\n' || line[0] == ' ' || line.size() == 0){
			continue;
		}
		else{
			//std::cout << "continues" <<std::endl;
			Process* p = new Process();;
			std::vector<std::string> temp1;							//This holds all the parts of the line
			
			temp1 = split(line, ' ');
			p->create_process(temp1[0][0], std::atoi(temp1[1].c_str()) );
			//std::cout <<"Size of line:" << temp1[0] << " -- " << temp1.size()-2 << std::endl;
			for (unsigned int i = 2; i < temp1.size(); i++){
				std::vector<std::string> temp2;
				temp2 = split(temp1[i], '/');
				std::pair<int,int> temp_pair(std::atoi(temp2[0].c_str()), std::atoi(temp2[1].c_str()));
				p->time_pushback(temp_pair);
			}
			
			processes.push_back(*p);
						
			
		}
		//std::cout << "hello" << std::endl;
	}
	//std::cout << "hello again" << std::endl;
	input.close();

	//Testing Defragmentation and printing
	//defrag_mem(testmem);
	//print_mem(testmem,32,8);
	std::vector<Process> firstfit = processes;
	
	first_fit(memory, processes);
	next_fit(memory, processes);
}

