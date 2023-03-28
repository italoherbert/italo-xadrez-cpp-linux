
#include "movimentos_simples_lista.h"

#include <cstdlib>

#include "movimento_simples.h"

MovimentosSimplesLista::MovimentosSimplesLista() {
	this->tam = 0;
	this->itPos = 0;
}

void MovimentosSimplesLista::inverte( int i, int j ) {
	MovimentoSimples* aux = movs[ i ];
	movs[ i ] = movs[ j ];
	movs[ j ] = aux;
}

void MovimentosSimplesLista::limpaIterador() {
	this->itPos = 0;
}

bool MovimentosSimplesLista::temProximo() {
	return itPos < tam;
}

MovimentoSimples* MovimentosSimplesLista::proximo() {
	if ( itPos < tam )
		return movs[ itPos++ ];
	return NULL;
}

void MovimentosSimplesLista::addMov( Peca* peca, int posX1, int posY1, int posX2, int posY2 ) {
	this->addMov( new MovimentoSimples( peca, posX1, posY1, posX2, posY2 ) );
}

void MovimentosSimplesLista::addMov( MovimentoSimples* mov ) {
	movs[ tam++ ] = mov;
}

int MovimentosSimplesLista::getTam() {
	return tam;
}

int MovimentosSimplesLista::getITPos() {
	return itPos;
}
