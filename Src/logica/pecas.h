#ifndef PECAS_H
#define PECAS_H

#include "peca.h"

class Pecas {	

	public:
		virtual ~Pecas() {}

		virtual Peca* getJogadorPeca( int i ) = 0;
		virtual Peca* getComputadorPeca( int i ) = 0;
		
		virtual Peca* getJogadorPeca( int posX, int posY ) = 0;		
		virtual Peca* getComputadorPeca( int posX, int posY ) = 0;
	
		virtual Peca* getPeca( int posX, int posY ) = 0;
		
		virtual Peca** getJogadorPecas() = 0;
		virtual Peca** getComputadorPecas() = 0;

		virtual void deleta_pecas() = 0;
					
};

#endif
