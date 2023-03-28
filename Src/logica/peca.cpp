#include "peca.h"

#include "jogo.h"

#include <cstdlib>

Peca::Peca( bool deComp, int tipo, int posX, int posY ) {
	this->deComp = deComp;
	this->posX = posX;
	this->posY = posY;
	this->tipo = tipo;	
	this->animPosX = 0;
	this->animPosY = 0;
	this->removida = false;	
	this->moveuContador = 0;
	this->jogadaCont = 0;
	this->ehPeaoNoInicio = ( tipo == Jogo::PEAO );
}

Peca* Peca::nova() {
	Peca* p = new Peca( deComp, tipo, posX, posY );	
	p->setRemovida( removida );
	p->setMoveuContador( moveuContador );
	p->setAnimPosX( animPosX );
	p->setAnimPosY( animPosY );

	p->jogadaCont = jogadaCont;
	return p;
}

void Peca::incJogadaCont() {
	jogadaCont++;
}

int Peca::getJogadaCont() {
	return jogadaCont;
}

bool Peca::isPeaoNoInicio() {
	return ehPeaoNoInicio;
}

bool Peca::isIgual( Peca* peca ) {
	if ( peca == NULL )
		return false;	
	return posX == peca->getPosX() && posY == peca->getPosY();
}

int Peca::getPosX() {
	return posX;
}

int Peca::getPosY() {
	return posY;
}

int Peca::getAnimPosX() {
	return animPosX;
}

int Peca::getAnimPosY() {
	return animPosY;
}

int Peca::getTipo() {
	return tipo;
}

bool Peca::isRemovida() {
	return removida;
}

int Peca::getMoveuContador() {
	return moveuContador;
}

bool Peca::isDeComp() {
	return deComp;
}

void Peca::setPosX( int posX ) {
	this->posX = posX;
}

void Peca::setPosY( int posY ) {
	this->posY = posY;	
}

void Peca::setAnimPosX( int posX ) {
	this->animPosX = posX;
}

void Peca::setAnimPosY( int posY ) {
	this->animPosY = posY;
}

void Peca::setTipo( int tipo ) {
	this->tipo = tipo;
}

void Peca::setRemovida( bool removida ) {
	this->removida = removida;
}

void Peca::setMoveuContador( int cont ) {
	this->moveuContador = cont;
}
