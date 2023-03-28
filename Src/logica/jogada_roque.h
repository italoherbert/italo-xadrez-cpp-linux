
#ifndef JOGADA_ROQUE_H
#define JOGADA_ROQUE_H

#include "jogada.h"

class JogadaRoque : public Jogada {
	
	private:
		Peca* rei;
		Peca* torre;
		
		int torrePosX;
		int torrePosY;
	
	public:
		JogadaRoque( int reiPosX, int reiPosY, int torrePosX, int torrePosY, Peca* captura, Peca* rei, Peca* torre );
		~JogadaRoque();
		
		JogadaRoque* nova();
		
		int getReiPosX();
		int getReiPosY();
		int getTorrePosX();
		int getTorrePosY();
		
		Peca* getRei();
		Peca* getTorre();
		
		void setRei( Peca* rei );
		void setTorre( Peca* torre );
};

#endif
