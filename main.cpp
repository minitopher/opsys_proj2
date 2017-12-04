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

void print_mem(std::vector<std::vector<char> > mem, int frames, int lines){
	std::string memory_block = "";
	for (unsigned int i = 0; i < frames; i++){
		memory_block += '=';
	}
	memory_block += '\n';
	for (unsigned int i = 0; i < mem.size(); i++){
		for (unsigned int j = 0; j < mem[i].size(); j++){
			memory_block += mem[i][j];
		}
		memory_block += '\n';
	}
	for (int i = 0; i < frames; i++){
		memory_block += '=';
	}
	
	std::cout << memory_block << std::endl;
}

int main(int argc, char* argv[]){

	std::ifstream input( argv[1] );

	//Creates the data structure to hold the bytes of memory
	std::vector<std::vector<char> > memory;
	for (unsigned int i = 0; i < 8; i++){
		std::vector<char> temp;
		for (unsigned int j = 0; j < 32; j++){
			temp.push_back ('.');
		}
		memory.push_back(temp);
	}	
	
	//Parses the file and stores the values in a Process structure
	std::vector<Process> processes;

	std::string line;
	while ( std::getline(input, line) ){
		if (line[0] == '#' || line[0] == '\n' || line[0] == ' ' || line.size() == 0){
			continue;
		}
		else{
			std::cout << "continues" <<std::endl;
			Process* p = new Process();;
			std::vector<std::string> temp1;							//This holds all the parts of the line
			
			temp1 = split(line, ' ');
			p->create_process(temp1[0][0], std::atoi(temp1[1].c_str()) );
			std::cout <<"Size of line:" << temp1[0] << " -- " << temp1.size()-2 << std::endl;
			for (int i = 2; i < temp1.size(); i++){
				std::vector<std::string> temp2;
				temp2 = split(temp1[i], '/');
				std::pair<int,int> temp_pair(std::atoi(temp2[0].c_str()), std::atoi(temp2[0].c_str()));
				p->time_pushback(temp_pair);
			}
			
			processes.push_back(*p);
			

			//processes.push_back(*p);
			
			
		}
		//std::cout << "hello" << std::endl;
	}
	//std::cout << "hello again" << std::endl;
	input.close();
}

