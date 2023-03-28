
#ifndef PECA_JOGADA_PARAMS_H
#define PECA_JOGADA_PARAMS_H

#include "jogo.h"
#include "jogada_lista.h"
#include "pecas.h"

class Jogo;

class PecaJogadaParams {
	
	private:
		Jogo* jogo;
		JogadaLista* lista;
		int posX;
		int posY;
		bool isComp;
		bool isIncluirRoque;				
		
		Pecas* pecas;
					
	public:
		PecaJogadaParams(
				Jogo* jogo,
				JogadaLista* lista,
				Pecas* pecas,
				int posX, int posY, bool isComp, bool incluirRoque );

		Jogo* getJogo();
		JogadaLista* getJogadas();
		int getPosX();
		int getPosY();
		bool getIsComp();
		bool getIsIncluirRoque();
	
		Pecas* getPecas();
	
};

#endif
