
#ifndef MENSAGEM_DESENHO_H
#define MENSAGEM_DESENHO_H

#include <iostream>
#include <SDL2/SDL.h>

#include "../gui/GUI.h"
#include "../logica/jogo.h"

class MensagemDesenho {
	
	private:
		const int MENSAGEM_BORDA = 10;
		const int MENSAGEM_FONTE_TAM = 24;

		std::string mensagem;
	
	public:
		MensagemDesenho();
		
		void desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor );
		
		void setMensagem( std::string msg );
		void removeMensagem();
		
		bool isMensagemVazia();

};

#endif
