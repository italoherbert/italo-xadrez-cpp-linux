
#ifndef MOVIMENTOS_SIMPLES_LISTA_H
#define MOVIMENTOS_SIMPLES_LISTA_H

#include "movimento_simples.h"

class MovimentosSimplesLista {
	
	private:
		MovimentoSimples* movs[ 10 ];
		int tam;
		int itPos;
		
	public:
		const static int N_MAX_MOVS = 10;
		
		MovimentosSimplesLista();
				
		MovimentoSimples* proximo();
		bool temProximo();
		
		void limpaIterador();
		
		void inverte( int i, int j );
		
		void addMov( Peca* peca, int posX1, int posY1, int posX2, int posY2 );
		void addMov( MovimentoSimples* mov );
		
		int getTam();
		
		int getITPos();
	
};

#endif
