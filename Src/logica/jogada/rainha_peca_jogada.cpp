
#include "rainha_peca_jogada.h"

RainhaPecaJogada::RainhaPecaJogada( TorrePecaJogada* torrePJ, BispoPecaJogada* bispoPJ ) {
	this->torrePJ = torrePJ;
	this->bispoPJ = bispoPJ;
}

void RainhaPecaJogada::calculaJogadasPossiveis( PecaJogadaParams* params ) {		
	torrePJ->calculaJogadasPossiveis( params );
	bispoPJ->calculaJogadasPossiveis( params );
}
