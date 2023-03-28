
#ifndef GRAFICO_H
#define GRAFICO_H

#include <SDL2/SDL.h>

class Grafico {
	
	public:
		virtual ~Grafico() {}
		virtual void desenha( SDL_Renderer* pintor ) = 0;
		
};

#endif
