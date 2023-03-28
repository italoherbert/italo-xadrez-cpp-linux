
#include "torre_peca_jogada.h"

#include <cstdlib>

void TorrePecaJogada::calculaJogadasPossiveis( PecaJogadaParams* params ) {
	Jogo* jogo = params->getJogo();
	JogadaLista* lista = params->getJogadas();
	int posX = params->getPosX();
	int posY = params->getPosY();
	bool isComp = params->getIsComp();
	Pecas* pecas = params->getPecas();

	int x = posX - 1;
	int y = posY;
	bool fim = false;
	while( !fim && x >= 0 ) {
		fim = jogo->addJogada( lista, pecas, x, y, isComp );
		x--;
	}
	
	x = posX + 1;
	y = posY;
	fim = false;
	while( !fim && x < 8 ) {
		fim = jogo->addJogada( lista, pecas, x, y, isComp );
		x++;
	}
		
	x = posX;
	y = posY - 1;
	fim = false;
	while( !fim && y >= 0 ) {
		fim = jogo->addJogada( lista, pecas, x, y, isComp );
		y--;
	}
	
	x = posX;
	y = posY + 1;
	fim = false;
	while( !fim && y < 8 ) {
		fim = jogo->addJogada( lista, pecas, x, y, isComp );
		y++;
	}		
	
}

