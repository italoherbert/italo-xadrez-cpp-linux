
#ifndef JOGO_PECAS_H
#define JOGO_PECAS_H

#include "jogo.h"
#include "pecas.h"

class JogoPecas : public Pecas {
		
	private:
		Peca* jogadorPecas[ Jogo::N_PECAS ];
		Peca* computadorPecas[ Jogo::N_PECAS ];
		
		Jogo* jogo;
	
	public:
		JogoPecas( Jogo* jogo );
		~JogoPecas();
		
		void setPecas( Peca* jogPecas[ Jogo::N_PECAS ], Peca* compPecas[ Jogo::N_PECAS ] );
		void deleta_pecas();
	
		Peca* getJogadorPeca( int i );
		Peca* getComputadorPeca( int i );		
	
		Peca* getJogadorPeca( int posX, int posY );		
		Peca* getComputadorPeca( int posX, int posY );
	
		Peca* getPeca( int posX, int posY );
		
		Peca** getJogadorPecas();
		Peca** getComputadorPecas();
	
};

#endif
