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


void print_mem(std::vector<char> mem, int frames, int lines){
	std::string memory_block = "";
	for (int i = 0; i < frames; i++){
		memory_block += '=';
	}
	memory_block += '\n';
	for (unsigned int i = 0; i < lines; i++){
		for (unsigned int j = 0; j < frames; j++){
			memory_block += mem[i*frames + j];
		}
		memory_block += '\n';
	}
	for (int i = 0; i < frames; i++){
		memory_block += '=';
	}
	
	std::cout << memory_block << std::endl;
}

void defrag_mem(std::vector<char> &mem){
	
	//int space_removed = 0;

	int total = 256;	

	/*for (std::vector<char>::iterator it = mem.begin(); it != mem.end(); it++){
		if (*it == '.'){
			mem.erase(it);
			space_removed++;
		}
	}*/

	mem.erase(std::remove(mem.begin(), mem.end(), '.'), mem.end());

	for (int i = mem.size(); i < total; i++){
		mem.push_back('.');
	}
	
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
	
}

void first_fit(std::vector<char> mem, std::vector<Process> processes){
	//I'll do this one
	
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
				std::pair<int,int> temp_pair(std::atoi(temp2[0].c_str()), std::atoi(temp2[0].c_str()));
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

	

	next_fit(memory, processes);
}

