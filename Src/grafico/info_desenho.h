
#ifndef PLACAR_DESENHO_H
#define PLACAR_DESENHO_H

#include "../gui/GUI.h"
#include "../logica/jogo.h"

#include <string>

class InfoDesenho {

	private:
		std::string brancasNivelRotulo = "Brancas:";
		std::string pretasNivelRotulo = "Pretas:";
		std::string vitoriasRotulo = "Vitorias:";
		std::string derrotasRotulo = "Derrotas:";

		SDL_Surface* reiPreto = nullptr;
		SDL_Surface* reiBranco = nullptr;
		SDL_Surface* reiVermelho = nullptr;

		int painelH = 0;
		int borda = 25;
		int infoEsp = 20;
		int imgInfoEsp = 10;

		int reiPecaImgDim = 36;

		int calculaPainelLargura( GUI* gui, SDL_Surface* rei, const char* info );

		int desenhaInfo(
					GUI* gui,
					SDL_Renderer* pintor,
					SDL_Surface* rei,
					const char* info,
					int x );

	public:
		InfoDesenho();
		~InfoDesenho();

		int desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor );

		int getPainelAltura();

};

#endif



