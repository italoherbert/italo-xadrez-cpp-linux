
#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "../logica/jogada.h"
#include "../logica/jogada_roque.h"
#include "../logica/jogo.h"
#include "../logica/peca.h"

#include <vector>
#include <iostream>

using namespace std;

typedef struct MiniMaxNoLista MiniMaxNoLista;

typedef struct MiniMaxNo {
	Jogada* jogada;
	int posX;
	int posY;
	float peso;
	int nivel;
	bool terminal;
	bool venceu;
	struct MiniMaxNo* pai;
	struct MiniMaxNoLista* filhos;
}MinMaxNo;

typedef struct MiniMaxNoLista {
	MiniMaxNo* no;
	struct MiniMaxNoLista* prox;
} MiniMaxLista;

class Algoritmo {
	
	private:
		Peca* jogPecas[ Jogo::N_PECAS ];
		Peca* compPecas[ Jogo::N_PECAS ];

	protected:
		Jogo* jogo;

		MiniMaxNo* minimax( MiniMaxNo* no, bool isMaximizador, int iniNivel, int nivel, float alpha, float beta, bool isComp );

		void limpaMiniMaxArvore( MiniMaxNo** no );
		void efetuaJogadas( MiniMaxNo* no, Peca* jps[Jogo::N_PECAS], Peca* cps[Jogo::N_PECAS] );

		bool tentaDominioDoCentro( int* posX, int* posY, Jogada** jogada, Peca** jps, Peca** cps, bool isComp );
		bool sorteiaJogada( int* posX, int* posY, Jogada** jogada, Peca** jps, Peca** cps, bool isComp, PecaMov* ultMov );

		Peca* sorteiaPeca( Peca** jps, Peca** cps, bool isComp );
		Jogada* sorteiaPecaJogada( Peca* peca, Peca** jps, Peca** cps, bool isComp );

		float estadoAtualSomaPesos( Peca** jps, Peca** cps, bool isComp );
		float calculaPeso( Peca* peca );
		float calculaPeso( int tipo );

	public:
		Algoritmo( Jogo* jogo );

		virtual ~Algoritmo() {}

		bool calculaMelhorJogada( int* posX, int* posY, Jogada** jogada, bool isComp );
	
};

#endif
