#include "movimento.h"

#include <cstdlib>


Movimento::Movimento( Jogada* jogada ) {
	this->jogada = jogada;
	this->mov1 = NULL;
	this->mov2 = NULL;
}

bool Movimento::isMoveu() {
	if ( mov2 != NULL )
		return mov2->isMoveu();
	
	if ( mov1 != NULL )
		return mov1->isMoveu();
	
	return false;
}

Jogada* Movimento::getJogada() {
	return jogada;
}

MovimentoSimples* Movimento::getMovimento1() {
	return this->mov1;
}

MovimentoSimples* Movimento::getMovimento2() {
	return this->mov2;
}

void Movimento::setMovimento1( MovimentoSimples* mov ) {
	this->mov1 = mov;	
}

void Movimento::setMovimento2( MovimentoSimples* mov ) {
	this->mov2 = mov;
}
		
