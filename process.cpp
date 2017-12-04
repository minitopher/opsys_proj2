#include <cstdlib>
#include <utility>
#include <vector>

#include "process.h"

Process::Process(){

}

void Process::create_process(const char PROC, const int MEM){
	PROC_ID = PROC;
	MEM_FRAMES = MEM;
	
}

