
#include "movimento_simples.h"

MovimentoSimples::MovimentoSimples( Peca* peca, int posX1, int posY1, int posX2, int posY2 ) {
	this->peca = peca;
	this->posX1 = posX1;
	this->posY1 = posY1;
	this->posX2 = posX2;
	this->posY2 = posY2;
	this->moveu = false;	
	this->raio = 0;
}

Peca* MovimentoSimples::getPeca() {
	return peca;
}

int MovimentoSimples::getPosX1() {
	return posX1;
}

int MovimentoSimples::getPosY1() {
	return posY1;
}

int MovimentoSimples::getPosX2() {
	return posX2;
}

int MovimentoSimples::getPosY2() {
	return posY2;
}

bool MovimentoSimples::isMoveu() {
	return moveu;
}

void MovimentoSimples::setMoveu( bool moveu ) {
	this->moveu = moveu;
}

int MovimentoSimples::getRaio() {
	return raio;
}

void MovimentoSimples::setRaio( int raio ) {
	this->raio = raio;
}
