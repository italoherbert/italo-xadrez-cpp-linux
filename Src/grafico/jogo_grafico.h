
#ifndef JOGO_GRAFICO_H
#define JOGO_GRAFICO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../gui/grafico.h"
#include "../gui/GUI.h"
#include "../logica/jogo.h"
#include "audio_ligado_desenho.h"
#include "info_desenho.h"
#include "mensagem_desenho.h"
#include "peca_desenho.h"
#include "tabuleiro_desenho.h"

class JogoGrafico : public Grafico {
	
	private:					
		Jogo* jogo;
		GUI* gui;
		
		SDL_Surface* imagens[12];
		
		InfoDesenho* infoDesenho;
		TabuleiroDesenho* tabuleiroDesenho;		
		PecaDesenho* pecaDesenho;
		MensagemDesenho* mensagemDesenho;
		AudioLigadoDesenho* audioLigadoDesenho;
		
		void desenhaMarc( Jogo* jogo, int posX, int posY, SDL_Renderer* pintor );
		
	public:
		JogoGrafico( Jogo* jogo, GUI* gui );
		~JogoGrafico();
		
		void inicializa();
		void finaliza();
		
		void desenha( SDL_Renderer* pintor );
	
		MensagemDesenho* getMensagemDesenho();
		AudioLigadoDesenho* getAudioLigadoDesenho();
		InfoDesenho* getInfoDesenho();
};

#endif
