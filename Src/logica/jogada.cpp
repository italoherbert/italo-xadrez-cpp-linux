#include "jogada.h"

#include <cstdlib>
#include <iostream>

Jogada::Jogada( int posX, int posY, Peca* captura, int tipo ) {
	this->posX = posX;
	this->posY = posY;
	this->captura = captura != NULL ? captura->nova() : NULL;
	this->tipo = tipo;
}

Jogada::~Jogada() {
	if ( captura != NULL )
		delete captura;
}

Jogada* Jogada::nova() {
	return new Jogada( posX, posY, captura, tipo );
}

int Jogada::getPosX() {
	return posX;
}

int Jogada::getPosY() {
	return posY;
}

int Jogada::getTipo() {
	return tipo;
}

Peca* Jogada::getCaptura() {
	return captura;
}

void Jogada::setPosX( int x ) {
	this->posX = x;
}

void Jogada::setPosY( int y ) {
	this->posY = y;
}

void Jogada::setCaptura( Peca* captura ) {
	this->captura = captura;
}

void Jogada::setTipo( int tipo ) {
	this->tipo = tipo;
}
