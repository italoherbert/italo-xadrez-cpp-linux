
#include "cavalo_peca_jogada.h"

#include "../jogo.h"
#include "../peca_jogada_params.h"

#include <cstdlib>

void CavaloPecaJogada::calculaJogadasPossiveis( PecaJogadaParams* params ) {
	int posX = params->getPosX();
	int posY = params->getPosY();
		
	int x = posX - 2;
	int y = posY - 1;	
	this->addJogada( params, x, y );
		
	x = posX - 2;
	y = posY + 1;	
	this->addJogada( params, x, y );
	
	x = posX + 2;
	y = posY - 1;	
	this->addJogada( params, x, y );
	
	x = posX + 2;
	y = posY + 1;	
	this->addJogada( params, x, y );
	
	x = posX - 1;
	y = posY - 2;
	this->addJogada( params, x, y );

	x = posX + 1;
	y = posY - 2;
	this->addJogada( params, x, y );

	x = posX - 1;
	y = posY + 2;
	this->addJogada( params, x, y );

	x = posX + 1;
	y = posY + 2;
	this->addJogada( params, x, y );

}

void CavaloPecaJogada::addJogada( PecaJogadaParams* params, int x, int y ) {
	Jogo* jogo = params->getJogo();
	JogadaLista* lista = params->getJogadas();
	bool isComp = params->getIsComp();
	Pecas* pecas = params->getPecas();

	if ( jogo->isPosicaoValida( x, y ) )	
		jogo->addJogada( lista, pecas, x, y, isComp );					
}
