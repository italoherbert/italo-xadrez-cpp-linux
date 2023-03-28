
#include "jogada_roque.h"

#include <cstdlib>

JogadaRoque::JogadaRoque( int reiPosX, int reiPosY, int torrePosX, int torrePosY, Peca* captura, Peca* rei, Peca* torre ) 
				: Jogada( reiPosX, reiPosY, captura, ROQUE ) {
	this->torrePosX = torrePosX;
	this->torrePosY = torrePosY;
	this->rei = rei->nova();
	this->torre = torre->nova();
}

JogadaRoque::~JogadaRoque() {
	delete rei;
	delete torre;
}

JogadaRoque* JogadaRoque::nova() {
 	return new JogadaRoque( posX, posY, torrePosX, torrePosY, captura, rei, torre );
}

int JogadaRoque::getReiPosX() {
	return Jogada::getPosX();
}

int JogadaRoque::getReiPosY() {
	return Jogada::getPosY();
}

int JogadaRoque::getTorrePosX() {
	return torrePosX;
}

int JogadaRoque::getTorrePosY() {
	return torrePosY;
}

Peca* JogadaRoque::getRei() {
	return rei;
}

Peca* JogadaRoque::getTorre() {
	return torre;
}

void JogadaRoque::setRei( Peca* rei ) {
	this->rei = rei;
}

void JogadaRoque::setTorre( Peca* torre ) {
	this->torre = torre;
}
