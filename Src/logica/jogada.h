
#ifndef JOGADA_H
#define JOGADA_H

#include "peca.h"

class Jogada {
	protected:
		int posX;
		int posY;
		Peca* captura;
		
		int tipo;		
	
	public:
		const static int NORMAL = 1;
		const static int ROQUE = 2;
		const static int EN_PASSANT = 3;
		
		Jogada( int posX, int posY, Peca* captura, int tipo );
		virtual ~Jogada();

		virtual Jogada* nova();

		int getPosX();
		int getPosY();
		Peca* getCaptura();
		int getTipo();
		
		void setPosX( int x );
		void setPosY( int y );
		void setCaptura( Peca* captura );
		void setTipo( int tipo );
};

#endif
