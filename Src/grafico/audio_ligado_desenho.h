
#ifndef AUDIO_LIGADO_H
#define AUDIO_LIGADO_H

#include <SDL2/SDL.h>

#include "../gui/GUI.h"
#include "../logica/jogo.h"

class AudioLigadoDesenho {
	
	private:
		int x;
		int y;
		int largura;
		int altura;
		
		SDL_Surface* audioLigado;
		SDL_Surface* audioDesligado;
	
	public:
		void inicializa( GUI* gui );
		void finaliza();
		
		void desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor );
	
		bool isMouseEmAudioBT( int mouseX, int mouseY );

};

#endif
