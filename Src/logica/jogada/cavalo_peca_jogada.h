#ifndef CAVALO_PECA_JOGADA_H
#define CAVALO_PECA_JOGADA_H

#include "../peca_jogada_params.h"

class PecaJogadaParams;

class CavaloPecaJogada {

	private:
		void addJogada( PecaJogadaParams* params, int x, int y );

	public:
		void calculaJogadasPossiveis( PecaJogadaParams* params );
		
};

#endif
