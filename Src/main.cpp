
#include "sistema.h"

#include <SDL2/SDL.h>
#include <thread>

Sistema * sistema = new Sistema();

void execJogo( void* id ) {
	sistema->execJogo( id );
}

int main(int argc, char** argv) {
	std::thread( execJogo, (void*)"Thread 0" ).detach();

	sistema->execGUI();

	return 0;
}
