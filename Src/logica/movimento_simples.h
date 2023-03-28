
#ifndef MOVIMENTO_SIMPLES_H
#define MOVIMENTO_SIMPLES_H

#include "peca.h"

class MovimentoSimples {
	
	private:
		Peca* peca;
		int posX1;
		int posY1;
		int posX2;
		int posY2;
		
		int raio;
		
		bool moveu;
		
	public:
		MovimentoSimples( Peca* peca, int posX1, int posY1, int posX2, int posY2 );
		
		Peca* getPeca();
		int getPosX1();
		int getPosY1();
		int getPosX2();
		int getPosY2();
		
		int getRaio();
		void setRaio( int raio );
		
		bool isMoveu();
		void setMoveu( bool moveu );
	
};

#endif
