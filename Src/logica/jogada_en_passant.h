
#ifndef JOGADA_EN_PASSANT_H
#define JOGADA_EN_PASSANT_H

#include "jogada.h"
#include "peca.h"

class JogadaEnPassant : public Jogada {
	
	public:
		JogadaEnPassant( int posX, int posY, Peca* captura );
		~JogadaEnPassant();
};

#endif
