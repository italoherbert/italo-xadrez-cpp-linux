#ifndef ALGORITMO_GERENCIADOR_H
#define ALGORITMO_GERENCIADOR_H

#include "algoritmo.h"

#include "../logica/jogada.h"
#include "../logica/jogada_roque.h"
#include "../logica/jogo.h"
#include "../logica/peca.h"

class AlgoritmoGerenciador {

	private:
		Jogo* jogo;

		Algoritmo* minimaxAlgoritmo;

	public:
		AlgoritmoGerenciador( Jogo* jogo );
		virtual ~AlgoritmoGerenciador();

		bool calculaMelhorJogada( int* posX, int* posY, Jogada** jogada, bool isComp );

};

#endif
