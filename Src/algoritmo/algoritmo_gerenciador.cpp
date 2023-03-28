#include "algoritmo_gerenciador.h"

#include <iostream>

#include "algoritmo.h"

AlgoritmoGerenciador::AlgoritmoGerenciador( Jogo* jogo ) {
	this->minimaxAlgoritmo = new Algoritmo( jogo );
	this->jogo = jogo;
}

AlgoritmoGerenciador::~AlgoritmoGerenciador() {
	delete this->minimaxAlgoritmo;
}

bool AlgoritmoGerenciador::calculaMelhorJogada( int* posX, int* posY, Jogada** jogada, bool isComp ) {
	return minimaxAlgoritmo->calculaMelhorJogada( posX, posY, jogada, isComp );
}

