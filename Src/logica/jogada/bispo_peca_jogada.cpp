
#include "bispo_peca_jogada.h"

#include <cstdlib>

void BispoPecaJogada::calculaJogadasPossiveis( PecaJogadaParams* params ) {
	Jogo* jogo = params->getJogo();
	JogadaLista* lista = params->getJogadas();
	int posX = params->getPosX();
	int posY = params->getPosY();
	bool isComp = params->getIsComp();
	Pecas* pecas = params->getPecas();
	
	int x = posX - 1;
	int y = posY - 1;
	bool fim = false;
	while( !fim && ( x >= 0 && y >= 0 ) ) {
		fim = jogo->addJogada( lista, pecas, x, y, isComp );
		x--;
		y--;
	}
	
	x = posX + 1;
	y = posY - 1;
	fim = false;
	while( !fim && ( x < 8 && y >= 0 ) ) {
		fim = jogo->addJogada( lista, pecas, x, y, isComp );
		x++;
		y--;
	}
	
	x = posX - 1;
	y = posY + 1;
	fim = false;
	while( !fim && ( x >= 0 && y < 8 ) ) {
		fim = jogo->addJogada( lista, pecas, x, y, isComp );
		x--;
		y++;
	}
	
	x = posX + 1;
	y = posY + 1;
	fim = false;
	while( !fim && ( x < 8 && y < 8 ) ) {
		fim = jogo->addJogada( lista, pecas, x, y, isComp );
		x++;
		y++;
	}
	
}


