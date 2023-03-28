
#include "peca_jogada_params.h"

PecaJogadaParams::PecaJogadaParams( Jogo* jogo, JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp, bool isCaptura ) {
	this->jogo = jogo;
	this->lista = lista;
	this->pecas = pecas;
	this->posX = posX;
	this->posY = posY;
	this->isComp = isComp;
	this->isIncluirRoque = isCaptura;
}

Jogo* PecaJogadaParams::getJogo() {
	return jogo;
}

JogadaLista* PecaJogadaParams::getJogadas() {
	return lista;
}

int PecaJogadaParams::getPosX() {
	return posX;
}

int PecaJogadaParams::getPosY() {
	return posY;
}

bool PecaJogadaParams::getIsComp() {
	return isComp;
}

bool PecaJogadaParams::getIsIncluirRoque() {
	return isIncluirRoque;
}

Pecas* PecaJogadaParams::getPecas() {
	return pecas;
}

