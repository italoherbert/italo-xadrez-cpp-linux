#ifndef RAINHA_PECA_JOGADA_H
#define RAINHA_PECA_JOGADA_H

#include "bispo_peca_jogada.h"
#include "torre_peca_jogada.h"

#include "../peca_jogada_params.h"

class PecaJogadaParams;

class BispoPecaJogada;
class TorrePecaJogada;

class RainhaPecaJogada {
	
	private:
		BispoPecaJogada* bispoPJ;
		TorrePecaJogada* torrePJ;
		
	public:
		RainhaPecaJogada( TorrePecaJogada* torrePJ, BispoPecaJogada* bispoPJ );
		
		void calculaJogadasPossiveis( PecaJogadaParams* params );
			
};

#endif
