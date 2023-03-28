
#include "jogo_pecas.h"

JogoPecas::JogoPecas( Jogo* jogo ) {
	this->jogo = jogo;
}

JogoPecas::~JogoPecas() {
	jogo->deleta_pecas( jogadorPecas );
	jogo->deleta_pecas( computadorPecas );
}

void JogoPecas::deleta_pecas() {
	jogo->deleta_pecas( jogadorPecas );
	jogo->deleta_pecas( computadorPecas );
}

Peca** JogoPecas::getJogadorPecas() {
	return jogadorPecas;
}

Peca** JogoPecas::getComputadorPecas() {
	return computadorPecas;
} 

Peca* JogoPecas::getJogadorPeca( int i ) {
	return jogadorPecas[ i ];
}
		
Peca* JogoPecas::getComputadorPeca( int i ) {
	return computadorPecas[ i ];
}
	

Peca* JogoPecas::getJogadorPeca( int posX, int posY ) {
	return jogo->getPeca( jogadorPecas, posX, posY );
}
		
Peca* JogoPecas::getComputadorPeca( int posX, int posY ) {
	return jogo->getPeca( computadorPecas, posX, posY );
}
		
Peca* JogoPecas::getPeca( int posX, int posY ) {
	return jogo->getPeca( jogadorPecas, computadorPecas, posX, posY );
}

void JogoPecas::setPecas( Peca** jogPecas, Peca** compPecas )  {
	jogo->copia_pecas( jogadorPecas, computadorPecas, jogPecas, compPecas );
}

