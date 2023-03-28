
#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#include "jogada.h"
#include "movimento_simples.h"
#include "peca.h"

class Movimento {

	private:		
		Jogada* jogada;
		
		MovimentoSimples* mov1;
		MovimentoSimples* mov2;
				
	public:
		Movimento( Jogada* jogada );
				
		MovimentoSimples* getMovimento1();
		MovimentoSimples* getMovimento2();		
		void setMovimento1( MovimentoSimples* mov );
		void setMovimento2( MovimentoSimples* mov );

		bool isMoveu();
		
		Jogada* getJogada();
		void setJogada( Jogada* jogada );								
};

#endif
