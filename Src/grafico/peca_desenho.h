
#ifndef PECA_DESENHO_H
#define PECA_DESENHO_H

#include <SDL2/SDL.h>

#include "../gui/GUI.h"
#include "../logica/jogo.h"

class PecaDesenho {
	
	private:
		SDL_Surface* getPecaIMG( int pecaTipo, int corTipo );
		
		SDL_Surface* peaoPreto;
		SDL_Surface* peaoBranco;
		SDL_Surface* peaoVermelho;
		
		SDL_Surface* torrePreta;
		SDL_Surface* torreBranca;
		SDL_Surface* torreVermelha;
		
		SDL_Surface* cavaloPreto;
		SDL_Surface* cavaloBranco;
		SDL_Surface* cavaloVermelho;
		
		SDL_Surface* bispoPreto;
		SDL_Surface* bispoBranco;
		SDL_Surface* bispoVermelho;
		
		SDL_Surface* rainhaPreta;
		SDL_Surface* rainhaBranca;
		SDL_Surface* rainhaVermelha;
		
		SDL_Surface* reiPreto;
		SDL_Surface* reiBranco;
		SDL_Surface* reiVermelho;
	
	public:
		const static int COR_BRANCA = 1;
		const static int COR_PRETA = 2;
		const static int COR_VERMELHA = 3;
		
		void carregaIMGs();
		void liberaIMGs();
		
		void desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor, Peca* peca, int cor );
	
};

#endif
