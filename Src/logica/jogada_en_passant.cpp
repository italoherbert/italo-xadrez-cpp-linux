
#include "jogada_en_passant.h"

JogadaEnPassant::JogadaEnPassant( int posX, int posY, Peca* captura ) 
		: Jogada( posX, posY, captura, EN_PASSANT ) {
}

JogadaEnPassant::~JogadaEnPassant() {

}
