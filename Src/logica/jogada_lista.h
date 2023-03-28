
#ifndef JOGADA_LISTA_H
#define JOGADA_LISTA_H

#include "jogada.h"
#include "peca.h"

class JogadaLista {
			
	private:
		Jogada* jogadas[ 200 ];
		int jogadas_tam;
			
	public:
		JogadaLista();
		~JogadaLista();
	
		void addJogada( int posX, int posY, Peca* captura, int tipo );
		void addJogada( int posX, int posY, Peca* captura );
		void addJogada( Jogada* jogada );	
		
		void deletaTodasAsJogadas();
		
		void copiaPara( JogadaLista* lista );
		
		int getTam();
		
		Jogada* getJogada( int i );		
		
};

#endif
